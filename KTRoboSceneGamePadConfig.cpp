#include "KTRoboSceneGamePadConfig.h"
#include "tolua_glue/tolua_glue.h"
#include "KTRoboInputGamePad.h"

using namespace KTROBO;

#define KTROBO_SCENE_GAMEPAD_CONFIG_IMG_PATH "resrc/sample/gui.png"
#define KTROBO_SCENE_GAMEPAD_CONFIG_INIT_LUA_FILEPATH "resrc/script/gamepad/init_gamepadconfig.lua"

SceneGamePadConfig::SceneGamePadConfig(Texture* tex, Texture* tex2, MyTextureLoader* loader) : Scene("gamepad",7)
{
	this->tex = tex;
	this->tex2 = tex2;
	this->loader = loader;
	text_no_gamepad = 0;
	tex_no_gamepad = 0;
	help_text = 0;
	help_text_waku = 0;
	focused_part = 0;
	focused_rule_index = 0;
	cursor_tex = 0;
	is_gamepad = false;
}


SceneGamePadConfig::~SceneGamePadConfig()
{
	Del();
}


void SceneGamePadConfig::getConfigString(char* out_str, GAMEPAD_STATE::GAMEPAD_STATE_CONFIG_RULE* rule, int PARTSDEF) {
	if (!rule) {
		mystrcpy(out_str, 10,0,"登録なし"); return;
	}

	if (rule->is_button && (KTROBO_GAMEPAD_BUTTON_NOUSE == rule->index)) {
		mystrcpy(out_str, 10,0, "登録なし"); return;
	}

	char str[512];
	memset(str, 0, 512);

	if (rule->is_button) {
		mystrcpy3(str, 512, 0, "ボタン");
	}
	else {
		mystrcpy3(str, 0, 0, "軸");
		if (rule->is_minus) {
			mystrcpy3(str, 512, strlen(str), "-");
		}
		else {
			mystrcpy3(str, 512, strlen(str), "+");
		}
	}
	char str2[128];
	memset(str2, 0, 128);
	getSuutiChara(rule->index, str2);
	mystrcpy3(str, 512, strlen(str), str2);
	mystrcpy3(str, 512, strlen(str), "番目");

	if ((rule->index >= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_START) && (rule->index <= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_END)) {
		memset(str2, 0, 128);
		getSuutiChara(rule->pov_value, str2);
		mystrcpy3(str, 512, strlen(str), str2);
	}

	mystrcpy(out_str,512,0, str);

}
void SceneGamePadConfig::Del() {
	PARTSDEF_to_parts_group_index.clear();
	int siz = parts_groups.size();
	for (int i = 0; i < siz; i++) {
		if (parts_groups[i]) {
			parts_groups[i]->cleardayo(tex, tex2);
			delete parts_groups[i];
			parts_groups[i] = 0;
		}
	}
	parts_groups.clear();
}
void SceneGamePadConfig::load(Graphics* g, Game* gg) {
	char str[1024];
	memset(str, 0, 1024);
	strcpy_s(str, 512, "この画面ではゲームパッドでロボを操縦する場合のキーを設定します。");// gtex_g->getHelpString());
	help_text = tex2->getRenderText(str, 50, g->getScreenHeight() - 55 + 11, 18, g->getScreenWidth(), 20);
	tex2->setRenderTextIsRender(help_text, true);
	int tex_index2 = tex->getTexture(KTROBO_GARAGE2_IMG_PATH);
	int tex_index22 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	//cursor_tex = tex2->getRenderTex(tex_index22, 0xFFFFFFFF, 100, 100, 67, 490 - 437, 0, 437, 67, 490 - 437);

	help_text_waku = tex->getRenderTex(tex_index2, 0x000000FF, 10, g->getScreenHeight() - 55 + 11, g->getScreenWidth() - 20, 20, 18, 390, 1, 1);


	//tex2->setRenderTextIsRender(help_text, false);

	if (!InputGamePad::getInstance()->getPJOYSTICK()) {
		text_no_gamepad = tex->getRenderText(
			"ゲームパッドが接続されていません。ゲームを再起動して！ ESCで戻ります。", 20, 100, 22, 900, 22);
		int tex_index = tex->getTexture(KTROBO_SCENE_GAMEPAD_CONFIG_IMG_PATH);
		tex_no_gamepad = tex->getRenderTex(tex_index, 0xFFFFFFFF, 20, 100, 900, 22, 30, 30, 1, 1);
		tex->setRenderTextIsRender(text_no_gamepad, true);
		setLoaded();
		return;
	}



	//setLoaded();
	//int tex_index22 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	cursor_tex = tex2->getRenderTex(tex_index22, 0xFFFFFFFF, 100, 100, 67, 490 - 437, 0, 437, 67, 490 - 437);
	cursor2_text = tex2->getRenderText("調整中", 0, 0, 20, 60, 20);
	CS::instance()->enter(CS_MESSAGE_CS, "test");
	CS::instance()->enter(CS_LOAD_CS, "test");
	MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->clearCPPParts(KTROBO_GAMEN2_SCENE_ID_GAMEPAD);
	for (int i = KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_START; i <= KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_END; i++) {
	
		char str[512];
		memset(str, 0, 512);
		getConfigString(str, &Input::gamepad_state.rules[i],i);
		Gamen2_partGroup* gg = new Gamen2_partGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, tex, tex2);
		int pp_index = parts_groups.size();
		PARTSDEF_to_parts_group_index.insert(pair<int, int>(i, pp_index));
		parts_groups.push_back(gg);

		int tex_index = tex->getTexture(KTROBO_SCENE_GAMEPAD_CONFIG_IMG_PATH);

		int texttt = tex->getRenderTex(tex_index, 0xFFFFFFFF, 20, 100, 300, 20, 30, 30, 1, 1);
		int textttt = tex->getRenderText(str, 20, 100, 20, 300, 20);
		tex->setRenderTextIsRender(textttt, true);
		MYRECT rec;
		rec.left = 20;
		rec.right = 20 + 300;
		rec.top = 100;
		rec.bottom = 120;
		int recto[4];
		recto[0] = 20;
		recto[1] = 20 + 300;
		recto[2] = 100;
		recto[3] = 120;
		gg->setTex(texttt, false, recto);
		gg->setText(textttt, false, recto);
		gg->setRect(&rec);
		MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(gg, i);

	}


	CS::instance()->leave(CS_LOAD_CS, "test");
	CS::instance()->leave(CS_MESSAGE_CS, "test");

	
	MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(KTROBO_SCENE_GAMEPAD_CONFIG_INIT_LUA_FILEPATH);
	is_gamepad = true;
	setLoaded();
}

