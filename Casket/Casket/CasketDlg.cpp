
// CasketDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Casket.h"
#include "CasketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCasketDlg::CCasketDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CASKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//게임
	sound = Sound();
	control = Control(&sound);
	socket = new Socket(&control);
	/*StartThread();*/
}

void CCasketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCasketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CCasketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowSize(768, 1024);
	SetTimer(LECT_DRAW, 10, 0);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCasketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC* pDC = GetDC();

		CRect rect;
		GetClientRect(rect);

		//메모리DC와 BITMAP 생성
		CDC memDC;
		CBitmap* pOldBitmap;
		CBitmap bmp;

		//메모리DC 및 BITMAP과 현재 DC의 설정 일치
		memDC.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);
		memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

		//메모리DC에 그리기
		DrawImage(&memDC);

		//메모리DC를 현재 DC에 복사
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		//사용된 메모리DC 및 BITMAP의 삭제
		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();

		CDialogEx::OnPaint();
	}
}

HCURSOR CCasketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CCasketDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) return TRUE;
	}

	KeyInput(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCasketDlg::OnClose()
{
	if (MessageBox(L"정말 종료하시겠습니까?", L"종료", MB_OKCANCEL) == IDCANCEL) {
		return;
	}

	StopThread();
	control.Finish();
	delete socket;
	CDialogEx::OnClose();
}


void CCasketDlg::DrawImage(CDC* pDC)
{
	control.Draw(pDC, GetWindowSize().Width(), GetWindowSize().Height());
}

void CCasketDlg::SetWindowSize(int x, int y)
{
	int sx = GetSystemMetrics(SM_CXSCREEN);
	int sy = GetSystemMetrics(SM_CYSCREEN);
	//printf("asd: %d, %d\n", sx, sy);

	// 크기 정하고
	MoveWindow(0, 0, x, y, TRUE);
	CRect rect = GetWindowSize();

	// 중앙으로
	CPoint pos;
	pos.x = sx / 2 - rect.Width() / 2;
	pos.y = (sy / 2 - rect.Height() / 2) - 35;
	SetWindowPos(NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE);
}

CRect CCasketDlg::GetWindowSize()
{
	CRect rect;
	GetClientRect(&rect);
	return rect;
}


void CCasketDlg::KeyInput(MSG* pMsg)
{
	if (!GetAsyncKeyState(VK_UP) || !GetAsyncKeyState(VK_DOWN) || !GetAsyncKeyState(VK_LEFT) || !GetAsyncKeyState(VK_RIGHT) || !GetAsyncKeyState(VK_SPACE)) {
		if (keyDelay) {
			return;
		}
		control.KeyInput(pMsg->wParam);
	}
	else { 
		keyDelay = true;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) control.KeyInput(false, LECT_UP);
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) control.KeyInput(false, LECT_DOWN);
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) control.KeyInput(false, LECT_LEFT);
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) control.KeyInput(false, LECT_RIGHT);
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) control.KeyInput(false, LECT_SPACE);
}

void CCasketDlg::SocketWait()
{
	switch (control.socket) {
	case LECT_SERVER:
		socket->Close();
		if (socket != nullptr) {
			delete socket;
		}
		socket = new SocketServer(&control);
		control.socket = LECT_WAIT;
		break;
	case LECT_CLIENT:
		socket->Close();
		if (socket != nullptr) {
			delete socket;
		}
		socket = new SocketClient(&control);
		control.socket = LECT_WAIT;
		break;
	case LECT_SOCKETBREAK:
		socket->Close();
		if (socket != nullptr) {
			delete socket;
		}
		socket = new Socket(&control);
		control.socket = LECT_WAIT;
		break;
	case LECT_PLAYING:
		socket->Commun();
		break;
	}

	if (socket->error) {
		control.game->socketError = true;
	}
}

UINT CCasketDlg::ThreadFunction(LPVOID method)
{
	CCasketDlg* fir = (CCasketDlg*)method;

	while (1)
	{
		CCasketDlg* pDlg = (CCasketDlg*)AfxGetApp()->m_pMainWnd;
		pDlg->SocketWait();

		Sleep(10);
	}
	return 0;
}

void CCasketDlg::StartThread()
{
	if (m_pThread == NULL) {
		m_pThread = AfxBeginThread(ThreadFunction, this);
		if (m_pThread == NULL) {
			printf("Error");
		}
		m_pThread->m_bAutoDelete = FALSE;
		m_eThreadWork = THREAD_RUNNING;
	}
	else {
		if (m_eThreadWork == THREAD_PAUSE) {
			m_pThread->ResumeThread();
			m_eThreadWork = THREAD_RUNNING;
		}
	}
}

void CCasketDlg::PauseThread()
{
	if (m_pThread == NULL) {
		printf("Error");
	}
	else {
		m_pThread->SuspendThread();
		m_eThreadWork = THREAD_PAUSE;
	}
}

void CCasketDlg::StopThread()
{
	if (m_pThread == NULL) {
		printf("Error");
	}
	else {
		m_pThread->SuspendThread();
		DWORD dwResult;
		::GetExitCodeThread(m_pThread->m_hThread, &dwResult);
		delete m_pThread;
		m_pThread = NULL;
		m_eThreadWork = THREAD_STOP;
	}
}

void CCasketDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) {
	case LECT_MOVEMENT:
		control.TimerCall(LECT_MOVEMENT);
		break;
	case LECT_STAGE:
		control.TimerCall(LECT_STAGE);
		break;
	case LECT_DRAW:
		InvalidateRect(NULL, FALSE);
		SocketWait();
		keyDelay = false;
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CCasketDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	control.MouseClick(point);

	CDialogEx::OnLButtonDown(nFlags, point);
}
