// COtherview.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication9.h"

#include "MainFrm.h"
#include "MFCApplication9Doc.h"
#include "MFCApplication9View.h"
#include "COtherview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COtherview

IMPLEMENT_DYNCREATE(COtherview, CView)

COtherview::COtherview()
{
	
	num = 0;
	_point = (0, 0);
	start = 1;
	for (int i = 0; i < 16; i++) {
		point_color2[i] = {};

	}
	point_color2[0] = {};
}

COtherview::~COtherview()
{
}

BEGIN_MESSAGE_MAP(COtherview, CView)
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// COtherview 그리기

void COtherview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CImage k_image;
	CImage j_image;
	CImage l_image;
	CRect rt;
	CMainFrame* Vfr = (CMainFrame*)AfxGetMainWnd();



	point_color1 = (0, 0, 0);

	if (FAILED(j_image.Load(_T("ok.bmp"))))
	{
		return;
	}
	j_image.BitBlt(dc.m_hDC, 170, 280, j_image.GetWidth(), j_image.GetHeight(), 0, 0, SRCCOPY);

	CRect rectWindow1(170, 280, 170 + j_image.GetWidth(), 280 + j_image.GetHeight());

	if (FAILED(l_image.Load(_T("start.bmp"))))
	{
		return;
	}
	l_image.BitBlt(dc.m_hDC, 170, 700, l_image.GetWidth(), l_image.GetHeight(), 0, 0, SRCCOPY);

	CRect rectWindow2(170, 700, 170 + l_image.GetWidth(), 700 + l_image.GetHeight());

	if (FAILED(k_image.Load(_T("color.bmp"))))
	{
		return;
	}
	k_image.BitBlt(dc.m_hDC, 40, 15, k_image.GetWidth() , k_image.GetHeight(), 0, 0, SRCCOPY);

	CRect rectWindow(40, 15, 40 + k_image.GetWidth(), 15 + k_image.GetHeight());
	CRect m_point(_point.x, _point.y, _point.x + 5, _point.y + 5);

	if (rt.IntersectRect(&rectWindow, &m_point)) {
		point_color = k_image.GetPixel(_point.x - 40, _point.y - 15);

	}

	if (rt.IntersectRect(&rectWindow1, &m_point)) {
		point_color2[num] = point_color;
		num++;
	}
	if (rt.IntersectRect(&rectWindow2, &m_point)) {

		
		Vfr->zxclss->rstart = start;
		Vfr->zxclss->UpdateData(FALSE);
		Vfr->zxclss->UpdateData(TRUE);
		for (int i = num; i < 16; i++) {
			point_color2[i] = point_color2[0];
		}

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 3; j++) {
				if (j == 0) {
					Npoint_color[i][j] = GetRValue(point_color2[i]);
				}
				if (j == 1) {
					Npoint_color[i][j] = GetGValue(point_color2[i]);
				}
				if (j == 2) {
					Npoint_color[i][j] = GetBValue(point_color2[i]);
				}
			}
		}
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 3; j++) {
				Vfr->zxclss->_color[i][j] = Npoint_color[i][j];
			}
		}

		Vfr->zxclss->UpdateData(FALSE);
		Vfr->zxclss->UpdateData(TRUE);

 
	}
	
	point_color1 = point_color;
	if (rt.IntersectRect(&rectWindow, &m_point)) {
		CPen pen;
		pen.CreatePen(PS_DOT, 3, RGB(220, 220, 220));
		CPen* oldPen = dc.SelectObject(&pen);
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetRValue(point_color), GetGValue(point_color), GetBValue(point_color)));
		CBrush* oldBrush = dc.SelectObject(&brush);
		dc.Rectangle(100, 300, 120, 320);
	}
	else {
		CPen pen;
		pen.CreatePen(PS_DOT, 3, RGB(220, 220, 220));
		CPen* oldPen = dc.SelectObject(&pen);
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetRValue(point_color1), GetGValue(point_color1), GetBValue(point_color1)));
		CBrush* oldBrush = dc.SelectObject(&brush);
		dc.Rectangle(100, 300, 120, 320);

	}


	for (int i = 0; i < 16; i++) {
		CPen pen;
		if (i < num) {
			pen.CreatePen(PS_DOT, 2, RGB(255, 0, 0));
		}
		else {
			pen.CreatePen(PS_DOT, 1, RGB(220, 220, 220));
		}
		CPen* oldPen = dc.SelectObject(&pen);
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetRValue(point_color2[i]), GetGValue(point_color2[i]), GetBValue(point_color2[i])));
		CBrush* oldBrush = dc.SelectObject(&brush);
		if (i < 8) {
			dc.Rectangle(100 + (i * 25), 350, 120 + (i * 25), 370);
		}
		else {
			dc.Rectangle(100 + ((i-8) * 25), 380, 120 + ((i-8) * 25), 400);
		}
	}

	CRect rect;
	GetClientRect(&rect);
	CFont m_font;
	m_font.CreatePointFont(180, _T("굴림"));
	dc.SelectObject(m_font);
	dc.TextOutW(50, rect.bottom - 50, _T("색상 변경창"));
	CImage k2_image;
	if (FAILED(k2_image.Load(_T("dot_bottom.png"))))
	{
		return;
	}
	k2_image.BitBlt(dc.m_hDC, 30, 500, k2_image.GetWidth(), k2_image.GetHeight(), 0, 0, SRCCOPY);

	CRect D_rectWindow1(30, 500, 30 + (k2_image.GetWidth() / 3), 500 + k2_image.GetHeight());
	CRect D_rectWindow2(30 + (k2_image.GetWidth() / 3), 500, 30 + (k2_image.GetWidth() / 3 * 2), 500 + k2_image.GetHeight());
	CRect D_rectWindow3((k2_image.GetWidth() / 3 * 2), 500, 30 + k2_image.GetWidth(), 500 + k2_image.GetHeight());


	if (rt.IntersectRect(&D_rectWindow1, &m_point)) {
		dotnum = 2;
		Vfr->zxclss->dotsize = dotnum;
		Vfr->zxclss->UpdateData(FALSE);
	}
	if (rt.IntersectRect(&D_rectWindow2, &m_point)) {
		dotnum = 3;
		Vfr->zxclss->dotsize = dotnum;
	}
	if (rt.IntersectRect(&D_rectWindow3, &m_point)) {
		dotnum = 4;
		Vfr->zxclss->dotsize = dotnum;
	}

	CImage k3_image;
	if (FAILED(k3_image.Load(_T("color_bottom.png"))))
	{
		return;
	}
	k3_image.BitBlt(dc.m_hDC, 30, 600, k3_image.GetWidth(), k3_image.GetHeight(), 0, 0, SRCCOPY);

	CRect C_rectWindow1(30, 600, 30 + k3_image.GetWidth()/4, 600 + k3_image.GetHeight());
	CRect C_rectWindow2(30+ k3_image.GetWidth() / 4, 600, 30 + (k3_image.GetWidth() / 4*2), 600 + k3_image.GetHeight());
	CRect C_rectWindow3(30 + (k3_image.GetWidth() / 4 * 2), 600, 30 + (k3_image.GetWidth() / 4 * 3), 600 + k3_image.GetHeight());
	CRect C_rectWindow4(30 + (k3_image.GetWidth() / 4 * 3), 600, 30 + k3_image.GetWidth(), 600 + k3_image.GetHeight());


	if (rt.IntersectRect(&C_rectWindow1, &m_point)) {
		colornum = 2;
		Vfr->zxclss->K = colornum;
	}
	if (rt.IntersectRect(&C_rectWindow2, &m_point)) {
		colornum = 4;
		Vfr->zxclss->K = colornum;
	}
	if (rt.IntersectRect(&C_rectWindow3, &m_point)) {
		colornum = 8;
		Vfr->zxclss->K = colornum;

	}
	if (rt.IntersectRect(&C_rectWindow4, &m_point)) {
		colornum = 16;
		Vfr->zxclss->K = colornum;
	}


}


// COtherview 진단

#ifdef _DEBUG
void COtherview::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void COtherview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// COtherview 메시지 처리기


void COtherview::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	_point.x = point.x;
	_point.y = point.y;
	Invalidate();
	CView::OnMButtonDown(nFlags, point);
}


void COtherview::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	_point.x = point.x;
	_point.y = point.y;


	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}
