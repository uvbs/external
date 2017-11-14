#pragma once
#include "OneshotsGlowHack.h"

class Offsets // Offset class to store all of our Offsets
{
public:

	struct Glow
	{
		float red = 1; 
		float green = 0; 
		float blue = 0;
		float alpha = 1.0;
		byte dick[8]; // just padding
		float buffer3 = 1;
		int buffer4 = 0;
		bool on = true;
	}EntGlow;

	struct Chams {
		float red = 1;
		float green = 0;
		float blue = 0;
		float alpha = 1.0;
	}EntChams;

	//glow
	DWORD m_dwLocalPlayer = 0xAAFD7C;
	DWORD m_iHealth = 0x000000FC;
	DWORD m_bDormant = 0x000000E9;
	DWORD m_iTeamNum = 0x000000F0;
	DWORD m_dwGlowObject = 0x4FA9D60;
	DWORD m_dwEntityList = 0x4A8D0EC;
	DWORD m_iGlowIndex = 0xA310;
	//bhop
	DWORD m_fFlags = 0x100;
	DWORD dwForceJump = 0x4F2419C;
	//rcs
	DWORD m_iShotsFired = 0xA2B0;
	DWORD m_aimPunchAngle = 0x301C;
	//aimbot
	DWORD dwClientState = 0x5A783C;
	DWORD ClientState;
	DWORD dwClientState_ViewAngles = 0x4D10;
	DWORD m_vecOrigin = 0x134;
	DWORD m_vecViewOffset = 0x104;
	DWORD EntityList;
	DWORD Entity;
	DWORD PlayerBase;
	DWORD Enemy;
	DWORD dwClientState_GetLocalPlayer = 0x180;
};

