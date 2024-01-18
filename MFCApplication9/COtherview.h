#pragma once


// COtherview 보기
extern int asd;

class COtherview : public CView
{
	DECLARE_DYNCREATE(COtherview)
	

protected:
	int num;
	COLORREF point_color;
	COLORREF point_color1;
	COtherview();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COtherview();



public:
	int colornum;
	int dotnum;
	int Npoint_color[16][3];
	COLORREF point_color2[16];
	int start;
	CPoint _point;
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


