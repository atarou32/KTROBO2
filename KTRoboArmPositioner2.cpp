#include "KTRoboArmPositioner2.h"
#include "MyGyouretuKeisan.h"

using namespace KTROBO;

ArmPositioner2::ArmPositioner2()
{
	dthetaxa=1.57;
	dthetaya=0;
	dthetaza=0;
	dthetaxb=0;
	dthetayb=0;
	dthetazb=0;
	robo=0;
	target = MYVECTOR3(0, 0, 0);; // ロボのアームが指し示す物体
	temoto_targetpos = MYVECTOR3(0,0,0); // ロボのアームの手部分の目標地点

}


ArmPositioner2::~ArmPositioner2()
{
}

void ArmPositioner2::hanneiThetaToRoboArm(bool is_migi) {
	MeshBone* arm1;
	MeshBone* arm2;
	MeshBone* handjoint;

	if (is_migi) {
		arm1 = robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["uparmBone"]];
		arm2 = robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["downarmBone"]];
		handjoint = robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["handBone"]];
	}
	else {
		arm1 = robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["uparmBone"]];
		arm2 = robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["downarmBone"]];
		handjoint = robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["handBone"]];
	}
	{
		MYMATRIX rotxmat;
		MYMATRIX rotymat;
		MYMATRIX rotzmat;


		if (dthetaxa < -0.37) {
			dthetaxa = -0.37;
		}
		if (dthetaxa > 3.5) {
			dthetaxa = 3.5;
		}

		if (dthetaza < -1.5) {
			dthetaza = -1.5;
		}
		if (dthetaza > 1.5) {
			dthetaza = 1.5;//0.2
		}
		if (dthetaya < 0) {
			dthetaya = 0;
		}
		if (dthetaya > 0.37) {
			dthetaya = 0.37;
		}


		MyMatrixRotationX(rotxmat, dthetaxa);
		MyMatrixRotationY(rotymat, dthetaya);
		MyMatrixRotationZ(rotzmat, dthetaza - 3.14);





		MeshBone* bn = arm2;
		float frame = 40;//this->frame;
		unsigned short ans_minmax;
		unsigned short ans_maxmin;
		float weight;
		if (is_migi) {
			robo->arm->rarm->getOffsetMatrixToGetMinMaxAndWeightIndex(bn, frame, &ans_minmax, &ans_maxmin, &weight);
		}
		else {
			robo->arm->larm->getOffsetMatrixToGetMinMaxAndWeightIndex(bn, frame, &ans_minmax, &ans_maxmin, &weight);
		}
		MYMATRIX mat1 = bn->animes[ans_minmax]->matrix_basis;
		MYMATRIX mat2 = bn->animes[ans_maxmin]->matrix_basis;
		MYMATRIX mat3;
		for (int i = 0; i < 16; i++) {
			mat2.m[i / 4][i % 4] *= weight;
			mat1.m[i / 4][i % 4] *= (1 - weight);
			mat3.m[i / 4][i % 4] = mat2.m[i / 4][i % 4] + mat1.m[i / 4][i % 4];
		}
		MYVECTOR3 v(1, 1, 1);
		WAsetScaleToMatrix(&mat3, &v);











		MYMATRIX offmat = mat3;
		//			robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["downarmBone"]]->offset_matrix;
		MyMatrixMultiply(offmat, offmat, rotzmat);
		MyMatrixMultiply(offmat, offmat, rotxmat);
		//		MyMatrixMultiply(offmat, offmat, rotymat);
		MYMATRIX ans;
		MyMatrixMultiply(ans, rotzmat, rotxmat);
		MyMatrixMultiply(ans, ans, rotymat);
		//		MyMatrixMultiply(ans, ans, trans);
		MyMatrixMultiply(ans, ans, mat3);
		//	MyMatrixIdentity(ans);
		if (is_migi) {
			robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["uparmBone"]]->offset_matrix = ans;
		}
		else {
			robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["uparmBone"]]->offset_matrix = ans;

		}
		//	robo->arm->rarm->animate(40,false);
	}

	{

		MYMATRIX rotxmat;
		MYMATRIX rotymat;
		MYMATRIX rotzmat;


		if (dthetaxb > 1.57) {
			dthetaxb = 1.57;
		}
		if (dthetaxb < -1.57) {
			dthetaxb = -1.57;
		}

		dthetayb = 0;

		if (dthetazb > 0.9) {
			dthetazb = 0.9;
		}
		if (dthetazb < -0.9) {
			dthetazb = -0.9;
		}


		MyMatrixRotationX(rotxmat, dthetaxb);
		MyMatrixRotationY(rotymat, dthetayb);
		MyMatrixRotationZ(rotzmat, dthetazb);




		//	robo->arm->rarm->animate(40,true);//
		MeshBone* bn = arm1;
		float frame = 40;//this->frame;
		unsigned short ans_minmax;
		unsigned short ans_maxmin;
		float weight;
		if (is_migi) {
			robo->arm->rarm->getOffsetMatrixToGetMinMaxAndWeightIndex(bn, frame, &ans_minmax, &ans_maxmin, &weight);
		}
		else {
			robo->arm->larm->getOffsetMatrixToGetMinMaxAndWeightIndex(bn, frame, &ans_minmax, &ans_maxmin, &weight);

		}
		MYMATRIX mat1 = bn->animes[ans_minmax]->matrix_basis;
		MYMATRIX mat2 = bn->animes[ans_maxmin]->matrix_basis;
		MYMATRIX mat3;
		for (int i = 0; i < 16; i++) {
			mat2.m[i / 4][i % 4] *= weight;
			mat1.m[i / 4][i % 4] *= (1 - weight);
			mat3.m[i / 4][i % 4] = mat2.m[i / 4][i % 4] + mat1.m[i / 4][i % 4];
		}
		MYVECTOR3 v(1, 1, 1);
		WAsetScaleToMatrix(&mat3, &v);











		MYMATRIX offmat = mat3;
		//			robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["downarmBone"]]->offset_matrix;
		MyMatrixMultiply(offmat, offmat, rotzmat);
		MyMatrixMultiply(offmat, offmat, rotxmat);
		//		MyMatrixMultiply(offmat, offmat, rotymat);
		MYMATRIX ans;
		MyMatrixMultiply(ans, rotzmat, rotxmat);
		MyMatrixMultiply(ans, ans, rotymat);
		//		MyMatrixMultiply(ans, ans, trans);
		MyMatrixMultiply(ans, ans, mat3);
		if (is_migi) {
			robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["downarmBone"]]->offset_matrix = ans;
		}
		else {
			robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["downarmBone"]]->offset_matrix = ans;

		}



	}

}


