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

#include <boost/property_tree/ptree.hpp>    
#include <boost/property_tree/ini_parser.hpp>  
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
	m_listCtrl.InsertColumn(0, _T("IP"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(1, _T("STATUS"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Type"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Version"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("freq"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("Elapse"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u5"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u6"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u7"), LVCFMT_CENTER);
	m_listCtrl.InsertColumn(i++, _T("u8"), LVCFMT_CENTER);
	//设置各列的宽度
	CRect rect;
	int nWidth;
	m_listCtrl.GetClientRect(&rect);					//获取客户区宽度
	nWidth = rect.Width();
	m_listCtrl.SetColumnWidth(0, 120);	//测试条件1 
	m_listCtrl.SetColumnWidth(1, 78);	//测试条件1 
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

	//读取配置参数
	string sip;
	int st;
	//读取参数
	boost::property_tree::ptree pt;
	try
	{
		//		boost::property_tree::ini_parser::read_ini("./config.ini", pt);
		boost::property_tree::ini_parser::read_ini("./bittool.ini", pt);  // 打开读文件  
																	  //boost::property_tree::ini_parser::write_ini("E:\\Projects\\boost_property_tree\\Overlay.ini", pt); // 写到文件    
		st = pt.get<int>("Pool.poo11");
		CheckDlgButton(IDC_POOL1, st);
		st = pt.get<int>("Pool.poo12");
		CheckDlgButton(IDC_POOL2, st);
		st = pt.get<int>("Pool.poo13");
		CheckDlgButton(IDC_POOL3, st);

		//st = pt.get<int>("Pool.suffix1");
		//CheckDlgButton(IDC_POOL1, st);
		//st = pt.get<int>("Pool.suffix2");
		//CheckDlgButton(IDC_POOL2, st);
		//st = pt.get<int>("Pool.suffix3");
		//CheckDlgButton(IDC_POOL3, st);
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
			it.ASC = p.get<std::string>("ASC");
			it.Name = p.get<std::string>("Name");
			it.Enabled = p.get<std::string>("Enabled");
			it.temperature = p.get<double>("temperature");
			info.items.push_back(it);
		}
		boost::property_tree::ptree array = parser.get_child(dev_info::STATUS);
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, array)
		{
			boost::property_tree::ptree p = v.second;
			dev_status it;
			it.Code = p.get<std::string>("Code");
			it.Description = p.get<std::string>("Description");
			it.Msg = p.get<std::string>("Msg");
			it.STATUS = p.get<std::string>("STATUS");
			it.When = p.get<double>("When");
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
	//boost::property_tree::ptree pt;
	//boost::property_tree::ini_parser::read_ini("bittool.ini", pt);  // 打开读文件  
	//pt.put<int>("ip", CheckDlgButton(IDC_POOL1, BST_CHECKED));
	//pt.put<int>("ip", CheckDlgButton(IDC_POOL2, BST_CHECKED));
	//pt.put<int>("ip", CheckDlgButton(IDC_POOL3, BST_CHECKED));
	//boost::property_tree::ini_parser::write_ini("bittool.ini", pt);
	return 0;
}
