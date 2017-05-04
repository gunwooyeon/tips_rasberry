
// ������_������⺻Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "������_������⺻.h"
#include "������_������⺻Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C������_������⺻Dlg ��ȭ ����



C������_������⺻Dlg::C������_������⺻Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD___DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C������_������⺻Dlg::myMenuClick(POINT point)	//����߰�) �޴� Ŭ�� ���� ������ �Լ�ȭ�� ���ѳ���.
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu* p_sub_menu = menu.GetSubMenu(point.x / MENU_WIDTH);
	CPoint pos;
	CRect r;
	GetWindowRect(r);

	GetCursorPos(&pos);
	p_sub_menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, r.left + MENU_WIDTH * (point.x / MENU_WIDTH), r.top + MENU_HEIGHT, this);

	menu.DestroyMenu();
	
}

void C������_������⺻Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C������_������⺻Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C������_������⺻Dlg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// C������_������⺻Dlg �޽��� ó����

BOOL C������_������⺻Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CRect r;
	GetWindowRect(r); // ���� ��ǥ 

	CRgn wnd_rgn;
	wnd_rgn.CreateRoundRectRgn(r.left, r.top, r.right, r.bottom, 10, 10);
	SetWindowRgn(wnd_rgn, TRUE);

	wnd_rgn.DeleteObject();
	// ������ ������ �ٽ� �׸� 


	m_cap_btn_cnt = m_caption_btn.GetCount();
	for (int i = 0; i < m_cap_btn_cnt; i++) {
		m_caption_btn.p[i]->SubclassDlgItem(IDC_CLOSE_BTN + i, this);
		m_caption_btn.p[i]->MoveWindow(CRect(r.right - close_btn_w * (i + 1), 0, r.right - close_btn_w * i, 30));
		m_caption_btn.p[i]->LoadBitmapImage(IDB_CLOSE_BTN + i * 2, IDB_CLOSEDOWN_BTN + i * 2);
	}

	SetWindowText(L"���� ������"); // ���¹ٿ��� �̸� 

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void C������_������⺻Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect r;
		CRgn wnd_rgn;
		if (m_caption_btn.p[1]->getFlag() == 0)
		{
			GetClientRect(r);
		}
		else if (m_caption_btn.p[1]->getFlag() == 1) {
			GetWindowRect(r);
		}
		for (int i = 0; i < m_cap_btn_cnt; i++) {
			m_caption_btn.p[i]->MoveWindow(CRect(r.right - close_btn_w * (i + 1), r.top, r.right - close_btn_w * i, CAPTION_HEIGHT));
			m_caption_btn.p[i]->setRectPos(CRect(r.right - close_btn_w * (i + 1), r.top, r.right - close_btn_w * i, CAPTION_HEIGHT));
		}

		// �ִ�ȭ ��ư�� ���� ��ü ��ǥ or Ŭ���̾�Ʈ�� ��ǥ ���� ���� 

		wnd_rgn.CreateRoundRectRgn(r.left, r.top, r.right, r.bottom, 10, 10);
		SetWindowRgn(wnd_rgn, TRUE);
		wnd_rgn.DeleteObject();
		dc.FillSolidRect(r.left, r.top, r.Width(), CAPTION_HEIGHT, RGB(77, 100, 255));
		// ĸ���� 



		CString str;
		GetWindowText(str);
		dc.SetTextColor(RGB(255, 255, 255));
		r.bottom = CAPTION_HEIGHT;
		dc.DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(0, 0, 0));
		dc.TextOut(5, CAPTION_HEIGHT + 5, L"����(F)");
		dc.TextOut(5 + MENU_WIDTH * 1, CAPTION_HEIGHT + 6, L"����(E)");	//��� �߰�) ������ �ø�
		dc.TextOut(5 + MENU_WIDTH * 2, CAPTION_HEIGHT + 6, L"�˻�(S)");
		dc.TextOut(5 + MENU_WIDTH * 3, CAPTION_HEIGHT + 6, L"����(O)");
		dc.TextOut(5 + MENU_WIDTH * 4, CAPTION_HEIGHT + 6, L"����(H)");
		// �̻��ϰ� 1 �� �����°� ����� ���̳׿� 


		//CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR C������_������⺻Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C������_������⺻Dlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void C������_������⺻Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.y < CAPTION_HEIGHT) {
		CRect r;
		GetClientRect(r);

		m_caption_clicked_flag = 1; // ���콺 ����
		SetCapture();
		GetCursorPos(&mp_last_pos); // ���� ��ǥ 
		Invalidate(TRUE);
	}
	else if (point.y < MENU_HEIGHT && point.x<MENU_HEIGHT * 5) {//��� �߰�) �޴��� 5��. 5���� �Ѿ�� �۵�ġ�ʰ�
		myMenuClick(point);	//��� �߰�) Ŭ���ϴ� �� �Լ��� ����
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void C������_������⺻Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_caption_clicked_flag == 1) {
		m_caption_clicked_flag = 0;
		ReleaseCapture();
	}

	//CDialogEx::OnLButtonUp(nFlags, point);
}


