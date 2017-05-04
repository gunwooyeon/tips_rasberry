// CapBtn.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "한이음_윈도우기본.h"
#include "CapBtn.h"


// CapBtn

IMPLEMENT_DYNAMIC(CapBtn, CStatic)

CapBtn::CapBtn()
{
}

CapBtn::~CapBtn()
{
}


BEGIN_MESSAGE_MAP(CapBtn, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



void CapBtn::LoadBitmapImage(int first,int second) {
	first_img = first;
	second_img = second;
	GetWindowRect(this->m_test_r);

	Set_MyBitmap();
}

void CapBtn::Set_MyBitmap() {
	if (changeImgFlag == 1) { // 버튼이 눌렸을 때
							  // 마우스 영역 안 일때
		CBitmap m_img;

		// 마우스 커서가 Picture Control 영역 안에 있을때 로드시킬 비트맵을 로드합니다
		m_img.LoadBitmap(second_img);

		// 비트맵을 Picture Control에 배치 시킵니다
		HBITMAP h_old_bitmap = SetBitmap(m_img);

		if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

		m_img.Detach();
	}
	else if (changeImgFlag == 0) {
		CBitmap m_img;
		m_img.LoadBitmap(first_img);

		HBITMAP h_old_bitmap = SetBitmap(m_img);

		if (h_old_bitmap != NULL) ::DeleteObject(h_old_bitmap);

		m_img.Detach();

		changeImgFlag = 1;
		countFlag = 0;
	}

}


void CapBtn::Set_Clicked_Btn(char a_state) {
	m_btn_clicked = a_state;
}

// CapBtn 메시지 처리기입니다.




void CapBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_btn_clicked = 1;
	changeImgFlag = 1;
	SetCapture();
	// 버튼 눌림 
	Set_MyBitmap();

	CStatic::OnLButtonDown(nFlags, point);
}


void CapBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_btn_clicked = 0; 
	changeImgFlag = 0;

	ReleaseCapture();
	// 버튼 안눌림 

	Set_MyBitmap();

	CStatic::OnLButtonUp(nFlags, point);
}

void CapBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	POINT p;
	GetCursorPos(&p);
	GetParent()->ScreenToClient(&p);
	// 부모 윈도우에 맞게 좌표를 구해옴 

	if (p.y <= m_test_r.bottom && p.x >= m_test_r.left && p.x <= m_test_r.right && p.y >= m_test_r.top && m_btn_clicked == 1) {
		// countFlag의 상태를 검사하여 0일 경우 마우스 커서가 아직 Picture Control 영역안에 들어와 있지 않음을 의미하므로
		// 만약 마우스 커서가 Picture Control 영역에 들어왔을 경우 값을 1로 변경하여 더이상 비트맵을 그리지 않도록 합니다.
		if (countFlag == 0)
		{
			// 현재 Picture Control의 영역 정보를 담을 CRect 구조체 변수 m_test_r에
			// Picture Control의 크기 정보를 담습니다.

			// 부모 윈도우에 WM_COMMAND 메세지를 보냅니다. 부모 윈도우에서 WM_COMMAND 메세지를 받아서
			// 해당 컨트롤의 ID + 10002 메세지에 대한 처리 루틴을 구성하게 됩니다.
			// 부모 윈도우에서는 이 메세지를 받았을시 MyPicture 클래스의 멤버함수 Load_MyBitmap()를 통하여
			// 로드 시키고자 하는 비트맵의 ID 두개를 넘겨줍니다.
			//GetParent()->SendMessage(WM_COMMAND, GetDlgCtrlID() + 10002, (LPARAM)m_hWnd);

			// Timer 설정을 통하여 마우스 커서가 Picture Control 영역 안에 있다가 벗어 났을 경우를 체크하게 됩니다.
			// 마우스 커서가 Picture Control 영역을 벗어 났을 경우 마우스 커서가 Picture Control 영역 안에 있을때
			// 로드 했던 비트맵에서 마우스 커서가 영역을 벗어 났을 경우의 비트맵으로 변경합니다.
			SetTimer(1, 30, NULL);

			// countFlag를 1로 설정하여 비트맵을 한번만 그리도록 제한합니다.
			countFlag = 1;

			// 비트맵을 그리기 위한 멤버 함수 Set_MyBitmap()을 호출합니다.
			Set_MyBitmap();
		}
	}
	
	CStatic::OnMouseMove(nFlags, point);
}


