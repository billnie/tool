// DialogVol.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MinerTool.h"
#include "DialogVol.h"
#include "afxdialogex.h"


// CDialogVol �Ի���

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


// CDialogVol ��Ϣ�������


void CDialogVol::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
