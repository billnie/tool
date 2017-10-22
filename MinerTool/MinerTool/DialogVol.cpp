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
	DDX_Control(pDX, IDC_COMBO1, m_typeMiner);
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


BOOL CDialogVol::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_typeMiner.AddString("D3");
	m_typeMiner.AddString("L3");
	m_typeMiner.AddString("L3_P");

	m_typeMiner.AddString("S3");
	m_typeMiner.AddString("S4");
	m_typeMiner.AddString("S4_P");

	m_typeMiner.AddString("S5");
	m_typeMiner.AddString("S5_P");
	m_typeMiner.AddString("S7");

	m_typeMiner.AddString("S9");
	m_typeMiner.AddString("T9");
	m_typeMiner.AddString("T9_P");
	m_typeMiner.SetCurSel(0);
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle()
		| LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);	//设置扩展风格

	m_listCtrl.ModifyStyle(0, LVS_SINGLESEL);
	//设置列表头
	int i = 2;
	m_listCtrl.InsertColumn(0, _T("IP"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(1, _T("STATUS"), LVCFMT_CENTER);

	CRect rect;
	int nWidth;
	m_listCtrl.GetClientRect(&rect);					//获取客户区宽度
	nWidth = rect.Width();
	m_listCtrl.SetColumnWidth(0, 120);	//测试条件1 
	m_listCtrl.SetColumnWidth(1, 78);	//测试条件1 
	nWidth = 60;
	i = 2;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
int CDialogVol::newSearch(string host, int min, int max)
{
	m_listCtrl.DeleteAllItems();
	string s;
	int i, cnt;
	char buf[32];	cnt = 0;
	for (i = min; i < max; i++) {
		s = host;	sprintf(buf, ".%d", i);
		s += buf;
		cnt = m_listCtrl.InsertItem(cnt, s.c_str());
	}
	return 0;
}
int CDialogVol::newSearch(vector<string>&vs) {
	m_listCtrl.DeleteAllItems();
	string s;
	int i, cnt;
	char buf[32];	cnt = 0;
	vector<string>::iterator it;
	for (it = vs.begin(); it != vs.end();) {
		//判断是否是ip
		cnt = m_listCtrl.InsertItem(cnt, (*it).c_str());
		it++;
	}
	return 0;
}