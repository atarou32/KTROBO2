#ifndef KTROBOATARI_H
#define KTROBOATARI_H

#pragma once
#include "KTRoboMesh.h"
#include "MyDefine.h"
#include "KTRoboMeshInstanced.h"
#include <set>

namespace KTROBO {
#define KTROBO_MAX_TIKEI_HITOTU_INDEX 1024 // �ЂƂ̒n�`��face�̍ő吔 ����������������Ƃ��̓V�F�[�_�����������邱��
class UMesh {
public:
	Mesh* mesh;
private:
	static int id_max;
	int UMESH_ID;
	bool RootBone_connect_without_material_local;
	MYMATRIX RootBone_matrix_local_kakeru;
	MeshBone* rootbone_parent;
	int rootbone_parent_index;
	float anime_frame;
	bool is_use_vertexs_and_indexs;
	
public:
	int getUMESHID() {return UMESH_ID;}

	MESH_VERTEX* vertexs;
	UINT* indexs;
	OBB bone_obbs[KTROBO_MESH_BONE_MAX]; // �e�ʒu�A�p���A�A�j���̌v�Z��̂�����
	int bone_obbs_idx[KTROBO_MESH_BONE_MAX];
	bool is_bone_obbs_use[KTROBO_MESH_BONE_MAX];
	bool is_bone_obbs_atatta[KTROBO_MESH_BONE_MAX];
public:
	void setInfo();
	void setAnimeFrame(float frame) {
		anime_frame = frame;
	}
	void Animate(bool calculateOffsetMatrix) {
		if (mesh) {
			mesh->animate(anime_frame, calculateOffsetMatrix);
		}
	}
	void setMatrixKakeru(MYMATRIX* mat) {
		RootBone_matrix_local_kakeru = *mat;
	}
	void changeMesh(Mesh* mm) {
		if (is_use_vertexs_and_indexs) {
			throw new GameError(FATAL_ERROR, " cant change mesh in umesh");
			return;
		}
		for (int i=0;i <KTROBO_MESH_BONE_MAX;i++) {
			is_bone_obbs_use[i] = false;
			//bone_obbs_idx[i] = 0; // �ς��Ȃ�
		}

		mesh = mm;
	}

	UMesh() {
		mesh = 0;
		RootBone_connect_without_material_local = false;
		MyMatrixIdentity(RootBone_matrix_local_kakeru);
		rootbone_parent = 0;
		rootbone_parent_index = KTROBO_MESH_BONE_NULL;
		is_use_vertexs_and_indexs = false;
		vertexs = 0;
		indexs = 0;
		anime_frame = 0;
		for (int i=0;i <KTROBO_MESH_BONE_MAX;i++) {
			is_bone_obbs_use[i] = false;
			is_bone_obbs_atatta[i] = false;
			bone_obbs_idx[i] = 0;
		}
		UMESH_ID = id_max;
		id_max++;
	}

	UMesh(Graphics* g, char* filename, MyTextureLoader* tex_loader, Mesh* mesh, bool RootBone_connect_without_material_local, MYMATRIX* RootBone_matrix_local_kakeru, MeshBone* parent_bone, int rootbone_parent_index, bool is_use_vertexs_and_indexs) {
		this->mesh = mesh;
		vertexs = 0;
		indexs = 0;
		this->RootBone_connect_without_material_local = RootBone_connect_without_material_local;
		this->RootBone_matrix_local_kakeru = *RootBone_matrix_local_kakeru;
		this->rootbone_parent = parent_bone;
		this->rootbone_parent_index = rootbone_parent_index;
		this->is_use_vertexs_and_indexs = is_use_vertexs_and_indexs;
		if (is_use_vertexs_and_indexs) {
			if (mesh) {
				// vertexs �Ɓ@indexs ���擾����
				mesh->readMeshOnlyForSaveVertexIndex(g, filename,tex_loader, &vertexs, &indexs);  
			}
		}
		for (int i=0;i<KTROBO_MESH_BONE_MAX;i++) {
			is_bone_obbs_use[i] = false;
			bone_obbs_idx[i] = 0;
		}
		UMESH_ID = id_max;
		id_max++;

	}

