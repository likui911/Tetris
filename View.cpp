#include "view.h"

View::View() :
	m_pFactory{ NULL },
	m_pRenderTarget{ NULL },
	m_pBrush{ NULL },
	m_pWriteFactory{ NULL },
	m_pTextFormat{ NULL },
	m_rectTetris{ 0, },
	m_rectGrid{ 0, },
	m_rectStatus{ 0, },
	m_fMargin_x{ 0.0f },
	m_fMargin_y{ 0.0f },
	m_fCell_x{ 0.0f },
	m_fCell_y{ 0.0f },
	m_pLcdScore{ NULL }
{
}

View::~View()
{
	SafeRelease(&m_pFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pBrush);
	SafeRelease(&m_pWriteFactory);
	SafeRelease(&m_pTextFormat);

	m_pLcdScore->~LCDNumber();
	m_pLcdRemoveLine->~LCDNumber();
	m_pLcdLevel->~LCDNumber();
}

HRESULT View::Initial(HWND hWnd)
{
	HRESULT hr = S_FALSE;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	if (SUCCEEDED(hr))
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2D1_SIZE_U size{ UINT32(rc.right - rc.left),UINT32(rc.bottom - rc.top) };

		hr = m_pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&m_pRenderTarget);
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(BACKCOLOR, &m_pBrush);
			if (SUCCEEDED(hr))
			{
				hr = DWriteCreateFactory(
					DWRITE_FACTORY_TYPE_ISOLATED,
					__uuidof(IDWriteFactory),
					reinterpret_cast<IUnknown * *> (&m_pWriteFactory));
			}
		}
	}
	return hr;
}

HRESULT View::SetTextFormat(float size)
{
	IDWriteTextFormat* p;

	HRESULT hr = m_pWriteFactory->CreateTextFormat(
		L"Microsoft YaHei UI",
		NULL,
		DWRITE_FONT_WEIGHT_LIGHT,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"",
		&p);
	if (SUCCEEDED(hr))
	{
		SafeRelease(&m_pTextFormat);
		m_pTextFormat = p;
	}
	return hr;
}

void View::InitialRectLCD()
{
	CaculateLayout();
	InitLCD();
}

void View::InitLCD()
{
	m_pLcdScore = new LCDNumber{ m_pRenderTarget,m_rectScoreLCD,0.3f,5 };
	m_pLcdRemoveLine = new LCDNumber{ m_pRenderTarget,m_rectRemoveLineLCD,0.3f,5 };
	m_pLcdLevel = new LCDNumber{ m_pRenderTarget,m_rectLevelLCD,0.3f,1,false };
}

void View::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
}

void View::EndDraw()
{
	m_pRenderTarget->EndDraw();
}

void View::Resize(int width, int height)
{
	m_pRenderTarget->Resize(D2D1_SIZE_U{ (UINT32)width,(UINT32)height });
	CaculateLayout();
	InitLCD();
}

void View::DrawBackground()
{
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	m_pRenderTarget->Clear(BACKCOLOR);
}

void View::DrawBorder()
{
	m_pBrush->SetColor(FORECOLOR);
	m_pRenderTarget->DrawRectangle(m_rectGrid, m_pBrush, 2.0f);
}

void View::DrawGrid(int pGrid[][COL_NUM])
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if ((pGrid)[i][j] == 1)
				m_pBrush->SetColor(FORECOLOR);
			else
				m_pBrush->SetColor(GRIDCOLOR);

			float left = m_rectGrid.left + (m_fMargin_x + m_fCell_x) * j + m_fMargin_x;
			float top = m_rectGrid.top + (m_fMargin_y + m_fCell_y) * i + m_fMargin_y;
			float right = left + m_fCell_x;
			float bottom = top + m_fCell_y;

			m_pRenderTarget->DrawRectangle(D2D1_RECT_F{
				left + m_fMargin_x * 0.5f,
				top + m_fMargin_y * 0.5f,
				right - m_fMargin_x * 0.5f,
				bottom - m_fMargin_y * 0.5f }, m_pBrush, 2.0f);

			m_pRenderTarget->FillRectangle(D2D1_RECT_F{
				left + m_fMargin_x * 1.9f,
				top + m_fMargin_y * 1.9f,
				right - m_fMargin_x * 1.9f,
				bottom - m_fMargin_y * 1.9f }, m_pBrush);
		}
	}
}

