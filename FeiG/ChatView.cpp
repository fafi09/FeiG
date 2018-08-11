// ChatView.cpp : 实现文件
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
	DDX_Control(pDX, IDC_LIST_FILE, m_wndFileList);
	DDX_Control(pDX, IDC_STATIC_ZILIAO, m_wndStaticZiLiao);
	DDX_Control(pDX, IDC_LIST_RECVFILE, m_wndListRecvFile);
}

BEGIN_MESSAGE_MAP(CChatView, CFormView)
	ON_BN_CLICKED(IDC_SEND_BTN, &CChatView::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatView::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_FILEDLG, &CChatView::OnBnClickedButtonFiledlg)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CChatView::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVECANCEL, &CChatView::OnBnClickedButtonSavecancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDLG, &CChatView::OnBnClickedButtonSavedlg)
END_MESSAGE_MAP()


// CChatView 诊断

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


// CChatView 消息处理程序


void CChatView::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
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

	CString strData = strIP + TEXT(" ") + strTime + TEXT(":");
	int nItem = m_wndChatList.AddString(strData);
	m_wndChatList.AddString(strChat);
	m_wndChatList.SetCurSel(nItem);
}


void CChatView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


int CChatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	
	return 0;
}


void CChatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	LVCOLUMN col;

	BOOL isExist = m_wndFileList.GetColumn(0, &col);

	if(isExist == FALSE)
	{
		m_wndFileList.InsertColumn(0,TEXT("名称"),LVCFMT_LEFT, 100, -1);
		m_wndFileList.InsertColumn(1,TEXT("类型"),LVCFMT_LEFT, 100, -1);
		m_wndFileList.InsertColumn(2,TEXT("大小"),LVCFMT_LEFT, 100, -1);
		m_wndFileList.InsertColumn(3,TEXT("路径"),LVCFMT_LEFT, 100, -1);
	}
	
	//初始化接收的文件列表的列名
	isExist = m_wndListRecvFile.GetColumn(0, &col);
	if(isExist == FALSE)
	{
		m_wndListRecvFile.InsertColumn(0,TEXT("名称"),LVCFMT_LEFT, 100, -1);
		m_wndListRecvFile.InsertColumn(1,TEXT("类型"),LVCFMT_LEFT, 100, -1);
		m_wndListRecvFile.InsertColumn(2,TEXT("大小"),LVCFMT_LEFT, 100, -1);
		m_wndListRecvFile.InsertColumn(3,TEXT("路径"),LVCFMT_LEFT, 100, -1);
	}
	
}


void CChatView::OnBnClickedButtonFiledlg()
{
	CFileDialog fileDlg(TRUE);

	if(fileDlg.DoModal() == IDOK)
	{
		CString strFileName = fileDlg.GetFileName();
		int nItem = m_wndFileList.InsertItem(0, strFileName);
		CString strFilePath = fileDlg.GetPathName();


		//打开文件
		CFile file;
		CString strFileSize;
		CFileException e;

		if ( !file.Open( strFilePath, CFile::modeReadWrite, &e) )
		{
			TCHAR szError[1024];
			e.GetErrorMessage(szError, 1024);

			return;
		}
		else
		{
			strFileSize.Format(TEXT("%ld"),file.GetLength());
			m_wndFileList.SetItemText(nItem, 1, TEXT("文件"));
			m_wndFileList.SetItemText(nItem, 2,  strFileSize);
			m_wndFileList.SetItemText(nItem, 3, file.GetFilePath());
		}

	}
	
}


void CChatView::OnBnClickedButtonCancel()
{
	m_wndFileList.DeleteAllItems();
}


void CChatView::OnBnClickedButtonSavecancel()
{
	m_wndListRecvFile.DeleteAllItems();
}


void CChatView::OnBnClickedButtonSavedlg()
{
	CFileDialog recvDlg(FALSE);
	if(IDOK == recvDlg.DoModal())
	{
		CString strFileName = recvDlg.GetFileName();
		CString strFilePath = recvDlg.GetPathName();

		return;
	}
}
