#include "LCDNumber.h"

LCDNumber::LCDNumber(ID2D1HwndRenderTarget* renderTarget, const D2D1_RECT_F rect,
	float spacing, int digits, bool enableBgColor) :
	m_pRenderTarget{ renderTarget }, m_iDigits{ digits }, m_vecDigit{}, m_enableBgColor{ enableBgColor }
{
	ID2D1Factory* pFactory;
	renderTarget->GetFactory(&pFactory);

	float width = GetRectHeight(rect) * DIGIT_WIDTH_FACTOR;
	for (int i = 0; i < digits; i++)
	{
		float px = rect.left + (width + width * spacing) * i;
		LCDDigit* pLcd = new LCDDigit{
			pFactory, D2D1_RECT_F{px, rect.top, px + width, rect.bottom} };
		m_vecDigit.push_back(pLcd);
	}
}

void LCDNumber::DrawLCDNumber(unsigned num, ID2D1SolidColorBrush* brush,
	const D2D1_COLOR_F& frColor,
	const D2D1_COLOR_F& bgColor)
{
	char buffer[MAXIMUM_DIGITS + 1] = { '\0' };

	// 显示不下舍去高位
	while (num > pow(10, m_iDigits) - 1) {
		num %= (int)pow(10, m_iDigits);
	}

	char fmt[] = "%00d";
	fmt[2] = m_iDigits + '0';
	sprintf_s(buffer, ((size_t)m_iDigits + 1), fmt, num);

	bool flag = false;
	for (int i = 0; i < m_vecDigit.size(); ++i) {
		int n = buffer[i] - '0';

		if (n > 0 || i == m_vecDigit.size() - 1) 
			flag = true;
		
		if (m_enableBgColor) {
			brush->SetColor(bgColor);
			m_pRenderTarget->FillGeometry(m_vecDigit[i]->GetDigit(0), brush);
		}
		if (flag) {
			brush->SetColor(frColor);
			m_pRenderTarget->FillGeometry(m_vecDigit[i]->GetDigit(n), brush);
		}
	}
}

LCDNumber::~LCDNumber() {
	for (auto& digit : m_vecDigit) {
		digit->~LCDDigit();
	}
}
