import java.util.*;

class bubbletea {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        int[] ts = new int[t];
        for (int i = 0; i < t; i++)
            ts[i] = scan.nextInt();
        int top = scan.nextInt();
        int[] tops = new int[top];
        for (int i = 0; i < top; i++)
            tops[i] = scan.nextInt();
        int minCost = Integer.MAX_VALUE;
        for (int i = 0; i < t; i++) {
            int len = scan.nextInt();
            for (int j = 0; j < len; j++)
                minCost = Math.min(minCost, tops[scan.nextInt() - 1] + ts[i]);
        }
        System.out.println(Math.max(0, scan.nextInt() / minCost - 1));
    }
}