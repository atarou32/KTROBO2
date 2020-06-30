#include "KTRoboCameraWork.h"


using namespace KTROBO;

CameraWork::CameraWork()
{
	atari_mesh = 0;
	atarihan = 0;
	rotx = 0;
	roty = 0;
	player = 0;
	player_pos = MYVECTOR3(0, 0, 0);
	camera_pos = MYVECTOR3(0, 0, 100);
	lookup = MYVECTOR3(0, 0, 1);
	lookat = MYVECTOR3(0, 20, 20);
	MyMatrixLookAtRH(view, camera_pos, lookat, lookup);
	is_changedrot = false;
}


CameraWork::~CameraWork()
{
	if (atarihan) {
		delete atarihan;
		atarihan = 0;
	}
	if (atari_mesh) {
		atari_mesh->Release();
		delete atari_mesh;
		atari_mesh = 0;
	}
}
void CameraWork::setRoty(float roty) {
	if (roty < -3.14) {
		roty = -3.14;
	}
	if (roty > 3.14) {
		roty = 3.14;
	}
	this->roty = roty;
	is_changedrot = true;
}
void CameraWork::setRotx(float rotx) {
	if (rotx > 1.57) {
		rotx = 1.57;
	}
	if (rotx < -1.57) {
		rotx = -1.57;
	}
	this->rotx = rotx;
	is_changedrot = true;
}


void CameraWork::calculateView() { // render Ç≈åƒÇ‘

	// rotx roty player character ÇÃposÇ©ÇÁ
	MYVECTOR3 player_pos(0, 0, 0);
	float player_r = 30;
	if (player) {
		player_pos = MYVECTOR3(player->atarihan->x, player->atarihan->y, player->atarihan->z);
		player_r = 20;// player->atarihan->r;
		rotx = player->getCameraRotX();
		roty = player->getCameraRotY();
	}

	MYVECTOR3 camera_posvec(0, 1.41f* player_r, player_r);
	MYVECTOR3 camera_vec(0, -1, 0);
	// camera_vecÇâÒì]Ç≥ÇπÇÈÅ@rotx roty ÇÃï™ÇæÇØ
	MYMATRIX rotxmat;
	MYMATRIX rotymat;
	MyMatrixRotationX(rotxmat, rotx);
	MyMatrixRotationZ(rotymat, roty);

	MyVec3TransformNormal(camera_vec, camera_vec, rotxmat);
	MyVec3TransformNormal(camera_vec, camera_vec, rotymat);
	MyVec3TransformCoord(camera_posvec, camera_posvec, rotymat);
	float tes = roty;

	tes += 1.57f+1;
	camera_posvec.float3.z -= 1 * player_r/5;
	camera_pos = player_pos + camera_posvec;



	lookat = camera_pos + camera_vec * 50;

	MyMatrixLookAtRH(view, camera_pos, lookat, lookup);


	is_changedrot = false;
}

