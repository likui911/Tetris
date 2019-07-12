#pragma once

#include "View.h"
#include "Util.h"
#include "Figure.h"
#include <time.h>

class Game
{
public:
	Game(View* pView = NULL);
	~Game();
	void SetView(View* pView);
	void UpdateView();
	unsigned GetLevel() const;

public:
	void UpArrowKey();
	void DownArrowKey();
	void LeftArrowKey();
	void RightArrowKey();
	void SpaceKey();
	void Timer();
	bool CanMoveDown();
	void MergeFigureToGrid();
	bool GameOver();
private:
	void IncreaseScore();
	void ReinitFigureInfo();
	void RemoveGridLine();
	bool CheckGameOver();

private:
	View* m_pView;
	int m_Grid[ROW_NUM][COL_NUM];
	FigureInfo m_currFigureInfo;
	FigureInfo m_nextFigureInfo;
	unsigned m_iLevel;
	unsigned m_iLines;
	unsigned m_iScore;
	bool m_isOver;
	int m_iFigure_i;
	int m_iFigure_j;
};