void CapBtn::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		POINT p;

		// 현재 마우스의 위치를 받아오기 위해 GetCursorPos 함수를 호출합니다.
		GetCursorPos(&p);
		GetParent()->ScreenToClient(&p);

		// PtInRect 함수는 해당 영역안에 마우스 커서가 위치가 존재하면 0이 아닌 값을 리턴해주고
		// 존재하지 않는 다면 0을 리턴합니다.
		// 멤버 변수 m_test_r는 Picture Control의 영역 정보가 담겨 있는 CRect 구조체 변수입니다.
		// 이 영역안에 마우스 커서가 존재하는지를 검사합니다. 만약 존재하지 않는다면 비트맵을 바꿔주게 됩니다.
		if (p.y < m_test_r.top || p.y > m_test_r.bottom ||
			p.x < m_test_r.left || p.x > m_test_r.right)
		{
			// 현재 로드되어 있는 비트맵이 마우스 커서가 Picture Control 영역 안에 있을때 로드되는 비트맵인지 확인
			// 합니다.
			if (changeImgFlag == 1)
			{
				// 마우스 커서가 Picture Control 영역을 벗어 났을때 로드 시켜야할 비트맵을 위해
				// chagneImgFlag를 1로 세팅합니다.
				changeImgFlag = 0;

				// 비트맵을 변경하기 위한 멤버함수 Set_MyBitmap()을 호출합니다.
				Set_MyBitmap();
			}
		}
	}
	CStatic::OnTimer(nIDEvent);
}




BEGIN_MESSAGE_MAP(CloseBtn, CapBtn)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CloseBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	POINT p;

	// 현재 마우스의 위치를 받아오기 위해 GetCursorPos 함수를 호출합니다.
	GetCursorPos(&p);
	GetParent()->ScreenToClient(&p);
	
	if (p.y >= m_test_r.top && p.y <= m_test_r.bottom &&
		p.x >= m_test_r.left && p.x <= m_test_r.right) 
	{
		GetParent()->PostMessage(WM_SYSCOMMAND, (WPARAM)SC_CLOSE);
	}

	CapBtn::OnLButtonUp(nFlags, point);
}





BEGIN_MESSAGE_MAP(MinimizeBtn, CapBtn)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void MinimizeBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	POINT p;

	// 현재 마우스의 위치를 받아오기 위해 GetCursorPos 함수를 호출합니다.
	GetCursorPos(&p);
	GetParent()->ScreenToClient(&p);
	if (p.y >= m_test_r.top && p.y <= m_test_r.bottom &&
		p.x >= m_test_r.left && p.x <= m_test_r.right)
	{
		GetParent()->PostMessage(WM_SYSCOMMAND, (WPARAM)SC_MINIMIZE);
	}

	CapBtn::OnLButtonUp(nFlags, point);
}




BEGIN_MESSAGE_MAP(MaximizeBtn, CapBtn)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void MaximizeBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	POINT p;

	// 현재 마우스의 위치를 받아오기 위해 GetCursorPos 함수를 호출합니다.
	GetCursorPos(&p);
	GetParent()->ScreenToClient(&p);
	if (p.y >= m_test_r.top && p.y <= m_test_r.bottom &&
		p.x >= m_test_r.left && p.x <= m_test_r.right)
	{
		m_maximize_flag = !m_maximize_flag;
		if (m_maximize_flag == 0) {
			GetParent()->PostMessage(WM_SYSCOMMAND, (WPARAM)SC_RESTORE);
			GetParent()->Invalidate(TRUE);
		}
		else if (m_maximize_flag == 1) {
			GetParent()->PostMessage(WM_SYSCOMMAND, (WPARAM)SC_MAXIMIZE);
			GetParent()->Invalidate(TRUE);
		}
	}

	CapBtn::OnLButtonUp(nFlags, point);
}
