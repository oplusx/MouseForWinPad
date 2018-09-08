
// MouseForWinPadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MouseForWinPad.h"
#include "MouseForWinPadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseForWinPadDlg 对话框

HWND CMouseForWinPadDlg::m_hTarget = NULL;

CMouseForWinPadDlg::CMouseForWinPadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMouseForWinPadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CMouseForWinPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMouseForWinPadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMouseForWinPadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDSET, &CMouseForWinPadDlg::OnBnClickedSet)
	ON_BN_CLICKED(IDCANCEL, &CMouseForWinPadDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMouseForWinPadDlg 消息处理程序

BOOL CMouseForWinPadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMouseForWinPadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMouseForWinPadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMouseForWinPadDlg::OnBnClickedOk()
{
	int state = ((CButton *)GetDlgItem(IDC_CHECKSIM))->GetCheck();
	if (state != BST_CHECKED)
	{
		RECT rect;
		this->GetWindowRect(&rect);
		LONG x = rect.left -1;
		LONG y = rect.top -1;
		POINT testPoint;
		testPoint.x = x;
		testPoint.y = y;
		CWnd* testWnd = WindowFromPoint(testPoint);
		if (testWnd != NULL)
		{
			while (testWnd->GetParent() != NULL)
			{
				testWnd = testWnd->GetParent();
			}
			testWnd->ScreenToClient(&testPoint);
			::SetCursorPos(x, y);
			LONG lParam = MAKELPARAM(testPoint.x, testPoint.y);
			::SendMessage(testWnd->m_hWnd, WM_MOUSEMOVE, 0, lParam);
			::SendMessage(testWnd->m_hWnd, WM_LBUTTONDOWN, 0, lParam);
			::PostMessage(testWnd->m_hWnd, WM_LBUTTONUP, 0, lParam);
		}
	}
	else
	{
		if (m_hTarget != NULL)
		{
			LONG lParam = MAKELPARAM(m_lTargetX, m_lTargetY);
			::SetCursorPos(m_lAbsoluteX, m_lAbsoluteY);
			::SendMessage(m_hTarget, WM_MOUSEMOVE, 0, lParam);
			::SendMessage(m_hTarget, WM_LBUTTONDOWN, 0, lParam);
			::PostMessage(m_hTarget, WM_LBUTTONUP, 0, lParam);
		}
	}
}


void CMouseForWinPadDlg::OnBnClickedSet()
{
	RECT rect;
	this->GetWindowRect(&rect);
	LONG x = rect.left - 1;
	LONG y = rect.top - 1;
	POINT testPoint;
	m_lAbsoluteX = x;
	m_lAbsoluteY = y;
	testPoint.x = x;
	testPoint.y = y;
	m_lTargetX = x;
	m_lTargetY = y;
	CWnd* testWnd = WindowFromPoint(testPoint);
	if (testWnd != NULL)
	{
		while (testWnd->GetParent() != NULL)
		{
			testWnd = testWnd->GetParent();
		}
		char buf[256] = "";
		//获取窗口标题
		testWnd->GetWindowText((LPTSTR)buf, sizeof(buf));
		m_hTarget = testWnd->m_hWnd;
		testWnd->GetWindowRect(&rect);
		m_lTargetX = m_lTargetX - rect.left;
		m_lTargetY = m_lTargetY - rect.top;

		char showText[512] = "";
		CString str;
		str.Append((LPTSTR)buf);
		str.AppendFormat(L"X = %d Y = %d ", m_lTargetX, m_lTargetY);
		MessageBox(str);

		
		::SetWindowLong(
			this->m_hWnd,
			GWL_EXSTYLE,
			GetWindowLong(this->m_hWnd, GWL_EXSTYLE) ^ WS_EX_LAYERED);


		// When bAlpha is 0, the window is completely transparent.   
		// When bAlpha is 255, the window is opaque.  
		::SetLayeredWindowAttributes(this->m_hWnd, RGB(0, 0, 0), 50, LWA_ALPHA);
	}
}


void CMouseForWinPadDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
