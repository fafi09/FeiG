// UserView.cpp : ʵ���ļ�
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


// CUserView ���

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


// CUserView ��Ϣ�������


int CUserView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ModifyStyle(1,LVS_REPORT);
	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.InsertColumn(0, _T("���������"), LVCFMT_LEFT,100);
	theCtrl.InsertColumn(1, _T("IP��ַ"), LVCFMT_LEFT,100);
	theCtrl.InsertColumn(2, _T("ǩ��"), LVCFMT_LEFT,100);

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
