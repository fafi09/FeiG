#pragma once


// CUserView ��ͼ

class CUserView : public CListView
{
	DECLARE_DYNCREATE(CUserView)

protected:
	CUserView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CUserView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


