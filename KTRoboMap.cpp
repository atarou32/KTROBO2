#include "KTRoboMap.h"
#include "KTRoboInput.h"
#include "KTRoboRobo.h"
#include "KTRoboGame.h"

using namespace KTROBO;



void RMap::registerMesh(string name, Mesh* m) {
	if (map_mesh_names.find(name) != map_mesh_names.end()) {


	}
	else {
		// register
		int index = map_meshs.size();
		map_meshs.push_back(m);
		map_mesh_names.insert(std::pair<string, int>(name, index));
	}

}

void RMap::registerTikei(UMeshUnit* um, MeshInstanced* mi) {
	MAP_ENT_TIKEI* ti = new MAP_ENT_TIKEI(um,mi);
	MAP_STRUCT* ms = new MAP_STRUCT();
	ms->struct_type = MAP_ENTITY_TYPE::MAP_ENTITY_TIKEI;
	ms->struct_id = max_struct_id;
	max_struct_id++;
	ms->ent = ti;
	map_structs.push_back(ms);
	map_meshinstanceds.push_back(mi);
	map_umeshunits.push_back(um);

}

void RMap::registerChara(UMeshUnit* um) {
	MAP_ENT_CHARA* ch = new MAP_ENT_CHARA(um);
	MAP_STRUCT* ms = new MAP_STRUCT();
	ms->struct_type = MAP_ENTITY_TYPE::MAP_ENTITY_CHARA;
	ms->struct_id = max_struct_id;
	max_struct_id++;
	ms->ent = ch;
	map_structs.push_back(ms);
	map_umeshunits.push_back(um);
}


void RMap::registerRobo(Robo* r, MAP_ENTITY_SHOZOKU_TYPE shz) {
	MAP_ENT_ROBO* tr = new MAP_ENT_ROBO(r,shz);
	MAP_STRUCT* ms = new MAP_STRUCT();
	ms->struct_type = MAP_ENTITY_TYPE::MAP_ENTITY_ROBO;
	ms->struct_id = max_struct_id;
	max_struct_id++;
	ms->ent = tr;

	int maxindex = map_structs.size();

	while (true) {
		vector<UMesh*>::iterator it = r->atarihan->meshs.begin();
		while (it != r->atarihan->meshs.end()) {
			UMesh* um = *it;
			umeshid_to_map_indexs.insert(std::pair<int, int>(um->getUMESHID(), maxindex));
			
			it++;
		}

		break;


	}



	map_structs.push_back(ms);
}

void RMap::registerObject(UMeshUnit* um, MeshInstanced* mi) {
	MAP_ENT_OBJECT* ob = new MAP_ENT_OBJECT(um,mi);
	MAP_STRUCT* ms = new MAP_STRUCT();
	ms->struct_id = max_struct_id;
	max_struct_id++;
	ms->struct_type = MAP_ENTITY_TYPE::MAP_ENTITY_OBJECT;
	ms->ent = ob;
	map_structs.push_back(ms);
}



Robo* RMap::getRobo(int UMESH_ID) {
	if (umeshid_to_map_indexs.find(UMESH_ID) != umeshid_to_map_indexs.end()) {
		MAP_STRUCT* ms = map_structs[umeshid_to_map_indexs[UMESH_ID]];

		return ms->ent->getRobo();

	}
	else {
		return NULL;
	}


}


void RMap::changePlayer(Robo* r) {
	// player_roboだけを置き換える
	if (player_robo) {
		InputMessageDispatcher::unregisterImpl(player_robo);
	}
	player_robo = r;
	InputMessageDispatcher::registerImpl(player_robo, NULL, NULL);

}


MAP_ENT_ROBO::~MAP_ENT_ROBO()
{
	if (rob) {
		rob->release();
		delete rob;
		rob = 0;
	}

};

#define KTROBO_MAP_POLYKOI 19
#define KTROBO_MAP_POLYKOMAX 22
#define KTROBO_MAP_POLYKO_MIGIUDE_INDEX 16
#define KTROBO_MAP_POLYKO_MIGIUDE_BONENAME "migitemaeBone"
#define KTROBO_MAP_POLYKO_MIGITE_BONENAME "migiteArmaBone"
#define KTROBO_MAP_POLYKO_HIDARIUDE_INDEX 9
#define KTROBO_MAP_POLYKO_HIDARIUDE_BONENAME "hidaritemaeBone"
#define KTROBO_MAP_POLYKO_HIDARITE_BONENAME "hidariteArmaBone"
#define KTROBO_MAP_POLYKO_MIGITE_INDEX 19
#define KTROBO_MAP_POLYKO_HIDARITE_INDEX 20
#define KTROBO_MAP_POLYKO_RWEAPON_TAIKEN_INDEX 21

