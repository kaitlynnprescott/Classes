import java.util.*;


// if [i][j] = 1:
	// start counting

// if neighbor([i][j]) = 1

public static void dfs(int arr[][], int row, int col, boolean visited[][]) {
	int rowNeighbor[] = new int[] {-1, -1, -1, 0, 0, 1, 1, 1};
	int colNeighbor[] = new int[] {-1, 0, 1, -1, 1, -1, 0, 1};
	visited[row][col] = true;

	for (int i = 0; i < 8; ++i) {
		if ()
	}
}

public static void main(String[] args) {
	// get input:
	Scanner sc = new Scanner(System.in);
	int n = sc.nextInt(); // number of rows
	int m = sc.nextInt(); // number of cols
	int[] row;
	int[][] matrix = new int[n+2][m+2];
	for (int i=1; i<=n; i++) { // num of rows
		row = sc.nextLine().split(" ");
		if (row.length != m) {
			// error
		}
		matrix[i] = row;
	}

	int count = 0;
	boolean visited[][] = new boolean[n][m];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (matrix[i][j] && !visited[i][j]) {
				dfs(matrix, i, j, visited);
				count++;
			}
		}
	}
	return count;
}