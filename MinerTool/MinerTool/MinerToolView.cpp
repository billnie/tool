
// MinerToolView.cpp : CMinerToolView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MinerTool.h"
#endif
#include <io.h>  
#include <fcntl.h> 

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include "MinerToolDoc.h"
#include "MinerToolView.h"
#include <boost/bind.hpp>  
#include <boost/function.hpp>  
#include <boost/thread/thread.hpp>  
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>

#include <boost/property_tree/ptree.hpp>    
#include <boost/property_tree/ini_parser.hpp>  

#include "dev_pool.h"
#include	"stlstr.h"
#include	"csv.h"
#include "bitminner.h"
using namespace str;
using namespace boost::xpressive;
using namespace std;

using std::string;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void InitConsoleWindow(void)
{
	int hCrt;
	FILE *hf;
	AllocConsole();
	hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	hf = _fdopen(hCrt, "w");
	*stdout = *hf;
	setvbuf(stdout, NULL, _IONBF, 0);
}
int read_file(vector<string> &data, string szFile)
{
	data.clear();
	//
	std::ifstream file_(szFile.c_str(), std::ios::in);
	//std::wifstream file_;
	//file_.open(szFile.c_str(), std::ios::in);
	if (!file_) return -1;
	const int bufsize = 512;
	char strbuf[bufsize];
	//
	while (!file_.eof())
	{
		file_.getline(strbuf, bufsize);
		string sentence = strbuf;
		if (sentence.empty())
		{
			continue;
		}
		data.push_back(sentence);
	}
	file_.close();
	//
	if (data.size() < 1)
	{
		return -1;
	}
	return 0;
}

// CMinerToolView

IMPLEMENT_DYNCREATE(CMinerToolView, CFormView)

BEGIN_MESSAGE_MAP(CMinerToolView, CFormView)

	ON_BN_CLICKED(IDC_BTN_OK, &CMinerToolView::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CMinerToolView::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_DEL, &CMinerToolView::OnBnClickedBtnDel)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMinerToolView::OnSelchangeTab1)
END_MESSAGE_MAP()

// CMinerToolView 构造/析构

CMinerToolView::CMinerToolView()
	: CFormView(IDD_MINERTOOL_FORM)
	, m_nMin(0)
	, m_nMax(0)
{
	// TODO: 在此处添加构造代码
	m_cur_mode_sel = NULL;
}

CMinerToolView::~CMinerToolView()
{
}

void CMinerToolView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	DDX_Text(pDX, IDC_EDIT_IPED, m_nMin);
	DDV_MinMaxInt(pDX, m_nMin, 1, 254);
	DDX_Text(pDX, IDC_EDIT_IPST, m_nMax);
	DDV_MinMaxInt(pDX, m_nMax, 1, 254);
}

BOOL CMinerToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bret =  CFormView::PreCreateWindow(cs);
	
	return bret;
}

void CMinerToolView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	InitConsoleWindow();
	
	str::initlog("log");

//	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";

	CRect rs;
	m_tabCtrl.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置
	rs.top += 40;
	rs.bottom -= 44;
	rs.left += 4;
	rs.right -= 4;

	m_dlgPool.Create(IDD_DLG_POOL, &m_tabCtrl);
	m_dlgPool.MoveWindow(&rs);
	//分别设置隐藏和显示
	m_dlgPool.ShowWindow(false);

	m_dlgVol.Create(IDD_DLG_VOL, &m_tabCtrl);
	m_dlgVol.MoveWindow(&rs);
	//分别设置隐藏和显示
	m_dlgVol.ShowWindow(true);

	m_dlgFirmware.Create(IDD_DLG_FIREWARE, &m_tabCtrl);
	m_dlgFirmware.MoveWindow(&rs);
	//分别设置隐藏和显示
	m_dlgFirmware.ShowWindow(false);

	int i = 0;
	m_tabCtrl.InsertItem(i++, TEXT(" 频率 & 电压 "));
	m_tabCtrl.InsertItem(i++, TEXT(" 矿池相关 "));
	m_tabCtrl.InsertItem(i++, TEXT(" 固件升级 "));
	i = 0;
	m_pPage[i++] = &m_dlgVol;
	m_pPage[i++] = &m_dlgPool;
	m_pPage[i++] = &m_dlgFirmware;

	string sip;
	//读取参数
	boost::property_tree::ptree pt;
	try
	{
//		boost::property_tree::ini_parser::read_ini("./config.ini", pt);
		boost::property_tree::ini_parser::read_ini("./bittool.ini", pt);  // 打开读文件  
																		//boost::property_tree::ini_parser::write_ini("E:\\Projects\\boost_property_tree\\Overlay.ini", pt); // 写到文件    
		sip = pt.get<std::string>("ip");
		SetDlgItemText(IDC_EDIT_IP, sip.c_str());
		sip = pt.get<std::string>("startip");
		SetDlgItemText(IDC_EDIT_IPST, sip.c_str());
		sip = pt.get<std::string>("endip");
		SetDlgItemText(IDC_EDIT_IPED, sip.c_str());
	}
	catch (std::exception e)
	{
		cout << e.what();
		boost::property_tree::ini_parser::write_ini("bittool.ini", pt);
	}
}


// CMinerToolView 诊断

