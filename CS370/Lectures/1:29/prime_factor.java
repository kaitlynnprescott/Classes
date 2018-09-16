import java.util.*;

class prime_factor {

	// public static List<Integer> prime_factor(int num) {
	// 	int n = num;
	// 	List<Integer> factors = new ArrayList<Integer>();
	// 	for (int i = 2; i <= n/i; i++) {
	// 		while (n%i == 0) {
	// 			factors.add(i);
	// 			n /= i;
	// 		}
	// 	}
	// 	if (n > 1) {
	// 		factors.add(n);
	// 	}
	// 	return factors;
	// }

	public static void main(String[] args) {
		// System.out.println("Primefactors of 517");
  //       for (Integer integer : prime_factor(517)) {
  //           System.out.println(integer);
  //       }
		
		long start = System.nanoTime(),
			n = Long.parseLong(args[0]);
        int i = 2, maxFactor = (int)Math.sqrt(n);
        while (i <= maxFactor) {
        	if (n % i == 0) {
        		n /= i;
        		System.out.println(i);
        		
        		maxFactor = (int)Math.sqrt(n);
        	} else {
        		i++;
        	}
        }
        System.out.println(n);
        double elapsed = (System.nanoTime() - start)/1e6;
        System.out.println("Elapsed time: " + elapsed + " ms");



	}
}