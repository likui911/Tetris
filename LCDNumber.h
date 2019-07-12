#pragma once
#include <d2d1.h>
#include <vector>
#include "LCDDigit.h"
#include "Util.h"
#include "framework.h"

#define MAXIMUM_DIGITS 8

class LCDNumber {
public:
	LCDNumber(ID2D1HwndRenderTarget* renderTarget,
		const D2D1_RECT_F rect,
		float spacing,
		int digits,
		bool enableBgColor = true);

	void DrawLCDNumber(unsigned num,
		ID2D1SolidColorBrush* brush,
		const D2D1_COLOR_F& frColor,
		const D2D1_COLOR_F& bgColor);
	~LCDNumber();

private:
	std::vector<LCDDigit*> m_vecDigit;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	int m_iDigits;
	bool m_enableBgColor;
};
