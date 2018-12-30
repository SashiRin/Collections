package main.java._OA.Amazon;

import java.util.Arrays;

public class ClosestTarget {
    public int closestTargetValue(int target, int[] array) {
        // Write your code here
        Arrays.sort(array);

        int start = 0;
        int end = array.length - 1;
        int min = Integer.MAX_VALUE;
        while (start < end) {
            int number = array[start] + array[end];
            if (number < target) {
                start++;
                min = Math.min((target - number), min);
            } else if (number > target) {
                end--;
            } else {
                return target;
            }
        }
        if (min == Integer.MAX_VALUE) {
            return -1;
        }

        return target - min;

    }
}
