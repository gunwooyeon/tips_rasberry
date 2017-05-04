#pragma once


// CapBtn

class CapBtn : public CStatic
{
protected:
	int first_img, second_img;
	char m_btn_clicked = 0; // ¾È´­¸² 
	char countFlag = 0;
	char changeImgFlag = 0;
	char m_maximize_flag = 0;
	CRect m_test_r;

	DECLARE_DYNAMIC(CapBtn)
public:
	CapBtn();
	virtual ~CapBtn();
	virtual char getFlag() { return -1; }
	virtual void setFlag(char a_flag) {}
	void LoadBitmapImage(int first, int second);
	void Set_Clicked_Btn(char a_state);
	void Set_MyBitmap();
	void setRectPos(CRect a_r) { m_test_r = a_r; }

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};



class CloseBtn : public CapBtn {
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

class MaximizeBtn : public CapBtn {
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual char getFlag() { return m_maximize_flag; }
	virtual void setFlag(char a_flag) { m_maximize_flag = a_flag; }
};

class MinimizeBtn : public CapBtn {
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


class ManageBtn : public CapBtn {
private:
	int cnt = 0;
public:
	int GetCount() { return cnt; }
	
	CapBtn* p[100];
	ManageBtn() {
		p[0] = new CloseBtn;
		p[1] = new MaximizeBtn;
		p[2] = new MinimizeBtn;
		cnt = 3;
	}
	virtual ~ManageBtn() {
		for (int i = 0; i < cnt; i++)
			delete p[i];
		cnt = 0;
	}
};