	~UMesh() {
		
		if (vertexs) {
			delete[] vertexs;
		}
		if (indexs) {
			delete[] indexs;
		}
	}

};

class AtariHantei;
class UMeshUnit;

class AtariUnit {
public:
	enum AtariType {
		ATARI_TIKEI=0, // �n�`�͂��ׂĂ̖ʂƓ����蔻����s��
		ATARI_OBJECT=1, // �I�u�W�F�N�g�͕������(�{�[������)�Ɠ����蔻����s��
		ATARI_CHARA=2, // �L�����N�^�[�͕������(�{�[�����Ɓj�Ɠ����蔻����s��
		ATARI_WAZA=3, // �L�����N�^�[�̍U���̋Z�̔��� // ����������������Ƃ���shader������������
		ATARI_NONE=4 // ������Ȃ�
	};

	AtariType type;
	// �����蔻��̎d�g��
	// �n�`�Ƃ��ēo�^���ꂽ���b�V�����m�͓����蔻����s��Ȃ�
	// �n�`�ƃI�u�W�F�N�g�@�I�u�W�F�N�g���m�@�n�`�ƃL�����N�^�[�@�I�u�W�F�N�g�ƃL�����N�^�[�@�L�����N�^�[���m
	// �Z�ƃL�����N�^�[�@�Z�ƃI�u�W�F�N�g�@�Z�ƒn�`�i�e�̏ꍇ����������s��) 
	// �͍s��

	int atariidx; // �V�F�[�_�ɓn��idx
	UMeshUnit* umesh_unit; // ���b�V���������郆�j�b�g
	UMesh* umesh; // ���b�V��
	AtariUnit() {
		type = ATARI_TIKEI;
		atariidx = 0;
		umesh_unit = 0;
		umesh = 0;
	}
};


class UMeshUnit {
private:
	
	bool is_updated;
	// �p���ƈʒu�̏��

	bool is_enabled;
	AtariUnit::AtariType type; // atarihantei�ȊO���ς��Ȃ�����
public:
	float x;
	float y;
	float z;
	float rotx; // zxy �̏�
	float roty;
	float rotz;
	float scalex;
	float scaley;
	float scalez;
	
	
	// atarihantei�ȊO���Ă΂Ȃ��悤��
	void setType(AtariUnit::AtariType t) {
		type = t;
	}

	AtariUnit::AtariType getType() {
		return type;
	}
	
public:
	MYVECTOR3 v;
	MYMATRIX world;
	MYVECTOR3 jyusin;// ����̏d�S(xyz rotx roty rotz ����) �����蔻��Ɏg�p����
	float r;// ����̂�
	float dt; // �o�ߎ���
	vector<UMesh*> meshs;
	void setUMesh(UMesh* mm) {
		meshs.push_back(mm);
	}
	void removeUMesh(UMesh* mm, bool is_release) {
		vector<UMesh*>::iterator it = meshs.begin();
		while(it != meshs.end()) {
			UMesh* mmm = *it;
			if (mmm == mm) {
				// �J�����ă����[�u����
				if (is_release) {
					delete mmm;
					mmm = 0;
				}
				meshs.erase(it);
				return;
			}


			it++;
		}
	}
public:
	bool getIsEnabled() {return is_enabled;}
	void setIsEnabled(AtariHantei* hantei, bool t);
//	void setIsEnabledWithoutChangeOBBNado(
	


	UMeshUnit() {
		x = 0;
		y = 0;
		z = 0;
		rotx = 0;
		roty = 0;
		rotz = 0;
		v.float3.x = 0;
		v.float3.y = 0;
		v.float3.z = 0;
		jyusin.float3.x = 0;
		jyusin.float3.y = 0;
		jyusin.float3.z = 0;
		scalex = 1;
		scaley = 1;
		scalez = 1;
		r = 1;
		MyMatrixIdentity(world);
		is_updated = true;
		is_enabled = true;
		dt = 0;
	}
	void setWorld(MYMATRIX* nworld);
	void setXYZ(float x, float y, float z);
	void setXYZD(float x, float y, float z, float ddmax);

	void setROTXYZ(float rotx, float roty, float rotz);
	void setSCALEXYZ(float scalex,float scaley,float scalez) {
		this->scalex = scalex;
		this->scaley = scaley;
		this->scalez = scalez;
		is_updated = true;
	}
	void setDT(float d) {
		dt = d;
	}

