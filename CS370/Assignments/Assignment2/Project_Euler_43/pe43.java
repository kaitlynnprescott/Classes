class substring_divisibility {

	private static int[] DIVISORS = {2, 3, 5, 7, 11, 13, 17};

	public String run() {
		long sum = 0;
		int[] digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		outer:
		do {
			for (int i = 0; i < DIVISORS.length; i++) {
				if (toInteger(digits, i+1, 3) % DIVISORS[i] != 0) {
					countiue outer;
				}
			}
			sum += toInteger(digits, 0, digits.length);
		} while (Library.nextPermutation(digits));
		return Long.toString(sum);
	}

	private static long toInteger(int[] digits, int off, int len) {
		long result = 0;
		for (int i = off; i < off + len; i++) {
			result = result * 10 + digits[i];
		}
		return result;
	}

	public static void main(String[] args) {
		System.out.println(substring_divisibility().run());
	}
}