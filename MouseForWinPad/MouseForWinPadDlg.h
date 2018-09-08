
// MouseForWinPadDlg.h : 头文件
//

#pragma once


// CMouseForWinPadDlg 对话框
class CMouseForWinPadDlg : public CDialogEx
{
// 构造
public:
	CMouseForWinPadDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_MOUSEFORWINPAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSet();
	afx_msg void OnBnClickedCancel();

	LONG m_lTargetX;
	LONG m_lTargetY;
	LONG m_lAbsoluteX;
	LONG m_lAbsoluteY;
	static HWND m_hTarget;
};
