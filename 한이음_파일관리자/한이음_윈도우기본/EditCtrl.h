#pragma once


// EditCtrl

class EditCtrl : public CEdit
{
	DECLARE_DYNAMIC(EditCtrl)

public:
	EditCtrl();
	virtual ~EditCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


