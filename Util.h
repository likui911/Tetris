#pragma once

#include "framework.h"
#include <d2d1.h>

#define ROW_NUM 20
#define COL_NUM 10

#define ROW_NUM_FIGURE 2
#define COL_NUM_FIGURE 4

#define MINIMUM_HEIGHT 284.0f
#define MINIMUM_WIDTH 223.0f

template <class T>
void SafeRelease(T * *ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

float GetRectHeight(D2D1_RECT_F rect);

float GetRectWidth(D2D1_RECT_F rect);