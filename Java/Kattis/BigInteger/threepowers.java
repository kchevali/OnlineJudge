import java.math.BigInteger;
import java.util.*;

public class threepowers {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        BigInteger n = new BigInteger(scan.next());
        StringBuilder sb = new StringBuilder();
        BigInteger three = new BigInteger("3");
        while (n.compareTo(BigInteger.ZERO) > 0) {
            n = n.subtract(BigInteger.ONE);
            BigInteger num = BigInteger.ONE, i = BigInteger.ONE;
            sb.append("{ ");
            int count = n.bitCount();
            for (int j = 0; j < 64; j++) {
                if (n.and(i).compareTo(BigInteger.ZERO) != 0)
                    sb.append(num).append(--count > 0 ? ", " : "");
                num = num.multiply(three);
                i = i.shiftLeft(1);
            }
            sb.append(" }\n");

            n = new BigInteger(scan.next());

        }
        System.out.print(sb.toString());
    }
}