#include "KTRoboUserData.h"
#include "MyTextureLoader.h"
#include "KTRoboLoadable.h"

using namespace KTROBO;

UserData::UserData()
{
	gold = 12000000;
}


UserData::~UserData()
{
	int siz = myitem.size();
	for (int i = 0; i < siz; i++) {
		if (myitem[i]) {
			if (myitem[i]->item) {
				myitem[i]->item->release();
				delete myitem[i]->item;
				myitem[i]->item = 0;
			}
			delete myitem[i];
			myitem[i] = 0;
		}
	}
	myitem.clear();
}

void AsmBody::init(Graphics* g, MyTextureLoader* loader) {
	arobo.initRobo(g, loader);
}


void UserData::Init(Graphics* g, MyTextureLoader* loader) {
	
	loadItemFile();
	for (int i = 0; i < KTROBO_USERDATA_ASMBODY_MAX; i++) {
		asms[i].init(g, loader);
		loadAsmBodyFile(i);
	}

	asms[0].setIsUse();

}



void UserData::getSuutiChara(int suuti, char* chara) {
	int temp = 0;
	if (suuti < 0) {
		chara[temp] = '-';
		temp++;
		suuti *= -1;
	}
	int suut = suuti;
	int keta = 0;
	while (suut > 0) {
		suut = suut / 10;
		keta++;
	}
	if (keta == 0) {
		chara[temp] = '0';
		temp++;
		chara[temp] = '\0';
		return;
	}
	suut = suuti;
	int tt = keta;
	while (keta > 0) {
		int amari = suut % 10;
		if (amari == 0) {
			chara[temp + keta - 1] = '0';
		}
		else if (amari == 1) {
			chara[temp + keta - 1] = '1';
		}
		else if (amari == 2) {
			chara[temp + keta - 1] = '2';
		}
		else if (amari == 3) {
			chara[temp + keta - 1] = '3';
		}
		else if (amari == 4) {
			chara[temp + keta - 1] = '4';
		}
		else if (amari == 5) {
			chara[temp + keta - 1] = '5';
		}
		else if (amari == 6) {
			chara[temp + keta - 1] = '6';
		}
		else if (amari == 7) {
			chara[temp + keta - 1] = '7';
		}
		else if (amari == 8) {
			chara[temp + keta - 1] = '8';
		}
		else if (amari == 9) {
			chara[temp + keta - 1] = '9';
		}
		suut = suut / 10;
		keta--;
	}
	chara[temp + tt] = 0;
	return;


}

void UserData::loadAsmBodyFile(int file_id) {
	if ((file_id < 0) || (file_id >= KTROBO_USERDATA_ASMBODY_MAX)) return;

	char str[1024];
	FILE* file;
	memset(str, 0, 1024);
	getSuutiChara(file_id, str);
	string filename = string("userdata/asm") + string(str) + string(".myasm");
	CS::instance()->enter(CS_LOG_CS, "loadasm");
	if (0 != fopen_s(&file, filename.c_str(), "r")) {
		CS::instance()->leave(CS_LOG_CS, "loadasm");
		return;
	}

	fclose(file);
	CS::instance()->leave(CS_LOG_CS, "loadasm");
	MyTokenAnalyzer ma;
	if (ma.load(filename.c_str())) {
		asms[file_id].setIsUse();

		while (!ma.enddayo()) {
			ma.GetToken();
			if (strcmp(ma.Toke(), "head") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "body") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "arm") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "leg") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "booster") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "fcs") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "engine") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "rarm") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "larm") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "rkata") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "lkata") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
			else if (strcmp(ma.Toke(), "inside") == 0) {
				asms[file_id].arobo.setItemWithCategory(
					myitem[item_id_to_index_map.find(ma.GetIntToken())->second]);
				ma.GetIntToken();
			}
		}
		ma.deletedayo();
	}

}
void AsmBody::saveToFile(const char* filename) {
	arobo.saveToFile(filename);


}
void AsmRobo::saveToFile(const char* filename) {
	if (head) {
		mylog::writelog(filename, "head=%d;%d;\n", head->item->getItemId(), head->item->getPartsId());
	}
	if (body) {
		mylog::writelog(filename, "body=%d;%d;\n", body->item->getItemId(), body->item->getPartsId());
	}
	if (leg) {
		mylog::writelog(filename, "leg=%d;%d;\n", leg->item->getItemId(), leg->item->getPartsId());
	}
	if (arm) {
		mylog::writelog(filename, "arm=%d;%d;\n", arm->item->getItemId(), arm->item->getPartsId());
	}

	if (booster) {
		mylog::writelog(filename, "booster=%d;%d;\n", booster->item->getItemId(), booster->item->getPartsId());
	}

	if (engine) {
		mylog::writelog(filename, "engine=%d;%d;\n", engine->item->getItemId(), engine->item->getPartsId());
	}
	if (fcs) {
		mylog::writelog(filename, "fcs=%d;%d;\n", fcs->item->getItemId(), fcs->item->getPartsId());
	}

	if (rarm_weapon) {
		mylog::writelog(filename, "rarm=%d;%d;\n", rarm_weapon->item->getItemId(), rarm_weapon->item->getPartsId());
	}
	if (larm_weapon) {
		mylog::writelog(filename, "larm=%d;%d;\n", larm_weapon->item->getItemId(), larm_weapon->item->getPartsId());
	}

	if (rshoulder_weapon) {
		mylog::writelog(filename, "rkata=%d;%d;\n", rshoulder_weapon->item->getItemId(), rshoulder_weapon->item->getPartsId());
	}

	if (lshoulder_weapon) {
		mylog::writelog(filename, "lkata=%d;%d;\n", lshoulder_weapon->item->getItemId(), lshoulder_weapon->item->getPartsId());
	}

	if (inside_weapon) {
		mylog::writelog(filename, "inside=%d;%d;\n", inside_weapon->item->getItemId(),inside_weapon->item->getPartsId());
	}



}

