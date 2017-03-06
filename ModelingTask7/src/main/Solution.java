/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

/**
 *
 * @author gc
 */
public class Solution {

    private static final int MAXN = 1000;
    private static final double LAMBDA = 0.075;
    private static final double TIME = 10.0;
    private static final double EPS = 1e-5;
    
    private static double getExponential(double lambda) {
        return - (1 / lambda) * Math.log(Math.random());
    }
    
    public static void main(String[] args) {
        int cntFault = 0;
        double mid = 0;
        
        for (int curTest = 0; curTest < MAXN; curTest++) {
            double fs = getExponential(LAMBDA);
            double sc = getExponential(LAMBDA);
            
            boolean fsCannon = (fs + EPS <= TIME);
            boolean scCannon = (sc + EPS <= TIME);
            
            if (fsCannon && scCannon) {
                mid += Math.min(fs, sc);
                cntFault++;
                continue;
            }
            
            if (fsCannon) {
                mid += fs;
                cntFault++;
            }
            
            if (scCannon) {
                mid += sc;
                cntFault++;
            }
        }
        
        double ml = mid / (double) cntFault;
        double p = (double) cntFault / (double) MAXN;
        
        System.out.printf("mid lifetime = %.5f\nalive probability = %.5f\n", ml, 1.0 - p);
    }
    
}
