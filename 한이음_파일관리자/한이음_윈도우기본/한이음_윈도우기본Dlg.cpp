
// 한이음_윈도우기본Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "한이음_윈도우기본.h"
#include "한이음_윈도우기본Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C한이음_윈도우기본Dlg 대화 상자



C한이음_윈도우기본Dlg::C한이음_윈도우기본Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD___DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C한이음_윈도우기본Dlg::myMenuClick(POINT point)	//재근추가) 메뉴 클릭 기존 로직을 함수화만 시켜놨음.
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

void C한이음_윈도우기본Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATH_TREE, m_my_tree_ctrl);
	DDX_Control(pDX, IDC_PATH_LIST, m_my_list_ctrl);
}

BEGIN_MESSAGE_MAP(C한이음_윈도우기본Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C한이음_윈도우기본Dlg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY(NM_RCLICK, IDC_PATH_TREE, &C한이음_윈도우기본Dlg::OnNMRClickPathTree)
	ON_COMMAND(ID_NEWFILE_TREE, &C한이음_윈도우기본Dlg::OnNewfileTree)
	ON_COMMAND(ID_32791, &C한이음_윈도우기본Dlg::OnModifyFilename)
	ON_COMMAND(ID_32792, &C한이음_윈도우기본Dlg::OnDeleteFile)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_PATH_TREE, &C한이음_윈도우기본Dlg::OnTvnItemexpandedPathTree)
	ON_COMMAND(ID_32793, &C한이음_윈도우기본Dlg::OnFindFile)
	ON_NOTIFY(NM_DBLCLK, IDC_PATH_TREE, &C한이음_윈도우기본Dlg::OnNMDblclkPathTree)
END_MESSAGE_MAP()


// C한이음_윈도우기본Dlg 메시지 처리기

BOOL C한이음_윈도우기본Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CRect r;
	GetWindowRect(r); // 절대 좌표 

	CRgn wnd_rgn;
	wnd_rgn.CreateRoundRectRgn(r.left, r.top, r.right, r.bottom, 10, 10);
	SetWindowRgn(wnd_rgn, TRUE);

	wnd_rgn.DeleteObject();
	// 윈도우 지역을 다시 그림 


	m_cap_btn_cnt = m_caption_btn.GetCount();
	for (int i = 0; i < m_cap_btn_cnt; i++) {
		m_caption_btn.p[i]->SubclassDlgItem(IDC_CLOSE_BTN + i, this);
		m_caption_btn.p[i]->MoveWindow(CRect(r.right - close_btn_w * (i + 1), 0, r.right - close_btn_w * i, CAPTION_HEIGHT));
		m_caption_btn.p[i]->LoadBitmapImage(IDB_CLOSE_BTN + i * 2, IDB_CLOSEDOWN_BTN + i * 2);
	}


	/* ----- 모서리 둥글게 작업해야됨 ----- */
	m_path_edit.SubclassDlgItem(IDC_PATH_EDIT, this);
	//m_path_edit.MoveWindow(CRect(BTN_WIDTH * 5, MENU_HEIGHT, r.right - BTN_WIDTH, PATH_MENU_HEIGHT));



	SetWindowText(L"파일 관리자"); // 상태바에서 이름 


	/* ----- 트리 컨트롤 ----- */
	// 트리 컨트롤 이동
	//m_my_tree_ctrl.MoveWindow(2, PATH_MENU_HEIGHT + 30, r.left + 200, 200);
	HTREEITEM h_root = AddTreeItem(NULL, L"pi"); // 루트
	HTREEITEM h_first_root = AddTreeItem(h_root, L"Desktop");
	AddTreeItem(h_first_root, L"temp");
	AddTreeItem(h_root, L"Documents");
	AddTreeItem(h_root, L"Downloads");
	AddTreeItem(NULL, L"pi_");

	m_tree_image.Create(IDB_TREE_BIT, 16, 2, RGB(255, 255, 255));
	m_my_tree_ctrl.SetImageList(&m_tree_image, TVSIL_NORMAL);
	// 컨트롤을 다시 그리도록 해줌 - setimagelist
	// 파일 비트맵을 오픈해줌 

	m_my_tree_ctrl.Expand(h_root, TVE_EXPAND);
	// 트리가 열린상태로 보이도록 


	m_font.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"굴림체");

	// 버튼객체의 SetFont() 함수를 이용하여 생성한 폰트를 적용시킨다.
	m_my_tree_ctrl.SetFont(&m_font, TRUE);


	

	CRect temp_r;
	GetDlgItem(IDC_PATH_TREE)->GetWindowRect(temp_r);
	/* ----- 리스트 컨트롤 ----- */
	m_my_list_ctrl.MoveWindow(CRect(temp_r.right + 4, PATH_MENU_HEIGHT + 5, r.right - 2, r.bottom - STATUS_BAR_HEIGHT));
	ShowIcon(h_root);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