void SceneGamePadConfig::mainrenderIMPL(bool is_focused, Graphics* g, Game* game) {

}
void SceneGamePadConfig::renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {
	setCursorTexPosToCursorPos(tex, tex2, game);

	


}
void SceneGamePadConfig::aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {

}
void SceneGamePadConfig::posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {

}
void SceneGamePadConfig::loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {
	if (!hasLoaded()) {
		load(g, game);
	}
}
void SceneGamePadConfig::enter() {
	
	INPUTGETBYMESSAGESTRUCT* ss = InputMessageDispatcher::getRootInputGetStruct();
	while (ss->getParent()) {
ss = ss->getParent();
	}
	InputMessageDispatcher::registerImpl(this, NULL, ss->impl);

	Scene::enter();
}
void SceneGamePadConfig::leave() {
	Scene::leave();
	MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->Del();
	this->Del();
	if (tex) {
		tex->deleteAll();
	}
	if (tex2) {
		tex2->deleteAll();
	}

	InputMessageDispatcher::unregisterImpl(this);
	
}

void SceneGamePadConfig::getSuutiChara(int suuti, char* chara) {
	int temp = 0;
	if (suuti < 0) {
		chara[temp] = '-';
		temp++;
		suuti *= -1;
	}
	int suut = suuti;
	int keta = 0;
	while (suut > 0) {
		suut = suut / 10;
		keta++;
	}
	if (keta == 0) {
		chara[temp] = '0';
		temp++;
		chara[temp] = '\0';
		return;
	}
	suut = suuti;
	int tt = keta;
	while (keta > 0) {
		int amari = suut % 10;
		if (amari == 0) {
			chara[temp + keta - 1] = '0';
		}
		else if (amari == 1) {
			chara[temp + keta - 1] = '1';
		}
		else if (amari == 2) {
			chara[temp + keta - 1] = '2';
		}
		else if (amari == 3) {
			chara[temp + keta - 1] = '3';
		}
		else if (amari == 4) {
			chara[temp + keta - 1] = '4';
		}
		else if (amari == 5) {
			chara[temp + keta - 1] = '5';
		}
		else if (amari == 6) {
			chara[temp + keta - 1] = '6';
		}
		else if (amari == 7) {
			chara[temp + keta - 1] = '7';
		}
		else if (amari == 8) {
			chara[temp + keta - 1] = '8';
		}
		else if (amari == 9) {
			chara[temp + keta - 1] = '9';
		}
		suut = suut / 10;
		keta--;
	}
	chara[temp + tt] = 0;
	return;


}

