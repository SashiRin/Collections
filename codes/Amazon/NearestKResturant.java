package main.java._OA.Amazon;


import java.util.*;

public class NearestKResturant {
    /**
     * @param restaurant:
     * @param n:
     * @return: nothing
     */
    public List<List<Integer>> nearestRestaurant(List<List<Integer>> restaurant, int n) {
        List<List<Integer>> res = new ArrayList<>();
        if (restaurant == null || restaurant.size() == 0 || n <= 0) {
            return res;
        }
        if (restaurant.size() < n) {
            return res;
        }

        globalOrigin = new Point(0, 0, -1);

        Queue<Point> maxHeap = new PriorityQueue<>(n, comp);

        for (int i = 0; i < restaurant.size(); i++) {
            Point point = new Point(restaurant.get(i).get(0),
                    restaurant.get(i).get(1), i);
            maxHeap.offer(point);
            if (maxHeap.size() > n) {
                maxHeap.poll();
            }
        }

        List<Point> temp = new ArrayList<>();
        while (!maxHeap.isEmpty()) {
            Point point = maxHeap.poll();
            temp.add(0, point);
        }
        // sort temp list so that the points are in the original order:
        Collections.sort(temp, resComp);
        for (Point p : temp) {
            List<Integer> pair = new ArrayList<>();
            pair.add(p.x);
            pair.add(p.y);
            res.add(pair);
            System.out.println(p.x);
        }
        return res;
    }

    private class Point {
        int x, y, id;
        public Point(int inX, int inY, int inId) {
            this.x = inX;
            this.y = inY;
            this.id = inId;
        }
    }

    private Point globalOrigin;

    private int getDistance(Point a, Point b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }

    private Comparator<Point> comp = new Comparator<Point>() {
        @Override
        public int compare(Point a, Point b) {
            int diff = getDistance(b, globalOrigin) - getDistance(a, globalOrigin);
            if (diff == 0) {
                diff = b.x - a.x;
            }
            if (diff == 0) {
                diff = b.y - a.y;
            }
            return diff;
        }
    };

    private Comparator<Point> resComp = new Comparator<Point>() {
        @Override
        public int compare(Point a, Point b) {
            int diff = a.id - b.id;
            return diff;
        }
    };
}