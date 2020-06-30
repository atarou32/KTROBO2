#include "KTRoboEntity.h"
#include "MyDefine.h"
#include "KTRoboInputGamePad.h"

using namespace KTROBO;

void EntityManager::setViewProj(Graphics* g, MYMATRIX* view, MYMATRIX* proj) {
	if (mis) {
		mis->setViewProj(g, view, proj, &MYVECTOR4(0, 0, -1, 1));

	}

}

void RoboPlayerCharacterEntity::fireUpdate(Graphics* g, Game* game, Scene* scene, AtariHantei* hantei, BulletController* bullet_c, float dt, int stamp) {
	if (bullet_c) {
		if (robo) {
			robo->fireUpdate(g, game, scene, bullet_c, hantei, dt, stamp);
		}
	}
}

void EntityManager::updatePos(Graphics* g, Game* game, Scene* scene, AtariHantei* hantei, BulletController* bullet_c, float dsecond, int timestamp) {
	if (bullet_c) {
		
	//	player->setV(1, 0, 0);
		static float y = 0;
	//	y += 0.1f;
		//player->setMuki(&MYVECTOR3(0, 0, y));
		if (player) {
			player->fireUpdate(g, game, scene, hantei, bullet_c, dsecond, timestamp);
		}


		int csize = characters.size();
		for (int i = 0; i < csize; i++) {
			characters[i]->fireUpdate(g,game,scene,hantei,bullet_c,dsecond,timestamp);
		
		}

		int esize = enemys.size();
		for (int i = 0; i < esize; i++) {
			enemys[i]->fireUpdate(g, game, scene, hantei, bullet_c, dsecond, timestamp);
	
		}

		int epsize = enemyparts.size();
		for (int i = 0; i < epsize; i++) {
			enemyparts[i]->fireUpdate(g, game, scene, hantei, bullet_c, dsecond, timestamp);
		
		}




	}

}


void EntityManager::updateAtariAndMeshInstanced(Graphics* g, AtariHantei* hantei, float dsecond, int timestamp) {
	if (player) {
		player->calcAtariUMesh();
		player->calcMeshInstanced();
	}
	int csize = characters.size();
	for (int i = 0; i < csize; i++) {
		characters[i]->calcAtariUMesh();
		characters[i]->calcMeshInstanced();
	}

	int esize = enemys.size();
	for (int i = 0; i < esize; i++) {
		enemys[i]->calcAtariUMesh();
		enemys[i]->calcMeshInstanced();
	}

	int epsize = enemyparts.size();
	for (int i = 0; i < epsize; i++) {
		enemyparts[i]->calcAtariUMesh();
		enemyparts[i]->calcMeshInstanced();
	}
}

void EntityManager::byouga(Graphics* g, Game* game, MYMATRIX* view, MYMATRIX* proj,float dt, int stamp) {
	if (mis) {
		mis->render(g);
		if (player) {
			float frames[1];
			bool coms[1];
			frames[0] = 1;
			coms[0] = true;
			player->atarihan->draw(g, view, proj, 1, frames, coms, true, true, true, false);
			player->render(g, game,view, proj,dt,stamp);
		}

		float frames[1];
		bool coms[1];
		frames[0] = 1;
		coms[0] = true;

		int csize = characters.size();
		for (int i = 0; i < csize; i++) {
			characters[i]->atarihan->draw(g, view, proj, 1, frames, coms, true, true, true, false);
			characters[i]->render(g, game,view, proj, dt, stamp);
		}

		int esize = enemys.size();
		for (int i = 0; i < esize; i++) {
			enemys[i]->atarihan->draw(g, view, proj, 1, frames, coms, true, true, true, false);
			enemys[i]->render(g, game,view, proj, dt, stamp);
		}

		int epsize = enemyparts.size();
		for (int i = 0; i < epsize; i++) {
			enemyparts[i]->atarihan->draw(g, view, proj, 1, frames, coms, true, true, true, false);
			enemyparts[i]->render(g, game,view, proj, dt, stamp);
		}


	}


}

void TikeiMap::setViewProj(Graphics* g, MYMATRIX* view, MYMATRIX* proj) {
	if (mis) {
		mis->setViewProj(g, view, proj, &MYVECTOR4(0, 0, -1, 1));
		
	}
}
void TikeiMap::byouga(Graphics* g) {
	/*if (mis) {
		mis->render(g);
	}*/


}
void EntityManager::updatemis(Graphics* g) {

	if (mis) {
		mis->loadAnimeMatrixBasisToTexture(g);
		mis->loadMatrixLocalToTexture(g);
		mis->calcCombinedMatrixToTexture(g);
		mis->loadColorToTexture(g);
	}

}


