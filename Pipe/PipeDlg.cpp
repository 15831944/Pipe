
// PipeDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Pipe.h"
#include "PipeDlg.h"
#include "afxdialogex.h"
#include "MainTradeTr.h"
#include "HedgeTradeTr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString CPipeDlg::PathSpread = _T("\\\\.\\pipe\\Spread");
CString CPipeDlg::PathTrade = _T("\\\\.\\pipe\\Trade");

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CPipeDlg ダイアログ




CPipeDlg::CPipeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPipeDlg::IDD, pParent)
	, m_tradeType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_transmitter = nullptr;
	m_timerId = 0;
}

CPipeDlg::~CPipeDlg()
{
	delete m_transmitter;

	if( 0 < m_timerId ){
		KillTimer(m_timerId);
	}
}

void CPipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_CMB_TRADE_TYPE, m_tradeType);
}

void CPipeDlg::setTransmitter(Transmitter* value)
{
	delete m_transmitter;
	m_transmitter = value;
}

BEGIN_MESSAGE_MAP(CPipeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDSTART, &CPipeDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDEND, &CPipeDlg::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_BTN_START, &CPipeDlg::OnBnClickedBtnStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DEBUG_SEND, &CPipeDlg::OnBnClickedBtnDebugSend)
END_MESSAGE_MAP()


// CPipeDlg メッセージ ハンドラー

BOOL CPipeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CPipeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CPipeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CPipeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPipeDlg::OnBnClickedStart()
{
	m_transmisson.execute("\\\\.\\pipe\\TEST");
}

void CPipeDlg::OnBnClickedEnd()
{
	Transmission::endTransmission();
}

void CPipeDlg::OnBnClickedBtnStart()
{
	if( UpdateData(TRUE) ){
		if( m_tradeType == Trade::MAIN ){
			setTransmitter( new MainTradeTr() );
			transmitter()->beginReciveData(PathSpread);
		}
		else if( m_tradeType == Trade::HEDGE ){
			setTransmitter( new HedgeTradeTr() );
			transmitter()->beginReciveData(PathTrade);
		}

		//m_timerId = SetTimer( Timer::SEND_DATA, 1000, NULL);
	}
}

void CPipeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if( nIDEvent == m_timerId ){
		BYTE buff[32];
		static int cnt = 0;

		if( m_tradeType == Trade::MAIN ){
			int trade[] = {1, 2};

			memcpy( buff, &trade[cnt%2], sizeof(int) );
			transmitter()->sendData( PathTrade, buff, sizeof(int) );
		}
		else if( m_tradeType == Trade::HEDGE ){
			int spread[] = {7, 8, 9};

			memcpy( buff, &spread[cnt%3], sizeof(int) );
			transmitter()->sendData( PathSpread, buff, sizeof(int) );
		}

		/*
		else if( m_tradeType == Trade::HEDGE ){
			double spread[] = {0.0002, 0.0003, 0.0004};

			memcpy( buff, &spread[cnt%3], sizeof(double) );
			transmitter()->sendData( PathSpread, buff, sizeof(double) );
		}
		*/
		cnt++;
	}

	//CDialogEx::OnTimer(nIDEvent);
}


void CPipeDlg::OnBnClickedBtnDebugSend()
{
	BYTE buff[32];
	static int cnt = 0;

	if( !UpdateData(TRUE) ){
		return;
	}

	if( m_tradeType == Trade::MAIN ){
		int trade[] = {1, 2};

		memcpy( buff, &trade[cnt%2], sizeof(int) );
		if( transmitter() == nullptr )
			setTransmitter( new MainTradeTr() );

		transmitter()->sendData( PathTrade, buff, sizeof(int) );
	}
	else{
		int spread[] = {7, 8, 9};

		memcpy( buff, &spread[cnt%3], sizeof(int) );
		
		if( transmitter() == nullptr )
			setTransmitter( new HedgeTradeTr() );

		transmitter()->sendData( PathSpread, buff, sizeof(int) );
	}

	cnt++;
}
