
// MyBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyBox.h"
#include "MyBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyBoxDlg �Ի���



CMyBoxDlg::CMyBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyBoxDlg::IDD, pParent), _game(20, 9)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyBoxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BSTART, &CMyBoxDlg::OnClickedBStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BPAUSE, &CMyBoxDlg::OnClickedBPause)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyBoxDlg ��Ϣ�������

BOOL CMyBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMyBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyBoxDlg::OnPaint()
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
		//��δ�����б���ͼƬ������
		CPaintDC  dc(this);			// ��Ӧһ��WM_PAINT��Ϣ��ʱ��ʹ��
		CRect  rect;				// �½�һ������
		GetClientRect(&rect);		// ��ÿؼ���С
		CDC  dcMem;
		dcMem.CreateCompatibleDC(&dc); // ����һ����dc���ݵ������Ļ���
		CBitmap  bmpBackground;
		bmpBackground.LoadBitmap(IDB_BMP_BACKGROUND);//�Լ���ͼ��Ӧ��ID  
		BITMAP  bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground); // ��bmpBackground�滻ԭ��ͬ���͵�ֵ
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY); // ���������ͼƬ�������ţ�����ʹ�õ������

		DrawSmallNet();	//������һ���������
		DrawBigNet();	//������Ϸ����
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyBoxDlg::OnClickedBStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (_game._state == GO) {
		KillTimer(1);               //������¿�ʼ����Ҫ�ر�ԭʱ��	
	}

	_game.Start();					//����_game�����Start()��������ʼ��Ϸ
	SetTimer(1, 500, NULL);
}


void CMyBoxDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!_game.Go()) {
		KillTimer(1);
		TCHAR *msg = _T("Game Over!");
		MessageBox(msg);
	}
	Invalidate(true);// �ػ滭��
}

//������Ϸ�����溯��
void CMyBoxDlg::DrawBigNet()
{
	CRect rect;
	//IDC_PIC_MAIN����Ϸ���ڵ�ID��wnd��ָ����Ϸ���ڵ�һ��ָ��
	CWnd *wnd = GetDlgItem(IDC_PIC_MAIN);	//�������Ҳ�����Ӧ�Ŀؼ�ID��������һ��VS����
	CPaintDC dc(wnd);
	wnd->GetClientRect(&rect);				//��ȡָ���ؼ��Ĵ�С

	_game.AddToolToAux(_game._bigNetAux, _game._iLocX, _game._iLocY, _game._tool);
	const COLORREF  colorTableA[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255),
		RGB(255, 255, 0), RGB(160, 32, 240) };
	int *pAuxBigNet = _game._bigNetAux;
	for (int i = 0; i < _game._netHeight; i++)
		for (int j = 0; j < _game._netWidth; j++) {
			//�����Σ����в�����0�ĸ��ӰѾ��α߿򶼻�����
			int iType = pAuxBigNet[i*(_game._netWidth) + j];
			if (iType > 0 && iType <= 5) {
				CClientDC dcc(wnd);		//���ޱ߿�ľ���
				CBrush brush(colorTableA[iType - 1]);
				dcc.FillRect(CRect(j*rect.Width() / _game._netWidth,
					i*rect.Height() / _game._netHeight,
					(j + 1)*rect.Width() / _game._netWidth,
					(i + 1)*rect.Height() / _game._netHeight), &brush);

				//������Ϊ͸���ľ��Σ��ձ�ˢ��
				CBrush *pBrush = CBrush::FromHandle((HBRUSH)
					GetStockObject(NULL_BRUSH));
				CBrush *pOldBrush = dc.SelectObject(pBrush);  //ѡ�뻭ˢ
				dc.Rectangle(
					j*rect.Width() / _game._netWidth,
					i*rect.Height() / _game._netHeight,
					(j + 1)*rect.Width() / _game._netWidth,
					(i + 1)*rect.Height() / _game._netHeight);
				dc.SelectObject(pOldBrush);                  //�ָ�ԭ�Ȼ�ˢ
			}
		}
	wnd->RedrawWindow();			//���»��ƴ���
}

//���Ʊ��ö���˹������溯��
void CMyBoxDlg::DrawSmallNet()
{
	Tool &next_tool = _game._nextTool;
	int type = next_tool.GetType();
	if (type == 0) //����Ч����˹���飬����
		return;
	CRect rect;
	//IDC_PIC_SMALL����ʾ��һ���Ĵ���
	CWnd *wnd = GetDlgItem(IDC_PIC_SMALL);
	CPaintDC dc(wnd);
	wnd->GetClientRect(&rect);
	CClientDC dcc(wnd);
	const COLORREF  colorTableA[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255),
		RGB(255, 255, 0), RGB(160, 32, 240) };
	CBrush brush(colorTableA[type - 1]);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (next_tool.ElementAt(i, j) != 0) {
				dcc.FillRect(CRect(j*rect.Width() / 4,
					i*rect.Height() / 4,
					(j + 1)*rect.Width() / 4,
					(i + 1)*rect.Height() / 4), &brush);

				CBrush *pBrush = CBrush::FromHandle((HBRUSH)
					GetStockObject(NULL_BRUSH));
				CBrush *pOldBrush = dc.SelectObject(pBrush); //ѡ�뻭ˢ
				dc.Rectangle(
					j*rect.Width() / 4,
					i*rect.Height() / 4,
					(j + 1)*rect.Width() / 4,
					(i + 1)*rect.Height() / 4);
				dc.SelectObject(pOldBrush);                  //�ָ�ԭ�Ȼ�ˢ
			}
		}
	wnd->RedrawWindow();
}

void CMyBoxDlg::OnClickedBPause()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	_game.PauseOrContinue();
	//IDΪ1�Ķ�ʱ��ʧЧ
	if (_game._state == PAUSE)
		KillTimer(1);
	//IDΪ1�Ķ�ʱ�����ã�ʱ����Ϊ500����
	if (_game._state == GO)
		SetTimer(1, 500, NULL);
}


BOOL CMyBoxDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN) {
		OnKeyDown((UINT)pMsg->wParam);
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMyBoxDlg::OnKeyDown(UINT nChar) {
	if (_game._state == GO)
		_game.Input(nChar);
	if (nChar == VK_SPACE) {
		OnClickedBPause();
	}
	Invalidate(true);// �ػ滭��
}

void CMyBoxDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (_game._state == GO)
		KillTimer(1);

	CDialogEx::OnClose();
}
