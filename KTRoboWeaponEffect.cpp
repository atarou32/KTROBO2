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

WeaponEffect* WeaponEffect::we_sniperrifle = NULL;
WeaponEffect* WeaponEffect::we_machinegun = NULL;
WeaponEffect* WeaponEffect::we_energyblade = NULL;

void WeaponEffect::Init(WeaponEffectManager* w) {
	we_rifle = new WE_Rifle(w);
	we_laserrifle = new WE_LaserRifle(w);
	we_pulsegun = new WE_Pulsegun(w);
	we_bazooka = new WE_Bazooka(w);
	we_sniperrifle = new WE_SniperRifle(w);
	we_machinegun = new WE_Machinegun(w);
	we_energyblade = new WE_EnergyBlade(w);
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
	if (we_machinegun) {
		delete we_machinegun;
		we_machinegun = 0;
	}
	if (we_bazooka) {
		delete we_bazooka;
		we_bazooka = 0;
	}

	if (we_sniperrifle) {
		delete we_sniperrifle;
		we_sniperrifle = 0;
	}

	if (we_energyblade) {
		delete we_energyblade;
		we_energyblade = 0;
	}
}



void WE_Rifle::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle08");
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800,true, robo_world, robo,fire_bone));
	MYMATRIX ww;
	bullet->mesh_i->getWorld(&ww);
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bulletkagayaki", 10000, true, &ww, bullet, bullet->atarihan->meshs[0]->mesh->Bones[0]));


}

void WE_Rifle::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponrifle", 3000, false, &worldd, NULL, NULL);
	// 当たり判定がおきるのをふせぐためにランダムに移動させる
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	game->getSound()->playCue("se_maoudamashii_explosion03");
}

void WE_Rifle::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	game->weapon_effect_manager->killEffectNow(bullet->getWES());
}

void WE_Rifle::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {
	if (aite) {
		MYVECTOR3 kyo = MYVECTOR3(bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		kyo = kyo - MYVECTOR3(aite->atarihan->x, aite->atarihan->y, aite->atarihan->z);
		float zkyo = aite->atarihan->z - bullet->atarihan->z;
		float kyoo = MyVec3Length(kyo);
		float vlen = bullet->getHVLen();
		float time = kyoo / vlen;
		float dist = bullet->getFireDistance();
		if (dist > kyoo) {
			// 下に移動させる
			float dz = zkyo - bullet->atarihan->v.float3.z * time;
			if (dz > 0) {
				bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));
			}
			else {
				bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z - 0.00003));
			}
		}
		else {
			// 上に移動させる
			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));

		}
	}
	else {

		MYVECTOR3 kyo = MYVECTOR3(bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		//kyo = kyo - MYVECTOR3(aite->atarihan->x, aite->atarihan->y, aite->atarihan->z);
		//float zkyo = aite->atarihan->z - bullet->atarihan->z;
		float kyoo = 20;// MyVec3Length(kyo);
		float vlen = bullet->getHVLen();
		float time = kyoo / vlen;
		float dist = bullet->getFireDistance();
		if (dist > kyoo) {
			// 下に移動させる
		
				bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z - 0.00003));
			
		}
		else {
			// 上に移動させる
			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));

		}
	}
}

void WE_LaserRifle::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle_gun05");
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800, true, robo_world, robo, fire_bone));
	MYMATRIX ww;
	bullet->mesh_i->getWorld(&ww);
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bulletkagayaki", 10000, true, &ww, bullet, bullet->atarihan->meshs[0]->mesh->Bones[0]));

}

void WE_LaserRifle::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponlaserrifle", 3000, false, &worldd, NULL, NULL);
	// 当たり判定がおきるのをふせぐためにランダムに移動させる
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	game->getSound()->playCue("se_maoudamashii_explosion04");
}

void WE_LaserRifle::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	game->weapon_effect_manager->killEffectNow(bullet->getWES());
}

