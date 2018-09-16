/**
 * Created by katieprescott on 1/22/18.
 */

import java.util.*;

public class intest {
    public static void main(String[] args) {
        int number;
        int divide;
        int total = 0;
        //System.out.println("Please input the number of integers: ");
        Scanner scan = new Scanner(System.in);
        number = scan.nextInt();
        //System.out.println("Please input the number to divide by: ");
        divide = scan.nextInt();
        if (divide == 0) {
            System.out.println("Cannot divide by zero");
            System.exit(1);
        }
        int[] numbers = new int[number];
        //System.out.println("Input your numbers: ");
        for (int i = 0; i<number; i++) {
            numbers[i] = scan.nextInt();
            if (numbers[i] < divide) {
                continue;
            }
            if (numbers[i]%divide == 0) {
                total++;
            }
        }
        System.out.println(total);
    }
}
