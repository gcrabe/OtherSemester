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
    
    private final static int[] CNT = { 10, 20, 50, 100, 1000 };
    
    private static double function(double x) {
        return x * x;
    }
    
    public static void main(String[] args) {
        double a = 0.0, b = 1.0;
        
        for (int cntNodes : CNT) {
            double[] nodes = new double[cntNodes];
            
            for (int i = 0; i < cntNodes; i++) {
                nodes[i] = Math.random();
            }
            
            double temp = 0.0;
            
            for (int i = 0; i < cntNodes; i++) {
                temp += function(nodes[i]);
            }
            
            double res = (temp * (b - a)) / (double) cntNodes;
            System.out.printf("N = %4d, I = %.10f\n", cntNodes, res);
        }
    }
}
