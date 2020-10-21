
import java.util.*;
import java.io.*;
import java.awt.Point;
import java.awt.geom.*;
import java.math.*;

public class abstractart {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        Area a = new Area();
        double area = 0.0;
        for (int i = 0; i < n; i++) {
            String[] line = br.readLine().split(" ");
            int count = Integer.parseInt(line[0]);
            double[] x = new double[count], y = new double[count];
            for (int j = 0; j < count; j++) {
                x[j] = Double.parseDouble(line[2 * j + 1]);
                y[j] = Double.parseDouble(line[2 * j + 2]);
            }
            a.add(makeArea(x, y));
            area += computeArea(x, y);
        }
        System.out.printf("%.8f %.8f\n", Math.abs(area), Math.abs(computeArea(a)));
    }

    public static Area makeArea(double[] x, double[] y) {
        Path2D.Double p = new Path2D.Double();
        p.moveTo(x[0], y[0]);
        for (int i = 1; i < x.length; i++)
            p.lineTo(x[i], y[i]);
        p.closePath();
        return new Area(p);
    }

    public static double computeArea(double[] x, double[] y) {
        double area2 = 0;
        for (int i = 0; i < x.length; i++) {
            int j = i + 1;
            if (j >= x.length) {
                j -= x.length;
            }

            area2 += (x[i] * y[j] - x[j] * y[i]);
        }

        return area2 / 2.0;
    }

    public static double computeArea(Area a) {
        double ret = 0.0;
        PathIterator iter = a.getPathIterator(null);
        double[] buffer = new double[6];
        List<Double> ps = new ArrayList<>();

        while (!iter.isDone()) {
            switch (iter.currentSegment(buffer)) {
            case PathIterator.SEG_MOVETO:
            case PathIterator.SEG_LINETO:
                ps.add(buffer[0]);
                ps.add(buffer[1]);
                break;
            case PathIterator.SEG_CLOSE:
                ps.add(ps.get(0));
                ps.add(ps.get(1));
                Double[] qs = ps.toArray(new Double[0]);
                for (int i = 0; i + 2 < ps.size(); i += 2) {
                    ret -= qs[i] * qs[i + 3] - qs[i + 1] * qs[i + 2];
                }
                ps.clear();
                break;
            }

            iter.next();
        }

        return ret / 2.0;
    }
}