void WE_LaserRifle::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {
	if (aite) {
		MYMATRIX worldd;
		MYVECTOR4 color;
		color.w = 1;
		color.x = 1;
		color.y = 1;
		color.z = 1;
		MyMatrixTranslation(worldd, bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		float dti = bullet->getdtime();
		
		if ((int)dti % 50 < 25 ) {
			game->weapon_effect_manager->makeWeaponEffect("kiseki_weaponlaserrifle", 2000, false, &worldd, NULL, NULL);
		
		}
	}
	
	return;
}




void WE_SniperRifle::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle_gun03");
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800, true, robo_world, robo, fire_bone));
	MYMATRIX ww;
	bullet->mesh_i->getWorld(&ww);
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bulletkagayaki", 10000, true, &ww, bullet, bullet->atarihan->meshs[0]->mesh->Bones[0]));

}

void WE_SniperRifle::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponrifle", 3000, false, &worldd, NULL, NULL);
	// 当たり判定がおきるのをふせぐためにランダムに移動させる
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	game->getSound()->playCue("se_maoudamashii_battle18");
}

void WE_SniperRifle::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	game->weapon_effect_manager->killEffectNow(bullet->getWES());
}

void WE_SniperRifle::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {
	if (aite) {
		MYMATRIX worldd;
		MYVECTOR4 color;
		color.w = 1;
		color.x = 1;
		color.y = 1;
		color.z = 1;
		MyMatrixTranslation(worldd, bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		float dti = bullet->getdtime();

		//if ((int)dti % 50 < 25) {
			game->weapon_effect_manager->makeWeaponEffect("kiseki_weaponsniperrifle", 2000, false, &worldd, NULL, NULL);

		//}
	}

	return;
}



void WE_Bazooka::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle07");
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800, true, robo_world, robo, fire_bone));
	MYMATRIX ww;
	bullet->mesh_i->getWorld(&ww);
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bulletkagayaki", 10000, true, &ww, bullet, bullet->atarihan->meshs[0]->mesh->Bones[0]));

}

void WE_Bazooka::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponbazooka", 2240, false, &worldd, NULL, NULL);
	// 当たり判定がおきるのをふせぐためにランダムに移動させる
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	game->getSound()->playCue("se_maoudamashii_explosion06");

}

void WE_Bazooka::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	game->weapon_effect_manager->killEffectNow(bullet->getWES());
}

void WE_Bazooka::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {
	//なし
	return;
}


void WE_Pulsegun::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle10");
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800, true, robo_world, robo, fire_bone));
	MYMATRIX ww;
	bullet->mesh_i->getWorld(&ww);
		bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bulletkagayaki", 10000, true, &ww, bullet, bullet->atarihan->meshs[0]->mesh->Bones[0]));

}

void WE_Pulsegun::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponpulsegun", 3000, false, &worldd, NULL, NULL);
	// 当たり判定がおきるのをふせぐためにランダムに移動させる
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	game->getSound()->playCue("se_maoudamashii_battle12");
}

void WE_Pulsegun::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	game->weapon_effect_manager->killEffectNow(bullet->getWES());
}

void WE_Pulsegun::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {
	if (aite) {
		MYVECTOR3 kyo = MYVECTOR3(bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		kyo = kyo - MYVECTOR3(aite->atarihan->x, aite->atarihan->y, aite->atarihan->z);
		float zkyo = aite->atarihan->z - bullet->atarihan->z;
		float kyoo = MyVec3Length(kyo);
		float vlen = bullet->getHVLen();
		float time = kyoo / vlen;
		float dist = bullet->getFireDistance();
		if (dist > kyoo) {
			// 下に移動させる
			float dz = zkyo - bullet->atarihan->v.float3.z * time;
			if (dz > 0) {
				bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));
			}
			else {
				bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z - 0.00003));
			}
		}
		else {
			// 上に移動させる
			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));

		}

		float dtt = bullet->getdtime();
		RoboDataPart* par = bullet->robo_parts->data->getData("FIRED");
		if (par) {
			if (dtt > 0.8* (float)par->int_data / bullet->getHVLen()) {
				bullet->setExpired();
			}
		}


	}
	else {

		MYVECTOR3 kyo = MYVECTOR3(bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		//kyo = kyo - MYVECTOR3(aite->atarihan->x, aite->atarihan->y, aite->atarihan->z);
		//float zkyo = aite->atarihan->z - bullet->atarihan->z;
		float kyoo = 20;// MyVec3Length(kyo);
		float vlen = bullet->getHVLen();
		float time = kyoo / vlen;
		float dist = bullet->getFireDistance();
		if (dist > kyoo) {
			// 下に移動させる

			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z - 0.00003));

		}
		else {
			// 上に移動させる
			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));

		}

		float dtt = bullet->getdtime();
		RoboDataPart* par = bullet->robo_parts->data->getData("FIRED");
		if (par) {
			if (dtt > 0.8*(float)par->int_data / bullet->getHVLen()) {
				bullet->setExpired();
			}
		}
	}
}


