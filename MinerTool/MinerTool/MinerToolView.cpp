
// MinerToolView.cpp : CMinerToolView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CMinerToolView ����/����

CMinerToolView::CMinerToolView()
	: CFormView(IDD_MINERTOOL_FORM)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CMinerToolView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	CRect rs;
	m_tabCtrl.GetClientRect(&rs);
	//�����ӶԻ����ڸ������е�λ��
	rs.top += 40;
	rs.bottom -= 44;
	rs.left += 4;
	rs.right -= 4;

	m_dlgPool.Create(IDD_DLG_POOL, &m_tabCtrl);
	m_dlgPool.MoveWindow(&rs);
	//�ֱ��������غ���ʾ
	m_dlgPool.ShowWindow(true);

	m_dlgVol.Create(IDD_DLG_POOL, &m_tabCtrl);
	m_dlgVol.MoveWindow(&rs);
	//�ֱ��������غ���ʾ
	m_dlgVol.ShowWindow(false);

	int i = 0;
	m_tabCtrl.InsertItem(i++, TEXT(" Ƶ�� & ��ѹ "));
	m_tabCtrl.InsertItem(i++, TEXT(" ������ "));
}


// CMinerToolView ���

#ifdef _DEBUG
void CMinerToolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMinerToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMinerToolDoc* CMinerToolView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMinerToolDoc)));
	return (CMinerToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMinerToolView ��Ϣ�������


void CMinerToolView::OnBnClickedBtnOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMinerToolView::OnBnClickedBtnImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMinerToolView::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