bool SceneGamePadConfig::handleMessage(int msg, void* data, DWORD time) {
	MYINPUTMESSAGESTRUCT* input = (MYINPUTMESSAGESTRUCT*)data;
	int x = input->getMOUSESTATE()->mouse_x;
	int y = input->getMOUSESTATE()->mouse_y;


	if (!is_gamepad) {

		if (msg == KTROBO_INPUT_MESSAGE_ID_KEYDOWN) {
			if (input->getKEYSTATE()[VK_ESCAPE] & KTROBO_INPUT_BUTTON_DOWN) {
				//CS::instance()->leave(CS_MESSAGE_CS, "enter");
				//modoru(tex, tex2, game);
				CS::instance()->enter(CS_LOAD_CS, "tner");

				Gamen2_event * ee = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GAMEPAD);
				if (ee) {
					int hensuu = ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED);
					if (hensuu != KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA) {
						tex2->setRenderTextIsRender(cursor2_text, false);




						ee->setHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA);

					}
					else {
						// modoru
						MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow("resrc/script/gamepad/modoru.lua");
					}
				}
				else {
					// modoru
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow("resrc/script/gamepad/modoru.lua");

				}
				CS::instance()->leave(CS_LOAD_CS, "tner");

				return true;
				//CS::instance()->enter(CS_MESSAGE_CS, "enter");
			}
		}

	}

	CS::instance()->enter(CS_LOAD_CS, "ee");
	volatile bool t = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getPaused();

	CS::instance()->leave(CS_LOAD_CS, "ee");
	if (t) return true;
	//garage_impl->setCursorTexPosToCursorPos(tex, tex2, game);

	CS::instance()->enter(CS_MESSAGE_CS, "enter");
	if (msg == KTROBO_INPUT_MESSAGE_ID_MOUSEMOVE) {
		CS::instance()->leave(CS_MESSAGE_CS, "enter");
		mouse_move(tex, tex2, game, x, y);
		CS::instance()->enter(CS_MESSAGE_CS, "enter");
	}
	if (msg == KTROBO_INPUT_MESSAGE_ID_MOUSERAWSTATE) {
		if (input->getMOUSESTATE()->mouse_button & KTROBO_MOUSESTATE_L_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			mouse_clicked_down(tex, tex2, game, x, y);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getMOUSESTATE()->mouse_button & KTROBO_MOUSESTATE_L_UP) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			mouse_clicked_up(loader, tex, tex2, game, x, y);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
	}

	if (msg == KTROBO_INPUT_MESSAGE_ID_KEYDOWN) {
		if (input->getKEYSTATE()[VK_ESCAPE] & KTROBO_INPUT_BUTTON_DOWN) {
			//CS::instance()->leave(CS_MESSAGE_CS, "enter");
			//modoru(tex, tex2, game);
			CS::instance()->enter(CS_LOAD_CS, "tner");

			Gamen2_event * ee = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GAMEPAD);
			if (ee) {
				int hensuu = ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED);
				if (hensuu != KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA) {
					tex2->setRenderTextIsRender(cursor2_text, false);




					ee->setHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA);

				}
				else {
					// modoru
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow("resrc/script/gamepad/modoru.lua");
				}
			}
			else {
				// modoru
				MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow("resrc/script/gamepad/modoru.lua");

			}
			CS::instance()->leave(CS_LOAD_CS, "tner");


			//CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_DOWN] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			pressed_button_down(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_UP] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			pressed_button_up(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_LEFT] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			pressed_button_left(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_RIGHT] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			pressed_button_right(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_RETURN] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			pressed_button_enter(loader, tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}

	}
	/*
		if (input->getKEYSTATE()[VK_DOWN] & KTROBO_INPUT_BUTTON_DOWN) {
			pressed_down_count = 1;
			temp_focused_list->clickedDown();

		}
		if (input->getKEYSTATE()[VK_UP] & KTROBO_INPUT_BUTTON_DOWN) {
			pressed_up_count = 1;
			temp_focused_list->clickedUp();
		}
		if (input->getKEYSTATE()[VK_RETURN] & KTROBO_INPUT_BUTTON_DOWN) {



			try {
				temp_focused_list->clickedEnter(this, NULL);
			}
			catch (GameError* err) {
				CS::instance()->leave(CS_MESSAGE_CS, "leave");
				delete err;
				return true;
			}


		}
		if (input->getKEYSTATE()[VK_ESCAPE] & KTROBO_INPUT_BUTTON_DOWN) {
			clickedEscape();

		}
	}

	if (msg == KTROBO_INPUT_MESSAGE_ID_KEYUP) {
		if (input->getKEYSTATE()[VK_DOWN] & KTROBO_INPUT_BUTTON_UP) {
			pressed_down_count = 0;
		}
		if (input->getKEYSTATE()[VK_UP] & KTROBO_INPUT_BUTTON_UP) {
			pressed_up_count = 0;
		}
	}
	if (pressed_up_count > 0) {
		if (pressed_up_count > 1) {
			if (input->getKEYSTATE()[VK_UP] & KTROBO_INPUT_BUTTON_PRESSED) {
				temp_focused_list->clickedUp();
			}



		}
		else {
			if (input->getKEYSTATE()[VK_UP] & KTROBO_INPUT_BUTTON_PRESSED) {
				pressed_up_count++;
			}
		}
	}
	*/

	CS::instance()->leave(CS_MESSAGE_CS, "enter");
	//	garage_impl->setCursorTexPosToCursorPos(tex, tex2, game);



















	if (msg == KTROBO_INPUT_MESSAGE_ID_GAMEPAD) {
		for (int i = 0; i < KTROBO_GAMEPAD_BUTTON_MAX; i++) {

			if (input->gamepadstate.button[i] & KTROBO_INPUT_BUTTON_DOWN) {
				char str[512];
				memset(str, 0, 512);
				this->getSuutiChara(i, str);
				int tt = tex->getRenderText(str, x, y, 20, 200, 20);
				tex->setRenderTextIsRender(tt, true);


				CS::instance()->enter(CS_MESSAGE_CS, "enter");
				CS::instance()->enter(CS_LOAD_CS, "enter");
				Gamen2_event* ee = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GAMEPAD);
				if (ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED) == KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED) {
					int PARTSDEF = ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF);
					Input::setGamePadRule(true, true, i, PARTSDEF, 0);
					Input::saveGamePadRule();

					tex2->setRenderTextIsRender(cursor2_text, false);

					char str[512];
					memset(str, 0, 512);
					getConfigString(str, &Input::gamepad_state.rules[PARTSDEF],PARTSDEF);
					parts_groups[PARTSDEF_to_parts_group_index.find(PARTSDEF)->second]->changeText(str, tex, tex2);


					ee->setHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA);
				}

				CS::instance()->leave(CS_LOAD_CS, "enter");
				CS::instance()->leave(CS_MESSAGE_CS, "enter");
			}
		}

		for (int i = 0; i < KTROBO_GAMEPAD_AXISROTSLIDERPOV_MAX; i++) {
			if ((i >= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_START) && (i <= KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_END)) {
				if (input->gamepadstate.axisrotsliderpov[i] != KTROBO_GAMEPAD_AXISROTSLIDERPOV_POV_DEFAULT) {
					char str[512];
					memset(str, 0, 512);
					this->getSuutiChara(i, str);
					int tt = tex->getRenderText(str, x, y, 20, 200, 20);
					tex->setRenderTextIsRender(tt, true);

					CS::instance()->enter(CS_MESSAGE_CS, "enter");
					CS::instance()->enter(CS_LOAD_CS, "enter");
					Gamen2_event* ee = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GAMEPAD);
					if (ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED) == KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED) {
						int PARTSDEF = ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF);
						bool is_minus = false;
						if (input->gamepadstate.axisrotsliderpov[i] < 0) {
							is_minus = true;
						}

						Input::setGamePadRule(false, is_minus, i, PARTSDEF, input->gamepadstate.axisrotsliderpov[i]);
						Input::saveGamePadRule();
						tex2->setRenderTextIsRender(cursor2_text, false);

						char str[512];
						memset(str, 0, 512);
						getConfigString(str, &Input::gamepad_state.rules[PARTSDEF],PARTSDEF);
						parts_groups[PARTSDEF_to_parts_group_index.find(PARTSDEF)->second]->changeText(str, tex, tex2);

						ee->setHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA);
					}

					CS::instance()->leave(CS_LOAD_CS, "enter");
					CS::instance()->leave(CS_MESSAGE_CS, "enter");



				}
			}
			else {
				if (abs(input->gamepadstate.axisrotsliderpov[i]) >= KTROBO_GAMEPAD_CONFIG_STATE_AXISROT_OFFSET) {
					char str[512];
					memset(str, 0, 512);
					this->getSuutiChara(i, str);
					int tt = tex->getRenderText(str, x, y, 20, 200, 20);
					tex->setRenderTextIsRender(tt, true);

					CS::instance()->enter(CS_MESSAGE_CS, "enter");
					CS::instance()->enter(CS_LOAD_CS, "enter");
					Gamen2_event* ee = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GAMEPAD);
					if (ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED) == KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED) {
						int PARTSDEF = ee->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF);
						bool is_minus = false;
						if (input->gamepadstate.axisrotsliderpov[i] < 0) {
							is_minus = true;
						}

						Input::setGamePadRule(false, is_minus, i, PARTSDEF, input->gamepadstate.axisrotsliderpov[i]);
						Input::saveGamePadRule();
						tex2->setRenderTextIsRender(cursor2_text, false);

						char str[512];
						memset(str, 0, 512);
						getConfigString(str, &Input::gamepad_state.rules[PARTSDEF],PARTSDEF);
						parts_groups[PARTSDEF_to_parts_group_index.find(PARTSDEF)->second]->changeText(str, tex, tex2);

						ee->setHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA);
					}

					CS::instance()->leave(CS_LOAD_CS, "enter");
					CS::instance()->leave(CS_MESSAGE_CS, "enter");


				}
			}

			



		}

	}



	return true;
}