void UserData::writeAsmBodyFile(int file_id, AsmBody* ab) {
	char str[1024];
	FILE* file;
	memset(str, 0, 1024);
	getSuutiChara(file_id, str);
	string filename = string("userdata/asm") + string(str) + string(".myasm");
	if (ab) {
		CS::instance()->enter(CS_LOG_CS, "saveasm");
		if (0 != fopen_s(&file, filename.c_str(), "w")) {
			CS::instance()->leave(CS_LOG_CS, "saveasm");
			return;
		}

		fclose(file);

		
		ab->saveToFile(filename.c_str());


		CS::instance()->leave(CS_LOG_CS, "loaditem");
	}
}


void UserData::saveItemFile() {
	FILE* file;
	const char* filename = "userdata/item.mydat";
	int size = myitem.size();
	CS::instance()->enter(CS_LOAD_CS, "enter");
	CS::instance()->enter(CS_LOG_CS, "saveitem");
	if (0 != fopen_s(&file, filename, "w")) {
		CS::instance()->leave(CS_LOG_CS, "saveitem");
		CS::instance()->leave(CS_LOAD_CS, "enter");
		return;
	}

	fclose(file);
	int tempp = 0;
	for (int i = 0; i < size; i++) {
		if (!myitem[i]->is_erased()) {
			tempp++;
		}
	}
	
	mylog::writelog(filename, "%d;\n", tempp);
	for (int i = 0; i < size; i++) {
		if (!myitem[i]->is_erased()) {
			mylog::writelog(filename, "{\n");
			mylog::writelog(filename, "pindex=%d;\n", myitem[i]->parts_node_index);
			mylog::writelog(filename, "metadata_filename=\"%s\";\n", myitem[i]->metadata_filename.c_str());
			mylog::writelog(filename, "parts_filename=\"%s\";\n", myitem[i]->parts_filename.c_str());
			mylog::writelog(filename, "category=%d;\n", (int)myitem[i]->category);
			mylog::writelog(filename, "itemID=%d;\n", myitem[i]->item->getItemId());
			mylog::writelog(filename, "partsID=%d;\n", myitem[i]->item->getPartsId());
			mylog::writelog(filename, "}\n");
		}
	}
	CS::instance()->leave(CS_LOG_CS, "saveitem");
	CS::instance()->leave(CS_LOAD_CS, "enter");
}


void UserData::loadItemFile() {
	FILE* file;
	const char* filename = "userdata/item.mydat";

	CS::instance()->enter(CS_LOG_CS, "loaditem");
	if (0 != fopen_s(&file, filename, "r")) {
		CS::instance()->leave(CS_LOG_CS, "loaditem");
		return;
	}

	fclose(file);
	CS::instance()->leave(CS_LOG_CS, "loaditem");
	// あるので
	MyTokenAnalyzer ma;
	item_max_id = 0;
	if (ma.load(filename)) {
		int itemmax = ma.GetIntToken();
		int temp_i = 0;
		while (!ma.enddayo() && (temp_i < itemmax)) {
			ma.GetToken("{");
			ma.GetToken("pindex");
			int pindex = ma.GetIntToken();
			ma.GetToken("metadata_filename");
			char metadata_filename[1024];
			memset(metadata_filename, 0, 1024);
			ma.GetToken();
			mystrcpy(metadata_filename, 1024, 0, ma.Toke());

			ma.GetToken("parts_filename");
			char parts_filename[1024];
			memset(parts_filename, 0, 1024);
			ma.GetToken();
			mystrcpy(parts_filename, 1024, 0, ma.Toke());
			ma.GetToken("category");
			int category = ma.GetIntToken();
			ma.GetToken("itemID");
			int item_id = ma.GetIntToken();

			if (item_id > item_max_id) {
				item_max_id = item_id;
			}

			ma.GetToken("partsID");
			int parts_id = ma.GetIntToken();

			ItemWithCategory* ic = new ItemWithCategory();
			ic->item = new Item(item_id,parts_id);
			ic->metadata_filename = metadata_filename;
			ic->parts_filename = parts_filename;
			ic->parts_node_index = pindex;
			ic->category = (ShopParts::PartsListCategory)category;
			item_id_to_index_map.insert(pair<int, int>(item_id, myitem.size()));
			myitem.push_back(ic);
			ma.GetToken("}");
			temp_i++;


		}

		ma.deletedayo();
		item_max_id++;
	}
}
void AsmRobo::changeToThisAsm(AsmRobo* srca) {
	this->arm = srca->arm;
	this->body = srca->body;
	this->booster = srca->booster;
	this->engine = srca->engine;
	this->fcs = srca->fcs;
	this->head = srca->head;
	this->leg = srca->leg;
	this->inside_weapon = srca->inside_weapon;
	this->rarm_weapon = srca->rarm_weapon;
	this->rshoulder_weapon = srca->rshoulder_weapon;
	this->lshoulder_weapon = srca->lshoulder_weapon;
	this->larm_weapon = srca->larm_weapon;
	reset();
}
void AsmBody::changeToThisAsm(AsmBody* src) {
	if (src) {
		this->arobo.changeToThisAsm(&src->arobo);
		this->is_use = src->is_use;
		reset();
	}
}
ShopParts::PartsListCategory AsmRobo::getLegCategory() {
	if (leg) {
		return leg->category;
	}
	return ShopParts::PartsListCategory::UNKNOWN;
}
bool AsmBody::calc(Robo* robo, Graphics* g, MyTextureLoader* loader) {
	bool t  = arobo.hanneiItemToRobo(robo,g, loader);
	if (!t) return false;

	// rank 付けの仕方については　パラメータ調整をしてから考える
	sougou_rank = S;
	kidou_rank = B;
	soukou_rank = A;
	attack_rank = C;

	ShopParts::PartsListCategory cc = arobo.getLegCategory();
	switch (cc) {
	case ShopParts::PartsListCategory::LEG_j2:
			leg = LEG_J2;
			break;
	case ShopParts::PartsListCategory::LEG_k2:
		leg = LEG_K2;
		break;
	case ShopParts::PartsListCategory::LEG_t2:
		leg = LEG_T2;
		break;
	case ShopParts::PartsListCategory::LEG_4:
		leg = LEG_4;
		break;
	case ShopParts::PartsListCategory::LEG_REVERSE:
		leg = LEG_REVERSE;
		break;
	case ShopParts::PartsListCategory::LEG_tank:
		leg = LEG_TANK;
		break;
	default:
		leg = LEG_K2;


	}

	setHyoukaName();
	setLoaded();
	return true;





}

