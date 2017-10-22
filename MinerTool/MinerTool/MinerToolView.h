
// MinerToolView.h : CMinerToolView ��Ľӿ�
//

#pragma once
#include "afxcmn.h"
#include	"DialogVol.h"
#include	"DialogPool.h"
#include "DialogFirmware.h"
class CMinerToolDoc;
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
	CDialogFirmware m_dlgFirmware;
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
	int asyn_execLua(LPCTSTR function, int start, int end ,string data);
	static int s_execLua(string function, int ,int ,string, CMinerToolView*mk);
	int m_nMin;
	int m_nMax;
	static int updateRequst(int type, string host, string data,void*);
	int GetMinnerInfo(LPCTSTR host);
	int SaveMinnerInfo(LPCTSTR host, LPCTSTR info);
};

#ifndef _DEBUG  // MinerToolView.cpp �еĵ��԰汾
inline CMinerToolDoc* CMinerToolView::GetDocument() const
   { return reinterpret_cast<CMinerToolDoc*>(m_pDocument); }
#endif