	void setV(MYVECTOR3* v);
	void calcAnimeFrame(int meshnum, float* frames, bool* calculateoffsetmatrixs);
	void calcJyusinAndR(bool calcWorld=true);
	virtual void calcJyusinAndRForEmptyMesh() {
	};

	~UMeshUnit() {
		vector<UMesh*>::iterator it = meshs.begin();
		// UMesh ���d�����ēo�^���邱�Ƃ̂Ȃ��悤�ɂ���

		while (it != meshs.end()) {
			UMesh* em = *it;
			delete em;
			em = 0;
			it++;
		}
		meshs.clear();
	}

	void draw(Graphics* g,  MYMATRIX* view, MYMATRIX* proj, int meshnum, float* frames, bool* calculateoffsetmatrixs,
		bool is_draw_mesh, bool is_calc_animeframe, bool is_draw_jyusinR, bool is_draw_boneobb);

};

class Game;

class AtariBase {
protected: 
	bool setdayo_formoveshori;
	bool setkabedayo_formoveshori;
	bool istenjyou_formoveshori;
	float vdayo_formoveshori;
	MYVECTOR3 atari_offsetdayo;
public:
	UMeshUnit* atarihan;
public:
	AtariBase() { atari_offsetdayo = MYVECTOR3(0, 0, 0);  setdayo_formoveshori = false; istenjyou_formoveshori = false; setkabedayo_formoveshori = false; vdayo_formoveshori = 0; };
	virtual ~AtariBase(){};// Atarihan�̏����͎q�̃N���X�ł��
	virtual void atarishori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {};
	virtual void moveshori(Graphics* g, MYMATRIX* view, AtariHantei* hantei, float dt, int stamp) {};
	virtual void render(Graphics* g, Game* game, MYMATRIX* view, MYMATRIX* proj, float dt, int stamp) {};
	void setSetDayo(bool s) { setdayo_formoveshori = s; };
	void setSetKabeDayo(bool s) { setkabedayo_formoveshori = s; };
	void setVdayo(float s) {
		vdayo_formoveshori = s; 
	};
	void setAtariOffsetDayo(float x, float y, float z) {
		atari_offsetdayo = MYVECTOR3(x, y, z);
	};
	void getAtariOffsetDayo(MYVECTOR3* pp) {
		*pp = atari_offsetdayo;
	};
};



#define KTROBO_MAX_TIKEI_VERTEXS_COUNT 65535
#define KTROBO_MAX_TIKEI_INDEXS_COUNT 65535*3
#define KTROBO_MAX_ATARI_HANTEI_UNIT_NUM 4048

struct AtariUnitInfo{
	int atari_idx;
	int vertexs_place;
	int indexs_place;
	int vertex_count;
	int index_count;
	int unit_type;
	MYMATRIX world;
	MYVECTOR3 jyusin;
	MYVECTOR3 v;
	float r;
	float dt;
};

struct AtariUnitVertexs {
	MYVECTOR4 pos;
	MYVECTOR4 normal;
};
struct AtariUnitIndexs {
	unsigned int index;
};

struct AtariUnitIncrementCounter {
	unsigned int counter;
};

struct AtariUnitKumi {
	int atari_idx;
	int atari_idx2;
};

struct AtariUnitAns {
	int atari_idx;
	int obbidx;
	int atari_idx2;
	int obbidx2;
	MYVECTOR3 kouten_jyusin;
	MYVECTOR3 kouten_housen;
	int is_use;
};

struct AtariUnitAnsKWSK {