void AsmBody::setHyoukaName() {
	// hyouka_name に　評価の文字列をセットする
	// 特化　か　汎用　近接かそうでないか　完璧かそうでないか　狙撃かそうでないか
	string hy = "";

	if (sougou_rank <= AsmBody::AsmRank::B) {
		// 高性能にする
		hy = hy + "高性能";
	}

	if (weapon == WeaponType::KINSETU) {
		hy = hy + "近接";
	}
	else if (weapon == WeaponType::SOGEKI) {
		hy = hy + "狙撃";
	}
	else if (weapon == WeaponType::MISSILE) {
		hy = hy + "ミサイル";
	}



	
	if ((attack_rank <= AsmBody::AsmRank::B) &&
		(soukou_rank <= AsmBody::AsmRank::B) &&
		(kidou_rank <= AsmBody::AsmRank::B)) {
		hy = hy + "汎用型";

	}else if ((attack_rank <= AsmBody::AsmRank::A) &&
		(soukou_rank >= AsmBody::AsmRank::C) &&
		(kidou_rank >= AsmBody::AsmRank::C)
		) {
		hy = hy + "攻撃特化";
	}else if ((attack_rank >= AsmBody::AsmRank::C) &&
		(soukou_rank <= AsmBody::AsmRank::A) &&
		(kidou_rank >= AsmBody::AsmRank::C)
		) {
		hy = hy + "防御特化";
	}else if ((attack_rank >= AsmBody::AsmRank::C) &&
		(soukou_rank >= AsmBody::AsmRank::C) &&
		(kidou_rank <= AsmBody::AsmRank::A)
		) {
		hy = hy + "機動特化";
	}
	else if ((attack_rank >= AsmBody::AsmRank::E) ||
		(soukou_rank >= AsmBody::AsmRank::E) ||
		(kidou_rank >= AsmBody::AsmRank::E)) {
		hy = hy + "ポンコツ型";
	}
	else {
		hy = hy + "量産型";
	}


	if (leg == LegType::LEG_K2) {
		hy = hy + "軽量二脚";
	}
	else if (leg == LegType::LEG_T2) {
		hy = hy + "中量二脚";
	}
	else if (leg == LegType::LEG_J2) {
		hy = hy + "重量二脚";
	}
	else if (leg == LegType::LEG_REVERSE) {
		hy = hy + "逆関節";
	}
	else if (leg == LegType::LEG_4) {
		hy = hy + "四脚";
	}
	else if (leg == LegType::LEG_TANK) {
		hy = hy + "タンク";
	}


	hyouka_name = hy;

}

bool UserData::buyItemInShop(RoboParts* parts, ShopParts::PartsListCategory category) {
	if (!parts) return false;
	if (myitem.size() >= KTROBO_USERDATA_ITEM_MAX) return false;

	int daikin = parts->data->getData("PRICE")->int_data;
	if (gold < daikin) {
		return false;
	}
	if (parts->getFilenameSet()) {
		ItemWithCategory* ii = new ItemWithCategory();
		ii->category = category;
		ii->metadata_filename = parts->getMetadataFilename();
		ii->parts_filename = parts->getPartsFilename();
		ii->parts_node_index = parts->getPIndex();
		

		Item* newite = new Item(this->myitem.size(),parts->data->getData("id")->int_data);
		//newite->init(parts); // item のパーツは個々にロードする
		ii->item = newite;
		item_id_to_index_map.insert(pair<int, int>(item_max_id, myitem.size()));
		myitem.push_back(ii);
		item_max_id++;
		
	}
	else {
		mylog::writelog(KTROBO::WARNING, "parts filename no set\n");
		return false;
	}

	gold = gold - daikin;
	saveItemFile();
	return true;

}


