/*******************************************************************************
 * Name          : LargeSum.java
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : February 8, 2016
 * Last modified : January 27, 2018
 * Description   : Solution to Project Euler #13 (Modified)
 ******************************************************************************/
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class LargeSum {
    private static List<String> bigNumbers = new ArrayList<String>();

    private static String removeLeadingZeros(String s) {
        int end = s.length();
        if (end == 1) {
            return s;
        }
        int i = 0;
        for (; i < end; i++) {
            if (s.charAt(i) != '0') {
                break;
            }
        }
        // If all digits were 0, return a single 0.
        return i != end ? s.substring(i) : "0";
    }

    private static void solve() {
        StringBuilder builder;
        if (bigNumbers.size() > 0) {
            // Implement the standard algorithm for addition.
            builder = new StringBuilder();
            int carry = 0;
            for (int charIndex = bigNumbers.get(0).length() - 1;
                    charIndex >= 0; charIndex--) {
                // Lower-order digits have higher index values, so work
                // backwards.
                int sumDigits = carry % 10;
                for (int numIndex = bigNumbers.size() - 1;
                        numIndex >= 0; numIndex--) {
                    sumDigits +=
                            bigNumbers.get(numIndex).charAt(charIndex) - 48;
                }
                builder.append(sumDigits % 10);
                carry /= 10;
                carry += sumDigits / 10;
            }
            while (carry > 0) {
                builder.append(carry % 10);
                carry /= 10;
            }
        } else {
            // If there were no numbers, the sum is vacuously 0.
            builder = new StringBuilder("0");
        }
        String sumString = removeLeadingZeros(builder.reverse().toString());
        System.out.println("Full sum: " + sumString);
        System.out.println("First 10 digits: " +
            sumString.substring(0, Math.min(10, sumString.length())));
    }

    public static void main(String[] args) {
        int maxLength = 0;
        try (BufferedReader reader = new BufferedReader(
                new FileReader("input.txt"))) {
            String line;
            // Read each line from the file, keeping track of the number of
            // digits found in the largest number.
            while ((line = reader.readLine()) != null) {
                bigNumbers.add(line);
                if (line.length() > maxLength) {
                    maxLength = line.length();
                }
            }
        } catch (IOException ioe) {
            System.err.println("Error: Cannot read file 'input.txt'.");
            System.exit(1);
        }
        for (int i = bigNumbers.size() - 1; i >= 0; i--) {
            String bigNumber = bigNumbers.get(i);
            StringBuilder builder = new StringBuilder();
            // Append 0s to a new StringBuilder, so that all numbers are the
            // same length.
            for (int j = 0, amount = maxLength - bigNumber.length();
                    j < amount; j++) {
                builder.append("0");
            }
            // Put the number after the 0s.
            builder.append(bigNumber);
            bigNumbers.set(i, builder.toString());
        }
        solve();
        System.exit(0);
    }
}
