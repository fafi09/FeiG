#pragma once


// CUserView 视图

class CUserView : public CListView
{
	DECLARE_DYNCREATE(CUserView)

protected:
	CUserView();           // 动态创建所使用的受保护的构造函数
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


