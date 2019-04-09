#ifndef KTROBO_SCENE_GAMEPAD_CONFIG_H
#define KTROBO_SCENE_GAMEPAD_CONFIG_H





#pragma once
#include "KTRoboScene.h"
#include "KTRoboInput.h"
#include "KTRoboTexture.h"
#include "KTRoboLoadable.h"
#include "KTRoboGamen2.h"

namespace KTROBO {

class SceneGamePadConfig : public Scene, public INPUTSHORICLASS, public Loadable2
{
private:
	vector<Gamen2_partGroup*> parts_groups;
	map<int, int> PARTSDEF_to_parts_group_index;
	Gamen2_part* focused_part;
	int focused_rule_index;

	int text_no_gamepad;
	int tex_no_gamepad;

	int cursor2_text;
	int help_text;
	int help_text_waku;
	int cursor_tex;

	Texture* tex;
	Texture* tex2;
	MyTextureLoader* loader;

public:
	void mouse_move(Texture* tex1, Texture* tex2, Game* game, int x, int y);
	void mouse_clicked_down(Texture* tex1, Texture* tex2, Game* game, int x, int y);
	void mouse_clicked_up(MyTextureLoader* loader, Texture* tex1, Texture* tex2, Game* game, int x, int y);
	void pressed_button_enter(MyTextureLoader* loader, Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_up(Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_down(Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_left(Texture* tex1, Texture* tex2, Game* game);
	void pressed_button_right(Texture* tex1, Texture* tex2, Game* game);
	void setCursorTexPosToCursorPos(Texture* tex1, Texture* tex2, Game* game);
	void getConfigString(char * buf, GAMEPAD_STATE::GAMEPAD_STATE_CONFIG_RULE* rule, int PARTSDEF);
	SceneGamePadConfig(Texture* tex, Texture* tex2, MyTextureLoader* loader);
	void getSuutiChara(int suuti, char* chara);
	~SceneGamePadConfig();
	void mainrenderIMPL(bool is_focused, Graphics* g, Game* game);
	void renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
	void load(Graphics* g, Game* gg);
	void enter();
	void leave();
	void Del();
	bool handleMessage(int msg, void* data, DWORD time);
};


}
#endif