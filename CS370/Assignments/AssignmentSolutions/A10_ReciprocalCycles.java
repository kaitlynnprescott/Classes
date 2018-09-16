/*******************************************************************************
 * Name        : ReciprocalCycles.java
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : February 29, 2016
 * Description : Solution to Project Euler #26 (Modified)
 ******************************************************************************/
public class ReciprocalCycles {
    public static final int MAX_DENOMINATOR = 2000;

    public static String fractionToDecimal(int numerator, int denominator) {
        // When bringing down the next digit from the dividend, the resulting
        // number will not exceed 10 x denominator.
        short[] visited = new short[denominator * 10];
        StringBuilder builder = new StringBuilder();
        int start = 0;
        short count = 1;
        // Allow it to work for numerators other than 1.
        builder.append(numerator / denominator);
        numerator %= denominator;
        if (numerator != 0) {
            builder.append(".");
            numerator *= 10;
            // Perform long division until either the numerator is 0 (and the
            // division terminates naturally) or when bringing down the next
            // digit from the dividend, the resulting number has already been
            // seen (yielding one full cycle of repeating digits).
            while (true) {
                // Keep track of the count to figure out how long the cycle is.
                visited[numerator] = count++;
                int quotient = numerator / denominator;
                builder.append(quotient);
                numerator = 10 * (numerator - (quotient * denominator));
                int position = visited[numerator];
                if (numerator == 0 || position != 0) {
                    // Record the starting position of the cycle. This value
                    // will be needed when printing parentheses around the
                    // cycle.
                    start = position;
                    break;
                }
            }
        }
        return start == 0 ?
            builder.toString() :
            builder.substring(0, start + 1) + "("
                + builder.substring(start + 1, count + 1) + ")";
    }
    
    public static int cycleLength(String s) {
        int start = s.indexOf('(');
        return start == -1 ? 0 : s.length() - start - 2;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java ReciprocalCycles <denominator>");
            System.exit(1);
        }
        int denominator = 1;
        try {
            denominator = Integer.parseInt(args[0]);
            if (denominator <= 0 || denominator > MAX_DENOMINATOR) {
                throw new NumberFormatException();
            }
        } catch (NumberFormatException nfe) {
            System.err.println(
                "Error: Denominator must be an integer in [1, 2000]. Received '"
                    + args[0] + "'.");
            System.exit(1);
        }
        String s = fractionToDecimal(1, denominator);
        int cycleLength = cycleLength(s);
        System.out.print("1/" + denominator + " = " + s
                + (cycleLength != 0 ? ", cycle length " + cycleLength(s) : ""));
        System.exit(0);
    }
}
