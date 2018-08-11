#pragma once
#include "afxwin.h"
#include "resource.h"
#include "UserClient.h"
#include "afxcmn.h"

// CChatView ������ͼ

class CChatView : public CFormView
{
	DECLARE_DYNCREATE(CChatView)

protected:
	CChatView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_wndChatList;
	CEdit m_wndChatData;
	afx_msg void OnBnClickedSendBtn();
	CUserClient* m_pUserClient;
	void AddChat(CString strChat, CString strIP);
	afx_msg void OnBnClickedButton1();
	CListCtrl m_wndFileList;
	CStatic m_wndStaticZiLiao;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonFiledlg();
	afx_msg void OnBnClickedButtonCancel();
	CListCtrl m_wndListRecvFile;
	afx_msg void OnBnClickedButtonSavecancel();
	afx_msg void OnBnClickedButtonSavedlg();
};


