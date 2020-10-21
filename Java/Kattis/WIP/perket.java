import java.util.*;

class perket {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int count = (1 << n);
        int[] sour = new int[n], bitter = new int[n];
        for (int i = 0; i < n; i++) {
            sour[i] = scan.nextInt();
            bitter[i] = scan.nextInt();
        }
        int min = Integer.MAX_VALUE;
        for (int i = 1; i < count; i++) {
            int s = 1, b = 0;
            for (int j = 1, k = 0; j != 0; j <<= 1, k++) {
                if ((j & i) != 0) {
                    s *= sour[k];
                    b += bitter[k];
                }
            }
            min = Math.min(min, Math.abs(b - s));
        }
        System.out.println(min);
    }
}