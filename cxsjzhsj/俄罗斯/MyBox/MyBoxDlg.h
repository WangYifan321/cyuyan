
// MyBoxDlg.h : ͷ�ļ�
//

#pragma once

#include "Game.h"

// CMyBoxDlg �Ի���
class CMyBoxDlg : public CDialogEx
{
// ����
public:
	CMyBoxDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYBOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private :
	Game	_game;
	void DrawBigNet();					//������Ϸ�����溯��
	void DrawSmallNet();				//����ϴ�¸跽����溯��
	void OnKeyDown(UINT nChar);		//�����������뺯��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedBStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedBPause();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
};
