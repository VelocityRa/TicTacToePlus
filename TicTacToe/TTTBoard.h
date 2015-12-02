#pragma once
class TTTBoard
{
private:

	enum Cell
	{
		Empty,
			X,
			O
	};

	Cell cells[3][3];

public:
	TTTBoard();
	~TTTBoard();

	Cell getCell(int i, int j)
	{
		return cells[i][j];
	}

	void setCell(int i, int j, Cell cell)
	{
		cells[i][j] = cell;
	}

	void clearBoard();
};

