// Author: Curt Powley, Hawaii Pacific University, cpowley@hpu.edu, 
// Algorithm: bfs
// Problem: grid, Kattis

// Programming notes:

import java.io.*;
import java.util.*;

public class grid {

    static int R, C;
    static Node[][] grid;
    static Queue<Node> vertexQueue = new LinkedList<>();

    public static void main(String[] args) throws IOException {

        // Scanner in = new Scanner(System.in);
        Scanner in = new Scanner(System.in);
        R = in.nextInt(); // number of rows
        C = in.nextInt(); // number of cols
        grid = new Node[R][C];

        for (int r = 0; r < R; r++) {
            String numStr = in.next(); // read row digits into a String
            for (int c = 0; c < C; c++) {
                grid[r][c] = new Node(r, c, numStr.charAt(c) - '0');
            }
        }
        System.out.println(bfs(grid[0][0]));
    }

    public static void move(int col, int row, int dist) {
        if (col >= 0 && col < C && row >= 0 && row < R) {
            Node n = grid[row][col];
            if (!n.isDone) {
                n.isDone = true;
                n.dist = dist;
                vertexQueue.add(n);
            }
        }
    }

    public static int bfs(Node source) {
        source.dist = 0;
        vertexQueue.add(source);
        while (!vertexQueue.isEmpty()) {
            Node n = vertexQueue.poll();
            int x = n.col, y = n.row, val = n.val;
            if ((n.row == R - 1) && (n.col == C - 1))
                return (n.dist);

            int new_dist = n.dist + 1;
            move(x + val, y, new_dist);
            move(x - val, y, new_dist);
            move(x, y + val, new_dist);
            move(x, y - val, new_dist);
        }
        return -1;
    }

    public static class Node {
        public int row;
        public int col;
        public int val;
        public int dist = 10000000;
        public boolean isDone = false;

        public Node(int r, int c, int val) {
            this.row = r;
            this.col = c;
            this.val = val;
        }
    }

}
