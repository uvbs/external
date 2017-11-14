#pragma once
#include "Glow.h"
#include <iostream>
#include "Maths.h"
#include "Player.h"
#include "Memory.h"

extern CHackProcess fProcess; // Same object thats in OneshotsGlowHack.cpp but we access it in here.
Offsets O; // Accessing the Offsets tru this object.
Memory mem;

using namespace std;

cLocalPlayer *localplayer = new cLocalPlayer;
cEntity *entity = new cEntity[64];

Vector ourloc;
Vector enmloc;

Vector Angles;
Vector AimAngles;
Vector Angle;

Vector AimPunch;

Vector OurViewAngles;

Vector oldvAngle;

float ourloceys;
float enmloceys;

float enmHealth;
int entHealth;
float aimFov = 2.0f;

int entityID = 0x00;

int Entitys[64];
int Enemys[5];

Vector CalcAngle(Vector src, Vector dir){
	Vector Angle;
	Vector NewAngle;

	Angle.x = dir.x - src.x;
	Angle.y = dir.y - src.y;
	Angle.z = dir.z - src.z;

	float Magnitude = sqrt(Angle.x * Angle.x + Angle.y * Angle.y + Angle.z * Angle.z);

	NewAngle.x = atan2(Angle.y, Angle.x) * 180 / 3.14;
	NewAngle.y = atan2(Angle.z, Magnitude) * 180 / 3.14;
	NewAngle.z = 0;

	return NewAngle;
}

void Aimbot() {
	int enmemyHealth = 0;

	for (int i = 0; i < 64; i++) {//loop 64 entitys
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + O.m_dwEntityList + (i*0x10)), &Entitys[i], sizeof(Entitys[i]), NULL);
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(Entitys[i] + O.m_iHealth), &enmemyHealth, sizeof(enmemyHealth), NULL);
		//Entitys[i] = mem.Read(fProcess.__HandleProcess, fProcess.__dwordClient + O.m_dwEntityList + (i * 0x10));//readmem of entity
		//enmemyHealth = mem.Read(fProcess.__HandleProcess, Entitys[i] + O.m_iHealth); //readmem health of entity
			if (enmemyHealth > 0) { //check healthstate
				Enemys[i] = Entitys[i]; //store into 5 enemys
			}
			else {
				Enemys[i] = 0;
			}
	}
	//std::cout << "Entity 1 -- " << Enemys[0] << std::endl;
	//std::cout << "Entity 2 -- " << Enemys[1] << std::endl;
	//std::cout << "Entity 3 -- " << Enemys[2] << std::endl;
	//std::cout << "Entity 4 -- " << Enemys[3] << std::endl;
	//std::cout << "Entity 5 -- " << Enemys[4] << std::endl;
}

void Glow::ChangeEntityID() {
	entityID += 0x10;
	if (entityID == 0x640) {
		entityID = 0x00;
	}
	//std::cout << entityID << std::endl;
}

float CalcFov() {
	Vector AimAngle;
	float newFov;

	AimAngle.x -= AimPunch.x;
	AimAngle.y -= AimPunch.y;

	newFov = Maths::GetFov(OurViewAngles, AimAngle);
	return newFov;
};

void Glow::CheckPlayer() {
	//if (enmHealth > 0 && fovToEnm < aimFov) {
		//store that entity to aimbot
		//O.Entity = O.Enemy;
	//}
	//else {
	//	O.Enemy = 0;
	//}
}

void Glow::ReadEnemy() {
	while (true) {
		localplayer->readInfo();
	}
	for (int i = 0; i < 64; i++) {
		entity[i].readInfo(i);
		exit;
	}
}

