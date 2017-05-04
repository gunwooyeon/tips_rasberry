// CapBtn.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "������_������⺻.h"
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
	if (changeImgFlag == 1) { // ��ư�� ������ ��
							  // ���콺 ���� �� �϶�
		CBitmap m_img;

		// ���콺 Ŀ���� Picture Control ���� �ȿ� ������ �ε��ų ��Ʈ���� �ε��մϴ�
		m_img.LoadBitmap(second_img);

		// ��Ʈ���� Picture Control�� ��ġ ��ŵ�ϴ�
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

// CapBtn �޽��� ó�����Դϴ�.




void CapBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_btn_clicked = 1;
	changeImgFlag = 1;
	SetCapture();
	// ��ư ���� 
	Set_MyBitmap();

	CStatic::OnLButtonDown(nFlags, point);
}


void CapBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_btn_clicked = 0; 
	changeImgFlag = 0;

	ReleaseCapture();
	// ��ư �ȴ��� 

	Set_MyBitmap();

	CStatic::OnLButtonUp(nFlags, point);
}

void CapBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	POINT p;
	GetCursorPos(&p);
	GetParent()->ScreenToClient(&p);
	// �θ� �����쿡 �°� ��ǥ�� ���ؿ� 

	if (p.y <= m_test_r.bottom && p.x >= m_test_r.left && p.x <= m_test_r.right && p.y >= m_test_r.top && m_btn_clicked == 1) {
		// countFlag�� ���¸� �˻��Ͽ� 0�� ��� ���콺 Ŀ���� ���� Picture Control �����ȿ� ���� ���� ������ �ǹ��ϹǷ�
		// ���� ���콺 Ŀ���� Picture Control ������ ������ ��� ���� 1�� �����Ͽ� ���̻� ��Ʈ���� �׸��� �ʵ��� �մϴ�.
		if (countFlag == 0)
		{
			// ���� Picture Control�� ���� ������ ���� CRect ����ü ���� m_test_r��
			// Picture Control�� ũ�� ������ ����ϴ�.

			// �θ� �����쿡 WM_COMMAND �޼����� �����ϴ�. �θ� �����쿡�� WM_COMMAND �޼����� �޾Ƽ�
			// �ش� ��Ʈ���� ID + 10002 �޼����� ���� ó�� ��ƾ�� �����ϰ� �˴ϴ�.
			// �θ� �����쿡���� �� �޼����� �޾����� MyPicture Ŭ������ ����Լ� Load_MyBitmap()�� ���Ͽ�
			// �ε� ��Ű���� �ϴ� ��Ʈ���� ID �ΰ��� �Ѱ��ݴϴ�.
			//GetParent()->SendMessage(WM_COMMAND, GetDlgCtrlID() + 10002, (LPARAM)m_hWnd);

			// Timer ������ ���Ͽ� ���콺 Ŀ���� Picture Control ���� �ȿ� �ִٰ� ���� ���� ��츦 üũ�ϰ� �˴ϴ�.
			// ���콺 Ŀ���� Picture Control ������ ���� ���� ��� ���콺 Ŀ���� Picture Control ���� �ȿ� ������
			// �ε� �ߴ� ��Ʈ�ʿ��� ���콺 Ŀ���� ������ ���� ���� ����� ��Ʈ������ �����մϴ�.
			SetTimer(1, 30, NULL);

			// countFlag�� 1�� �����Ͽ� ��Ʈ���� �ѹ��� �׸����� �����մϴ�.
			countFlag = 1;

			// ��Ʈ���� �׸��� ���� ��� �Լ� Set_MyBitmap()�� ȣ���մϴ�.
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

		// ���� ���콺�� ��ġ�� �޾ƿ��� ���� GetCursorPos �Լ��� ȣ���մϴ�.
		GetCursorPos(&p);
		GetParent()->ScreenToClient(&p);

		// PtInRect �Լ��� �ش� �����ȿ� ���콺 Ŀ���� ��ġ�� �����ϸ� 0�� �ƴ� ���� �������ְ�
		// �������� �ʴ� �ٸ� 0�� �����մϴ�.
		// ��� ���� m_test_r�� Picture Control�� ���� ������ ��� �ִ� CRect ����ü �����Դϴ�.
		// �� �����ȿ� ���콺 Ŀ���� �����ϴ����� �˻��մϴ�. ���� �������� �ʴ´ٸ� ��Ʈ���� �ٲ��ְ� �˴ϴ�.
		if (p.y < m_test_r.top || p.y > m_test_r.bottom ||
			p.x < m_test_r.left || p.x > m_test_r.right)
		{
			// ���� �ε�Ǿ� �ִ� ��Ʈ���� ���콺 Ŀ���� Picture Control ���� �ȿ� ������ �ε�Ǵ� ��Ʈ������ Ȯ��
			// �մϴ�.
			if (changeImgFlag == 1)
			{
				// ���콺 Ŀ���� Picture Control ������ ���� ������ �ε� ���Ѿ��� ��Ʈ���� ����
				// chagneImgFlag�� 1�� �����մϴ�.
				changeImgFlag = 0;

				// ��Ʈ���� �����ϱ� ���� ����Լ� Set_MyBitmap()�� ȣ���մϴ�.
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

	// ���� ���콺�� ��ġ�� �޾ƿ��� ���� GetCursorPos �Լ��� ȣ���մϴ�.
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

	// ���� ���콺�� ��ġ�� �޾ƿ��� ���� GetCursorPos �Լ��� ȣ���մϴ�.
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

	// ���� ���콺�� ��ġ�� �޾ƿ��� ���� GetCursorPos �Լ��� ȣ���մϴ�.
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
