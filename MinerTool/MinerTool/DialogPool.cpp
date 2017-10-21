// DialogPool.cpp : 实现文件
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
// CDialogPool 对话框

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


// CDialogPool 消息处理程序


void CDialogPool::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL CDialogPool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle()
		| LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);	//设置扩展风格

	m_listCtrl.ModifyStyle(0, LVS_SINGLESEL);
	//设置列表头
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
	//设置各列的宽度
	CRect rect;
	int nWidth;
	m_listCtrl.GetClientRect(&rect);					//获取客户区宽度
	nWidth = rect.Width();
	m_listCtrl.SetColumnWidth(0, 60);	//测试条件1 
	m_listCtrl.SetColumnWidth(1, 58);	//测试条件1 
	nWidth = 40;
	i = 2;
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


int CDialogPool::AddNote(string resp)
{

	return 0;
}
