#ifndef KTROBO_ARMPOSITIONER2_H
#define KTROBO_ARMPOSITIONER2_H

#pragma once
#include "KTRoboRobo.h"

namespace KTROBO {
	class ArmPositioner2
	{
	private:
		float dthetaxa;
		float dthetaya;
		float dthetaza;
		float dthetaxb;
		float dthetayb;
		float dthetazb;
		Robo* robo;
		MYVECTOR3 target; // ���{�̃A�[�����w����������
		MYVECTOR3 temoto_targetpos; // ���{�̃A�[���̎蕔���̖ڕW�n�_

		void hanneiThetaToRoboArm(bool is_migi);
	public:
		void calc(Graphics*g , MYMATRIX* view, bool is_migi);
		void setTarget(MYVECTOR3* ta) {
			target = *ta;
		};
		void setRobo(Robo* ro) {
			robo = ro;
		};

		ArmPositioner2();
		~ArmPositioner2();
	};


}

#endif