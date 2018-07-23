
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "FeiG.h"

#include "MainFrm.h"
#include "ChatView.h"
#include "UserView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	//ON_WM_SETFOCUS()
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	/*if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("δ�ܴ�����ͼ����\n");
		return -1;
	}*/

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	Initialize();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

//void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
//{
//	// ������ǰ�Ƶ���ͼ����
//	m_wndView.SetFocus();
//}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ����ִ��Ĭ�ϴ���
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!m_wndSplitter.CreateStatic(this, 2, 1))   
		return FALSE;   
	//����createview���������,�ᱨ��
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CUserView),CSize( 20, 200 ), pContext);
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CChatView),CSize( 20, 20 ), pContext);
	//pContext->m_pCurrentFrame = this;
	//m_wndSplitter.RecalcLayout();
	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	CUserView* pUserView = (CUserView*)
	m_wndSplitter.GetPane(0,0);

	CChatView* pChatView = (CChatView*)m_wndSplitter.GetPane(1,0);

	m_UserServer.m_pUserView = pUserView;
	m_UserServer.m_pChatView = pChatView;

	return TRUE;
}

void CMainFrame::Initialize()
{
	m_UserServer.InitServer();
	m_UserClient.InitClient(m_hWnd);

	m_UserClient.Broadcast();
	SetTimer(1, 5000*10, NULL);
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_UserClient.Broadcast();
	CFrameWnd::OnTimer(nIDEvent);
}
