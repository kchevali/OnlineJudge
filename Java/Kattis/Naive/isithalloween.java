import java.util.*;

class isithalloween {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String line = scan.nextLine();
        System.out.println(line.equals("OCT 31") || line.equals("DEC 25") ? "yup" : "nope");
    }
}