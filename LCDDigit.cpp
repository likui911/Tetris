#include "LCDDigit.h"

LCDDigit::LCDDigit(ID2D1Factory* pFactory, const D2D1_RECT_F rect)
	: m_pFactory{ pFactory },
	m_pZero{ nullptr },
	m_pOne{ nullptr },
	m_pTwo{ nullptr },
	m_pThree{ nullptr },
	m_pFour{ nullptr },
	m_pFive{ nullptr },
	m_pSix{ nullptr },
	m_pSeven{ nullptr },
	m_pEight{ nullptr },
	m_pNine{ nullptr },
	m_pTen{ nullptr },
	m_pGeometry1{ nullptr },
	m_pGeometry2{ nullptr },
	m_pGeometry3{ nullptr },
	m_pGeometry4{ nullptr },
	m_pGeometry5{ nullptr },
	m_pGeometry6{ nullptr },
	m_pGeometry7{ nullptr },
	m_rect{ rect }
{
	InitPathGeometry();
	InitGeometryGroup();
}

LCDDigit::~LCDDigit()
{
	ReleasePathGeometry();
	ReleaseGeometryGroup();

}

ID2D1GeometryGroup* LCDDigit::GetDigit(const int n)
{
	ID2D1GeometryGroup* pGeoGroup;
	switch (n)
	{
	case 1:
		pGeoGroup = m_pOne;
		break;
	case 2:
		pGeoGroup = m_pTwo;
		break;
	case 3:
		pGeoGroup = m_pThree;
		break;
	case 4:
		pGeoGroup = m_pFour;
		break;
	case 5:
		pGeoGroup = m_pFive;
		break;
	case 6:
		pGeoGroup = m_pSix;
		break;
	case 7:
		pGeoGroup = m_pSeven;
		break;
	case 8:
		pGeoGroup = m_pEight;
		break;
	case 9:
		pGeoGroup = m_pNine;
		break;
	default:
		pGeoGroup = m_pZero;
	}
	return pGeoGroup;
}

