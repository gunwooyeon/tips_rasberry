
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
	DDX_Control(pDX, IDC_PATH_TREE, m_my_tree_ctrl);
	DDX_Control(pDX, IDC_PATH_LIST, m_my_list_ctrl);
}

BEGIN_MESSAGE_MAP(C������_������⺻Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C������_������⺻Dlg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY(NM_RCLICK, IDC_PATH_TREE, &C������_������⺻Dlg::OnNMRClickPathTree)
	ON_COMMAND(ID_NEWFILE_TREE, &C������_������⺻Dlg::OnNewfileTree)
	ON_COMMAND(ID_32791, &C������_������⺻Dlg::OnModifyFilename)
	ON_COMMAND(ID_32792, &C������_������⺻Dlg::OnDeleteFile)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_PATH_TREE, &C������_������⺻Dlg::OnTvnItemexpandedPathTree)
	ON_COMMAND(ID_32793, &C������_������⺻Dlg::OnFindFile)
	ON_NOTIFY(NM_DBLCLK, IDC_PATH_TREE, &C������_������⺻Dlg::OnNMDblclkPathTree)
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
		m_caption_btn.p[i]->MoveWindow(CRect(r.right - close_btn_w * (i + 1), 0, r.right - close_btn_w * i, CAPTION_HEIGHT));
		m_caption_btn.p[i]->LoadBitmapImage(IDB_CLOSE_BTN + i * 2, IDB_CLOSEDOWN_BTN + i * 2);
	}


	/* ----- �𼭸� �ձ۰� �۾��ؾߵ� ----- */
	m_path_edit.SubclassDlgItem(IDC_PATH_EDIT, this);
	//m_path_edit.MoveWindow(CRect(BTN_WIDTH * 5, MENU_HEIGHT, r.right - BTN_WIDTH, PATH_MENU_HEIGHT));



	SetWindowText(L"���� ������"); // ���¹ٿ��� �̸� 


	/* ----- Ʈ�� ��Ʈ�� ----- */
	// Ʈ�� ��Ʈ�� �̵�
	//m_my_tree_ctrl.MoveWindow(2, PATH_MENU_HEIGHT + 30, r.left + 200, 200);
	HTREEITEM h_root = AddTreeItem(NULL, L"pi"); // ��Ʈ
	HTREEITEM h_first_root = AddTreeItem(h_root, L"Desktop");
	AddTreeItem(h_first_root, L"temp");
	AddTreeItem(h_root, L"Documents");
	AddTreeItem(h_root, L"Downloads");
	AddTreeItem(NULL, L"pi_");

	m_tree_image.Create(IDB_TREE_BIT, 16, 2, RGB(255, 255, 255));
	m_my_tree_ctrl.SetImageList(&m_tree_image, TVSIL_NORMAL);
	// ��Ʈ���� �ٽ� �׸����� ���� - setimagelist
	// ���� ��Ʈ���� �������� 

	m_my_tree_ctrl.Expand(h_root, TVE_EXPAND);
	// Ʈ���� �������·� ���̵��� 


	m_font.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"����ü");

	// ��ư��ü�� SetFont() �Լ��� �̿��Ͽ� ������ ��Ʈ�� �����Ų��.
	m_my_tree_ctrl.SetFont(&m_font, TRUE);


	

	CRect temp_r;
	GetDlgItem(IDC_PATH_TREE)->GetWindowRect(temp_r);
	/* ----- ����Ʈ ��Ʈ�� ----- */
	m_my_list_ctrl.MoveWindow(CRect(temp_r.right + 4, PATH_MENU_HEIGHT + 5, r.right - 2, r.bottom - STATUS_BAR_HEIGHT));
	ShowIcon(h_root);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

CString C������_������⺻Dlg::GetItemName(HTREEITEM a_node) {
	return m_my_tree_ctrl.GetItemText(a_node);
}

void C������_������⺻Dlg::ShowIcon(HTREEITEM a_start_node) {
	m_icon_count = 0;
	if (a_start_node != NULL) {
		HTREEITEM temp = m_my_tree_ctrl.GetChildItem(a_start_node);
		do {
			CString str = GetItemName(temp);

			m_list_image.Create(16, 16, ILC_COLOR24 | ILC_MASK, 2, 2);
			m_list_image.Add(AfxGetApp()->LoadIcon(IDI_LIST_ICON));
			m_my_list_ctrl.SetImageList(&m_list_image, LVSIL_SMALL);
			m_my_list_ctrl.InsertItem(0, str, 0);

			m_list_image.Detach();
			m_icon_count++;
		} while ((temp = m_my_tree_ctrl.GetNextSiblingItem(temp)) != NULL);
	}
}


void C������_������⺻Dlg::OnNMDblclkPathTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_my_list_ctrl.DeleteAllItems();
	HTREEITEM node = m_my_tree_ctrl.GetSelectedItem();
	ShowIcon(node);

	*pResult = 0;
}

