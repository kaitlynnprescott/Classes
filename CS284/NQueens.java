public class NQueens
{
	public Board chessBoard;

	public NQueens(int n)
	{this.chessBoard = new Board(n);}

	private boolean isSafe(int x, int y)
	{
		for (int row = 0; row < chessBoard.rows; ++row) 
		{
			if (chessBoard.board[x][row] == 1 || chessBoard.board[row][y] == 1)
			{
				return false;
			}	
		}
		// checking the main diagonal.

		for (int row = x; col = y; row >= 0 && col >= 0; --row, --col) 
		{
			if (chessBoard.board[row][col] == 1)
			{
				return false;
			}
		}
		// checking the anti-diagonal.
		for (int row = x; col = y; col >= 0 && row < chessBoard.rows; ++row, --col) 
		{
			if (chessBoard.board[row][col] == 1) 
			{
				return false;
			}
		}
		return true;
	}

	private boolean solve(int col)
	{
		if (col == chessBoard.cols) 
		{
			return true;
		}

		for (int row = 0; row < chessBoard.rows; ++row) 
		{
			if (isSafe(row, col)) 
			{
				chessBoard.board[row][col] = 1;
				if (solve(col + 1))
				{
					System.out.println(chessBoard);
				}
				chessBoard.board[row][col] = 0;
			}
		}
		return false;
	}

	public boolean solve()
	{return solve(0);}

	public String toString()
	{return chessBoard.toString();}

	public static void main(String[] args) 
	{
		NQueens fourQueens = new NQueens(4);
		fourQueens.solve();
	}
}