HRESULT LCDDigit::InitPathGeometry()
{
	ID2D1GeometrySink* pSink;
	HRESULT hr = m_pFactory->CreatePathGeometry(&m_pGeometry1);
	if (SUCCEEDED(hr))
	{
		hr = m_pGeometry1->Open(&pSink);

		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

		pSink->BeginFigure(
			getAbsolutePoint(D2D1::Point2F(3, 0)),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
		   getAbsolutePoint(D2D1::Point2F(3 ,0)),
		   getAbsolutePoint(D2D1::Point2F(16,13)),
		   getAbsolutePoint(D2D1::Point2F(58,13)),
		   getAbsolutePoint(D2D1::Point2F(71,0))
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
		SafeRelease(&pSink);
	}

	hr = m_pFactory->CreatePathGeometry(&m_pGeometry2);
	if (SUCCEEDED(hr))
	{
		hr = m_pGeometry2->Open(&pSink);

		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

		pSink->BeginFigure(
			getAbsolutePoint(D2D1::Point2F(0, 1)),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
		   getAbsolutePoint(D2D1::Point2F(0, 1)),
		   getAbsolutePoint(D2D1::Point2F(14, 15)),
		   getAbsolutePoint(D2D1::Point2F(14, 53)),
		   getAbsolutePoint(D2D1::Point2F(7, 60)),
		   getAbsolutePoint(D2D1::Point2F(6, 60)),
		   getAbsolutePoint(D2D1::Point2F(0, 54))
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
		SafeRelease(&pSink);
	}

	hr = m_pFactory->CreatePathGeometry(&m_pGeometry3);
	if (SUCCEEDED(hr))
	{
		hr = m_pGeometry3->Open(&pSink);

		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

		pSink->BeginFigure(
			getAbsolutePoint(D2D1::Point2F(74, 1)),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
		   getAbsolutePoint(D2D1::Point2F(74, 1)),
		   getAbsolutePoint(D2D1::Point2F(74, 54)),
		   getAbsolutePoint(D2D1::Point2F(68, 60)),
		   getAbsolutePoint(D2D1::Point2F(67, 60)),
		   getAbsolutePoint(D2D1::Point2F(60, 53)),
		   getAbsolutePoint(D2D1::Point2F(60, 15)),

		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
		SafeRelease(&pSink);
	}

	hr = m_pFactory->CreatePathGeometry(&m_pGeometry4);
	if (SUCCEEDED(hr))
	{
		hr = m_pGeometry4->Open(&pSink);

		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

		pSink->BeginFigure(
			getAbsolutePoint(D2D1::Point2F(15, 56)),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
		   getAbsolutePoint(D2D1::Point2F(15, 56)),
		   getAbsolutePoint(D2D1::Point2F(59, 56)),
		   getAbsolutePoint(D2D1::Point2F(65, 62)),
		   getAbsolutePoint(D2D1::Point2F(59, 69)),
		   getAbsolutePoint(D2D1::Point2F(15, 69)),
		   getAbsolutePoint(D2D1::Point2F(9, 63)),
		   getAbsolutePoint(D2D1::Point2F(9, 62)),
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
		SafeRelease(&pSink);
	}

	hr = m_pFactory->CreatePathGeometry(&m_pGeometry5);
	if (SUCCEEDED(hr))
	{
		hr = m_pGeometry5->Open(&pSink);

		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

		pSink->BeginFigure(
			getAbsolutePoint(D2D1::Point2F(6, 65)),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
		   getAbsolutePoint(D2D1::Point2F(6, 65)),
		   getAbsolutePoint(D2D1::Point2F(7, 65)),
		   getAbsolutePoint(D2D1::Point2F(14, 72)),
		   getAbsolutePoint(D2D1::Point2F(14, 110)),
		   getAbsolutePoint(D2D1::Point2F(0, 124)),
		   getAbsolutePoint(D2D1::Point2F(0, 71)),
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
		SafeRelease(&pSink);
	}

	hr = m_pFactory->CreatePathGeometry(&m_pGeometry6);
	if (SUCCEEDED(hr))
	{
		hr = m_pGeometry6->Open(&pSink);

		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

		pSink->BeginFigure(
			getAbsolutePoint(D2D1::Point2F(3, 125)),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
		   getAbsolutePoint(D2D1::Point2F(3, 125)),
		   getAbsolutePoint(D2D1::Point2F(16, 112)),
		   getAbsolutePoint(D2D1::Point2F(58, 112)),
		   getAbsolutePoint(D2D1::Point2F(71, 125))
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
		SafeRelease(&pSink);
	}

	hr = m_pFactory->CreatePathGeometry(&m_pGeometry7);
	if (SUCCEEDED(hr))
	{
		hr = m_pGeometry7->Open(&pSink);

		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

		pSink->BeginFigure(
			getAbsolutePoint(D2D1::Point2F(67, 65)),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
		   getAbsolutePoint(D2D1::Point2F(67, 65)),
		   getAbsolutePoint(D2D1::Point2F(68, 65)),
		   getAbsolutePoint(D2D1::Point2F(74, 71)),
		   getAbsolutePoint(D2D1::Point2F(74, 124)),
		   getAbsolutePoint(D2D1::Point2F(60, 110)),
		   getAbsolutePoint(D2D1::Point2F(60, 72)),
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pSink->Close();
		SafeRelease(&pSink);
	}
	return hr;
}

HRESULT LCDDigit::InitGeometryGroup()
{
	HRESULT hr = S_FALSE;
	// Number 0
	ID2D1Geometry* ppGeometries_0[] =
	{
		m_pGeometry1,
		m_pGeometry2,
		m_pGeometry3,
		m_pGeometry5,
		m_pGeometry6,
		m_pGeometry7
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_0,
		ARRAYSIZE(ppGeometries_0),
		&m_pZero
	);
	// Number 1
	ID2D1Geometry* ppGeometries_1[] =
	{
		m_pGeometry3,
		m_pGeometry7
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_1,
		ARRAYSIZE(ppGeometries_1),
		&m_pOne
	);
	// Number 2
	ID2D1Geometry* ppGeometries_2[] =
	{
		m_pGeometry1,
		m_pGeometry3,
		m_pGeometry4,
		m_pGeometry5,
		m_pGeometry6
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_2,
		ARRAYSIZE(ppGeometries_2),
		&m_pTwo
	);
	// Number 3
	ID2D1Geometry* ppGeometries_3[] =
	{
		m_pGeometry1,
		m_pGeometry3,
		m_pGeometry4,
		m_pGeometry7,
		m_pGeometry6
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_3,
		ARRAYSIZE(ppGeometries_3),
		&m_pThree
	);
	// Number 4
	ID2D1Geometry* ppGeometries_4[] =
	{
		m_pGeometry2,
		m_pGeometry4,
		m_pGeometry3,
		m_pGeometry7
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_4,
		ARRAYSIZE(ppGeometries_4),
		&m_pFour
	);
	// Number 5
	ID2D1Geometry* ppGeometries_5[] =
	{
		m_pGeometry1,
		m_pGeometry2,
		m_pGeometry4,
		m_pGeometry7,
		m_pGeometry6
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_5,
		ARRAYSIZE(ppGeometries_5),
		&m_pFive
	);
	// Number 6
	ID2D1Geometry* ppGeometries_6[] =
	{
		m_pGeometry1,
		m_pGeometry2,
		m_pGeometry5,
		m_pGeometry6,
		m_pGeometry7,
		m_pGeometry4
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_6,
		ARRAYSIZE(ppGeometries_6),
		&m_pSix
	);
	// Number 7
	ID2D1Geometry* ppGeometries_7[] =
	{
		m_pGeometry1,
		m_pGeometry3,
		m_pGeometry7,
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_7,
		ARRAYSIZE(ppGeometries_7),
		&m_pSeven
	);
	// Number 8
	ID2D1Geometry* ppGeometries_8[] =
	{
		m_pGeometry1,
		m_pGeometry2,
		m_pGeometry3,
		m_pGeometry4,
		m_pGeometry5,
		m_pGeometry6,
		m_pGeometry7
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_8,
		ARRAYSIZE(ppGeometries_8),
		&m_pEight
	);
	// Number 9
	ID2D1Geometry* ppGeometries_9[] =
	{
		m_pGeometry1,
		m_pGeometry2,
		m_pGeometry3,
		m_pGeometry4,
		m_pGeometry6,
		m_pGeometry7
	};
	hr = m_pFactory->CreateGeometryGroup(
		D2D1_FILL_MODE_WINDING,
		ppGeometries_9,
		ARRAYSIZE(ppGeometries_9),
		&m_pNine
	);
	return hr;
}

D2D1_POINT_2F LCDDigit::getAbsolutePoint(D2D1_POINT_2F relPoint)
{
	float px = m_rect.left;
	float py = m_rect.top;
	return D2D1::Point2F(px + relPoint.x / ORDINARY_NUM_WIDTH * GetRectWidth(m_rect),
		py + relPoint.y / ORDINARY_NUM_HEIGHT * GetRectHeight(m_rect));
}

void LCDDigit::ReleaseGeometryGroup()
{
	SafeRelease(&m_pGeometry1);
	SafeRelease(&m_pGeometry2);
	SafeRelease(&m_pGeometry3);
	SafeRelease(&m_pGeometry4);
	SafeRelease(&m_pGeometry5);
	SafeRelease(&m_pGeometry6);
	SafeRelease(&m_pGeometry7);
}

void LCDDigit::ReleasePathGeometry()
{
	SafeRelease(&m_pZero);
	SafeRelease(&m_pOne);
	SafeRelease(&m_pTwo);
	SafeRelease(&m_pThree);
	SafeRelease(&m_pFour);
	SafeRelease(&m_pFive);
	SafeRelease(&m_pSix);
	SafeRelease(&m_pSeven);
	SafeRelease(&m_pEight);
	SafeRelease(&m_pNine);
	SafeRelease(&m_pTen);
}
