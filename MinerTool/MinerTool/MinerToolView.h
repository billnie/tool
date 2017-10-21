
// MinerToolView.h : CMinerToolView ��Ľӿ�
//

#pragma once
#include "afxcmn.h"
#include	"DialogVol.h"
#include	"DialogPool.h"

class CMinerToolView : public CFormView
{
protected: // �������л�����
	CMinerToolView();
	DECLARE_DYNCREATE(CMinerToolView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MINERTOOL_FORM };
#endif
	CDialogPool m_dlgPool;
	CDialogVol	m_dlgVol;
	CDialog *m_pPage[3];
	int m_cur_mode_sel;
// ����
public:
	CMinerToolDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMinerToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnDel();
	CTabCtrl m_tabCtrl;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // MinerToolView.cpp �еĵ��԰汾
inline CMinerToolDoc* CMinerToolView::GetDocument() const
   { return reinterpret_cast<CMinerToolDoc*>(m_pDocument); }
#endif

