import java.io.*;
import java.util.*;

class recount {
    public static void main(String[] args) throws Exception {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        HashMap<String, Integer> map = new HashMap<>();
        String name;
        do {
            name = r.readLine();
            if (!map.containsKey(name)) {
                map.put(name, 1);
            } else {
                map.put(name, map.get(name) + 1);
            }
        } while (!name.equals("***"));

        int maxCount = 0;
        String maxName = "Runoff!";
        for (String key : map.keySet()) {
            int count = map.get(key);
            if (count > maxCount) {
                maxCount = count;
                maxName = key;
            } else if (count == maxCount) {
                maxName = "Runoff!";
            }
        }
        System.out.println(maxName);
    }
}