void EntityManager::loadExample1(Graphics* g, MyTextureLoader* loader,Texture* te) {

	PlayerCharacterEntity* cc = new RoboPlayerCharacterEntity(g,te,hantei,loader,100000, 100, "test");
	player = cc;
	float frame = 0;
	Mesh* e1 = new Mesh();
	e1->readMesh(g, "resrc/model/bonebody/bonebody.MESH", loader);
	e1->readAnime("resrc/model/bonebody/bonebody.ANIME");
	e1->animate(frame, true);

	Mesh* e2 = new Mesh();
	e2->readMesh(g, "resrc/model/bonebody/hair.MESH", loader);
	e2->readAnime("resrc/model/bonebody/hair.ANIME");

	e2->RootBone->parent_bone = e1->Bones[e1->BoneIndexes["atamaBone"]];
	e2->RootBone->parent_bone_index = e1->BoneIndexes["atamaBone"];
	e2->RootBone_connect_without_material_local = false;
	MYMATRIX inv;
	inv = e1->Bones[e1->BoneIndexes["atamaBone"]]->matrix_local;
	MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
	MyMatrixInverse(inv, NULL, inv);
	e2->rootbone_matrix_local_kakeru = inv;
	MYMATRIX scaling;

	e2->animate(frame, true);

	Mesh* e3 = new Mesh();

	//mesh3[1]->readMesh(g, "resrc/model/ponko2-3/pk2hidarime.MESH", demo->tex_loader);
	//mesh3[1]->readAnime("resrc/model/ponko2-3/pk2hidarime.ANIME");
	e3->readMesh(g, "resrc/model/bonebody/head.MESH", loader);
	e3->readAnime("resrc/model/bonebody/head.ANIME");
	e3->RootBone->parent_bone = e1->Bones[e1->BoneIndexes["atamaBone"]];
	e3->RootBone->parent_bone_index = e1->BoneIndexes["atamaBone"];
	e3->RootBone_connect_without_material_local = false;
	MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
	MyMatrixInverse(inv, NULL, inv);
	e3->rootbone_matrix_local_kakeru = inv;// m->example1->Bones[m->example1->BoneIndexes["atamaBone"]]->combined_matrix;
	e3->animate(frame, true);
	//cc->regMesh(e1);
	//cc->regMesh(e2);
	//cc->regMesh(e3);
	this->entity_meshs.push_back(e1);
	this->entity_meshs.push_back(e2);
	this->entity_meshs.push_back(e3);

	unsigned short animf[KTROBO_MESH_INSTANCED_BONE_MAX];
	unsigned short animl[KTROBO_MESH_INSTANCED_BONE_MAX];
	float animw[KTROBO_MESH_INSTANCED_BONE_MAX];

	memset(animf, 0, sizeof(animf));
	memset(animl, 0, sizeof(animl));
	memset(animw, 0, sizeof(animw));

	MeshInstanced* misdayo;
	{
		MYMATRIX idenmat;
		MyMatrixIdentity(idenmat);
		UMeshUnit* umesh_unit = new UMeshUnit();
		UMesh* um = new UMesh(g, "resrc/model/bonebody/bonebody.MESH", loader, e1, false, &idenmat,
			0, KTROBO_MESH_BONE_NULL, false); // doBoneのobbがtrueになるので大丈夫

		MeshInstanced* mi = mis->makeInstanced(e1, e1, NULL, NULL, false, &idenmat);
		umesh_unit->setUMesh(um);
		misdayo = mi;

		//umesh_units.push_back(umesh_unit);
		umesh_unit->setSCALEXYZ(100, 100, 100);
		umesh_unit->setXYZ(0 + 0, 0, 0/*-4*/);
		um->setAnimeFrame(0);
		um->Animate(true);
		umesh_unit->calcJyusinAndR();
		mi->setWorld(&umesh_unit->world);
		mi->setIsRender(true);
		mi->setBoneIndexInfo(animf, animl, animw);

		bool tyo_unko = true;
		float frame_anime = 0;

		umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
		umesh_unit->calcJyusinAndR();
		hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);
		mids.push_back(mi);
		entity_umeshunits.push_back(umesh_unit);
	//	cc->regMeshI(mi);
	//	cc->regUMeshUnit(umesh_unit);
		//cc->setBody(umesh_unit);
		
	}
	{
		MYMATRIX idenmat;
		MyMatrixIdentity(idenmat);
		MYMATRIX inv;

		MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
		MyMatrixInverse(inv, NULL, inv);
		idenmat = inv;
		UMeshUnit* umesh_unit = new UMeshUnit();
		UMesh* um = new UMesh(g, "resrc/model/bonebody/head.MESH", loader, e3, false, &idenmat,
			e1->Bones[e1->BoneIndexes["atamaBone"]], e1->BoneIndexes["atamaBone"], false); // doBoneのobbがtrueになるので大丈夫

		MeshInstanced* me = mis->makeInstanced(e3, e3, misdayo, e1->BoneIndexes["atamaBone"], false, &idenmat);
		umesh_unit->setUMesh(um);
		

		//umesh_units.push_back(umesh_unit);
		umesh_unit->setSCALEXYZ(100, 100, 100);
		umesh_unit->setXYZ(0 + 0, 0, 0/*-4*/);
		um->setAnimeFrame(0);
		um->Animate(true);
		umesh_unit->calcJyusinAndR();
		me->setWorld(&umesh_unit->world);
		me->setIsRender(true);
		me->setBoneIndexInfo(animf, animl, animw);

		bool tyo_unko = true;
		float frame_anime = 0;

		umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
		umesh_unit->calcJyusinAndR();
		hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);

		mids.push_back(me);
		entity_umeshunits.push_back(umesh_unit);
	//	cc->regMeshI(me);
	//	cc->regUMeshUnit(umesh_unit);
	}
	{
		MYMATRIX idenmat;
		MyMatrixIdentity(idenmat);
		MYMATRIX inv;

		MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
		MyMatrixInverse(inv, NULL, inv);
		idenmat = inv;
		UMeshUnit* umesh_unit = new UMeshUnit();
		UMesh* um = new UMesh(g, "resrc/model/bonebody/hair.MESH", loader, e2, false, &idenmat,
			e1->Bones[e1->BoneIndexes["atamaBone"]], e1->BoneIndexes["atamaBone"], false); // doBoneのobbがtrueになるので大丈夫

		MeshInstanced* mes = mis->makeInstanced(e2, e2, misdayo, e1->BoneIndexes["atamaBone"], false, &idenmat);
		umesh_unit->setUMesh(um);
		

		//umesh_units.push_back(umesh_unit);
		umesh_unit->setSCALEXYZ(100, 100, 100);
		umesh_unit->setXYZ(0 + 0, 0, 0/*-4*/);
		um->setAnimeFrame(0);
		um->Animate(true);
		umesh_unit->calcJyusinAndR();
		mes->setWorld(&umesh_unit->world);
		mes->setIsRender(true);
		mes->setBoneIndexInfo(animf, animl, animw);

		bool tyo_unko = true;
		float frame_anime = 0;

		umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
		umesh_unit->calcJyusinAndR();
		hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);

		mids.push_back(mes);
		entity_umeshunits.push_back(umesh_unit);
	//	cc->regMeshI(mes);
	//	cc->regUMeshUnit(umesh_unit);
	}
	cc->setPos(0, 0, 50);
	cc->calcAtariUMesh();
	cc->calcMeshInstanced();
}