CString C한이음_윈도우기본Dlg::GetItemName(HTREEITEM a_node) {
	return m_my_tree_ctrl.GetItemText(a_node);
}

void C한이음_윈도우기본Dlg::ShowIcon(HTREEITEM a_start_node) {
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


void C한이음_윈도우기본Dlg::OnNMDblclkPathTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_my_list_ctrl.DeleteAllItems();
	HTREEITEM node = m_my_tree_ctrl.GetSelectedItem();
	ShowIcon(node);

	*pResult = 0;
}

char C한이음_윈도우기본Dlg::FindNodeByString(HTREEITEM parm_item, CString parm_string)
{
	if (m_my_tree_ctrl.GetItemText(parm_item) == parm_string) {
		// 검색하고자 하는 항목을 찾은 경우..
		m_my_tree_ctrl.Select(parm_item, TVGN_CARET);
		return 1;
	}
	else {
		if (m_my_tree_ctrl.ItemHasChildren(parm_item)) {
			// 자식노드가 있는 경우, 자식노드를 탐색해야 한다.
			HTREEITEM child_item = m_my_tree_ctrl.GetChildItem(parm_item);
			do {
				if (1 == FindNodeByString(child_item, parm_string)) return 1;
			} while ((child_item = m_my_tree_ctrl.GetNextSiblingItem(child_item)) != NULL);
		}
	}

	return 0;
}

void C한이음_윈도우기본Dlg::OnFindFile()
{
	CString str;
	GetDlgItemText(IDC_PATH_EDIT, str);

	int find_flag = 0;
	HTREEITEM first_item = m_my_tree_ctrl.GetRootItem();
	if (first_item != NULL) {
		do {
			if (1 == FindNodeByString(first_item, str)) {
				find_flag = 1;
				MessageBox(L"항목을 찾았습니다..", L"검색 완료", MB_OK);
				break;
			}
		} while ((first_item = m_my_tree_ctrl.GetNextSiblingItem(first_item)) != NULL);

		if (find_flag == 0) MessageBox(L"찾고자하는 항목이 존재하지 않습니다..", L"검색 완료", MB_ICONSTOP);
	}
	else MessageBox(L"등록된 항목이 없습니다.", L"검색 오류", MB_ICONSTOP);
}



HTREEITEM C한이음_윈도우기본Dlg::AddTreeItem(HTREEITEM parm_parent, LPWSTR parm_text)
{
	TVINSERTSTRUCT data; // 트리 구조체 

	data.hParent = parm_parent; // 부모
	data.hInsertAfter = TVI_SORT; // 정렬
	data.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE; // 텍스트 ( 이름 )
	data.item.pszText = parm_text; // 어떤 문자를 넣을 건지 
	data.item.iImage = 1;
	data.item.iSelectedImage = 3;
	// 선택 x, 선택 o 

	return m_my_tree_ctrl.InsertItem(&data);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void C한이음_윈도우기본Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
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

		// 최대화 버튼에 따라서 전체 좌표 or 클라이언트내 좌표 인지 선택 


		wnd_rgn.CreateRoundRectRgn(r.left, r.top, r.right, r.bottom, 10, 10);
		SetWindowRgn(wnd_rgn, TRUE);
		wnd_rgn.DeleteObject();
		dc.FillSolidRect(r.left, r.top, r.Width(), CAPTION_HEIGHT, RGB(77, 100, 255));
		// 캡선바 


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
		dc.TextOut(5, CAPTION_HEIGHT + 5, L"파일(F)");
		dc.TextOut(5 + MENU_WIDTH * 1, CAPTION_HEIGHT + 6, L"편집(E)");	//재근 추가) 제목을 늘림
		dc.TextOut(5 + MENU_WIDTH * 2, CAPTION_HEIGHT + 6, L"검색(S)");
		dc.TextOut(5 + MENU_WIDTH * 3, CAPTION_HEIGHT + 6, L"설정(O)");
		dc.TextOut(5 + MENU_WIDTH * 4, CAPTION_HEIGHT + 6, L"도움말(H)");
		// 이상하게 1 더 내리는게 제대로 보이네요 

		
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR C한이음_윈도우기본Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C한이음_윈도우기본Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void C한이음_윈도우기본Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.y < CAPTION_HEIGHT) {
		CRect r;
		GetClientRect(r);

		m_caption_clicked_flag = 1; // 마우스 눌림
		SetCapture();
		GetCursorPos(&mp_last_pos); // 절대 좌표 
		Invalidate(TRUE);
	}
	else if (point.y < MENU_HEIGHT && point.x<MENU_HEIGHT * 5) {//재근 추가) 메뉴가 5개. 5개를 넘어가면 작동치않게
		myMenuClick(point);	//재근 추가) 클릭하는 거 함수로 변경
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void C한이음_윈도우기본Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_caption_clicked_flag == 1) {
		m_caption_clicked_flag = 0;
		ReleaseCapture();
	}

	//CDialogEx::OnLButtonUp(nFlags, point);
}


