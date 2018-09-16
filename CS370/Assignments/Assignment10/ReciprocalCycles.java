/*
*
*   Meng Qui, Kaitlynn Prescott, Christopher Rudel
*   ReciprocalCycles.java
*   We pledge our honor that we have abided by the Stevens Honor System
*
*/

import java.math.BigDecimal;
import java.math.BigInteger;


class ReciprocalCycles {
	public static final BigInteger NINE = BigInteger.valueOf(9);

	public static void main(String[] args) {
		if (args.length != 1) {
			// incorrect number of parameters
			System.out.println("Usage: denominator");
		}
		// save denominator as integer
		int den = Integer.parseInt(args[0]);
		long denominator = Long.parseLong(args[0]);
		if (denominator < 1 || denominator > 2000) {
			// denominator out of range
			System.out.println("Error: Denominator must be an integer in [1,2000]. Recieved '" + denominator + "'.");
			System.exit(1);
		}

		String soln = repeating_fraction(1, denominator);
		// check if it is recurring
		if (isRecurring(1, den)) {
			int ind = soln.indexOf("(");
			int count = 0;
			String[] arr = soln.split("");
			// get length of recurring cycle
			for (int i = ind+1; i < arr.length-1; i++) {
				if (arr[i] == ")"){
					break;
				}
				count += 1;
			}
			System.out.println("1/" + args[0] + " = " + soln + ", cycle length " + count);
		} else {
			// not recurring
			System.out.println("1/" + args[0] + " = " + soln);
		}
	}

	private static String repeating_fraction(long num, long den) {
		// use string builder to easily add to the string
		StringBuilder sb = new StringBuilder();
		// get non-decimal places of division
		sb.append(num/den);
		sb.append(".");
		// get remainder to divide for decimal place
		num %= den;
		// rest is basically long division
		for (int i = 3, lim = (int)Math.sqrt(num); i <= lim; i++) {
			// divide by i while possible for i from 3 to square root of numerator
			while (num % i == 0 && den % i == 0) {
				num /= i;
				den /= i;
			}
		}
		while (num > 0) {
			// divide by 2 while possible
			while (den % 2 == 0 && num % 2 == 0) {
				num /= 2;
				den /= 2;
			}
			// divide by 5 while possible
			while (den % 5 == 0 && num % 5 == 0) {
				num /= 5;
				den /= 5;
			}
			// get big integers
			BigInteger nine = NINE;
			BigInteger denBI = BigInteger.valueOf(den);
			long lim = den;
			// divide by 2 while possible
			while (lim % 2 == 0) 
				lim /= 2;
			// divide by 5 while possible
			while (lim % 5 == 0)
				lim /= 5;
			// get the next decimal place, and add it to sb, formatted for recurring values
			for (int j = 1; j <= lim; j++, nine = nine.multiply(BigInteger.TEN).add(NINE)) {
				if (nine.mod(denBI).equals(BigInteger.ZERO)) {
					BigInteger repeat = BigInteger.valueOf(num).multiply(nine).divide(denBI);
					sb.append('(').append(String.format("%0" + j + "d", repeat)).append(')');
					return sb.toString();
				}
			}
			// get ready for next value
			num *= 10;
			sb.append(num/den);
			// get the remainder
			num %= den;
		}
		return sb.toString();
	}

	static boolean isRecurring(int numerator, int denominator) {
		// checks if a division results in a recurring number
		BigDecimal n = new BigDecimal(numerator);
    	n.setScale(2 * denominator + 1);
    	BigDecimal d = new BigDecimal(denominator);
    	try {
       		n.divide(d);
       		// not recurring
        	return false;
    	} catch (ArithmeticException ae) {
    		// recurring
        	return true;
    	}
    }
}