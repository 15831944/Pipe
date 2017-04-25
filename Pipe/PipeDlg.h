
// PipeDlg.h : ヘッダー ファイル
//

#pragma once

#include "Transmission.h"
#include "Transmitter.h"

// CPipeDlg ダイアログ
class CPipeDlg : public CDialogEx
{
// コンストラクション
public:
	CPipeDlg(CWnd* pParent = NULL);	// 標準コンストラクター
	virtual ~CPipeDlg();

// ダイアログ データ
	enum { IDD = IDD_PIPE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

private:
	void setTransmitter(Transmitter* value);

	Transmitter* transmitter() const{
		return m_transmitter;
	}

	enum Timer : UINT_PTR{
		SEND_DATA = 1
	};

	UINT_PTR m_timerId;

private:
	Transmission m_transmisson;

	Transmitter* m_transmitter;

	enum Trade : int {
		MAIN,
		HEDGE
	};

	static CString PathSpread;
	static CString PathTrade;

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedEnd();
	afx_msg void OnBnClickedBtnStart();
private:
	int m_tradeType;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnDebugSend();
	afx_msg void OnBnClickedBtnTestSend();
	afx_msg void OnBnClickedBtnBegin();
	afx_msg void OnBnClickedBtnBeginService();
private:
	double m_spread;
	int m_trade;
public:
	afx_msg void OnBnClickedBtnGetSpread();
private:
	double m_sendSpread;
	int	   m_sendTrade;
public:
	afx_msg void OnBnClickedBtnSendSpread();
	afx_msg void OnBnClickedBtnSendTrade();
	afx_msg void OnBnClickedBtnGetTrade();
	afx_msg void OnBnClickedBtnStop();
};
