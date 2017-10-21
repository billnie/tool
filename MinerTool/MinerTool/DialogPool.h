#pragma once


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
};
