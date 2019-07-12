#include "Util.h"

float GetRectHeight(D2D1_RECT_F rect)
{
	return rect.bottom-rect.top;
}

float GetRectWidth(D2D1_RECT_F rect)
{
	return rect.right-rect.left;
}