RMapSetterExample::RMapSetterExample(Graphics* g, Game* game, AtariHantei* hantei, MeshInstanceds* mids, MyTextureLoader* loader, RMap* m) {
	Mesh* mesh;
	Mesh* mesh2;
	Mesh* mesh3[11];
	
	string polykomeshname[] = {
		"resrc/model/polyko/polyko_atama.mesh",
		"resrc/model/polyko/polyko_dou.mesh",
		"resrc/model/polyko/polyko_hana.mesh",
		"resrc/model/polyko/polyko_hidariasi.mesh",
		"resrc/model/polyko/polyko_hidarimabuta.mesh",
		"resrc/model/polyko/polyko_hidarimatuge.mesh",
		"resrc/model/polyko/polyko_hidarimayuge.mesh",
		"resrc/model/polyko/polyko_hidarimedama.mesh",
		"resrc/model/polyko/polyko_hidarititi.mesh",
		"resrc/model/polyko/polyko_hidariude.mesh",
		"resrc/model/polyko/polyko_migiasi.mesh",
		"resrc/model/polyko/polyko_migimabuta.mesh",
		"resrc/model/polyko/polyko_migimatuge.mesh",
		"resrc/model/polyko/polyko_migimayuge.mesh",
		"resrc/model/polyko/polyko_migimedama.mesh",
		"resrc/model/polyko/polyko_migititi.mesh",
		"resrc/model/polyko/polyko_migiude.mesh",
		"resrc/model/polyko/polyko_kubi.mesh",
		"resrc/model/polyko/polyko_kuti.mesh",
		"resrc/model/polyko/polyko_migite_migite.mesh",
		"resrc/model/polyko/polyko_hidarite_hidarite.mesh",
		"resrc/model/polyko/polyko_rweapon_taiken.mesh"
	};
	string polykoanimename[] = {
		"resrc/model/polyko/polyko_atama.anime",
		"resrc/model/polyko/polyko_dou.anime",
		"resrc/model/polyko/polyko_hana.anime",
		"resrc/model/polyko/polyko_hidariasi.anime",
		"resrc/model/polyko/polyko_hidarimabuta.anime",
		"resrc/model/polyko/polyko_hidarimatuge.anime",
		"resrc/model/polyko/polyko_hidarimayuge.anime",
		"resrc/model/polyko/polyko_hidarimedama.anime",
		"resrc/model/polyko/polyko_hidarititi.anime",
		"resrc/model/polyko/polyko_hidariude.anime",
		"resrc/model/polyko/polyko_migiasi.anime",
		"resrc/model/polyko/polyko_migimabuta.anime",
		"resrc/model/polyko/polyko_migimatuge.anime",
		"resrc/model/polyko/polyko_migimayuge.anime",
		"resrc/model/polyko/polyko_migimedama.anime",
		"resrc/model/polyko/polyko_migititi.anime",
		"resrc/model/polyko/polyko_migiude.anime",
		"resrc/model/polyko/polyko_kubi.anime",
		"resrc/model/polyko/polyko_kuti.anime",
		"resrc/model/polyko/polyko_migite_migite.anime",
		"resrc/model/polyko/polyko_hidarite_hidarite.anime",
		"resrc/model/polyko/polyko_rweapon_taiken.anime"
	};
	Mesh* polykomesh[KTROBO_MAP_POLYKOMAX];
	MeshInstanced* polykomi[KTROBO_MAP_POLYKOMAX];

	Mesh* unko;
	MeshInstanced* mesh_is[100];
	MeshInstanced* mesh_is2[30];
	float frame = 0;

	unko = new Mesh();
	unko->readMesh(g, "resrc/model/sora/sora.MESH", loader);
	unko->readAnime("resrc/model/sora/sora.ANIME");
	unko->animate(frame, true);
	m->registerMesh("resrc/model/sora/sora.MESH", unko);
	
	for (int i = 0; i < KTROBO_MAP_POLYKOI; i++) {
		polykomesh[i] = new Mesh();
		char p[512];
		memset(p, 0, 512);
		strcpy_s(p, polykomeshname[i].c_str());
		polykomesh[i]->readMesh(g, p, loader);
		memset(p, 0, 512);
		strcpy_s(p, polykoanimename[i].c_str());
		polykomesh[i]->readAnime(p);
		polykomesh[i]->animate(frame, true);
		m->registerMesh(polykomeshname[i], polykomesh[i]);
	}
	for (int i = KTROBO_MAP_POLYKOI; i < KTROBO_MAP_POLYKOMAX; i++) {
		polykomesh[i] = new Mesh();
		char p[512];
		memset(p, 0, 512);
		strcpy_s(p, polykomeshname[i].c_str());
		polykomesh[i]->readMesh(g, p, loader);
		memset(p, 0, 512);
		strcpy_s(p, polykoanimename[i].c_str());
		polykomesh[i]->readAnime(p);
		polykomesh[i]->animate(frame, true);
		m->registerMesh(polykomeshname[i], polykomesh[i]);
	}



	mesh = new Mesh();
	mesh->readMesh(g, "resrc/model/tikei/tikei_douro.MESH", loader);
	mesh->readAnime("resrc/model/tikei/tikei_douro.ANIME");
	mesh->animate(frame, true);
	m->registerMesh("resrc/model/tikei/tikei_douro.MESH", mesh);

	mesh2 = new Mesh();
	mesh2->readMesh(g, "resrc/model/tikei/tikei_densin.MESH", loader);
	mesh2->readAnime("resrc/model/tikei/tikei_densin.ANIME");
	mesh2->animate(frame, true);
	m->registerMesh("resrc/model/tikei/tikei_densin.MESH", mesh2);

	mesh3[0] = new Mesh();
	mesh3[0]->readMesh(g, "resrc/model/tikei/tikei_house.MESH", loader);
	mesh3[0]->readAnime("resrc/model/tikei/tikei_house.ANIME");
	mesh3[0]->animate(frame, true);
	m->registerMesh("resrc/model/tikei/tikei_house.MESH", mesh3[0]);




	
	mesh3[2] = new Mesh();
	mesh3[2]->readMesh(g, "resrc/model/bonebody/bonebody.MESH", loader);
	mesh3[2]->readAnime("resrc/model/bonebody/bonebody.ANIME");
	mesh3[2]->animate(frame, true);
	m->registerMesh("resrc/model/bonebody/bonebody.MESH", mesh3[2]);
	mesh3[3] = new Mesh();
	mesh3[3]->readMesh(g, "resrc/model/bonebody/hair.MESH", loader);
	mesh3[3]->readAnime("resrc/model/bonebody/hair.ANIME");

	mesh3[3]->RootBone->parent_bone = mesh3[2]->Bones[mesh3[2]->BoneIndexes["atamaBone"]];
	mesh3[3]->RootBone->parent_bone_index = mesh3[2]->BoneIndexes["atamaBone"];
	mesh3[3]->RootBone_connect_without_material_local = false;
	MYMATRIX inv;

	MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
	MyMatrixInverse(inv, NULL, inv);
	mesh3[3]->rootbone_matrix_local_kakeru = inv;
	mesh3[3]->animate(frame, true);
	
	m->registerMesh("resrc/model/bonebody/hair.MESH", mesh3[3]);

	mesh3[1] = new Mesh();

	//mesh3[1]->readMesh(g, "resrc/model/ponko2-3/pk2hidarime.MESH", demo->tex_loader);
	//mesh3[1]->readAnime("resrc/model/ponko2-3/pk2hidarime.ANIME");
	mesh3[1]->readMesh(g, "resrc/model/bonebody/head.MESH", loader);
	mesh3[1]->readAnime("resrc/model/bonebody/head.ANIME");
	mesh3[1]->RootBone->parent_bone = mesh3[2]->Bones[mesh3[2]->BoneIndexes["atamaBone"]];
	mesh3[1]->RootBone->parent_bone_index = mesh3[2]->BoneIndexes["atamaBone"];
	mesh3[1]->RootBone_connect_without_material_local = false;

	MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
	MyMatrixInverse(inv, NULL, inv);
	mesh3[3]->rootbone_matrix_local_kakeru = inv;
	mesh3[1]->animate(frame, true);
	m->registerMesh("resrc/model/bonebody/head.MESH", mesh3[1]);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	m->example1 = new Mesh();
	m->example1->readMesh(g, "resrc/model/bonebody/bonebody.MESH", loader);
	m->example1->readAnime("resrc/model/bonebody/bonebody.ANIME");
	m->example1->animate(frame, true);

	m->example2 = new Mesh();
	m->example2->readMesh(g, "resrc/model/bonebody/hair.MESH", loader);
	m->example2->readAnime("resrc/model/bonebody/hair.ANIME");

	m->example2->RootBone->parent_bone = m->example1->Bones[m->example1->BoneIndexes["atamaBone"]];
	m->example2->RootBone->parent_bone_index = m->example1->BoneIndexes["atamaBone"];
	m->example2->RootBone_connect_without_material_local = false;
	
	inv = m->example1->Bones[m->example1->BoneIndexes["atamaBone"]]->matrix_local;
	MyMatrixScaling(inv, 1/15.0, 1/15.0, 1/15.0);
	MyMatrixInverse(inv, NULL, inv);
	m->example2->rootbone_matrix_local_kakeru = inv;
	MYMATRIX scaling;
	
	m->example2->animate(frame, true);

	m->example3 = new Mesh();

	//mesh3[1]->readMesh(g, "resrc/model/ponko2-3/pk2hidarime.MESH", demo->tex_loader);
	//mesh3[1]->readAnime("resrc/model/ponko2-3/pk2hidarime.ANIME");
	m->example3->readMesh(g, "resrc/model/bonebody/head.MESH", loader);
	m->example3->readAnime("resrc/model/bonebody/head.ANIME");
	m->example3->RootBone->parent_bone = m->example1->Bones[m->example1->BoneIndexes["atamaBone"]];
	m->example3->RootBone->parent_bone_index = m->example1->BoneIndexes["atamaBone"];
	m->example3->RootBone_connect_without_material_local = false;
	MyMatrixScaling(inv, 1/15.0, 1/15.0, 1/15.0);
	MyMatrixInverse(inv, NULL, inv);
	m->example3->rootbone_matrix_local_kakeru = inv;// m->example1->Bones[m->example1->BoneIndexes["atamaBone"]]->combined_matrix;
	m->example3->animate(frame, true);
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	mesh3[4] = new Mesh();
	mesh3[4]->readMesh(g, "resrc/model/polyko/polyko_hidariasi.MESH", loader);
	mesh3[4]->readAnime("resrc/model/polyko/polyko_hidariasi.ANIME");
	mesh3[4]->animate(frame, true);
	m->registerMesh("resrc/model/polyko/polyko_hidariasi.MESH", mesh3[4]);
	*/
	/*
	mesh3[3] = new Mesh();
	mesh3[3]->readMesh(g, "resrc/model/ponko2-3/pk2kami.MESH", loader);
	mesh3[3]->readAnime("resrc/model/ponko2-3/pk2kami.ANIME");
	mesh3[3]->animate(frame, true);
	m->registerMesh("resrc/model/ponko2-3/pk2kami.MESH", mesh3[3]);

	mesh3[4] = new Mesh();
	mesh3[4]->readMesh(g, "resrc/model/ponko2-3/pk2kuti.MESH", loader);
	mesh3[4]->readAnime("resrc/model/ponko2-3/pk2kuti.ANIME");
	mesh3[4]->animate(frame, true);
	m->registerMesh("resrc/model/ponko2-3/pk2kuti.MESH", mesh3[4]);
	*/

	mesh3[5] = new Mesh();
	mesh3[5]->readMesh(g, "resrc/model/ponko2-3/pk2kubi.MESH", loader);
	mesh3[5]->readAnime("resrc/model/ponko2-3/pk2kubi.ANIME");
	mesh3[5]->animate(frame, true);
	m->registerMesh("resrc/model/ponko2-3/pk2kubi.MESH", mesh3[5]);

	mesh3[6] = new Mesh();
	mesh3[6]->readMesh(g, "resrc/model/ponko2-3/pk2mayuge.MESH", loader);
	mesh3[6]->readAnime("resrc/model/ponko2-3/pk2mayuge.ANIME");
	mesh3[6]->animate(frame, true);
	m->registerMesh("resrc/model/ponko2-3/pk2mayuge.MESH", mesh3[6]);

	/*
	mesh3[7] = new Mesh();
	mesh3[7]->readMesh(g, "resrc/model/ponko2-3/pk2midarime.MESH", demo->tex_loader);
	mesh3[7]->readAnime("resrc/model/ponko2-3/pk2midarime.ANIME");
	*/

	mesh3[8] = new Mesh();
	mesh3[8]->readMesh(g, "resrc/model/ponko2-3/pk2migimedama.MESH", loader);
	mesh3[8]->readAnime("resrc/model/ponko2-3/pk2migimedama.ANIME");
	mesh3[8]->animate(frame, true);
	m->registerMesh("resrc/model/ponko2-3/pk2migimedama.MESH", mesh3[8]);


	mesh3[7] = new Mesh();
	mesh3[7]->readMesh(g, "resrc/model/ponko2-4/pk2migihanddayo.MESH", loader);
	mesh3[7]->readAnime("resrc/model/ponko2-4/pk2migihanddayo.ANIME");
	mesh3[7]->RootBone->parent_bone = mesh2->Bones[mesh2->BoneIndexes["migiArmTekubiBone"]];
	mesh3[7]->RootBone->parent_bone_index = mesh2->BoneIndexes["migiArmTekubiBone"];
	mesh3[7]->RootBone_connect_without_material_local = true;
	mesh3[7]->animate(frame, true);
	m->registerMesh("resrc/model/ponko2-4/pk2migihanddayo.MESH", mesh3[7]);


	mesh3[10] = new Mesh();
	mesh3[10]->readMesh(g, "resrc/model/ponko2-4/pk2hidarihand.MESH", loader);
	mesh3[10]->readAnime("resrc/model/ponko2-4/pk2hidarihand.ANIME");
	mesh3[10]->RootBone->parent_bone = mesh2->Bones[mesh2->BoneIndexes["hidariArmTekubiBone"]];
	mesh3[10]->RootBone->parent_bone_index = mesh2->BoneIndexes["hidariArmTekubiBone"];// = mesh3[9]->RootBone->parent_bone->bone_index;
	mesh3[10]->RootBone_connect_without_material_local = true;
	mesh3[10]->animate(frame, true);
	m->registerMesh("resrc/model/ponko2-4/pk2hidarihand.MESH", mesh3[10]);

	mesh3[9] = new Mesh();
	mesh3[9]->readMesh(g, "resrc/model/bazooka/rweaponbazookaguna.MESH", loader);
	mesh3[9]->readAnime("resrc/model/bazooka/rweaponbazookaguna.ANIME");
	mesh3[9]->RootBone->parent_bone = mesh2->Bones[mesh2->BoneIndexes["migiArmTekubiBone"]];//mesh3[9]->Bones[mesh3[9]->BoneIndexes["MigiHandMotiBone"]];
	mesh3[9]->RootBone->parent_bone_index = mesh3[10]->RootBone->parent_bone->bone_index;
	mesh3[9]->RootBone_connect_without_material_local = false;
	mesh3[9]->animate(frame, true);
	m->registerMesh("resrc/model/bazooka/rweaponbazookaguna.MESH", mesh3[9]);


	


	/*
	for (int i = 0; i <= 10; i++) {
		
		if (i == 9) {
			mesh3[i]->animate(0, true);
		}
	}
	mesh3[7]->animate(frame, true);
	mesh3[8]->animate(frame, true);
	*/

	/*
	mesh3[8] = new Mesh();
	mesh3[8]->readMesh(g, "resrc/model/bazooka/rweaponbazookaguna.MESH", demo->tex_loader);
	mesh3[8]->readAnime("resrc/model/bazooka/rweaponbazookaguna.ANIME");
	mesh3[8]->RootBone->parent_bone = mesh3[7]->Bones[mesh3[7]->BoneIndexes["MigiHandMotiBone"]];
	mesh3[8]->RootBone->parent_bone_index = mesh3[7]->BoneIndexes["MigiHandMotiBone"];
	mesh3[8]->RootBone_connect_without_material_local = false;
	*/

	//throw new GameError(FATAL_ERROR,"test");



	MYMATRIX mat;
	MyMatrixIdentity(mat);
	MYMATRIX worldforg;
	MyMatrixRotationZ(worldforg, 3.14 / 2);
	MyMatrixMultiply(mat, mat, worldforg);

	MyMatrixScaling(worldforg, 1 / 3.0, 1 / 3.0, 1 / 3.0);
	MyMatrixMultiply(mat, mat, worldforg);

	MyMatrixRotationY(worldforg, -3.14 / 2);
	MyMatrixMultiply(mat, mat, worldforg);


	//	MYMATRIX worldforg;
	MyMatrixRotationZ(worldforg, 3.14 / 2);
	MyMatrixMultiply(mesh3[9]->rootbone_matrix_local_kakeru, mesh3[9]->rootbone_matrix_local_kakeru, worldforg);

	MyMatrixScaling(worldforg, 1 / 3.0, 1 / 3.0, 1 / 3.0);
	MyMatrixMultiply(mesh3[9]->rootbone_matrix_local_kakeru, mesh3[9]->rootbone_matrix_local_kakeru, worldforg);

	MyMatrixRotationY(worldforg, -3.14 / 2);
	MyMatrixMultiply(mesh3[9]->rootbone_matrix_local_kakeru, mesh3[9]->rootbone_matrix_local_kakeru, worldforg);

	Robo* robodayo;
	Robo* roboaitedayo;
	robodayo = new Robo();
	robodayo->init(g, loader, hantei);
	InputMessageDispatcher::registerImpl(robodayo, NULL, NULL);
	robodayo->atarihan->setXYZ(0, 3, 5);
	roboaitedayo = new Robo();
	roboaitedayo->init(g, loader, hantei);
	roboaitedayo->atarihan->setXYZ(10, 3, 10);
	game->robodayo = robodayo;
	game->roboaitedayo = roboaitedayo;
	m->registerRobo(robodayo,MAP_ENTITY_SHOZOKU_TYPE::MAP_ENTITY_SHOZOKU_SUN);
	m->registerRobo(roboaitedayo, MAP_ENTITY_SHOZOKU_TYPE::MAP_ENTITY_SHOZOKU_STAR);

	/*
	for (int i = 0; i<1; i++) {
		{
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			UMeshUnit* umesh_unit = new UMeshUnit();
			UMesh* um = new UMesh(g, "resrc/model/ponko2-4/pk2sailor.MESH", loader, mesh2, false, &idenmat,
				0, KTROBO_MESH_BONE_NULL, false);
			umesh_unit->setUMesh(um);
			m->registerChara(umesh_unit);
			//umesh_units.push_back(umesh_unit);
			bool tyo_unko = true;
			float frame_anime = 0;

			umesh_unit->setSCALEXYZ(1, 1, 1);
			umesh_unit->setXYZ(0, 0, 10);
			umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);

			umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_CHARA);
		}

	}
	UMeshUnit* uum;
	{
		MYMATRIX idenmat;
		MyMatrixIdentity(idenmat);
		UMeshUnit* umesh_unit = new UMeshUnit();
		uum = umesh_unit;

		UMesh* um = new UMesh(g, "resrc/model/ponko2-4/pk2sailordayo.MESH"/*"resrc/model/cube/pkcube.MESH"*/
		/*
				, loader, mesh2, false, &idenmat,
				0, KTROBO_MESH_BONE_NULL, false);
			umesh_unit->setUMesh(um);
			umesh_units.push_back(umesh_unit);
			bool tyo_unko = true;
			float frame_anime = 0;

			umesh_unit->setSCALEXYZ(1, 1, 1);
			umesh_unit->setXYZ(0, 3, -5);
			umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);

			umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_CHARA);
	*/
	/*sinai = new Sinai();
	sinai->init(g, demo->tex_loader,hantei);
	ss = new SinaiNigiru(sinai,umesh_unit);

	sfuru = new SinaiFuru(sinai,umesh_unit);
	*/
	/*
	SinaiFuruPart p;
	p.dt =0.1;
	p.rotx = 0;
	p.rotz = 0;
	p.tuka_dpos = MYVECTOR3(0,0,0);
	sfuru->setMenParts(&p);
	*/
	/*
	p.dt = 10;
	p.rotx = -1.57;
	p.rotz = 0;
	p.tuka_dpos = MYVECTOR3(0,0.7f,1.1f);
	sfuru->setMenParts(&p);

	p.dt = 20;
	p.rotx = 0.05f;
	p.rotz = 0;
	p.tuka_dpos = MYVECTOR3(0,0,1);
	sfuru->setMenParts(&p);
	*/
	//	sfuru->setKAMAE(-0.12,0,&MYVECTOR3(0,1.9,-0.20));
/*
}
*/

	unsigned short animf[KTROBO_MESH_INSTANCED_BONE_MAX];
	unsigned short animl[KTROBO_MESH_INSTANCED_BONE_MAX];
	float animw[KTROBO_MESH_INSTANCED_BONE_MAX];

	memset(animf, 0, sizeof(animf));
	memset(animl, 0, sizeof(animl));
	memset(animw, 0, sizeof(animw));

	{

		MYMATRIX idenmat;
		MyMatrixIdentity(idenmat);
		UMeshUnit* umesh_unit = new UMeshUnit();
		UMesh* um = new UMesh(g, "resrc/model/sora/sora.MESH", loader, unko, false, &idenmat,
			0, KTROBO_MESH_BONE_NULL, true); // doBoneのobbがtrueになるので大丈夫

		mesh_is[75] = mids->makeInstanced(unko, unko, NULL, NULL, false, &idenmat);
		umesh_unit->setUMesh(um);
		m->registerTikei(umesh_unit, mesh_is[75]);

		//umesh_units.push_back(umesh_unit);
		umesh_unit->setSCALEXYZ(300, 300, 300);
		umesh_unit->setXYZ(0, 0, 0);
		um->setAnimeFrame(0);
		um->Animate(true);
		umesh_unit->calcJyusinAndR();
		mesh_is[75]->setWorld(&umesh_unit->world);
		mesh_is[75]->setIsRender(true);
		mesh_is[75]->setBoneIndexInfo(animf, animl, animw);
		bool tyo_unko = true;
		float frame_anime = 0;

		umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
		umesh_unit->calcJyusinAndR();
		hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);

	}
	{
		for (int i = 0; i < KTROBO_MAP_POLYKOI; i++) {
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			UMeshUnit* umesh_unit = new UMeshUnit();
			char p[512];
			memset(p, 0, 512);
			strcpy_s(p, polykomeshname[i].c_str());
			UMesh* um = new UMesh(g, p, loader, polykomesh[i], false, &idenmat,
				0, KTROBO_MESH_BONE_NULL, false);
			umesh_unit->setUMesh(um);
			//umesh_units.push_back(umesh_unit);
			umesh_unit->calcJyusinAndR();
			//hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_CHARA);
			Mesh* unko = polykomesh[i];
			polykomi[i] = mids->makeInstanced(unko, unko, NULL, NULL, false, &idenmat);
			//umesh_unit->setUMesh(um);
			m->registerObject(umesh_unit, polykomi[i]);
			
			//umesh_units.push_back(umesh_unit);
			umesh_unit->setSCALEXYZ(10, 10, 10);
			umesh_unit->setXYZ(0, 0, 0);
			um->setAnimeFrame(0);
			um->Animate(true);
			umesh_unit->calcJyusinAndR();
			polykomi[i]->setWorld(&umesh_unit->world);
			polykomi[i]->setIsRender(true);
			polykomi[i]->setBoneIndexInfo(animf, animl, animw);
			bool tyo_unko = true;
			float frame_anime = 0;

			umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
			umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);

		
		}


		{
			int i = KTROBO_MAP_POLYKO_MIGITE_INDEX;
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			UMeshUnit* umesh_unit = new UMeshUnit();
			char p[512];
			memset(p, 0, 512);
			strcpy_s(p, polykomeshname[i].c_str());
			
			int parentbone_index = polykomesh[KTROBO_MAP_POLYKO_MIGIUDE_INDEX]->BoneIndexes[KTROBO_MAP_POLYKO_MIGIUDE_BONENAME];
			MeshBone* parentbone = polykomesh[KTROBO_MAP_POLYKO_MIGIUDE_INDEX]->Bones[parentbone_index];
			UMesh* um = new UMesh(g, p, loader, polykomesh[i], false, &idenmat,
				parentbone,parentbone_index, false);
			umesh_unit->setUMesh(um);
			//umesh_units.push_back(umesh_unit);
			umesh_unit->calcJyusinAndR();
			//hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_CHARA);
			Mesh* unko = polykomesh[i];
			polykomi[i] = mids->makeInstanced(unko, unko, polykomi[KTROBO_MAP_POLYKO_MIGIUDE_INDEX], parentbone_index, false, &idenmat);
			//umesh_unit->setUMesh(um);
			m->registerObject(umesh_unit, polykomi[i]);

			//umesh_units.push_back(umesh_unit);
			umesh_unit->setSCALEXYZ(10, 10, 10);
			umesh_unit->setXYZ(0, 0, 0);
			um->setAnimeFrame(0);
			um->Animate(true);
			umesh_unit->calcJyusinAndR();
			polykomi[i]->setWorld(&umesh_unit->world);
			polykomi[i]->setIsRender(true);
			polykomi[i]->setBoneIndexInfo(animf, animl, animw);
			bool tyo_unko = true;
			float frame_anime = 0;

			umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
			umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);


		}
		{
			int i = KTROBO_MAP_POLYKO_HIDARITE_INDEX;
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			UMeshUnit* umesh_unit = new UMeshUnit();
			char p[512];
			memset(p, 0, 512);
			strcpy_s(p, polykomeshname[i].c_str());

			int parentbone_index = polykomesh[KTROBO_MAP_POLYKO_HIDARIUDE_INDEX]->BoneIndexes[KTROBO_MAP_POLYKO_HIDARIUDE_BONENAME];
			MeshBone* parentbone = polykomesh[KTROBO_MAP_POLYKO_HIDARIUDE_INDEX]->Bones[parentbone_index];
			UMesh* um = new UMesh(g, p, loader, polykomesh[i], false, &idenmat,
				parentbone, parentbone_index, false);
			umesh_unit->setUMesh(um);
			//umesh_units.push_back(umesh_unit);
			umesh_unit->calcJyusinAndR();
			//hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_CHARA);
			Mesh* unko = polykomesh[i];
			polykomi[i] = mids->makeInstanced(unko, unko, polykomi[KTROBO_MAP_POLYKO_HIDARIUDE_INDEX], parentbone_index, false, &idenmat);
			//umesh_unit->setUMesh(um);
			m->registerObject(umesh_unit, polykomi[i]);

			//umesh_units.push_back(umesh_unit);
			umesh_unit->setSCALEXYZ(10, 10, 10);
			umesh_unit->setXYZ(0, 0, 0);
			um->setAnimeFrame(0);
			um->Animate(true);
			umesh_unit->calcJyusinAndR();
			polykomi[i]->setWorld(&umesh_unit->world);
			polykomi[i]->setIsRender(true);
			polykomi[i]->setBoneIndexInfo(animf, animl, animw);
			bool tyo_unko = true;
			float frame_anime = 0;

			umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
			umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);


		}

		{
			int i = KTROBO_MAP_POLYKO_RWEAPON_TAIKEN_INDEX;
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			UMeshUnit* umesh_unit = new UMeshUnit();
			char p[512];
			memset(p, 0, 512);
			strcpy_s(p, polykomeshname[i].c_str());

			int parentbone_index = polykomesh[KTROBO_MAP_POLYKO_MIGITE_INDEX]->BoneIndexes[KTROBO_MAP_POLYKO_MIGITE_BONENAME];
			MeshBone* parentbone = polykomesh[KTROBO_MAP_POLYKO_MIGITE_INDEX]->Bones[parentbone_index];
			UMesh* um = new UMesh(g, p, loader, polykomesh[i], false, &idenmat,
				0, KTROBO_MESH_BONE_NULL, false);
			umesh_unit->setUMesh(um);
			//umesh_units.push_back(umesh_unit);
			umesh_unit->calcJyusinAndR();
			//hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_CHARA);
			Mesh* unko = polykomesh[i];
			polykomi[i] = mids->makeInstanced(unko, unko, 0, KTROBO_MESH_BONE_NULL, false, &idenmat);
			//umesh_unit->setUMesh(um);
			m->registerObject(umesh_unit, polykomi[i]);

			//umesh_units.push_back(umesh_unit);
			umesh_unit->setSCALEXYZ(10, 10, 10);
			umesh_unit->setXYZ(0, 0, 0);
			um->setAnimeFrame(0);
			um->Animate(true);
			umesh_unit->calcJyusinAndR();
			polykomi[i]->setWorld(&umesh_unit->world);
			polykomi[i]->setIsRender(true);
			polykomi[i]->setBoneIndexInfo(animf, animl, animw);
			bool tyo_unko = true;
			float frame_anime = 0;

			umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
			umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);


		}

	}
	/*
{
MYMATRIX idenmat;
MyMatrixIdentity(idenmat);
UMeshUnit* umesh_unit = new UMeshUnit();
UMesh* um = new UMesh(g,"resrc/model/polyko/polyko_dou.MESH", loader,mesh3[2],false,&idenmat,
0,KTROBO_MESH_BONE_NULL,false);
umesh_unit->setUMesh(um);
//umesh_units.push_back(umesh_unit);
umesh_unit->calcJyusinAndR();
//hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_CHARA);
Mesh* unko = mesh3[2];
mesh_is[76] = mids->makeInstanced(unko, unko, NULL, NULL, false, &idenmat);
//umesh_unit->setUMesh(um);
m->registerTikei(umesh_unit, mesh_is[76]);

//umesh_units.push_back(umesh_unit);
umesh_unit->setSCALEXYZ(10, 10, 10);
umesh_unit->setXYZ(0, 0, 0);
um->setAnimeFrame(0);
um->Animate(true);
umesh_unit->calcJyusinAndR();
mesh_is[76]->setWorld(&umesh_unit->world);
mesh_is[76]->setIsRender(true);
mesh_is[76]->setBoneIndexInfo(animf, animl, animw);
bool tyo_unko = true;
float frame_anime = 0;

umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
umesh_unit->calcJyusinAndR();
hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);



}


{
	MYMATRIX idenmat;
	MyMatrixIdentity(idenmat);
	UMeshUnit* umesh_unit = new UMeshUnit();
	UMesh* um = new UMesh(g, "resrc/model/polyko/polyko_migiasi.MESH", loader, mesh3[3], false, &idenmat,
		0, KTROBO_MESH_BONE_NULL, false);
	umesh_unit->setUMesh(um);
	//umesh_units.push_back(umesh_unit);
	umesh_unit->calcJyusinAndR();

Mesh* 	unko = mesh3[3];
	mesh_is[77] = mids->makeInstanced(unko, unko, NULL, NULL, false, &idenmat);
	//umesh_unit->setUMesh(um);
	m->registerTikei(umesh_unit, mesh_is[77]);

	//umesh_units.push_back(umesh_unit);
	umesh_unit->setSCALEXYZ(10, 10, 10);
	umesh_unit->setXYZ(0, 0, 0);
	um->setAnimeFrame(0);
	um->Animate(true);
	umesh_unit->calcJyusinAndR();
	mesh_is[77]->setWorld(&umesh_unit->world);
	mesh_is[77]->setIsRender(true);
	mesh_is[77]->setBoneIndexInfo(animf, animl, animw);
	bool tyo_unko = true;
	float frame_anime = 0;

	umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
	umesh_unit->calcJyusinAndR();
	hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);

}


{
	MYMATRIX idenmat;
	MyMatrixIdentity(idenmat);
	UMeshUnit* umesh_unit = new UMeshUnit();
	UMesh* um = new UMesh(g, "resrc/model/polyko/polyko_hidariasi.MESH", loader, mesh3[4], false, &idenmat,
		0, KTROBO_MESH_BONE_NULL, false);
	umesh_unit->setUMesh(um);
	//umesh_units.push_back(umesh_unit);
	umesh_unit->calcJyusinAndR();

	Mesh* unko = mesh3[4];
	mesh_is[78] = mids->makeInstanced(unko, unko, NULL, NULL, false, &idenmat);
	//umesh_unit->setUMesh(um);
	m->registerTikei(umesh_unit, mesh_is[78]);

	//umesh_units.push_back(umesh_unit);
	umesh_unit->setSCALEXYZ(10, 10, 10);
	umesh_unit->setXYZ(0, 0, 0);
	um->setAnimeFrame(0);
	um->Animate(true);
	umesh_unit->calcJyusinAndR();
	mesh_is[78]->setWorld(&umesh_unit->world);
	mesh_is[78]->setIsRender(true);
	mesh_is[78]->setBoneIndexInfo(animf, animl, animw);
	bool tyo_unko = true;
	float frame_anime = 0;

	umesh_unit->calcAnimeFrame(1, &frame_anime, &tyo_unko);
	umesh_unit->calcJyusinAndR();
	hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);

}
*/

	


		//	return;

	//if ((i == 0) && (k == 0))continue;

