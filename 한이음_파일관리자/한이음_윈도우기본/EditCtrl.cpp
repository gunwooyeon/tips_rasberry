// EditCtrl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "������_������⺻.h"
#include "EditCtrl.h"


// EditCtrl

IMPLEMENT_DYNAMIC(EditCtrl, CEdit)

EditCtrl::EditCtrl()
{

}

EditCtrl::~EditCtrl()
{
}


BEGIN_MESSAGE_MAP(EditCtrl, CEdit)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// EditCtrl �޽��� ó�����Դϴ�.




int EditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)

	return 0;
}



void EditCtrl::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);
}
