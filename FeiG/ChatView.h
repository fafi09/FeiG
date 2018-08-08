#pragma once
#include "afxwin.h"
#include "resource.h"
#include "UserClient.h"

// CChatView 窗体视图

class CChatView : public CFormView
{
	DECLARE_DYNCREATE(CChatView)

protected:
	CChatView();           // 动态创建所使用的受保护的构造函数
	virtual ~CChatView();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_wndChatList;
	CEdit m_wndChatData;
	afx_msg void OnBnClickedSendBtn();
	CUserClient* m_pUserClient;
	void AddChat(CString strChat, CString strIP);
};


