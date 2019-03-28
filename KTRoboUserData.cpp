#include "KTRoboUserData.h"
#include "MyTextureLoader.h"

using namespace KTROBO;

UserData::UserData()
{
}


UserData::~UserData()
{
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

			ma.load(dfile[i]);
			while (!ma.enddayo()) {
				RoboParts* head = constructParts();
				try {
					head->init(&ma, head_md, g, tex_loader,false);
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
			//	ma.SkipNode();
			}
			ma.deletedayo();
			delete head_md;
		}
		
	}

}
RoboParts* ShopParts::constructParts() {
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

		ma.load(dfile);
		while (!ma.enddayo()) {
			RoboParts* head = constructParts();
			try {
				head->init(&ma, head_md, g, tex_loader,false);
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
			//ma.SkipNode();
		}
		ma.deletedayo();
		delete head_md;
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


