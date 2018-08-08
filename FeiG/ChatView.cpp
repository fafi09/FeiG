// ChatView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FeiG.h"
#include "ChatView.h"
#include "UserView.h"

// CChatView

IMPLEMENT_DYNCREATE(CChatView, CFormView)

CChatView::CChatView()
	: CFormView(CChatView::IDD)
{

}

CChatView::~CChatView()
{
}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAT_LIST, m_wndChatList);
	DDX_Control(pDX, IDC_CHAT_CONTENT, m_wndChatData);
}

BEGIN_MESSAGE_MAP(CChatView, CFormView)
	ON_BN_CLICKED(IDC_SEND_BTN, &CChatView::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CChatView ���

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChatView ��Ϣ�������


void CChatView::OnBnClickedSendBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//
	CSplitterWnd* pWnd = (CSplitterWnd*)this->GetParent();
	CUserView* pUserView = (CUserView*)(pWnd->GetPane(0,0));
	CListCtrl& theCtrl = pUserView->GetListCtrl();


	int nIdx = theCtrl.GetNextItem(-1,LVNI_SELECTED);

	if(nIdx != -1)
	{
		CString strIP = theCtrl.GetItemText(nIdx,1);
		CString msg;
		m_wndChatData.GetWindowTextW(msg);

		m_pUserClient->SendChat(strIP,msg,FALSE);

		MessageBox(strIP);
	}

	
}


void CChatView::AddChat(CString strChat, CString strIP)
{
	CTime tmCur = CTime::GetCurrentTime();
	CString strTime = tmCur.Format("%Y-%m-%d %H:%M:%S");

	CString strData = strIP + TEXT(" ") + strTime + TEXT(":") + strChat;
	int nItem = m_wndChatList.AddString(strData);
	m_wndChatList.SetCurSel(nItem);
}
