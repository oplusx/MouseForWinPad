
// MouseForWinPad.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMouseForWinPadApp: 
// �йش����ʵ�֣������ MouseForWinPad.cpp
//

class CMouseForWinPadApp : public CWinApp
{
public:
	CMouseForWinPadApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMouseForWinPadApp theApp;