/**
 * 
 */
package main;

/**
 * @author batyrev
 *
 */
public class Solution {

	private static final int MAXR = 12;
	private static final int MAXN = 1000;
	
	private static final double MU = 10.0;
	private static final double SIGMA = 2.0;
	
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
	
	public static void main(String[] args) {
		double[] z = new double[MAXN];
		double expectation = 0.0;
		
		for (int i = 0; i < MAXN; i++) {
			double fs = getNormal(MU, SIGMA);
			double sc = getNormal(MU, SIGMA);
			double td = getNormal(MU,  SIGMA);
			
			double temp = Math.max(fs, Math.max(sc, td));
			
			z[i] = temp;
			expectation += temp;
			
			System.out.printf("fs = %.2f\tsc = %.2f\ttd = %.2f\tz = %.2f\n", fs, sc, td, z[i]);
		}
		
		expectation /= (double) (MAXN);
		
		System.out.printf("expectation = %.7f\n", expectation);
		
		double dispersion = 0.0;
		
		for (int i = 0; i < MAXN; i++) {
			dispersion += (z[i] - expectation) * (z[i] - expectation);
		}
		
		dispersion /= (double) (MAXN - 1);
		
		System.out.printf("standard deviation = %.7f\n", Math.sqrt(dispersion));
	}
	
}
