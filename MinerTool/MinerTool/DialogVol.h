#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include	<string>
#include	<vector>
using namespace std;

// CDialogVol 对话框

class CDialogVol : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogVol)

public:
	CDialogVol(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogVol();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_VOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listCtrl;
	virtual BOOL OnInitDialog();
	CComboBox m_typeMiner;
	int newSearch(string host, int min, int max);
	int newSearch(vector<string>&vs);
};
