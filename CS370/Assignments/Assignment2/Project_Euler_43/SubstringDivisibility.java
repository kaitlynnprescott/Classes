/************************************************************************************
 * Name        : SubstringDivisibility.java
 * Author      : Kaitlynn Prescott, Christopher Rudel, Meng Qiu
 * Date        : Feb 5, 2018
 * Description : Project Euler #43 - Modified
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/
import java.util.*;
import java.lang.*;

class SubstringDivisibility {

	private static int[] DIVISORS = {2, 3, 5, 7, 11, 13, 17};

	// converts integer array to long and returns it
	private static long toLong(ArrayList<Integer> arr, int off, int len)
	{
		long answer=0;
		StringBuilder ans = new StringBuilder("");
		for(int i=off; i<off+len; i++)
			ans.append(arr.get(i));
		answer = Long.parseLong(ans.toString());
		return answer;	
	}

	// gets the next permutation of an integer array and returns true if it has one
	public static boolean nextPermutation(ArrayList<Integer> a) {
		int i, n = a.size();
		for (i = n-2; ; i--) {
			if (i < 0)
				return false;
			if (a.get(i) < a.get(i+1))
				break;
		}
		for (int j = 1; i+j < n-j; j++) {
			int temp = a.get(i+j);
			a.set(i+j, a.get(n-j));
			a.set(n-j, temp);
		}
		int j;
		for (j = i+1; a.get(j) <= a.get(i); j++);
		int temp = a.get(i);
		a.set(i, a.get(j));
		a.set(j, temp);
		return true;
	}

	public static void main(String[] args) {
		// get input_digits as array and length 
		ArrayList<Integer> digit_array = new ArrayList<Integer>();
		for(int i=0; i<args[0].length(); i++)
			digit_array.add(Character.getNumericValue(args[0].charAt(i)));

		// start timer
		long start = System.nanoTime();
		
		// get array of divisibility rules necessary:
		int num_length = digit_array.size();
		int num_rules = num_length-3;
		int[] rules = Arrays.copyOfRange(DIVISORS, 0, num_rules+1);

		// initalize sum to be 0  
		long sum = 0;

		// for each permutation, 
		outer:
		do {
			for (int i = 0; i < rules.length-1; i++) {
				if (toLong(digit_array, i+1, 3) % rules[i] != 0) {
					continue outer;
				}
			}
			// print out permutation that works and add it to sum
			long perm = toLong(digit_array, 0, digit_array.size());
			System.out.println(perm);
			sum += perm;
		} while (nextPermutation(digit_array));

		System.out.println("Sum: " + Long.toString(sum));
		System.out.printf("Elapsed time: %.6f ms\n", (System.nanoTime() - start) / 1e6);
	}
}