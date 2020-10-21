import java.util.*;

class reverseBinary {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println(
                Integer.parseInt(new StringBuilder(Integer.toBinaryString(scan.nextInt())).reverse().toString(), 2));
    }
}