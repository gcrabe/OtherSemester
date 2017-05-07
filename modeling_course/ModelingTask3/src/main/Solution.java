/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.util.Random;

/**
 *
 * @author gc
 */
public class Solution {
    
    private final static int CNT_TESTS = 1000;
    private static Random random = new Random(System.currentTimeMillis());
    
    private static int shot() {
        int[] parts = { 0, 0, 0, 0 };
        int res = 0;
        
        while (true) {
            for (int part : parts) {
                if (part >= 3) {
                    return res;
                }
            }
            
            parts[random.nextInt(4)]++;
            res++;
        }
    }
    
    public static void main(String[] args) {
        
        int[] tests = new int[CNT_TESTS];
        int countShots = 0;
        
        for (int i = 0; i < CNT_TESTS; i++) {
            tests[i] = shot();
            countShots += tests[i];
        }
        
        double ev = (double) countShots / (double) CNT_TESTS;
        System.out.printf("Expectation value = %.5f\n", ev);
    }
}
