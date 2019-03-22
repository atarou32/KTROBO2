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
	virtual bool moveLoop(float dt) { return false; }; // 動き終わったらtrueを返す
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
	
	}; // カーソルがあわされた　または　マウスで合わされた
	virtual bool selected(int x, int y) {
		
		if (is_focused) {
			unsigned int bu = getButukariStatusPoint(x, y, &nowRect);
			if (bu & BUTUKARIPOINT_IN) {
				return true;
			}
		}
		return false; 
	
	}; // カーソルがあわされた状態で選択ボタンが押された　またはマウスで選択しているものが押された
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
	}; // カーソルが外れた
	
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
	vector<MYRECT> now_rects; // これにマウスの動きのフォーカス判定にも使用する
	vector<MYRECT> dest_rects;
	vector<MYRECT> rects;
	vector<GAMEN2_PARTGROUPSTRUCT> tex_or_textindexs;

	// rects および　textindexs help_text に関しては　外部からロードされる可能性があるので使うときは CS_LOAD_CS のロックをかける
	
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

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る
	char* getHelpString() {
		return "ガレージ画面です。ここでアセンブルやショップなどの出撃の準備ができます。";
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

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る
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
		return "アセンブルします。購入済みのパーツを使って自分独自の機体構成を作ります。";
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
	 // load manpai ファイル
	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei);
	char* getHelpString() {
		return "現在の機体構成をファイルに保存します。16個まで保存できます。";
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
	// 押された後に呼ぶロード 保存済みの機体構成をロードする
	
	
	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei);
	char* getHelpString() {
		return "保存済みの機体構成をロードします。ロード完了すると現在の機体構成は失われます。";
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
		return "貴重なGを払ってパーツを購入します。ご利用は戦略的に。";
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