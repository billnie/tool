// DialogPool.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MinerTool.h"
#include "DialogPool.h"
#include "afxdialogex.h"


// CDialogPool �Ի���

IMPLEMENT_DYNAMIC(CDialogPool, CDialogEx)

CDialogPool::CDialogPool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_POOL, pParent)
{

}

CDialogPool::~CDialogPool()
{
}

void CDialogPool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogPool, CDialogEx)
END_MESSAGE_MAP()


// CDialogPool ��Ϣ�������
