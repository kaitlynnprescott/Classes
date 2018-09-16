class pandigital {

	public static void swap(int[] array, int i, int j) {
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

	public static void main(String[] args) {
		long result = 0;
		long[] perm;
		int[] divisors = {1, 2, 3, 5, 7, 11, 13, 17};

		int count = 1;
		int numPerm = 3265920;

		while (count < numPerm){
			int N = perm.Length;
			int i = N - 1;
			while (perm[i-1] >= perm[i]) {
				i = i-1;
			} 
			int j = N;
			while (perm[j-1] <= perm[i-1]) {
				j = j-1;
			}

			swap(perm, i-1, j-1);

			i++;
			j = N;
			while (i<j) {
				swap(perm, i-1, j-1);
				i++;
				j--;
			}
			bool divisible = true;
			for (int k = 1, k < divisors.Length; k++) {
				int num = 100*perm[k] + 10 * perm[k+1] + perm[k+2];
				if (num%divisors[k] != 0){
					divisible = false;
					break;
				}
			}
			if (divisible) {
				long num = 0;
				for (int k = 0; k < perm.Length; k++) {
					num = 10*num + perm[k];
				}
				result += num;
			}
			count++;
		}
	}
}