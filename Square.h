#pragma once

class Square
{
public:
	Square();
	Square(int col, int row);
	int GetRow() const { return m_iRow; }
	int GetCol()const { return m_iCol; }
	void SetRow(int row) { m_iRow = row; }
	void SetCol(int col) { m_iCol = col; }
	~Square();

private:
	int m_iCol;
	int m_iRow;
};
