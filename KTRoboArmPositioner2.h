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
		MYVECTOR3 target; // ロボのアームが指し示す物体
		MYVECTOR3 temoto_targetpos; // ロボのアームの手部分の目標地点

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