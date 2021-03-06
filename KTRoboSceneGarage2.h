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

	void load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る
	const char* getHelpString() {
		return "ガレージ画面です。ここでアセンブルやショップなどの出撃の準備ができます。";
	};
	
};
class AsmBody;
class Garage2;
class MyRobo_Garage2 : public Loadable2 , public Gamen2_part{
private:
	int tex_waku;
	int tex_haikei;
	bool toggle_render;
	int robo_parts_tex[32];
	int robo_parts_text[32];
	AsmBody* now_asm;
	bool asm_hanneied;
public:
	Robo* robo;
private:
	void haribote_render(Graphics* g, MYMATRIX* view, MYMATRIX* proj);
	void setRoboPartsTexText(Texture* tex2,int temp,int index, int x, int y, int tex_height, char* prefix, const char* parts_name,int tex_width);
public:
	MyRobo_Garage2();
	~MyRobo_Garage2();
	void render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);
	void setAsm(AsmBody* asme);// { now_asm = asme; };
	void atoload(Garage2* gg, Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る
	void makeRoboPartTex(Garage2* gg, Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る

	void load(Garage2* gg,Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei); // user/MyRobo.robodat を開いて該当のパーツのロボを作る

	const char* getHelpString() {
		return "あなたの愛情を一身に受けて大活躍するロボットです。";
	}
	const char* getSelectedLua() {
		return "resrc/script/garage/modoru_now.lua";
	}
};

class RoboParts_Info {
public:
	RoboMetaDataPart* metpart;
	RoboParts* parts;
	int tex;
	int text;
	RoboParts_Info() {
		metpart = 0;
		parts = 0;
		tex = 0;
		text = 0;
	}
	void del(Texture* tex1, Texture* tex2) {
		if (tex) {
			tex1->lightdeleteRenderTex(tex);
			tex = 0;
		}
		if (text) {
			tex1->lightdeleteRenderText(text);
			text = 0;
		}
	}
	
};

class ItemWithCategory;
class AssembleParts_Garage2 : public Gamen2_part, public Loadable2 {
private:
	vector<ItemWithCategory*> sp; //消さなくてよい
	vector<RoboDataMetaData*> metadatas;
	map<string, int> metadatas_map; // mdfile to index
	MyTextureLoader* loader;
	vector<Gamen2_partGroup*> pgs;
	RoboParts_Info parts_info[32];
	int parts_info_max;

	int tex_waku;
	int tex_haikei;
	bool toggle_render;
	int parts_index;
public:
	int parts_category;
	int parts_category2;
	AssembleParts_Garage2(int p, int p2, MyTextureLoader* loaer) :Gamen2_part() {
		parts_category = p;
		parts_category2 = p2;
		loader = loaer;
		
		tex_waku = 0;
		tex_haikei = 0;
		toggle_render = true;
		parts_index = 0;
		parts_info_max = 0;

	}
	~AssembleParts_Garage2();
	void render(Garage2* gg2, MyRobo_Garage2* robop, Texture* tex1, Texture* tex2, Graphics* g, MYMATRIX* view, MYMATRIX* proj, float dt);
	void load(Game* gg,Graphics* g);
	void atoload(Game* gg, Graphics* g);
	void makeTexDayo(Garage2* gg2, MyRobo_Garage2* parts, Graphics* g, Texture* tex, Texture* tex2);
	void changeTexPartsDayo(Garage2* gg2, MyRobo_Garage2* parts, Graphics* g, Texture* tex, Texture* tex2);
	void Del(Texture* tex, Texture* tex2);
	
	bool purgeParts(int all_index, Game* g);
	bool assembleParts(Garage2* gg, int all_index, Game* game, Graphics* g);
	bool sellParts(int all_index, Game* g);
	const char* getHelpString() {
		return "選択しているパーツの外見です。ゴージャス！";
	}
	const char* getSelectedLua() {
		return "resrc/script/garage/modoru_now.lua";
	}
};

class ShopParts_Garage2 : public Gamen2_part, public Loadable2{
private:
	ShopParts* sp;
	MyTextureLoader* loader;
	vector<Gamen2_partGroup*> pgs;
	RoboParts_Info parts_info[32];
	int parts_info_max;

	int tex_waku;
	int tex_haikei;
	bool toggle_render;
	int parts_index;
public:
	int parts_category;
	int parts_category2;
	ShopParts_Garage2(int p, int p2, MyTextureLoader* loaer):Gamen2_part() {
		parts_category = p;
		parts_category2 = p2;
		loader = loaer;
		sp = 0;
		tex_waku = 0;
		tex_haikei = 0;
		toggle_render = true;
		parts_index = 0;
		parts_info_max = 0;
		
	}
	~ShopParts_Garage2();
	void render(Garage2* gg2,MyRobo_Garage2* robop, Texture* tex1, Texture* tex2, Graphics* g, MYMATRIX* view, MYMATRIX* proj, float dt);
	void load(Graphics* g);
	void atoload(Graphics* g);
	void makeTexDayo(Garage2* gg2, MyRobo_Garage2* parts, Graphics* g, Texture* tex, Texture* tex2);
	void changeTexPartsDayo(Garage2* gg2,MyRobo_Garage2* parts, Graphics* g, Texture* tex, Texture* tex2);
	void Del(Texture* tex, Texture* tex2);
	bool buyParts(int all_index, Game* g);
	const char* getHelpString() {
		return "選択しているパーツの外見です。ゴージャス！";
	}
	const char* getSelectedLua() {
		return "resrc/script/garage/modoru_now.lua";
	}
};

class AsmBody;

class AsmSaveLoadPartsGroup_Garage2 : public Loadable2, public Gamen2_partGroup {
private:
	AsmBody* now_asm;
	AsmBody* asmb;
	Garage2* gg2;
	MyRobo_Garage2* roboparts;
	//Graphics* g;
	Game* gg;
	bool for_load;
	Robo* robo;
	MyTextureLoader * loader;
	int file_index;
public:

	AsmSaveLoadPartsGroup_Garage2(int file_index, MyTextureLoader * loader, AsmBody* now_asm, bool for_load,Robo* robo,Game* gg,Garage2* gg2, MyRobo_Garage2* parts, Graphics* g, AsmBody* asmb, int scene_id, Texture* tex, Texture* tex2) :Gamen2_partGroup(scene_id,tex, tex2) {
		this->asmb = asmb;
		this->gg2 = gg2;
		this->roboparts = parts;
		this->loader = loader;
		//this->g = g;
		this->gg = gg;
		this->for_load = for_load;
		this->robo = robo;
		this->file_index = file_index;
		this->now_asm = now_asm;
		int tex_index2 = tex->getTexture(KTROBO_GARAGE2_IMG_PATH);
		int tee = tex->getRenderTex(tex_index2, 0x000000FF,
			400, 300 , 300, 30, 18, 390, 1, 1);
		int textee = tex->getRenderText("計算中です・・・", 400, 300, 22, 300, 30);
		tex->setRenderTextIsRender(textee, true);
		int recto[4];
		recto[0] = 400;
		recto[1] = 400 + 300;
		recto[2] = 300;
		recto[3] = 300 + 30;

		this->setTex(tee, false, recto);
		this->setText(textee, false, recto);
		MYRECT rec;
		rec.left = 400;
		rec.right = 400 + 300;
		rec.top = 300;
		rec.bottom = 300 + 30;
		this->setRect(&rec);

	};

	~AsmSaveLoadPartsGroup_Garage2() {};

	void focusExe();
	bool exeSelectKondokoso(int file_inde, Graphics* g);

	void selectExe();
	void load(Graphics* g);

};


class AsmSaveLoadParts_Garage2 : public Loadable2, Gamen2_part {
private:
	Robo* robo;
	//vector<AsmBody*> asms;// [KTROBO_USERDATA_ASMBODY_MAX];
	MyTextureLoader* loader;
	vector<AsmSaveLoadPartsGroup_Garage2*> pgs;
	int parts_index;
	bool for_load;
	int parts_category;
	int parts_category2;
	Texture* tex1;
	Texture* tex2;
public:
	AsmSaveLoadParts_Garage2(int p, int p2, MyTextureLoader* loaer, bool for_lor, Texture* tex, Texture* tex2) :Gamen2_part() {
		parts_category = p;
		parts_category2 = p2;
		loader = loaer;
		for_load = for_lor;
		parts_index = 0;
		robo = 0;
		this->tex1 = tex;
		this->tex2 = tex2;

	}
	~AsmSaveLoadParts_Garage2();

	//void render(Garage2* gg2, MyRobo_Garage2* robop, Texture* tex1, Texture* tex2, Graphics* g, MYMATRIX* view, MYMATRIX* proj, float dt);
	void load(Garage2* gg2, MyRobo_Garage2* myrobob, Texture* tex, Texture* tex2, Game* gg, Graphics* g);
	void atoload(Graphics* g);
	void doLoadSave(int file_index, Graphics* g);

};


class Garage2 : public Loadable2, Gamen2_part{
private:
	MyRobo_Garage2* robog;
	
	Garage2Tex_Garage2* gtex_g;


	int help_text;
	int help_text_waku;

	int cursor_tex;

	int has_gold_tex;
	int has_gold_text;
	int has_gold_tex_waku;


	Gamen2_part* selected_categorypart;
	Gamen2_part* focused_part;

	const char* getHelpStringWhenNoneFocused();
	vector<ShopParts_Garage2*> destruct_shopparts; // 廃棄予定のパーツ
	ShopParts_Garage2* shopparts_g;

	vector<AssembleParts_Garage2*> destruct_assembles;
	AssembleParts_Garage2* assembles_g;

	vector<AsmSaveLoadParts_Garage2*> destruct_asmsls;
	AsmSaveLoadParts_Garage2* asmsls_g;

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
	void load(Game* gg,Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);

	// ガレージ画面が始まってから遅れてロードしてもいいもの
	// 主に表示部分だよね
private:
	// atoniyobareru
	void atoload(Game* gg,Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);
public:	
	void modoru(Texture* tex, Texture* tex2, Game* game);
	void render(Graphics* g, Texture* tex, Texture* tex2, MYMATRIX* view, MYMATRIX* proj);
	void mouse_move(Texture* tex1, Texture* tex2, Game* game,int x, int y);
	void mouse_clicked_down(Texture* tex1, Texture* tex2, Game* game, int x, int y);
	void mouse_clicked_up(MyTextureLoader* loader, Texture* tex1, Texture* tex2, Game* game, int x, int y);
	void pressed_button_enter(MyTextureLoader* loader, Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_up(Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_down(Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_left(Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_right(Texture* tex1, Texture* tex2, Game* game);
	void setCursorTexPosToCursorPos(Texture* tex1, Texture* tex2, Game* game);
	void getMessageFromLua(Graphics* g,Texture* tex1, Texture* tex2, Game* game);
	void getSuutiChara(int suuti, char* chara);
	void setAsmToRoboG(AsmBody* asme);
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