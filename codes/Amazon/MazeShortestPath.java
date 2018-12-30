package main.java._OA.Amazon;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class MazeShortestPath {
    // 1 is road
    private final static int[][] DIR = new int[][]{{0,1},{0,-1},{1,0},{-1,0}};
    public static int path(List<List<Integer>> matrix) {
        if (matrix == null || matrix.size() == 0 ||
                matrix.get(0).size() == 0) {
            return -1;
        }
        if (matrix.get(0).get(0) == 9) {
            return 0;
        }
        if (matrix.get(0).get(0) == 0) {
            return 0;
        }

        int m = matrix.size(), n = matrix.get(0).size();
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0});
        matrix.get(0).set(0, 0);
        int res = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            while (size-- > 0) {
                int[] curr = queue.poll();
                if (matrix.get(curr[0]).get(curr[1]) == 9) {
                    return res;
                }
                for (int i = 0; i < 4; i++) {
                    int[] next = {curr[0] + DIR[i][0], curr[1] + DIR[i][1]};
                    if (next[0] >= 0 && next[0] < m && next[1] >= 0 && next[1] < n) {
                        if (matrix.get(next[0]).get(next[1]) == 1) {
                            queue.offer(next);
                            matrix.get(next[0]).set(next[1], 0);
                        } else if (matrix.get(next[0]).get(next[1]) == 9) {
                            queue.offer(next);
                        }
                    }
                }
                res++;
            }
        }

        return -1;
    }


    private static class Coordinate {
        int x;
        int y;
        public Coordinate(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    public static int shortestPath(int[][] targetMap) {
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
                        if (targetMap[newCoor.x][newCoor.y] == 9) return path;
                        if (targetMap[newCoor.x][newCoor.y] == 1) {
                            queue.offer(newCoor);
                            // set.add(newCoor);
                            targetMap[newCoor.x][newCoor.y] = 0;
                        }
                    }
                }
            }
        }

        return -1;


    }

    private static boolean isValid(int[][] map, Coordinate coor) {
        return coor.x >= 0 && coor.x < map.length && coor.y >= 0 && coor.y < map[0].length;
    }

    public static void main(String[] args) {
        int mat[][] =
        {
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
        };

        int mat2[][] =
                {
                        { 1, 0, 0 },
                        { 1, 0, 0 },
                        { 1, 9, 1 },
                };

        int mat3[][] =
                {
                        { 1, 1, 1, 1 },
                        { 0, 1, 1, 1 },
                        { 0, 1, 0, 1 },
                        { 1, 1, 9, 1 },
                        { 0, 0, 1, 1 },

                };

        List<List<Integer>> list = Arrays.stream(mat3)
                .map(row -> IntStream.of(row).boxed().collect(Collectors.toList()))
                .collect(Collectors.toList());

        //System.out.println(path(list));
        System.out.println(shortestPath(mat2));
    }
}