void C������_������⺻Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_caption_clicked_flag == 1) {
		CRect r;
		GetWindowRect(r);

		POINT pos;
		GetCursorPos(&pos);
		r = r + CPoint(pos.x - mp_last_pos.x, pos.y - mp_last_pos.y);
		//SetWindowPos(NULL, r.left + pos.x - p_last_pos.x, r.top + pos.y - p_last_pos.y, 0, 0, SWP_NOSIZE);
		MoveWindow(r);

		mp_last_pos = pos;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void C������_������⺻Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (point.y < CAPTION_HEIGHT) {
		char temp = m_caption_btn.p[1]->getFlag();
		temp = !temp;
		m_caption_btn.p[1]->setFlag(temp);

		if (m_caption_btn.p[1]->getFlag() == 1) {
			PostMessage(WM_SYSCOMMAND, (WPARAM)SC_MAXIMIZE); // �ִ�ȭ
		}
		else if (m_caption_btn.p[1]->getFlag() == 0) {
			PostMessage(WM_SYSCOMMAND, (WPARAM)SC_RESTORE); // ���� ���·� ����
		}

		

		Invalidate(TRUE);
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


BOOL C������_������⺻Dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	/*if (wParam == (IDC_CLOSE_BTN + 10002)) {
		m_caption_btn.p[0]->LoadBitmapImage(IDB_CLOSE_BTN, IDB_CLOSEDOWN_BTN);
	}*/
	// ������ �� �ѹ��� �ҷ��� ���ǹ� 
	return CDialogEx::OnCommand(wParam, lParam);
}


//��� �߰�) VK_MENU altŰ�� ���� ���¿��� �޴�Ű�� ȣ����
//��ȭ���ڿ��� PreTranslateMessage�� ��� Ŭ���� �����Ǹ� ���� �߰��Ͽ����ϴ�.
BOOL C������_������⺻Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (GetKeyState(VK_MENU) < 0) {	//VK_MENU�� �����쿡�� Alt Ű�� ���մϴ�.
		POINT point;
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'F' || pMsg->wParam == 'f') {
			point.x = 50;	//50�� ������ �޴� �߰������� ���� myMenuClick�� ó����.
			myMenuClick(point);	//myMenuClick�� ������ ������ �� �ۿ� ���°� alt Ű�� ������ ��쵵 �־ 
		}
		else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'E' || pMsg->wParam == 'e') {
			point.x = 100;
			myMenuClick(point);
		}
		else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'S' || pMsg->wParam == 's') {
			point.x = 150;
			myMenuClick(point);
		}
		else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'O' || pMsg->wParam == 'o') {
			point.x = 200;
			myMenuClick(point);
		}
		else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'H' || pMsg->wParam == 'h') {
			point.x = 250;
			myMenuClick(point);
		}

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
