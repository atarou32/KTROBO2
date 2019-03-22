#ifndef KTROBO_SCENE_GARAGE2_H
#define KTROBO_SCENE_GARAGE2_H

#pragma once
#include "KTRoboScene.h"
#ifndef KTROBO_TEXTURE_H
  #include "KTRoboTexture.h"
#endif
#include "KTRoboInput.h"
#include "KTRoboAtari.h"
#include "KTRoboLoadable.h"
#include "KTRoboRobo.h"

namespace KTROBO {

class Gamen2_part {
private:
	int pid;
	static unsigned int part_id;
	bool has_touroku;

	MYRECT rect;
	MYRECT nowRect;
	MYRECT destRect;
	float speed;
	float dt;
protected:
	bool is_focused;
	bool has_is_focused_changed;
	unsigned int color;
public:
	virtual void setRect(MYRECT* re) {
		rect = *re;
		nowRect = *re;
		destRect = *re;
	}
	virtual void moveTo(MYRECT* dest_re, float time) {};
	virtual bool moveLoop(float dt) { return false; }; // �����I�������true��Ԃ�
	virtual bool focused(int x, int y) {
		
		unsigned int bu = getButukariStatusPoint(x, y, &nowRect);
		if (bu & BUTUKARIPOINT_IN) {
			if (is_focused) {
				return true;
			}
			else {
				has_is_focused_changed = true;
				is_focused = true;
				return true;
			}
			
		}
		if (is_focused) {
			has_is_focused_changed = true;
			is_focused = false;
		}
		return false; 
	
	}; // �J�[�\�������킳�ꂽ�@�܂��́@�}�E�X�ō��킳�ꂽ
	virtual bool selected(int x, int y) {
		
		if (is_focused) {
			unsigned int bu = getButukariStatusPoint(x, y, &nowRect);
			if (bu & BUTUKARIPOINT_IN) {
				return true;
			}
		}
		return false; 
	
	}; // �J�[�\�������킳�ꂽ��ԂőI���{�^���������ꂽ�@�܂��̓}�E�X�őI�����Ă�����̂������ꂽ
	virtual void unfocused(int x, int y) {
		if (is_focused) {
			unsigned int bu = getButukariStatusPoint(x, y, &nowRect);
			if (bu & BUTUKARIPOINT_IN) {
			}
			else {
				is_focused = false;
				has_is_focused_changed = true;
			}

		}
	}; // �J�[�\�����O�ꂽ
	
	void touroku() { has_touroku = true; };
	bool getTouroku() { return has_touroku; };
	Gamen2_part() { 
		pid = part_id; part_id++; has_touroku = false; is_focused = false; has_is_focused_changed = false; color = 0xFFFFFFFF; 
	};
	~Gamen2_part() {};
	virtual char* getHelpString() {
		return "default help string";
	}
};


struct GAMEN2_PARTGROUPSTRUCT {
	int tex_or_textindex;
	bool is_tex;
};

class Gamen2_partGroup : public Gamen2_part {
public:
	Gamen2_partGroup() : Gamen2_part() {};
	~Gamen2_partGroup(){};

private:
	int gamen_id;
	int group_index;
	vector<MYRECT> now_rects; // ����Ƀ}�E�X�̓����̃t�H�[�J�X����ɂ��g�p����
	vector<MYRECT> dest_rects;
	vector<MYRECT> rects;
	vector<GAMEN2_PARTGROUPSTRUCT> tex_or_textindexs;

	// rects ����с@textindexs help_text �Ɋւ��Ắ@�O�����烍�[�h�����\��������̂Ŏg���Ƃ��� CS_LOAD_CS �̃��b�N��������
	