void View::DrawCurrentFigure(Figure& figure)
{
	m_pBrush->SetColor(FORECOLOR);
	for (int i = 0; i < FIGURE_NUM; ++i)
	{

		int	col = figure.GetPositionX() + (figure.GetSquare(i)).GetCol();
		int	row = figure.GetPositionY() + (figure.GetSquare(i)).GetRow();
		if (row < 0)
		{
			continue;
		}
		float left = m_rectGrid.left + (m_fMargin_x + m_fCell_x) * col + m_fMargin_x;
		float top = m_rectGrid.top + (m_fMargin_y + m_fCell_y) * row + m_fMargin_y;
		float right = left + m_fCell_x;
		float bottom = top + m_fCell_y;

		m_pRenderTarget->DrawRectangle(D2D1_RECT_F{
			left + m_fMargin_x * 0.5f,
			top + m_fMargin_y * 0.5f,
			right - m_fMargin_x * 0.5f,
			bottom - m_fMargin_y * 0.5f }, m_pBrush, 2.0f);

		m_pRenderTarget->FillRectangle(D2D1_RECT_F{
			left + m_fMargin_x * 1.9f,
			top + m_fMargin_y * 1.9f,
			right - m_fMargin_x * 1.9f,
			bottom - m_fMargin_y * 1.9f }, m_pBrush);

	}
}

void View::DrawNextFigure(Figure& figure)
{
	m_pBrush->SetColor(GRIDCOLOR);
	for (int i = 0; i < ROW_NUM_FIGURE; i++)
	{
		for (int j = 0; j < COL_NUM_FIGURE; j++)
		{
			float left = m_rectNextFigure.left + (m_fMargin_x + m_fCell_x) * j + m_fMargin_x;
			float top = m_rectNextFigure.top + (m_fMargin_y + m_fCell_y) * i + m_fMargin_y;
			float right = left + m_fCell_x;
			float bottom = top + m_fCell_y;

			m_pRenderTarget->DrawRectangle(D2D1_RECT_F{
				left + m_fMargin_x * 0.5f,
				top + m_fMargin_y * 0.5f,
				right - m_fMargin_x * 0.5f,
				bottom - m_fMargin_y * 0.5f }, m_pBrush, 2.0f);

			m_pRenderTarget->FillRectangle(D2D1_RECT_F{
				left + m_fMargin_x * 1.9f,
				top + m_fMargin_y * 1.9f,
				right - m_fMargin_x * 1.9f,
				bottom - m_fMargin_y * 1.9f }, m_pBrush);
		}
	}

	int x = figure.GetLeftX();
	int y = figure.GetTopY();

	int a = x < 0 ? 0 - x : x;
	int b = y < 0 ? 0 - y : y;
	figure.Move(figure.GetPositionX() + a, figure.GetPositionY() + b);

	m_pBrush->SetColor(FORECOLOR);
	for (int i = 0; i < FIGURE_NUM; ++i)
	{
		int	col = figure.GetPositionX() + (figure.GetSquare(i)).GetCol();
		int	row = figure.GetPositionY() + (figure.GetSquare(i)).GetRow();
		float left = m_rectNextFigure.left + (m_fMargin_x + m_fCell_x) * col + m_fMargin_x;
		float top = m_rectNextFigure.top + (m_fMargin_y + m_fCell_y) * row + m_fMargin_y;
		float right = left + m_fCell_x;
		float bottom = top + m_fCell_y;

		m_pRenderTarget->DrawRectangle(D2D1_RECT_F{
			left + m_fMargin_x * 0.5f,
			top + m_fMargin_y * 0.5f,
			right - m_fMargin_x * 0.5f,
			bottom - m_fMargin_y * 0.5f }, m_pBrush, 2.0f);

		m_pRenderTarget->FillRectangle(D2D1_RECT_F{
			left + m_fMargin_x * 1.9f,
			top + m_fMargin_y * 1.9f,
			right - m_fMargin_x * 1.9f,
			bottom - m_fMargin_y * 1.9f }, m_pBrush);
	}
}

void View::DrawScore(unsigned score)
{
	m_pLcdScore->DrawLCDNumber(score, m_pBrush, FORECOLOR, GRIDCOLOR);
}

void View::DrawRemoveLine(unsigned lines)
{
	m_pLcdRemoveLine->DrawLCDNumber(lines, m_pBrush, FORECOLOR, GRIDCOLOR);
}

void View::DrawLevel(unsigned lev)
{
	m_pLcdLevel->DrawLCDNumber(lev, m_pBrush, FORECOLOR, GRIDCOLOR);
}

