import java.lang.*;
import java.util.*;

class zeros {

	public static int trailingZeros(int n) {
		int k = (int)Math.floor(Math.log(n)/Math.log(5));
		int sum = 0;
		for (int i = 1; i <= k; i++) {
			sum += n/Math.pow(5,i);
		}
		return sum;
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int number = scan.nextInt();
		for (int i = 0; i< number; i++) {
			int newNum = scan.nextInt();
			System.out.println(trailingZeros(newNum));
		}
	}
}