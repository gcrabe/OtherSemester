package main;

import javax.swing.JFrame;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 *
 * @author gc
 */
public class Solution {

    final static double EPS = 0.01;
    
    static XYSeries series = new XYSeries("Solution plot");
    
    public static double firstFunction(double x, double y) {
        double l = 10.0, m = 5;
        double c1 = 0.0, c2 = 0.3;
        double g = 9.8;
        
        return -x;
    }
    
    public static double secondFunction(double x, double y) {
        return y;
    }
    
    public static void solve(double xPrev, double yPrev) {
        double xCur = 0, yCur = 0;
        
        double h = 0.01;
        double t = 0, dt = 0.01;
        
        series.add(xPrev, yPrev);
        
        for (int i = 0; i < 100; i++) {
            xCur = xPrev + h * firstFunction(xPrev, yPrev);
            yCur = yPrev + h * secondFunction(xPrev, yPrev);
            
            t += dt;
            
            xPrev = xCur;
            yPrev = yCur;
            
            series.add(xCur, yCur);
        }
    }
    
    public static void main(String[] args) {
        JFrame frame = new JFrame("Solution plot");
        
        solve(1, 1);
        
        XYDataset dataset = new XYSeriesCollection(series);
        JFreeChart chart = ChartFactory.createXYLineChart("Solution plot", "x(t)", "y(t)", dataset,
                PlotOrientation.VERTICAL, true, true, true);
        
        frame.getContentPane().add(new ChartPanel(chart));
        
        frame.setSize(800, 600);
        frame.show();
    }
}