void View::DrawStaticText()
{
	m_pBrush->SetColor(FORECOLOR);
	SetTextFormat(GetRectHeight(m_rectScoreText));
	m_pRenderTarget->DrawTextW(TEXT("得分"), (UINT32)2, m_pTextFormat, m_rectScoreText, m_pBrush);

	SetTextFormat(GetRectHeight(m_rectRemoveLineText));
	m_pRenderTarget->DrawTextW(TEXT("清除行"), (UINT32)3, m_pTextFormat, m_rectRemoveLineText, m_pBrush);

	SetTextFormat(GetRectHeight(m_rectLevelText));
	m_pRenderTarget->DrawTextW(TEXT("级别"), (UINT32)3, m_pTextFormat, m_rectLevelText, m_pBrush);

	SetTextFormat(GetRectHeight(m_rectNextText));
	m_pRenderTarget->DrawTextW(TEXT("下一个"), (UINT32)3, m_pTextFormat, m_rectNextText, m_pBrush);
}

void View::CaculateLayout()
{
	D2D1_SIZE_F size = m_pRenderTarget->GetSize();
	float width = size.width;
	float height = size.height;
	if ((size.width / size.height) > (MINIMUM_WIDTH / MINIMUM_HEIGHT))
	{
		width = size.height * MINIMUM_WIDTH / MINIMUM_HEIGHT;
	}
	else
	{
		height = width * MINIMUM_HEIGHT / MINIMUM_WIDTH;
	}

	float left = (size.width - width) / 2;
	float top = (size.height - height) / 2;
	m_rectTetris = D2D1_RECT_F{ left,top,left + width,top + height };

	m_rectGrid = D2D1_RECT_F{
		m_rectTetris.left + GetRectWidth(m_rectTetris) * 0.03f,
		m_rectTetris.top + GetRectWidth(m_rectTetris) * 0.03f,
		m_rectTetris.left + (m_rectTetris.right - m_rectTetris.left) * 0.6f,
		m_rectTetris.bottom - GetRectWidth(m_rectTetris) * 0.03f };

	m_fMargin_x = (m_rectGrid.right - m_rectGrid.left) / (10 * COL_NUM + 1);
	m_fMargin_y = (m_rectGrid.bottom - m_rectGrid.top) / (10 * ROW_NUM + 1);

	m_fCell_x = m_fMargin_x * 9;
	m_fCell_y = m_fMargin_y * 9;

	m_rectStatus = D2D1_RECT_F{
		m_rectTetris.left + (m_rectTetris.right - m_rectTetris.left) * 0.6f,
		m_rectTetris.top + 5 * m_fMargin_y,
		m_rectTetris.right - 5 * m_fMargin_x,
		m_rectTetris.bottom - 5 * m_fMargin_y };

	m_rectScoreText = D2D1_RECT_F{
		m_rectStatus.left + m_fCell_x,
		m_rectStatus.top + m_fCell_y * 0.5f,
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 5.0f,
		m_rectStatus.top + m_fCell_y * 1.5f };

	m_rectScoreLCD = D2D1_RECT_F{
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 2.0f,
		m_rectStatus.top + m_fCell_y * 2.5f,
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 6.0f,
		m_rectStatus.top + m_fCell_y * 3.5f };

	m_rectRemoveLineText = D2D1_RECT_F{
		m_rectStatus.left + m_fCell_x,
		m_rectStatus.top + m_fCell_y * 4.5f,
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 5.0f,
		m_rectStatus.top + m_fCell_y * 5.5f };

	m_rectRemoveLineLCD = D2D1_RECT_F{
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 2.0f,
		m_rectStatus.top + m_fCell_y * 6.5f,
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 6.0f,
		m_rectStatus.top + m_fCell_y * 7.5f };

	m_rectLevelText = D2D1_RECT_F{
		m_rectStatus.left + m_fCell_x,
		m_rectStatus.top + m_fCell_y * 8.5f,
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 5.0f,
		m_rectStatus.top + m_fCell_y * 9.5f };

	m_rectLevelLCD = D2D1_RECT_F{
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 5.0f,
		m_rectStatus.top + m_fCell_y * 10.5f,
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 6.0f,
		m_rectStatus.top + m_fCell_y * 11.5f };

	m_rectNextText = D2D1_RECT_F{
		m_rectStatus.left + m_fCell_x,
		m_rectStatus.top + m_fCell_y * 12.5f,
		m_rectStatus.left + (m_fCell_x + m_fMargin_x) * 5.0f,
		m_rectStatus.top + m_fCell_y * 13.5f };

	m_rectNextFigure = D2D1_RECT_F{
		m_rectNextText.left + m_fCell_x,
		m_rectNextText.bottom + m_fCell_y * 0.67f,
		m_rectNextText.left + (m_fCell_x + m_fMargin_x) * 5.0f,
		m_rectNextText.bottom + m_fCell_y * 2.67f
	};
}