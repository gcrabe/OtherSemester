/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

/**
 *
 * @author batyrev
 */
public class Solution {
    
    private static final int MAXR = 12;
    private static final int MAXN = 1000;
    private static final double EPS = 1e-7;
    
    private static double getNormal(double mu, double sigma) {
        double[] r = new double[MAXR];
        
        for (int i = 0; i < MAXR; i++) {
            r[i] = Math.random();
        }
        
        double res = 0;
        
        for (int i = 0; i < MAXR; i++) {
            res += r[i];
        }
        
        return mu + sigma * (res - (double) (MAXR / 2));
    }
    
    private static boolean inSector(double value, double a, double b) {
        return value >= a && value <= b - EPS;
    }
    
    private static double getDiscrete() {
        double val = Math.random();
        
        if (inSector(val, 0.0, 0.10)) {
            return 10;
        } else if (inSector(val, 0.10, 0.35)) {
            return 20;
        } else if (inSector(val, 0.35, 0.85)) {
            return 30;
        } else if (inSector(val, 0.85, 1.00)) {
            return 40;
        }
        
        return -1.0;
    }
    
    public static void main(String[] args) {
        double[] z = new double[MAXN];
        double expectation = 0.0;
        
        for (int i = 0; i < MAXN; i++) {
            double a = getNormal(5.0, 2.0);
            double b = getNormal(3.0, 3.0);
            double c = getDiscrete();
            
            z[i] = (a + b) / c;
            expectation += z[i];
            
            System.out.printf("a = %.2f\tb = %.2f\tc = %.2f\tz = %.2f\n", a, b, c, z[i]);
        }
        
        expectation /= (double) MAXN;
        
        System.out.printf("expectation = %.5f\n", expectation);
        
        double dispersion = 0.0;
        
        for (int i = 0; i < MAXN; i++) {
            dispersion += (z[i] - expectation) * (z[i] - expectation);
        }
        
        dispersion /= (double) (MAXN - 1);
        
        System.out.printf("dispersion = %.5f\n", dispersion);
    }
}
