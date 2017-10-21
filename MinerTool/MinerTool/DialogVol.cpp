// DialogVol.cpp : 实现文件
//

#include "stdafx.h"
#include "MinerTool.h"
#include "DialogVol.h"
#include "afxdialogex.h"


// CDialogVol 对话框

IMPLEMENT_DYNAMIC(CDialogVol, CDialogEx)

CDialogVol::CDialogVol(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_VOL, pParent)
{

}

CDialogVol::~CDialogVol()
{
}

void CDialogVol::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CDialogVol, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialogVol::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CDialogVol 消息处理程序


void CDialogVol::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
