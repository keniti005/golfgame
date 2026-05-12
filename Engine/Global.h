#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

namespace
{
	float deltaTime()
	{
		static DWORD pt = timeGetTime();
		DWORD ct = timeGetTime();
		float dt = (ct - pt) / 1000.0f;
		pt = ct;
		return dt;
	};
}