void ShopParts::atoload(Graphics* g) {
	// meshパーツのロード

	int sz = parts_list.size();

	for (int i = 0; i < sz; i++) {
		if (!parts_list[i]->hasMeshLoaded()) {
			parts_list[i]->loadMesh(g, tex_loader);
		}
	}
	setLoaded();

}
void ShopParts::loadInside(Graphics* g) {
	

	char* mdfile[] = {
		"resrc/ktrobo/info/metadata/inside/ktroboinsidedecoymetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsideenergyzoufukumetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsidejyamarocketmetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsidekiraimetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsidepartsaddmissilemetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsidepartsapkaifukumetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsidepartsbitmetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsiderocketmetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsidestealthmetadata.txt",
		"resrc/ktrobo/info/metadata/inside/ktroboinsidesubcomputermetadata.txt" };
	char* dfile[] = {
		"resrc/ktrobo/info/inside/ktroboinsidedecoy.txt",
		"resrc/ktrobo/info/inside/ktroboinsideenergyzoufuku.txt",
		"resrc/ktrobo/info/inside/ktroboinsidejyamarocket.txt",
		"resrc/ktrobo/info/inside/ktroboinsidekirai.txt",
		"resrc/ktrobo/info/inside/ktroboinsideaddmissile.txt",
		"resrc/ktrobo/info/inside/ktroboinsideapkaifuku.txt",
		"resrc/ktrobo/info/inside/ktroboinsidebit.txt",
		"resrc/ktrobo/info/inside/ktroboinsiderocket.txt",
		"resrc/ktrobo/info/inside/ktroboinsidestealth.txt",
		"resrc/ktrobo/info/inside/ktroboinsidesubcomputer.txt" };
	for (int i = 0; i < 10; i++) {
		MyTokenAnalyzer ma;
		{
			ma.load(mdfile[i]);
			RoboDataMetaData* head_md = new RoboDataMetaData();
			RoboMetaDataPart rmdp;
			rmdp.clear();
			int dnum = ma.GetIntToken();
			for (int i = 0; i < dnum; i++) {
				rmdp.clear();
				rmdp.readline(&ma);
				head_md->setData(rmdp.data_name, rmdp.data_name2, rmdp.data_type, rmdp.data_sentence, rmdp.data_compare);
			}

			ma.deletedayo();
			int pindex = 0;
			ma.load(dfile[i]);
			while (!ma.enddayo()) {
				RoboParts* head = constructParts(category);
				try {
					head->init(&ma, head_md, g, tex_loader,false);
					head->setFilenameAndIndex(pindex, dfile[i], mdfile[i]);
				}
				catch (GameError* err) {
					if (err->getErrorCode() == KTROBO::WARNING) {
						delete err;
						head->Release();
						delete head;
						continue;
					}
					//	MessageBoxA(g->getHWND(), err->getMessage(), err->getErrorCodeString(err->getErrorCode()), MB_OK);
					delete head_md;
					ma.deletedayo();
					throw err;
				}
				
				this->parts_list.push_back(head);
				this->meta_datas.push_back(head_md);
				pindex++;
			//	ma.SkipNode();
			}
			ma.deletedayo();
			//delete head_md;
			iden_meta_datas.push_back(head_md);
		}
		
	}

}
RoboParts* ShopParts::constructParts(ShopParts::PartsListCategory category) {
	if (category == ShopParts::PartsListCategory::HEAD) {
		return new RoboHead();
	}

	if (category == ShopParts::PartsListCategory::BODY) {
		return new RoboBody();
	}

	if (category == ShopParts::PartsListCategory::ARM) {
		return new RoboArm();
	}

	if ((category >= ShopParts::PartsListCategory::LEG_START) && (category <= ShopParts::PartsListCategory::LEG_END)) {
		return new RoboLeg();
	}

	if ((category >= ShopParts::PartsListCategory::LARMWEAPON_START) && (category <= ShopParts::PartsListCategory::LARMWEAPON_END)) {
		return new LArmWeapon();
	}

	if ((category >= ShopParts::PartsListCategory::RARMWEAPON_START) && (category <= ShopParts::PartsListCategory::RARMWEAPON_END)) {
		return new RArmWeapon();
	}
	if ((category >= ShopParts::PartsListCategory::RKATAWEAPON_START) && (category <= ShopParts::PartsListCategory::RKATAWEAPON_END)) {		
		return new RShoulderWeapon();
	}
	if ((category >= ShopParts::PartsListCategory::LKATAWEAPON_START) && (category <= ShopParts::PartsListCategory::LKATAWEAPON_END)) {		
		return new LShoulderWeapon();
	}

	if (category == ShopParts::PartsListCategory::BOOSTER) {
		return new RoboBooster();
	}
	if (category == ShopParts::PartsListCategory::FCS) {
		return new RoboFCS();
	}
	if (category == ShopParts::PartsListCategory::ENGINE) {
		return new RoboEngine();
	}
	if (category == ShopParts::PartsListCategory::INSIDE_WEAPON) {
		return new InsideWeapon();
	}

	mylog::writelog(KTROBO::WARNING, "threre is no metadata");
	return new RoboHead();

}
void ShopParts::load(Graphics* g) {

	// inside の場合は複数のファイルを呼ぶ
	if (category == ShopParts::PartsListCategory::INSIDE_WEAPON) {
		loadInside(g);
		return;
	}
	char* mdfile = getMetaDataName();
	char* dfile = getDataName();

	MyTokenAnalyzer ma;
	{
		ma.load(mdfile);
		RoboDataMetaData* head_md = new RoboDataMetaData();
		RoboMetaDataPart rmdp;
		rmdp.clear();
		int dnum = ma.GetIntToken();
		for (int i = 0; i < dnum; i++) {
			rmdp.clear();
			rmdp.readline(&ma);
			head_md->setData(rmdp.data_name, rmdp.data_name2, rmdp.data_type, rmdp.data_sentence, rmdp.data_compare);
		}

		ma.deletedayo();
		int pindex = 0;
		ma.load(dfile);
		while (!ma.enddayo()) {
			RoboParts* head = constructParts(category);
			try {
				head->init(&ma, head_md, g, tex_loader,false);
				head->setFilenameAndIndex(pindex, dfile, mdfile);
			}
			catch (GameError* err) {
				if (err->getErrorCode() == KTROBO::WARNING) {
					delete err;
					head->Release();
					delete head;
					continue;
				}
				//	MessageBoxA(g->getHWND(), err->getMessage(), err->getErrorCodeString(err->getErrorCode()), MB_OK);
				delete head_md;
				ma.deletedayo();
				throw err;
			}
		
			this->parts_list.push_back(head);
			meta_datas.push_back(head_md);
			pindex++;
			//ma.SkipNode();
		}
		ma.deletedayo();
		//delete head_md;
		iden_meta_datas.push_back(head_md);
	}
	


	



}


