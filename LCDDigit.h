#pragma once
#include <d2d1.h>
#include <vector>
#include "Util.h"
#include "framework.h"

#define ORDINARY_NUM_WIDTH 75.0f
#define ORDINARY_NUM_HEIGHT 126.0f
#define DIGIT_WIDTH_FACTOR (ORDINARY_NUM_WIDTH / ORDINARY_NUM_HEIGHT)

class LCDDigit {
public:
	LCDDigit(ID2D1Factory* pFactory, const D2D1_RECT_F rect);
	~LCDDigit();
	ID2D1GeometryGroup* GetDigit(const int n);

private:
	HRESULT InitPathGeometry();
	HRESULT InitGeometryGroup();
	D2D1_POINT_2F getAbsolutePoint(D2D1_POINT_2F relPoint);
	void ReleaseGeometryGroup();
	void ReleasePathGeometry();

private:
	ID2D1Factory* m_pFactory;

	ID2D1GeometryGroup* m_pZero;
	ID2D1GeometryGroup* m_pOne;
	ID2D1GeometryGroup* m_pTwo;
	ID2D1GeometryGroup* m_pThree;
	ID2D1GeometryGroup* m_pFour;
	ID2D1GeometryGroup* m_pFive;
	ID2D1GeometryGroup* m_pSix;
	ID2D1GeometryGroup* m_pSeven;
	ID2D1GeometryGroup* m_pEight;
	ID2D1GeometryGroup* m_pNine;
	ID2D1GeometryGroup* m_pTen;

	ID2D1PathGeometry* m_pGeometry1;
	ID2D1PathGeometry* m_pGeometry2;
	ID2D1PathGeometry* m_pGeometry3;
	ID2D1PathGeometry* m_pGeometry4;
	ID2D1PathGeometry* m_pGeometry5;
	ID2D1PathGeometry* m_pGeometry6;
	ID2D1PathGeometry* m_pGeometry7;

	D2D1_RECT_F m_rect;
};
