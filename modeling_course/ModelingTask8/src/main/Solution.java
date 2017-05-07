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

    private static final int MAXC = 700;
    private static final int MAXN = 100;

    private static double getEponential(double lambda) {
        return -(1 / lambda) * Math.log(Math.random());
    }

    public static void main(String[] args) {
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

            System.out.printf("lambda = %.1f\tbl = %.5f\n", lambda[i], batteryLifetime[i]);
        } 
    }
}

