def displayBoard(board):
	rows = len(board)
	for row in range(rows):
		print '', # print space, keep cursor on same line
		cols = len(board[row])
		for col in range(cols):
			print board[row][col],
			if col < cols - 1:
				print '|',
		print
		if row < rows - 1:
			print '-' * (cols * 4 - 1)
			
board = [['X', 'X', 'O', 'X'], ['O', 'X', ], ['X', 'O', 'O'], ['X', 'X', 'X']]
displayBoard(board)
