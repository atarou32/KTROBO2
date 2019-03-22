#include "KTRoboUserData.h"

using namespace KTROBO;

UserData::UserData()
{
}


UserData::~UserData()
{
}


void AsmBody::setHyoukaName() {
	// hyouka_name �Ɂ@�]���̕�������Z�b�g����
	// �����@���@�ėp�@�ߐڂ������łȂ����@�����������łȂ����@�_���������łȂ���
	string hy = "";

	if (sougou_rank <= AsmBody::AsmRank::B) {
		// �����\�ɂ���
		hy = hy + "�����\";
	}

	if (weapon == WeaponType::KINSETU) {
		hy = hy + "�ߐ�";
	}
	else if (weapon == WeaponType::SOGEKI) {
		hy = hy + "�_��";
	}
	else if (weapon == WeaponType::MISSILE) {
		hy = hy + "�~�T�C��";
	}



	
	if ((attack_rank <= AsmBody::AsmRank::B) &&
		(soukou_rank <= AsmBody::AsmRank::B) &&
		(kidou_rank <= AsmBody::AsmRank::B)) {
		hy = hy + "�ėp�^";

	}else if ((attack_rank <= AsmBody::AsmRank::A) &&
		(soukou_rank >= AsmBody::AsmRank::C) &&
		(kidou_rank >= AsmBody::AsmRank::C)
		) {
		hy = hy + "�U������";
	}else if ((attack_rank >= AsmBody::AsmRank::C) &&
		(soukou_rank <= AsmBody::AsmRank::A) &&
		(kidou_rank >= AsmBody::AsmRank::C)
		) {
		hy = hy + "�h�����";
	}else if ((attack_rank >= AsmBody::AsmRank::C) &&
		(soukou_rank >= AsmBody::AsmRank::C) &&
		(kidou_rank <= AsmBody::AsmRank::A)
		) {
		hy = hy + "�@������";
	}
	else if ((attack_rank >= AsmBody::AsmRank::E) ||
		(soukou_rank >= AsmBody::AsmRank::E) ||
		(kidou_rank >= AsmBody::AsmRank::E)) {
		hy = hy + "�|���R�c�^";
	}
	else {
		hy = hy + "�ʎY�^";
	}


	if (leg == LegType::LEG_K2) {
		hy = hy + "�y�ʓ�r";
	}
	else if (leg == LegType::LEG_T2) {
		hy = hy + "���ʓ�r";
	}
	else if (leg == LegType::LEG_J2) {
		hy = hy + "�d�ʓ�r";
	}
	else if (leg == LegType::LEG_REVERSE) {
		hy = hy + "�t�֐�";
	}
	else if (leg == LegType::LEG_4) {
		hy = hy + "�l�r";
	}
	else if (leg == LegType::LEG_TANK) {
		hy = hy + "�^���N";
	}


	hyouka_name = hy;

}