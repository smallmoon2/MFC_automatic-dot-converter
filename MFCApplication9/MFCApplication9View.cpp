
// MFCApplication9View.cpp: CMFCApplication9View 클래스의 구현
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>
#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication9.h"
#endif

#include "MFCApplication9Doc.h"
#include "MFCApplication9View.h"
#include "COtherview.h"
#include "헤더.h"
#include <atlimage.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;
// CMFCApplication9View

IMPLEMENT_DYNCREATE(CMFCApplication9View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication9View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication9View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplication9View 생성/소멸

CMFCApplication9View::CMFCApplication9View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	row = 16;
	col = 3;
	dotsize = 3;
	rstart = 5;
	collision = 1;
	one = 1;
	strPathName = _T("image_bottom.bmp");
	K = 4;

}

CMFCApplication9View::~CMFCApplication9View()
{
}

BOOL CMFCApplication9View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication9View 그리기

void CMFCApplication9View::OnDraw(CDC* /*pDC*/)
{
	CRect rt;
	CClientDC dc(this);
	// opencv @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	// TODO: Add your control notification handler code here

	if (one == 1) {
		m_image1.Destroy();
		m_image1.Load(strPathName);
		opencv = CT2A(strPathName);

		Input_Image = imread(opencv);
		cout << "Height: " << Input_Image.rows << ", Width: " << Input_Image.rows << ", Channels: " << Input_Image.channels() << endl;



		Mat samples(Input_Image.rows * Input_Image.cols, Input_Image.channels(), CV_32F);
		for (int y = 0; y < Input_Image.rows; y++)
			for (int x = 0; x < Input_Image.cols; x++)
				for (int z = 0; z < Input_Image.channels(); z++)
					if (Input_Image.channels() == 3) {
						samples.at<float>(y + x * Input_Image.rows, z) = Input_Image.at<Vec3b>(y, x)[z];
					}

					else {
						samples.at<float>(y + x * Input_Image.rows, z) = Input_Image.at<uchar>(y, x);
					}

		labels;
		int attempts = 5;
		centers;
		kmeans(samples, K, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

		int te = 0;

		Mat new_image(Input_Image.size(), Input_Image.type());
		for (int y = 0; y < Input_Image.rows; y++) {
			for (int x = 0; x < Input_Image.cols; x++)
			{
				int cluster_idx = labels.at<int>(y + x * Input_Image.rows, 0);
				if (Input_Image.channels() == 3) {
					for (int i = 0; i < Input_Image.channels(); i++) {
						new_image.at<Vec3b>(y, x)[i] = centers.at<float>(cluster_idx, i);
						Gcolor[0][i] = centers.at<float>(cluster_idx, i);
					}
					r = Gcolor[0][2];// 현재 픽셀의 RGB중 R값을 저장
					g = Gcolor[0][1]; // 현재 픽셀의 RGB중 G값을 저장
					b = Gcolor[0][0]; // 현재 픽셀의 RGB중 B값을 저장
					//CString str;

					//str.Format(L"%d", g);

					//AfxMessageBox(str);

					m_image1.SetPixel(x, y, RGB(r, g, b));
				}
				else {
					te++;
					new_image.at<uchar>(y, x) = centers.at<float>(cluster_idx, 0);
				}
			}
		}

		//imshow("clustered image", new_image);

		one = 2;
	}
	
	



	// opencv @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	CMFCApplication9Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect m_point(_point.x, _point.y, _point.x + 5, _point.y + 5);
	CImage m_image;

	CImage m_imageo;
	m_image.Destroy();
	m_imageo.Destroy();
	m_image.Load(strPathName);
	m_imageo.Load(strPathName);
	//int _color[32][3] = { {255,255,255}, {244,67,54}, {233,30,99}, {156,39,176}, {103,58,183},{63,81,181},
	//{33,150,243}, {3,169,244}, {0,188,212},{0,150,136},{76,175,80 },{139,195,74},
	//{205,220,57},{255,255,59} ,{255,193,7}  ,{255,152,0 } ,{77,44,64} ,{77,44,64} ,{158,158,158},
	//{0,0,0}, {255,204,253}, {204,204,204}, {0,0,153}, {0,0,0}, {0,0,0}, {0,0,0},
	//{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} };
	//int _color[32][3] = { (0,0,0),(0,0,0),(0,0,0),(0,0,0) };

	//_color[2][3] = (0, 255, 255);
	//_color[3][3] = (255, 0, 0);
	int pointcolor[32];

	//for (int i = 0; i < 16; i++) {
	//	_color[i][3] = (getrvalue(rpoint_color[i]), getgvalue(rpoint_color[i]), getbvalue(rpoint_color[i]));
	//}


	//AfxMessageBox(str);
	COLORREF temp_color;


	if (rstart == 1)
	{
		for (_pos[1] = 0; _pos[1] <= m_image.GetHeight() - dotsize; _pos[1] += dotsize) {
			for (_pos[0] = 0; _pos[0] <= m_image.GetWidth() - dotsize; _pos[0] += dotsize) {

				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						temp_color = m_image.GetPixel(x, y); // 현재 픽셀의 색상을 얻어 저장

						r = r + GetRValue(temp_color); // 현재 픽셀의 RGB중 R값을 저장
						g = g + GetGValue(temp_color); // 현재 픽셀의 RGB중 G값을 저장
						b = b + GetBValue(temp_color); // 현재 픽셀의 RGB중 B값을 저장

						// 반전된 RGB 값으로 새로운 이미지에 SetPixel 해줌
					}
				}

				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						int _newcolor[1][3] = { {r / (dotsize * dotsize), g / (dotsize * dotsize), b / (dotsize * dotsize)} };
						int sizecolors = 2000;
						int colorN = 0;
						for (int i = 0; i < row; i++)    // 2차원 배열의 세로 크기만큼 반복
						{
							int colors = 0;
							for (int j = 0; j < col; j++)    // 2차원 배열의 가로 크기만큼 반복
							{
								colors += abs(_color[i][j] - _newcolor[0][j]);
							}
							pointcolor[i] = colors;
							if (sizecolors > colors) {
								sizecolors = colors;
							}
							printf("\n");                // 가로 요소를 출력한 뒤 다음 줄로 넘어감
						}
						for (int i = 0; i < row; i++) {
							if (pointcolor[i] == sizecolors) {
								colorN = i;
								break;
							}
						}
						m_image.SetPixel(x, y, RGB(_color[colorN][0], _color[colorN][1], _color[colorN][2]));

					}
				}
				r = 0;
				g = 0;
				b = 0;
			}
		}
	}
	if (rstart == 2) {
		for (_pos[1] = 0; _pos[1] <= m_image.GetHeight() - dotsize; _pos[1] += dotsize) {
			for (_pos[0] = 0; _pos[0] <= m_image.GetWidth() - dotsize; _pos[0] += dotsize) {

				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						temp_color = m_image.GetPixel(x, y); // 현재 픽셀의 색상을 얻어 저장

						r = r + GetRValue(temp_color); // 현재 픽셀의 RGB중 R값을 저장
						g = g + GetGValue(temp_color); // 현재 픽셀의 RGB중 G값을 저장
						b = b + GetBValue(temp_color); // 현재 픽셀의 RGB중 B값을 저장

						// 반전된 RGB 값으로 새로운 이미지에 SetPixel 해줌
					}
				}
				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						m_image.SetPixel(x, y, RGB(r / (dotsize * dotsize), g / (dotsize * dotsize), b / (dotsize * dotsize)));
					}
				}
				r = 0;
				g = 0;
				b = 0; 
			}
		}
	}
	if (rstart == 3) {

		for (_pos[1] = 0; _pos[1] <= m_image.GetHeight() - dotsize; _pos[1] += dotsize) {
			for (_pos[0] = 0; _pos[0] <= m_image.GetWidth() - dotsize; _pos[0] += dotsize) {

				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						temp_color = m_image1.GetPixel(x, y); // 현재 픽셀의 색상을 얻어 저장

						r = r + GetRValue(temp_color); // 현재 픽셀의 RGB중 R값을 저장
						g = g + GetGValue(temp_color); // 현재 픽셀의 RGB중 G값을 저장
						b = b + GetBValue(temp_color); // 현재 픽셀의 RGB중 B값을 저장

						// 반전된 RGB 값으로 새로운 이미지에 SetPixel 해줌
					}
				}
				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						m_image1.SetPixel(x, y, RGB(r / (dotsize * dotsize), g / (dotsize * dotsize), b / (dotsize * dotsize)));
					}
				}
				r = 0;
				g = 0;
				b = 0;
			}
		}
	}
	if (gray == 3) {


		for (_pos[1] = 0; _pos[1] <= m_image.GetHeight() - dotsize; _pos[1] += dotsize) {
			for (_pos[0] = 0; _pos[0] <= m_image.GetWidth() - dotsize; _pos[0] += dotsize) {

				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						if (rstart != 3) {
							temp_color = m_image.GetPixel(x, y); // 현재 픽셀의 색상을 얻어 저장
						}
						else {
							temp_color = m_image1.GetPixel(x, y);
						}

						r = r + GetRValue(temp_color); // 현재 픽셀의 RGB중 R값을 저장
						g = g + GetGValue(temp_color); // 현재 픽셀의 RGB중 G값을 저장
						b = b + GetBValue(temp_color); // 현재 픽셀의 RGB중 B값을 저장

						// 반전된 RGB 값으로 새로운 이미지에 SetPixel 해줌
					}
				}
				r = r / (dotsize * dotsize);
				g = g / (dotsize * dotsize);
				b = b / (dotsize * dotsize);
				r = r + g + b;
				for (y = _pos[1]; y < dotsize + _pos[1]; y++) { // 이미지의 세로 픽셀값 만큼
					for (x = _pos[0]; x < dotsize + _pos[0]; x++) { // 이미지의 가로 픽셀값 만큼
						m_image.SetPixel(x, y, RGB(r/3,r/3,r/3));

					}
				}
				r = 0;
				g = 0;
				b = 0;
			}
		}
	}

	CRect rect;
	GetClientRect(&rect);
	CFont m_font;
	m_font.CreatePointFont(180,_T("굴림"));
	dc.SelectObject(m_font);
	dc.TextOutW(50, rect.bottom - 50, _T("이미지 변경창"));

	
	m_imageo.BitBlt(dc.m_hDC, 80, 100, m_imageo.GetWidth() - (m_imageo.GetWidth() % dotsize) , m_image.GetHeight() - (m_imageo.GetWidth() % dotsize), 0, 0, SRCCOPY);
	if (rstart != 3 || gray == 3)
	{
		m_image.BitBlt(dc.m_hDC, 150 + m_imageo.GetWidth(), 100, m_imageo.GetWidth() - (m_imageo.GetWidth() % dotsize), m_image.GetHeight() - (m_imageo.GetWidth() % dotsize), 0, 0, SRCCOPY);
	}
	else {
		m_image1.BitBlt(dc.m_hDC, 150 + m_imageo.GetWidth(), 100, m_imageo.GetWidth() - (m_imageo.GetWidth() % dotsize), m_image.GetHeight() - (m_imageo.GetWidth() % dotsize), 0, 0, SRCCOPY);
	}

	CImage color_image;
	CImage Gray_image;
	CImage kmean_image;
	CImage dot_image;
	color_image.Destroy();
	if (FAILED(color_image.Load(_T("color_bottom.bmp"))))
	{
		return;
	}
	color_image.BitBlt(dc.m_hDC, rect.right - 550, rect.bottom - 100, color_image.GetWidth(), color_image.GetHeight(), 0, 0, SRCCOPY);

	CRect rectWindow(rect.right - 550, rect.bottom - 100, rect.right - 550 + color_image.GetWidth(), rect.bottom - 100 + color_image.GetHeight());

	if (rt.IntersectRect(&rectWindow, &m_point)) { // 컬러번환을 클릭하면
		rstart = 2;

	}
	kmean_image.Destroy();
	if (FAILED(kmean_image.Load(_T("kmean_bottom.bmp"))))
	{
		return;
	}
	kmean_image.BitBlt(dc.m_hDC, rect.right - 400, rect.bottom - 100, kmean_image.GetWidth(), kmean_image.GetHeight(), 0, 0, SRCCOPY);

	CRect rectWindow1(rect.right - 400, rect.bottom - 100, rect.right - 400 + kmean_image.GetWidth(), rect.bottom - 100 + kmean_image.GetHeight());

	if (rt.IntersectRect(&rectWindow1, &m_point)) { // 군집도을 클릭하면
		rstart = 3;
		one = 1;
	}
	Gray_image.Destroy();
	if (FAILED(Gray_image.Load(_T("gray_bottom.bmp"))))
	{
		return;
	}
	Gray_image.BitBlt(dc.m_hDC, rect.right - 700, rect.bottom - 100, Gray_image.GetWidth(), Gray_image.GetHeight(), 0, 0, SRCCOPY);

	CRect rectWindow2(rect.right - 700, rect.bottom - 100, rect.right - 700 + Gray_image.GetWidth(), rect.bottom - 100 + Gray_image.GetHeight());

	gray = 1;
 
	if (rt.IntersectRect(&rectWindow2, &m_point)) { // 흑백번환을 클릭하면
		gray = 3;
	}
	dot_image.Destroy();
	if (FAILED(dot_image.Load(_T("dot_bottom.bmp"))))
	{
		return;
	}
	dot_image.BitBlt(dc.m_hDC, rect.right - 250, rect.bottom - 100, dot_image.GetWidth(), dot_image.GetHeight(), 0, 0, SRCCOPY);

	CRect rectWindow3(rect.right - 250, rect.bottom - 100, rect.right - 250 + dot_image.GetWidth(), rect.bottom - 100 + dot_image.GetHeight());

	if (rt.IntersectRect(&rectWindow3, &m_point)) { // 도트번환을 클릭하면
	}
	//ATLASSUME(dc.m_hDC != NULL);
	//ATLASSUME(dc.m_hDC == NULL);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

}


// CMFCApplication9View 인쇄


void CMFCApplication9View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication9View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비 
	return DoPreparePrinting(pInfo);
}

void CMFCApplication9View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication9View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplication9View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication9View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication9View 진단

#ifdef _DEBUG
void CMFCApplication9View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication9View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication9Doc* CMFCApplication9View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication9Doc)));
	return (CMFCApplication9Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication9View 메시지 처리기


void CMFCApplication9View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	_point.x = point.x;
	_point.y = point.y;
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication9View::OnRButtonDown(UINT nFlags, CPoint point)
{


	CString szFilter = _T("Image (*.BMP, *.PNG, *.JPG) | *.BMP;*.PNG;*.JPG | All Files(*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		strPathName = dlg.GetPathName();


		// get picture-control dc
		// load image jpg,bmp,png
		CImage m_bmpBitmap;
		int width, height;
		m_bmpBitmap.Destroy();
		m_bmpBitmap.Load(strPathName);
		width = m_bmpBitmap.GetWidth();
		height = m_bmpBitmap.GetHeight();
		rstart = 2;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CView::OnRButtonDown(nFlags, point);
}
