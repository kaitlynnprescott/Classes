import java.util.*;
import java.lang.*;

class prime1 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		for (int t = scan.nextInt(); t > 0; t--){
			// Use standard sieve of Eratosthenes to find all primes up to 
			// and including sqrt(b), call them low_primes[]
			int a = scan.nextInt();
			int b = scan.nextInt();
			int n = ceil(sqrt(b));
			int[] low_primes = new int[n-1];
			for (int i=2; i<=n; i++) {
				low_primes[i-2] = i;
			}
			for (int div = 0; div <= n-1; div++) {
				int divides = low_primes[div];
				for (int i = 1; i <= n-1; i++) {
					if (low_primes[i]%divides == 0) {
						low_primes = ArrayUtils.removeElement(low_primes, i);
					}
				}
			}
			

			if (a < 2) 
				a = 2;
			...


			low_primes[0] = low_primes[1] = false;
			for (int i = 2; i <= sqrt_b; i++) {
				low_primes[i] = true;
			}
			for (int i = 2; len = sqrt(sqrt_b); i<= len; i++) {
				if (low_primes[i]) {
					for (int j = i*i; j<=sqrt_b; j+=i) {
						low_primes[j] = false;
					}
				}
			}


			// Create a boolean array high_primes[] with length = b - a + 1 
			// and initialize each element to true
			int len = b-a+1;
			int[] high_primes = new int[len];
			for (int i = 0; i<=len; i++){
				high_primes[i] = true;
			}
			// for each prime p in low_primes[],
          		// set i = ceil((double)a/p) * p - a
          		// if a <= p
                // set i = i + p
          		// starting at i, cross off all multiples of p in high_primes[]
			for (int p : low_primes) {
				int x = ceil((double)a/p)*p-a;
				if (a <= p){
					x = x+p;
				}
				for (int j = x; j <= len; j++) {
					if ((x+a)%p == 0) {
						high_primes = ArrayUtils.removeElement(high_primes, j);
					}
				}
			}
			for (int el = 0; el <= high_primes.length; el++) {
				System.out.println(high_primes[el]+a);
			}
		}
	}
}