
// MainFrm.cpp : CMainFrame 类的实现
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建一个视图以占用框架的工作区
	/*if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}*/

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	Initialize();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序

//void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
//{
//	// 将焦点前移到视图窗口
//	m_wndView.SetFocus();
//}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (!m_wndSplitter.CreateStatic(this, 2, 1))   
		return FALSE;   
	//下面createview的坐标错了,会报错
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_UserClient.Broadcast();
	CFrameWnd::OnTimer(nIDEvent);
}
