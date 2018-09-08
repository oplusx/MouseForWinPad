
// MouseForWinPadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MouseForWinPad.h"
#include "MouseForWinPadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseForWinPadDlg �Ի���

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


// CMouseForWinPadDlg ��Ϣ�������

BOOL CMouseForWinPadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMouseForWinPadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		//��ȡ���ڱ���
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
