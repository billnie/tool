#pragma once


// CDialogFirmware 对话框

class CDialogFirmware : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFirmware)

public:
	CDialogFirmware(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogFirmware();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FIREWARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
