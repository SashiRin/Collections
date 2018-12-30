package main.java._OA.Amazon;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MaxPair {
    public int[][] getAns(int[] a, int[] b, int x) {
        // Write your code here.
        Arrays.sort(a);
        Arrays.sort(b);
        List<int[]> result = new ArrayList<>();
        int curMax = Integer.MIN_VALUE;
        int index1 = 0, index2 = b.length - 1;
        while (index1 < a.length && index2 >= 0) {
            if (index1 != 0 && a[index1] == a[index1 - 1]) {
                index1++;
                continue;
            }
            if (index2 != b.length - 1 && b[index2] == b[index2 + 1]) {
                index2--;
                continue;
            }
            int sum = a[index1] + b[index2];
            if (sum > x) {
                index2--;
            } else {
                if (sum > curMax) {
                    result = new ArrayList<int[]>();
                    result.add(new int[]{a[index1], b[index2]});
                    curMax = sum;
                } else if (sum == curMax) {
                    result.add(new int[]{a[index1], b[index2]});
                    //index2--;
                }
                index1++;
            }
        }
        return result.toArray(new int[result.size()][]);
    }
}
