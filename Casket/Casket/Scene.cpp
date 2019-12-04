#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
	//NOT USE
	sound = nullptr;
	Initialize();
}

Scene::Scene(Sound* _sound)
{
	sound = _sound;
	Initialize();
}

void Scene::Initialize()
{
	view = LECT_VNONE;
	gotoScene = LECT_SNONE;
	charSelect = LECT_CNONE;
	matchLoaded = false;
}

void Scene::Draw(CDC* pDC, int wx, int wy)
{
	//NOT USE
}

void Scene::TimerCall(TIMER timer)
{
	//NOT USE
}

void Scene::Finish()
{
	//NOT USE
}

void Scene::KeyInput(bool b, KEY key)
{
	//NOT USE
}

void Scene::KeyInput(WPARAM wParam)
{
	//NOT USE
}

void Scene::MouseClick(CPoint point)
{
	//NOT USE
}

bool Scene::ButtonClick(CPoint point, Rect rect)
{
	if (point.x > rect.l && point.x < rect.r
		&& point.y > rect.t && point.y < rect.b) {
		return true;
	}
	else {
		return false;
	}
}

void Scene::DrawRectImage(CDC* pDC, CDC* memDC, int bmpID, Rect rect)
{
	BITMAP bitmap;
	CBitmap cBitmap;
	cBitmap.LoadBitmapW(bmpID);
	cBitmap.GetBitmap(&bitmap);

	memDC->SelectObject(cBitmap);
	DeleteObject(cBitmap);

	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->TransparentBlt(rect.l, rect.t, rect.r - rect.l, rect.b - rect.t, 
		memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(255, 0, 255));
}

void Scene::DrawRectImage(CDC* pDC, CDC* memDC, int bmpID, Rect rect, int r, int g, int b)
{
	BITMAP bitmap;
	CBitmap cBitmap;
	cBitmap.LoadBitmapW(bmpID);
	cBitmap.GetBitmap(&bitmap);

	memDC->SelectObject(cBitmap);
	DeleteObject(cBitmap);

	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->TransparentBlt(rect.l, rect.t, rect.r - rect.l, rect.b - rect.t,
		memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(r, g, b));
}

void Scene::DrawRectText(CDC* pDC, CDC* memDC, CString str, int fontSize, Rect rect)
{
	SetBkMode(*pDC, TRANSPARENT);
	CFont font, * pOldFont;
	pOldFont = (CFont*)memDC->SelectObject(&font);
	font.CreatePointFont(fontSize * 10, L"±¼¸²");
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	pDC->SelectObject(&font);
	pDC->TextOutW((rect.l + rect.r) / 2, (rect.t + rect.b) / 2 + 5, str);
}

char* Scene::GetMyIP()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	char* strIpAddress = "";
	wVersionRequested = MAKEWORD(2, 0);

	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
				strIpAddress = inet_ntoa(*(struct in_addr*) * hostinfo->h_addr_list);
		}
		WSACleanup();
	}

	return strIpAddress;
}