void ArmPositioner2::calc(Graphics*g, MYMATRIX* view, bool is_migi) {

	MeshBone* arm1;
	MeshBone* arm2;
	MeshBone* handjoint;

	if (is_migi) {
		arm1 = robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["uparmBone"]];
		arm2 = robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["downarmBone"]];
		handjoint = robo->arm->rarm->Bones[robo->arm->rarm->BoneIndexes["handBone"]];
	}
	else {
		arm1 = robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["uparmBone"]];
		arm2 = robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["downarmBone"]];
		handjoint = robo->arm->larm->Bones[robo->arm->larm->BoneIndexes["handBone"]];
	}


/*	if (is_migi) {
		robo->arm->rarm->animate(40, true);
	}
	else {
		robo->arm->larm->animate(40, true);
	}*/
	hanneiThetaToRoboArm(is_migi);
	if (is_migi) {
		robo->arm->rarm->animate(40, false);
	}
	else {
		robo->arm->larm->animate(40, false);
	}
	OBB ob;


	// 現在のdthetaが反映されたアーム姿勢 から　次のステップに進む
	
	MYVECTOR3 mokuhf(0, 0, 0);
	// まずmokuhfを求める
	// 現在のアームの手部分の座標地点を基にして　それより　指し示す目標地点が　左か右か　上か下か　でmokuhfを求める
	MYVECTOR3 arm1_pos(0, 0, 0);
	MYVECTOR3 arm2_pos(0, 0, 0);
	

	MYMATRIX mma;
	MyMatrixMultiply(mma, arm2->matrix_local, arm2->combined_matrix);
	MyVec3TransformCoord(arm1_pos, arm1_pos, mma);

	MyMatrixMultiply(mma, handjoint->matrix_local, handjoint->combined_matrix);
	MyVec3TransformCoord(arm2_pos, arm2_pos, mma);
	
	ob.c = arm1_pos;
	ob.e = MYVECTOR3(11, 11, 11);
	MYMATRIX iden;
	MyMatrixIdentity(iden);
	g->drawOBBFill(g, 0xFF000011, &iden, view, g->getProj(), &ob);

	ob.c = arm2_pos;
	g->drawOBBFill(g, 0xFFFFFFFF, &iden, view, g->getProj(), &ob);


	MYVECTOR3 armvec;
	MyVec3Subtract(armvec, arm2_pos, arm1_pos);
	MyVec3Normalize(armvec, armvec);
	MYVECTOR3 armvec_moku;
	MYVECTOR3 invtarget;
	MYMATRIX worldinv;
	MyMatrixInverse(worldinv, NULL, robo->atarihan->world);
	MyVec3TransformCoord(invtarget, target, worldinv);
	MyVec3Subtract(armvec_moku, invtarget, arm1_pos);
	MYVECTOR3 norm_armvec_moku;
	MyVec3Normalize(norm_armvec_moku, armvec_moku);
	MYVECTOR3 noz_armvec;
	MYVECTOR3 noz_armvec_moku;
	noz_armvec = armvec;
	noz_armvec.float3.z = 0;
	MyVec3Normalize(noz_armvec, noz_armvec);
	noz_armvec_moku = norm_armvec_moku;
	noz_armvec_moku.float3.z = 0;
	MyVec3Normalize(noz_armvec_moku, noz_armvec_moku);
	MYVECTOR3 asi;
	MyVec3Cross(asi, noz_armvec, noz_armvec_moku);
	float test = MyVec3Length(asi);
	float the = asin(test);

	RAY r;
	r.org = arm2_pos;
	MyVec3TransformCoord(r.org, r.org, robo->atarihan->world);
	r.dir = norm_armvec_moku;
	MyVec3TransformNormal(r.dir, r.dir, robo->atarihan->world);
	g->drawRAY(g, 0xFF0000FF, &iden, view, g->getProj(), 30, &r);

	r.dir = armvec;
	MyVec3TransformNormal(r.dir, r.dir, robo->atarihan->world);
	MyVec3Normalize(r.dir, r.dir);
	g->drawRAY(g, 0xFF00FFFF, &iden, view, g->getProj(), 30, &r);



	float mydot = MyVec3Dot(armvec, armvec_moku);
	if (mydot < -0.15* MyVec3Length(armvec)*MyVec3Length(armvec_moku)) {
		//見当違い
		dthetaxa = 1.57;
		dthetaxb = 0;
		dthetaya = 0;
		dthetayb = 0;
		dthetaza = 0;
		dthetazb = 0;
		/*hanneiThetaToRoboArm(is_migi);
		if (is_migi) {
			robo->arm->rarm->animate(40, false);
		}
		else {
			robo->arm->larm->animate(40, false);
		}*/
		return;
	}

	MYVECTOR3 armvec_moku_migi;
	MYVECTOR3 up(0, 0, 1);
	MyVec3Cross(armvec_moku_migi, armvec, up);
	if (MyVec3Length(armvec_moku_migi) < 0.00001) {
		// armvec_moku が 0,0,1 または　0,0,-1 になっている
		// armvec_moku のy に　0.001プラスする
		armvec.float3.y += -0.001;
		MyVec3Cross(armvec_moku_migi, armvec, up);
	}
	MyVec3Normalize(armvec_moku_migi,armvec_moku_migi);
	float dist = MyVec3Length(armvec_moku);
	float dist2 = MyVec3Length(armvec);
	// 現在指し示している　地点　と目標地点とのおおまかな距離を求める
	if ((dist2 < 0.00001) || (dist < 0.00001)) {
		mylog::writelog(KTROBO::INFO, "keisan dame");
		return;
	}
	MYVECTOR3 genzai = arm1_pos + armvec * dist / dist2;
	MYVECTOR3 sa_gen;
	MyVec3Subtract(sa_gen, invtarget, genzai);

	float migidot = MyVec3Dot(armvec_moku_migi, armvec_moku);

	volatile bool is_miginiaru = false;
	if (migidot > 0) {
		is_miginiaru = true;
	}
	MYVECTOR3 armvec_moku_ue;
	MyVec3Cross(armvec_moku_ue, armvec_moku_migi, armvec);
	MyVec3Normalize(armvec_moku_ue,armvec_moku_ue);
	float uedot = MyVec3Dot(armvec_moku_ue, armvec_moku);
	volatile bool is_ueniaru = false;
	
