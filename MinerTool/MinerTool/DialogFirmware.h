#pragma once


// CDialogFirmware �Ի���

class CDialogFirmware : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFirmware)

public:
	CDialogFirmware(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogFirmware();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FIREWARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
