package main.java._OA.Amazon;

import java.util.*;


public class CityConnection {

    public static class Connection {
        public String node1, node2;
        public int cost;
        public Connection(String city1, String city2, int cost) {
            this.node1 = city1;
            this.node2 = city2;
            this.cost = cost;
        }
    }

    public static ArrayList<Connection> getLowCost(ArrayList<Connection> connections) {
        if(connections == null || connections.isEmpty()) return connections;
        Collections.sort(connections, new Comparator<Connection>(){
            @Override
            public int compare(Connection c1, Connection c2){ return c1.cost - c2.cost; }
        });
        Map<String, String> map = new HashMap<String, String>();// pre-processing to make city connect to itself
        for(Connection con : connections){
            map.put(con.node1, con.node1);
            map.put(con.node2, con.node2);
        }
        ArrayList<Connection> ans = new ArrayList<Connection>(); // traverse connections to build MST
        for(Connection con : connections){
            String root1 = root(con.node1, map);
            String root2 = root(con.node2, map);
            if(root1.equals(root2)) continue; // if they are already connected
            map.put(root2, root1); // union them
            ans.add(con);
        }
        if(map.size() - 1 != ans.size())return null; //检查是否联通，不连通的话边更少
        Collections.sort(ans, new Comparator<Connection>(){
            @Override
            public int compare(Connection c1, Connection c2){
                if(c1.node1.equals(c2.node1))
                    return c1.node2.compareTo(c2.node2);
                return c1.node1.compareTo(c2.node1);
            }
        });
        return ans;
    }
}

/**
 * Definition for a Connection.
 * public class Connection {
 *   public String city1, city2;
 *   public int cost;
 *   public Connection(String city1, String city2, int cost) {
 *       this.city1 = city1;
 *       this.city2 = city2;
 *       this.cost = cost;
 *   }
 * }
 */
public class Solution {
    /**
     * @param connections given a list of connections include two cities and cost
     * @return a list of connections from results
     */
    private String find(String str, Map<String, String> father) {
        if (!father.containsKey(str)) {
            father.put(str, str);
        } else if (!father.get(str).equals(str)) {
            father.put(str, find(father.get(str), father));
        }

        return father.get(str);
    }

    public List<Connection> lowestCost(List<Connection> connections) {
        // Write your code here
        List<Connection> res = new ArrayList<Connection>();
        Collections.sort(connections, new Comparator<Connection>() {
            public int compare(Connection a, Connection b) {
                if (a.cost != b.cost) {
                    return a.cost - b.cost;
                }
                if (!a.city1.equals(b.city1)) {
                    return a.city1.compareTo(b.city1);
                }
                return a.city2.compareTo(b.city2);
            }
        });

        Map<String, String> father = new HashMap<>();
        for (Connection con : connections) {
            String root1 = find(con.city1, father);
            String root2 = find(con.city2, father);
            /*
            Kruskal's algorithm：
            将边排序后选择边，在选择边的过程中使用并查集维护保证无环。
            */
            if (!root1.equals(root2)) {
                father.put(root1, root2);
                res.add(con);
            }
        }

        if (res.size() != father.size() - 1) {
            return new ArrayList<Connection>();
        }

        return res;
    }
}