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
	ON_WM_TIMER()
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

	//检测heartbeat的定时器
	SetTimer(2, 7000*10, NULL);
	return 0;
}


void CUserView::AddUser(CString strName, CString strIP, CString strSign)
{
	CListCtrl& theCtrl = GetListCtrl();
	int nItem = FindUser(strIP);
	if(nItem != -1) 
	{
		//设置heartbeat为true
		theCtrl.SetItemData(nItem, 1);
		return;
	}
	
	nItem = theCtrl.GetItemCount();
	nItem = theCtrl.InsertItem(nItem,strName);
	theCtrl.SetItemText(nItem,1, strIP);
	theCtrl.SetItemText(nItem,2, strSign);
	//设置heartbeat为true
	theCtrl.SetItemData(nItem, 1);

}


int CUserView::FindUser(CString strIP)
{
	CListCtrl& theCtrl = GetListCtrl();
	int nCount = theCtrl.GetItemCount();
	for(int i = 0; i < nCount; i++)
	{
		CString strItemIp = theCtrl.GetItemText(i,1);
		if(strItemIp.CompareNoCase(strIP)==0)
		{
			return i;
		}
	}
	return -1;
}


void CUserView::DelUser(CString strIP)
{
	int nItem = FindUser(strIP);
	if(nItem == -1)
	{
		return;
	}
	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.DeleteItem(nItem);

}


void CUserView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent != 2)
	{
		//CListView中OnTimer()函数只进入一次的问题
		//基类的的OnTimer()会调用KillTimer,杀死你的定时器。
		CListView::OnTimer(nIDEvent);
		return;
	}
		

	CListCtrl& theCtrl = GetListCtrl();
	int nCount = theCtrl.GetItemCount();

	for(int i = 0; i < nCount; i++)
	{
		//获取HeartBeat数值  GetItemData:是将关联的内容取出来
		int data = theCtrl.GetItemData(i);
		//判断HeartBeat数值
		if(data > 0)
		{
			//清空HeartBeat数值  SetItemData的功能是把相应的条目与一个数据相关联
			theCtrl.SetItemData(i, 0);
		}
		else
		{
			theCtrl.DeleteItem(i);
		}
	}

	
}
