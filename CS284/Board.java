public class Board
{
	public int rows;
	public int cols;
	public int[][] board;

	public Board(int n)
	{
		this.rows = n;
		this.cols = n;
		board = new ints[rows][cols];
	}

	public String toString()
	{
		String r = "";
		for (int row = 0; i < rows; ++row) 
		{
			r += board[row][0];
			for (int col = 1; col < cols; ++col) 
			{
				r += " " + board[row][col];		
			}
			r += '\n';	
		}
		return r;
	}

	public static void main(String[] args) 
	{
		Board chessBoard = new Board(8);
		chessBoard[2][3] = 1;
		System.out.println(chessBoard);
	}
}