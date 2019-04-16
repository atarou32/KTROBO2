#include "KTRoboBullet.h"

#ifndef KTROBO_GAME_H
#include "KTRoboGame.h"
#endif
#include "KTRoboWeaponEffect.h"
#include "KTRoboMap.h"


using namespace KTROBO;
Bullet::~Bullet() {
	if (atarihan) {
		delete atarihan;
		atarihan = 0;
	}
}

void Bullet::Init(Graphics* g, AtariHantei* h, MeshInstanced* mi) {

	//if (!atarihan) {
		atarihan = new UMeshUnit();
		UMesh* n = new UMesh();
		n->is_bone_obbs_use[0] =true;
		n->bone_obbs[0].c = MYVECTOR3(0,0,0);//atarihan->x,atarihan->y,atarihan->z);
		n->bone_obbs[0].e = MYVECTOR3(1,1,1);
		n->bone_obbs[0].u[0] = MYVECTOR3(1,0,0);
		n->bone_obbs[0].u[1] = MYVECTOR3(0,1,0);
		n->bone_obbs[0].u[2] = MYVECTOR3(0,0,1);
		atarihan->setUMesh(n);
	
		//atarihan->calcJyusinAndR(true);




		h->setUMeshUnit(atarihan,AtariUnit::AtariType::ATARI_WAZA);
		atarihan->setIsEnabled(h, true);

		/*CS::instance()->enter(CS_RENDERDATA_CS, "un");
		atarihan->setIsEnabled(h,false);
		CS::instance()->leave(CS_RENDERDATA_CS, "un");
		*/


	//}

	this->mesh_i = mi;
}

void Bullet::setParam(Robo* robo, RoboParts* parts, MYVECTOR3* hassyapos, MYVECTOR3* vdayo, MYMATRIX* shoki_world) {
	this->robo = robo;
	this->robo_parts =parts;
	h_pos = *hassyapos;
	h_v = *vdayo; // ���˕��������˂�
	this->shoki_world = *shoki_world;
	


}


bool Bullet::fire(Game* game, AtariHantei* hantei) {

	// �O��̏ꏊ�œ����蔻�肪�s����̂�h��
	setAtariJyunbi(false);
	MYMATRIX world = shoki_world;
	MYMATRIX dpos_wor;
	dpos = MYVECTOR3(0,0,0);
	atarihan->setV(&h_v);
	atarihan->setXYZ(h_pos.float3.x, h_pos.float3.y, h_pos.float3.z);
	
	dpos = dpos + atarihan->v* 0;
	MyMatrixTranslation(dpos_wor, dpos.float3.x,dpos.float3.y,dpos.float3.z);
	MyMatrixMultiply(world,world,dpos_wor);
	// rotx roty rotz ���v�Z����K�v������ // setworld����邱�ƂőΉ� bool calcworld������悤�ɂ���
	//atarihan->setXYZ(rand() %1000/10.0,rand() % 1000/10.0,rand() %10000/10.0);//test,test2,0);
	atarihan->setWorld(&world);
	atarihan->setDT(0);
	atarihan->calcJyusinAndR(false);
	mesh_i->setWorld(&world);

	mesh_i->setIsRender(true);
	this->is_fired = true;
	
	CS::instance()->enter(CS_RENDERDATA_CS, "un");
	
	//atarihan->setIsEnabled(hantei,true);
	// ���Ƃ���true�ɂȂ��Ă���̂Ŗ��Ȃ�

	MYVECTOR3 pp(0,0,0);
//	MyVec3TransformCoord(pp,pp,atarihan->world);

//	game->effect_suuji->render(1, &game->lookfromtoat,&pp);


	CS::instance()->leave(CS_RENDERDATA_CS, "un");
	return true;

}


void Bullet::atariShori(AtariHantei* hantei, MYMATRIX* view, float dsecond, int stamp) {



}


void Bullet::byouga(Graphics* g, MYMATRIX* view, MYMATRIX* proj, float dsecond, int stamp) {



}


void Bullet::update(Graphics* g, AtariHantei* hantei, float dsecond, int stamp) {
	if(mesh_i && is_fired && is_use){
		
		setAtariJyunbi(true);
		MYMATRIX world = shoki_world;
		MYMATRIX dpos_wor;

		dpos = dpos + atarihan->v* dsecond;
		MyMatrixTranslation(dpos_wor, dpos.float3.x,dpos.float3.y,dpos.float3.z);
		MyMatrixMultiply(world,world,dpos_wor);
		// rotx roty rotz ���v�Z����K�v������ // setworld����邱�ƂőΉ� bool calcworld������悤�ɂ���
		//atarihan->setXYZ(rand() %1000/10.0,rand() % 1000/10.0,rand() %10000/10.0);//test,test2,0);
		atarihan->setWorld(&world);
		atarihan->setDT(dsecond);
		atarihan->calcJyusinAndR(false);

		mesh_i->setWorld(&world);
		//mesh_i->setIsRender(true);

	} else if(mesh_i) {
	
	}

}




