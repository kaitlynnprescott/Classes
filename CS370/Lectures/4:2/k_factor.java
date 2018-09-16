import java.util.Arrays;
import java.util.ArrayList;
import java.util.Scanner;

public class k_factor {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String inp[] = sc.nextLine().split(" ");
		int inpp[] = new int[2];
		inpp[0] = Integer.parseInt(inp[0]);
		inpp[1] = Integer.parseInt(inp[1]);
		int n = inpp[0];
		if (n <= 1000000000){
			// error
		}
		int k = inpp[1];
		if (k <= 20) {
			// error
		}
		String arr[] = sc.nextLine().split(" ");
		int a[] = new int[arr.length];
		for (int i = 0; i < arr.length; i++) {
			a[i] = Integer.parseInt(arr[i]);
		}
		if (dups(a)) {
			// error
		}
		
		// sort array
		Arrays.sort(a);
		ArrayList<Integer> divisors = new ArrayList<>();
		for (int i = 0; i < a.length; i++) {
			if (isEvenlyDivisable(n, a[i])) {
				n = n/a[i];
				divisors.add(a[i]);
			}
		}
		//System.out.println(Arrays.toString(divisors.toArray()));
		int[] solution = new int[divisors.size()+1];
		solution[0] = 1;
		for (int i = 1; i < solution.length; i++) {
			solution[i] = solution[i-1] * divisors.get(i-1);
		}
		System.out.println(Arrays.toString(solution));
	}
	// checks for duplicates
	public static boolean dups(int[] arr) {
		boolean duplicates = false;
		for (int i = 0; i < arr.length; i++) {
			for (int j = i+1; j < arr.length; j++) {
				if (j != i && arr[j] == arr[i]) {
					duplicates = true;
				}
			}
		}
		return duplicates;
	}
	public static boolean isEvenlyDivisable(int a, int b) {
	    return a % b == 0;
	}

}
