/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
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
 * @author batyrev
 */
public class Solution {

    private static final int MAXC = 700;
    private static final int MAXN = 100;

    private static double getEponential(double lambda) {
        return -(1 / lambda) * Math.log(Math.random());
    }

    public static void main(String[] args) {
        XYSeries series = new XYSeries("Solution plot");
        
        double[] lambda = new double[MAXN];
        double[] batteryLifetime = new double[MAXN];

        for (int i = 0; i < MAXN; i++) {
            lambda[i] = i + 1;
            batteryLifetime[i] = 0;
        }

        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXC; j++) {
                double temp = getEponential(lambda[i]);
                batteryLifetime[i] += temp;
            }
            
            series.add(lambda[i], batteryLifetime[i]);
            System.out.printf("lambda = %.1f\tbl = %.5f\n", lambda[i], batteryLifetime[i]);
        }
        
        XYDataset dataset = new XYSeriesCollection(series);
        JFreeChart chart = ChartFactory.createXYLineChart("Solution plot", "lambda", "battery-lifetime(lambda)", dataset,
                PlotOrientation.VERTICAL, true, true, true);
        
        JFrame frame = new JFrame("Solution plot");
        
        frame.getContentPane().add(new ChartPanel(chart));
        frame.setSize(800, 600);
        frame.show();
    }
}