/*	if (uedot > 0) {
		is_ueniaru = true;
	}
*/	
	if (sa_gen.float3.z > 0) {
		is_ueniaru = true;
	}

	

	
	MYVECTOR3 sa;
	MyVec3Subtract(sa, genzai, invtarget);
	float disst = MyVec3Length(sa);
	// 動かす距離は (disst /dist * dist2 *0.5)
	//mokuhf = arm2_pos + armvec_moku_migi * (disst / dist * dist) * (migidot)*abs(migidot)/dist / dist + armvec_moku_ue * (disst / dist * dist) * (uedot) *abs(uedot) / dist/ dist;
	mokuhf = arm2_pos + armvec_moku_migi * migidot / dist * 0.001f +armvec_moku_ue * uedot / dist * 0.001f;
	//MyVec3TransformCoord(mokuhf, mokuhf, robo->atarihan->world);
	// atteru
	

	if (is_miginiaru) {
		if (is_migi) {
			dthetaza -= 0.06*abs(the) + 0.07f*asin(abs(migidot) / dist);
			dthetazb -= 0.0008f*abs(migidot) / dist;
		}
		else {
			dthetaza += 0.06*abs(the) + 0.07f*asin(abs(migidot) / dist);
					dthetazb += 0.0008f*abs(migidot) / dist;
		}
	}
	else {
		if (is_migi) {
			dthetaza += 0.06*abs(the) + 0.07f * asin(abs(migidot) / dist);
			//		dthetazb -= 0.8f*abs(migidot) / dist;
			dthetazb += 0.0008f*abs(migidot) / dist;
		}
		else {
			dthetaza -= 0.06*abs(the) + 0.07f * asin(abs(migidot) / dist);
			dthetazb -= 0.0008f*abs(migidot) / dist;
		}
	}
	// *atteru* //
	//is_ueniaru = !is_ueniaru;
	if (is_ueniaru) {
		dthetaxa += 0.01f * asin(abs(uedot)/dist);
	//	dthetaxb += 0.03f * abs(uedot) / disst2;
	}
	else {
		dthetaxa -= 0.01f * asin(abs(uedot)/dist);
	//	dthetaxb -= 0.03f * abs(uedot) / disst2;
	}

	//dthetaxa = 1.57;
	return;
	
	// mokuhfが決まったので あとは　dtheta を求める
	if (is_migi) {
		MyIKMODOKI modoki(robo->arm->rarm, &iden/*robo->atarihan->world*/, &mokuhf, "modoruBone", "handBone");
		modoki.setXFreeBone("uparmBone");
		modoki.setYFreeBone("uparmBone");
		modoki.setZFreeBone("uparmBone");
		modoki.setXFreeBone("downarmBone");
		modoki.setZFreeBone("downarmBone");

		for (int i = 0; i < 1; i++) {
			modoki.updateStep();
			dthetaxa += modoki.getdthetaXBone("uparmBone") / 30000.0f;
			dthetaya += modoki.getdthetaYBone("uparmBone") / 30000.0f;
			dthetaza += modoki.getdthetaZBone("uparmBone") / 30000.0f;
			dthetaxb += modoki.getdthetaXBone("downarmBone") / 3000000.0f;
			dthetayb = 0;
			dthetazb += modoki.getdthetaZBone("downarmBone") / 3000000.0f;



			hanneiThetaToRoboArm(is_migi);
			if (is_migi) {
				robo->arm->rarm->animate(40, false);
			}
			else {
				robo->arm->larm->animate(40, false);
			}
		}

	}
	else {
		MyIKMODOKI modoki(robo->arm->larm, &iden/* &robo->atarihan->world*/, &mokuhf, "modoruBone", "handBone");
		modoki.setXFreeBone("uparmBone");
		modoki.setYFreeBone("uparmBone");
		modoki.setZFreeBone("uparmBone");
		modoki.setXFreeBone("downarmBone");
		modoki.setZFreeBone("downarmBone");

		for (int i = 0; i < 1; i++) {
			modoki.updateStep();
			dthetaxa += modoki.getdthetaXBone("uparmBone") / 30000.0f;
			dthetaya += modoki.getdthetaYBone("uparmBone") / 30000.0f;
			dthetaza += modoki.getdthetaZBone("uparmBone") / 30000.0f;
			dthetaxb += modoki.getdthetaXBone("downarmBone") / 3000000.0f;
			dthetayb = 0;
			dthetazb += modoki.getdthetaZBone("downarmBone") / 3000000.0f;
			hanneiThetaToRoboArm(is_migi);
			if (is_migi) {
				robo->arm->rarm->animate(40, false);
			}
			else {
				robo->arm->larm->animate(40, false);
			}
		}

	}


/*
	if (is_migi) {
		robo->arm->rarm->animate(40, true);
	}
	else {
		robo->arm->larm->animate(40, true);
	}*/
	hanneiThetaToRoboArm(is_migi);
	if (is_migi) {
		robo->arm->rarm->animate(40, false);
	}
	else {
		robo->arm->larm->animate(40, false);
	}




}

