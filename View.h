#pragma once

#include "Util.h"
#include "Figure.h"
#include "LCDNumber.h"
#include <d2d1.h>
#include <dwrite.h>
//#include <windows.h>

#define MARGIN 11.0f

#define BACKCOLOR D2D1_COLOR_F{ 0.62f,0.68f,0.53f,1.0f }
#define FORECOLOR D2D1_COLOR_F{ 0.0f,0.0f,0.0f,1.0f }
#define GRIDCOLOR D2D1_COLOR_F{ 0.54f,0.59f,0.46f,1.0f}
class View
{
public:
	View();
	~View();
	HRESULT Initial(HWND);
	HRESULT SetTextFormat(float size);
	void InitialRectLCD();
	void InitLCD();
	void BeginDraw();
	void EndDraw();
	void Resize(int width, int height);
	void CaculateLayout();
	void DrawBackground();
	void DrawBorder();
	void DrawGrid(int pGrid[][COL_NUM]);
	void DrawCurrentFigure(Figure& figure);
	void DrawNextFigure(Figure& figure);
	void DrawScore(unsigned score);
	void DrawRemoveLine(unsigned lines);
	void DrawLevel(unsigned lev);
	void DrawStaticText();

private:
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;
	IDWriteFactory* m_pWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	D2D1_RECT_F m_rectTetris;
	D2D1_RECT_F m_rectGrid;
	D2D1_RECT_F m_rectStatus;

	D2D1_RECT_F m_rectScoreText;
	D2D1_RECT_F m_rectScoreLCD;
	D2D1_RECT_F m_rectRemoveLineText;
	D2D1_RECT_F m_rectRemoveLineLCD;
	D2D1_RECT_F m_rectLevelText;
	D2D1_RECT_F m_rectLevelLCD;
	D2D1_RECT_F m_rectNextText;
	D2D1_RECT_F m_rectNextFigure;

private:
	LCDNumber* m_pLcdScore;
	LCDNumber* m_pLcdRemoveLine;
	LCDNumber* m_pLcdLevel;

	float m_fMargin_x;
	float m_fMargin_y;
	float m_fCell_x;
	float m_fCell_y;
};