void EnemyEntityPart::calcAtariUMesh() {
	if (unit && um && bone && atarihan) {
		this->setPos(pos.float3.x, pos.float3.y, pos.float3.z);
		this->setMuki(&MYVECTOR3(rot.float3.x, rot.float3.y, rot.float3.z));
		unit->calcJyusinAndR();
		// atari_umesh のそのときの位置大きさを計算して　当てはめる
		MYVECTOR3 pos(0, 0, 0);
		MYMATRIX ansmat;
		MyMatrixMultiply(ansmat, bone->matrix_local, bone->combined_matrix);
		MyMatrixMultiply(ansmat, ansmat, unit->world);
		MyVec3TransformCoord(pos, pos, ansmat); // これでワールド空間におけるボーンの位置が見つかる

		float r = unit->r;
		atarihan->setSCALEXYZ(1, 1, 1);
//		atarihan->setXYZ(pos.float3.x, pos.float3.y, pos.float3.z);
//		atarihan->setXYZ(pos.float3.x + atari_offsetdayo.float3.x, pos.float3.y + atari_offsetdayo.float3.y, pos.float3.z + atari_offsetdayo.float3.z);
		MYVECTOR3 atari_o;
		this->getAtariOffsetDayo(&atari_o);
		atarihan->setXYZ(pos.float3.x + atari_o.float3.x, pos.float3.y + atari_o.float3.y, pos.float3.z + atari_o.float3.z);
		atarihan->calcJyusinAndR();
		atarihan->setSCALEXYZ(r / atarihan->r, r / atarihan->r, r / atarihan->r);
		atarihan->setROTXYZ(rot.float3.x, rot.float3.y, rot.float3.z);
		atarihan->calcJyusinAndR();


	}
}

void CharacterEntity::calcAtariUMesh() {

	if (atari_umesh) {
		// atari_umesh のそのときの位置大きさを計算して　当てはめる
		int uis = units.size();
		this->setPos(pos.float3.x, pos.float3.y, pos.float3.z);
		this->setMuki(&MYVECTOR3(rot.float3.x, rot.float3.y, rot.float3.z));
		for (int i = 0; i < uis; i++) {
			
			units[i]->calcJyusinAndR();
		}

		MYVECTOR3 pos2 = atari_umesh->jyusin;
		float r = atari_umesh->r;
		atarihan->setSCALEXYZ(1, 1, 1);
		MYVECTOR3 atari_o;
		this->getAtariOffsetDayo(&atari_o);
		atarihan->setXYZ(pos2.float3.x+atari_o.float3.x, pos2.float3.y + atari_o.float3.y, pos2.float3.z +atari_o.float3.z);
		atarihan->calcJyusinAndR();
		atarihan->setSCALEXYZ(r / atarihan->r, r / atarihan->r, r / atarihan->r);
		atarihan->setROTXYZ(rot.float3.x, rot.float3.y, rot.float3.z);
		atarihan->calcJyusinAndR();


	}
}


void TikeiMap::loadExample1(Graphics* g,MyTextureLoader* loader) {

	Mesh* mesh = new Mesh();
	mesh->readMesh(g, "resrc/model/tikei/tikei_douro.MESH", loader);
	mesh->readAnime("resrc/model/tikei/tikei_douro.ANIME");
	mesh->animate(0, true);
	this->regmesh(mesh);
	MYMATRIX idenmat;
	MyMatrixIdentity(idenmat);
	UMeshUnit* umesh_unit = new UMeshUnit();
	UMesh* um = new UMesh(g, "resrc/model/tikei/tikei_douro.MESH", loader, mesh, false, &idenmat,
		0, KTROBO_MESH_BONE_NULL, true); // doBoneのobbがtrueになるので大丈夫

	MeshInstanced* mids = mis->makeInstanced(mesh, mesh, NULL, NULL, false, &idenmat);
	umesh_unit->setUMesh(um);


	unsigned short animf[KTROBO_MESH_INSTANCED_BONE_MAX];
	unsigned short animl[KTROBO_MESH_INSTANCED_BONE_MAX];
	float animw[KTROBO_MESH_INSTANCED_BONE_MAX];

	memset(animf, 0, sizeof(animf));
	memset(animl, 0, sizeof(animl));
	memset(animw, 0, sizeof(animw));
	

	//umesh_units.push_back(umesh_unit);
	umesh_unit->setSCALEXYZ(100, 100, 130);
	umesh_unit->setXYZ(0, 0, -10/*-4*/);
	um->setAnimeFrame(0);
	um->Animate(true);
	umesh_unit->calcJyusinAndR();
	mids->setWorld(&umesh_unit->world);
	mids->setIsRender(true);
	mids->setBoneIndexInfo(animf, animl, animw);
	bool tyo_unko = true;
	float frame_anime = 0;

	//		umesh_unit->calcAnimeFrame(1,&frame_anime,&tyo_unko);
	//		umesh_unit->calcJyusinAndR();
	hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_TIKEI);

	this->reg(umesh_unit, mids);
}

Mesh* Entity::atari_mesh=0;

void Entity::AtariMeshInit(Graphics* g, MyTextureLoader* loader) {
	if (!atari_mesh) {
		atari_mesh = new Mesh();
		atari_mesh->readMesh(g, KTROBO_ENTITY_ATARI_UMESH_MESH_FILENAME, loader);
		atari_mesh->readAnime(KTROBO_ENTITY_ATARI_UMESH_MESH_ANIMENAME);
		atari_mesh->animate(0, true);
	}
}

void Entity::AtariMeshDel() {
	if (atari_mesh) {
		atari_mesh->Release();
		delete atari_mesh;
		atari_mesh = 0;
	}
}

void EnemyEntityPart::setPos(float x, float y, float z) {
	Entity::setPos(x, y, z);
	unit->setXYZ(x, y, z);
}

