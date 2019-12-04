#include "pch.h"
#include "Sound.h"

void Sound::Play(int num)
{
	LPCWSTR str = NULL;/* (LPCWSTR)MAKEINTRESOURCE(IDR_BUTTON);
	switch (num) {
	case 1:
		str = (LPCWSTR)MAKEINTRESOURCE(IDR_BUTTON);
		break;
	case 2:
		str = (LPCWSTR)MAKEINTRESOURCE(IDR_COIN);
		break;
	case 3:
		str = (LPCWSTR)MAKEINTRESOURCE(IDR_DIE);
		break;
	case 4:
		str = (LPCWSTR)MAKEINTRESOURCE(IDR_HIT);
		break;
	case 5:
		str = (LPCWSTR)MAKEINTRESOURCE(IDR_JUMP);
		break;
	}*/
	PlaySound(str, AfxGetInstanceHandle(), SND_ASYNC | SND_RESOURCE);
}
