#include "Memory.h"
#include "OneshotsGlowHack.h"

	int Memory::ReadInt(HANDLE Process, DWORD address) {
		int value;
		ReadProcessMemory(Process, (PBYTE*)(address), &value, sizeof(int), 0);
		return value;
	}

	float Memory::ReadFloat(HANDLE Process, DWORD address) {
		float value;
		ReadProcessMemory(Process, (PBYTE*)(address), &value, sizeof(float), 0);
		return value;
	}

	DWORD Memory::ReadDWORD(HANDLE Process, DWORD address) {
		DWORD value;
		ReadProcessMemory(Process, (PBYTE*)(address), &value, sizeof(DWORD), 0);
		return value;
	}

	int Memory::Read(HANDLE Process, DWORD address) {
		DWORD value;
		ReadProcessMemory(Process, (PBYTE*)(address), &value, sizeof(value), NULL);
		return value;
	}

	void Memory::WriteFloat(HANDLE Process, DWORD address, float value) {
		WriteProcessMemory(Process, (PBYTE*)(address), &value, sizeof(float), 0);
	}

	void Memory::WriteInt(HANDLE Process, DWORD address, int value) {
		WriteProcessMemory(Process, (PBYTE*)(address), &value, sizeof(int), 0);
	}
	void Memory::Write(HANDLE Process, DWORD address, int value) {
		WriteProcessMemory(Process, (PBYTE*)(address), &value, sizeof(value), 0);
	}