	AtariUnit::AtariType aite_type;
	AtariUnitAns* ans;
	UMeshUnit* aite;
	UMesh* aite_umesh;
	UMesh* my_umesh;
	UMeshUnit* my_umeshunit;
};

// ����OBB�̓A�j���[�V�����ƈʒu�p�����K�p���ꂽOBB
// ���̓K�p��GPU�ł͂Ȃ�CPU�ōs���Ă���

struct AtariUnitOBB {
	MYVECTOR3 c; // ���S�̍��W
	MYVECTOR3 u[3];
	MYVECTOR3 e; // ���S�_����ʂ܂ł̒���
};

struct AtariUnitTikeiToSoreigai {
	int atariidx;
	int obbidx;
	int atariidx2;
	int offset;
};

struct AtariUnitTikeiIgaiDousi {
	int atariidx;
	int obbidx;
	int atariidx2;
	int obbidx2;
};

// ���������ǂꂭ�炢�m�ۂ��Ă��邩�z��̐�����ۑ����Ă���
struct AtariHanteiTempCount {
	int vertexs_count;
	int indexs_count;
	int auinfo_count;
	int obbs_count;
	int kumi_count;
	int ans_count;
	int igaidousi_count;
	int soreigai_count;
};

// ansbuf2 �Ɋi�[����Ă��铖�����������擾����ۂ̃I�t�Z�b�g

#define KTROBO_ATARI_OFFSET 512

struct AtariHanteiTempOffset {
	int offset_atari;
	int atari_offset; // KTROBO_ATARI_OFFSET ������
	int nasi;
	int nasi2;
};



#define KTROBO_ATARI_SHADER_COMPUTE "resrc/shader/simple_atari_compute.cso"
#define KTROBO_ATARI_SHADER_COMPUTE2 "resrc/shader/simple_atari_compute_kuwasiku.cso"
#define KTROBO_ATARI_SHADER_COMPUTE_AIDA "resrc/shader/simple_atari_compute_aida.cso"
#define KTROBO_ATARI_SHADER_COMPUTE_AIDA_OFFSET "resrc/shader/simple_atari_compute_aida_offset.cso"
// AIDA ��autts �Ɓ@autid �̌v�Z���R���s���[�g�V�F�[�_�ōs��

#define KTROBO_ATARI_CALC_OBBS_IDX_TIKEI 0
#define KTROBO_ATARI_CALC_OBBS_IDX_DUMMY 1

#define KTROBO_ATARI_CALC_KUWASIKU_NONCALCYET 0
#define KTROBO_ATARI_CALC_KUWASIKU_WAITFORCOPYKEKKACALC 1
#define KTROBO_ATARI_CALC_KUWASIKU_NONCALCKUWASIKUYET 2
#define KTROBO_ATARI_CALC_KUWASIKU_WAITFORCOPYKEKKACALCKUWASIKU 3
#define KTROBO_ATARI_CALC_KUWASIKU_CALCED 4
#define KTROBO_ATARI_CALC_KUWASIKU_GETTED 5

class AtariHantei {
private:
	static const int kakuho_max = 7;
	static const int kakuho_counts[]; 
	static int getKakuhoCountsFromCount(int count);
	bool is_updated;
	bool is_unit_updated;
	int is_calc_kuwasiku;
	bool atari_start;

	bool need_calc_kumi;
	
public:

	int getAtattaCount() {
		return atatta_count;
	}

	AtariUnit units[KTROBO_MAX_ATARI_HANTEI_UNIT_NUM];
private:
	AtariHanteiTempCount max_count;
	AtariHanteiTempCount temp_count;
	AtariHanteiTempOffset temp_offset;
	int au_count;
	int au_tikei_count;
	int au_object_count;
	int au_chara_count;
	int au_waza_count;
	//int au_obbs_count;
	int atatta_count;
public:
	AtariUnitIncrementCounter icounter;
private:

	set<UMeshUnit*> state_changed_umeshunit; // �Čv�Z���K�v��umeshunit
	AtariHanteiTempCount state_changed_plus_count; // �Čv�Z�ɂ���ĕϓ�����J�E���g�̒l �_�~�[�̒l�̑����͍l�������̒l
	UMeshUnit* dummy_umeshunit; // �_�~�[�p��umeshunit �g���Ȃ��C���t�H�\���̂̂Ȃ��ɓ������
	UMesh* dummy_umesh;
	set<int> au_dummy_index;
	set<int> auinfo_dummy_index; // �_�~�[�������Ă���C���f�b�N�X��ۑ�����
	set<int> kumi_dummy_index;
	set<int> obbs_dummy_index;
	set<int> autid_dummy_index;
	set<int> autts_dummy_index;

	// ���̊֐��̌v�Z�̍ۂɕK�v�ƂȂ�
	set<int> au_dummy_index_used;
	set<int> auinfo_dummy_index_used;
	set<int> kumi_dummy_index_used;
	set<int> obbs_dummy_index_used;
	set<int> autid_dummy_index_used;
	set<int> autts_dummy_index_used;

