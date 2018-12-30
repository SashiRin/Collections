package main.java._OA.Amazon;

public class MaximumMinimumPath2 {
    private int min, max;
    public int maxMinPath(int[][] matrix) {
        min = Integer.MAX_VALUE;
        max = Integer.MIN_VALUE;
        dfsHelper(matrix, min, 0, 0);
        return max;
    }

    public void dfsHelper(int[][] matrix, int min, int i, int j ) {
        int row = matrix.length;
        int col = matrix[0].length;
        if (i >= row || j >= col) return;
        if (i == row - 1 && j == col - 1) {
            min = Math.min(min, matrix[i][j]);
            max = Math.max(max, min);
            return;
        }
        min = Math.min(min, matrix[i][j]);
        dfsHelper(matrix, min, i, j + 1);
        dfsHelper(matrix, min, i + 1, j);
    }
}