char C������_������⺻Dlg::FindNodeByString(HTREEITEM parm_item, CString parm_string)
{
	if (m_my_tree_ctrl.GetItemText(parm_item) == parm_string) {
		// �˻��ϰ��� �ϴ� �׸��� ã�� ���..
		m_my_tree_ctrl.Select(parm_item, TVGN_CARET);
		return 1;
	}
	else {
		if (m_my_tree_ctrl.ItemHasChildren(parm_item)) {
			// �ڽĳ�尡 �ִ� ���, �ڽĳ�带 Ž���ؾ� �Ѵ�.
			HTREEITEM child_item = m_my_tree_ctrl.GetChildItem(parm_item);
			do {
				if (1 == FindNodeByString(child_item, parm_string)) return 1;
			} while ((child_item = m_my_tree_ctrl.GetNextSiblingItem(child_item)) != NULL);
		}
	}

	return 0;
}

void C������_������⺻Dlg::OnFindFile()
{
	CString str;
	GetDlgItemText(IDC_PATH_EDIT, str);

	int find_flag = 0;
	HTREEITEM first_item = m_my_tree_ctrl.GetRootItem();
	if (first_item != NULL) {
		do {
			if (1 == FindNodeByString(first_item, str)) {
				find_flag = 1;
				MessageBox(L"�׸��� ã�ҽ��ϴ�..", L"�˻� �Ϸ�", MB_OK);
				break;
			}
		} while ((first_item = m_my_tree_ctrl.GetNextSiblingItem(first_item)) != NULL);

		if (find_flag == 0) MessageBox(L"ã�����ϴ� �׸��� �������� �ʽ��ϴ�..", L"�˻� �Ϸ�", MB_ICONSTOP);
	}
	else MessageBox(L"��ϵ� �׸��� �����ϴ�.", L"�˻� ����", MB_ICONSTOP);
}



HTREEITEM C������_������⺻Dlg::AddTreeItem(HTREEITEM parm_parent, LPWSTR parm_text)
{
	TVINSERTSTRUCT data; // Ʈ�� ����ü 

	data.hParent = parm_parent; // �θ�
	data.hInsertAfter = TVI_SORT; // ����
	data.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE; // �ؽ�Ʈ ( �̸� )
	data.item.pszText = parm_text; // � ���ڸ� ���� ���� 
	data.item.iImage = 1;
	data.item.iSelectedImage = 3;
	// ���� x, ���� o 

	return m_my_tree_ctrl.InsertItem(&data);
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


		CRect temp_r;
		GetDlgItem(IDC_PATH_TREE)->GetWindowRect(temp_r);
		ScreenToClient(temp_r);
		m_path_edit.MoveWindow(CRect(BTN_WIDTH * 5, MENU_HEIGHT, r.right - BTN_WIDTH, PATH_MENU_HEIGHT));
		m_my_tree_ctrl.MoveWindow(2, PATH_MENU_HEIGHT + 30, r.left + 200, r.Height() - 150);
		m_my_list_ctrl.MoveWindow(CRect(temp_r.right + 4, PATH_MENU_HEIGHT + 5, r.right - 2, r.bottom - STATUS_BAR_HEIGHT));


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


void C������_������⺻Dlg::OnNMRClickPathTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	TV_HITTESTINFO hit_info;

	::GetCursorPos(&hit_info.pt);// Ʈ�� ��Ʈ�ѿ� ���Ͽ� ��ǥ�� ���� 
	::ScreenToClient(m_my_tree_ctrl.m_hWnd, &hit_info.pt);
	// api �Լ��� ��Ÿ���� ::������ �ڵ��� ������ �� ���� 

	HTREEITEM current_item = m_my_tree_ctrl.HitTest(&hit_info);
	if (current_item != NULL) {
		m_my_tree_ctrl.Select(current_item, TVGN_CARET);
		CMenu menu;
		menu.LoadMenu(IDR_MENU2);
		CMenu* p_sub_menu = menu.GetSubMenu(1);
		CPoint pos;

		GetCursorPos(&pos);
		p_sub_menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);

		menu.DestroyMenu();
	}
	else {
		CMenu menu;
		menu.LoadMenu(IDR_MENU2);
		CMenu* p_sub_menu = menu.GetSubMenu(0);
		CPoint pos;

		GetCursorPos(&pos);
		p_sub_menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);

		menu.DestroyMenu();

	}
}


void C������_������⺻Dlg::OnNewfileTree()
{
	LPWSTR str = L"";
	AddTreeItem(m_my_tree_ctrl.GetSelectedItem(), str);
	m_my_tree_ctrl.Expand(m_my_tree_ctrl.GetSelectedItem(), TVE_EXPAND);
}


void C������_������⺻Dlg::OnModifyFilename()
{
	m_my_tree_ctrl.EditLabel(m_my_tree_ctrl.GetSelectedItem());
}


void C������_������⺻Dlg::OnDeleteFile()
{
	m_my_tree_ctrl.DeleteItem(m_my_tree_ctrl.GetSelectedItem());
}


void C������_������⺻Dlg::OnTvnItemexpandedPathTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	if (pNMTreeView->action == 2) m_my_tree_ctrl.SetItemImage(pNMTreeView->itemNew.hItem, 0, 2);
	else m_my_tree_ctrl.SetItemImage(pNMTreeView->itemNew.hItem, 1, 3);

	*pResult = 0;
}

