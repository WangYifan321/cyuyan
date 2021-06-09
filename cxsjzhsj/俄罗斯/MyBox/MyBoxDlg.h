
// MyBoxDlg.h : 头文件
//

#pragma once

#include "Game.h"

// CMyBoxDlg 对话框
class CMyBoxDlg : public CDialogEx
{
// 构造
public:
	CMyBoxDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYBOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private :
	Game	_game;
	void DrawBigNet();					//绘制游戏主界面函数
	void DrawSmallNet();				//绘制洗衣歌方块界面函数
	void OnKeyDown(UINT nChar);		//监听键盘输入函数


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
