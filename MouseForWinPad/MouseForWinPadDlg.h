
// MouseForWinPadDlg.h : ͷ�ļ�
//

#pragma once


// CMouseForWinPadDlg �Ի���
class CMouseForWinPadDlg : public CDialogEx
{
// ����
public:
	CMouseForWinPadDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_MOUSEFORWINPAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
