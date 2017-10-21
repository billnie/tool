// DialogVol.cpp : 实现文件
//

#include "stdafx.h"
#include "MinerTool.h"
#include "DialogVol.h"
#include "afxdialogex.h"


// CDialogVol 对话框

IMPLEMENT_DYNAMIC(CDialogVol, CDialogEx)

CDialogVol::CDialogVol(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_VOL, pParent)
{

}

CDialogVol::~CDialogVol()
{
}

void CDialogVol::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogVol, CDialogEx)
END_MESSAGE_MAP()


// CDialogVol 消息处理程序
