package main.java._OA.Amazon;

import java.util.Comparator;
import java.util.PriorityQueue;

public class TopKNearestPoint {

     private static class Point {
          int x;
          int y;
          Point(int a, int b) { x = a; y = b; }
     }

    public Point[] kClosest(Point[] points, Point origin, int k) {
        // write your code here
        PriorityQueue<Point> pq = new PriorityQueue<>(k, new Comparator<Point>(){
            public int compare(Point a, Point b) { //maxheap
                int diff = dis(b, origin) - dis(a, origin);
                if (diff == 0) {
                    diff = b.x - a.x;
                }
                if (diff == 0) {
                    diff = b.y - a.y;
                }
                return diff;
            }
        });

        for (Point pt: points) {
            pq.add(pt);
            if (pq.size() > k) {
                pq.poll();
            }
        }

        Point[] res = new Point[k];
        while (k > 0) {
            res[--k] = pq.poll();
        }
        return res;
    }



    public int dis(Point a, Point b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
}
