// DialogFirmware.cpp : 实现文件
//

#include "stdafx.h"
#include "MinerTool.h"
#include "DialogFirmware.h"
#include "afxdialogex.h"


// CDialogFirmware 对话框

IMPLEMENT_DYNAMIC(CDialogFirmware, CDialogEx)

CDialogFirmware::CDialogFirmware(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_FIREWARE, pParent)
{

}

CDialogFirmware::~CDialogFirmware()
{
}

void CDialogFirmware::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogFirmware, CDialogEx)
END_MESSAGE_MAP()


// CDialogFirmware 消息处理程序
