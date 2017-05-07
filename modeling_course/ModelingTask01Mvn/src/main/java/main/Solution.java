package main;

import javax.swing.JFrame;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author gc
 */
public class Solution {
    
    final static double EPS = 0.01;
    
    public static double function(double velocity) {
        double g = 9.8, k = 0.1;
        return - (g + k * velocity * velocity);
    }
    
    public static void main(String[] args) {
        XYSeries series = new XYSeries("Solution plot");
        
        double h = 0.01;
        double vPrev = 800, t = 0;
        double vCur;
        double x = 0;
        int i = 0;
        
        series.add(t, vPrev);
        
        do {
            vCur = vPrev + h * function(vPrev);
            t += h;
            x += vCur * h;
            vPrev  = vCur;
            
            series.add(t, vCur);
        } while (vCur > EPS);
        
        System.out.println("--------------------------------------------------");
        System.out.printf("t = %11.7f v(t) = %11.7f x(t) = %11.7f\n", t, vCur, x);
        
        XYDataset dataset = new XYSeriesCollection(series);
        JFreeChart chart = ChartFactory.createXYLineChart("Solution plot", "t", "v(t)", dataset,
                PlotOrientation.VERTICAL, true, true, true);
        
        JFrame frame = new JFrame("Solution plot");
        
        frame.getContentPane().add(new ChartPanel(chart));
        frame.setSize(800, 600);
        frame.show();
    }
}
