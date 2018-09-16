/**
 * Listing 2.4 Programming Question 1
 * Write a program that compares the values of yl and y2 in the following expressions
 * for values of n up to 100 in increments of 10. Does the result surprise you?
 * yl = 100 * n + 10
 * y2 = 5 * n * n + 2
 */
public class AsymptoticAnalysis
{
    public static int y1(int n)
    {
        return (100 * n + 10);
    }

    public static int y2(int n)
    {
        return (5 * n * n + 2);
    }

    public static void main(String[] args)
    {
        for (int i = 0; i <= 100; i += 10)
        {
            System.out.printf("y1(%d) = %,d, y2(%d) = %,d\n", i, y1(i), i, y2(i));
            // System.out.println("y1(" + i + ") = " + y1(i) + ", y2(" + i + ") = " + y2(i));
        }
    }
}