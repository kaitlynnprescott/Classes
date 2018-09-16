import java.util.*;

class almostSorted {
	public static boolean distinct(int[] arr) {
		for (int i = 0; i < arr.length-1; i++) {
			for (int j = i+1; j < arr.length; j++) {
				if (arr[i] == arr[j]) {
					return false;
				}
			}
		}
		return true;
	}

	public static boolean isSorted(int[] arr) {
		int i;
		for (i = 0; i < arr.length; i++) {
			if (arr[i] > arr[i+1]) {
				return false;
			}
		}
		return true;
	}

	public static int[] swap(int[] arr, int x, int y) {
		int temp = arr[x];
		arr[x] = arr[y];
		arr[y] = temp;
		return arr;
	}

	public static int[] reverse(int[] arr) {
		for (int i = 0; i < arr.length/2; i++) {
			int temp = arr[i];
			arr[i] = arr[arr.length-i-1];
			arr[arr.length-i-1] = temp;
		}
		return arr;
	}

	public static int[] oneSwap(int[] arr) {
		// should find if one swap will sort the array
		for (int i = 0; i < arr.length - 1; i++) {
			for (int j = i+1; j < arr.length; j++) {
				int[] newarr = swap(arr, i, j);
				if (isSorted(newarr)) {
					return new int[] {1, i, j};
				}
			}
		}
		return new int[] {0};
	}

	public static int[] reversal(int[] arr) {
		// should find if one reversal will sort the array
		for (int i = 0; i < arr.length - 1; i++) {
			for (int j = i+1; j < arr.length; j++) {
				int [] subarray = Arrays.copyOfRange(arr, i, j+1);
				int[] newarr = reverse(subarray);
				if (isSorted(newarr)) {
					return new int[] {1, i, j};
				}
			}
		}
		return new int[] {0};
	}

	public static void main(String[] args) {
		// get input:
		Scanner sc = new Scanner(System.in);
		int n = Integer.parseInt(sc.nextLine()); // number of rows
		String[] ds = sc.nextLine().split(" "); 
		int[] d = new int[ds.length-1];
		for (int x = 0; x < ds.length; x++) {
			d[x] = Integer.parseInt(ds[x]);
		}
		// number of cols
		if (distinct(d)) {
			// error
		}
		if (isSorted(d)) {
			System.out.println("yes");
			return;
		} else {
			int[] arr = oneSwap(d);
			if (arr[0] == 1) {
				// if some swap makes it sorted, return yes and the swap
				System.out.println("yes");
				System.out.println("swap " + arr[1] + arr[2]);
				return;
			} else {
				int[] arr1 = reversal(d);
				if (arr1[0] == 1) {
					// if some reverse makes it sorted, return yes and first and last indexes of the reverse
					System.out.println("yes");
					System.out.println("reverse " + arr1[1] + arr[2]);
					return;
				} else {
					System.out.println("no");
					return;
				}
			}
		}
	}
}