void BulletController::atariShori(Game* game, AtariHantei* hantei, MYMATRIX* view, float dsecond, int stamp) {
	AtariUnitAnsKWSK kuwasiku[2048];
	
	int temp = hantei->getAnsWaza(kuwasiku,2048);
	for (int i=0;i<temp;i++) {
		if (kuwasiku[i].aite_umesh && kuwasiku[i].my_umesh) {
			MeshInstanced * mm = bullets[umesh_id_to_bullet_indexs[kuwasiku[i].my_umesh->getUMESHID()]].mesh_i;
			Bullet* b = &bullets[umesh_id_to_bullet_indexs[kuwasiku[i].my_umesh->getUMESHID()]];
			if (b->getIsUse() && b->getAtariJyunbi() && b->robo && (b->robo->atarihan != kuwasiku[i].aite)) {
				//bullets[umesh_id_to_bullet_indexs[kuwasiku[i].my_umesh->getUMESHID()]].mesh_i->setIsRender(false);
				MYVECTOR3 kouten_jyusin = kuwasiku[i].ans->kouten_jyusin;
				MYVECTOR3 posdayo(b->atarihan->x, b->atarihan->y, b->atarihan->z);
				MYVECTOR3 sa;
				MyVec3Subtract(sa, posdayo, kouten_jyusin);
				float len = MyVec3Length(b->atarihan->v);
				float dotdayo = MyVec3Dot(b->atarihan->v, kuwasiku[i].ans->kouten_housen);
				if ((dotdayo<0) || (MyVec3Length(sa) < b->atarihan->r*(20 + dsecond * len))) {

					MYMATRIX worldd;
					MYVECTOR4 color;
					MYVECTOR3 pos(0, 0, 0);
					MYVECTOR3 vec(0, 0, 1);
					MyVec3TransformCoord(pos, pos, b->atarihan->world);
					MyVec3TransformNormal(vec, vec, b->atarihan->world);
					color.w = 1;
					color.x = 1;
					color.y = 1;
					color.z = 1;
					WeaponEffect::butukariEffectS(b->robo_parts, game, b->robo, &pos, &vec);
					Robo* aite_robo = game->rmap->getRobo(kuwasiku[i].aite_umesh->getUMESHID());
					if (aite_robo) {
						WeaponEffect::butukariShoriS(b->robo_parts, game, b->robo, aite_robo, b);
					}
					// �����蔻�肪������̂��ӂ������߂Ƀ����_���Ɉړ�������
					b->atarihan->setXYZ((rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100, (rand() % 256) / 256 * 100);
					b->atarihan->calcJyusinAndR(true);
					b->setIsUse(false);
					mm->setColor(&color);
					//game->getSound()->playCue("se_maoudamashii_explosion03");
					/*
					Bullet* bb = this->getEmptyBullet();
					bb->atarihan->setWorld(&kuwasiku[i].aite->world);
					bb->atarihan->meshs[0]->bone_obbs[0] = kuwasiku[i].aite->meshs[0]->bone_obbs[0];
					bb->atarihan->meshs[0]->is_bone_obbs_use[0] = true;
					*/
					//bb->fire(game,hantei);	
				}
			}
		}



		//if (this->umesh_id_to_bullet_indexs.find(kuwasiku[i].my_umesh->getUMESHID()) != umesh_id_to_bullet_indexs.end()) {
		//	bullets[umesh_id_to_bullet_indexs[kuwasiku[i].my_umesh->getUMESHID()]].mesh_i->setIsRender(false);
		//}
		//if (this->umesh_id_to_bullet_indexs.find(kuwasiku[i].aite_umesh->getUMESHID()) != umesh_id_to_bullet_indexs.end()) {
		//	bullets[umesh_id_to_bullet_indexs[kuwasiku[i].my_umesh->getUMESHID()]].mesh_i->setIsRender(false);
		//}
	}

}

void BulletController::byouga(Graphics* g, MYMATRIX* view, MYMATRIX* proj, float dsecond, int stamp) {

	if (mis) {
		mis->render(g);
		if (bullets) {
			for(int i=0;i<KTROBO_BULLET_CONTROLLER_BULLET_NUM;i++) {
				if (bullets[i].getIsUse()) {
					if (bullets[i].atarihan->meshs[0] && bullets[i].atarihan->meshs[0]->mesh) {
						for(int k=0;k< KTROBO_MESH_BONE_MAX;k++) {
							if (bullets[i].atarihan->meshs[0]->is_bone_obbs_use[k]) {
								MYMATRIX idenmat;
								MyMatrixIdentity(idenmat);
							//	g->drawOBBFill(g,0xFFFFFFFF,&idenmat,view,proj,&bullets[i].atarihan->meshs[0]->bone_obbs[k]);
							}

						}
					}
				}
			}
		}
	}

}


void BulletController::update(Graphics* g, AtariHantei* hantei, float dsecond, int stamp) {
	if (bullets) {
	for (int i=0;i<KTROBO_BULLET_CONTROLLER_BULLET_NUM;i++) {
		bullets[i].update(g,hantei, dsecond, stamp);
	}
	}
}


BulletController::BulletController() {
	this->hantei = 0;
	this->bullets = 0;
	mis = 0;
	dummy_mesh = 0;
}

BulletController::~BulletController() {
}
void BulletController::Init(Graphics* g, AtariHantei* hantei, MyTextureLoader* loader) {

	this->hantei = hantei;

	if (!dummy_mesh) {
		dummy_mesh = new Mesh();
		dummy_mesh->readMesh(g, KTROBO_BULLET_MESH_DUMMY_FILENAME,loader);
		dummy_mesh->readAnime(KTROBO_BULLET_MESH_ANIME_DUMMY_FILENAME);
		dummy_mesh->animate(0,true);

		// bullet_mesh�̓ǂݍ���
		Mesh* m = new Mesh();
		m->readMesh(g,KTROBO_BULLET_MESH_RIFLE_FILENAME,loader);
		m->readAnime(KTROBO_BULLET_MESH_ANIME_RIFLE_FILENAME);
		
		bullet_meshs.push_back(m);
		MyMatrixScaling(m->rootbone_matrix_local_kakeru,1.2f,1.2f,1.2f);
		m->animate(0,true);
		bullet_mesh_index.insert(std::pair<string,int>(string(KTROBO_BULLET_MESH_RIFLE_INDEXNAME),0));

		Mesh* mm = new Mesh();
		mm->readMesh(g, KTROBO_BULLET_MESH_LASERRIFLE_FILENAME, loader);
		mm->readAnime(KTROBO_BULLET_MESH_ANIME_LASERRIFLE_FILENAME);
		bullet_meshs.push_back(mm);
		MyMatrixScaling(mm->rootbone_matrix_local_kakeru,1.2f,1.2f,1.2f);
		mm->animate(0,true);
		bullet_mesh_index.insert(std::pair<string,int>(string(KTROBO_BULLET_MESH_LASERRIFLE_INDEXNAME),1));




	}
	hantei->setIsUnitUpdated();

	if (!mis) {
		mis = new MeshInstanceds(g, loader);
	}

	if (hantei && mis) {
		MYMATRIX idenmat;
		MyMatrixIdentity(idenmat);
		bullets = new Bullet[KTROBO_BULLET_CONTROLLER_BULLET_NUM];
		for (int i=0;i<KTROBO_BULLET_CONTROLLER_BULLET_NUM; i++) {
			// mesh_instanceds ������
			
			MeshInstanced* mi = mis->makeInstanced(dummy_mesh,dummy_mesh,NULL,KTROBO_MESH_BONE_NULL,false,&idenmat);
			//���̎��_��hantei�ɒǉ������
			bullets[i].Init(g,hantei, mi);
			//bullets[i].atarihan->setXYZ(i,i,i);

			bullets[i].atarihan->setXYZ(i/20 * 10, i%20 * 10, rand()%1000000/100-50);
			bullets[i].atarihan->calcJyusinAndR(true);
			// calcjyusinr�ł͍��̂Ƃ���v�Z����Ȃ��̂�
			bullets[i].atarihan->meshs[0]->bone_obbs[0].c = MYVECTOR3(bullets[i].atarihan->x, bullets[i].atarihan->y, bullets[i].atarihan->z);
			bullets[i].atarihan->jyusin = bullets[i].atarihan->meshs[0]->bone_obbs[0].c;
			bullets[i].atarihan->r = 1;
			MYMATRIX world;
			float x = bullets[i].atarihan->x;
			float y = bullets[i].atarihan->y;
			float z = bullets[i].atarihan->z;
			MyMatrixTranslation(world,x,y,z);
			mi->setWorld(&world);
			mi->setIsRender(false);//true);
			umesh_id_to_bullet_indexs.insert(std::pair<int,int>(bullets[i].atarihan->meshs[0]->getUMESHID(),i));
		}
	}

	




}

Bullet* BulletController::getEmptyBullet() {
	if (!bullets) return NULL;

	for (int i=0;i<KTROBO_BULLET_CONTROLLER_BULLET_NUM;i++) {
		if (!bullets[i].getIsUse()) {
			bullets[i].setIsUse(true);
			return &bullets[i];
		}
	}
	return NULL;

}


void BulletController::Release() {
	if (hantei) {
		hantei->clearUMeshUnits();
	}
	if (bullets) {
		delete[] bullets;
		bullets = 0;
	}

	if (mis) {
		mis->Release();
		delete mis;
		mis = 0;
	}

	if (dummy_mesh) {
		dummy_mesh->Release();
		delete dummy_mesh;
		dummy_mesh = 0;
	}

	vector<Mesh*>::iterator it = bullet_meshs.begin();
	while(it != bullet_meshs.end()) {
		Mesh* m = *it;
		delete m;
		m = 0;
		it++;
	}
	bullet_meshs.clear();
	bullet_mesh_index.clear();

}


void BulletController::calcUpdate(Graphics* g) {
	// mis�p
	if (mis) {

		mis->loadAnimeMatrixBasisToTexture(g);
		mis->loadMatrixLocalToTexture(g);
		mis->calcCombinedMatrixToTexture(g);
		mis->loadColorToTexture(g);

	}

}