
// ������_������⺻.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// C������_������⺻App:
// �� Ŭ������ ������ ���ؼ��� ������_������⺻.cpp�� �����Ͻʽÿ�.
//

class C������_������⺻App : public CWinApp
{
public:
	C������_������⺻App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern C������_������⺻App theApp;