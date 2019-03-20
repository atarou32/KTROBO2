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
	virtual bool moveLoop(float dt) { return false; }; // 動き終わったらtrueを返す
	virtual bool focused(int x, int y) { return false; }; // カーソルがあわされた　または　マウスで合わされた
	virtual bool selected(int x, int y) { return false; }; // カーソルがあわされた状態で選択ボタンが押された　またはマウスで選択しているものが押された
	virtual void unfocused(int x, int y) {}; // カーソルが外れた
	void touroku() { has_touroku = true; };
	bool getTouroku() { return has_touroku; };
	Garage2_part() { 
		pid = part_id; part_id++; has_touroku = false; is_focused = false; has_is_focused_changed = false; color = 0xFFFFFFFF; 
	};
	~Garage2_part() {};
	virtual char* getHelpString() {
		return "default help string";
	}
};
class Garage2Tex_Garage2 : public Garage2_part {

private:
	int texe;
	int tex_waku;
public:
	Garage2Tex_Garage2() {
		texe = 0;
		tex_waku = 0;
	}
	~Garage2Tex_Garage2() {};

	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る
	char* getHelpString() {
		return "ガレージ画面です。ここでアセンブルやショップなどの出撃の準備ができます。";
	};
};

class MyRobo_Garage2 : public Loadable2 , public Garage2_part{
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

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る
};



class Garage2 : public Loadable2{
private:
	MyRobo_Garage2* robog;
	//MyRobo_Garage2* robog2;
	//MyRobo_Garage2* robog3;
	//MyRobo_Garage2* robog4;
	//MyRobo_Garage2* robog5;
	Garage2Tex_Garage2* gtex_g;
	vector<Garage2_part*> parts;
public:
	Garage2();
	~Garage2();

	// あとluaファイルからガレージ画面を制御できるようにしたとき
	// ガレージ画面でないときに制御コマンドが飛んだ時どうしたらいいかという問題がある
	// ガレージ制御インタフェースインプル　の中に　ガレージ画面中かどうかのフラグを持っておく必要がある？
	// 画面(シーン)に関してどういうアプローチをとったらいいかという問題なのかもしれない
	// 最低限ロードされていなければならないものだけロードしてクラスをいつも一個持っているようにすれば
	// 切り替えはすごく早くなる
	// ロードされてるかされてないかの判定と
	// ロードされたものをどうやって動かす中に入れるかという仕組みの問題がある
	// つまり　renderスレッド　と　loadスレッドがあるけど
	// renderスレッドで該当ロード物のロックをいつも行うのはばかげてるし、
	// どうやったらいいのかな
	// Loadable2 を使ってみようということになった.

	// ガレージ画面が始まったときに最低限ロードされていなければならないもの
	void load(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);

	// ガレージ画面が始まってから遅れてロードしてもいいもの
	// 主に表示部分だよね
private:
	// atoniyobareru
	void atoload(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);
public:	
	void render(Graphics* g, Texture* tex, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);

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