#ifdef _DEBUG
void CMinerToolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMinerToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMinerToolDoc* CMinerToolView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMinerToolDoc)));
	return (CMinerToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMinerToolView 消息处理程序

int CMinerToolView::asyn_execLua(LPCTSTR function, int start, int end, string data) {
	int ret = -1;
	string s = function;
	boost::function<int(LPCTSTR function, int star, int end, string data, CMinerToolView*)> func;
	func = &CMinerToolView::s_execLua;
	boost::thread downloadThread = boost::thread(boost::bind(func, function, start, end, data,this));
	return ret;
}
int CMinerToolView::s_execLua(LPCTSTR shost,int start,int end,string data, CMinerToolView*mk)
{
	string  host;
	host = shost;
	boost::function<void(int,string, string,void*)> f = &CMinerToolView::updateRequst;
	boost::shared_ptr<bitminner::AnsyncMinerRequst> mq(new bitminner::AnsyncMinerRequst);
	mq->obj = (void*)mk;
	mq->initdevslist(host,start,end, f);
	return 0;
}
void CMinerToolView::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strIp, strStart, strStop, strError;
	string resp, host;
	int ret =0;
	GetDlgItemText(IDC_EDIT_IP, strIp);
	GetDlgItemText(IDC_EDIT_IPST, strStart);
	GetDlgItemText(IDC_EDIT_IPED, strStop);

	//resp = bitminner::xdevs(host);
	//m_dlgPool.AddNote(resp, host);
//	return;
	cregex reg_ip = cregex::compile("(25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
	/* 定义正则表达
	式 */
	if (regex_match((LPCTSTR)strIp, reg_ip)) {
		if (strIp.GetLength() > 3 && strStart.GetLength() > 1 && strStop.GetLength() > 1) {
			int st, ed;
			st = ::atoi((LPCTSTR)strStart);
			ed = ::atoi((LPCTSTR)strStop);
			//合法的网段地址
			if (st > 0 && st < 255 && ed >0 && ed < 255 && ed >= st) {
				ret = 1;
				m_dlgPool.AddNote(resp, host);
				boost::property_tree::ptree pt;
				boost::property_tree::ini_parser::read_ini("bittool.ini", pt);  // 打开读文件  
				pt.put<std::string>("ip", (LPCTSTR)strIp);
				pt.put<std::string>("startip", (LPCTSTR)strStart);
				pt.put<std::string>("endip", (LPCTSTR)strStop);
				boost::property_tree::ini_parser::write_ini("bittool.ini", pt);
				m_dlgPool.newSearch((LPCTSTR)strIp, st, ed);
				m_dlgVol.newSearch((LPCTSTR)strIp, st, ed);
				asyn_execLua((LPCTSTR)strIp, st, ed,"");
			}
		}
	}
}


void CMinerToolView::OnBnClickedBtnImport()
{
	CFileDialog   dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT,
		_T("txt   Files   (*.txt)|*.txt|All   Files   (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		CString str;
		vector<string> vs;
		str = dlg.GetPathName();
		//io::CSVReader<2> in((LPCTSTR)str);
		//in.read_header(io::ignore_extra_column, "No", "ip");
		//std::string vendor, ip; int size; double speed;
		//while (in.read_row(vendor, ip)) {
		//	// do stuff with the data
		//}
		read_file(vs, (LPCTSTR)str);
		if (vs.size() > 0) {
			m_dlgPool.newSearch(vs);
			m_dlgVol.newSearch(vs);
		}
	}
}


void CMinerToolView::OnBnClickedBtnDel()
{
	dev_pools dps;
	dev_pool dp;
	string s;
	dp.url = "stratum_ltc.bw1.com:8888";
	dp.username = "jjyykk.L22";
	dp.password = "123123";
	dp.bPrefix = true;
	dps.pools.push_back(dp);

	dp.url = "stratum_ltc.bw1.com:8888";
	dp.username = "jjyykk.L23";
	dp.password = "123123";
	dp.bPrefix = true;
	dps.pools.push_back(dp);

	dp.url = "stratum_ltc.bw1.com:8888";
	dp.username = "jjyykk.L24";
	dp.password = "123123";
	dp.bPrefix = true;
	dps.pools.push_back(dp);

	dps.Frequency = 648;
	s = dps.urlcodestring();

	DT(s.c_str());
	int ret;
	bitminner::xpoolset("192.168.3.16", s.c_str(),ret);
	bitminner::xgetminner("192.168.3.16", ret);
	bitminner::xnet("192.168.3.16", ret);
}


void CMinerToolView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	CSize sizeTotal;
	sizeTotal.cx = cx;
	sizeTotal.cy = cy;

	if (m_tabCtrl.GetSafeHwnd() != NULL && m_dlgVol.GetSafeHwnd()!=NULL) {
		CRect rect;
		GetClientRect(rect);
		rect.top += 60;
		rect.bottom -= 60;
		m_tabCtrl.MoveWindow(rect);
		m_tabCtrl.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.right = cx - rect.left;
		rect.bottom = cy - rect.left;
		m_tabCtrl.MoveWindow(rect);
		rect.top = 20;

		m_dlgPool.MoveWindow(rect);
		m_dlgVol.MoveWindow(rect);
		m_dlgFirmware.MoveWindow(rect);
	}
}


void CMinerToolView::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int cur_sel = m_tabCtrl.GetCurSel();

	if (m_cur_mode_sel != cur_sel) {
		m_pPage[m_cur_mode_sel]->ShowWindow(SW_HIDE);
		m_pPage[cur_sel]->ShowWindow(SW_SHOW);
		m_cur_mode_sel = cur_sel;
	}
	*pResult = 0;
}


int CMinerToolView::updateRequst(int type, string host, string data, void*obj)
{
	CMinerToolView *mv;
	mv = (CMinerToolView*)obj;

	return 0;
}