char* ShopParts::getMetaDataName() {
	// inside は個別に対応する

	if (category == ShopParts::PartsListCategory::HEAD) {
		return "resrc/ktrobo/info/metadata/ktroboheadpartsmetadata.txt";
	}

	if (category == ShopParts::PartsListCategory::BODY) {
		return "resrc/ktrobo/info/metadata/ktrobocorepartsmetadata.txt";
	}


	if (category == ShopParts::PartsListCategory::ARM) {
		return "resrc/ktrobo/info/metadata/ktroboarmpartsmetadata.txt";
	}

	if ((category >= ShopParts::PartsListCategory::LEG_START) && (category <= ShopParts::PartsListCategory::LEG_END)) {
		return "resrc/ktrobo/info/metadata/ktrobolegpartsmetadata.txt";
	}

	if ((category >= ShopParts::PartsListCategory::LARMWEAPON_START) && (category <= ShopParts::PartsListCategory::LARMWEAPON_END)) {

		if (category == ShopParts::PartsListCategory::LARMWEAPON_BLADE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponblademetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_ENERGYBLADE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponblademetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_PILE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponpilemetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_MISSILE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponyuudoumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_GRENEDE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponbakuhatumetadata.txt";
		}

		return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponmetadata.txt";
	}

	if ((category >= ShopParts::PartsListCategory::RARMWEAPON_START) && (category <= ShopParts::PartsListCategory::RARMWEAPON_END)) {


		if (category == ShopParts::PartsListCategory::RARMWEAPON_BLADE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponblademetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RARMWEAPON_ENERGYBLADE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponblademetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RARMWEAPON_PILE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponpilemetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RARMWEAPON_MISSILE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponyuudoumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RARMWEAPON_GRENEDE) {
			return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponbakuhatumetadata.txt";
		}
		return "resrc/ktrobo/info/metadata/weapon/ktrobopartsweaponmetadata.txt";
	}
	if ((category >= ShopParts::PartsListCategory::RKATAWEAPON_START) && (category <= ShopParts::PartsListCategory::RKATAWEAPON_END)) {

		if (category == ShopParts::PartsListCategory::RKATAWEAPON_GRENEDE) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RKATAWEAPON_PULSE) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RKATAWEAPON_RASER) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RKATAWEAPON_PLAZUMA) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::RKATAWEAPON_MISSILE) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatamissilemetadata.txt";
		}
		return "resrc/ktrobo/info/metadata/kata/ktrobopartskatametadata.txt";
	}
	if ((category >= ShopParts::PartsListCategory::LKATAWEAPON_START) && (category <= ShopParts::PartsListCategory::LKATAWEAPON_END)) {

		if (category == ShopParts::PartsListCategory::LKATAWEAPON_GRENEDE) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LKATAWEAPON_PULSE) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LKATAWEAPON_RASER) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LKATAWEAPON_PLAZUMA) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatabakuhatumetadata.txt";
		}
		if (category == ShopParts::PartsListCategory::LKATAWEAPON_MISSILE) {
			return "resrc/ktrobo/info/metadata/kata/ktrobopartskatamissilemetadata.txt";
		}
		return "resrc/ktrobo/info/metadata/kata/ktrobopartskatametadata.txt";
	}

	if (category == ShopParts::PartsListCategory::BOOSTER) {
		return "resrc/ktrobo/info/metadata/ktroboboosterpartsmetadata.txt";
	}
	if (category == ShopParts::PartsListCategory::FCS) {
		return "resrc/ktrobo/info/metadata/ktrobofcspartsmetadata.txt";
	}
	if (category == ShopParts::PartsListCategory::ENGINE) {
		return "resrc/ktrobo/info/metadata/ktroboenginepartsmetadata.txt";
	}



	mylog::writelog(KTROBO::WARNING, "threre is no metadata");
	return "test";
}


char* ShopParts::getDataName() {
	if (category == ShopParts::PartsListCategory::ARM) {
		return "resrc/ktrobo/info/ktroboarmparts.txt";
	}
	if (category == ShopParts::PartsListCategory::BODY) {
		return "resrc/ktrobo/info/ktrobocoreparts.txt";
	}
	if (category == ShopParts::PartsListCategory::BOOSTER) {
		return "resrc/ktrobo/info/ktroboboosterparts.txt";
	}
	if (category == ShopParts::PartsListCategory::ENGINE) {
		return "resrc/ktrobo/info/ktroboengineparts.txt";
	}
	if (category == ShopParts::PartsListCategory::FCS) {
		return "resrc/ktrobo/info/ktrobofcsparts.txt";
	}
	if (category == ShopParts::PartsListCategory::HEAD) {
		return "resrc/ktrobo/info/ktroboheadparts.txt";
	}
	if (category == ShopParts::PartsListCategory::LEG_4) {
		return "resrc/ktrobo/info/leg/ktroboleg4k.txt";
	}
	if (category == ShopParts::PartsListCategory::LEG_j2) {
		return "resrc/ktrobo/info/leg/ktrobolegj2.txt";
	}
	if (category == ShopParts::PartsListCategory::LEG_k2) {
		return "resrc/ktrobo/info/leg/ktrobolegk2.txt";
	}
	if (category == ShopParts::PartsListCategory::LEG_REVERSE) {
		return "resrc/ktrobo/info/leg/ktrobolegr.txt";
	}
	if (category == ShopParts::PartsListCategory::LEG_t2) {
		return "resrc/ktrobo/info/leg/ktrobolegt2.txt";
	}
	if (category == ShopParts::PartsListCategory::LEG_tank) {
		return "resrc/ktrobo/info/leg/ktrobolegtk.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_CHAINGUN) {
		return "resrc/ktrobo/info/lkata/ktrobolkatachaingun.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_GRENEDE) {
		return "resrc/ktrobo/info/lkata/ktrobolkatagrenede.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_HANABI) {
		return "resrc/ktrobo/info/lkata/ktrobolkatahanabi.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_MISSILE) {
		return "resrc/ktrobo/info/lkata/ktrobolkatamissile.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_PLAZUMA) {
		return "resrc/ktrobo/info/lkata/ktrobolkataplazuma.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_PULSE) {
		return "resrc/ktrobo/info/lkata/ktrobolkatapulse.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_RASER) {
		return "resrc/ktrobo/info/lkata/ktrobolkataraser.txt";
	}
	if (category == ShopParts::PartsListCategory::LKATAWEAPON_ROCKET) {
		return "resrc/ktrobo/info/lkata/ktrobolkatarocket.txt";
	}

	if (category == ShopParts::PartsListCategory::RKATAWEAPON_CHAINGUN) {
		return "resrc/ktrobo/info/rkata/ktroborkatachaingun.txt";
	}
	if (category == ShopParts::PartsListCategory::RKATAWEAPON_GRENEDE) {
		return "resrc/ktrobo/info/rkata/ktroborkatagrenede.txt";
	}
	if (category == ShopParts::PartsListCategory::RKATAWEAPON_HANABI) {
		return "resrc/ktrobo/info/rkata/ktroborkatahanabi.txt";
	}
	if (category == ShopParts::PartsListCategory::RKATAWEAPON_MISSILE) {
		return "resrc/ktrobo/info/rkata/ktroborkatamissile.txt";
	}
	if (category == ShopParts::PartsListCategory::RKATAWEAPON_PLAZUMA) {
		return "resrc/ktrobo/info/rkata/ktroborkataplazuma.txt";
	}
	if (category == ShopParts::PartsListCategory::RKATAWEAPON_PULSE) {
		return "resrc/ktrobo/info/rkata/ktroborkatapulse.txt";
	}
	if (category == ShopParts::PartsListCategory::RKATAWEAPON_RASER) {
		return "resrc/ktrobo/info/rkata/ktroborkataraser.txt";
	}
	if (category == ShopParts::PartsListCategory::RKATAWEAPON_ROCKET) {
		return "resrc/ktrobo/info/rkata/ktroborkatarocket.txt";
	}

	if (category == ShopParts::PartsListCategory::RARMWEAPON_BAZOOKA) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponbazooka.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_BLADE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponblade.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_ENERGYBLADE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponenergyblade.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_ENERGYRIFLE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponenergyrifle.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_GRENEDE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweapongrenede.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_HANABIGUN) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponhanabigun.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_HANDGUN) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponhandgun.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_MACHINEGUN) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponmachinegun.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_MISSILE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponmissile.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_PILE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponpile.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_PLAZUMAGUN) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponplazumagun.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_PULSEGUN) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponpulsegun.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_RIFLE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponrifle.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_ROCKET) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponrocket.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_SHOTGUN) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponshotgun.txt";
	}
	if (category == ShopParts::PartsListCategory::RARMWEAPON_SNIPERRIFLE) {
		return "resrc/ktrobo/info/rweapon/ktroborarmweaponsniperrifle.txt";
	}


	if (category == ShopParts::PartsListCategory::LARMWEAPON_BAZOOKA) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponbazooka.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_BLADE) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponblade.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_ENERGYBLADE) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponenergyblade.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_ENERGYRIFLE) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponenergyrifle.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_GRENEDE) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweapongrenede.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_HANABIGUN) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponhanabigun.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_HANDGUN) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponhandgun.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_MACHINEGUN) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponmachinegun.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_MISSILE) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponmissile.txt";
	}
	if (category == ShopParts::PartsListCategory::LARMWEAPON_PILE) {
		return "resrc/ktrobo/info/lweapon/ktrobolarmweaponpile.txt";
	}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_PLAZUMAGUN) {
			return "resrc/ktrobo/info/lweapon/ktrobolarmweaponplazumagun.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_PULSEGUN) {
			return "resrc/ktrobo/info/lweapon/ktrobolarmweaponpulsegun.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_RIFLE) {
			return "resrc/ktrobo/info/lweapon/ktrobolarmweaponrifle.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_ROCKET) {
			return "resrc/ktrobo/info/lweapon/ktrobolarmweaponrocket.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_SHOTGUN) {
			return "resrc/ktrobo/info/lweapon/ktrobolarmweaponshotgun.txt";
		}
		if (category == ShopParts::PartsListCategory::LARMWEAPON_SNIPERRIFLE) {
			return "resrc/ktrobo/info/lweapon/ktrobolarmweaponsniperrifle.txt";
		}

	
	mylog::writelog(KTROBO::WARNING, "there is no parts datafile");
	return "test";
}


