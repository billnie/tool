#pragma once


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
};
