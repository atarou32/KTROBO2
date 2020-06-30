#ifndef KTROBOCAMERAWORK_H
#define KTROBOCAMERAWORK_H

#pragma once
#include "KTRoboTexture.h"
#include "KTRoboEntity.h"
#include "KTRoboAtari.h"

namespace KTROBO {

	class CameraWork : public AtariBase
	{

		Mesh* atari_mesh;
		float roty; // -3.14 ~ 3.14 default 0
		float rotx; // 1.57 ~ -1.57 default ?
		PlayerCharacterEntity* player;
		MYVECTOR3 player_pos;
		MYVECTOR3 camera_pos; // lookfrom
		MYVECTOR3 lookat;
		MYVECTOR3 lookup;
		MYMATRIX view;
		bool is_changedrot;

		MYVECTOR3 camera_pos_now;
		MYVECTOR3 lookat_now;
	public:
		CameraWork();
		~CameraWork();

		float getRoty() { return roty; };
		float getRotx() { return rotx; };
		void setRoty(float roty);
		void setRotx(float rotx);
		
		void calculateView(); // render ‚ÅŒÄ‚Ô
		void getViewOfText(MYMATRIX* ans, MYMATRIX* text_world);
		void getView(MYMATRIX* ans);
		void setPlayerCharacter(PlayerCharacterEntity* pl) {
			player = pl;
		}
		void getLookAt(MYVECTOR3* ans);
		void getLookFrom(MYVECTOR3* ans);

	};


}

#endif