void ItemWithCategory::loadRoboParts(Graphics* g, MyTextureLoader* tex_loader) {
	if (this->item&& !this->hasLoaded()) {
		const char* mdfile = this->metadata_filename.c_str();
		const char* dfile = this->parts_filename.c_str();

		MyTokenAnalyzer ma;
		{
			ma.load(mdfile);
			RoboDataMetaData* head_md = new RoboDataMetaData();
			RoboMetaDataPart rmdp;
			rmdp.clear();
			int dnum = ma.GetIntToken();
			for (int i = 0; i < dnum; i++) {
				rmdp.clear();
				rmdp.readline(&ma);
				head_md->setData(rmdp.data_name, rmdp.data_name2, rmdp.data_type, rmdp.data_sentence, rmdp.data_compare);
			}

			ma.deletedayo();
			
			ma.load(dfile);
			while (!ma.enddayo()) {

				for (int i = 0; i < this->parts_node_index; i++) {
				//	ma.GetToken();
					ma.SkipNode();
				}

				RoboParts* head = ShopParts::constructParts(this->category);
				try {
					head->init(&ma, head_md, g, tex_loader, false);
					head->setFilenameAndIndex(parts_node_index, dfile, mdfile);
				}
				catch (GameError* err) {
					if (err->getErrorCode() == KTROBO::WARNING) {
						delete err;
						head->Release();
						delete head;
						continue;
					}
					//	MessageBoxA(g->getHWND(), err->getMessage(), err->getErrorCodeString(err->getErrorCode()), MB_OK);
					delete head_md;
					ma.deletedayo();
					throw err;
				}
				this->item->setParts(head);
				delete head_md;
				break;
				//this->parts_list.push_back(head);
				//meta_datas.push_back(head_md);
				//pindex++;
				//ma.SkipNode();
			}
			ma.deletedayo();
			//delete head_md;
			//iden_meta_datas.push_back(head_md);
		}

		//item->loadRoboParts(g, tex_loader);
		setLoaded();

	}


}
RoboParts* Item::getLoadedParts() {
	if (part) {
		return part;
		/*
		if (this->hasLoaded()) {
			return part;
		}
		else {
			return part;
			mylog::writelog(KTROBO::INFO, "there is yet loaded part in item equip\n");
		}
		*/
	}
	else {
		mylog::writelog(KTROBO::WARNING, "there is no part in item equip\n");
	}

	return 0;

}
bool Item::equip(Robo* robo, Graphics* g, MyTextureLoader* loader) {
	if (part) {
		if (part->hasMeshLoaded()) {
			part->equipRobo(robo, g, loader);
			return true;
		}
		else {
			mylog::writelog(KTROBO::WARNING, "there is yet loaded part in item equip\n");
			return false;
		}
	}
	else {
		mylog::writelog(KTROBO::WARNING, "there is no part in item equip\n");
		return false;
	}
}
void Item::loadRoboParts(Graphics* g, MyTextureLoader* loader) {
	if (part) {
		if (!hasLoaded()) {
			//Sleep(2000);
			part->loadMesh(g, loader);
		}
		setLoaded();
	}
	else {
		mylog::writelog(KTROBO::WARNING, "there is no part in item\n");
		throw new GameError(KTROBO::FATAL_ERROR, "no item\n");
	}
}