for (int i = 0; i < 16; i+=3) {
		

		{
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			UMeshUnit* umesh_unit = new UMeshUnit();
			UMesh* um = new UMesh(g, "resrc/model/bonebody/bonebody.MESH", loader, mesh3[2], false, &idenmat,
				0, KTROBO_MESH_BONE_NULL, false); // doBoneのobbがtrueになるので大丈夫

			mesh_is[80 + i] = mids->makeInstanced(mesh3[2], mesh3[2], NULL, NULL, false, &idenmat);
			umesh_unit->setUMesh(um);
			m->registerObject(umesh_unit, mesh_is[80 + i]);

			//umesh_units.push_back(umesh_unit);
			umesh_unit->setSCALEXYZ(100, 100, 100);
			umesh_unit->setXYZ(10 + i * 10, 10, 100/*-4*/);
			um->setAnimeFrame(0);
			um->Animate(true);
			umesh_unit->calcJyusinAndR();
			mesh_is[80 + i]->setWorld(&umesh_unit->world);
			mesh_is[80 + i]->setIsRender(true);
			mesh_is[80 + i]->setBoneIndexInfo(animf, animl, animw);

			bool tyo_unko = true;
			float frame_anime = 0;

					umesh_unit->calcAnimeFrame(1,&frame_anime,&tyo_unko);
					umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);
		}
		{
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			MYMATRIX inv;

			MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
			MyMatrixInverse(inv, NULL, inv);
			idenmat = inv;
			UMeshUnit* umesh_unit = new UMeshUnit();
			UMesh* um = new UMesh(g, "resrc/model/bonebody/head.MESH", loader, mesh3[1], false, &idenmat,
				mesh3[2]->Bones[mesh3[2]->BoneIndexes["atamaBone"]], mesh3[2]->BoneIndexes["atamaBone"] , false); // doBoneのobbがtrueになるので大丈夫

			mesh_is[80 + i+1] = mids->makeInstanced(mesh3[1], mesh3[1], mesh_is[80+i], mesh3[2]->BoneIndexes["atamaBone"],false, &idenmat);
			umesh_unit->setUMesh(um);
			m->registerObject(umesh_unit, mesh_is[80 + i+1]);

			//umesh_units.push_back(umesh_unit);
			umesh_unit->setSCALEXYZ(100, 100, 100);
			umesh_unit->setXYZ(10 + i * 10, 10, 100/*-4*/);
			um->setAnimeFrame(0);
			um->Animate(true);
			umesh_unit->calcJyusinAndR();
			mesh_is[80 + i+1]->setWorld(&umesh_unit->world);
			mesh_is[80 + i+1]->setIsRender(true);
			mesh_is[80 + i+1]->setBoneIndexInfo(animf, animl, animw);

			bool tyo_unko = true;
			float frame_anime = 0;

					umesh_unit->calcAnimeFrame(1,&frame_anime,&tyo_unko);
					umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);
		}
		{
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			MYMATRIX inv;

			MyMatrixScaling(inv, 1 / 15.0, 1 / 15.0, 1 / 15.0);
			MyMatrixInverse(inv, NULL, inv);
			idenmat = inv;
			UMeshUnit* umesh_unit = new UMeshUnit();
			UMesh* um = new UMesh(g, "resrc/model/bonebody/hair.MESH", loader, mesh3[3], false, &idenmat,
				mesh3[2]->Bones[mesh3[2]->BoneIndexes["atamaBone"]], mesh3[2]->BoneIndexes["atamaBone"], false); // doBoneのobbがtrueになるので大丈夫

			mesh_is[80 + i + 2] = mids->makeInstanced(mesh3[3], mesh3[3], mesh_is[80+i], mesh3[2]->BoneIndexes["atamaBone"], false, &idenmat);
			umesh_unit->setUMesh(um);
			m->registerObject(umesh_unit, mesh_is[80 + i + 2]);

			//umesh_units.push_back(umesh_unit);
			umesh_unit->setSCALEXYZ(100, 100, 100);
			umesh_unit->setXYZ(10 + i * 10, 10, 100/*-4*/);
			um->setAnimeFrame(0);
			um->Animate(true);
			umesh_unit->calcJyusinAndR();
			mesh_is[80 + i + 2]->setWorld(&umesh_unit->world);
			mesh_is[80 + i + 2]->setIsRender(true);
			mesh_is[80 + i + 2]->setBoneIndexInfo(animf, animl, animw);
			
			bool tyo_unko = true;
			float frame_anime = 0;

					umesh_unit->calcAnimeFrame(1,&frame_anime,&tyo_unko);
					umesh_unit->calcJyusinAndR();
			hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_NONE);
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			{
				//if ((i == 0) && (k == 0))continue;
				MYMATRIX idenmat;
				MyMatrixIdentity(idenmat);
				UMeshUnit* umesh_unit = new UMeshUnit();
				UMesh* um = new UMesh(g, "resrc/model/tikei/tikei_douro.MESH", loader, mesh, false, &idenmat,
					0, KTROBO_MESH_BONE_NULL, true); // doBoneのobbがtrueになるので大丈夫

				mesh_is[i + 5 * k] = mids->makeInstanced(mesh, mesh, NULL, NULL, false, &idenmat);
				umesh_unit->setUMesh(um);
				m->registerTikei(umesh_unit, mesh_is[i + 5 * k]);

				//umesh_units.push_back(umesh_unit);
				umesh_unit->setSCALEXYZ(100, 100, 130);
				umesh_unit->setXYZ((i - 2) * 200, (k - 2) * 200, -100/*-4*/);
				um->setAnimeFrame(0);
				um->Animate(true);
				umesh_unit->calcJyusinAndR();
				mesh_is[i + 5 * k]->setWorld(&umesh_unit->world);
				mesh_is[i + 5 * k]->setIsRender(true);
				mesh_is[i + 5 * k]->setBoneIndexInfo(animf, animl, animw);
				bool tyo_unko = true;
				float frame_anime = 0;

				//		umesh_unit->calcAnimeFrame(1,&frame_anime,&tyo_unko);
				//		umesh_unit->calcJyusinAndR();
				hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_TIKEI);
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			{
				MYMATRIX idenmat;
				MyMatrixIdentity(idenmat);
				UMeshUnit* umesh_unit = new UMeshUnit();
				UMesh* um = new UMesh(g, "resrc/model/tikei/tikei_densin.MESH", loader, mesh2, false, &idenmat,
					0, KTROBO_MESH_BONE_NULL, true); // doBoneのobbがtrueになるので大丈夫

				mesh_is[i + 5 * k + 25] = mids->makeInstanced(mesh2, mesh2, NULL, NULL, false, &idenmat);
				umesh_unit->setUMesh(um);
				m->registerTikei(umesh_unit, mesh_is[i + 5 * k + 25]);

				//				umesh_units.push_back(umesh_unit);
				umesh_unit->setSCALEXYZ(100, 100, 130);
				umesh_unit->setXYZ((i - 2) * 200, (k - 2) * 200, -100/*0*/);
				um->setAnimeFrame(0);
				um->Animate(true);
				umesh_unit->calcJyusinAndR();
				mesh_is[i + 5 * k + 25]->setWorld(&umesh_unit->world);
				mesh_is[i + 5 * k + 25]->setIsRender(true);
				mesh_is[i + 5 * k + 25]->setBoneIndexInfo(animf, animl, animw);
				bool tyo_unko = true;
				float frame_anime = 0;

				//		umesh_unit->calcAnimeFrame(1,&frame_anime,&tyo_unko);
				//		umesh_unit->calcJyusinAndR();
				hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_TIKEI);
			}
		}
	}
	/*
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			{
				MYMATRIX idenmat;
				MyMatrixIdentity(idenmat);
				UMeshUnit* umesh_unit = new UMeshUnit();
				UMesh* um = new UMesh(g, "resrc/model/tikei/tikei_house.MESH", loader, mesh3[0], false, &idenmat,
					0, KTROBO_MESH_BONE_NULL, true); // doBoneのobbがtrueになるので大丈夫

				mesh_is[i + 5 * k + 50] = mids->makeInstanced(mesh3[0], mesh3[0], NULL, NULL, false, &idenmat);
				umesh_unit->setUMesh(um);
				*/
			/*	// カメラが家の中に向かないように当たり判定を設けておく　家の包括ＯＢＢの大きさよりちょっと小さめにしておく
				MyMatrixScaling(idenmat, mesh3[0]->houkatuobb.e.float3.x-0.91, mesh3[0]->houkatuobb.e.float3.y-0.91, mesh3[0]->houkatuobb.e.float3.z-0.91);
				UMesh* umesh = new UMesh(g, "resrc/model/cube/pkcube.MESH", loader, mesh3[1], false, &idenmat, NULL, KTROBO_MESH_BONE_NULL, true);
			
				umesh_unit->setUMesh(umesh);
				*/
			/*
				m->registerTikei(umesh_unit, mesh_is[i + 5 * k + 50]);
*/
				//				umesh_units.push_back(umesh_unit);
