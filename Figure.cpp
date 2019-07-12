#include "Figure.h"

Figure::Figure() :cell{ {0,0},{0,0}, {0,0}, {0,0} }, position{ 0,0 }
{
}

Figure::Figure(int i1, int j1, int i2, int j2, int i3, int j3, int i4, int j4)
	: cell{ {i1,j1},{i2,j2}, {i3,j3}, {i4,j4} }, position{ 0,0 }
{
}

Figure::Figure(const Figure& fg) : Figure{}
{
	position[0] = fg.position[0];
	position[1] = fg.position[1];
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		cell[i].SetRow(fg.cell[i].GetRow());
		cell[i].SetCol(fg.cell[i].GetCol());
	}
}

void Figure::Move(int x, int y)
{
	position[0] = x;
	position[1] = y;
}

Square Figure::GetSquare(int idx)
{
	return cell[idx];
}

int Figure::GetPositionX()
{
	return position[0];
}

int Figure::GetPositionY()
{
	return position[1];
}

int Figure::GetLeftX()
{
	int left = 0;
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		if (cell[i].GetCol() < left)
		{
			left = cell[i].GetCol();
		}
	}
	return left + GetPositionX();
}

int Figure::GetRightX()
{
	int right = 0;
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		if (cell[i].GetCol() > right)
		{
			right = cell[i].GetCol();
		}
	}
	return right + GetPositionX();
}

int Figure::GetTopY()
{
	int top = 0;
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		if (cell[i].GetRow() < top)
		{
			top = cell[i].GetRow();
		}
	}
	return top+GetPositionY();
}

int Figure::GetBottomY()
{
	int bottom = 0;
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		if (cell[i].GetRow() > bottom)
		{
			bottom = cell[i].GetRow();
		}
	}
	return bottom+GetPositionY();
}

Figure::~Figure()
{
}
FigureInfo::FigureInfo(Figure f0, Figure f1, Figure f2, Figure f3)
{
	m_figures[0] = f0;
	m_figures[1] = f1;
	m_figures[2] = f2;
	m_figures[3] = f3;
}

FigureInfo::FigureInfo(const FigureInfo& info)
{
	m_figures[0] = info.m_figures[0];
	m_figures[1] = info.m_figures[1];
	m_figures[2] = info.m_figures[2];
	m_figures[3] = info.m_figures[3];
}

Figure& FigureInfo::GetFigure()
{
	return m_figures[m_idx];
}

Figure& FigureInfo::GetPrevFigure()
{
	m_idx = (m_idx == 0) ? FIGURE_NUM - 1 : m_idx - 1;
	return m_figures[m_idx];
}

Figure& FigureInfo::GetNextFigure()
{
	m_idx = (m_idx + 1) % FIGURE_NUM;
	return m_figures[m_idx];
}

void FigureInfo::SetIndex(int i)
{
	if (i >= 0 && i <= FIGURE_NUM)
	{
		m_idx = i;
	}
}
