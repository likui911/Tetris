#pragma once

#include "Square.h"

#define FIGURE_INFO_NUM 7
#define FIGURE_NUM 4

class Figure
{
public:
	Figure();
	Figure(int i1, int j1, int i2, int j2, int i3, int j3, int i4, int j4);
	Figure(const Figure& fg);
	~Figure();
	void Move(int x, int y);
	Square GetSquare(int idx);
	int GetPositionX();
	int GetPositionY();
	int GetLeftX();
	int GetRightX();
	int GetTopY();
	int GetBottomY();

private:
	int position[2];
	Square cell[FIGURE_NUM];
};

class FigureInfo
{
public:
	FigureInfo() {}
	FigureInfo(Figure f0, Figure f1, Figure f2, Figure f3);
	FigureInfo(const FigureInfo& info);
	Figure& GetFigure();
	Figure& GetPrevFigure();
	Figure& GetNextFigure();
	void SetIndex(int i);

private:
	Figure m_figures[FIGURE_NUM];
	int m_idx = 0;
};


static FigureInfo figureO{ {0,0,0,1,1,1,1,0},
						  {0,0,0,1,1,1,1,0},
						  {0,0,0,1,1,1,1,0},
						  {0,0,0,1,1,1,1,0} };

static FigureInfo figureI{ {0,0,-1,0,1,0,2,0},
						  {0,0,0,-1,0,1,0,2},
						  {0,0,-1,0,1,0,2,0},
						  {0,0,0,-1,0,1,0,2} };

static FigureInfo figureZ1{ {0,0,-1,0,0,1,1,1},
						   {0,0,1,-1,1,0,0,1},
						   {0,0,-1,0,0,1,1,1},
						   {0,0,1,-1,1,0,0,1} };

static FigureInfo figureZ2{ {0,0,1,-1,0,-1,-1,0},
						   {0,0,0,-1,1,0,1,1},
						   {0,0,1,-1,0,-1,-1,0},
						   {0,0,0,-1,1,0,1,1} };

static FigureInfo figureT{ {0,0,-1,0,0,-1,1,0},
						  {0,0,0,-1,-1,0,0,1},
						  {0,0,-1,0,0,1,1,0},
						  {0,0,0,-1,1,0,0,1} };

static FigureInfo figureL1{ {0,0,0,-1,1,0,2,0},
						   {0,0,0,-2,0,-1,-1,0},
						   {0,0,-2,0,-1,0,0,1},
						   {0,0,1,0,0,1,0,2} };

static FigureInfo figureL2{ {0,0,1,0,2,0,0,1},
						   {0,0,0,-2,0,-1,1,0},
						   {0,0,0,-1,-2,0,-1,0},
						   {0,0,-1,0,0,1,0,2} };

static FigureInfo FigureInfos[FIGURE_INFO_NUM]{ figureO,figureI,figureZ1,figureZ2,figureT,figureL1,figureL2 };