#pragma once
#include "OneshotsGlowHack.h"
#include "Offsets.h"

class Glow
{
public:

	void Run();

	void ReadInfo();

	void ReadEntity(int Entnum);

	void GlowEntity(int Entnum);

	void Dick(int i);

	void Bhop();

	void RCS();

	void ChangeEntityID();

	void CheckPlayer();

	void ReadEnemy();

	bool glowSwitch = false;

	bool bhopSwitch = false;

	bool rcsSwitch = false;

	bool lockOnPlayer = false;

private:
	DWORD LocalTeam = 0;
	DWORD GlowObject = 0;
	DWORD LocalPlayer = 0;
	DWORD Entity = 0;
	DWORD EntityList = 0;
	DWORD Health = 0;
	DWORD IsDormant = 0;
	DWORD GlowIndex = 0;
	DWORD TeamNum = 0;
	DWORD ClassID = 0;

	DWORD Player;
};

