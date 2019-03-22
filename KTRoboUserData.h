#ifndef KTROBO_USER_DATA_H
#define KTROBO_USER_DATA_H
#pragma once
#include "KTRoboRobo.h"

namespace KTROBO {

#define KTROBO_USERDATA_ASMBODY_MAX 16
#define KTROBO_USERDATA_ITEM_MAX 1024

class AsmRobo;

class AsmBody {
public:
	AsmRobo* arobo;
private:
	string filename;
	int file_id;
public:
	enum AsmRank {
		UNKNOWN = 0,
		S = 1,
		A = 2,
		B = 3,
		C = 4,
		D = 5,
		E = 6,
		F = 7,
	};
private:
	AsmRank sougou_rank;
	AsmRank attack_rank;
	AsmRank soukou_rank;
	AsmRank kidou_rank;
	
	enum LegType {
		UNKNOWN  = 0,
		LEG_K2 = 1,
		LEG_T2 = 2,
		LEG_J2 = 3,
		LEG_4 = 4,
		LEG_TANK = 5,
		LEG_REVERSE = 6,
	};

	enum WeaponType {
		UNKNOWN = 0,
		KINSETU = 1,
		BALANCE = 2,
		SOGEKI = 3,
		MISSILE = 4,
	};

	LegType leg;
	WeaponType weapon;

	string hyouka_name;

	void setHyoukaName();
	void hyouka();
public:
	string getHyoukaName() { return hyouka_name; };
};
	
class Item {
private:
	int item_id;
	int parts_id;
	RoboParts* part;
	bool is_equiped; // 出撃する機体のパーツのときは
public:
	Item();
	~Item();
	enum ITEM_SOUBI_KASHO {
		UNKNOWN = 0,
		HEAD = 1,
		BODY = 2,
		ARM = 3,
		LEG = 4,
		BOOSTER = 5,
		ENGINE = 6,
		FCS = 7,
		RARMWEAPON = 8,
		LARMWEAPON = 9,
		RSWEAPON = 10,
		LSWEAPON = 11,
		INSIDE = 12,
	};

	ITEM_SOUBI_KASHO kasho;
	void init(Item* ite);
	void init(RoboParts* parts);
	void init(int item_id);


	void equip(Robo* robo); // robo に装備させる
};



class AsmRobo {
private:

	Item* head;
	Item* body;
	Item* arm;
	Item* leg;
	Item* booster;
	Item* engine;
	Item* fcs;
	Item* rarm_weapon;
	Item* larm_weapon;
	Item* rshoulder_weapon;
	Item* lshoulder_weapon;
	Item* inside_weapon;
	Robo* robo;

	int ap;
	int def;
	int e_def;
	int max_weight;
	int weight;
	int energy_pool;
	int energy_supply;
	int energy_shuturyoku;
	int jump_power;
	int booster_power;
	int booster_useenergy;

	int move_speed;
	int boost_speed;
	int on_speed;


public:
	AsmRobo();
	~AsmRobo();
	void setHead(Item* h);
	void setBody(Item* h);
	void setLeg(Item* h);
	void setArm(Item* h);
	void setBooster(Item* h);
	void setEngine(Item* h);
	void setFCS(Item* h);
	void setRArmWeapon(Item* h);
	void setLArmWeapon(Item* h);
	void setRShoulderWeapon(Item* h);
	void setLShoulderWeapon(Item* h);


};






class UserData
{
public:
	UserData();
	~UserData();


	void makeNewAsmBodyFile(); // 最初のデフォルトの機体構成はアセンブルボディがない場合　
	// ロードした時になってる構成もアセンブルボディで書く
	void overWriteAsmBodyFile();
	void loadAsmBodyfile();

	void buyItemInShop();
	void sellItemInShop(); // AsmBodyfileに使っているものであれば警告を出す
	bool isThisItemUsedInAllAsmBody();
	bool isThisItemUsedInNowAsmBody();


};


}
#endif