void SceneGamePadConfig::mouse_move(Texture* tex, Texture* tex2, Game* game, int x, int y) {


	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		const vector<vector<int>*> const * cg = sono->getCG();

		int cgsize = cg->size();
		for (int i = 0; i < cgsize; i++) {
			vector<int>* gro = (*cg)[i];
			int grosize = gro->size();

			for (int k = 0; k < grosize; k++) {
				int ginde = (*gro)[k];
				Gamen2_part* pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(ginde);
				if (pp) {
					pp->unfocused(x, y);
				}
			}
		}


		cgsize = cg->size();
		for (int i = 0; i < cgsize; i++) {
			vector<int>* gro = (*cg)[i];
			int grosize = gro->size();

			for (int k = 0; k < grosize; k++) {
				int ginde = (*gro)[k];
				Gamen2_part* pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(ginde);
				if (pp && pp->focused(x, y)) {
					if (pp != focused_part) {
						char test[1024];
						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getHelpString());
						tex2->setRenderTextChangeText(help_text, test);
						focused_part = pp;
						sono->setCursorXY(ginde);// pp->getAllIndex());

						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getFocusedLua());
						if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
							MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
						}


					}

					CS::instance()->leave(CS_LOAD_CS, "ee");
					CS::instance()->leave(CS_MESSAGE_CS, "e");
					return;
				}
			}
		}


		if (focused_part != 0) {
			focused_part = 0;
			char test[1024];
			memset(test, 0, 1024);
			//mystrcpy(test, 1024, 0, this->getHelpStringWhenNoneFocused());
			//tex2->setRenderTextChangeText(help_text, test);
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");

}


