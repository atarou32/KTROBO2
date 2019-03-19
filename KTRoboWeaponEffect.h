#ifndef KTROBO_WEAPON_EFFECT_H
#define KTROBO_WEAPON_EFFECT_H

#pragma once
#include "KTRoboWeapon.h"

namespace KTROBO {
// weaponeffectmanager を内部で使う
// 複数のエフェクトを各武器ごとにまとめる
// エフェクトの種類
// 
class Robo;
class Game;
class Bullet;
class WeaponEffect {
public:
	WeaponEffectManager * we_manager;
	static WeaponEffect* we_rifle;
	static WeaponEffect* we_pulsegun;
	static WeaponEffect* we_laserrifle;
	static WeaponEffect* we_bazooka;
	static WeaponEffect* getWE(RoboParts* weapon);
public:
	WeaponEffect(WeaponEffectManager* w);
	~WeaponEffect();
	static void Init(WeaponEffectManager* w);
	static void Del();

	virtual void fireEffect(Game* game, Robo* robo, MYVECTOR3* pos,  AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone) = 0;
	virtual void butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec) = 0;
	virtual void butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet) = 0;
	virtual void bulletMoveControl(Game* game, Robo* aite, Bullet* bullet) = 0;
	virtual char* getBulletMeshIndexName()=0;

	static void fireEffectS(RoboParts* weaponparts, Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone);
	static void butukariEffectS(RoboParts* weaponparts, Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec);
	static void butukariShoriS(RoboParts* weaponparts, Game* game, Robo* robo, Robo* aite, Bullet* bullet);
	static void bulletMoveControlS(RoboParts* weaponparts, Game* game, Robo* aite, Bullet* bullet);
	static char* getBulletMeshIndexNameS(RoboParts* weaponparts);



};

class WE_Rifle : public WeaponEffect {
public:
	WE_Rifle(WeaponEffectManager* w) : WeaponEffect(w) {

	};
	~WE_Rifle() {};

	void fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone);
	void butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec);
	void butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet);
	void bulletMoveControl(Game* game, Robo* aite, Bullet* bullet);

	char* getBulletMeshIndexName();
};


class WE_LaserRifle : public WeaponEffect {
public:
	WE_LaserRifle(WeaponEffectManager* w) : WeaponEffect(w) {

	};
	~WE_LaserRifle() {};

	void fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone);
	void butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec);
	void butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet);
	void bulletMoveControl(Game* game, Robo* aite, Bullet* bullet);
	char* getBulletMeshIndexName();

};


class WE_Bazooka : public WeaponEffect {
public:
	WE_Bazooka(WeaponEffectManager* w) : WeaponEffect(w) {

	};
	~WE_Bazooka() {};

	void fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone);
	void butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec);
	void butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet);
	void bulletMoveControl(Game* game, Robo* aite, Bullet* bullet);
	char* getBulletMeshIndexName();

};


class WE_Pulsegun : public WeaponEffect {
public:
	WE_Pulsegun(WeaponEffectManager* w) : WeaponEffect(w) {

	};
	~WE_Pulsegun() {};

	void fireEffect(Game* game, Robo* robo, MYVECTOR3* pos, AtariBase* bullet, MYVECTOR3* vec, MYMATRIX* robo_world, MeshBone* fire_bone);
	void butukariEffect(Game* game, Robo* robo, MYVECTOR3* pos, MYVECTOR3* vec);
	void butukariShori(Game* game, Robo* robo, Robo* aite, Bullet* bullet);
	void bulletMoveControl(Game* game, Robo* aite, Bullet* bullet);
	char* getBulletMeshIndexName();

};



}

#endif