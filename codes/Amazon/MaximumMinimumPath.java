package main.java._OA.Amazon;

public class MaximumMinimumPath {
    /**
     * [8, 4, 7]
     * [6, 5, 9]
     * 有3条path：
     * 8-4-7-9 min: 4
     * 8-4-5-9 min: 4
     * 8-6-5-9 min: 5
     * return: 5
    * */


    static int helper(int[][] matrix){
        int[] result = new int[matrix[0].length];
        result[0] = matrix[0][0];
        for (int i = 1; i < matrix[0].length; i++) {
            result[i] = Math.min(result[i - 1], matrix[0][i]);
        }
        for (int i = 1; i < matrix.length; i++) {
            result[0] = Math.min(matrix[i][0], result[0]);
            for (int j = 1; j < matrix[0].length; j++) {
                result[j] = (result[j] < matrix[i][j] && result[j - 1] < matrix[i][j]) ?
                            Math.max(result[j - 1], result[j]) : matrix[i][j];
            }
        }
        return result[result.length - 1];
    }

}