void Glow::ReadInfo()
{
	//entity idchecker
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + O.m_dwGlowObject), &GlowObject, sizeof(int), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + O.m_dwLocalPlayer), &LocalPlayer, sizeof(int), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + O.m_dwGlowObject), &GlowObject, sizeof(int), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(LocalPlayer + O.m_iTeamNum), &LocalTeam, sizeof(int), NULL);
	//aimbot
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + O.m_dwLocalPlayer), &O.PlayerBase, sizeof(DWORD), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.PlayerBase + O.m_vecOrigin), &ourloc, sizeof(ourloc), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.PlayerBase + O.m_vecViewOffset), &ourloceys, sizeof(ourloceys), NULL);
	//entity
	//ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + O.m_dwEntityList + 0x50), &O.Entity, sizeof(O.Entity), NULL);
	//ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.Entity + O.m_vecOrigin), &enmloc, sizeof(enmloc), NULL);
	//ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.Entity + O.m_vecViewOffset), &enmloceys, sizeof(enmloceys), NULL);
	//ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.Entity + O.m_iHealth), &enmHealth, sizeof(enmHealth), NULL);
	//engine
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordEngine + O.dwClientState), &O.ClientState, sizeof(O.ClientState), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.ClientState + O.dwClientState_ViewAngles), &Angles, sizeof(Angles), NULL);

	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.ClientState + O.dwClientState_ViewAngles), &OurViewAngles, sizeof(OurViewAngles), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.ClientState + O.m_aimPunchAngle), &AimPunch, sizeof(AimPunch), NULL); // maybe edit clientstate to lplayer
}
void Glow::ReadEntity(int Entnum)
{
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObject + 0x38 * Entnum), &Entity, sizeof(int), NULL);
	DWORD gBuffer = NULL;
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(Entity + 0x8), &gBuffer, sizeof(int), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(gBuffer + 0x8), &gBuffer, sizeof(int), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(gBuffer + 0x1), &gBuffer, sizeof(int), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(gBuffer + 0x14), &ClassID, sizeof(int), NULL);
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(Entity + O.m_iTeamNum), &TeamNum, sizeof(int), NULL);
}
void Glow::GlowEntity(int Entnum)
{
	WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(GlowObject + 0x38 * Entnum + 0x4), &O.EntGlow, sizeof(O.EntGlow), NULL);
}

void changevAngle(Vector angle) {
	if (angle.x >= -89 && angle.x <= 89 && angle.y >= -180 && angle.y <= 180)
	{
		WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordEngine + O.dwClientState_ViewAngles), &angle, sizeof(angle), NULL);

	}
}

Vector nAngle(Vector angle)
{
	if (angle.x > 89.0f && angle.x <= 180.0f)
	{
		angle.x = 89.0f;
	}
	while (angle.x > 180.f)
	{
		angle.x -= 360.f;
	}
	while (angle.x < -89.0f)
	{
		angle.x = -89.0f;
	}
	while (angle.y > 180.f)
	{
		angle.y -= 360.f;
	}
	while (angle.y < -180.f)
	{
		angle.y += 360.f;
	}

	angle.z = 0;
	return angle;
}

void Glow::RCS() {
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		int shotsFired;

		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.PlayerBase + O.m_iShotsFired), &shotsFired, sizeof(shotsFired), NULL);


		if (shotsFired > 1)
		{
			Vector vAngle;
			Vector pAngle;

			Vector Angle;

			ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordEngine + O.dwClientState_ViewAngles), &vAngle, sizeof(vAngle), NULL);
			ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.PlayerBase + O.m_iShotsFired), &pAngle, sizeof(pAngle), NULL);


			vAngle.x += oldvAngle.x;
			vAngle.y += oldvAngle.y;

			Angle.x = vAngle.x - pAngle.x * 1.2;
			Angle.y = vAngle.y - pAngle.y * 1;

			nAngle(Angle);

			changevAngle(Angle);

			oldvAngle.x = pAngle.x * 1.2;
			oldvAngle.y = pAngle.y * 1;

			Sleep(30);
		}
		else
		{
			oldvAngle.x = 0;
			oldvAngle.y = 0;
		}
	}
	else
	{
		oldvAngle.x = 0;
		oldvAngle.y = 0;
	}
}

void Glow::Bhop() {

	if (bhopSwitch) {

		if (!O.PlayerBase) return;

		if (GetAsyncKeyState(VK_SPACE))
		{
			int flags;

			int value = 6;

			ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.PlayerBase + O.m_fFlags), &flags, sizeof(flags), NULL);

			if (flags & 1 << 0)
			{
				WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + O.dwForceJump), &value, sizeof(value), NULL);
			}
		}
	}
}

