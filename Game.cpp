#include "Game.h"

Game::Game(View* pView) :m_pView{ pView }, m_Grid{ 0, }, m_iLevel{ 1 }, m_iLines{ 0 }, m_iScore{ 0 }, m_isOver{ false }
{
	srand((unsigned)time(0));

	m_currFigureInfo = FigureInfos[rand() % FIGURE_INFO_NUM];
	m_currFigureInfo.SetIndex(rand() % FIGURE_NUM);
	int y = m_currFigureInfo.GetFigure().GetBottomY();
	m_currFigureInfo.GetFigure().Move((COL_NUM - 1) / 2, 0 - y);

	Sleep(50);
	srand((unsigned)time(0));
	m_nextFigureInfo = FigureInfos[rand() % FIGURE_INFO_NUM];

}

Game::~Game()
{
}

void Game::SetView(View* pView)
{
	m_pView = pView;
}

void Game::UpdateView()
{
	m_pView->BeginDraw();
	m_pView->DrawBackground();
	m_pView->DrawBorder();
	m_pView->DrawGrid(m_Grid);
	m_pView->DrawCurrentFigure(m_currFigureInfo.GetFigure());
	m_pView->DrawNextFigure(m_nextFigureInfo.GetFigure());
	m_pView->DrawStaticText();
	m_pView->DrawScore(m_iScore);
	m_pView->DrawRemoveLine(m_iLines);
	m_pView->DrawLevel(m_iLevel);
	m_pView->EndDraw();
}

unsigned Game::GetLevel() const
{
	return m_iLevel;
}

void Game::UpArrowKey()
{
	int x = m_currFigureInfo.GetFigure().GetPositionX();
	int y = m_currFigureInfo.GetFigure().GetPositionY();
	Figure& figure = m_currFigureInfo.GetNextFigure();
	figure.Move(x, y);
	if (figure.GetLeftX() < 0 || figure.GetRightX() > COL_NUM - 1)
	{
		m_currFigureInfo.GetPrevFigure();
	}
}

void Game::DownArrowKey()
{
	Figure& figure = m_currFigureInfo.GetFigure();
	int x = figure.GetPositionX();
	int y = figure.GetPositionY();

	figure.Move(x, y + 1);

}

void Game::LeftArrowKey()
{
	Figure& figure = m_currFigureInfo.GetFigure();
	int x = figure.GetPositionX();
	int y = figure.GetPositionY();

	bool canMove = true;
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		Square sq = figure.GetSquare(i);
		int r = sq.GetRow() + figure.GetPositionY();
		int c = sq.GetCol() + figure.GetPositionX();

		if (!(c > 0) || (r >= 0 && m_Grid[r][c - 1] == 1))
		{
			canMove = false;
		}
	}

	if (canMove)
	{
		figure.Move(x - 1, y);
	}
}

void Game::RightArrowKey()
{
	Figure& figure = m_currFigureInfo.GetFigure();
	int x = figure.GetPositionX();
	int y = figure.GetPositionY();

	bool canMove = true;
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		Square sq = figure.GetSquare(i);
		int r = sq.GetRow() + figure.GetPositionY();
		int c = sq.GetCol() + figure.GetPositionX();
		if (!(c < COL_NUM - 1) || (r >= 0 && m_Grid[r][c + 1] == 1))
		{
			canMove = false;
		}
	}
	if (canMove)
	{
		figure.Move(x + 1, y);
	}
}

void Game::SpaceKey()
{
	while (CanMoveDown())
	{
		DownArrowKey();
	}
	MergeFigureToGrid();
}

void Game::Timer()
{
	DownArrowKey();
}

void Game::MergeFigureToGrid()
{
	Figure& figure = m_currFigureInfo.GetFigure();
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		Square sq = figure.GetSquare(i);
		int r = sq.GetRow() + figure.GetPositionY();
		int c = sq.GetCol() + figure.GetPositionX();
		if (r >= 0)
		{
			m_Grid[r][c] = 1;
		}
	}

	RemoveGridLine();

	if (CheckGameOver())
	{
		m_isOver = true;
	}
	else
	{
		ReinitFigureInfo();
	}

}

bool Game::GameOver()
{
	return m_isOver;
}

void Game::IncreaseScore()
{
	m_iLines += 1;
	m_iScore += 10;
	m_iLevel = m_iScore / 1000 + 1;
}

void Game::ReinitFigureInfo()
{
	m_currFigureInfo = m_nextFigureInfo;
	m_currFigureInfo.GetFigure().Move(0, 0);

	srand((unsigned)time(0));
	m_currFigureInfo.SetIndex(rand() % FIGURE_NUM);

	int y = m_currFigureInfo.GetFigure().GetBottomY();
	m_currFigureInfo.GetFigure().Move((COL_NUM - 1) / 2, 0 - y);
	m_nextFigureInfo = FigureInfos[rand() % FIGURE_INFO_NUM];
}

void Game::RemoveGridLine()
{
	for (int i = 0; i < ROW_NUM; ++i)
	{
		bool isFull = true;
		for (int j = 0; j < COL_NUM; ++j)
		{
			if (m_Grid[i][j] == 0)
			{
				isFull = false;
				break;
			}
		}
		if (isFull)
		{
			IncreaseScore();
			for (int z = i; z > 0; z--)
			{
				for (int j = 0; j < COL_NUM; ++j)
				{
					m_Grid[z][j] = m_Grid[z - 1][j];
				}
			}
		}
	}
}

bool Game::CheckGameOver()
{
	bool ret = false;
	for (int i = 0; i < COL_NUM; ++i)
	{
		if (m_Grid[0][i] == 1)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

bool Game::CanMoveDown()
{
	Figure& figure = m_currFigureInfo.GetFigure();
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		Square sq = figure.GetSquare(i);
		int r = sq.GetRow() + figure.GetPositionY();
		int c = sq.GetCol() + figure.GetPositionX();

		if (r >= -1 && (r >= ROW_NUM - 1 || m_Grid[r + 1][c] == 1))
		{
			return false;
		}
	}
	return true;
}