	void clearDummyInfo(bool is_use_in_maedummy);
	bool isNeedMaeCalcWhenMaeCalcDummy(); // maxcount �𒴂��Ă��܂��ꍇ�S�Ă̍Čv�Z���K�v�ɂȂ�
	void setStateChangedUMeshUnitToDummy();
	void setInfoOfStateChangedUMeshUnit();

public:
	void setUnitStateChanged(UMeshUnit* umesh) {// type�͕ς��Ȃ����� umesh�̍\����isenabled���ς�����肵���ꍇ�ɌĂ�
		state_changed_umeshunit.insert(umesh);
	}

	bool getIsUpdated() {return is_updated;}
	void resetIsUnitUpdated() {is_unit_updated = true;}
	vector<UMeshUnit*> umesh_units;
private:
	vector<AtariUnit::AtariType> umesh_unit_types;

	AtariUnitVertexs* max_tikei_vertexs;
	AtariUnitIndexs* max_tikei_indexs;
	AtariUnitInfo* au_info;
	AtariUnitKumi* kumi;
	AtariUnitAns* ans;
	
	AtariUnitOBB* obbs;
	AtariUnitTikeiIgaiDousi* autid;
	AtariUnitTikeiToSoreigai* autts;
public:
	void setIsUnitUpdated() {
		is_unit_updated = true;
	}

	void setUMeshUnit(UMeshUnit* u, AtariUnit::AtariType type) {
		umesh_units.push_back(u);
		umesh_unit_types.push_back(type);
		u->setType(type);
		is_unit_updated = true;
		need_calc_kumi = true;
	}
	void ataristart() {atari_start =true;}
	void maeCalcDummy(Graphics* g); // maecalcdayo�̌�ɌĂ�
	void maecalcdayo(Graphics* g);
	void clearUMeshUnits() {
		umesh_units.clear();
		umesh_unit_types.clear();
		is_unit_updated = true;
		atari_start = false;
	}

public:
	void calcKumi(Graphics* g);
	void calcKumiKuwasiku(Graphics* g);
	void calcAuInfo(Graphics* g, bool calc_vertex_and_index);
	void calcObb(Graphics* g);
	
	void sendAtariWithOffset(ID3D11DeviceContext* context, int offset);

public:
	void drawKekka(Graphics* g, MYMATRIX* view, MYMATRIX* proj);
	int getAns(AtariUnitAnsKWSK* out_ans, UMeshUnit* oya,UMesh* oya2, int out_ans_num);
	int getAnsWaza(AtariUnitAnsKWSK* out_ans, int out_ans_num);
private:
	static MYSHADERSTRUCT mss;
	static MYSHADERSTRUCT mss2;
	static MYSHADERSTRUCT mss_aida;
	static MYSHADERSTRUCT mss_aida_offset;
	static ID3D11Buffer* buffer_count;
	static ID3D11Buffer* buffer_offset;
	static ID3D11Buffer* buffer_counter;

	ID3D11Buffer* buffer_vertexs;
	ID3D11Buffer* buffer_indexs;
	ID3D11Buffer* buffer_au_info;
	ID3D11Buffer* buffer_obbs;
	ID3D11Buffer* buffer_kumi;
	ID3D11Buffer* buffer_ans;
	ID3D11Buffer* buffer_ans2;
	ID3D11Buffer* buffer_ans2_aida;
	ID3D11Buffer* buffer_ans_copy;
	ID3D11Buffer* buffer_ans2_copy;
	ID3D11Buffer* buffer_ans2_copy_aida;
	ID3D11Buffer* buffer_autid;
	ID3D11Buffer* buffer_autts;

	ID3D11ShaderResourceView* buffer_vertexs_view;
	ID3D11ShaderResourceView* buffer_indexs_view;
	ID3D11ShaderResourceView* buffer_au_info_view;
	ID3D11ShaderResourceView* buffer_obbs_view;
	ID3D11ShaderResourceView* buffer_kumi_view;
	ID3D11ShaderResourceView* buffer_autid_view;
	ID3D11ShaderResourceView* buffer_autts_view;

