
// MinerTool.h : MinerTool Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMinerToolApp:
// �йش����ʵ�֣������ MinerTool.cpp
//

class CMinerToolApp : public CWinApp
{
public:
	CMinerToolApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMinerToolApp theApp;
