// DialogPool.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MinerTool.h"
#include "DialogPool.h"
#include "afxdialogex.h"

#include <boost/progress.hpp>  
#include "sstream"  
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/json_parser.hpp>  
#include <boost/property_tree/xml_parser.hpp>  
#include <boost/typeof/typeof.hpp>  
#include <boost/foreach.hpp>  
// CDialogPool �Ի���

IMPLEMENT_DYNAMIC(CDialogPool, CDialogEx)

CDialogPool::CDialogPool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_POOL, pParent)
{

}

CDialogPool::~CDialogPool()
{
}

void CDialogPool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CDialogPool, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialogPool::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CDialogPool ��Ϣ�������


void CDialogPool::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


BOOL CDialogPool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle()
		| LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);	//������չ���

	m_listCtrl.ModifyStyle(0, LVS_SINGLESEL);
	//�����б�ͷ
	int i = 2;
	m_listCtrl.InsertColumn(0, _T("x,y,sub"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(1, _T("state"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u1"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u2"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u3"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u4"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u5"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u6"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u7"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u8"), LVCFMT_CENTER);
	//���ø��еĿ��
	CRect rect;
	int nWidth;
	m_listCtrl.GetClientRect(&rect);					//��ȡ�ͻ������
	nWidth = rect.Width();
	m_listCtrl.SetColumnWidth(0, 60);	//��������1 
	m_listCtrl.SetColumnWidth(1, 58);	//��������1 
	nWidth = 40;
	i = 2;
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//��������1 

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


int CDialogPool::AddNote(string resp)
{

	return 0;
}