	ID3D11UnorderedAccessView* buffer_ans_view;
	ID3D11UnorderedAccessView* buffer_ans2_view;
	ID3D11UnorderedAccessView* buffer_ans2_aida_view;
	void releaseBufferAndView();

public:
	static void compileShader(Graphics* g);
	static void del() {
		mss.Del();
		mss2.Del();
		mss_aida.Del();
		mss_aida_offset.Del();
		if (buffer_count) {
			buffer_count->Release();
			buffer_count = 0;
		}
		if (buffer_offset) {

			buffer_offset->Release();
			buffer_offset = 0;
		}

		if (buffer_counter) {
			buffer_counter->Release();
			buffer_counter = 0;
		}

	}

	static HRESULT createStructuredBuffer(Graphics* g, UINT element_size, UINT count, void* pInitData, ID3D11Buffer** ppBufferOut);
	static HRESULT createShaderResourceView(Graphics* g, ID3D11Buffer* pBuffer, ID3D11ShaderResourceView** ppSrvOut);
	static HRESULT createBufferUnorderedAccessView(Graphics* g, ID3D11Buffer* pBuffer, ID3D11UnorderedAccessView** ppUavOut);
	static HRESULT createBufferForCopy(Graphics* g, ID3D11Buffer* pBuffer, ID3D11Buffer** ppBufOut);
public:
	HRESULT copyKekkaToBufferForCopy(Graphics* g,bool isans1);
	HRESULT copyKekkaToBufferForCopy2(Graphics* g);// for aida
public:
	void copyCounterOfKekkaBuffer(Graphics* g);

	// �v�Z����̂͂��������ɍs��

	void runComputeShader(Graphics* g);
	void runComputeShaderKuwasiku(Graphics* g);
	void runComputeShaderAida(Graphics* g);
public:

	bool setIsCalcKuwasikuGetted() {
		if (is_calc_kuwasiku == KTROBO_ATARI_CALC_KUWASIKU_CALCED) {
			is_calc_kuwasiku = KTROBO_ATARI_CALC_KUWASIKU_GETTED;
			return true;
		}
		return false;
	}

	bool canGetAns() {
		if (is_calc_kuwasiku == KTROBO_ATARI_CALC_KUWASIKU_CALCED) {
			return true;
		}
		return false;
	}

	HRESULT copyKekkaForBufferCopy(Graphics* g) {
		if (is_calc_kuwasiku == KTROBO_ATARI_CALC_KUWASIKU_WAITFORCOPYKEKKACALC) {
			HRESULT hr = copyKekkaToBufferForCopy(g, true);
			is_calc_kuwasiku = KTROBO_ATARI_CALC_KUWASIKU_NONCALCKUWASIKUYET;
			return hr;
		}
		if (is_calc_kuwasiku == KTROBO_ATARI_CALC_KUWASIKU_WAITFORCOPYKEKKACALCKUWASIKU) {
			HRESULT hr = copyKekkaToBufferForCopy(g, false);
			is_calc_kuwasiku = KTROBO_ATARI_CALC_KUWASIKU_CALCED;
			return hr;
		}
		return S_OK;
	}

	void calc(Graphics* g) {
		if (!atari_start) return;
		if (is_calc_kuwasiku == KTROBO_ATARI_CALC_KUWASIKU_GETTED) {
			is_calc_kuwasiku = KTROBO_ATARI_CALC_KUWASIKU_NONCALCYET;
		}

		if (is_calc_kuwasiku == KTROBO_ATARI_CALC_KUWASIKU_NONCALCYET) {
			
			calcAuInfo(g,true);
			calcKumi(g);
			calcObb(g);
			copyCounterOfKekkaBuffer(g);
			runComputeShader(g);
			
			
		
			is_calc_kuwasiku = KTROBO_ATARI_CALC_KUWASIKU_WAITFORCOPYKEKKACALC;
		} else if (is_calc_kuwasiku == KTROBO_ATARI_CALC_KUWASIKU_NONCALCKUWASIKUYET){
			calcKumiKuwasiku(g);
			runComputeShaderKuwasiku(g);
			is_calc_kuwasiku = KTROBO_ATARI_CALC_KUWASIKU_WAITFORCOPYKEKKACALCKUWASIKU;
		}
	}
	~AtariHantei() {
		// UMeshUnit�͊O�ŏ���
		/*
		vector<UMeshUnit*>::iterator it = umesh_units.begin();
		while(it != umesh_units.end()) {
			UMeshUnit* uu = *it;
			delete uu;
			uu = 0;
			it++;
		}
		*/
		umesh_unit_types.clear();
		umesh_units.clear();

		if (max_tikei_vertexs) {
			delete[] max_tikei_vertexs;
			max_tikei_vertexs = 0;
		}

		if (max_tikei_indexs) {
			delete[] max_tikei_indexs;
			max_tikei_indexs = 0;
		}

		if (au_info) {
			delete[] au_info;
			au_info = 0;
		}
		if (kumi) {
			delete[] kumi;
			kumi = 0;
		}

		if (ans) {
			delete[] ans;
			ans = 0;
		}

		if (obbs) {
			delete[] obbs;
			obbs = 0;
		}

		if (autid) {
			delete[] autid;
			autid =0;
		}

		if (autts) {
			delete[] autts;
			autts = 0;
		}

		if (dummy_umeshunit) {
			delete dummy_umeshunit;
			dummy_umeshunit = 0;
		}

		releaseBufferAndView();
	}