void EnemyEntityPart::setMuki(MYVECTOR3* srot) {
	Entity::setMuki(srot);
	unit->setROTXYZ(srot->float3.x, srot->float3.y, srot->float3.z);
}
void CharacterEntity::setPos(float x, float y, float z) {
	Entity::setPos(x, y, z);
	int us = this->units.size();
	for (int i = 0; i < us; i++) {
		units[i]->setXYZ(x, y, z);
	}
}

void CharacterEntity::setMuki(MYVECTOR3* srot) {
	Entity::setMuki(srot);
	int us = this->units.size();
	for (int i = 0; i < us; i++) {
		units[i]->setROTXYZ(srot->float3.x, srot->float3.y, srot->float3.z);
	}
}
void RoboPlayerCharacterEntity::atarishori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {
	MYVECTOR3 maepos = MYVECTOR3(robo->atarihan->x, robo->atarihan->y, robo->atarihan->z);


	CharacterEntity::atarishori(g, view, hantei, dt, stamp);
	
	MYVECTOR3 atopos = MYVECTOR3(robo->atarihan->x, robo->atarihan->y, robo->atarihan->z);
	if (robo) {
		MYVECTOR3 sa;
		MyVec3Subtract(sa, atopos, maepos);
		robo->atarihan->setXYZ(robo->atarihan->x + sa.float3.x, robo->atarihan->y + sa.float3.y, robo->atarihan->z + sa.float3.z);
		//robo->atarishori(g, view, hantei, dt, stamp);
		robo->setSetDayo(this->setdayo_formoveshori);
		robo->setSetKabeDayo(this->setkabedayo_formoveshori);
		robo->setVdayo(this->vdayo_formoveshori);
	}
}
void RoboPlayerCharacterEntity::moveshori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {

	//CharacterEntity::moveshori(g, view, hantei, dt, stamp);
	if (robo) {
		MYVECTOR3 maepos = MYVECTOR3(robo->atarihan->x, robo->atarihan->y, robo->atarihan->z);
		robo->moveshori(g, view, hantei, dt, stamp);
		MYVECTOR3 atopos = MYVECTOR3(robo->atarihan->x, robo->atarihan->y, robo->atarihan->z);
		MYVECTOR3 sa;
		MyVec3Subtract(sa, atopos, maepos);
		this->setPos(pos.float3.x + sa.float3.x, pos.float3.y + sa.float3.y, pos.float3.z + sa.float3.z);
		this->setV(robo->atarihan->v.float3.x, robo->atarihan->v.float3.y, robo->atarihan->v.float3.z);
		robo->atarihan->calcJyusinAndR();
	
	
		this->setMuki(&MYVECTOR3(robo->atarihan->rotx, robo->atarihan->roty, robo->atarihan->rotz));
		this->calcAtariUMesh();
		this->calcMeshInstanced();
		robo->atarihan->calcJyusinAndR();
	

	}
	else {
		CharacterEntity::moveshori(g, view, hantei, dt, stamp);
	}
}
bool RoboPlayerCharacterEntity::handleMessage(int msg, void* data, DWORD time) {

	PlayerCharacterEntity::handleMessage(msg, data, time);

	if (robo) {
		float maerotz = robo->atarihan->rotz;
		robo->handleMessage(msg, data, time);
		float atorotz = robo->atarihan->rotz;
		// roboのアップダウン向きを一致させる
		this->setCameraRotX(robo->updown_muki);
		this->setCameraRotY(atorotz);
		
		
	}
	


	return false;

}

void CharacterEntity::calcMeshInstanced() {
	
	int misize = mesh_is.size();
	int umsize = units.size();
	
	if (misize && (misize == umsize)) {

		for (int i = 0; i < misize; i++) {
			mesh_is[i]->setWorld(&units[i]->world);
		}
	}
}


void EnemyEntityPart::calcMeshInstanced() {
// 見た目の更新は　enemyの中で行われている
}
void RoboPlayerCharacterEntity::render(Graphics* g,Game* game, MYMATRIX* view, MYMATRIX* proj,float dt , int stamp) {
	if (robo) {
		robo->byouga(g, view, proj);

		robo->boosterEffect(game, g, dt, stamp);
	}

}