/*				umesh_unit->setSCALEXYZ(50, 50, 50);*/
//				umesh_unit->setXYZ((i - 2) * 200 - 100, (k - 2) * 200 - 100,-100/* 0*/);
/*				um->setAnimeFrame(0);
				um->Animate(true);
				umesh_unit->calcJyusinAndR();
				mesh_is[i + 5 * k + 50]->setWorld(&umesh_unit->world);
				mesh_is[i + 5 * k + 50]->setIsRender(true);
				mesh_is[i + 5 * k + 50]->setBoneIndexInfo(animf, animl, animw);
				bool tyo_unko = true;
				float frame_anime = 0;
				*/
				//		umesh_unit->calcAnimeFrame(1,&frame_anime,&tyo_unko);
				//		umesh_unit->calcJyusinAndR();
		/*		hantei->setUMeshUnit(umesh_unit, AtariUnit::AtariType::ATARI_TIKEI);

			}
		}
	}
	*/


	//*//

	/*
	MyMatrixRotationX(worldforg, -3.14/4*2);
	MyMatrixMultiply(mesh3[10]->RootBone->matrix_local, mesh3[10]->RootBone->matrix_local, worldforg);
	MyMatrixRotationZ(worldforg, 3.14/2);
	MyMatrixMultiply(mesh3[10]->RootBone->matrix_local, mesh3[10]->RootBone->matrix_local, worldforg);

	MyMatrixRotationY(worldforg, 3.14/2);
	MyMatrixMultiply(mesh3[10]->RootBone->matrix_local, mesh3[10]->RootBone->matrix_local, worldforg);
	MyMatrixRotationZ(worldforg, 3.14);
	MyMatrixMultiply(mesh3[10]->RootBone->matrix_local, mesh3[10]->RootBone->matrix_local, worldforg);
	MyMatrixRotationY(worldforg, 3.14/2);
	MyMatrixMultiply(mesh3[10]->RootBone->matrix_local, mesh3[10]->RootBone->matrix_local, worldforg);

	*/
}