char* WE_Rifle::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_RIFLE_INDEXNAME;
}

char* WE_LaserRifle::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_LASERRIFLE_INDEXNAME;
}


char* WE_SniperRifle::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_SNIPERRIFLE_INDEXNAME;
}

char* WE_Pulsegun::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_RIFLE_INDEXNAME;
}


char* WE_Machinegun::getBulletMeshIndexName() {
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

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWSRF") != -1) {
		return we_sniperrifle;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWSRF") != -1) {
		return we_sniperrifle;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWMC") != -1) {
		return we_machinegun;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWMC") != -1) {
		return we_machinegun;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWEBL") != -1) {
		return we_energyblade;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWEBL") != -1) {
		return we_energyblade;
	}


	return we_rifle;

}

void WeaponEffect::fireEffectS(RoboParts* weaponparts,Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {

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
bool WeaponEffect::isExpireWhenButukari(RoboParts* weapon, Game* game, Robo* robo, Bullet* bullet) {
	if (hstrpos(weapon->data->getData("name")->string_data, "BZK") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "PUL") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWRF") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWRF") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWERF") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWERF") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWSRF") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWSRF") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTRWMC") != -1) {
		return true;
	}

	if (hstrpos(weapon->data->getData("name")->string_data, "KTLWMC") != -1) {
		return true;
	}

	return false;


}


void WE_Machinegun::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle_gun04");
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800, true, robo_world, robo, fire_bone));
	MYMATRIX ww;
	bullet->mesh_i->getWorld(&ww);
//	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bulletkagayaki", 10000, true, &ww, bullet, bullet->atarihan->meshs[0]->mesh->Bones[0]));


}

void WE_Machinegun::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponrifle", 3000, false, &worldd, NULL, NULL);
	// 当たり判定がおきるのをふせぐためにランダムに移動させる
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	game->getSound()->playCue("se_maoudamashii_battle15");
}

void WE_Machinegun::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	game->weapon_effect_manager->killEffectNow(bullet->getWES());
}

void WE_Machinegun::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {




	if (aite) {
		MYVECTOR3 kyo = MYVECTOR3(bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		kyo = kyo - MYVECTOR3(aite->atarihan->x, aite->atarihan->y, aite->atarihan->z);
		float zkyo = aite->atarihan->z - bullet->atarihan->z;
		float kyoo = MyVec3Length(kyo);
		float vlen = bullet->getHVLen();
		float time = kyoo / vlen;
		float dist = bullet->getFireDistance();
		if (dist > kyoo) {
			// 下に移動させる
			float dz = zkyo - bullet->atarihan->v.float3.z * time;
			if (dz > 0) {
				bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));
			}
			else {
				bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z - 0.00003));
			}
		}
		else {
			// 上に移動させる
			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));

		}

		float dtt = bullet->getdtime();
		RoboDataPart* par = bullet->robo_parts->data->getData("FIRED");
		if (par) {
			if (dtt > 0.8* (float)par->int_data / bullet->getHVLen()) {
				bullet->setExpired();
			}
		}


	}
	else {

		MYVECTOR3 kyo = MYVECTOR3(bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		//kyo = kyo - MYVECTOR3(aite->atarihan->x, aite->atarihan->y, aite->atarihan->z);
		//float zkyo = aite->atarihan->z - bullet->atarihan->z;
		float kyoo = 20;// MyVec3Length(kyo);
		float vlen = bullet->getHVLen();
		float time = kyoo / vlen;
		float dist = bullet->getFireDistance();
		if (dist > kyoo) {
			// 下に移動させる

			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z - 0.00003));

		}
		else {
			// 上に移動させる
			bullet->atarihan->setV(&MYVECTOR3(bullet->atarihan->v.float3.x, bullet->atarihan->v.float3.y, bullet->atarihan->v.float3.z + 0.00003));

		}

		float dtt = bullet->getdtime();
		RoboDataPart* par = bullet->robo_parts->data->getData("FIRED");
		if (par) {
			if (dtt > 0.8*(float)par->int_data / bullet->getHVLen()) {
				bullet->setExpired();
			}
		}
	}
}




