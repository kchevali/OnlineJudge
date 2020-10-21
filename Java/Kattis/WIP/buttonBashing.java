// Author: Curt Powley, Hawaii Pacific University, cpowley@hpu.edu, 
// Algorithm: bfs
// Problem: grid, Kattis

// Programming notes:

import java.io.*;
import java.util.*;

public class buttonBashing {

    static int buttonCount, target;
    static final int MAX_T = 3600 * 2 + 10;
    static int[] buttons = new int[16], dist = new int[MAX_T];
    static boolean[] visited = new boolean[MAX_T];

    public static void main(String[] args) throws IOException {

        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            buttonCount = in.nextInt();
            target = in.nextInt() + 3600;
            for (int j = 0; j < buttonCount; j++) {
                buttons[j] = in.nextInt();
            }
            for (int j = 0; j < MAX_T; j++) {
                dist[j] = 10000000;
                visited[j] = false;
            }
            int endTime = bfs();
            System.out.println((dist[endTime]) + " " + (endTime - target));
        }
    }

    public static int bfs() {
        int source = 3600;
        dist[source] = 0;
        if (target == source)
            return target;

        int greatestLowerBound = MAX_T - 1;
        Queue<Integer> vertexQueue = new LinkedList<>();
        vertexQueue.add(source);

        while (!vertexQueue.isEmpty()) {
            int n = vertexQueue.poll();
            for (int i = 0; i < buttonCount; i++) {
                int m = Math.max(0, Math.min(7200, n + buttons[i]));
                if (!visited[m]) {
                    dist[m] = dist[n] + 1;
                    if (m == target)
                        return target;
                    if (m > target)
                        greatestLowerBound = Math.min(m, greatestLowerBound);
                    visited[m] = true;
                    vertexQueue.add(m);
                }
            }
        }
        return greatestLowerBound;
    }

}