void AsmRobo::setItemWithCategory(ItemWithCategory* i) {
	if (!i) return;
	if (i->item && i->item->isEmpty()) return;
	if (!i->item) return;

	switch (i->category) {
	case ShopParts::PartsListCategory::ARM:
		arm = i;
		break;
	case ShopParts::PartsListCategory::BODY:
		body = i;
		break;
	case ShopParts::PartsListCategory::BOOSTER:
		booster = i;
		break;
	case ShopParts::PartsListCategory::ENGINE:
		engine = i;
		break;
	case ShopParts::PartsListCategory::FCS:
		fcs = i;
		break;
	case ShopParts::PartsListCategory::HEAD:
		head = i;
		break;
	case ShopParts::PartsListCategory::INSIDE_WEAPON:
		inside_weapon = i;
		break;
	default:
		if ((i->category >= ShopParts::PartsListCategory::LEG_START) && (i->category <= ShopParts::PartsListCategory::LEG_END)) {
			leg = i;
		}
		if ((i->category >= ShopParts::PartsListCategory::LARMWEAPON_START) && (i->category <= ShopParts::PartsListCategory::LARMWEAPON_END)) {
			larm_weapon = i;
		}
		if ((i->category >= ShopParts::PartsListCategory::RARMWEAPON_START) && (i->category <= ShopParts::PartsListCategory::RARMWEAPON_END)) {
			rarm_weapon = i;
		}
		if ((i->category >= ShopParts::PartsListCategory::LKATAWEAPON_START) && (i->category <= ShopParts::PartsListCategory::LKATAWEAPON_END)) {
			lshoulder_weapon = i;
		}
		if ((i->category >= ShopParts::PartsListCategory::RKATAWEAPON_START) && (i->category <= ShopParts::PartsListCategory::RKATAWEAPON_END)) {
			rshoulder_weapon = i;
		}

	}
	reset(); // loadedのフラグをリセットする

}
void AsmRobo::loadItems(Graphics* g, MyTextureLoader* loader) {
	if (hasLoaded()) return;
	if (head && head->item) {
		if (!head->hasLoaded()) {
			head->loadRoboParts(g, loader);

		}
		if (!head->item->hasLoaded()) {
			head->item->loadRoboParts(g, loader);
		}
	}

	if (body && body->item) {
		if (!body->hasLoaded()) {
			body->loadRoboParts(g, loader);
		}
		if (!body->item->hasLoaded()) {
			body->item->loadRoboParts(g, loader);
		}
	}

	if (arm && arm->item) {
		if (!arm->hasLoaded()) {
			arm->loadRoboParts(g, loader);
		}
		if (!arm->item->hasLoaded()) {
			arm->item->loadRoboParts(g, loader);
		}
	}

	if (leg && leg->item) {
		if (!leg->hasLoaded()) {
			leg->loadRoboParts(g, loader);
		}
		if (!leg->item->hasLoaded()) {
			leg->item->loadRoboParts(g, loader);
		}
	}

	if (this->booster && booster->item) {
		if (!booster->hasLoaded()) {
			booster->loadRoboParts(g, loader);
		}
		if (!booster->item->hasLoaded()) {
			booster->item->loadRoboParts(g, loader);
		}
	}

	if (engine && engine->item) {
		if (!engine->hasLoaded()) {
			engine->loadRoboParts(g, loader);
		}
		if (!engine->item->hasLoaded()) {
			engine->item->loadRoboParts(g, loader);
		}
	}

	if (fcs && fcs->item) {
		if (!fcs->hasLoaded()) {
			fcs->loadRoboParts(g, loader);
		}
		if (!fcs->item->hasLoaded()) {
			fcs->item->loadRoboParts(g, loader);
		}
	}

	if (rarm_weapon && rarm_weapon->item) {
		if (!rarm_weapon->hasLoaded()) {
			rarm_weapon->loadRoboParts(g, loader);
		}
		if (!rarm_weapon->item->hasLoaded()) {
			rarm_weapon->item->loadRoboParts(g, loader);
		}
	}
	if (larm_weapon && larm_weapon->item) {
		if (!larm_weapon->hasLoaded()) {
			larm_weapon->loadRoboParts(g, loader);
		}
		if (!larm_weapon->item->hasLoaded()) {
			larm_weapon->item->loadRoboParts(g, loader);
		}
	}

	if (lshoulder_weapon && lshoulder_weapon->item) {
		if (!lshoulder_weapon->hasLoaded()) {
			lshoulder_weapon->loadRoboParts(g, loader);
		}
		if (!lshoulder_weapon->item->hasLoaded()) {
			lshoulder_weapon->item->loadRoboParts(g, loader);
		}
	}
	if (rshoulder_weapon && rshoulder_weapon->item) {
		if (!rshoulder_weapon->hasLoaded()) {
			rshoulder_weapon->loadRoboParts(g, loader);
		}
		if (!rshoulder_weapon->item->hasLoaded()) {
			rshoulder_weapon->item->loadRoboParts(g, loader);
		}

	}

	if (inside_weapon) {
		if (!inside_weapon->hasLoaded()) {
			inside_weapon->loadRoboParts(g, loader);
		}
		if (!inside_weapon->item->hasLoaded()) {
			inside_weapon->item->loadRoboParts(g, loader);
		}

	}

	setLoaded();
}
bool AsmRobo::hanneiItemToRobo(Robo* robo, Graphics* g, MyTextureLoader* loader) {
	if (robo) {
		// inside rarm larm rkata lkata のみ　0になってるときに外す
		// ほかの部位に関しては　元のままにする
		if (!rarm_weapon) {
			RoboPartsEmpty emp;
			emp.emptyRArmWeapon(robo, true);
		}
		if (!larm_weapon) {
			RoboPartsEmpty emp;
			emp.emptyLArmWeapon(robo, true);
		}

		if (!lshoulder_weapon) {
			RoboPartsEmpty emp;
			emp.emptyLShoulderWeapon(robo, true);
		}
		if (!rshoulder_weapon) {
			RoboPartsEmpty emp;
			emp.emptyRShoulderWeapon(robo, true);
		}

		if (!inside_weapon) {
			RoboPartsEmpty emp;
			emp.emptyInsideWeapon(robo, true);
		}

		if (head) {
			if (head->hasLoaded()) {
				head->item->equip(robo,g,loader);
			}
			else {
				return false;
			}
		}

		if (body) {
			if (body->hasLoaded()) {
				body->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (arm) {
			if (arm->hasLoaded()) {
				arm->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (leg) {
			if (leg->hasLoaded()) {
				leg->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (this->booster) {
			if (booster->hasLoaded()) {
				booster->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (engine) {
			if (engine->hasLoaded()) {
				engine->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (fcs) {
			if (fcs->hasLoaded()) {
				fcs->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (rarm_weapon) {
			if (rarm_weapon->hasLoaded()) {
				rarm_weapon->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}
		if (larm_weapon) {
			if (larm_weapon->hasLoaded()) {
				larm_weapon->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (lshoulder_weapon) {
			if (lshoulder_weapon->hasLoaded()) {
				lshoulder_weapon->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}
		if (rshoulder_weapon) {
			if (rshoulder_weapon->hasLoaded()) {
				rshoulder_weapon->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}

		if (inside_weapon) {
			if (inside_weapon->hasLoaded()) {
				inside_weapon->item->equip(robo, g, loader);
			}
			else {
				return false;
			}
		}



	}

	return true;

}




	
	
void UserData::setItemWithCategoryToVector(vector<ItemWithCategory*>* outdayo, ShopParts::PartsListCategory category) {
	outdayo->clear();
	outdayo->push_back(&emptyitem);

	int siz = myitem.size();
	for (int i = 0; i < siz; i++) {
		if ((myitem[i]->category == category) && !myitem[i]->is_erased()) {
			outdayo->push_back(myitem[i]);
		}
	}
}

AsmBody* UserData::getAsmBody(int asm_id) {
	if ((asm_id >= 0) && (asm_id < KTROBO_USERDATA_ASMBODY_MAX)) {
		return &asms[asm_id];
	}
	return 0;
}


string AsmBody::getKidouRank() {
	return string("機動：") + getRankString(kidou_rank);
}

string AsmBody::getSougouRank() {
	return string("総合：") + getRankString(sougou_rank);
}
string AsmBody::getSoukouRank() {
	return string("装甲：") + getRankString(soukou_rank);
}
string AsmBody::getAttackRank() {
	return string("攻撃：") + getRankString(attack_rank);
}


void AsmRobo::emptyItem(ShopParts::PartsListCategory category) {
	if (category == ShopParts::PartsListCategory::INSIDE_WEAPON) {
		inside_weapon = 0;
	}
	if ((category >= ShopParts::PartsListCategory::LARMWEAPON_START) && (category <= ShopParts::PartsListCategory::LARMWEAPON_END)) {
		larm_weapon = 0;
	}
	if ((category >= ShopParts::PartsListCategory::RARMWEAPON_START) && (category <= ShopParts::PartsListCategory::RARMWEAPON_END)) {
		rarm_weapon = 0;
	}
	if ((category >= ShopParts::PartsListCategory::LKATAWEAPON_START) && (category <= ShopParts::PartsListCategory::LKATAWEAPON_END)) {
		lshoulder_weapon = 0;
	}
	if ((category >= ShopParts::PartsListCategory::RKATAWEAPON_START) && (category <= ShopParts::PartsListCategory::RKATAWEAPON_END)) {
		rshoulder_weapon = 0;
	}
	// ほかの部位は外せない
}


bool UserData::sellItemInShop(int item_id, ItemWithCategory* i) {
	// AsmBodyfileに使っているものであれば消させない
	if (i && i->item && !i->item->isEmpty()&& !i->is_erased()) {
		if (i->item->getItemId() == item_id) {

			if (this->isThisItemUsedInAllAsmBody(item_id, i)) {
				return false;
			}

			if (item_id_to_index_map.find(item_id) != item_id_to_index_map.end()) {
				myitem[item_id_to_index_map.find(item_id)->second]->erase();
				this->gold += myitem[item_id_to_index_map.find(item_id)->second]->item->getLoadedParts()->data->getData("PRICE")->int_data;
				return true;
			}
		}
	}

	return false;
}

bool AsmRobo::containsThisItem(int item_id, ItemWithCategory* c) {
	if (!c) return false;

	if ((c == head) && head->item) {
		if (item_id == head->item->getItemId()) {
			return true;
		}
	}

	if ((c == body) && body->item) {
		if (item_id == body->item->getItemId()) {
			return true;
		}
	}

	if ((c == arm) && arm->item) {
		if (item_id == arm->item->getItemId()) {
			return true;
		}
	}

	if ((c == leg) && leg->item) {
		if (item_id == leg->item->getItemId()) {
			return true;
		}
	}

	if ((c == fcs) && fcs->item) {
		if (item_id == fcs->item->getItemId()) {
			return true;
		}
	}

	if ((c == engine) && engine->item) {
		if (item_id == engine->item->getItemId()) {
			return true;
		}
	}

	if ((c == booster) && booster->item) {
		if (item_id == booster->item->getItemId()) {
			return true;
		}
	}

	if ((c == rarm_weapon) && rarm_weapon->item) {
		if (item_id == rarm_weapon->item->getItemId()) {
			return true;
		}
	}

	if ((c == larm_weapon) && larm_weapon->item) {
		if (item_id == larm_weapon->item->getItemId()) {
			return true;
		}
	}

	if ((c == rshoulder_weapon) && rshoulder_weapon->item) {
		if (item_id == rshoulder_weapon->item->getItemId()) {
			return true;
		}
	}

	if ((c == lshoulder_weapon) && lshoulder_weapon->item) {
		if (item_id == lshoulder_weapon->item->getItemId()) {
			return true;
		}
	}

	if ((c == inside_weapon) && inside_weapon->item) {
		if (item_id == inside_weapon->item->getItemId()) {
			return true;
		}
	}


	return false;

}

bool UserData::isThisItemUsedInAllAsmBody(int item_id, ItemWithCategory* i) {

	if (i && i->item && !i->item->isEmpty()) {

		for (int k = 0; k < KTROBO_USERDATA_ASMBODY_MAX; k++) {
			if (asms[k].getIsUse()) {
				if (asms[k].arobo.containsThisItem(item_id, i)) {
					return true;
				}

			}
		}

		return false;
	}

	mylog::writelog(KTROBO::WARNING, "itemusedinallasmbody okasii\n");
	return false;

}