void C한이음_윈도우기본Dlg::OnMouseMove(UINT nFlags, CPoint point)
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


void C한이음_윈도우기본Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (point.y < CAPTION_HEIGHT) {
		char temp = m_caption_btn.p[1]->getFlag();
		temp = !temp;
		m_caption_btn.p[1]->setFlag(temp);

		if (m_caption_btn.p[1]->getFlag() == 1) {
			PostMessage(WM_SYSCOMMAND, (WPARAM)SC_MAXIMIZE); // 최대화
		}
		else if (m_caption_btn.p[1]->getFlag() == 0) {
			PostMessage(WM_SYSCOMMAND, (WPARAM)SC_RESTORE); // 원래 상태로 복원
		}

		

		Invalidate(TRUE);
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


BOOL C한이음_윈도우기본Dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	/*if (wParam == (IDC_CLOSE_BTN + 10002)) {
		m_caption_btn.p[0]->LoadBitmapImage(IDB_CLOSE_BTN, IDB_CLOSEDOWN_BTN);
	}*/
	// 시작할 때 한번에 불러서 무의미 
	return CDialogEx::OnCommand(wParam, lParam);
}


//재근 추가) VK_MENU alt키를 누른 상태에서 메뉴키를 호출함
//대화상자에는 PreTranslateMessage이 없어서 클래스 재정의를 통해 추가하였습니다.
BOOL C한이음_윈도우기본Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (GetKeyState(VK_MENU) < 0) {	//VK_MENU는 윈도우에서 Alt 키를 뜻합니다.
		POINT point;
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'F' || pMsg->wParam == 'f') {
			point.x = 50;	//50은 어차피 메뉴 중간값으로 가면 myMenuClick이 처리함.
			myMenuClick(point);	//myMenuClick을 일일이 나열할 수 밖에 없는건 alt 키만 눌렸을 경우도 있어서 
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


void C한이음_윈도우기본Dlg::OnNMRClickPathTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	TV_HITTESTINFO hit_info;

	::GetCursorPos(&hit_info.pt);// 트리 컨트롤에 대하여 좌표를 얻어옴 
	::ScreenToClient(m_my_tree_ctrl.m_hWnd, &hit_info.pt);
	// api 함수를 나타내는 ::에서만 핸들을 정해줄 수 있음 

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


void C한이음_윈도우기본Dlg::OnNewfileTree()
{
	LPWSTR str = L"";
	AddTreeItem(m_my_tree_ctrl.GetSelectedItem(), str);
	m_my_tree_ctrl.Expand(m_my_tree_ctrl.GetSelectedItem(), TVE_EXPAND);
}


void C한이음_윈도우기본Dlg::OnModifyFilename()
{
	m_my_tree_ctrl.EditLabel(m_my_tree_ctrl.GetSelectedItem());
}


void C한이음_윈도우기본Dlg::OnDeleteFile()
{
	m_my_tree_ctrl.DeleteItem(m_my_tree_ctrl.GetSelectedItem());
}


void C한이음_윈도우기본Dlg::OnTvnItemexpandedPathTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	if (pNMTreeView->action == 2) m_my_tree_ctrl.SetItemImage(pNMTreeView->itemNew.hItem, 0, 2);
	else m_my_tree_ctrl.SetItemImage(pNMTreeView->itemNew.hItem, 1, 3);

	*pResult = 0;
}

