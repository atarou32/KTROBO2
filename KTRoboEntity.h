#pragma once
#ifndef KTROBOENTITY_H
#define KTROBOENTITY_H

#pragma once
#include <string>
#include <vector>
#include "KTRoboTexture.h"
#include "KTRoboAtari.h"
#include "KTRoboInput.h"
#include "KTRoboRobo.h"


using namespace std;

namespace KTROBO {

#define KTROBO_ENTITY_CHARACTER_ENTITY_MIN_ID 1000000
#define KTROBO_ENTITY_WAZA_UMESH_MESH_FILENAME "resrc/model/cube/pkcube.MESH"
#define KTROBO_ENTITY_WAZA_UMESH_MESH_ANIMENAME "resrc/model/cube/pkcube.ANIME"
#define KTROBO_ENTITY_WAZA_ATARI_MAX 200
	// 暫定的に１にする　元は２００


#define KTROBO_ENTITY_ATARI_UMESH_MESH_FILENAME "resrc/model/cube/pkcube.MESH"
#define KTROBO_ENTITY_ATARI_UMESH_MESH_ANIMENAME "resrc/model/cube/pkcube.ANIME"

	namespace ENTITY {
		namespace ESTATE {
			enum  ENTITY_STATE {
				NORMAL = 0,
				UNKNOWN = 1,
				NOFIGHT = 2, // 戦闘不能
				DEAD = 3,    // やられてアイテムに
				NOTALIVEYET = 4, // まだ出現していない
			};
		};
		namespace EBSTATE {
			enum ENTITY_BATTLE_STATE {
				UNCONSCIOUS = 0, // ボーっとしている
				NORMAL = 1, // 通常（敵には気をついていない)
				UNKNOWN = 2,
				BATTLE = 3, // 戦闘時（
				HIRUMI = 4,
				IKAKU = 5,
				DOWN = 6,
				BATTLERAID = 7,
				NOFIGHT = 8, // 戦闘不能
				DEAD = 9,
				NOTALIVEYET = 10,
				NOCANCEL = 11, // 行動中（レイドとダウン　NOFIGHT デッドには移行する)

			};
		};

		namespace EMSTATE {
			enum ENTITY_MOVE_STATE {
				STOP = 0,
				UNKNOWN = 1,
				MOVING = 2,
				GOAL = 3,
				NOTALIVEYET = 4,

			};
		};


	};
	using namespace ENTITY;


	class Entity
	{
	private:
		unsigned int id; //(USERNO)
		int hp;
		int maxhp;
		string name;
	
		ESTATE::ENTITY_STATE state;
		
		EBSTATE::ENTITY_BATTLE_STATE bstate;
		
		EMSTATE::ENTITY_MOVE_STATE move_state;
		EMSTATE::ENTITY_MOVE_STATE turn_state;
		int move_key;
		int turn_key;
	protected:
		static Mesh* atari_mesh;
		MYVECTOR3 rot; // rotx roty rotz
		MYVECTOR3 pos;
		MYVECTOR3 v;
	public:
		virtual void setPos(float x, float y, float z) {
			pos = MYVECTOR3(x, y, z);
		};
		virtual void setMuki(MYVECTOR3* srot) {
			rot = *srot;
		};
		virtual void setV(float x, float y, float z) {
			v = MYVECTOR3(x, y, z);
		};

		static void AtariMeshInit(Graphics* g,MyTextureLoader* loader);
		static void AtariMeshDel();

		
	public:
		Entity(unsigned int id, int maxhp , string nam) {
			this->id = id;
			hp = maxhp;
			this->maxhp = maxhp;
			state = ESTATE::ENTITY_STATE::NOTALIVEYET;
			name = nam;
			bstate = EBSTATE::ENTITY_BATTLE_STATE::NOTALIVEYET;
			move_state = EMSTATE::ENTITY_MOVE_STATE::NOTALIVEYET;
			turn_state = EMSTATE::ENTITY_MOVE_STATE::NOTALIVEYET;
			move_key = 0;
			turn_key = 0;
			rot = MYVECTOR3(0, 0, 0);
			pos = MYVECTOR3(0, 0, 0);
			v = MYVECTOR3(0, 0, 0);
		};
		~Entity() {};

