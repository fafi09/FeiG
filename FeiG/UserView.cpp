// UserView.cpp : 实现文件
//

#include "stdafx.h"
#include "FeiG.h"
#include "UserView.h"


// CUserView

IMPLEMENT_DYNCREATE(CUserView, CListView)

CUserView::CUserView()
{

}

CUserView::~CUserView()
{
}

BEGIN_MESSAGE_MAP(CUserView, CListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CUserView 诊断

#ifdef _DEBUG
void CUserView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserView 消息处理程序


int CUserView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ModifyStyle(1,LVS_REPORT);
	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.InsertColumn(0, _T("计算机名称"), LVCFMT_LEFT,100);
	theCtrl.InsertColumn(1, _T("IP地址"), LVCFMT_LEFT,100);
	theCtrl.InsertColumn(2, _T("签名"), LVCFMT_LEFT,100);

	return 0;
}


void CUserView::AddUser(CString strName, CString strIP, CString strSign)
{
	CListCtrl& theCtrl = GetListCtrl();
	int nItem = theCtrl.GetItemCount();
	nItem = theCtrl.InsertItem(nItem,strName);
	theCtrl.SetItemText(nItem,1, strIP);
	theCtrl.SetItemText(nItem,2, strSign);

}
