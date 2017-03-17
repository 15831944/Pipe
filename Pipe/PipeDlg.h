
// PipeDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include "Transmission.h"
#include "Transmitter.h"

// CPipeDlg �_�C�A���O
class CPipeDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CPipeDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[
	virtual ~CPipeDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PIPE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

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

// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
};