void CharacterEntity::moveshori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {
	if ((abs(dt) > 150) || (dt < 0)) {
		//atarihan->calcJyusinAndR();
		this->calcAtariUMesh();
		this->calcMeshInstanced();
		return;
	}

	bool setdayo = setdayo_formoveshori;
	bool is_tenjyou = istenjyou_formoveshori;
	bool setkabedayo = setkabedayo_formoveshori;
	float vdayo = vdayo_formoveshori;
	MYVECTOR3 offset = MYVECTOR3(atarihan->x, atarihan->y, atarihan->z);
	MyVec3Subtract(offset, offset, pos);
	if (is_tenjyou) {
		this->setV(v.float3.x, v.float3.y, -abs(v.float3.z));
	}

	if (setdayo == false) {

		// 空中にいる
		if (dt < 200) {
			vdayo = this->v.float3.z;

			vdayo = vdayo - 0.0000098*dt;





			float xx = vdayo * dt;
			atarihan->setDT(dt);

			this->setPos(pos.float3.x, pos.float3.y, pos.float3.z + xx);
			
			this->setV(v.float3.x, v.float3.y, vdayo);
			//atarihan->setXYZD(atarihan->x, atarihan->y, atarihan->z + xx, 24);
			//atarihan->setV(&MYVECTOR3(atarihan->v.float3.x, atarihan->v.float3.y, vdayo));







		}

	}
	else {
		atarihan->setDT(dt);
		this->setV(v.float3.x, v.float3.y, 0);
		MYVECTOR3 vdt = v * dt;


		this->setPos(pos.float3.x+vdt.float3.x, pos.float3.y+vdt.float3.y, pos.float3.z + vdt.float3.z+0.001f);
		
	}
	atarihan->calcJyusinAndR();
	
	// アニメ―と
	/*
	int ms = units.size();
	for (int i = 0; i < ms; i++) {
		bool coms[1];
		static float ff = 0;
		float frames[1];
		coms[0] = true;
		ff += dt/1000.0f;
		frames[0] = ff;
		units[i]->calcAnimeFrame(1, frames, coms);
		units[i]->calcJyusinAndR();
		unsigned short afs[KTROBO_MESH_BONE_MAX];
		unsigned short afe[KTROBO_MESH_BONE_MAX];
		float afw[KTROBO_MESH_BONE_MAX];
		for (int j = 0; j < KTROBO_MESH_BONE_MAX; j++) {
			afs[j] = floor(frames[0]);
			afe[j] = ceil(frames[0]);
			afw[j] = 1 - (frames[0] - floor(frames[0]));
		}
		mesh_is[i]->setBoneIndexInfo(afs, afe, afw);
	}
	*/

	atarihan->setXYZ(pos.float3.x+ offset.float3.x, pos.float3.y+offset.float3.y , pos.float3.z+offset.float3.z);
	this->calcAtariUMesh();
	this->calcMeshInstanced();
	
}
void CharacterEntity::atarishori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {

	if ((abs(dt) > 400) || (dt < 0)) {
		atarihan->calcJyusinAndR();
		calcAtariUMesh();
		calcMeshInstanced();
		setdayo_formoveshori = true;
		setkabedayo_formoveshori = true;
		vdayo_formoveshori = 0;
		return;
	}

	calcAtariUMesh();
	
	AtariUnitAnsKWSK ans[1024];
	float vdayo = 0;
	bool setdayo = false;
	bool setkabe = false;
	bool setkabedayo = false;
	bool is_setti = false;
	// あらかじめ　pos と　atarihanのpos のオフセットを取っておく
	MYVECTOR3 offset = MYVECTOR3(atarihan->x, atarihan->y, atarihan->z);
	MyVec3Subtract(offset, offset, pos);
	float offsetlen = MyVec3Length(offset);
	MYVECTOR3 maepos = pos;

	bool is_tenjyou = false;
	int atari_num = hantei->getAns(ans, atarihan, NULL, 1024);
	if (atari_num > 0) {
		float dx = 0;
		float dy = 0;
		float dz = 0;
		bool ato_setdayo = false;

		bool is_kabe = false;
		bool no_z = false;
		for (int i = 0; i < atari_num; i++) {
			if (ans[i].aite_type == AtariUnit::AtariType::ATARI_TIKEI) {
				MYVECTOR3 kouten_housen = ans[i].ans->kouten_housen;
				//if (MyVec3Length(kouten_housen) < 0.3) continue;
				MyVec3Normalize(kouten_housen, kouten_housen);
				MYVECTOR3 kouten_jyusin = ans[i].ans->kouten_jyusin;
				MYVECTOR3 robo_center = MYVECTOR3(atarihan->x, atarihan->y, atarihan->z);
				// robo_center を　vの長さ分だけ前にする
				robo_center = robo_center - atarihan->v * dt;

				//UMesh* atari_umesh = ans[i].my_umesh;
				//for (int k = 0; k < KTROBO_MESH_BONE_MAX; k++) {
				//
				//}
				MYVECTOR3 up(0, 0, 1);
				MYVECTOR3 down(0, 0, -1);
				MYVECTOR3 kk;
				kk = robo_center - kouten_jyusin;
				float klen = MyVec3Length(kk);
				/*if (klen > offsetlen + atarihan->r) {
					continue;
				}
				else {
					setkabedayo = true;
					//	setkabe_count = 1;

				}*/
				MyVec3Normalize(kk, kk);
				float updot = MyVec3Dot(up, kouten_housen);
				float downdot = MyVec3Dot(down, kk);
				if (updot > 0.6) {
					MYVECTOR3 pos(atarihan->x - kouten_jyusin.float3.x, atarihan->y - kouten_jyusin.float3.y
						, atarihan->z - kouten_jyusin.float3.z);
					/*	if (MyVec3Length(pos) < atarihan->r) {
							setdayo = true;
							setti_state = &setti;
							//vdayo = 0;
						}*/
						//	setdayo = true;
				}


				if (updot > 0.7) {
					//&ans[i].my_umesh->bone_obbs[ans[i].ans->obbidx];// atari_leg->bone_obbs[atari_leg->mesh->BoneIndexes["rightLegDownBone"]];
					OBB obdayo;

					for (int rr = 0; rr < KTROBO_MESH_BONE_MAX; rr++) {
						if (ans[i].ans->obbidx == ans[i].my_umesh->bone_obbs_idx[rr]) {
							obdayo = ans[i].my_umesh->bone_obbs[rr];
						}
					}










					// 本来ならば　足のボーンのobbと交点の重心が一致するはずと考えて
					MYVECTOR3 sa;
					MyVec3Subtract(sa, kouten_jyusin, obdayo.c);
					// z 分だけタス

					bool do_shori = true;


					if (do_shori) {

						dz += min(0.08f, abs(sa.float3.z));
						//setdayo = false;
						ato_setdayo = true;
						this->setV(v.float3.x, v.float3.y, abs(v.float3.z));
						MYVECTOR3 setpos(0, 0, 0);// kouten_jyusin.float3.x, kouten_jyusin.float3.y, kouten_jyusin.float3.z);
						setpos = setpos + (kouten_housen * atarihan->r*0.6);
						this->setPos(atarihan->x, atarihan->y, atarihan->z + setpos.float3.z);
					}
					else {
						dz += min(0.05f, abs(sa.float3.z));
						//	atarihan->setV(&MYVECTOR3(atarihan->v.float3.x, atarihan->v.float3.y, abs(atarihan->v.float3.z)));

					}
					//vdayo = 0;
					//setkabedayo = false;
					//continue; // 地面と考える


















				}
				if ((downdot > 0.1)/* && !is_tenjyou && !setdayo*/) {
					// 天井と考えて

				/*	if ((move_state->isJump() || move_state->isJumpKABE()) && (this->pressed_space_count > 10)) {
						move_state->leave(this, &movestop, move_state);
						movestop.enter(this, &movestop, move_state);
						move_state = &movestop;
					}
				*/

				//	settenjyou_state->leave(this, &settenjyou, settenjyou_state);
				//	settenjyou.enter(this, &settenjyou, settenjyou_state);
				//	settenjyou_state = &settenjyou;
					MYVECTOR3 cc;
					MyVec3Subtract(cc, robo_center, kouten_jyusin);
					float ddd = MyVec3Dot(cc, kouten_housen);
					if ((ddd * downdot > 0) && (robo_center.float3.z < kouten_jyusin.float3.z)) {
						MYVECTOR3 ddvec;
						MyVec3Normalize(ddvec, kouten_housen);
						ddvec = (ddvec * 0.1f);
						MYVECTOR3 ddvec2 = atarihan->v * dt*0.5;
						MyVec3Subtract(ddvec, ddvec, ddvec2);
						dx += ddvec.float3.x;
						dy += ddvec.float3.y;
						dz += ddvec.float3.z;
						/*	move_state->leave(this, &movestop, move_state);
							movestop.enter(this, &movestop, move_state);
							move_state = &movestop;*/
							//	atarihan->v = atarihan->v / 2;
					}
					this->setPos(atarihan->x, atarihan->y, atarihan->z - 0.002f - abs(kouten_housen.float3.z)* abs(v.float3.z)* abs(dt));
					atarihan->setXYZ(atarihan->x, atarihan->y, atarihan->z - 0.002f - abs(kouten_housen.float3.z)* abs(v.float3.z)* abs(dt));
					this->setV(atarihan->v.float3.x, atarihan->v.float3.y, -abs(atarihan->v.float3.z));
					atarihan->setV(&MYVECTOR3(atarihan->v.float3.x, atarihan->v.float3.y, -abs(atarihan->v.float3.z)));
					is_tenjyou = true;
					no_z = false;
					//setkabedayo = false;
					vdayo = 0;
					continue;
				}
				continue;
				// 壁と考える
				//if (is_kabe) continue;


				// headとbodyに関して考えてみて　交点の重心がbone_obbの中にないものは処理を行わない
				bool do_shori = true;

				OBB obkaku;

				// もし交点の重心が足元より下にあれば無視する
				MYVECTOR3 center = MYVECTOR3(atarihan->x, atarihan->y, atarihan->z);
				//	OBB* ob = &ans[i].my_umesh->bone_obbs[ans[i].ans->obbidx];// &atari_leg->bone_obbs[atari_leg->mesh->BoneIndexes["rightLegDownBone"]];
				OBB obdayo;
				for (int rr = 0; rr < KTROBO_MESH_BONE_MAX; rr++) {
					if (ans[i].ans->obbidx == ans[i].my_umesh->bone_obbs_idx[rr]) {
						obdayo = ans[i].my_umesh->bone_obbs[rr];
					}
				}
				MYVECTOR3 sitatiten = obdayo.c;
				MYVECTOR3 sitatiten2 = obdayo.u[0] * obdayo.e[0];
				sitatiten.float3.z += abs(sitatiten2.float3.z);
				sitatiten2 = obdayo.u[1] * obdayo.e[1];
				sitatiten.float3.z += abs(sitatiten2.float3.z);

				sitatiten2 = obdayo.u[2] * obdayo.e[2];
				sitatiten.float3.z += abs(sitatiten2.float3.z);
				sitatiten = (sitatiten + center)*0.5;
				if (!do_shori) {
					if (center.float3.z + atarihan->r*0.2 >= kouten_jyusin.float3.z) continue;
					MYVECTOR3 centertojyusin;
					MyVec3Subtract(centertojyusin, center, kouten_jyusin);
					if (MyVec3Length(centertojyusin) > atarihan->r * 1.4 + MyVec3Length(atarihan->v)*dt) continue;
				}
				float dbairitu = 1;
				if (!do_shori) {
					do_shori = true;
					dbairitu = 0.5;
					float dot = MyVec3Dot(atarihan->v, kouten_housen);
					MYVECTOR3 vato = kouten_housen * (0.02 + abs(dot)*0.2f);
					MyVec3Subtract(vato, atarihan->v, vato);
					atarihan->setV(&vato);
				}

				if (do_shori) {
					OBB rec;
					rec.c = kouten_jyusin;
					rec.e = MYVECTOR3(4, 4, 4);



					MYMATRIX wor;
					MyMatrixIdentity(wor);
					//	g->drawOBBFill(g, 0xFFFFFFFF, &wor, view, g->getProj(), &rec);

						/*move_state->leave(this, &movestop, move_state);
						movestop.enter(this, &movestop, move_state);
						move_state = &movestop;
						*/
						//if ((move_state->isJump() || move_state->isJumpKABE()) && (this->pressed_space_count > 10)) {
						//	move_state->leave(this, &movestop, move_state);
						//	movestop.enter(this, &movestop, move_state);
						//	move_state = &movestop;
						//}

						/*setkabe_state->leave(this, &setkabe, setkabe_state);
						setkabe.enter(this, &setkabe, setkabe_state);
						setkabe_state = &setkabe;*/
					MYVECTOR3 cc;
					MyVec3Subtract(cc, robo_center, kouten_jyusin);
					float ddd = MyVec3Dot(cc, kouten_housen);
					MYVECTOR3 vnor;
					MyVec3Normalize(vnor, atarihan->v);
					float dddd = MyVec3Dot(vnor, kouten_housen);
					float dddbairitu = 1;
					float vlen = MyVec3Length(atarihan->v);
					if (true || (dddd < -0.0)) {
						// 正面衝突
					//	move_state->leave(this, &movestop, move_state);
					//	movestop.enter(this, &movestop, move_state);
					//	move_state = &movestop;
						// vの成分を逆分増やすようにしてみる


						//if ((abs(downdot) < 0.9) || (abs(updot) < 0.9)) {


						MYVECTOR3 sinv = atarihan->v;

						sinv = sinv + kouten_housen * (0.005 + MyVec3Length(sinv) * 0.201);
						this->setV(sinv.float3.x, sinv.float3.y, sinv.float3.z);
						dddbairitu = 4;
						//}
					}

					if (ddd > -0.4) {
						MYVECTOR3 ddvec;
						MyVec3Normalize(ddvec, kouten_housen);
						//	ddvec = ddvec + atarihan->jyusin;
						//	MyVec3Subtract(ddvec, ddvec, kouten_jyusin);
						//	MyVec3Normalize(ddvec, ddvec);
						float ddd = 1;
						if (vlen < 0.001) {
							ddd = 0.003 * dddbairitu;
						}
						else {
							ddd = (MyVec3Length(atarihan->v)  * MyVec3Length(atarihan->v) + 0.003)* dddbairitu;
						}
						MYVECTOR3 a(atarihan->x, atarihan->y, atarihan->z);
						MyVec3Subtract(a, a, kouten_jyusin);


						ddvec = ddvec * ddd *dt;
						dx += ddvec.float3.x * dbairitu;
						dy += ddvec.float3.y * dbairitu;
						dz += ddvec.float3.z * dbairitu;
						//	is_kabe = true;
					}
					//vdayo = 0;
					no_z = false;
				}
			}
		}

		/*
		if (isnan(dx) || isnan(dy) || isnan(dz)) return;

		if (setdayo) {
			this->setPos(atarihan->x + dx, atarihan->y + dy, atarihan->z);
			if (ato_setdayo) {
				//	atarihan->setXYZD(atarihan->x , atarihan->y, atarihan->z+dz, 0.0005f);
				this->setPos(atarihan->x, atarihan->y, atarihan->z + dz);

			}
			//	setti_state = &setti;
	//			setdayo = true;
		}
		else {
			this->setPos(atarihan->x + dx, atarihan->y + dy, atarihan->z);
			//atarihan->setXYZD(atarihan->x, atarihan->y, atarihan->z+dz, 0.15);
			//if (no_z) {}
			//else {
			//}

			if (ato_setdayo) {
				//			setdayo = true;
						//	setti_state = &setti;
				this->setPos(atarihan->x, atarihan->y, atarihan->z + dz);

			}


		}
		*/
	}

	atari_num = hantei->getAns(ans, atarihan, NULL, 1024);
	if ((atari_num > 0)) {
		for (int i = 0; i < atari_num; i++) {
			if (ans[i].aite_type == AtariUnit::AtariType::ATARI_TIKEI) {
				
					MYVECTOR3 up(0, 0, 1);
					MYVECTOR3 san;
					MYVECTOR3 pos(atarihan->x, atarihan->y, atarihan->z+atarihan->r);
					MyVec3Subtract(san, pos, ans[i].ans->kouten_jyusin);
					float sanlen = MyVec3Length(san);
					//if (sanlen > atarihan->r+offsetlen) continue;

					MyVec3Normalize(san, san);
					if ((MyVec3Dot(ans[i].ans->kouten_housen, up) > 0.5)) {// && (MyVec3Dot(ans[i].ans->kouten_housen, san) > 0.5)) {
					
							
						MYVECTOR3 atapos = MYVECTOR3(atarihan->x, atarihan->y, atarihan->z);
						MYVECTOR3 a;
						MyVec3Subtract(a,atapos, ans[i].ans->kouten_jyusin);
						OBB ob;
						for (int rr = 0; rr < KTROBO_MESH_BONE_MAX; rr++) {
							if (ans[i].ans->obbidx == ans[i].my_umesh->bone_obbs_idx[rr]) {
								ob = ans[i].my_umesh->bone_obbs[rr];
							}
						}

						float f = min(MyVec3Length(atarihan->v)*dt, abs(MyVec3Length(a) - abs(MyVec3Dot(ob.u[0], ans[i].ans->kouten_housen) * ob.e[0])
								- abs(MyVec3Dot(ob.u[1], ans[i].ans->kouten_housen)) * ob.e[1]
								- abs(MyVec3Dot(ob.u[2], ans[i].ans->kouten_housen)) * ob.e[2]));
						f = min(abs(f), 0.05f);
					//	this->setPos(atarihan->x, atarihan->y, (atarihan->z + ans[i].ans->kouten_jyusin.float3.z) / 2.0f);

					
						is_setti = true;
						vdayo = 0;
						setdayo = true;
//						this->setPos(atarihan->x, atarihan->y, atarihan->z + abs(atarihan->v.float3.z) * abs(dt)+0.05f);

						if (!is_tenjyou) {
							this->setV(atarihan->v.float3.x, atarihan->v.float3.y, abs(atarihan->v.float3.z));
							this->setPos(atarihan->x, atarihan->y, atarihan->z + abs(ans[i].ans->kouten_housen.float3.z) * 1.02f*f*f);
						}

						
						
							

								






							
						
					}
				

			}
		}
	}


	atari_num = hantei->getAns(ans, atarihan, NULL, 1024);
	if ((atari_num > 0)) {
		for (int i = 0; i < atari_num; i++) {
			if (ans[i].aite_type == AtariUnit::AtariType::ATARI_TIKEI) {
				MYVECTOR3 up(0, 0, 1);
				MYVECTOR3 koutenhou = ans[i].ans->kouten_housen;
				
				MyVec3Normalize(koutenhou, koutenhou);
				float koutenhoudot = MyVec3Dot(koutenhou, atarihan->v);
				float dot = MyVec3Dot(up, ans[i].ans->kouten_housen);
				if ((abs(dot) < 0.6) && (((koutenhoudot < 0) && ((MyVec3Length(atarihan->v) > 0.05))) || (koutenhoudot ==0))) {
					// 壁とみなす
					// 大きな立方体の中に交点重心があれば処理する
					MYVECTOR3 jyusinhou = ans[i].ans->kouten_jyusin;
					MYVECTOR3 atarihanjyusin = atarihan->jyusin - atarihan->v * abs(dt);
					MYVECTOR3 pos(atarihan->x, atarihan->y, atarihan->z);
					pos = pos - atarihan->v *dt/2;
					MYVECTOR3 jyusinvec;
					MyVec3Subtract(jyusinvec, jyusinhou, atarihanjyusin);
					MyVec3Normalize(jyusinvec, jyusinvec);
					if (MyVec3Dot(jyusinvec, koutenhou) > 0) continue;
					MyVec3Subtract(jyusinhou, pos, jyusinhou);
					if (atarihan->r*3 + MyVec3Length(atarihan->v)*dt > MyVec3Length(jyusinhou)) {
						// 足元の壁の場合は崖の壁の場合があるので無視する
						if (jyusinhou.float3.z > 0 + atarihan->r / 4) continue;
						// 壁の場合は vを０にする
						vdayo = 0;

						// めり込んでる分戻す
						// koutenhou の方向に　r- jyusinhouの長さ分戻す
						MYVECTOR3 plus(0, 0, 0);
						plus = plus + koutenhou *  abs(atarihan->r + /*MyVec3Length(atarihan->v)*dt / 2*/ -MyVec3Length(jyusinhou)) / 2.0f;
						this->setPos(atarihan->x + plus.float3.x, atarihan->y + plus.float3.y,
							atarihan->z + 0);// , max(0.12f, MyVec3Length(atarihan->v)*dt));
						atarihan->setXYZ(atarihan->x + plus.float3.x, atarihan->y + plus.float3.y,
							atarihan->z + 0);
						if (koutenhoudot < -0.2) {
							atarihan->setV(&MYVECTOR3(atarihan->v + (koutenhou* koutenhoudot)));
							//	setkabe_state = &setkabe;
						}
						setkabedayo = true;
					}
					else {
						jyusinhou = ans[i].ans->kouten_jyusin;

						pos = MYVECTOR3(atarihan->x, atarihan->y, atarihan->z);
						MyVec3Subtract(jyusinhou, pos, jyusinhou);
						if (atarihan->r*3 > MyVec3Length(jyusinhou)) {
							// 足元の壁の場合は崖の壁の場合があるので無視する
							if (jyusinhou.float3.z > 0 + atarihan->r / 4) continue;
							// 壁の場合は vを０にする
							vdayo = 0;

							// めり込んでる分戻す
							// koutenhou の方向に　r- jyusinhouの長さ分戻す
							MYVECTOR3 plus(0, 0, 0);
							plus = plus + koutenhou * 0.05f;// abs(atarihan->r - MyVec3Length(jyusinhou)) / 2.0f;
							this->setPos(atarihan->x + plus.float3.x, atarihan->y + plus.float3.y,
								atarihan->z + 0);// max(0.12f, MyVec3Length(atarihan->v) * dt));
							atarihan->setXYZ(atarihan->x + plus.float3.x, atarihan->y + plus.float3.y,
								atarihan->z + 0);
							if (koutenhoudot < -0.2) {
								atarihan->setV(&MYVECTOR3(atarihan->v + (koutenhou* koutenhoudot)));
								//	setkabe_state = &setkabe;
							}
							setkabedayo = true;
						}
					}
				}

			}
		}
	}


	MYVECTOR3 sa = maepos;
	MyVec3Subtract(sa,pos,sa);
	float len = MyVec3Length(sa);
	if ((len > 0.00001) && (sa.float3.z > 0)) {
		//変わっているので offset をひく
		this->setPos(pos.float3.x-offset.float3.x, pos.float3.y-offset.float3.y, pos.float3.z-offset.float3.z);
		atarihan->setXYZ(pos.float3.x + offset.float3.x, pos.float3.y + offset.float3.y, pos.float3.z + offset.float3.z);
		atarihan->setV(&MYVECTOR3(atarihan->v.float3.x, atarihan->v.float3.y, 0));
		this->setV(v.float3.x, v.float3.y, 0);
	}
	else if (len > 0.000001) {

		this->setPos(pos.float3.x - offset.float3.x, pos.float3.y - offset.float3.y, pos.float3.z - offset.float3.z);
		atarihan->setXYZ(pos.float3.x + offset.float3.x, pos.float3.y + offset.float3.y, pos.float3.z + offset.float3.z);
		atarihan->setV(&MYVECTOR3(atarihan->v.float3.x, atarihan->v.float3.y, 0));
		this->setV(v.float3.x, v.float3.y, 0);

	}

	setdayo_formoveshori = setdayo;
	setkabedayo_formoveshori = setkabedayo;
	vdayo_formoveshori = vdayo;
	istenjyou_formoveshori = is_tenjyou;

	this->calcAtariUMesh();

}
void EntityManager::atarishori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {
	if (player) {
		player->atarishori(g, view, hantei, dt, stamp);
	}

	int csize = characters.size();
	for (int i = 0; i < csize; i++) {
		characters[i]->atarishori(g, view, hantei, dt, stamp);
	}

	int esize = enemys.size();
	for (int i = 0; i < esize; i++) {
		enemys[i]->atarishori(g, view, hantei, dt, stamp);
	}

	int epsize = enemyparts.size();
	for (int i = 0; i < epsize; i++) {
		enemyparts[i]->atarishori(g, view, hantei, dt, stamp);
	}
}

void EntityManager::moveshori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {
	if (player) {
		player->moveshori(g, view, hantei, dt, stamp);
		
	}
	int csize = characters.size();
	for (int i = 0; i < csize; i++) {
		characters[i]->moveshori(g, view, hantei, dt, stamp);
	}

	int esize = enemys.size();
	for (int i = 0; i < esize; i++) {
		enemys[i]->moveshori(g, view, hantei, dt, stamp);
	}

	int epsize = enemyparts.size();
	for (int i = 0; i < epsize; i++) {
		enemyparts[i]->moveshori(g, view, hantei, dt, stamp);
	}
}