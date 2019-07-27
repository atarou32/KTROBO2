#ifndef KTROBOWEAPON_H
#define KTROBOWEAPON_H

#pragma once
#include "KTRoboGraphics.h"
#include "KTRoboAtari.h"
#include "KTRoboTexture.h"
#include "MySound.h"

namespace KTROBO {

class Scene;
class Game;
class BulletController;
class Robo;
class RoboParts;
class WeaponFire
{
protected:
	float reloadtime;
	bool is_canfire;
	float dtime;

public:
	WeaponFire(void);
	~WeaponFire(void);
	virtual void fire(Robo* robo, RoboParts* parts,Graphics* g, Game* game, Scene* scene, BulletController* controller, AtariHantei* hantei, MySound* sound, MYMATRIX* robo_world, MYVECTOR3* vec, MYVECTOR3* pos,MeshBone* fire_bone);
	void update(float dsecond, int stamp);
};

class WeaponFireRifle : public WeaponFire {
public:
	WeaponFireRifle();
	~WeaponFireRifle();
	void fire(Robo* robo, RoboParts* parts, Graphics* g, Game* game, Scene* scene, BulletController* controller, AtariHantei* hantei, MySound* sound, MYMATRIX* robo_world, MYVECTOR3* vec, MYVECTOR3* pos, MeshBone* fire_bone);

};

struct WeaponEffectStruct {
	int effect_id;
	int effect_impl_id;
	float alive_time; // ���̎������������烊���[�X����
	float now_time;
	bool is_use; // ���ݎg���Ă��邩
	bool is_once_used; //�g���Ă������Ƃ����邩
	
	bool is_world_update;
	
	AtariBase* world_update_base;
	MeshBone* fire_bone;

	WeaponEffectStruct() {
		effect_id = 0;
		effect_impl_id = 0;
		alive_time = 0;
		is_use = false;
		is_once_used = false;
		world_update_base = 0;
		is_world_update = false;
		now_time = 0;
		fire_bone = 0;
	}

};
class EffectManager;
class WeaponEffectManager {
private:
	EffectManager* manager;
	vector<WeaponEffectStruct*> effect_structs;

public:
	WeaponEffectManager(EffectManager* mang) {
		manager = mang;
	}
	~WeaponEffectManager(); // struct �݂̂������̂݁@�G�t�F�N�g�͎c�� �ǂ������̏ꏊ��effectmanager::deleteeffectimpl�݂����Ȃ��̂��Ă�

	void update(float dt);
	void killEffectNow(WeaponEffectStruct* effe);
	WeaponEffectStruct* makeWeaponEffect(char* effect_name, float alive_time, bool is_world_update, MYMATRIX* world, AtariBase* world_update_base,MeshBone* fire_bone);

};
}

#endif