void  SceneGamePadConfig::mouse_clicked_down(Texture* tex, Texture* tex2, Game* game, int x, int y) {
	



	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		const vector<vector<int>*> const * cg = sono->getCG();

		int cgsize = cg->size();
		for (int i = 0; i < cgsize; i++) {
			vector<int>* gro = (*cg)[i];
			int grosize = gro->size();

			for (int k = 0; k < grosize; k++) {
				int ginde = (*gro)[k];
				Gamen2_part* pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(ginde);
				if (pp) {
					pp->unfocused(x, y);
				}
			}
		}


		cgsize = cg->size();
		for (int i = 0; i < cgsize; i++) {
			vector<int>* gro = (*cg)[i];
			int grosize = gro->size();

			for (int k = 0; k < grosize; k++) {
				int ginde = (*gro)[k];
				Gamen2_part* pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(ginde);
				if (pp && pp->focused(x, y)) {
					if (pp != focused_part) {
						char test[1024];
						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getHelpString());
						tex2->setRenderTextChangeText(help_text, test);
						focused_part = pp;
						sono->setCursorXY(ginde);// pp->getAllIndex());

						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getFocusedLua());
						if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
							MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
						}


					}

					CS::instance()->leave(CS_LOAD_CS, "ee");
					CS::instance()->leave(CS_MESSAGE_CS, "e");
					return;
				}
			}
		}


		if (focused_part != 0) {
			focused_part = 0;
			char test[1024];
			memset(test, 0, 1024);
			//mystrcpy(test, 1024, 0, this->getHelpStringWhenNoneFocused());
			//tex2->setRenderTextChangeText(help_text, test);
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");




}

