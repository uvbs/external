#pragma once
#include "OneshotsGlowHack.h"
	class Memory
	{
	public:
		int Memory::ReadInt(HANDLE, DWORD);
		float Memory::ReadFloat(HANDLE, DWORD);
		DWORD Memory::ReadDWORD(HANDLE, DWORD);
		int Memory::Read(HANDLE, DWORD);
		void Memory::WriteFloat(HANDLE, DWORD, float);
		void Memory::WriteInt(HANDLE, DWORD, int);
		void Memory::Write(HANDLE, DWORD, int);
	};
