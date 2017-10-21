#pragma once
#include "afxcmn.h"
#include	<string>
using namespace std;
// CDialogPool �Ի���

class CDialogPool : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPool)

public:
	CDialogPool(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogPool();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_POOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listCtrl;
	virtual BOOL OnInitDialog();
	int AddNote(string resp);
};
