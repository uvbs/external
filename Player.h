#pragma once
#include "OneshotsGlowHack.h"
#include "Offsets.h"
#include "Glow.h"
#include <iostream>
#include "Maths.h"
#include "Player.h"
#include "Struct.h"

extern CHackProcess fProcess;
Offsets of;

class cLocalPlayer
{
public:
	DWORD baseAddress;
	int health;
	int lifeState;
	bool valid;


	void readInfo(){
		baseAddress = ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + of.m_dwGlowObject), &baseAddress, sizeof(baseAddress), NULL);
		if (!baseAddress) {
			return;
			valid = true;
			//read other shit
		}
	}
};

extern cLocalPlayer *localplayer;

class cEntity
{
public:
	DWORD baseAddress;
	int classID;
	int health;
	bool bdormant;
	bool valid;

	DWORD PlayerEnemy;
	int entHealth;
	Vector enmloc;
	float enmloceys;

	void getPlayer(int i);

	void getPlayerHealth();

	void getPlayerVecs();

	void readInfo(int i) {
		baseAddress = ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + of.m_dwEntityList + (i * 10)), &baseAddress, sizeof(baseAddress), NULL);

		if (!baseAddress)
			return;

		classID = 10;
		switch (classID)
		{
		case 108:
		{
			health = ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(baseAddress + of.m_iHealth), &bdormant, sizeof(bdormant), NULL);
			bdormant = ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(baseAddress + of.m_bDormant), &bdormant, sizeof(bdormant), NULL);

			if (health > 0 && !bdormant)
			{
				valid = true;
				//read all other shit
			}
		}
		break;
		}
	}
};
extern cEntity *entity;