#include "Glow.h"
#include "OneshotsGlowHack.h"
#include "Player.h"

Offsets offset;
cEntity *entity = new cEntity[64];

	void cEntity::getPlayer(int i)
	{
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + offset.m_dwEntityList + (i * 0x10)), &entity->PlayerEnemy, sizeof(entity->PlayerEnemy), NULL);
	}

	void cEntity::getPlayerHealth() {
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(entity->PlayerEnemy + offset.m_iHealth), &entity->entHealth, sizeof(entity->entHealth), NULL);
	}

	void cEntity::getPlayerVecs() {
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(entity->PlayerEnemy + offset.m_vecOrigin), &entity->enmloc, sizeof(entity->enmloc), NULL);
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(entity->PlayerEnemy + offset.m_vecViewOffset), &entity->enmloceys, sizeof(entity->enmloceys), NULL);
	}