void Glow::Run()
{
	while (true) {
		Aimbot();
		ReadInfo();
			if (GetAsyncKeyState(VK_LBUTTON) && enmHealth > 0) {
				AimAngles = CalcAngle(ourloc, enmloc);
				//WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.ClientState + O.dwClientState_ViewAngles + 0x4), &AimAngles.x, sizeof(float), NULL);
				//WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.ClientState + O.dwClientState_ViewAngles), &AimAngles.y, sizeof(float), NULL);
		}
			for (int i = 0; i < 64; i++) {
				entity->getPlayer(i);
				entity->getPlayerHealth();
				entity->getPlayerVecs();
				if (entity->entHealth > 0) {
					AimAngles = CalcAngle(ourloc, entity->enmloc);
					WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.ClientState + O.dwClientState_ViewAngles + 0x4), &AimAngles.x, sizeof(float), NULL);
					WriteProcessMemory(fProcess.__HandleProcess, (PBYTE*)(O.ClientState + O.dwClientState_ViewAngles), &AimAngles.y, sizeof(float), NULL);
				}
			}

		
			for (int i = 0; i < 200; i++)
			{

				ReadEntity(i);
				Dick(i);
			}
	}

}		

void Glow::Dick(int i)
{

	switch (i) // to do make this 
	{
	default:
		break;
	}

	if (GetAsyncKeyState(VK_F1)) {
		glowSwitch = !glowSwitch;
	}
	if (GetAsyncKeyState(VK_F2)) {
		bhopSwitch = !bhopSwitch;
	}
	if (bhopSwitch) {
		Bhop();
	}
	if (GetAsyncKeyState(VK_F3)) {
		rcsSwitch = !rcsSwitch;
	}
	if (rcsSwitch) {
		RCS();
	}
	if(glowSwitch){
		RCS();
		if (ClassID == 35)// base granade
		{
			if (LocalTeam != TeamNum)
			{
				O.EntGlow.red = 1;
				O.EntGlow.green = 0;
				O.EntGlow.blue = 0;
				O.EntGlow.alpha = 1;
				GlowEntity(i);
				return;
			}
			else
			{
				O.EntGlow.red = 0;
				O.EntGlow.green = 1;
				O.EntGlow.blue = 0;
				O.EntGlow.alpha = 1;
				GlowEntity(i);
				return;
			}

		}

		if (ClassID == 9)// base granade
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 9)// base granade
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 1) // ak47
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0.3;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 107)// plantad c4
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 29)//c4
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 233) // scar20
		{
			O.EntGlow.red = 0.3;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 204)// aug
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0.1;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 205)// awp
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 207)// ppbizon
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 2011)// elites
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 212)// famas
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 213)// fiveseven
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 214)//G3SG1
		{
			O.EntGlow.red = 0.5;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 216)// gallil
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 217) // glock
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 218)// p2000
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 219)//M249
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 221)//M4A1
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 222)//mac10
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 223)//mag7
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 225)//mp7
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 226)//mp9
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 227)//negev
		{
			O.EntGlow.red = 0.3;
			O.EntGlow.green = 0.3;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 228)//nova
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 230)//p250
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 231)//p90
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 232)//sawdoff
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 238)//scout
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 237)//sg556
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 237)//tazer
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 238)//tec9
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 240)//ump
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 242)//XM1014
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 0.6;
			GlowEntity(i);
		}
		if (ClassID == 39)//desert eagle
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 107)// plantad c4
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 66)// flashbang
		{
			O.EntGlow.red = 0;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 84)// he
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 0;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 96)// molotov ground
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 97)// molotov air
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i);
		}
		if (ClassID == 87)// insindiary
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 0;
			O.EntGlow.alpha = 1;
			GlowEntity(i); return;
		}
		if (ClassID == 40)// decoy
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i); return;
		}
		if (ClassID == 41)// decoy air
		{
			O.EntGlow.red = 1;
			O.EntGlow.green = 1;
			O.EntGlow.blue = 1;
			O.EntGlow.alpha = 1;
			GlowEntity(i); return;
		}
	}
}