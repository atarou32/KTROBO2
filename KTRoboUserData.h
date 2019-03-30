#ifndef KTROBO_USER_DATA_H
#define KTROBO_USER_DATA_H
#pragma once
#include "KTRoboRobo.h"
#include "KTRoboLoadable.h"


namespace KTROBO {

#define KTROBO_USERDATA_ASMBODY_MAX 16
#define KTROBO_USERDATA_ITEM_MAX 1024

class Item;
	// AsmRobo では　Item*　および　Robo*　の　デストラクタは呼ばない
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
		AsmRobo() {};
		~AsmRobo() {};
		void setHead(Item* h) {};
		void setBody(Item* h) {};
		void setLeg(Item* h) {};
		void setArm(Item* h) {};
		void setBooster(Item* h) {};
		void setEngine(Item* h) {};
		void setFCS(Item* h) {};
		void setRArmWeapon(Item* h) {};
		void setLArmWeapon(Item* h) {};
		void setRShoulderWeapon(Item* h) {};
		void setLShoulderWeapon(Item* h) {};
		void setRobo(Robo* robo) {};

		void setParam() {};

};

class AsmBody : public Loadable2 {
	// ファイルを読み込んでアセンブルロボをロードするまで
public:
	AsmRobo arobo;
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
		LEG_K2 = 1,
		LEG_T2 = 2,
		LEG_J2 = 3,
		LEG_4 = 4,
		LEG_TANK = 5,
		LEG_REVERSE = 6,
	};

	enum WeaponType {
		KINSETU = 1,
		BALANCE = 2,
		SOGEKI = 3,
		MISSILE = 4,
	};

	LegType leg;
	WeaponType weapon;

	string hyouka_name;

	void setHyoukaName();
	void hyouka() {};

public:
	AsmBody() {};
	~AsmBody() {};

	string getHyoukaName() { return hyouka_name; };
};


class Item : public Loadable2 {
private:
	int item_id;
	int parts_id;
	RoboParts* part;
	bool is_equiped; // 出撃する機体のパーツのときは
	bool is_part_loaded;
public:
	Item(int item_id) {};
	~Item() {};
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

	void init(RoboParts* parts) {};
	void init(int item_id) {}; // userdat ファイルから読み込む
	void release() {};

	void equip(Robo* robo) {}; // robo に装備させる
};


struct ShopPartsInfo {
	string parts_name;
	string category;
	int price;
};


class ShopParts : public Loadable2 {
private:
	vector<RoboParts*> parts_list;
	vector<RoboDataMetaData*> meta_datas;

	vector<RoboDataMetaData*> iden_meta_datas;
	MyTextureLoader* tex_loader;

public:
	// roboparts を外部で使用するときは　shopparts->hasloaded を呼んでロードされたのを確認してから関数を呼ぶ
	// もしまだロードされていなければ　商品の整理中です　みたいなダイアログを出しておく
	int getPartsSize() { return parts_list.size(); }
	RoboParts* getRoboParts(int index) {
		if ((index >= 0) && index < parts_list.size()) {
			return parts_list[index];
		}
		return 0;
	};
	RoboDataMetaData* getMetaData(int index) {
		if ((index >= 0) && index < meta_datas.size()) {
			return meta_datas[index];
		}
		return 0;
	}
	void getShopPartsInfo(int index, ShopPartsInfo* info) {};

	enum PartsListCategory {
		UNKNOWN = 0,
		HEAD = 1,
		LEG_START =2,
		LEG_k2 = 2,
		LEG_t2 = 3,
		LEG_j2 = 4,
		LEG_tank = 5,
		LEG_4 = 6,
		LEG_REVERSE = 7,
		LEG_END = 7,
		ARM = 8,
		BODY = 9,
		BOOSTER = 10,
		ENGINE = 11,
		FCS = 12,
		INSIDE_WEAPON = 13,

		RARMWEAPON_START = 14,
		RARMWEAPON_BAZOOKA = 14,
		RARMWEAPON_BLADE = 15,
		RARMWEAPON_ENERGYBLADE = 16,
		RARMWEAPON_ENERGYRIFLE = 17,
		RARMWEAPON_GRENEDE = 18,
		RARMWEAPON_HANABIGUN = 19,
		RARMWEAPON_HANDGUN = 20,
		RARMWEAPON_MACHINEGUN = 21,
		RARMWEAPON_MISSILE = 22,
		RARMWEAPON_PILE = 23,
		RARMWEAPON_PLAZUMAGUN = 24,
		RARMWEAPON_PULSEGUN = 25,
		RARMWEAPON_RIFLE = 26,
		RARMWEAPON_ROCKET = 27,
		RARMWEAPON_SHOTGUN = 28,
		RARMWEAPON_SNIPERRIFLE = 29,
		RARMWEAPON_END = 29,

