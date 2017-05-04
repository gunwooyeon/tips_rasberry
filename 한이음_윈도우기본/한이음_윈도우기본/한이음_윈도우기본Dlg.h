
// ������_������⺻Dlg.h : ��� ����
//

#pragma once
#include "CapBtn.h"

enum CaptionPosition {
	close_btn_w = 30, maximize_btn_w = close_btn_w + 30, minimize_btn_w = maximize_btn_w + 30
};
// ��ư ��ġ 

enum MouseCaptionFlagBit {
	close = 0, maximize = 2, minimize = 4,
};
// ĸ�� ��ư flag 

#define CAPTION_HEIGHT 30
#define MENU_HEIGHT 60
#define MENU_WIDTH 60


// C������_������⺻Dlg ��ȭ ����
class C������_������⺻Dlg : public CDialogEx
{
private:
	ManageBtn m_caption_btn;
	POINT mp_last_pos;
	char m_caption_clicked_flag = 0;   // �巡�׿� 
	char m_maximize_flag = 0;
	int m_cap_btn_cnt = 0;
public:
	C������_������⺻Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	void myMenuClick(POINT point);	//����߰�) �޴� Ŭ�� ����
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD___DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//����߰�) Ű����. Ű�� ���ҽ�->Accelerator�� ����
};
