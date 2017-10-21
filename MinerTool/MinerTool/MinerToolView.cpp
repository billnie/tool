
// MinerToolView.cpp : CMinerToolView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MinerTool.h"
#endif

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include "MinerToolDoc.h"
#include "MinerToolView.h"
#include <process.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>

using namespace boost::xpressive;

using boost::asio::ip::tcp;
using std::string;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int post(const string& host, const string& port, const string& page, const string& data, string& reponse_data)
{
	try
	{
		boost::asio::io_service io_service;
		//如果io_service存在复用的情况
		if (io_service.stopped())
			io_service.reset();

		// 从dns取得域名下的所有ip
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(host, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// 尝试连接到其中的某个ip直到成功 
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "POST " << page << " HTTP/1.0\r\n";
		request_stream << "Host: " << host << ":" << port << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Content-Length: " << data.length() << "\r\n";
		request_stream << "Content-Type: application/x-www-form-urlencoded\r\n";
		request_stream << "Connection: close\r\n\r\n";
		request_stream << data;

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			reponse_data = "Invalid response";
			return -2;
		}
		// 如果服务器返回非200都认为有错,不支持301/302等跳转
		if (status_code != 200)
		{
			reponse_data = "Response returned with status code != 200 ";
			return status_code;
		}

		// 传说中的包头可以读下来了
		std::string header;
		std::vector<string> headers;
		while (std::getline(response_stream, header) && header != "\r")
			headers.push_back(header);

		// 读取所有剩下的数据作为包体
		boost::system::error_code error;
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error))
		{
		}

		//响应有数据
		if (response.size())
		{
			std::istream response_stream(&response);
			std::istreambuf_iterator<char> eos;
			reponse_data = string(std::istreambuf_iterator<char>(response_stream), eos);
		}

		if (error != boost::asio::error::eof)
		{
			reponse_data = error.message();
			return -3;
		}
	}
	catch (std::exception& e)
	{
		reponse_data = e.what();
		return -4;
	}
	return 0;
}

int xmain()
{
	string host = "127.0.0.1";
	string port = "80";
	string page = "/auth/login";
	string data = "user_name=linbc&password=a";
	string reponse_data;

	int ret = post(host, port, page, data, reponse_data);
	if (ret != 0)
		std::cout << "error_code:" << ret << std::endl;

	std::cout << reponse_data << std::endl;

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


void CMinerToolView::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strIp, strStart, strStop, strError;
	int ret =0;
	GetDlgItemText(IDC_EDIT_IP, strIp);
	GetDlgItemText(IDC_EDIT_IPST, strStart);
	GetDlgItemText(IDC_EDIT_IPED, strStop);
	cregex reg_ip = cregex::compile("(25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[.](25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])");
	/* 定义正则表达
	式 */
	if (regex_match((LPCTSTR)strIp, reg_ip)) {
		if (strIp.GetLength() > 3 && strStart.GetLength() > 1 && strStop.GetLength() > 1) {
			int st, ed;
			st = ::atoi((LPCTSTR)strStart);
			ed = ::atoi((LPCTSTR)strStop);
			//
			//合法的网段地址
			if (st > 0 && st < 255 && ed >0 && ed < 255 && ed >= st) {
				xmain();
				ret = 1;
			}
		}
	}
	
	
}


void CMinerToolView::OnBnClickedBtnImport()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMinerToolView::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
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