		LARMWEAPON_START = 30,
		LARMWEAPON_BAZOOKA = 30,
		LARMWEAPON_BLADE = 31,
		LARMWEAPON_ENERGYBLADE = 32,
		LARMWEAPON_ENERGYRIFLE = 33,
		LARMWEAPON_GRENEDE = 34,
		LARMWEAPON_HANABIGUN = 35,
		LARMWEAPON_HANDGUN = 36,
		LARMWEAPON_MACHINEGUN = 37,
		LARMWEAPON_MISSILE = 38,
		LARMWEAPON_PILE = 39,
		LARMWEAPON_PLAZUMAGUN = 40,
		LARMWEAPON_PULSEGUN = 41,
		LARMWEAPON_RIFLE = 42,
		LARMWEAPON_ROCKET = 43,
		LARMWEAPON_SHOTGUN = 44,
		LARMWEAPON_SNIPERRIFLE = 45,
		LARMWEAPON_END = 45,

		RKATAWEAPON_START = 46,
		RKATAWEAPON_CHAINGUN = 46,
		RKATAWEAPON_GRENEDE = 47,
		RKATAWEAPON_HANABI = 48,
		RKATAWEAPON_MISSILE = 49,
		RKATAWEAPON_PLAZUMA = 50,
		RKATAWEAPON_PULSE = 51,
		RKATAWEAPON_RASER = 52,
		RKATAWEAPON_ROCKET = 53,
		RKATAWEAPON_END = 53,

		LKATAWEAPON_START = 54,
		LKATAWEAPON_CHAINGUN = 54,
		LKATAWEAPON_GRENEDE = 55,
		LKATAWEAPON_HANABI = 56,
		LKATAWEAPON_MISSILE = 57,
		LKATAWEAPON_PLAZUMA = 58,
		LKATAWEAPON_PULSE = 59,
		LKATAWEAPON_RASER = 60,
		LKATAWEAPON_ROCKET = 61,
		LKATAWEAPON_END = 61,
	};
	PartsListCategory category;

	ShopParts(PartsListCategory cat, MyTextureLoader* loader) {
		category = cat;
		tex_loader = loader;
		
	};
	~ShopParts() {
		int size = parts_list.size();
		for (int i = 0; i < size; i++) {
			if (parts_list[i]) {
				parts_list[i]->Release();
				delete parts_list[i];
				parts_list[i] = 0;
			}
		}
		parts_list.clear();

		int msize = iden_meta_datas.size();
		for (int i = 0; i < msize; i++) {
			if (iden_meta_datas[i]) {
				delete iden_meta_datas[i];
				iden_meta_datas[i] = 0;
			}
		}
		iden_meta_datas.clear();
		meta_datas.clear();
	};
	void atoload(Graphics* g); // meshパーツのロード
	void load(Graphics* g);
private:
	RoboParts* constructParts();
	char* getMetaDataName();
	char* getDataName();
	void loadInside(Graphics* g);
};







class UserData
{
public:
	UserData();
	~UserData();


	void saveAsmBodyFile(AsmBody* save_ab) {}; // 最初のデフォルトの機体構成はアセンブルボディがない場合　
	// アセンブルボディが多すぎるときは例外を投げる　
	// この関数を呼ぶところで例外をキャッチして　メッセージをダイアログに投げる
	// ロードした時になってる構成もアセンブルボディで書く
	void overWriteAsmBodyFile(int file_id, AsmBody* ab) {};
	void loadAsmBodyfile(int file_id) {};

	void buyItemInShop(RoboParts* parts, ShopParts::PartsListCategory category) {};
	void sellItemInShop(int item_id, Item* i) {}; // AsmBodyfileに使っているものであれば警告を出す


	void getUnLoadedItemIds(int item_ids_size, int* item_ids) {}; // ITEM_IDS_SIZE 32まで item_ids に格納する
	Item* getItem(int item_id) {};
	void loadItem(int item_id) {}; // parts の　mesh までロードする

	bool isThisItemUsedInAllAsmBody(int item_id, Item* i) {};
	bool isThisItemUsedInNowAsmBody(int item_id, Item* i) {};


};


}
#endif