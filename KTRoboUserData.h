#ifndef KTROBO_USER_DATA_H
#define KTROBO_USER_DATA_H
#pragma once
#include "KTRoboRobo.h"
#include "KTRoboLoadable.h"


namespace KTROBO {

#define KTROBO_USERDATA_ASMBODY_MAX 16
#define KTROBO_USERDATA_ITEM_MAX 512
#define KTROBO_USERDATA_EMPTYITEM_METADATA_FILENAME "resrc/ktrobo/info/metadata/ktroboemptypartsmetadata.txt"

class ItemWithCategory;
	// AsmRobo では　Item* の　デストラクタは呼ばない
class AsmRobo {
	private:

		ItemWithCategory* head;
		ItemWithCategory* body;
		ItemWithCategory* arm;
		ItemWithCategory* leg;
		ItemWithCategory* booster;
		ItemWithCategory* engine;
		ItemWithCategory* fcs;
		ItemWithCategory* rarm_weapon;
		ItemWithCategory* larm_weapon;
		ItemWithCategory* rshoulder_weapon;
		ItemWithCategory* lshoulder_weapon;
		ItemWithCategory* inside_weapon;
public:
		Robo* robo;

	public:
		AsmRobo() {
			robo = new Robo();
			head = 0;
			body = 0;
			arm = 0;
			leg = 0;
			booster = 0;
			engine = 0;
			fcs = 0;
			rarm_weapon = 0;
			larm_weapon = 0;
			rshoulder_weapon = 0;
			lshoulder_weapon = 0;
			inside_weapon = 0;
		};
		~AsmRobo() {
			if (robo) {
				robo->release();
				delete robo;
				robo = 0;
			}
		};
		void initRobo(Graphics* g, MyTextureLoader* loader) {
			robo->initWithOutLoadingParts(g, loader);
		}
		void setItemWithCategory(ItemWithCategory* i);
		bool hanneiItemToRobo(Graphics* g , MyTextureLoader* tex_loader); // ロボにメッシュまでを反映させる　できなかったらfalseを返す
		void saveToFile(const char* filename);
};

class AsmBody : public Loadable2 {
	// ファイルを読み込んでアセンブルロボをロードするまで
public:
	AsmRobo arobo;
private:
	bool is_use;
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
public:
	void init(Graphics* g, MyTextureLoader* loader);
	bool calc(Graphics* g, MyTextureLoader* loader);
private:
	void setHyoukaName();

public:
	void setIsUse() { is_use = true; };
	bool getIsUse() { return is_use; };
	AsmBody() {
		weapon = BALANCE;
		leg = LEG_T2;
		sougou_rank = E;
		kidou_rank = E;
		attack_rank = E;
		soukou_rank = E;
		is_use = false;
	};
	~AsmBody() {};
	void saveToFile(const char* filename);
	string getHyoukaName() { return hyouka_name; };
};


class Item : public Loadable2 {

private:
	int item_id;
	int parts_id;
	RoboParts* part;

	

public:
	Item(int item_id,int parts_id) {
		this->item_id = item_id;
		this->parts_id = parts_id;
		part = 0;
	
	};
	~Item() {
		release();
	};
	
	virtual int getItemId() { return item_id; };
	virtual int getPartsId() { return parts_id; };

	virtual void setParts(RoboParts* parts) {

		release();

		this->part = parts;
		if (parts_id != this->part->data->getData("id")->int_data) {
			mylog::writelog(KTROBO::WARNING, "there is item okasii in %s itemid %d parts_id",parts->data->getData("id")->int_data, item_id, parts_id);
		}
	}
	
	virtual void release() {
		if (part) {
			part->Release();
			delete part;
			part = 0;
		}
		//parts_id = 0;
	};
	virtual void equip(Robo* robo, Graphics* g, MyTextureLoader* loader);
	virtual void loadRoboParts(Graphics* g, MyTextureLoader* loader);
	virtual RoboParts* getLoadedParts();

