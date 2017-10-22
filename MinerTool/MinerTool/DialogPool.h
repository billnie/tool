#pragma once
#include "afxcmn.h"
#include	<string>
#include	<vector>
#include  <map>
#include	"dev_info.h"
#include "afxwin.h"
using namespace std;
// CDialogPool 对话框

class CDialogPool : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPool)

public:
	CDialogPool(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPool();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_POOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listCtrl;
	std::map<std::string, dev_item> m_devMap;
	virtual BOOL OnInitDialog();
	int AddNote(string resp, string host);
	int updateDevs(string host, string data);

	int addListNote(dev_info &info, string host);
	int saveParam();
	afx_msg void OnBnClickedBtnCheck();
	afx_msg void OnBnClickedBtnSet();
	int newSearch(string host,int min, int max);
	int newSearch(vector<string>&vs);
	CComboBox m_typePool;
	afx_msg void OnBnClickedBtnExport();
	afx_msg LRESULT OnCommonNotify(WPARAM wParam, LPARAM lParam);
};
