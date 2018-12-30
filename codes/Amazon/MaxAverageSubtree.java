package main.java._OA.Amazon;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/*
*             20
     12                18
 11  2  3           15     8
* */

public class MaxAverageSubtree {
    private static class Node {
        int val;
        List<Node> children;

        public Node(int _val, List<Node> _children) {
            val = _val;
            children = _children;
        }
    }

    private static class ResultType {
        public int sum, size;
        public ResultType(int sum, int size) {
            this.sum = sum;
            this.size = size;
        }
    }

    private static Node subtree = null;
    private static ResultType subtreeResult = null;

    public static Node findSubtree(Node root) {
        // write your code here
        helper(root);
        System.out.println("Average: " + (double)subtreeResult.sum / subtreeResult.size);
        return subtree;
    }

    private static ResultType helper(Node root) {
        if (root.children == null) {
            return new ResultType(root.val, 1);
        }

        int sum = 0, size = 0;
        for (Node elem : root.children) {
            ResultType child = helper(elem);
            sum += child.sum;
            size += child.size;
        }

        ResultType result = new ResultType(sum, size);

        if (subtree == null ||
                subtreeResult.sum * result.size <
                        result.sum * subtreeResult.size) {
            subtree = root;
            subtreeResult = result;
        }
        return result;

    }

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
                new Node(5, null),
                new Node(-1, null)
        )));

        Node root2 = new Node(1, new ArrayList<>(Arrays.asList(aa, bb)));

        Node res = findSubtree(root2);
        System.out.println(res.val);
    }
}
