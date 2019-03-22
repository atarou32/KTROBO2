#include "KTRoboUserData.h"

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