import java.util.*;

class hourglass {



	public static void main(String[] args) {
		int sum = 0;
		int maximum = 0;
		int[] sum_arr = new int[16];
		int[][] A = new int[6][6];
		for (int k = 1; k <= 16; k++){
			for (int i = 0; i <= 6; i++) { // row
				for (int j = 0; j <= 6; j++) { // col
					sum += A[i][j] + A[i][j+1] + A[i][j+2];
					sum += A[i+1][j+1];
					sum += A[i+2][j] + A[i+2][j+1] + A[i+2][j+2];
					sum_arr[k] = sum;
				}
			}
		}
		maximum = max(sum_arr);
		System.out.println(maximum);
	}
}