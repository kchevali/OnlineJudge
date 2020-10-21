import java.util.*;
import java.io.*;

public class getshorty {

  static int n, m;

  public static double dijkstra(int src, ArrayList<ArrayList<Pair>> adj) // start, end, adj[a][i], w[a][b]
  {

    PriorityQueue<Pair> q = new PriorityQueue<>(); // element {current height, current node number}

    ArrayList<Double> dis = new ArrayList<>();
    for (int i = 0; i < n; i++)
      dis.add(0.0);

    dis.set(src, 1.0);
    q.add(new Pair(1, src));
    while (!q.isEmpty()) {
      Pair p = q.poll(); // pq.poll()

      int a = p.second; // current node number
      if (a == n - 1)
        return dis.get(a);
      for (Pair pp : adj.get(a)) { // go to all adj nodes
        int b = pp.second; // next node number
        double d = dis.get(a) * pp.first; // (current height at a) * (fraction of the next node)

        // cout << "FROM: " << a << " TO " << b << " Height: " << d << "\n";
        // System.out.println("From: " + a + " TO " + b + " H: " + d);
        if (d > dis.get(b)) {
          dis.set(b, d);
          q.add(new Pair(d, b)); // {current height at node b, the node number b}
        }
      }
    }
    return dis.get(n - 1);
  }

  public static void main(String[] args) throws Exception {
    BufferedReader scan = new BufferedReader(new InputStreamReader(System.in));

    while (true) {
      StringTokenizer line = new StringTokenizer(scan.readLine());
      n = Integer.parseInt(line.nextToken());
      m = Integer.parseInt(line.nextToken());
      if (n + m == 0)
        break;

      ArrayList<ArrayList<Pair>> adj = new ArrayList<>();
      for (int i = 0; i < n; i++) {
        adj.add(new ArrayList<>());
      }

      for (int i = 0; i < m; i++) {
        line = new StringTokenizer(scan.readLine());
        int a = Integer.parseInt(line.nextToken()), b = Integer.parseInt(line.nextToken());
        double w = Double.parseDouble(line.nextToken());
        adj.get(a).add(new Pair(w, b)); // (fraction , node number)
        adj.get(b).add(new Pair(w, a));
      }
      System.out.printf("%.4f\n", dijkstra(0, adj));
    }
  }
}

class Pair implements Comparable<Pair> {
  double first;
  int second;

  public Pair(double first, int second) {
    this.first = first;
    this.second = second;
  }

  public int compareTo(Pair other) {
    return -Double.compare(first, other.first);
  }
}