	AtariHantei() {
		max_count.ans_count = 0;//kakuho_counts[0];
		max_count.auinfo_count = 0;//kakuho_counts[0];
		max_count.igaidousi_count =0;// kakuho_counts[0];
		max_count.indexs_count = 0;//kakuho_counts[0];
		max_count.kumi_count = 0;//kakuho_counts[0];
		max_count.obbs_count = 0;//kakuho_counts[0];
		max_count.soreigai_count =0;// kakuho_counts[0];
		max_count.vertexs_count = 0;//kakuho_counts[0];
		
		temp_count.ans_count = 0;
		temp_count.auinfo_count = 0;
		temp_count.igaidousi_count = 0;
		temp_count.indexs_count = 0;
		temp_count.kumi_count = 0;
		temp_count.obbs_count = 0;
		temp_count.soreigai_count = 0;
		temp_count.vertexs_count = 0;

		state_changed_plus_count.ans_count = 0;
		state_changed_plus_count.auinfo_count = 0;
		state_changed_plus_count.igaidousi_count = 0;
		state_changed_plus_count.indexs_count = 0;
		state_changed_plus_count.kumi_count = 0;
		state_changed_plus_count.obbs_count = 0;
		state_changed_plus_count.soreigai_count = 0;
		state_changed_plus_count.vertexs_count = 0;
		

		max_tikei_vertexs = new AtariUnitVertexs[kakuho_counts[2]];
		max_tikei_indexs = new AtariUnitIndexs[kakuho_counts[2]];
		au_info = new AtariUnitInfo[kakuho_counts[2]];
		autid = new AtariUnitTikeiIgaiDousi[kakuho_counts[2]];
		autts = new AtariUnitTikeiToSoreigai[kakuho_counts[2]];
		kumi = new AtariUnitKumi[kakuho_counts[2]];
		ans = new AtariUnitAns[kakuho_counts[2]];
		obbs = new AtariUnitOBB[kakuho_counts[2]];
		au_count = 0;
		au_tikei_count = 0;
		au_chara_count = 0;
		au_waza_count = 0;
		au_object_count = 0;
//		au_obbs_count=0;
		atari_start = false;
		is_updated = false;
		is_unit_updated = false;
		//KTROBO_ATARI_CALC_KUWASIKU_NONCALCYET
		is_calc_kuwasiku = KTROBO_ATARI_CALC_KUWASIKU_NONCALCYET;
		/*
		ID3D11Buffer* buffer_vertexs;
		ID3D11Buffer* buffer_indexs;
		ID3D11Buffer* buffer_au_info;
		ID3D11Buffer* buffer_obbs;
		ID3D11Buffer* buffer_kumi;
		ID3D11Buffer* buffer_ans;
		ID3D11Buffer* buffer_ans2;
		ID3D11Buffer* buffer_autid;
		ID3D11Buffer* buffer_autts;
		*/

		buffer_vertexs = 0;
		buffer_indexs = 0;
		buffer_au_info = 0;
		buffer_obbs = 0;
		buffer_kumi = 0;
		buffer_ans = 0;
		buffer_ans2 = 0;
		buffer_autid = 0;
		buffer_autts = 0;

		buffer_vertexs_view = 0;
		buffer_indexs_view = 0;
		buffer_au_info_view = 0;
		buffer_obbs_view = 0;
		buffer_kumi_view = 0;
		buffer_ans_view = 0;
		buffer_ans2_view = 0;
		buffer_ans2_aida_view = 0;
		buffer_autid_view = 0;
		buffer_autts_view = 0;
		buffer_ans_copy = 0;
		buffer_ans2_copy  =0;
		buffer_ans2_aida = 0;
		buffer_ans2_copy_aida = 0;
		atatta_count = 0;

	
		need_calc_kumi = false;

		dummy_umeshunit = 0; // �L�����N�^�Ƃ��Ĉ���
		dummy_umesh = 0;
		icounter.counter = 0;
	}
};


// ���l���Ă��邱�Ƃ͒n�`�̒��_�����ǂ��Ɏ������邩�Ƃ�������
// �n�`�̒��ɂ��������b�V���𕡐��o�^����ꍇ�͑��݂��Ă���

// �n�`�ƒn�`�͓����蔻����s��Ȃ�
// �n�`�ȊO�̂��̓��m�̓����蔻���OBB���m�ł�GPU���g���čs��
// �n�`�ƒn�`�ȊO�̓����蔻���vertexindex����OBB����GPU�ɑ����čs��
// �n�`���͕�����UMesh��vertex���m����������vertexs�Ƃ��� UMesh��indexs���m����������indexs�Ƃ���
// UmeshUnit �̏��i�ʒu�p��)���R���s���[�g�V�F�[�_�ɓn��
// OBB�����R���s���[�g�V�F�[�_�ɓn��
// �����蔻��̒i���
// 1. �S�Ă�UMeshUnit�̑g�ɑ΂��ďd�S�Ƃ����g���ē����蔻����s��
// 2. ��������UMeshUnit�̑g�Ɋւ���
// 2-a. �n�`���m�̏ꍇ�@��������
// 2-b. �n�`�ƒn�`�ȊO�̏ꍇ
//      vertexs �Ɓ@indexs �̏��(�n�`�Ȃ̂œ����Ȃ��̂ň��) �Ɓ@OBB�i�����������đ傫������) �œ����蔻����s��
// 2-c. �n�`�ȊO���m�̏ꍇ
//		OBB (v���������đ傫������)���m�œ����蔻����s��
// vertexs �Ɓ@indexs �̏�񂨂��UMeshUnit�̏����ǂ��i�[���邩
// 1.vertexs �̔z��
// 2.indexs �̔z��
// 3.AtariUnit�̏��, UMesh, UMeshUnit
/*
	int UMeshID, int UMeshUnitIDX, int atariidx, int vertexs_place, int indexs_place , int vertex_count, int index_count,
	MYMATRIX world, MYVECTOR3 v, MYVECTOR3 jyusin, float r
*/
// 4. �ǂ̓����胆�j�b�g���m�̔�����s�����̏��
// 5. ���ʂ̏�� atariidx umeshid umeshunitidx �̑g
// 5�̌��ʂ��g���Ă���ɍi�荞��ł���
// OBB�̏������͂��Ȃ���΂Ȃ�Ȃ�
// 1. OBB�̔z��œ��͂���
// 2. OBBUnit�݂����Ȃ��̂������atariidx�̌��ʏ�����������
// obbidx, atariidx, obbidx2,atariidx2�̓��͏��łQ�|���̔�����s��
// 
// 3. ���ʂ̏��@atariidx �̑g�ƌ�_�H

// 1.OBBUnit2�݂����Ȃ��̂������atariidx�̌��ʏ�����������
// obbidx atariidx atariidx2, vertexs_place,indexs_place, vertex_count, index_count �̓��͏���2-b�̔�����s��
// 2-b, 2-c�̏o�͂Ƃ��Ă�atariidx �̑g���o�͂����@�����CPU���œǂݍ���ŏ����Ɏg��
// 2. OBB�̔z��
// 3.vertexs�̔z��
// 4.indexs�̔z��
// 5. atariidx�̑g�ƒn�`�ʂ̏d�S�Ɩ@���H

// ���́iCPU���j�̃f�[�^���������̂�
// 1.��̓R���s���[�g�V�F�[�_�ɓn����`���ɂ���
// 2.�V�F�[�_������
// 3.�V�F�[�_����������

}

#endif