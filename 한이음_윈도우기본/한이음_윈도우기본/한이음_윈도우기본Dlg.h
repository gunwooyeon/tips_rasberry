
// 한이음_윈도우기본Dlg.h : 헤더 파일
//

#pragma once
#include "CapBtn.h"

enum CaptionPosition {
	close_btn_w = 30, maximize_btn_w = close_btn_w + 30, minimize_btn_w = maximize_btn_w + 30
};
// 버튼 위치 

enum MouseCaptionFlagBit {
	close = 0, maximize = 2, minimize = 4,
};
// 캡션 버튼 flag 

#define CAPTION_HEIGHT 30
#define MENU_HEIGHT 60
#define MENU_WIDTH 60


// C한이음_윈도우기본Dlg 대화 상자
class C한이음_윈도우기본Dlg : public CDialogEx
{
private:
	ManageBtn m_caption_btn;
	POINT mp_last_pos;
	char m_caption_clicked_flag = 0;   // 드래그용 
	char m_maximize_flag = 0;
	int m_cap_btn_cnt = 0;
public:
	C한이음_윈도우기본Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	void myMenuClick(POINT point);	//재근추가) 메뉴 클릭 로직
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD___DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//재근추가) 키눌림. 키는 리소스->Accelerator를 참고
};
