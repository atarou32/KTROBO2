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

class Garage2_part {
private:
	int pid;
	static unsigned int part_id;
	bool has_touroku;
public:
	virtual void focused(unsigned int focused_pid) {}; // �J�[�\�������킳�ꂽ�@�܂��́@�}�E�X�ō��킳�ꂽ
	virtual void selected(unsigned int selected_pid) {}; // �J�[�\�������킳�ꂽ��ԂőI���{�^���������ꂽ�@�܂��̓}�E�X�őI�����Ă�����̂������ꂽ
	virtual void unfocused() {}; // �J�[�\�����O�ꂽ
	void touroku() { has_touroku = true; };
	bool getTouroku() { return has_touroku; };
	Garage2_part() { pid = part_id; part_id++; has_touroku = false; };
	~Garage2_part() {};
};

class MyRobo_Garage2 : public Loadable2 , public Garage2_part{
private:
public:
	Robo* robo;
private:
	void haribote_render(Graphics* g, MYMATRIX* view, MYMATRIX* proj);
public:
	MyRobo_Garage2();
	~MyRobo_Garage2();
	void render(Graphics* g, MYMATRIX* view, MYMATRIX* proj);

	void load(Graphics* g, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat ���J���ĊY���̃p�[�c�̃��{�����
};



class Garage2 : public Loadable2{
private:
	MyRobo_Garage2* robog;
	MyRobo_Garage2* robog2;
	MyRobo_Garage2* robog3;
	MyRobo_Garage2* robog4;
	MyRobo_Garage2* robog5;

	vector<Garage2_part*> parts;
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
	void render(Graphics* g, MYMATRIX* view, MYMATRIX* proj);

};
class SceneGarage2 : public Scene, public INPUTSHORICLASS{

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