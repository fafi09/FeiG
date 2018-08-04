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
	ON_WM_TIMER()
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

	//���heartbeat�Ķ�ʱ��
	SetTimer(2, 7000*10, NULL);
	return 0;
}


void CUserView::AddUser(CString strName, CString strIP, CString strSign)
{
	CListCtrl& theCtrl = GetListCtrl();
	int nItem = FindUser(strIP);
	if(nItem != -1) 
	{
		//����heartbeatΪtrue
		theCtrl.SetItemData(nItem, 1);
		return;
	}
	
	nItem = theCtrl.GetItemCount();
	nItem = theCtrl.InsertItem(nItem,strName);
	theCtrl.SetItemText(nItem,1, strIP);
	theCtrl.SetItemText(nItem,2, strSign);
	//����heartbeatΪtrue
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent != 2)
	{
		//CListView��OnTimer()����ֻ����һ�ε�����
		//����ĵ�OnTimer()�����KillTimer,ɱ����Ķ�ʱ����
		CListView::OnTimer(nIDEvent);
		return;
	}
		

	CListCtrl& theCtrl = GetListCtrl();
	int nCount = theCtrl.GetItemCount();

	for(int i = 0; i < nCount; i++)
	{
		//��ȡHeartBeat��ֵ  GetItemData:�ǽ�����������ȡ����
		int data = theCtrl.GetItemData(i);
		//�ж�HeartBeat��ֵ
		if(data > 0)
		{
			//���HeartBeat��ֵ  SetItemData�Ĺ����ǰ���Ӧ����Ŀ��һ�����������
			theCtrl.SetItemData(i, 0);
		}
		else
		{
			theCtrl.DeleteItem(i);
		}
	}

	
}