void MAP_ENT_TIKEI::update() {
	unit->setXYZ(unit->x, unit->y, unit->z);
	unit->calcJyusinAndR();
	mesh_inst->setWorld(&unit->world);

}


void MAP_ENT_OBJECT::update() {

	static float dayo = 0;
	dayo += 0.01f;
	if (dayo > 512) {
		dayo = 0;
	}
	int testdayo = (int)dayo;
	unsigned short animf[KTROBO_MESH_INSTANCED_BONE_MAX];
	unsigned short animl[KTROBO_MESH_INSTANCED_BONE_MAX];
	float animw[KTROBO_MESH_INSTANCED_BONE_MAX];
	
	memset(animf, 0, sizeof(animf));
	memset(animl, 0, sizeof(animl));
	memset(animw, 0, sizeof(animw));
	for (int i = 0; i < KTROBO_MESH_BONE_MAX; i++) {


		animf[i] = 0;// testdayo / 100 + 1;
		animl[i] = 1;// testdayo / 100 + 2;
		animw[i] = 1-(testdayo%100)/100.0;
	}

	unit->setXYZ(unit->x, unit->y, unit->z);
	unit->calcJyusinAndR();
	mesh_inst->setWorld(&unit->world);
	mesh_inst->setBoneIndexInfo(animf, animl, animw);
}