void CameraWork::getViewOfText(MYMATRIX* ans, MYMATRIX* text_world) {
	MYMATRIX worl = *text_world;

	MYMATRIX tem;
	MYMATRIX tem2;
	MYMATRIX mattt;
	static float test = 0;
	test += 0.3f;

	MYVECTOR3 lookaxis = lookat - camera_pos;
	MyVec3Normalize(lookaxis, lookaxis);
	MYVECTOR3 axisz(0, 0, -1);
	MYVECTOR3 crossz;
	MyVec3Cross(crossz, axisz, lookaxis);
	float len = MyVec3Length(crossz);
	float crossthet = asin(len);
	MyVec3Normalize(crossz, crossz);
	float xthet = 0;
	float zthet = 0;
	float ythet = 0;
	if (len < 0.000001) {
		if (lookaxis.float3.z < 0) {
			// ìØÇ∂
			MyMatrixRotationX(mattt, 0);
		}
		else {
			MyMatrixRotationX(mattt, 3.141592f);
			xthet = 3.1415f;
		}
	}
	else {

		MYVECTOR3 axisx(1, 0, 0);
		MYVECTOR3 axisy(0, 1, 0);
		MYVECTOR3 axisz(0, 0, 1);
		float dotx = MyVec3Dot(axisx, lookaxis);
		float doty = MyVec3Dot(axisy, lookaxis);
		float dotz = MyVec3Dot(axisz, lookaxis);
		xthet = acos(dotx);
		zthet = acos(dotz);
		ythet = acos(doty);
		MYMATRIX rotxmat;
		MYMATRIX rotymat;

		MyMatrixRotationX(rotxmat, xthet);
		MyMatrixRotationY(rotymat, ythet);

		MyMatrixMultiply(mattt, rotxmat, rotymat);




	}
	//MyMatrixRotationZ(tem, test);
	//MyMatrixScaling(tem2, test, test, test);
	//MyMatrixMultiply(tem, tem2, tem);
	//MyMatrixMultiply(worl, tem, worl);
	//MyMatrixIdentity(worl);
//		MyMatrixMultiply(worl, mattt, worl);

	MYMATRIX ken;
	MYMATRIX ken2;
	MyMatrixInverse(ken, NULL, worl);
	MyMatrixRotationAxis(ken2, crossz, crossthet);
	MYVECTOR3 unkoa(1, 0, 0);
	MYVECTOR3 unkob;
	//MyVec3Cross(unkob, ); // viewÇ…Ç®ÇØÇÈxé≤
	//MyVec3Normalize(unkob,unkob);
	MYVECTOR3 unkoca(0, 1, 0);
	MYVECTOR3 unkoca2;
	MYVECTOR3 lookyokoaxis;
	MyVec3Cross(lookyokoaxis, lookaxis, lookup);
	MyVec3Normalize(lookyokoaxis, lookyokoaxis);
	MyVec3TransformNormal(unkob, unkoa, ken2);
	MyVec3TransformNormal(unkoca2, unkoca, ken2);
	MyVec3Normalize(unkob, unkob);
	MyVec3Normalize(unkoca2, unkoca2);
	MYVECTOR3 crossunko;
	MyVec3Cross(crossunko, unkoa, unkob);
	float lln = MyVec3Length(crossunko);
	float lookthet = 0;
	float offset = 0;
	if (lln < 0.0000001) {
		if (unkob.float3.y > 0) {
			lookthet = 0;
		}
		else {
			lookthet = 3.141592f;
		}
	}
	else {
		lookthet = asin(lln);

		float dd = MyVec3Dot(lookyokoaxis, unkob);
		lookthet = acos(dd);

		float dd2 = MyVec3Dot(lookup, unkoca2);

		MYVECTOR3 axx(1, 0, 0);
		MYVECTOR3 axy(0, 1, 0);
		float ddd = MyVec3Dot(axx, lookaxis);
		float ddd2 = MyVec3Dot(axy, lookaxis);


		if ((ddd > 0) && (ddd2 > 0)) {

		}
		else if ((ddd < 0) && (ddd2 > 0)) {
			lookthet = -lookthet;
		}
		else if ((ddd > 0) && (ddd2 < 0)) {

		}
		else {
			lookthet = -lookthet;
		}

		if (lookaxis.float3.z > 0) {

			//offset += 3.14f;
			lookthet = -lookthet;
		}


	}
	//			mattt = ken;
	MYMATRIX iden_mat;
	MyMatrixIdentity(iden_mat);
	MyMatrixMultiply(mattt, ken, ken2);
	if (lookaxis.float3.z > 0) {

		MyMatrixRotationX(ken2, 3.14f);
		MyMatrixMultiply(mattt, mattt, ken2);
	}
	MyMatrixRotationAxis(ken2, lookaxis, lookthet + offset);// +offset);// +tess);// 3.141592f);

	MyMatrixMultiply(mattt, mattt, ken2);
	MyMatrixMultiply(mattt, mattt, worl);
	MyMatrixMultiply(mattt, mattt, view);
	*ans = mattt;

}
void CameraWork::getView(MYMATRIX* ans) {
	*ans = view;
}

void CameraWork::getLookAt(MYVECTOR3* ans) {
	*ans = lookat;
}

void CameraWork::getLookFrom(MYVECTOR3* ans) {
	*ans = camera_pos;
}



