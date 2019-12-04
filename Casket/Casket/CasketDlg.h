// CasketDlg.h: 헤더 파일
//
#include "Control.h"
#include "Socket.h"
#include "SocketServer.h"
#include "SocketClient.h"

#pragma once

enum ThreadWorkingType {
	THREAD_STOP = 0,
	THREAD_RUNNING = 1,
	THREAD_PAUSE = 2
};

// CCasketDlg 대화 상자
class CCasketDlg : public CDialogEx
{
// 생성입니다.
public:
	CCasketDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CASKET_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	void DrawImage(CDC* pDC);
	void SetWindowSize(int x, int y);
	CRect GetWindowSize();

private:
	Control control;
	Socket *socket;
	Sound sound;
	bool keyDelay;
	void KeyInput(MSG* pMsg);
	void SocketWait();

//스레드
public:
	static UINT ThreadFunction(LPVOID _mothod);
	bool m_bThreadStart;
	CWinThread *m_pThread;
	ThreadWorkingType m_eThreadWork;
	void StartThread();
	void PauseThread();
	void StopThread();
};
