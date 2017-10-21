
// MinerToolView.cpp : CMinerToolView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MinerTool.h"
#endif

#include "MinerToolDoc.h"
#include "MinerToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMinerToolView

IMPLEMENT_DYNCREATE(CMinerToolView, CFormView)

BEGIN_MESSAGE_MAP(CMinerToolView, CFormView)

	ON_BN_CLICKED(IDC_BTN_OK, &CMinerToolView::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CMinerToolView::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_DEL, &CMinerToolView::OnBnClickedBtnDel)
END_MESSAGE_MAP()

// CMinerToolView 构造/析构

CMinerToolView::CMinerToolView()
	: CFormView(IDD_MINERTOOL_FORM)
{
	// TODO: 在此处添加构造代码

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

	return CFormView::PreCreateWindow(cs);
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
	m_dlgPool.ShowWindow(true);

	m_dlgVol.Create(IDD_DLG_POOL, &m_tabCtrl);
	m_dlgVol.MoveWindow(&rs);
	//分别设置隐藏和显示
	m_dlgVol.ShowWindow(false);

	int i = 0;
	m_tabCtrl.InsertItem(i++, TEXT(" 频率 & 电压 "));
	m_tabCtrl.InsertItem(i++, TEXT(" 矿池相关 "));
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
}


void CMinerToolView::OnBnClickedBtnImport()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMinerToolView::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
}