	string help_text;



};

#define KTROBO_GARAGE2_IMG_PATH "resrc/img/garage2.png"

class Garage2Tex_Garage2 : public Gamen2_part {

private:
	int texe;
	int tex_waku;
public:
	Garage2Tex_Garage2() :  Gamen2_part() {
		texe = 0;
		tex_waku = 0;
	}
	~Garage2Tex_Garage2() {};

	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat ���J���ĊY���̃p�[�c�̃��{�����
	char* getHelpString() {
		return "�K���[�W��ʂł��B�����ŃA�Z���u����V���b�v�Ȃǂ̏o���̏������ł��܂��B";
	};
};

class MyRobo_Garage2 : public Loadable2 , public Gamen2_part{
private:
	int tex_waku;
	int tex_haikei;

public:
	Robo* robo;
private:
	void haribote_render(Graphics* g, MYMATRIX* view, MYMATRIX* proj);
public:
	MyRobo_Garage2();
	~MyRobo_Garage2();
	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat ���J���ĊY���̃p�[�c�̃��{�����
};

class AssembleTex_Garage2 :  public Gamen2_part {
private:
	int texe;
public:
	AssembleTex_Garage2() :  Gamen2_part() { texe = 0; };
	~AssembleTex_Garage2() {};

	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei);
	char* getHelpString() {
		return "�A�Z���u�����܂��B�w���ς݂̃p�[�c���g���Ď����Ǝ��̋@�̍\�������܂��B";
	};

	bool selected(int x, int y);
	

};
/*
class AsmBodySaveTex_Garage2 : public Gamen2_part {
private:
	int texe;
public:
	AsmBodySaveTex_Garage2() :  Gamen2_part() { texe = 0; };
	~AsmBodySaveTex_Garage2() {};

	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);
	 // load manpai �t�@�C��
	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei);
	char* getHelpString() {
		return "���݂̋@�̍\�����t�@�C���ɕۑ����܂��B16�܂ŕۑ��ł��܂��B";
	};
};

class AsmBodyLoadTex_Garage2 : public Loadable2, public Gamen2_part {
private:
	int texe;
public:
	AsmBodyLoadTex_Garage2() : Loadable2(), Gamen2_part() { texe = 0; };
	~AsmBodyLoadTex_Garage2() {};

	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);
	void atoload(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei);
	// �����ꂽ��ɌĂԃ��[�h �ۑ��ς݂̋@�̍\�������[�h����
	
	
	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei);
	char* getHelpString() {
		return "�ۑ��ς݂̋@�̍\�������[�h���܂��B���[�h��������ƌ��݂̋@�̍\���͎����܂��B";
	};
};

class ShopTex_Garage2 : public Loadable2, public Gamen2_part {
private:
	int texe;
public:
	ShopTex_Garage2() : Loadable2(), Gamen2_part() { texe = 0; };
	~ShopTex_Garage2() {};

	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei);
	char* getHelpString() {
		return "�M�d��G�𕥂��ăp�[�c���w�����܂��B�����p�͐헪�I�ɁB";
	};
};
*/

class Garage2 : public Loadable2, Gamen2_part{
private:
	MyRobo_Garage2* robog;
	
	Garage2Tex_Garage2* gtex_g;
/*	AssembleTex_Garage2* atex_g;
	AsmBodySaveTex_Garage2* abstex_g;
	AsmBodyLoadTex_Garage2* abltex_g;
	ShopTex_Garage2* stex_g;
	*/

	int help_text;
	int help_text_waku;

	

	Gamen2_part* selected_categorypart;
	Gamen2_part* focused_part;

	char* getHelpStringWhenNoneFocused();

public:
	Garage2();
	~Garage2();

	// ����lua�t�@�C������K���[�W��ʂ𐧌�ł���悤�ɂ����Ƃ�
	// �K���[�W��ʂłȂ��Ƃ��ɐ���R�}���h����񂾎��ǂ������炢�����Ƃ�����肪����
	// �K���[�W����C���^�t�F�[�X�C���v���@�̒��Ɂ@�K���[�W��ʒ����ǂ����̃t���O�������Ă����K�v������H
	// ���(�V�[��)�Ɋւ��Ăǂ������A�v���[�`���Ƃ����炢�����Ƃ������Ȃ̂�������Ȃ�
	// �Œ�����[�h����Ă��Ȃ���΂Ȃ�Ȃ����̂������[�h���ăN���X������������Ă���悤�ɂ����
	// �؂�ւ��͂����������Ȃ�
	// ���[�h����Ă邩����ĂȂ����̔����
	// ���[�h���ꂽ���̂��ǂ�����ē��������ɓ���邩�Ƃ����d�g�݂̖�肪����
	// �܂�@render�X���b�h�@�Ɓ@load�X���b�h�����邯��
	// render�X���b�h�ŊY�����[�h���̃��b�N�������s���̂͂΂����Ă邵�A
	// �ǂ�������炢���̂���
	// Loadable2 ���g���Ă݂悤�Ƃ������ƂɂȂ���.

	// �K���[�W��ʂ��n�܂����Ƃ��ɍŒ�����[�h����Ă��Ȃ���΂Ȃ�Ȃ�����
	void load(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);

	// �K���[�W��ʂ��n�܂��Ă���x��ă��[�h���Ă���������
	// ��ɕ\�����������
private:
	// atoniyobareru
	void atoload(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);
public:	
	void render(Graphics* g, Texture* tex, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);
	void mouse_move(Texture* tex1, Texture* tex2, Game* game,int x, int y);
	void mouse_clicked_down(Texture* tex1, Texture* tex2, Game* game, int x, int y);
	void mouse_clicked_up(Texture* tex1, Texture* tex2, Game* game, int x, int y);
};
class SceneGarage2 : public Scene, public INPUTSHORICLASS {

	AtariHantei* hantei;
	Texture* tex;
	Texture* tex2;
	MyTextureLoader* loader;
	Garage2* garage_impl;
	
public:
	SceneGarage2(AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);
	~SceneGarage2(void);

public:
	void mainrenderIMPL(bool is_focused, Graphics* g, Game* game);
	void renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g,  Game* game);

	void enter();
	void leave();
	bool handleMessage(int msg, void* data, DWORD time);
};


}

#endif