void WE_EnergyBlade::fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, Bullet* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) {
	game->getSound()->playCue("se_maoudamashii_battle17");
	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bakuhatu", 800, true, robo_world, robo, fire_bone));
	MYMATRIX ww;
	bullet->mesh_i->getWorld(&ww);
	//	bullet->setWES(game->weapon_effect_manager->makeWeaponEffect("bulletkagayaki", 10000, true, &ww, bullet, bullet->atarihan->meshs[0]->mesh->Bones[0]));
	
}


void WE_EnergyBlade::butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) {
	MYMATRIX worldd;
	MYVECTOR4 color;
	color.w = 1;
	color.x = 1;
	color.y = 1;
	color.z = 1;
	MyMatrixTranslation(worldd, pos->float3.x, pos->float3.y, pos->float3.z);
	//game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponlaserrifle", 3000, false, &worldd, NULL, NULL);
	// 当たり判定がおきるのをふせぐためにランダムに移動させる
	//b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
	//b->atarihan->calcJyusinAndR(true);
	//b->setIsUse(false);
	//mm->setColor(&color);
	
}


void WE_EnergyBlade::butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) {
	//game->weapon_effect_manager->killEffectNow(bullet->getWES());
	if (aite) {
	//	game->getSound()->playCue("se_maoudamashii_battle06");
		MYMATRIX worldd;
		MYVECTOR4 color;
		color.w = 1;
		color.x = 1;
		color.y = 1;
		color.z = 1;
		MyMatrixTranslation(worldd, bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		game->weapon_effect_manager->makeWeaponEffect("bakuhatu_weaponlaserrifle", 3000, false, &worldd, NULL, NULL);

	}
}


void WE_EnergyBlade::bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) {
	
		MYMATRIX worldd;
		MYVECTOR4 color;
		color.w = 1;
		color.x = 1;
		color.y = 1;
		color.z = 1;
		MyMatrixTranslation(worldd, bullet->atarihan->x, bullet->atarihan->y, bullet->atarihan->z);
		float dti = bullet->getdtime();

		if (dti > 1300) {
			bullet->setExpired();
		}
		else {

			if (bullet->robo) {
				MYMATRIX mat = bullet->robo->atarihan->world;
				MYMATRIX mat2;
				MYVECTOR3 mum(0, -1, 0);
				MyVec3TransformNormal(mum, mum, mat);
				MyVec3Normalize(mum, mum);

				MYVECTOR3 up(0, 0, 1);

				if (hstrpos(bullet->robo_parts->data->getData("name")->string_data, "KTRW") != -1) {
					up = MYVECTOR3(0, 0, -1);
				}
				MyVec3TransformNormal(up, up, mat);
				MYVECTOR3 mvec(0, 0, 0);
				MyMatrixRotationAxis(mat2, up, (3, 14 - dti / 1300.0 * 3.14)+1.57);
				MyVec3TransformNormal(mvec, mum, mat2);
				MyVec3Normalize(mvec, mvec);
				float fired = (float)bullet->robo_parts->data->getData("FIRED")->int_data;
				bullet->setHPOS(&MYVECTOR3(bullet->robo->atarihan->x, bullet->robo->atarihan->y, bullet->robo->atarihan->z));
				bullet->setPOS(&MYVECTOR3(bullet->robo->atarihan->x + mvec.float3.x *fired, bullet->robo->atarihan->y + mvec.float3.y *fired, bullet->robo->atarihan->z + mvec.float3.z *fired));
				bullet->setSHOKIWORLD(&bullet->robo->atarihan->world);
			}






		}
		game->weapon_effect_manager->makeWeaponEffect("kiseki_weaponlaserrifle", 500, false, &worldd, NULL, NULL);

	

	return;
}

char* WE_EnergyBlade::getBulletMeshIndexName() {
	return KTROBO_BULLET_MESH_ENERGYBLADE_INDEXNAME;
}