void RMap::update() {
	
	vector<UMeshUnit*>::iterator it = map_umeshunits.begin();
	while (it != map_umeshunits.end()) {
		UMeshUnit* mm = *it;
		mm->setDT(35);
	//	mm->setXYZ(mm->x + 0.01f, mm->y, mm->z);
		mm->calcJyusinAndR();


		it++;
	}
	
	vector<MAP_STRUCT*>::iterator itt = map_structs.begin();
	while (itt != map_structs.end()) {
		MAP_STRUCT* ma = *itt;
		ma->ent->update();
		
		itt++;
	}


	/*
	unsigned short animf[KTROBO_MESH_INSTANCED_BONE_MAX];
	unsigned short animl[KTROBO_MESH_INSTANCED_BONE_MAX];
	float animw[KTROBO_MESH_INSTANCED_BONE_MAX];
	static int de = 0;
	de++;
	memset(animf, 0, sizeof(animf));
	memset(animl, 0, sizeof(animl));
	memset(animw, 0, sizeof(animw));
	vector<MeshInstanced*>::iterator ittt = map_meshinstanceds.begin();
	while (ittt != map_meshinstanceds.end()) {
		MeshInstanced* mi  = *ittt;
		mi->setBoneIndexInfo(animf, animl, animw);
		ittt++;
	}
	*/


}


