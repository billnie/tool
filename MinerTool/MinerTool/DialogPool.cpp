// DialogPool.cpp : 实现文件
//

#include "stdafx.h"
#include "MinerTool.h"
#include "DialogPool.h"
#include "afxdialogex.h"
#include "MinerToolView.h"
#include <boost/progress.hpp>  
#include "sstream"  
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/json_parser.hpp>  
#include <boost/property_tree/xml_parser.hpp>  
#include <boost/typeof/typeof.hpp>  
#include <boost/foreach.hpp>  

#include <boost/property_tree/ptree.hpp>    
#include <boost/property_tree/ini_parser.hpp>  
#include "csv/writer.hpp"

// CDialogPool 对话框
#include	"stlstr.h"
using namespace str;
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
	DDX_Control(pDX, IDC_COMBO1, m_typePool);
}


BEGIN_MESSAGE_MAP(CDialogPool, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialogPool::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_CHECK, &CDialogPool::OnBnClickedBtnCheck)
	ON_BN_CLICKED(IDC_BTN_SET, &CDialogPool::OnBnClickedBtnSet)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CDialogPool::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// CDialogPool 消息处理程序


void CDialogPool::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	saveParam();
	*pResult = 0;
}


BOOL CDialogPool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_typePool.AddString("BTC");
	m_typePool.AddString("LTC");
	m_typePool.AddString("DASH");
	m_typePool.SetCurSel(0);

	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle()
		| LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);	//设置扩展风格

	m_listCtrl.ModifyStyle(0, LVS_SINGLESEL);
	//设置列表头
	int i = 2;
	m_listCtrl.InsertColumn(0, _T("IP"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(1, _T("STATUS"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Type"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Version"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("freq"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Elapsed"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Hash Rate(5s)"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Hash Rate(avg)"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("HW"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("HWP"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Temp"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Fan"), LVCFMT_CENTER);

	//设置各列的宽度
	CRect rect;
	int nWidth;
	m_listCtrl.GetClientRect(&rect);					//获取客户区宽度
	nWidth = rect.Width();
	m_listCtrl.SetColumnWidth(0, 120);	//测试条件1 
	m_listCtrl.SetColumnWidth(1, 78);	//测试条件1 
	nWidth = 60;
	i = 2;
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, 100);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, 100);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 
	m_listCtrl.SetColumnWidth(i++, nWidth);	//测试条件1 

	//读取配置参数
	string sip;
	int st=0;
	//读取参数
	boost::property_tree::ptree pt;
	try
	{
		boost::property_tree::ini_parser::read_ini("./bittool.ini", pt);  // 打开读文件  			
		st = pt.get<int>("Pool.pool1",1);
		CheckDlgButton(IDC_POOL1, st);
		st = pt.get<int>("Pool.poo12",1);
		CheckDlgButton(IDC_POOL2, st);
		st = pt.get<int>("Pool.poo13",1);
		CheckDlgButton(IDC_POOL3, st);

		st = pt.get<int>("Pool.suffix1",1);
		if (st = 1)
			CheckRadioButton(IDC_RADIO_PL1IP, IDC_RADIO_PL1NONE, IDC_RADIO_PL1IP);
		else
			CheckRadioButton(IDC_RADIO_PL1IP, IDC_RADIO_PL1NONE, IDC_RADIO_PL1NONE);
		st = pt.get<int>("Pool.suffix2",1);
		if (st = 1)
			CheckRadioButton(IDC_RADIO_PL2IP, IDC_RADIO_PL2NONE, IDC_RADIO_PL2IP);
		else
			CheckRadioButton(IDC_RADIO_PL2IP, IDC_RADIO_PL2NONE, IDC_RADIO_PL2NONE);

		st = pt.get<int>("Pool.suffix3",1);
		if (st = 1)
			CheckRadioButton(IDC_RADIO_PL3IP, IDC_RADIO_PL3NONE, IDC_RADIO_PL3IP);
		else
			CheckRadioButton(IDC_RADIO_PL3IP, IDC_RADIO_PL3NONE, IDC_RADIO_PL3NONE);
	}
	catch (std::exception e)
	{
		cout << e.what();
		boost::property_tree::ini_parser::write_ini("bittool.ini", pt);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
std::string dev_info::INDEX = "index";
std::string dev_info::DEVS = "DEVS";
std::string dev_info::STATUS = "STATUS";
std::string dev_info::id = "id";

int CDialogPool::AddNote(string resp, string host)
{
	if (resp.length() > 0) {
		dev_info info;
		std::istringstream iss;
		iss.str(resp.c_str());
		boost::property_tree::ptree parser;
		boost::property_tree::json_parser::read_json(iss, parser);
		boost::property_tree::ptree sms_array = parser.get_child(dev_info::DEVS);
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, sms_array)
		{
			boost::property_tree::ptree p = v.second;
			dev_item it;
			it.parseFromPTree(p);
			info.items.push_back(it);
			//m_devMap[it.]
		}
		boost::property_tree::ptree array = parser.get_child(dev_info::STATUS);
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, array)
		{
			boost::property_tree::ptree p = v.second;
			dev_status it;
			it.parseFromPTree(p);
			info.status.push_back(it);
		}
		addListNote(info, host);
	}
	
	return 0;
}


int CDialogPool::addListNote(dev_info &info, string host)
{
	int cnt, cnx;
	int ret;
	int fsid, gfsid;
	int sub;
	int direct = 0;
	int x, y;
	CString str1, str2, str3, str;
	string ss;
	cnt = m_listCtrl.GetItemCount();
	cnt = m_listCtrl.InsertItem(cnt, host.c_str());
	m_listCtrl.SetItemText(cnt, 1, info.status[0].Description.c_str());
	m_listCtrl.SetItemText(cnt, 2, info.status[0].STATUS.c_str());
	m_listCtrl.SetItemText(cnt, 3, info.status[0].Msg.c_str());
//	m_listCtrl.SetItemText(cnt, 4, "未开始");

	return 0;
}


int CDialogPool::saveParam()
{
	boost::property_tree::ptree pt;
	boost::property_tree::ptree pool_setting;
//	pool_setting = pt.get_child("Pool");
	boost::property_tree::ini_parser::read_ini("bittool.ini", pt);  // 打开读文件  
	pt.put<int>("Pool.pool1", IsDlgButtonChecked(IDC_POOL1));
	pt.put<int>("Pool.pool2", IsDlgButtonChecked(IDC_POOL2));
	pt.put<int>("Pool.pool3", IsDlgButtonChecked(IDC_POOL3));

	pt.put<int>("Pool.suffix1", GetCheckedRadioButton(IDC_RADIO_PL1IP, IDC_RADIO_PL1NONE)== IDC_RADIO_PL1IP);
	pt.put<int>("Pool.suffix2", GetCheckedRadioButton(IDC_RADIO_PL2IP, IDC_RADIO_PL2NONE)== IDC_RADIO_PL2IP);
	pt.put<int>("Pool.suffix3", GetCheckedRadioButton(IDC_RADIO_PL3IP, IDC_RADIO_PL3NONE)== IDC_RADIO_PL3IP);
	
	boost::property_tree::ini_parser::write_ini("bittool.ini", pt);
	return 0;
}


void CDialogPool::OnBnClickedBtnCheck()
{
	int ret = -1;
	int cnt;
	CString str;
	cnt = m_listCtrl.GetItemCount();
	if (cnt > 0) {
		POSITION pos;
		pos = m_listCtrl.GetFirstSelectedItemPosition();
		if (pos) {
			cnt = m_listCtrl.GetNextSelectedItem(pos);
			str = m_listCtrl.GetItemText(cnt, 0);
			CMinerToolView *form;
			form = (CMinerToolView *)GetParent()->GetParent();
			if (form) {
				form->GetMinnerInfo(str);
			}
		}
	}
}


void CDialogPool::OnBnClickedBtnSet()
{
	int ret = -1;
	int cnt;
	CString str,s;
	cnt = m_listCtrl.GetItemCount();
	if (cnt > 0) {
		POSITION pos;
		pos = m_listCtrl.GetFirstSelectedItemPosition();
		if (pos) {
			cnt = m_listCtrl.GetNextSelectedItem(pos);
			str = m_listCtrl.GetItemText(cnt, 0);
			CMinerToolView *form;
			form = (CMinerToolView *)GetParent()->GetParent();
			if (form) {
				form->SaveMinnerInfo(str,s);
			}
		}
	}
	saveParam();
}


int CDialogPool::newSearch(string host, int min, int max)
{
	m_listCtrl.DeleteAllItems();
	string s;
	int i,cnt ;
	char buf[32];	cnt = 0;
	for (i = min; i <= max; i++) {
		s = host;	sprintf(buf, ".%d", i);
		s += buf;
		cnt = m_listCtrl.InsertItem(cnt, s.c_str());
	}
	return 0;
}
int CDialogPool::newSearch(vector<string>&vs) {
	m_listCtrl.DeleteAllItems();
	string s;
	int i, cnt;
	char buf[32];	cnt = 0;
	vector<string>::iterator it;
	for (it = vs.begin(); it != vs.end();) {
		//判断是否是ip
		if (isregxip(*it)) {
			cnt = m_listCtrl.InsertItem(cnt, (*it).c_str());
		}
		it++;
	}
	return 0;
}

void CDialogPool::OnBnClickedBtnExport()
{
	BOOL isOpen = FALSE;        //是否打开(否则为保存)  
	CString defaultDir = "";   //默认打开的文件路径  
	CString fileName = "";         //默认打开的文件名  
	CString filter = "文件 (*.csv)|*.csv||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);

	INT_PTR result = openFileDlg.DoModal();
	CString filePath ;
	if (result==IDOK) {
		filePath = openFileDlg.GetPathName();
		std::ofstream file;
		file.open((LPCTSTR)filePath);
		int i, n;
		CString s;
		n = m_listCtrl.GetItemCount();
		Csv::Writer writer(file, ';');
		Csv::Row header, row;
		header.push_back("No");
		header.push_back("ip");
		writer.insert(header);
		for (i = 0; i < n; i++) {
			Csv::Row  row;
			row.push_back(str::format("%d", i + 1));
			s = m_listCtrl.GetItemText(i, 0);
			row.push_back((LPCTSTR)s);
			writer.insert(row);
		}
		file.close();
	}

}

int CDialogPool::updateDevs(string host, string data) {
	if (data.length() > 0) {
		dev_info info;
		std::istringstream iss;
		iss.str(data.c_str());
		boost::property_tree::ptree parser;
		boost::property_tree::json_parser::read_json(iss, parser);
		boost::property_tree::ptree sms_array = parser.get_child(dev_info::DEVS);
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, sms_array)
		{
			boost::property_tree::ptree p = v.second;
			dev_item it;
			it.parseFromPTree(p);
			info.items.push_back(it);
			m_devMap[host] = it;
		}
		boost::property_tree::ptree array = parser.get_child(dev_info::STATUS);
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, array)
		{
			boost::property_tree::ptree p = v.second;
			dev_status it;
			it.parseFromPTree(p);
			info.status.push_back(it);
		}
		addListNote(info, host);
	}
	return 0;
}
