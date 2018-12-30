package main.java._OA.Amazon;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CompanyTree {
    private static class Node {
        int val;
        List<Node> children;

        public Node(int _val, List<Node> _children) {
            val = _val;
            children = _children;
        }
    }

    private static class ResultType {
        public int sum, num;
        double maxAvg;
        public ResultType(int sum, int num, double maxAvg) {
            this.sum = sum;
            this.num = num;
            this.maxAvg = maxAvg;
        }
    }

    public static Node getMaxAvgSubtree(Node root){
        if(root == null) return root;
        Node[] ans = new Node[1];
        helper(root, ans);
        return ans[0];
    }
    public static ResultType helper(Node root, Node[] ans) {
        int sum = root.val, num = 1;
        double maxAvg = Integer.MIN_VALUE;
        if (root.children == null || root.children.isEmpty())
            return new ResultType(sum, num, maxAvg);
        for(Node child : root.children){
            ResultType rw = helper(child, ans);
            sum += rw.sum;
            num += rw.num;
            maxAvg = Math.max(maxAvg, rw.maxAvg);
        }
        double curAvg = (double) sum / num;
        if(curAvg > maxAvg){
            ans[0] = root;
            maxAvg = curAvg;
        }
        return new ResultType(sum, num, maxAvg);
    }

/*
*             20
     12                18
 11  2  3           15     8
* */

    public static void main(String[] args) {
        Node a = new Node(12, new ArrayList<>(Arrays.asList(
                new Node(11, null),
                new Node(2, null),
                new Node(3, null)
        )));

        Node b = new Node(18, new ArrayList<>(Arrays.asList(
                new Node(15, null),
                new Node(8, null)
        )));

        Node root = new Node(20, new ArrayList<>(Arrays.asList(a, b)));


        Node aa = new Node(5, new ArrayList<>(Arrays.asList(
                new Node(1, null),
                new Node(2, null)
        )));

        Node bb = new Node(11, new ArrayList<>(Arrays.asList(
                new Node(44, null),
                new Node(-1, null)
        )));

        Node root2 = new Node(1, new ArrayList<>(Arrays.asList(aa, bb)));

        Node res = getMaxAvgSubtree(root2);
        System.out.println(res.val);
    }
}
