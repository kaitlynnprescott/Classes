/*******************************************************************************
 * Name          : SubstringDivisibility.java
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : January 27, 2018
 * Last modified : January 28, 2018
 * Description   : Solution to Project Euler #43 (Modified)
 *                 To solve the original Euler problem, run
 *                 java SubstringDivisibility 0123456789
 ******************************************************************************/
import java.util.ArrayList;
import java.util.Collections;

public class SubstringDivisibility {
    public static final int[] PRIMES = { 2, 3, 5, 7, 11, 13, 17 };
    private static ArrayList<String> values = new ArrayList<String>();
    private static long sum = 0;

    /**
     * Returns the integer value of the leftmost 3 digits in the string.
     * @param s the input string
     * @return an integer containing the value of the leftmost 3 digits
     *         in the string.
     */
    private static int threeDigitValue(String s) {
        int value = 0;
        for (int i = 0; i < 3; i++) {
            value = (value << 3) + (value << 1) + s.charAt(i) - '0';
        }
        return value;
    }

    /**
     * Returns a string without the character at index i. This method is
     * faster than concatenating two substrings.
     * @param s the string
     * @param index the index of the character to remove
     * @return a new string without the characeter at index i
     */
    private static String remove(String s, int index) {
        int len = s.length();
        StringBuilder builder = new StringBuilder(len - 1);
        for (int i = 0; i < len; i++) {
            if (i != index) {
                builder.append(s.charAt(i));
            }
        }
        return builder.toString();
    }

    /**
     * Generates all permutations that satisfy the requirements of the
     * problem definition of ProjectEuler #43.
     * @param s1 the string being built up
     * @param s2 the initial string of digits
     * @param primeIndex the index of the prime number used in the divisibility
     *                   test
     */
    private static void getPermutations(String s1, String s2, int primeIndex) {
        if (s2.equals("")) {
            values.add(s1);
            sum += Long.valueOf(s1);
        } else {
            if (s1.length() >= 3) {
                if (threeDigitValue(s1) % PRIMES[primeIndex] != 0) {
                    return;
                }
                primeIndex--;
            }
            for (int i = s2.length() - 1; i >= 0; i--) {
                getPermutations(s2.charAt(i) + s1, remove(s2, i), primeIndex);
            }
        }
    }
    
    public static void main(String[] args) {
        // Make sure there is exactly on command line argument.
        if (args.length != 1) {
            System.err.println(
                "Usage: java SubstringDivisibility <input string>");
            System.exit(1);
        }
        // Make sure the string contains between 4 and 10 characters.
        int sLength = args[0].length();
        if (sLength < 4 || sLength > 11) {
            System.err.println(
                "Error: String length must be between 4 and 10, inclusive.");
            System.exit(1);
        }
        // Make sure all characters are digits.
        for (int i = 0; i < sLength; i++) {
            char c = args[0].charAt(i);
            if (c < '0' || c > '9') {
                System.err.println("Error: Invalid character '" + c
                        + "' at index " + i + ".");
                System.exit(1);
            }
        }
        long start = System.nanoTime();
        getPermutations("", args[0], args[0].length() - 4);
        Collections.sort(values);
        for (String value : values) {
            System.out.println(value);
        }
        System.out.println("Sum: " + sum);
        System.out.printf("Elapsed time: %.6f ms\n",
                (System.nanoTime() - start) / 1e6);
        System.exit(0);
    }
}
