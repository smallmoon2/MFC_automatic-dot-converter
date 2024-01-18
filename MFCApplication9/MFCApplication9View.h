
// MFCApplication9View.h: CMFCApplication9View 클래스의 인터페이스
//

#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
class CMFCApplication9View : public CView
{

protected: // serialization에서만 만들어집니다.
	CMFCApplication9View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication9View)
	
// 특성입니다.
public:
	CString strPathName;
	int one ;
	CImage m_image1;
	String opencv;
	CPoint _point;
	COLORREF test[16];
	int Gcolor[16][3];
	int r = 0;
	int g = 0;
	int b = 0;
	int x = 0;
	int y = 0;
	int row, col;
	int _pos[2];
	int dotsize;
	int gray = 0;
	int rstart;
	Mat Input_Image;
	int K;
	Mat labels;
	Mat centers;

	int collision;
	int select_color[16][3];
	int _color[32][3]= { (0,0,0),(0,0,0),(0,0,0),(0,0,0) };
	COLORREF rpoint_color[16];
	CMFCApplication9Doc* GetDocument() const;
	

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApplication9View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFCApplication9View.cpp의 디버그 버전
inline CMFCApplication9Doc* CMFCApplication9View::GetDocument() const
   { return reinterpret_cast<CMFCApplication9Doc*>(m_pDocument); }
#endif

