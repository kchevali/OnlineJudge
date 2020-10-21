import java.util.*;

class asciiaddition {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        String[] rows = new String[7];
        for (int i = 0; i < 7; i++)
            rows[i] = keyboard.nextLine();

        int charCount = (rows[0].length() + 1) / 6;
        String stringForm = "";
        HashMap<String, String> artToString = new HashMap<>();// reading input

        String[] stringToArt = { "xxxxxx...xx...xx...xx...xx...xxxxxx", "....x....x....x....x....x....x....x",
                "xxxxx....x....xxxxxxx....x....xxxxx", "xxxxx....x....xxxxxx....x....xxxxxx",
                "x...xx...xx...xxxxxx....x....x....x", "xxxxxx....x....xxxxx....x....xxxxxx",
                "xxxxxx....x....xxxxxx...xx...xxxxxx", "xxxxx....x....x....x....x....x....x",
                "xxxxxx...xx...xxxxxxx...xx...xxxxxx", "xxxxxx...xx...xxxxxx....x....xxxxxx" };// creating output

        for (int i = 0; i < 10; i++) {
            artToString.put(stringToArt[i], "" + i);

        }
        artToString.put(".......x....x..xxxxx..x....x.......", "+");

        for (int i = 0; i < charCount; i++) {
            String ascii = "";
            for (int j = 0; j < 7; j++)
                ascii += rows[j].substring(i * 6, (i * 6) + 5);
            stringForm += artToString.get(ascii);
        }
        String[] nums = stringForm.split("\\+");
        String sol = "" + (Integer.parseInt(nums[0]) + Integer.parseInt(nums[1]));
        String out = "";
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < sol.length(); j++) {
                out += stringToArt[sol.charAt(j) - '0'].substring(i * 5, (i + 1) * 5);
                if (j < sol.length() - 1)
                    out += ".";
            }
            out += "\n";
        }
        System.out.print(out);
    }
}