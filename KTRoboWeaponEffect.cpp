#include "KTRoboWeaponEffect.h"
#include "KTRoboRobo.h"
#include "MyTokenAnalyzer.h"
#include "KTRoboBullet.h"
#include "KTRoboGame.h"


using namespace KTROBO;

WeaponEffect::WeaponEffect(WeaponEffectManager* w)
{
	we_manager = w;
}


WeaponEffect::~WeaponEffect()
{
}

WeaponEffect* WeaponEffect::we_rifle = NULL;

WeaponEffect* WeaponEffect::we_laserrifle = NULL;

WeaponEffect* WeaponEffect::we_pulsegun = NULL;

WeaponEffect* WeaponEffect::we_bazooka = NULL;



void WeaponEffect::Init(WeaponEffectManager* w) {
	we_rifle = new WE_Rifle(w);
	we_laserrifle = new WE_LaserRifle(w);
	we_pulsegun = new WE_Pulsegun(w);
	we_bazooka = new WE_Bazooka(w);
}
void WeaponEffect::Del() {
	if (we_rifle) {
		delete we_rifle;
		we_rifle = 0;
	}
	if (we_laserrifle) {
		delete we_laserrifle;
		we_laserrifle=0;
	}
	if (we_pulsegun) {
		delete we_pulsegun;
		we_pulsegun = 0;
	}
	if (we_bazooka) {
		delete we_bazooka;
		we_bazooka = 0;
	}
}



void WE_Rifle::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle08");
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800,true, robo_world, robo,fire_bone);

}

void WE_Rifle::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponrifle", 1500, false, &worldd, NULL, NULL);
	// “–‚½‚è”»’è‚ª‚¨‚«‚é‚Ì‚ð‚Ó‚¹‚®‚½‚ß‚Éƒ‰ƒ“ƒ_ƒ€‚ÉˆÚ“®‚³‚¹‚é
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	game->getSound()->playCue("se_maoudamashii_explosion03");
}

void WE_Rifle::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	
}

void WE_Rifle::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {


}

void WE_LaserRifle::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {

}

void WE_LaserRifle::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {

}

void WE_LaserRifle::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {

}

void WE_LaserRifle::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {

}


void WE_Bazooka::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {

}

void WE_Bazooka::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {


}

void WE_Bazooka::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {

}

void WE_Bazooka::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {

}


void WE_Pulsegun::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {

}

void WE_Pulsegun::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {

}

void WE_Pulsegun::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {

}

void WE_Pulsegun::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {

}


char* WE_Rifle::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_RIFLE_INDEXNAME;
}

char* WE_LaserRifle::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_LASERRIFLE_INDEXNAME;
}

char* WE_Pulsegun::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_RIFLE_INDEXNAME;
}

char* WE_Bazooka::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_RIFLE_INDEXNAME;
}

WeaponEffect* WeaponEffect::getWE(RoboParts* weapon) {
	if (hstrpos(weapon->data->getData("name")->string_data, "BZK") != -1) {
		return we_bazooka;
	}
	
	if (hstrpos(weapon->data->getData("name")->string_data, "PUL") != -1) {
		return we_pulsegun;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWRF") != -1) {
		return we_rifle;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWRF") != -1) {
		return we_rifle;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWERF") != -1) {
		return we_laserrifle;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWERF") != -1) {
		return we_laserrifle;
	}

	return we_rifle;

}

void WeaponEffect::fireEffectS(RoboParts* weaponparts,Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {

	getWE(weaponparts)->fireEffect(game, robo,pos , bullet, vec,robo_world,fire_bone);
}
void WeaponEffect::butukariEffectS(RoboParts* weaponparts, Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {

	getWE(weaponparts)->butukariEffect(game, robo, pos, vec);
}

void WeaponEffect::butukariShoriS(RoboParts* weaponparts, Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	getWE(weaponparts)->butukariShori(game, robo, aite,bullet);
}


void WeaponEffect::bulletMoveControlS(RoboParts* weaponparts, Game* game, Robo* aite, Bullet* bullet) {
	getWE(weaponparts)->bulletMoveControl(game, aite, bullet);
}


char* WeaponEffect::getBulletMeshIndexNameS(RoboParts* weaponparts) {
	return getWE(weaponparts)->getBulletMeshIndexName();
}

