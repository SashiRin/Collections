package main.java._OA.Amazon;


import java.util.LinkedList;
import java.util.Queue;

public class MazePath {

    class Coordinate {
        int x;
        int y;
        public Coordinate(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    public int shortestPath(int[][] targetMap) {
        // Write your code here
        if (targetMap == null || targetMap.length == 0 || targetMap[0].length == 0) return 0;

        Queue<Coordinate> queue = new LinkedList<>();
        // Set<Coordinate> set = new HashSet<>();

        Coordinate origin = new Coordinate(0, 0);
        queue.offer(origin);
        // set.add(origin);

        int[] X = new int[]{1, -1, 0, 0};
        int[] Y = new int[]{0, 0, 1, -1};

        int path = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            path++;
            for (int i = 0; i < size; i++) {
                Coordinate curr = queue.poll();
                for (int j = 0; j < 4; j++) {
                    Coordinate newCoor = new Coordinate(curr.x + X[j], curr.y + Y[j]);
                    if (isValid(targetMap, newCoor)) {
                        if (targetMap[newCoor.x][newCoor.y] == 2) return path;
                        if (targetMap[newCoor.x][newCoor.y] == 0) {
                            queue.offer(newCoor);
                            // set.add(newCoor);
                            targetMap[newCoor.x][newCoor.y] = 1;
                        }
                    }
                }
            }
        }

        return -1;


    }

    private boolean isValid(int[][] map, Coordinate coor) {
        return coor.x >= 0 && coor.x < map.length && coor.y >= 0 && coor.y < map[0].length;
    }
}