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
#include "KTRoboGamen2.h"

namespace KTROBO {


class ShopParts;

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
	const char* getHelpString() {
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

class ShopParts_Garage2 : public Loadable2{
private:
	ShopParts* sp;
	MyTextureLoader* loader;
	vector<Gamen2_partGroup*> pgs;
	int tex_waku;
	int tex_haikei;
public:
	int parts_category;
	int parts_category2;
	ShopParts_Garage2(int p, int p2, MyTextureLoader* loaer) {
		parts_category = p;
		parts_category2 = p2;
		loader = loaer;
		sp = 0;
		tex_waku = 0;
		tex_haikei = 0;
	}
	~ShopParts_Garage2();
	void render(Graphics* g, MYMATRIX* view, MYMATRIX* proj, float dt);
	void load(Graphics* g);
	void atoload(Graphics* g);
	void makeTexDayo(Graphics* g, Texture* tex, Texture* tex2);
	void Del(Texture* tex, Texture* tex2);
};


class Garage2 : public Loadable2, Gamen2_part{
private:
	MyRobo_Garage2* robog;
	
	Garage2Tex_Garage2* gtex_g;


	int help_text;
	int help_text_waku;

	int cursor_tex;
	

	Gamen2_part* selected_categorypart;
	Gamen2_part* focused_part;

	const char* getHelpStringWhenNoneFocused();
	vector<ShopParts_Garage2*> destruct_shopparts; // �p���\��̃p�[�c
	ShopParts_Garage2* shopparts_g;
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
	void mouse_clicked_up(MyTextureLoader* loader, Texture* tex1, Texture* tex2, Game* game, int x, int y);
	void setCursorTexPosToCursorPos(Texture* tex1, Texture* tex2, Game* game);
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