	virtual bool isEmpty() { return false; };
};


class EmptyItem : public Item {
private:
	RoboPartsEmpty* empty;

public:

	EmptyItem() : Item(0, 0) {
		empty = new RoboPartsEmpty();
	}

	~EmptyItem() {};

	void release() {
		Item::release();
		if (empty) {
			empty->Release();
			delete empty;
			empty = 0;
		}
	};

	virtual void equip(Robo* robo, Graphics* g, MyTextureLoader* loader) {};
	virtual void loadRoboParts(Graphics* g, MyTextureLoader* loader) {};
	virtual RoboParts* getLoadedParts() {
		return empty;
	};
	bool isEmpty() { return true; };
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
public:
	static RoboParts* constructParts(PartsListCategory category);
private:
	char* getMetaDataName();
	char* getDataName();
private:
	void loadInside(Graphics* g);
};

class ItemWithCategory:public Loadable2 {
private:
	bool is_save;
public:
	Item* item;
	ShopParts::PartsListCategory category;
	string metadata_filename;
	string parts_filename;
	int parts_node_index; // parts_filenameの何番目に書いてあるか
public:
	ItemWithCategory() {
		item = 0;// new Item(item_id);
		category = ShopParts::PartsListCategory::UNKNOWN;// = categ;
		metadata_filename;// = metadata_f;
		parts_filename;// = parts_f;
		this->parts_node_index = 0;// parts_node_index;
		is_save = true;
	}

	~ItemWithCategory() {
		if (item) {
			item->release();
			delete item;
			item = 0;
		}
	}
	bool is_erased() { return !is_save; };
	void erase() {
		is_save = false;
	}
	virtual void loadRoboParts(Graphics* g, MyTextureLoader* loader); // meshはロードしない　item のloadRoboPartsを呼ぶ

};

class EmptyItemWithCategory : public ItemWithCategory {

public:
	EmptyItemWithCategory(): ItemWithCategory() {
		erase();
		this->item = new EmptyItem();
		metadata_filename = KTROBO_USERDATA_EMPTYITEM_METADATA_FILENAME;
	}

	~EmptyItemWithCategory() {
		if (item) {
			item->release();
			delete item;
			item = 0;
		}

	}
	void loadRoboParts(Graphics* g, MyTextureLoader* loader) { setLoaded(); };

};

class UserData
{
private:
	int gold;
	vector<ItemWithCategory*> myitem;
	map<int, int> item_id_to_index_map;
	int item_max_id;
	EmptyItemWithCategory emptyitem;

	AsmBody asms[KTROBO_USERDATA_ASMBODY_MAX]; // 0が現在の　パーツ構成となる
	void getSuutiChara(int suuti, char* chara);
public:
	UserData();
	~UserData();


	//void saveAsmBodyFile(); // 最初のデフォルトの機体構成はアセンブルボディがない場合　
	// アセンブルボディが多すぎるときは例外を投げる　
	// この関数を呼ぶところで例外をキャッチして　メッセージをダイアログに投げる
	// ロードした時になってる構成もアセンブルボディで書く
	void writeAsmBodyFile(int file_id, AsmBody* ab);
	void Init(Graphics* g, MyTextureLoader* loader);
	void loadAsmBodyFile(int file_id);
	void loadItemFile();
	void saveItemFile();

	int getGold() { return gold; }

	void setItemWithCategoryToVector(vector<ItemWithCategory*>* outdayo, ShopParts::PartsListCategory category);

	bool buyItemInShop(RoboParts* parts, ShopParts::PartsListCategory category);
	void sellItemInShop(int item_id, Item* i) {}; // AsmBodyfileに使っているものであれば消させない

	void loadItem(int item_id) {}; // parts の　mesh までロードする

	bool isThisItemUsedInAllAsmBody(int item_id, Item* i) {};
	bool isThisItemUsedInNowAsmBody(int item_id, Item* i) {};


};


}
#endif