		unsigned int getID() { return id; };
		int getHP() { return hp; };
		void setHP(int hp) { this->hp = hp; };
		void setSTATE(ESTATE::ENTITY_STATE s) { state = s; };
		ESTATE::ENTITY_STATE getSTATE() { return state; };
		const char* getName() { return name.c_str(); };
		int getMAXHP() { return maxhp; };
		void setMoveKey(int move_k) {
			move_key = move_k;
		};
		void setTurnKey(int turn_k) {
			turn_key = turn_k;
		};
		virtual void calcAtariUMesh() {};
		virtual void calcMeshInstanced() {};
	};
	class CharacterEntity : public Entity, public AtariBase {
	protected:
		vector<UMeshUnit*> units;

		vector<Mesh*> meshs;
		vector<MeshInstanced*> mesh_is;


		UMeshUnit* atari_umesh;


		int tex_name;
		int tex_hpbar;
	public:
		void setBody(UMeshUnit* uu) {
			atari_umesh = uu;
		}
		CharacterEntity(Graphics* g, Texture* te, AtariHantei* hantei, MyTextureLoader* loader, unsigned int id, int maxhp, string nam) :
			Entity(id, maxhp, nam) {
			atarihan = new UMeshUnit();
			MYMATRIX iden_mat;
			MyMatrixIdentity(iden_mat);
			UMesh* um = new UMesh(g, Entity::atari_mesh->filename, loader, Entity::atari_mesh, false, &iden_mat, NULL, KTROBO_MESH_BONE_NULL, false);
			atarihan->setUMesh(um);
			atarihan->calcJyusinAndR();
			hantei->setUMeshUnit(atarihan, AtariUnit::AtariType::ATARI_CHARA);
			atari_umesh = 0;

		};
		~CharacterEntity() {

			if (atarihan) {
				delete atarihan;
				atarihan = 0;
			}

		};
		void regMesh(Mesh* m) {
			meshs.push_back(m);
		};
		void regMeshI(MeshInstanced* mi) {
			mesh_is.push_back(mi);
		};
		void regUMeshUnit(UMeshUnit* uu) {
			units.push_back(uu);
		};
		void Release() {

		};
		void calcAtariUMesh();
		virtual void setPos(float x, float y, float z);
		virtual void setMuki(MYVECTOR3* srot);
		virtual void calcMeshInstanced();
		virtual void atarishori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp);
		virtual void moveshori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp);
		virtual void fireUpdate(Graphics* g, Game* game, Scene* scene, AtariHantei* hantei, BulletController* bullet_c, float dt, int stamp) {};
	};

	class EnemyEntityPart : public Entity, public AtariBase {
	private:

		// 部位では　属するUMeshから位置を計算して
		// 当たり判定の位置を更新する　
		// class atarihanteiで計算して, 攻撃が当たっていたりしたら
		// 攻撃パケットを送る

		
	
		UMeshUnit* unit; // 部位が属するumeshunit // enemyentity が持っている
		UMesh* um;       // 部位が属するumesh(Mesh)
		MeshBone* bone;  // 部位が属するbone

		
	public:
		EnemyEntityPart(Graphics* g, AtariHantei* hantei,  MyTextureLoader* loader,unsigned int id, int maxhp, string nam) : Entity(id, maxhp, nam) {
			atarihan = new UMeshUnit();
			MYMATRIX iden_mat;
			MyMatrixIdentity(iden_mat);
			UMesh* um = new UMesh(g, Entity::atari_mesh->filename, loader, Entity::atari_mesh, false, &iden_mat, NULL, KTROBO_MESH_BONE_NULL, false);
			atarihan->setUMesh(um);
			atarihan->calcJyusinAndR();
			hantei->setUMeshUnit(atarihan, AtariUnit::AtariType::ATARI_CHARA);
		}

		~EnemyEntityPart() {
			if (atarihan) {
				delete atarihan;
				atarihan = 0;
			}
		}

		void reg(MYVECTOR3* part_pos, UMeshUnit* unit,
			UMesh* um, MeshBone* bone) {
			this->pos =* part_pos;
			
			this->unit = unit;
			this->um = um;
			this->bone = bone;
			
		}
		void Release() {};
		virtual void setPos(float x, float y, float z);
		virtual void setMuki(MYVECTOR3* srot);
		virtual void calcAtariUMesh();
		virtual void calcMeshInstanced();
		virtual void fireUpdate(Graphics* g, Game* game, Scene* scene, AtariHantei* hantei, BulletController* bullet_c, float dt, int stamp) {};
	};
	class CharacterEntity;
	class EnemyEntity : public CharacterEntity{
	private:
		// エネミーには　当たり判定が複数ある
		vector<EnemyEntityPart*> parts;
//		vector<UMeshUnit*> units; // 表示用のUMeshUnit
		
//		vector<Mesh*> meshs;      // 
//		vector<MeshInstanced*> mesh_is;

//		UMeshUnit* atari_umesh; // このumeshから位置と大きさを取る


//		int tex_name;
//		int tex_hpbar;


	public:

		void setPart(EnemyEntityPart* p) { 
			// setPartするのはクエスト受注時などの
			// スレッドがあまり動いていない時
			parts.push_back(p);
		}
	/*	void regMesh(Mesh* m) {
			meshs.push_back(m);
		};
		void regMeshI(MeshInstanced* mi) {
			mesh_is.push_back(mi);
		};
		void regUMeshUnit(UMeshUnit* uu) {
			units.push_back(uu);
		};

		void setBody(UMeshUnit* uu) {
			atari_umesh = uu;
		}
		*/
		EnemyEntity(Graphics* g, Texture* te, AtariHantei* hantei,MyTextureLoader* loader, unsigned int id, int maxhp, string nam) : CharacterEntity(g,te,hantei,loader,id, maxhp, nam) 
		{
		
			};
		~EnemyEntity() {
			
		
		
		};
	
	};

	class PlayerCharacterEntity : public CharacterEntity, public INPUTSHORICLASS {
	private:
		float camera_rotx;
		float camera_roty;


	public:
		float getCameraRotX() { return camera_rotx; };
		float getCameraRotY() { return camera_roty; };
		void setCameraRotX(float x) { camera_rotx = x; };
		void setCameraRotY(float y) { camera_roty = y; };
		PlayerCharacterEntity(Graphics* g, Texture* te, AtariHantei* hantei,MyTextureLoader* loader, unsigned int id, int maxhp, string nam)
			: CharacterEntity(g, te, hantei,loader, id, maxhp, nam) {
			camera_rotx = 0;
			camera_roty = 0;
			
		};
		~PlayerCharacterEntity() {
		
			};

		void Release() {};

		bool handleMessage(int msg, void* data, DWORD time) {

			MYINPUTMESSAGESTRUCT* input = (MYINPUTMESSAGESTRUCT*)data;
			float x = input->getMOUSESTATE()->mouse_x;
			float y = input->getMOUSESTATE()->mouse_y;
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
			if (input->getMSGID() == KTROBO_INPUT_MESSAGE_ID_MOUSEMOVE) {
				float dx = 0.03f * input->getMOUSESTATE()->mouse_dx;
				float dy = 0.03f * input->getMOUSESTATE()->mouse_dy;
				camera_rotx += dy;
				if (camera_rotx > 1.5) {
					camera_rotx = 1.5;
				}
				if (camera_rotx < -1.5) {
					camera_rotx = -1.5;
				}

				camera_roty -= dx;
				if (camera_roty > 2.1f) {
					camera_roty = 2.1f;
				}
				if (camera_roty < -2.1f) {
					camera_roty = -2.1f;
				}
			}
			
			CS::instance()->leave(CS_MESSAGE_CS,"leave");
			return false;
		};
	
	};

	class RoboPlayerCharacterEntity : public PlayerCharacterEntity {
	public:
		Robo* robo;

		RoboPlayerCharacterEntity(Graphics* g, Texture* te, AtariHantei* hantei, MyTextureLoader* loader, unsigned int id, int maxhp, string nam)
			: PlayerCharacterEntity(g, te, hantei, loader, id, maxhp, nam) {
			
			robo = new Robo();
			robo->init(g, loader, hantei);
			
			robo->atarihan->calcJyusinAndR();
			// ロボのmesh を　characterentity に登録する
			this->regUMeshUnit(robo->atarihan);
			this->setBody(robo->atarihan);
			this->setPos(0, 0, 0);
			this->calcAtariUMesh();
			this->calcMeshInstanced();
			robo->atarihan->calcJyusinAndR();
			MYVECTOR3 robopos = MYVECTOR3(0, 0, 0);// MYVECTOR3(robo->atarihan->x, robo->atarihan->y, robo->atarihan->z);
			MYVECTOR3 jyusinpos = robo->atarihan->jyusin;
			MYVECTOR3 pp;
			MyVec3Subtract(pp, robopos, jyusinpos);
			this->setAtariOffsetDayo(pp.float3.x, pp.float3.y,  pp.float3.z);
		};
		~RoboPlayerCharacterEntity() {
			if (robo) {
				robo->release();
				delete robo;
				robo = 0;
			}
		};

		

		bool handleMessage(int msg, void* data, DWORD time);
		void atarishori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp);
		void moveshori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp);
		void render(Graphics* g, Game* game, MYMATRIX* view, MYMATRIX* proj, float dt, int stamp);
		virtual void fireUpdate(Graphics* g, Game* game, Scene* scene, AtariHantei* hantei, BulletController* bullet_c, float dt, int stamp);
	};

	// ロボによる弾ではなく範囲技
	class Waza {

	private:


		Entity* ateta_entity; // 技を使ったエンティティ
		UMeshUnit* entity_umeshunit; // 技を使ったエンティティのUMeshUnit
		UMesh* entity_umesh;
		MeshBone* entity_meshbone;

		UMeshUnit* waza_umeshunit;
		UMesh* waza_umesh;

		float scalex;
		float scaley;
		float scalez;

		float dtime; // 発生してから立った時間
		float hasseidtimestart; // 技が発生するdtime;
		float hasseidtimeend; // 技が終了するdtime;
		bool is_once_hit; // 一回でも誰かに当たればなくなるか
		bool is_use;
		int hitted_ids[30]; // 一度に３０の敵までヒットする
	public:
		Waza() {
			clear();
		};
		~Waza() {};

		void clear() {
			for (int i = 0; i < 30; i++) {
				hitted_ids[i] = 0;
			}
			scalex = 1;
			scaley = 1;
			scalez = 1;
			entity_umeshunit = 0;
			entity_umesh = 0;
			entity_meshbone = 0;
			waza_umeshunit = 0;
			waza_umesh = 0;
			ateta_entity = 0;
			is_once_hit = true;
			is_use = false;
			dtime = 0;
			hasseidtimestart = 0;
			hasseidtimeend = 0;
		};


	};

	//技があたった場合の処理を行う　HPの減少など

	class WazaAtatta {

	private:
		// あてたエンティティ
		Entity* ateta_entity;
		// あたったエンティティ
		Entity* atatta_entity;
		// あてた技
		Waza* atatta_waza;
		
	public:
		WazaAtatta() {
			ateta_entity = 0;
			atatta_entity = 0;
			atatta_waza = 0;
		};

		~WazaAtatta() {};




	};

	class EntityManager {
	private:
		AtariHantei* hantei;
		PlayerCharacterEntity* player;
		vector<CharacterEntity*> characters; // playerは含まない
		map<int, Entity*> map_id_to_entitys;
		map<UMeshUnit*, int> map_umeshunit_to_ids; // enemyの部位のIDは含まない　enemyのIDを含むので　部位に攻撃したかは再計算が必要
		vector<EnemyEntity*> enemys;
		vector<EnemyEntityPart*> enemyparts;
		vector<UMeshUnit*> entity_umeshunits;
		vector<Mesh*> entity_meshs;
		//vector<UMesh*> entity_umeshs;
		UMeshUnit* atari_units[KTROBO_ENTITY_WAZA_ATARI_MAX];
		//UMesh* atari_umeshs[KTROBO_ENTITY_WAZA_ATARI_MAX];
		Mesh* atari_mesh;

		Waza* wazas[KTROBO_ENTITY_WAZA_ATARI_MAX];
		WazaAtatta waza_atattas[KTROBO_ENTITY_WAZA_ATARI_MAX];
		MeshInstanceds* mis;
		vector<MeshInstanced*> mids;

		int turn_key_max; // ai 用のluaファイルを実行するためのkey
		int move_key_max;
		unsigned int enemy_entity_max_id;
		unsigned int character_entity_min_id;
	public:
		EntityManager() {
			player = 0;
			mis = 0;
			hantei = 0;
			turn_key_max = 1;
			move_key_max = 1;
			enemy_entity_max_id = 1;
			character_entity_min_id = KTROBO_ENTITY_CHARACTER_ENTITY_MIN_ID;
			// エネミーのID、キャラクターのIDは完成した場合は内部ではなく外部のサーバから通知される
		}
		~EntityManager() {
		};
		void Del() {
			if (mis) {
				mis->Release();
				delete mis;
				mis = 0;

			}
			mids.clear();

			for (int i = 0; i < KTROBO_ENTITY_WAZA_ATARI_MAX; i++) {
				if (wazas[i]) {

					delete wazas[i];
					wazas[i] = 0;
				}
				if (atari_units[i]) {

					delete atari_units[i];
					atari_units[i] = 0;
				}
			}
			if (atari_mesh) {
				atari_mesh->Release();
				delete atari_mesh;
				atari_mesh = 0;
			}


			/*

				PlayerCharacterEntity* player;
		vector<CharacterEntity*> characters; // playerは含まない
		vector<EnemyEntity*> enemys;
		vector<EnemyEntityPart*> enemyparts;
		vector<UMeshUnit*> entity_umeshunits;


			*/

			if (player) {
				player->Release();
				delete player;
				player = 0;
			}

			int csize = characters.size();
			for (int i = 0; i < csize; i++) {
				if (characters[i]) {
					characters[i]->Release();
					delete characters[i];
					characters[i] = 0;
				}

			}
			characters.clear();

			int esize = enemys.size();
			for (int i = 0; i < esize; i++) {
				if (enemys[i]) {
					enemys[i]->Release();
					delete enemys[i];
					enemys[i] = 0;
				}

			}
			enemys.clear();

			int epsize = enemyparts.size();
			for (int i = 0; i < epsize; i++) {
				if (enemyparts[i]) {
					enemyparts[i]->Release();
					delete enemyparts[i];
					enemyparts[i] = 0;
				}

			}
			enemyparts.clear();

			int emsize = entity_meshs.size();
			for (int i = 0; i < emsize; i++) {
				if (entity_meshs[i]) {
					entity_meshs[i]->Release();
					delete entity_meshs[i];
					entity_meshs[i] = 0;
				}

			}
			entity_meshs.clear();

			int eumsize = entity_umeshunits.size();
			for (int i = 0; i < eumsize; i++) {
				if (entity_umeshunits[i]) {

					delete entity_umeshunits[i];
					entity_umeshunits[i] = 0;
				}

			}
			entity_umeshunits.clear();
		}
		void Init(Graphics* g, MyTextureLoader* tex_l, AtariHantei* hantei) {
			this->hantei = hantei;
			if (!mis) {
				mis = new MeshInstanceds(g, tex_l);

				atari_mesh = new Mesh();
				atari_mesh->readMesh(g, KTROBO_ENTITY_WAZA_UMESH_MESH_FILENAME, tex_l);
				atari_mesh->readAnime(KTROBO_ENTITY_WAZA_UMESH_MESH_ANIMENAME);
				atari_mesh->animate(0, true);
				MYMATRIX iden_mat;
				MyMatrixIdentity(iden_mat);
				for (int i = 0; i < KTROBO_ENTITY_WAZA_ATARI_MAX; i++) {
					wazas[i] = new Waza();
					atari_units[i] = new UMeshUnit();
					UMesh* atari_umesh = new UMesh(g, KTROBO_ENTITY_WAZA_UMESH_MESH_FILENAME, tex_l, atari_mesh, false, &iden_mat,
						NULL, KTROBO_MESH_BONE_NULL, false);
					atari_units[i]->setUMesh(atari_umesh);
					atari_units[i]->setROTXYZ(0, 0, 0);
					atari_units[i]->setSCALEXYZ(1, 1, 1);
					atari_units[i]->setV(&MYVECTOR3(0, 0, 0));
					atari_units[i]->setXYZ(i * 10, i * 10, 100);
					atari_units[i]->calcJyusinAndR(true);

					MeshInstanced* mid = mis->makeInstanced(atari_mesh, atari_mesh, NULL, KTROBO_MESH_BONE_NULL, false, &iden_mat);
					mids.push_back(mid);
					mid->setWorld(&atari_units[i]->world);
					unsigned short framef[KTROBO_MESH_BONE_MAX];
					unsigned short framel[KTROBO_MESH_BONE_MAX];
					float framew[KTROBO_MESH_BONE_MAX];
					for (int j = 0; j < KTROBO_MESH_BONE_MAX; j++) {
						framef[j] = 0;
						framel[j] = 0;
						framew[j] = 1;
					}
					mid->setBoneIndexInfo(framef, framel, framew);

					mid->setIsRender(true);

				}
			}
		}

		void setViewProj(Graphics* g, MYMATRIX* view, MYMATRIX* proj);
		void updatePos(Graphics* g, Game* game, Scene* scene, AtariHantei* hantei, BulletController* bullet_c, float dsecond, int timestamp);
		void updateAtariAndMeshInstanced(Graphics* g, AtariHantei* hantei, float dsecond, int timestamp);
		void updatemis(Graphics* g);
		void byouga(Graphics* g,Game* game, MYMATRIX* view, MYMATRIX* proj,float dt, int stamp);
		void loadExample1(Graphics* g, MyTextureLoader* loader, Texture* te);
		PlayerCharacterEntity* getPlayer() { return player; };
		void atarishori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp);
		void moveshori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp);
	};

	class TikeiMap {
	private:
		AtariHantei* hantei;
		MeshInstanceds* mis;
		vector<UMeshUnit*> units;
		vector<MeshInstanced*> insts;
		vector<Mesh*> meshs;
	public:
		TikeiMap() { hantei = 0; mis = 0; };
		~TikeiMap() {};
		void Init(AtariHantei* h, MeshInstanceds* mids) {
			this->hantei = h;
			this->mis = mids;
		}

		void Del() {
			int si = units.size();
			for (int i = 0; i < si; i++) {
				if (units[i]) {
					delete units[i];
					units[i] = 0;
				}
			}

			int mi = meshs.size();
			for (int i = 0; i < mi; i++) {
				if (meshs[i]) {
					meshs[i]->Release();
					delete meshs[i];
					meshs[i] = 0;
				}
			}
			meshs.clear();
			units.clear();
			insts.clear();

		}
		void regmesh(Mesh* mesh) {
			meshs.push_back(mesh);
		}
		void reg(UMeshUnit* unit, MeshInstanced* inst) {
			units.push_back(unit);
			insts.push_back(inst);
			if (hantei) {
				hantei->setUMeshUnit(unit, AtariUnit::AtariType::ATARI_TIKEI);
			}
		}

		void setViewProj(Graphics* g, MYMATRIX* view, MYMATRIX* proj);
		void byouga(Graphics* g);
		void loadExample1(Graphics* g, MyTextureLoader* loader);

	};
}

#endif