void  SceneGamePadConfig::mouse_clicked_up(MyTextureLoader* loader, Texture* tex, Texture* tex2, Game* game, int x, int y) {
	

	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		int focused_group_all_index = sono->getCursorGroup();
		Gamen2_part* focused_part = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(focused_group_all_index);
		if (focused_part && focused_part->selected(x, y)) {
			// lua ファイルを呼ぶ
			MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->pauseWork();

			Gamen2_event* eve = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GAMEPAD);
			if (eve) {
				eve->selected(focused_group_all_index);
				if (eve->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED) == KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED) {
			
					focused_rule_index = eve->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF);

					tex2->setRenderTextIsRender(cursor2_text,true);





//					eve->setHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED);
				}
			
			}
			
			char strdayo[1024];
			memset(strdayo, 0, 1024);
			mystrcpy(strdayo, 1024, 0, focused_part->getSelectedLua());
			if (strcmp(KTROBO_GAMEN2_LUA_FILENAME_NO_LUA, strdayo) != 0) {
				MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(strdayo);
			}
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");
}



void  SceneGamePadConfig::pressed_button_enter(MyTextureLoader* loader, Texture* tex1, Texture* tex2, Game* game) {

	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		int allinde = sono->getCursorGroup();
		Gamen2_part* pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(allinde);

		if (pp && pp->getIsWork()) {
			focused_part = pp;
			pp->selectExe();
			// lua ファイルを呼ぶ
			MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->pauseWork();

			Gamen2_event* eve = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GARAGE);
			if (eve) {
				eve->selected(allinde);
				focused_rule_index = eve->getHensuu(KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF);
				tex2->setRenderTextIsRender(cursor2_text, true);

			}
			
			char strdayo[1024];
			memset(strdayo, 0, 1024);
			mystrcpy(strdayo, 1024, 0, focused_part->getSelectedLua());
			if (strcmp(KTROBO_GAMEN2_LUA_FILENAME_NO_LUA, strdayo) != 0) {
				MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(strdayo);
			}

		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");
}
void  SceneGamePadConfig::pressed_button_up(Texture* tex1, Texture* tex2, Game* game) {

	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		sono->setCursorY(sono->getCursorY() - 1);
		int all_inde = sono->getCursorGroup();
		Gamen2_part* pp = 0;
		pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(all_inde);
		if (pp && pp->getIsWork()) {
			if (focused_part != pp) {
				focused_part = pp;
				pp->focusExe();
				char test[1024];
				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getHelpString());
				tex2->setRenderTextChangeText(help_text, test);

				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getFocusedLua());
				if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
				}

			}
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");
}
void  SceneGamePadConfig::pressed_button_down(Texture* tex1, Texture* tex2, Game* game) {

	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		sono->setCursorY(sono->getCursorY() + 1);
		int all_inde = sono->getCursorGroup();
		Gamen2_part* pp = 0;
		pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(all_inde);
		if (pp && pp->getIsWork()) {
			if (focused_part != pp) {
				focused_part = pp;
				pp->focusExe();
				char test[1024];
				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getHelpString());
				tex2->setRenderTextChangeText(help_text, test);

				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getFocusedLua());
				if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
				}

			}
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");
}
void  SceneGamePadConfig::pressed_button_left(Texture* tex1, Texture* tex2, Game* game) {

	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		sono->setCursorX(sono->getCursorX() + 1);
		int all_inde = sono->getCursorGroup();
		Gamen2_part* pp = 0;
		pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(all_inde);
		if (pp && pp->getIsWork()) {
			if (focused_part != pp) {
				focused_part = pp;
				pp->focusExe();
				char test[1024];
				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getHelpString());
				tex2->setRenderTextChangeText(help_text, test);

				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getFocusedLua());
				if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
				}

			}
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");
}
void  SceneGamePadConfig::pressed_button_right(Texture* tex1, Texture* tex2, Game* game) {

	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		sono->setCursorX(sono->getCursorX() - 1);
		int all_inde = sono->getCursorGroup();
		Gamen2_part* pp = 0;
		pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(all_inde);
		if (pp && pp->getIsWork()) {
			if (focused_part != pp) {
				focused_part = pp;
				pp->focusExe();
				char test[1024];
				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getHelpString());
				tex2->setRenderTextChangeText(help_text, test);

				memset(test, 0, 1024);
				mystrcpy(test, 1024, 0, pp->getFocusedLua());
				if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
				}

			}
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	CS::instance()->leave(CS_MESSAGE_CS, "e");
}



void SceneGamePadConfig::setCursorTexPosToCursorPos(Texture* tex1, Texture* tex2, Game* game) {

	if (MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getPaused()) return;

	//CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		try {

			int focused_group_all_index = sono->getCursorGroup();
			Gamen2_part* focused_part = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(focused_group_all_index);
			if (focused_part) {

				tex2->setRenderTexPos(cursor_tex, focused_part->getRect()->left - 70, focused_part->getRect()->top);
			}

			int PARTSDEF = this->focused_rule_index;
			MYRECT rect = *parts_groups[PARTSDEF_to_parts_group_index.find(PARTSDEF)->second]->getRect();
			tex2->setRenderTextPos(cursor2_text, rect.left-60, rect.top);

		}
		catch (GameError* err) {
			// 無視する
			mylog::writelog(KTROBO::WARNING, err->getMessage());
			delete err;
		}
		catch (...) {

			CS::instance()->leave(CS_LOAD_CS, "ee");
			//CS::instance()->leave(CS_MESSAGE_CS, "e");
			return;
		}
	}

	CS::instance()->leave(CS_LOAD_CS, "ee");
	//	CS::instance()->leave(CS_MESSAGE_CS, "e");

}