void RMap::byougaHojyo(Graphics*g, MYMATRIX* view, MYMATRIX* proj) {

	MYMATRIX world;
	OBB r;

	vector<UMeshUnit*>::iterator it = map_umeshunits.begin();
	while (it != map_umeshunits.end()) {
		UMeshUnit* mm = *it;
		mm->setDT(35);
		mm->setXYZ(mm->x, mm->y, mm->z);
		mm->calcJyusinAndR();
 		//MyMatrixTranslation(world, mm->x, mm->y, mm->z);
		MyMatrixIdentity(world);
		for (int k = 0; k < mm->meshs.size();k++) {
			for (int i = 0; i < KTROBO_MESH_BONE_MAX; i++) {
				if (mm->meshs[k]->is_bone_obbs_use[i]) {
					r = mm->meshs[k]->bone_obbs[i];
					g->drawOBB(g, 0xFFFF0000, &world, view, proj, &r);
				}
			}
		}
		it++;
	}
	
	example1->animate(0, true);
	example2->animate(0, true);
	example3->animate(0, true);

	MyMatrixTranslation(world,30,10,100);
	MYMATRIX scaling;
	MyMatrixScaling(scaling, 100, 100, 100);
	MyMatrixMultiply(world, scaling, world);
	example1->draw(g, &world, view, proj);
	MyMatrixTranslation(world, 30, 10, 100);
	MyMatrixScaling(scaling, 100, 100, 100);
	MyMatrixMultiply(world, scaling, world);
	example2->draw(g, &world, view, proj);


	MyMatrixTranslation(world, 30, 10, 100);
	MyMatrixScaling(scaling, 100, 100, 100);
	MyMatrixMultiply(world, scaling, world);
	example3->draw(g, &world, view, proj);








}