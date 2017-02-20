package main;

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
        double h = 0.01;
        double vPrev = 800, t = 0;
        double vCur;
        double x = 0;
        int i = 0;
        
        do {
            vCur = vPrev + h * function(vPrev);
            t += h;
            x += vCur * h;
            vPrev  = vCur;
            System.out.printf("%3d t = %11.7f v(t) = %11.7f x(t) = %11.7f\n", i++, t, vCur, x);
        } while (vCur > EPS);
        
        System.out.println("--------------------------------------------------");
        System.out.printf("t = %11.7f v(t) = %11.7f x(t) = %11.7f\n", t, vCur, x);
    }
}
