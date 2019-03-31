#include "KTRoboSceneGarage2.h"
#include "KTRoboGame.h"
#include "KTRoboUserData.h"
#include "tolua_glue/tolua_glue.h"

using namespace KTROBO;

#define KTROBO_GARAGE2_SHOP_PART_TEX_FOCUSED_LUA "resrc/script/garage/part_tex_focused.lua"
#define KTROBO_GARAGE2_SHOP_PART_TEX_SELECTED_LUA "resrc/script/garage/part_tex_selected.lua"
#define KTROBO_GARAGE2_SHOP_PART_TEX_SONOTOKI_LUA "resrc/script/garage/part_tex_sonotoki.lua"

SceneGarage2::SceneGarage2(AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader) : Scene("garage", 6)
{
	garage_impl = 0;
	this->tex = tex;
	this->tex2 = tex2;
	this->loader = loader;
	this->hantei = hantei;
}


SceneGarage2::~SceneGarage2()
{
	if (garage_impl) {
		delete garage_impl;
		garage_impl = 0;
	}
}


void SceneGarage2::mainrenderIMPL(bool is_focused, Graphics* g, Game* game) {
/*	if (gg && is_focused) {
		gg->byouga(g, NULL, game->getDMSecond(), game->getTimeStamp());
		MYVECTOR3 from(22, 22, 10);
		MYVECTOR3 at(0, 0, 0);
		MYVECTOR3 up(0, 0, 1);
		MyMatrixLookAtRH(game->view, from, at, up);

		tex->setViewProj(g, &game->view, g->getProj(), &from, &at);
		tex2->setViewProj(g, &game->view, g->getProj(), &from, &at);
	}*/
	MYMATRIX view;

	MYVECTOR3 from(25, 25, 12);
	MYVECTOR3 at(0, 0, 0);
	MYVECTOR3 up(0, 0, 1);

	MyMatrixLookAtRH(view, from, at, up);
	if (game->telop_texts->isRenderFinished()) {
		//	telop_texts->readFile(g, "resrc/sample/KTROBO.txt", 30, 14, &MYVECTOR4(1, 1, 1, 1), 0.1);
	}
	else {
		game->telop_texts->plusTime(g, game->getDMSecond());
	}

	if (!game->telop_texts->isRenderFinished()) {
		game->telop_texts->render(g);
	}
	
	garage_impl->render(g, tex,tex2,&view, g->getProj());
}
void SceneGarage2::renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g,  Game* game) {

	garage_impl->setCursorTexPosToCursorPos(tex, tex2, game);


}


void SceneGarage2::aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {
	CS::instance()->enter(CS_MESSAGE_CS, "enter");
	garage_impl->getMessageFromLua(this->gs[TASKTHREADS_AIDECISION], tex, tex2, game);
	CS::instance()->leave(CS_MESSAGE_CS, "enter");
}

void SceneGarage2::posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g,  Game* game) {

}

void SceneGarage2::loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g,  Game* game) {
//	if (gg) {
//		try {
//			gg->loadData(g, game->getDMSecond(), game->getTimeStamp());
//		}
//		catch (GameError* err) {
//			KTROBO::mylog::writelog(KTROBO::FATAL_ERROR, err->getMessage());
//			throw err;
//		}
//	}

	garage_impl->load(game,g, hantei, tex, tex2, loader);


}


bool ShopParts_Garage2::buyParts(int all_index, Game* g) {


	if (all_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET) {
		int inde = all_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		if (sp && (inde >= 0) && (inde < this->sp->getPartsSize())) {
			RoboParts* rp = sp->getRoboParts(inde);
			UserData* uu = g->getUserData();
			bool t = uu->buyItemInShop(rp, sp->category);
			return t;
		}
	}




	return false;
}

void Garage2::getMessageFromLua(Graphics* g, Texture* tex1, Texture* tex2, Game* game) {
	int msg_indexs[32];
	int msgs[32];
	int msgids[32];
	int senders[32];
	int receivers[32];
	float fmsgs[32];
	for (int i = 0; i < 32; i++) {
		msgs[i] = 0;
		msg_indexs[i] = 0;
		msgids[i] = 0;
		senders[i] = 0;
		receivers[i] = 0;
		fmsgs[i] = 0;
	}
	int msize = MyLuaGlueSingleton::getInstance()->getColMessages(0)->getInstance(0)->getMessageIndexsFromMsgId(KTROBO_MESSAGE_ID_GARAGE_SHOP_BUY_PARTS, msg_indexs);
	if (msize) {
		MyLuaGlueSingleton::getInstance()->getColMessages(0)->getInstance(0)->getMsgBody(msize, msg_indexs, msgids, senders, receivers, msgs, fmsgs);

		for (int i = 0; i < msize; i++) {
			if (msgids[i] == KTROBO_MESSAGE_ID_GARAGE_SHOP_BUY_PARTS) {
				if (msgs[i] == KTROBO_MESSAGE_MSG_GARAGE_SHOP_BUY_PARTS) {
					int ginde = senders[i];
					CS::instance()->enter(CS_LOAD_CS, "enter");
					if (shopparts_g) {
						
						bool is_true = shopparts_g->buyParts(ginde,game);

						if (is_true) {
							MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecCoDoNow("resrc/script/garage/shop_buy_parts.lua");

						}
						else {
							MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecCoDoNow("resrc/script/garage/shop_buy_parts_error.lua");
						}

						//has_gold_tex = tex->getRenderText("所持金:", 600, g->getScreenHeight() - 85 + 11, 20, g->getScreenWidth() - 600 - 10, 20);
						int ggg = game->getUserData()->getGold();
						char test[1024];
						memset(test, 0, 1024);
						getSuutiChara(ggg, test);
						int last = strlen(test);
						test[last] = 'G';
						test[last + 1] = '\0';
					
						tex1->setRenderTextChangeText(has_gold_text, test);
						tex1->setRenderTextPos(has_gold_text, 600 + (16-strlen(test)) * 20, g->getScreenHeight() - 85 + 11);

					//	has_gold_tex_waku = tex1->getRenderTex(tex_index2, 0x000000FF, 600, g->getScreenHeight() - 85 + 11, g->getScreenWidth() - 600 - 10, 20, 18, 390, 1, 1);




					}
					else {
						// エラー
						MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecCoDoNow("resrc/script/garage/shop_buy_parts_error.lua");
					}
					CS::instance()->leave(CS_LOAD_CS, "enter");
				}
			}
		}

		MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow("resrc/script/garage/modoru_now.lua");
	}
}
void SceneGarage2::enter() {
	//	gg = new Gamen_GARAGE();
	//	gg->Init(g, hantei, tex, tex2, loader);
	//	INPUTGETBYMESSAGESTRUCT* ss = InputMessageDispatcher::getRootInputGetStruct();
	//	while (ss->getParent()) {
	//		ss = ss->getParent();
	//	}
	//	InputMessageDispatcher::registerImpl(gg, NULL, ss->impl);
	if (!garage_impl) {
		garage_impl = new Garage2();
	}
	INPUTGETBYMESSAGESTRUCT* ss = InputMessageDispatcher::getRootInputGetStruct();
	while (ss->getParent()) {
		ss = ss->getParent();
	}
	InputMessageDispatcher::registerImpl(this, NULL, ss->impl);
	
	Scene::enter();


}


void SceneGarage2::leave() {

	Scene::leave();


	InputMessageDispatcher::unregisterImpl(this);
	


}

void Garage2::setCursorTexPosToCursorPos(Texture* tex1, Texture* tex2, Game* game) {

	
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

void Garage2::render(Graphics* g,Texture* tex,Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {
	CS::instance()->enter(CS_RENDERDATA_CS, "render");
	if (robog) {
		robog->render(g, tex2,view, proj);










	}

	if (gtex_g) {
		gtex_g->render(g, tex2, view, proj);
	}

	if (shopparts_g && robog) {
		CS::instance()->leave(CS_RENDERDATA_CS, "render");
		shopparts_g->render(this,robog,tex,tex2,g, view, proj, 30);
		CS::instance()->enter(CS_RENDERDATA_CS, "render");
	}
	CS::instance()->leave(CS_RENDERDATA_CS, "render");
}

bool SceneGarage2::handleMessage(int msg, void* data, DWORD time) {
	MYINPUTMESSAGESTRUCT* input = (MYINPUTMESSAGESTRUCT*)data;
	int x = input->getMOUSESTATE()->mouse_x;
	int y = input->getMOUSESTATE()->mouse_y;


	//garage_impl->setCursorTexPosToCursorPos(tex, tex2, game);

	CS::instance()->enter(CS_MESSAGE_CS, "enter");
	if (msg == KTROBO_INPUT_MESSAGE_ID_MOUSEMOVE) {
		CS::instance()->leave(CS_MESSAGE_CS, "enter");
		garage_impl->mouse_move(tex,tex2,game, x, y);
		CS::instance()->enter(CS_MESSAGE_CS, "enter");
	}
	if (msg == KTROBO_INPUT_MESSAGE_ID_MOUSERAWSTATE) {
		if (input->getMOUSESTATE()->mouse_button & KTROBO_MOUSESTATE_L_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->mouse_clicked_down(tex,tex2,game,x, y);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getMOUSESTATE()->mouse_button & KTROBO_MOUSESTATE_L_UP) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->mouse_clicked_up(loader, tex,tex2,game, x, y);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
	}
	
	if (msg == KTROBO_INPUT_MESSAGE_ID_KEYDOWN) {
		if (input->getKEYSTATE()[VK_ESCAPE] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->modoru(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_DOWN] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->pressed_button_down(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_UP] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->pressed_button_up(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_LEFT] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->pressed_button_left(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_RIGHT] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->pressed_button_right(tex, tex2, game);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
		if (input->getKEYSTATE()[VK_RETURN] & KTROBO_INPUT_BUTTON_DOWN) {
			CS::instance()->leave(CS_MESSAGE_CS, "enter");
			garage_impl->pressed_button_enter(loader,tex, tex2, game);
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
	return false;
}

const char* Garage2::getHelpStringWhenNoneFocused() {
	if (!selected_categorypart) {
		return gtex_g->getHelpString();
	}
	return selected_categorypart->getHelpString();
}

Garage2::Garage2() :  Loadable2(), Gamen2_part() {
	robog = 0;
	gtex_g = 0;
	/*
	atex_g = 0;
	abstex_g = 0;
	abltex_g = 0;
	stex_g = 0;
	*/
	help_text = 0;
	help_text_waku = 0;
	selected_categorypart = 0;
	focused_part = 0;
	cursor_tex = 0;
	shopparts_g = 0;
	has_gold_tex = 0;
	has_gold_tex_waku = 0;
	has_gold_text = 0;
};
Garage2::~Garage2() {
	if (robog) {
		delete robog;
			robog = 0;
	}
	if (gtex_g) {
		delete gtex_g;
		gtex_g = 0;
	}
	/*
	if (atex_g) {
		delete atex_g;
		atex_g = 0;
	}
	if (abstex_g) {
		delete abstex_g;
		abstex_g = 0;
	}
	if (abltex_g) {
		delete abltex_g;
		abltex_g = 0;
	}
	if (stex_g) {
		delete stex_g;
		stex_g = 0;
	}
	*/
	if (this->shopparts_g) {
		delete shopparts_g;
		shopparts_g = 0;
	}
	if (destruct_shopparts.size()) {
		int s = destruct_shopparts.size();
		for (int i = 0; i < s; i++) {
			if (destruct_shopparts[i]) {
				delete destruct_shopparts[i];
				destruct_shopparts[i] = 0;
			}
		}
		destruct_shopparts.clear();
	}
};

void Garage2::atoload(Graphics* g, AtariHantei* hantei, Texture* tex1, Texture* tex2, MyTextureLoader* loader) {
	ShopParts_Garage2* temp = 0;
	if (!robog->getTouroku()) {
		robog->load(this,g, tex1,tex2, loader, hantei);
		robog->robo->atarihan->setXYZ(0, 0, 0);
		robog->touroku();
		return;
	}
	CS::instance()->enter(CS_MESSAGE_CS, "destruct_parts");
	CS::instance()->enter(CS_LOAD_CS, "destruct_parts");
	volatile int size = destruct_shopparts.size();
	for (int i = 0; i < size; i++) {
		ShopParts_Garage2* ga = destruct_shopparts[i];
		
		if (ga) {
			ga->Del(tex1, tex2);
			delete ga;
			ga = 0;
		}
	}
	destruct_shopparts.clear();
	temp = shopparts_g;
	CS::instance()->leave(CS_LOAD_CS, "destruct_parts");
	CS::instance()->leave(CS_MESSAGE_CS, "destruct_parts");
	if (temp) {
		// tempがこの時点でほかのスレッドからデストラクトされる予定に入ってしまっていたとしても
		// デストラクタが実際に呼ばれるのは次のこの関数が呼ばれるときなので大丈夫.
		if (!temp->hasLoaded()) {
			temp->load(g);

			if (temp->hasLoaded()) {
				// makeTexdayo
				temp->makeTexDayo(this,this->robog,g, tex1, tex2);
			}

		} else {
			temp->atoload(g);
		}

	}



}

void Garage2::mouse_move(Texture* tex, Texture* tex2, Game* game, int x, int y) {
	if (!selected_categorypart) {
		/*
		vector<Gamen2_part*>::iterator it = this->select_parts.begin();
		while (it != select_parts.end()) {
			Gamen2_part* p = *it;

			p->unfocused(x, y);


			it++;
		}
		it = select_parts.begin();

		while (it != select_parts.end()) {
			Gamen2_part* p = *it;

			if (p->focused(x, y)) {

				if (p != focused_part) {

					tex2->setRenderTextChangeText(help_text, p->getHelpString());
					focused_part = p;
				}
				return;
			}


			it++;
		}

		if (focused_part != 0) {
			focused_part = 0;
			tex2->setRenderTextChangeText(help_text, this->getHelpStringWhenNoneFocused());
		}
		return;
		*/
	}


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

void ShopParts_Garage2::render(Garage2* gg2,MyRobo_Garage2* robop,Texture* tex1,Texture* tex2, Graphics* g,MYMATRIX* view, MYMATRIX* proj, float dt) {
	CS::instance()->enter(CS_LOAD_CS, "test");
	CS::instance()->enter(CS_DEVICECON_CS, "test");
	CS::instance()->enter(CS_RENDERDATA_CS, "test");
	if (sp) {
		int siz = sp->getPartsSize();
		/*for (int i = 0; i < siz; i++) {


			RoboParts* pp = sp->getRoboParts(i);
			if (pp->hasMeshLoaded()) {
				pp->drawMesh(g, view, proj);
			}
		}*/
		int cgi = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotokiCursorGroup();
		
		if (cgi >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET) {
			int start_inde = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getCPPPartsIndex(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START);
			int end_inde = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getCPPPartsIndex(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END);
			if ((start_inde <= cgi) && (end_inde >= cgi)) {
				
				int ato_parts_index = cgi - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
				if (ato_parts_index != parts_index) {
					parts_index = ato_parts_index;
					changeTexPartsDayo(gg2,robop, g, tex1, tex2);				}
			}
		}
		RoboParts* pp = sp->getRoboParts(parts_index);
		if (pp && pp->hasMeshLoaded()) {
			const D3D11_VIEWPORT* ggg = g->getViewPort();
			D3D11_VIEWPORT ggg2;
			D3D11_VIEWPORT ggg3;
			ggg2 = *ggg;
			ggg3.TopLeftX = 480;
			ggg3.TopLeftY = 450;
			ggg3.Width = 200;
			ggg3.Height = 200;
			ggg3.MaxDepth = 0.5;
			ggg3.MinDepth = 0.3;
			g->getDeviceContext()->RSSetViewports(1, &ggg3);
			static float unko = 0;
			unko += 100 / 3333.0;


			//g->getDeviceContext()->ClearRenderTargetView(g->getRenderTargetView(), clearColor);
			MYMATRIX view;

			float r = pp->getR();
			MYVECTOR3 c = pp->getC();
			MYVECTOR3 lookat(c.float3.x, c.float3.y, c.float3.z + r);
			MYVECTOR3 lookfrom(0, 3 * r, r * 2);
			MYVECTOR3 up(0, 0, 1);
			MYMATRIX tes;
			MyMatrixRotationZ(tes, unko);
			MyVec3TransformNormal(lookfrom, lookfrom, tes);
			MyMatrixLookAtRH(view, lookfrom, lookat, up);
			float clearColor[4] = {
				0.6f,0.6f,0.8f,1.0f };

			if (pp) {
				if (pp->hasMeshLoaded()) {
					pp->drawMesh(g, &view, g->getProj());
				}
			}


			g->getDeviceContext()->RSSetViewports(1, ggg);

		}
		



	}
	CS::instance()->leave(CS_RENDERDATA_CS, "test");
	CS::instance()->leave(CS_DEVICECON_CS, "test");
	CS::instance()->leave(CS_LOAD_CS, "test");
}

ShopParts_Garage2::~ShopParts_Garage2() {

	if (sp) {
		delete sp;
		sp = 0;
	}
	int siz = pgs.size();
	for (int i = 0; i < siz; i++) {
		if (pgs[i]) {
			delete pgs[i];
			pgs[i] = 0;
		}
	}
	pgs.clear();
}
void ShopParts_Garage2::changeTexPartsDayo(Garage2* gg2, MyRobo_Garage2* parts, Graphics* g, Texture* tex, Texture* tex2) {
	int siz = sp->getPartsSize();
	if ((parts_index >= 0) && (parts_index < siz)) {
		RoboParts* now_pa = sp->getRoboParts(parts_index);
		RoboDataMetaData* mdata = sp->getMetaData(parts_index);
		vector<RoboMetaDataPart*>* ppp = mdata->getMetaDatas();
		int pppsize = ppp->size();
		if (pppsize > 32) {
			mylog::writelog(KTROBO::WARNING, "too many robomedatapart 32");

		}
		else {
			int now_info_index = 0;
			for (int i = 0; i < pppsize; i++) {
				RoboMetaDataPart* pp = (*ppp)[i];
				int tex_index2 = tex->getTexture(KTROBO_GARAGE2_IMG_PATH);
				if (strcmp(pp->data_sentence, "YES_SENTENCE") == 0) {
					// テクスを作る
					parts_info[now_info_index].parts = now_pa;
					parts_info[now_info_index].metpart = pp;
					parts_info[now_info_index].parts = now_pa;
					if (parts_info[now_info_index].tex) {
						// texは何もしない
					}
					else {
						parts_info[now_info_index].tex = tex->getRenderTex(tex_index2, 0x000000FF,
							400, 300 + 30 * now_info_index, 300, 30, 18, 390, 1, 1);
					}
					char str[256];
					memset(str, 0, 256);
					mystrcpy3(str, 256, 0, pp->data_name2);
					mystrcpy3(str, 256, strlen(pp->data_name2), ":");
					char bstr[256];
					memset(bstr, 0, 256);
					if (strcmp(pp->data_type, "INT") == 0) {
						gg2->getSuutiChara(now_pa->data->getData(pp->data_name)->int_data, bstr);
						mystrcpy3(str, 256, strlen(str), bstr);
					}
					else if (strcmp(pp->data_type, "STRING") == 0) {
						mystrcpy3(str, 256, strlen(str), now_pa->data->getData(pp->data_name)->string_data);
					}
					if (parts_info[now_info_index].text) {
						tex->setRenderTextChangeText(parts_info[now_info_index].text, str);
					}
					else {
						parts_info[now_info_index].text = tex->getRenderText(str, 400, 300 + 30 * now_info_index, 22, 300, 30);
						tex->setRenderTextIsRender(parts_info[now_info_index].text, true);
					}
					now_info_index++;

				}
			}
			parts_info_max = now_info_index;
			int xdayo = 700;
			int ydayo = 450 - parts_info_max * 30 / 2;
			// よさげな場所に移動させる
			for (int i = 0; i < parts_info_max; i++) {
				tex->setRenderTexPos(parts_info[i].tex, xdayo, ydayo + 30 * i);
				tex->setRenderTextPos(parts_info[i].text, xdayo, ydayo + 30 * i);

			}

		}



	}
}
void ShopParts_Garage2::makeTexDayo(Garage2* gg2, MyRobo_Garage2* parts, Graphics* g, Texture* tex, Texture* tex2) {

	//shop_parts はパーツだけ

	int siz = sp->getPartsSize();
	MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->clearCPPParts(KTROBO_GAMEN2_SCENE_ID_GARAGE);
	//MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_SHOP_BUY_PARTS, KTROBO_GARAGE2_HENSUU_IS_SHOP_BUY_PARTS_YES);
	//MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_SHOP_BUY_PARTS_ALL_INDEX, KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET);
	if ((parts_index >= 0) && (parts_index < siz)) {
		RoboParts* now_pa = sp->getRoboParts(parts_index);
		RoboDataMetaData* mdata = sp->getMetaData(parts_index);
		vector<RoboMetaDataPart*>* ppp = mdata->getMetaDatas();
		int pppsize = ppp->size();
		if (pppsize > 32) {
			mylog::writelog(KTROBO::WARNING, "too many robomedatapart 32");

		}
		else {
			int now_info_index = 0;
			for (int i = 0; i < pppsize; i++) {
				RoboMetaDataPart* pp = (*ppp)[i];
				int tex_index2 = tex->getTexture(KTROBO_GARAGE2_IMG_PATH);
				if (strcmp(pp->data_sentence, "YES_SENTENCE") == 0) {
					// テクスを作る
					parts_info[now_info_index].metpart = pp;
					parts_info[now_info_index].parts = now_pa;
					parts_info[now_info_index].tex = tex->getRenderTex(tex_index2, 0x000000FF,
						400, 300 + 30 * now_info_index, 300, 30, 18, 390, 1, 1);
					char str[256];
					memset(str, 0, 256);
					mystrcpy3(str, 256, 0, pp->data_name2);
					mystrcpy3(str, 256, strlen(pp->data_name2), ":");
					char bstr[256];
					memset(bstr, 0, 256);
					if (strcmp(pp->data_type, "INT") == 0) {
						gg2->getSuutiChara(now_pa->data->getData(pp->data_name)->int_data, bstr);
						mystrcpy3(str, 256, strlen(str), bstr);
					}
					else if (strcmp(pp->data_type, "STRING") == 0) {
						mystrcpy3(str, 256, strlen(str), now_pa->data->getData(pp->data_name)->string_data);
					}
					parts_info[now_info_index].text = tex->getRenderText(str, 400, 300 + 30 * now_info_index, 22, 300, 30);
					tex->setRenderTextIsRender(parts_info[now_info_index].text, true);
					now_info_index++;

				}
			}
			parts_info_max = now_info_index;
			int xdayo = 700;
			int ydayo = 450 - parts_info_max * 30 / 2;
			// よさげな場所に移動させる
			for (int i = 0; i < parts_info_max; i++) {
				tex->setRenderTexPos(parts_info[i].tex, xdayo, ydayo + 30 * i);
				tex->setRenderTextPos(parts_info[i].text, xdayo, ydayo + 30 * i);

			}

		}
	


	}
	



	for (int i = 0; i < siz; i++) {
		RoboParts* pp = sp->getRoboParts(i);
		if (pp) {
			Gamen2_partGroup* gg = new Gamen2_partGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET+i,
				KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET+i, tex, tex2);
			int unko = tex2->getRenderText(pp->data->getData("name")->string_data, 400, 25+50 * i, 20, 400, 40);
			gg->setString(pp->data->getData("COMMENT")->string_data, KTROBO_GARAGE2_SHOP_PART_TEX_FOCUSED_LUA,
				KTROBO_GARAGE2_SHOP_PART_TEX_SELECTED_LUA);
			MYRECT re;
			re.left = 400 - 13;
			re.right = re.left + (238 - 68) * 2 + 100;
			re.top = 25 + 50 * i - 5;
			re.bottom = re.top + 27;

			gg->setRect(&re);

			tex2->setRenderTextIsRender(unko, true);
			tex2->setRenderTextColor(unko, 0xFF000000);
			int tex_index2 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH,4096);
			int unko2 = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, 400-13, 25+50 * i-5, (238 - 68)*2+40+60, 27, 68, 376, 238 - 68, 54);
			int ret[4];
			ret[0] = 400;
			ret[1] = 400 + 400;
			ret[2] = 25 + 50 * i;
			ret[3] = ret[2] + 40;
			gg->setText(unko, true, ret);
			ret[0] = 400 - 13;
			ret[1] = ret[0] + (238 - 68) * 2 + 100;
			ret[2] = 25 + 50 * i - 5;
			ret[3] = ret[2] + 27;
			gg->setTex(unko2, true, ret);
			this->pgs.push_back(gg);

			if (siz == 1) {
				// END と START が同じでも　二つ登録する
				MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(gg, KTROBO_GAMEN2_SCENE_ID_GARAGE
					, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END);
			
				MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(gg, KTROBO_GAMEN2_SCENE_ID_GARAGE
					, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START);

			} else {
				if (i == siz - 1) {
					MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(gg, KTROBO_GAMEN2_SCENE_ID_GARAGE
						, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END);
				}
				else {
					MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(gg, KTROBO_GAMEN2_SCENE_ID_GARAGE
						, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START + i);
				}
			}
		}
	}

	int tex_index = tex->getTexture(KTROBO_GARAGE2_IMG_PATH);
	//	tex_waku = tex2->getRenderTex(tex_index, 0xFFFFFFFF, 0, 0, 238, 46, 0, 0, 238, 46);
	int tex_index2 = tex->getTexture(KTROBO_GARAGE2_IMG_PATH);
	

	tex_waku = tex->getRenderTex(tex_index, 0xFFFFFFFF, 480, 450, 200, 200, 245, 0, 200, 200);
	tex_haikei = tex->getRenderTex(tex_index2, 0xFFFFFFFF, 480, 450, 200, 200, 18, 390, 1, 1);
	tex->setRenderTexColor(tex_haikei, 0xFFBBBBBDD);
	MYRECT re;
	re.left = 480;
	re.right = re.left + 200;
	re.top = 450;
	re.bottom = 450 + 200;
	this->setRect(&re);
	MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(this, KTROBO_GAMEN2_SCENE_ID_GARAGE
		, KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYSHOPPARTS);
	MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(parts, KTROBO_GAMEN2_SCENE_ID_GARAGE
		, KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO);
	


	MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(KTROBO_GARAGE2_SHOP_PART_TEX_SONOTOKI_LUA);
}


void ShopParts_Garage2::Del(Texture* tex, Texture* tex2) {
	CS::instance()->enter(CS_MESSAGE_CS, "test");
	CS::instance()->enter(CS_LOAD_CS, "test");
	int siz = pgs.size();
	for (int i = 0; i < siz; i++) {
		if (pgs[i]) {
			pgs[i]->cleardayo(tex,tex2);
			delete pgs[i];
			pgs[i] = 0;
		}
	}
	pgs.clear();
	if (tex_haikei) {
		tex->lightdeleteRenderTex(tex_haikei);
	}
	if (tex_waku) {
		tex->lightdeleteRenderTex(tex_waku);
	}

	for (int i = 0; i < 32; i++) {
		parts_info[i].del(tex, tex2);
	}

	CS::instance()->leave(CS_LOAD_CS, "test");
	CS::instance()->leave(CS_MESSAGE_CS, "test");
}

void Garage2::mouse_clicked_down(Texture* tex, Texture* tex2, Game* game, int x, int y) {
	if (!selected_categorypart) {
		/*
		vector<Gamen2_part*>::iterator it = this->select_parts.begin();
		while (it != select_parts.end()) {
			Gamen2_part* p = *it;

			p->unfocused(x, y);


			it++;
		}
		it = select_parts.begin();

		while (it != select_parts.end()) {
			Gamen2_part* p = *it;

			if (p->focused(x, y)) {
				
				if (p != focused_part) {

					tex2->setRenderTextChangeText(help_text, p->getHelpString());
					focused_part = p;
				}
				return;
			}


			it++;
		}


		if (focused_part != 0) {
			focused_part = 0;
			tex2->setRenderTextChangeText(help_text, this->getHelpStringWhenNoneFocused());
		}
		return;
		*/
	}


	
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

void Garage2::mouse_clicked_up(MyTextureLoader* loader, Texture* tex, Texture* tex2, Game* game, int x, int y) {
	if (!selected_categorypart) {
/*		vector<Gamen2_part*>::iterator it = this->select_parts.begin();
		while (it != select_parts.end()) {
			Gamen2_part* p = *it;

			if (p->selected(x, y)) {
				return;
			}
			it++;
		}
		return;
		*/
	}

	
	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		int focused_group_all_index = sono->getCursorGroup();
		Gamen2_part* focused_part = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(focused_group_all_index);
		if (focused_part && focused_part->selected(x, y)) {
			// lua ファイルを呼ぶ
			MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->pauseWork();

			Gamen2_event* eve = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getEvent(KTROBO_GAMEN2_SCENE_ID_GARAGE);
			if (eve) {
				eve->selected(focused_group_all_index);
				if (eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS) == KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES) {
					// 
					if (this->shopparts_g) {
						this->destruct_shopparts.push_back(shopparts_g);
					}
					shopparts_g = new ShopParts_Garage2(eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY),
					eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2), loader);
					

					eve->setHensuu(KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_NO);
				}
				if (eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL) != KTROBO_GARAGE2_HENSUU_LUA_KEY_CALL_NOKEY) {
					int key = eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL);
					
					CS::instance()->leave(CS_LOAD_CS, "ee");
					CS::instance()->leave(CS_MESSAGE_CS, "e");
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->doAndCoDoExecByKey(
						key);
					CS::instance()->enter(CS_MESSAGE_CS, "e");
					CS::instance()->enter(CS_LOAD_CS, "ee");
					eve->setHensuu(KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL, KTROBO_GARAGE2_HENSUU_LUA_KEY_CALL_NOKEY);
				}
				// 変数をセットする
				// bool is_load_parts
			}
			selected_categorypart = focused_part;
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

void Garage2::load(Game* gg, Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader) {
	
	if (hasLoaded()) {
		atoload(g, hantei, tex, tex2, loader);
		return;
	}
	robog = new MyRobo_Garage2();
	
//	robog->load(g, loader, hantei);
	
	gtex_g = new Garage2Tex_Garage2();
	gtex_g->load(g, tex, tex2, loader, hantei);
/*
	atex_g = new AssembleTex_Garage2();
	atex_g->load(g, tex, tex2, loader, hantei);

	abstex_g = new AsmBodySaveTex_Garage2();
	abstex_g->load(g, tex, tex2, loader, hantei);

	abltex_g = new AsmBodyLoadTex_Garage2();
	abltex_g->load(g, tex, tex2, loader, hantei);

	stex_g = new ShopTex_Garage2();
	stex_g->load(g, tex, tex2, loader, hantei);
	*/

	MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(robog, KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO);

	MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(KTROBO_GARAGE2_INIT_LUA_FILEPATH);
		


	CS::instance()->enter(CS_LOAD_CS, "garage2part");
	/*
	select_parts.push_back(robog);
	select_parts.push_back(gtex_g);
	select_parts.push_back(atex_g);
	select_parts.push_back(abstex_g);
	select_parts.push_back(abltex_g);
	select_parts.push_back(stex_g);
	*/
	CS::instance()->leave(CS_LOAD_CS, "garage2part");

	char str[1024];
	memset(str, 0, 1024);
	strcpy_s(str, 512, gtex_g->getHelpString());
	help_text = tex2->getRenderText(str, 50, g->getScreenHeight() - 55+11, 18, g->getScreenWidth(),20);
	tex2->setRenderTextIsRender(help_text, true);


	//tex2->setRenderTextIsRender(help_text, false);




	setLoaded();
	int tex_index2 = tex->getTexture(KTROBO_GARAGE2_IMG_PATH);
	int tex_index22 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	cursor_tex = tex2->getRenderTex(tex_index22, 0xFFFFFFFF, 100, 100, 67, 490 - 437, 0, 437, 67, 490 - 437);
	
	help_text_waku = tex->getRenderTex(tex_index2,0x000000FF,10,g->getScreenHeight()-55+11,g->getScreenWidth()-20,20, 18, 390, 1, 1);
	//tex->setRenderTexIsRender(help_text_waku, false);

	int ggg = gg->getUserData()->getGold();
	has_gold_tex = tex->getRenderText("所持金:",600,g->getScreenHeight()-85+11, 20,g->getScreenWidth()-600-10,20);
	char test[1024];
	memset(test, 0, 1024);
	getSuutiChara(ggg, test);
	int last = strlen(test);
	test[last] = 'G';
	test[last + 1] = '\0';
	has_gold_text = tex->getRenderText(test, 600+(16-strlen(test))*20, g->getScreenHeight() - 85 + 11, 20, g->getScreenWidth(), 20);

	has_gold_tex_waku = tex->getRenderTex(tex_index2, 0x000000FF, 600, g->getScreenHeight() - 85 + 11, g->getScreenWidth() -600 - 10, 20, 18, 390, 1, 1);

	tex->setRenderTextIsRender(has_gold_tex, true);
	tex->setRenderTextIsRender(has_gold_text, true);

}


void Garage2::getSuutiChara(int suuti, char* chara) {
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


MyRobo_Garage2::MyRobo_Garage2() : Loadable2(), Gamen2_part() {
	robo = 0;
	tex_waku = 0;
	toggle_render = true;

	for (int i = 0; i < 32; i++) {
		//robo_param_tex[i] = 0;
		//robo_param_text[i] = 0;
		robo_parts_tex[i] = 0;
		robo_parts_text[i] = 0;
	}
}
MyRobo_Garage2::~MyRobo_Garage2() {
	if (robo) {
		robo->release();
		delete robo;
		robo = 0;
	}
}

void MyRobo_Garage2::haribote_render(Graphics* g, MYMATRIX* view, MYMATRIX* proj) {

}

void MyRobo_Garage2::render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {

	if (hasLoaded()) {
	//	robo->byouga(g, view, proj);
		const D3D11_VIEWPORT* ggg = g->getViewPort();
		D3D11_VIEWPORT ggg2;
		D3D11_VIEWPORT ggg3;
		ggg2 = *ggg;
		ggg3.TopLeftX = 71;
		ggg3.TopLeftY = 350;
		ggg3.Width = 400;
		ggg3.Height = 400;
		ggg3.MaxDepth = 1;
		ggg3.MinDepth = 0;
		g->getDeviceContext()->RSSetViewports(1, &ggg3);
		static float unko = 0;
		unko += 20.0 / 3333;
		MYMATRIX view;
		MYVECTOR3 lookat(0, 0, 0.2);
		MYVECTOR3 lookfrom(0, -6, 1);
		MYVECTOR3 up(0, 0, 1);
		MYMATRIX tes;
		MyMatrixRotationZ(tes, unko);
		MyVec3TransformNormal(lookfrom, lookfrom, tes);
		lookfrom = lookfrom + MYVECTOR3(0, 0, 0.7);
		lookat = lookat + MYVECTOR3(0, 0, 0.7);
		MyMatrixLookAtRH(view, lookfrom, lookat, up);
		float clearColor[4] = {
			0.6f,0.6f,0.8f,1.0f };

		//g->getDeviceContext()->ClearRenderTargetView(g->getRenderTargetView(), clearColor);
		if (robo) {

			robo->aim(g, &view);
			robo->byouga(g, &view, g->getProj());
		}

		g->getDeviceContext()->RSSetViewports(1, &ggg2);
		

/*

		const D3D11_VIEWPORT* ggg = g->getViewPort();
		D3D11_VIEWPORT ggg2;
		D3D11_VIEWPORT ggg3;
		ggg2 = *ggg;
		ggg3.TopLeftX = 500;
		ggg3.TopLeftY = 100;
		ggg3.Width = 330;
		ggg3.Height = 330;
		ggg3.MaxDepth = 1;
		ggg3.MinDepth = 0;
		g->getDeviceContext()->RSSetViewports(1, &ggg3);
		static float unko = 0;
		unko += 100 / 3333;


		//g->getDeviceContext()->ClearRenderTargetView(g->getRenderTargetView(), clearColor);
		MYMATRIX view;

		float r = 3;// parts->getR();
		MYVECTOR3 c = MYVECTOR3(0, 0, 0);// parts->getC();
		MYVECTOR3 lookat(c.float3.x, c.float3.y, c.float3.z + r);
		MYVECTOR3 lookfrom(0, 3 * r, r * 2);
		MYVECTOR3 up(0, 0, 1);
		MYMATRIX tes;
		MyMatrixRotationZ(tes, unko);
		MyVec3TransformNormal(lookfrom, lookfrom, tes);
		MyMatrixLookAtRH(view, lookfrom, lookat, up);
		float clearColor[4] = {
			0.6f,0.6f,0.8f,1.0f };
		robo->byouga(g, &view, g->getProj());
	
		g->getDeviceContext()->RSSetViewports(1, ggg);


		//int stt = stamp % 130;
		static float unko2 = 0;
		unko2 += 100;
		if (unko2 >= 1000) {
			unko2 = 0;
		}

		int stt = (int)(unko2) % 130;
		unsigned int color = ((((0xFFFF0000 / 130 * stt) & 0x77770000) + 0x88880000) & 0xFFFF0000) + 0x0000FFFF;
*/

	}
	else {
		// haribote->render(g, view, proj);
		haribote_render(g, view, proj);
	}
}
void MyRobo_Garage2::setRoboPartsTexText(Texture* tex2, int temp,int index, int x, int y, int tex_height, char* prefix, const char* parts_name,int tex_width=400) {
	int tex_index22 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	if (index >= 32) return;
	char str[1024];
	{
		memset(str, 0, 1024);
		mystrcpy3(str, 1024, 0, prefix);
		mystrcpy3(str, 1024, strlen(str), parts_name);
		robo_parts_text[index] = tex2->getRenderText(str, x, y + temp * tex_height, tex_height, tex_width, tex_height);
		tex2->setRenderTextIsRender(robo_parts_text[index], true);
		robo_parts_tex[index] = tex2->getRenderTex(tex_index22, 0x000000FF, x, y + temp * tex_height, tex_width, tex_height, 18, 390, 1, 1);
		
	}
}
void MyRobo_Garage2::load(Garage2* gg,Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	// user/MyRobo.robodat を開いて該当のパーツのロボを作る
	robo = new Robo();
	robo->init(g, loader, hantei);
	int tex_index2  = tex1->getTexture(KTROBO_GARAGE2_IMG_PATH);
	
	int tex_index = tex1->getTexture(KTROBO_GARAGE2_IMG_PATH);
//	tex_waku = tex2->getRenderTex(tex_index, 0xFFFFFFFF, 0, 0, 238, 46, 0, 0, 238, 46);
	tex_waku = tex1->getRenderTex(tex_index2, 0xFFFFFFFF, 71,350,400,400, 245, 0, 200, 200);
	tex_haikei = tex1->getRenderTex(tex_index2, 0xFFFFFFFF, 71, 350, 400, 400, 18, 390, 1, 1);
	tex1->setRenderTexColor(tex_haikei, 0xAAAAAAFF);
	MYRECT re;
	re.left = 71;
	re.right = 71 + 400;
	re.top = 350;
	re.bottom = 350 + 400;
	setRect(&re);
	int temp = 0;
	setRoboPartsTexText(tex2, temp,temp, 250, 170, 15, "頭部：", robo->roboparam.getNameOfHead());
	temp++;
	setRoboPartsTexText(tex2, temp,temp, 250, 170, 15, "コア：", robo->roboparam.getNameOfBody());
	temp++;
	setRoboPartsTexText(tex2, temp,temp, 250, 170, 15, "腕部：", robo->roboparam.getNameOfArm());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "脚部：", robo->roboparam.getNameOfLeg());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "エンジン：", robo->roboparam.getNameOfEngine());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "ブースタ：", robo->roboparam.getNameOfBooster());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "FCS：", robo->roboparam.getNameOfFCS());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "右腕武器：", robo->roboparam.getNameOfRArmWeapon());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "左腕武器：", robo->roboparam.getNameOfLArmWeapon());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "右肩武器：", robo->roboparam.getNameOfRShoulderWeapon());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "左肩武器：", robo->roboparam.getNameOfLShoulderWeapon());
	temp++;
	setRoboPartsTexText(tex2, temp, temp, 250, 170, 15, "インサイド：", robo->roboparam.getNameOfInside());
	temp++;
	
	char str[1024];
	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getMaxAP(), str);
	int temp_i = 0;

	setRoboPartsTexText(tex2, temp_i, temp, 20, 650, 18, "AP:", str,250);
	temp++;
	temp_i++;
	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getAllWeight(), str);
	setRoboPartsTexText(tex2, temp_i, temp, 20, 650, 18, "総重量:", str,250);
	temp++;
	temp_i++;

	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getCanWeight(), str);
	setRoboPartsTexText(tex2, temp_i, temp, 20, 650, 18, "積載量:", str,250);
	temp++;
	temp_i++;

	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getAmariEnergy(), str);
	setRoboPartsTexText(tex2, temp_i, temp, 20, 650, 18, "E余剰:", str,250);
	temp++;
	temp_i++;
	temp_i = 0;

	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getEnergyPool(), str);
	setRoboPartsTexText(tex2, temp_i, temp, 320, 650, 18, "Eプール:", str,250);
	temp++;
	temp_i++;

	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getEnergyShuturyoku(), str);
	setRoboPartsTexText(tex2, temp_i, temp, 320, 650, 18, "E出力:", str,250);
	temp++;
	temp_i++;

	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getDef(), str);
	setRoboPartsTexText(tex2, temp_i, temp, 320, 650, 18, "実弾防御力:", str,250);
	temp++;
	temp_i++;

	memset(str, 0, 1024);
	gg->getSuutiChara(robo->roboparam.getEDef(), str);
	setRoboPartsTexText(tex2, temp_i, temp, 320, 650, 18, "E防御力:", str,250);
	temp++;
	temp_i++;






	setLoaded();
}

void Garage2Tex_Garage2::render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {
	/*
	static unsigned char colorr = 0;
	static unsigned char colorg = 0;
	static unsigned char colorb = 0;

	colorr++;
	colorg++;
	colorb++;
	if (is_focused) {
		// unfocus to focus
		color = 0;
		color += (colorr << 24);
		color += (colorg << 16);
		color += (colorb << 8);
		color += 0xFF; // a
		tex2->setRenderTexColor(texe, color);
	}

	if (has_is_focused_changed) {
		has_is_focused_changed = false;
		if (is_focused) {
			// unfocus to focus
			color = 0;
			color += (colorr << 24);
			color += (colorg << 16);
			color += (colorb << 8);
			color += 0xFF; // a
			tex2->setRenderTexColor(texe, color);
		}
		else {
			tex2->setRenderTexColor(texe, 0xFFFFFFFF);
		}

		

	}
	*/
}

void Garage2Tex_Garage2::load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	int tex_index2 = tex1->getTexture(KTROBO_GARAGE2_IMG_PATH);
	texe = tex1->getRenderTex(tex_index2, 0xFFFFFFFF, 5, 5, 236, 46, 0, 0, 236, 46);
	MYRECT re;
	re.left = 5;
	re.right = 236+5;
	re.top = 5;
	re.bottom = 46+5;
	this->setRect(&re);
	tex_waku = tex1->getRenderTex(tex_index2, 0xFFFFFFFF, 5, 5, g->getScreenWidth()-10, g->getScreenHeight()-10 , 245, 0, 200, 200);
	
}
/*
void AsmBodyLoadTex_Garage2::atoload(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei)
{
	// 押された後に呼ぶロード 保存済みの機体構成をロードする
}
*/
/*
void AssembleTex_Garage2::render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {

}

void AssembleTex_Garage2::load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	int tex_index2 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	texe = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, g->getScreenWidth() - 236 - 50, 50, 236, 51, 0, 48, 236, 51);
	MYRECT re;
	re.left = g->getScreenWidth()-236-50;
	re.right = re.left + 236;
	re.top = 50;
	re.bottom = re.top + 51;
	this->setRect(&re);

}

void AsmBodySaveTex_Garage2::render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {

}

void AsmBodySaveTex_Garage2::load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	int tex_index2 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	texe = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, g->getScreenWidth() - 236 - 50,30+51+ 50 + 26, 236, 52, 0, 98, 236, 52);
	MYRECT re;
	re.left = g->getScreenWidth() - 236 - 50;
	re.right = re.left + 236;
	re.top = 31+50+26+50;
	re.bottom = re.top + 52;
	this->setRect(&re);
}

void AsmBodyLoadTex_Garage2::render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {

}

void AsmBodyLoadTex_Garage2::load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	int tex_index2 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	texe = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, g->getScreenWidth() - 236 - 50, 100+51+50 + 52 + 25, 236, 50, 0, 150, 236, 50);
	MYRECT re;
	re.left = g->getScreenWidth() - 236 - 50;
	re.right = re.left + 236;
	re.top = 51+50 + 25 + 52+100;
	re.bottom = re.top + 50;
	this->setRect(&re);
}

void ShopTex_Garage2::load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	int tex_index2 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	texe = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, g->getScreenWidth() - 236 - 50, 150+51+50 + 52 + 50+27, 236, 50, 0, 201, 236, 55);
	MYRECT re;
	re.left = g->getScreenWidth() - 236 - 50;
	re.right = re.left + 236;
	re.top = 51+50 + 50 + 52+27+150;
	re.bottom = re.top + 55;
	this->setRect(&re);
}
void ShopTex_Garage2::render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {

}


bool AssembleTex_Garage2::selected(int x, int y) {

	bool  t = Garage2_part::selected(x, y);
	if (t) {
		MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow("resrc/script/SCENE_LOADTYUU.lua");
	}
	return t;
};
*/
unsigned int Gamen2_part::part_id = 0;



ShopParts::PartsListCategory getPLC(int fc, int fc2) {
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_ARM) {
		return ShopParts::PartsListCategory::ARM;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_BODY) {
		return ShopParts::PartsListCategory::BODY;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_HEAD) {
		return ShopParts::PartsListCategory::HEAD;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_BOOSTER) {
		return ShopParts::PartsListCategory::BOOSTER;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_FCS) {
		return ShopParts::PartsListCategory::FCS;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_ENGINE) {
		return ShopParts::PartsListCategory::ENGINE;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_INSIDE) {
		return ShopParts::PartsListCategory::INSIDE_WEAPON;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LEG) {
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_4) {
			return ShopParts::PartsListCategory::LEG_4;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_K2) {
			return ShopParts::PartsListCategory::LEG_k2;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_T2) {
			return ShopParts::PartsListCategory::LEG_t2;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_J2) {
			return ShopParts::PartsListCategory::LEG_j2;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_REVERSE) {
			return ShopParts::PartsListCategory::LEG_REVERSE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_TANK) {
			return ShopParts::PartsListCategory::LEG_tank;
		}
		return ShopParts::PartsListCategory::UNKNOWN;
	}

	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RARM) {
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_BAZOOKA) {
			return ShopParts::PartsListCategory::RARMWEAPON_BAZOOKA;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_BLADE) {
			return ShopParts::PartsListCategory::RARMWEAPON_BLADE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ENERGYBLADE) {
			return ShopParts::PartsListCategory::RARMWEAPON_ENERGYBLADE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ENERGYRIFLE) {
			return ShopParts::PartsListCategory::RARMWEAPON_ENERGYRIFLE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_GRENEDE) {
			return ShopParts::PartsListCategory::RARMWEAPON_GRENEDE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_HANABIGUN) {
			return ShopParts::PartsListCategory::RARMWEAPON_HANABIGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_HANDGUN) {
			return ShopParts::PartsListCategory::RARMWEAPON_HANDGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_MACHINEGUN) {
			return ShopParts::PartsListCategory::RARMWEAPON_MACHINEGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_MISSILE) {
			return ShopParts::PartsListCategory::RARMWEAPON_MISSILE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PILE) {
			return ShopParts::PartsListCategory::RARMWEAPON_PILE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PLAZUMAGUN) {
			return ShopParts::PartsListCategory::RARMWEAPON_PLAZUMAGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PULSEGUN) {
			return ShopParts::PartsListCategory::RARMWEAPON_PULSEGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_RIFLE) {
			return ShopParts::PartsListCategory::RARMWEAPON_RIFLE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ROCKET) {
			return ShopParts::PartsListCategory::RARMWEAPON_ROCKET;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_SHOTGUN) {
			return ShopParts::PartsListCategory::RARMWEAPON_SHOTGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_SNIPERRIFLE) {
			return ShopParts::PartsListCategory::RARMWEAPON_SNIPERRIFLE;
		}

		return ShopParts::PartsListCategory::UNKNOWN;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LARM) {
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_BAZOOKA) {
			return ShopParts::PartsListCategory::LARMWEAPON_BAZOOKA;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_BLADE) {
			return ShopParts::PartsListCategory::LARMWEAPON_BLADE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ENERGYBLADE) {
			return ShopParts::PartsListCategory::LARMWEAPON_ENERGYBLADE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ENERGYRIFLE) {
			return ShopParts::PartsListCategory::LARMWEAPON_ENERGYRIFLE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_GRENEDE) {
			return ShopParts::PartsListCategory::LARMWEAPON_GRENEDE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_HANABIGUN) {
			return ShopParts::PartsListCategory::LARMWEAPON_HANABIGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_HANDGUN) {
			return ShopParts::PartsListCategory::LARMWEAPON_HANDGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_MACHINEGUN) {
			return ShopParts::PartsListCategory::LARMWEAPON_MACHINEGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_MISSILE) {
			return ShopParts::PartsListCategory::LARMWEAPON_MISSILE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PILE) {
			return ShopParts::PartsListCategory::LARMWEAPON_PILE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PLAZUMAGUN) {
			return ShopParts::PartsListCategory::LARMWEAPON_PLAZUMAGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PULSEGUN) {
			return ShopParts::PartsListCategory::LARMWEAPON_PULSEGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_RIFLE) {
			return ShopParts::PartsListCategory::LARMWEAPON_RIFLE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ROCKET) {
			return ShopParts::PartsListCategory::LARMWEAPON_ROCKET;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_SHOTGUN) {
			return ShopParts::PartsListCategory::LARMWEAPON_SHOTGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_SNIPERRIFLE) {
			return ShopParts::PartsListCategory::LARMWEAPON_SNIPERRIFLE;
		}
		return ShopParts::PartsListCategory::UNKNOWN;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RKATA) {
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_CHAINGUN) {
			return ShopParts::PartsListCategory::RKATAWEAPON_CHAINGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_GRENEDE) {
			return ShopParts::PartsListCategory::RKATAWEAPON_GRENEDE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_HANABI) {
			return ShopParts::PartsListCategory::RKATAWEAPON_HANABI;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_MISSILE) {
			return ShopParts::PartsListCategory::RKATAWEAPON_MISSILE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_PLAZUMA) {
			return ShopParts::PartsListCategory::RKATAWEAPON_PLAZUMA;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_PULSE) {
			return ShopParts::PartsListCategory::RKATAWEAPON_PULSE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_RASER) {
			return ShopParts::PartsListCategory::RKATAWEAPON_RASER;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_ROCKET) {
			return ShopParts::PartsListCategory::RKATAWEAPON_ROCKET;
		}
		return ShopParts::PartsListCategory::UNKNOWN;
	}
	if (fc == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LKATA) {
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_CHAINGUN) {
			return ShopParts::PartsListCategory::LKATAWEAPON_CHAINGUN;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_GRENEDE) {
			return ShopParts::PartsListCategory::LKATAWEAPON_GRENEDE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_HANABI) {
			return ShopParts::PartsListCategory::LKATAWEAPON_HANABI;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_MISSILE) {
			return ShopParts::PartsListCategory::LKATAWEAPON_MISSILE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_PLAZUMA) {
			return ShopParts::PartsListCategory::LKATAWEAPON_PLAZUMA;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_PULSE) {
			return ShopParts::PartsListCategory::LKATAWEAPON_PULSE;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_RASER) {
			return ShopParts::PartsListCategory::LKATAWEAPON_RASER;
		}
		if (fc2 == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_ROCKET) {
			return ShopParts::PartsListCategory::LKATAWEAPON_ROCKET;
		}
		return ShopParts::PartsListCategory::UNKNOWN;
	}
	return ShopParts::PartsListCategory::UNKNOWN;
}

void ShopParts_Garage2::load(Graphics* g) {

	// ロードでは パーツのメタデータとgarage_partsgroupの登録などまでを行う
	if (!sp) {
		sp = new ShopParts(getPLC(this->parts_category, this->parts_category2),loader);
		sp->load(g);
	}

	

	setLoaded();
}

void ShopParts_Garage2::atoload(Graphics* g) {
	// atoloadでは　robopartsのデータのメッシュロードを行う
	if (sp) {
		//if (!sp->hasLoaded()) {
			sp->atoload(g);
		//}
	}

}

void Garage2::modoru(Texture* tex, Texture* tex2, Game* game) {
	CS::instance()->enter(CS_LOAD_CS, "enter");
	if (shopparts_g) {
		this->destruct_shopparts.push_back(shopparts_g);
		shopparts_g = 0;
	}
	if (focused_part) {
		focused_part = 0;
	}
	if (selected_categorypart) {
		selected_categorypart = 0;
	}
	CS::instance()->leave(CS_LOAD_CS, "enter");
	if (robog) {
	//	MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_SHOP_BUY_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_NO);
	
		MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->clearCPPParts(KTROBO_GAMEN2_SCENE_ID_GARAGE);
		MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->setCPPParts(robog, KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO);
		MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow("resrc/script/garage/modoru.lua");
		MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->doAndCoDoExecByKey(1);
	}
}





void Garage2::pressed_button_enter(MyTextureLoader* loader, Texture* tex1, Texture* tex2, Game* game) {
	
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
				if (eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS) == KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES) {
					// 
					if (this->shopparts_g) {
						this->destruct_shopparts.push_back(shopparts_g);
					}
					shopparts_g = new ShopParts_Garage2(eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY),
						eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2), loader);


					eve->setHensuu(KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_NO);
				}
				if (eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL) != KTROBO_GARAGE2_HENSUU_LUA_KEY_CALL_NOKEY) {
					int key = eve->getHensuu(KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL);

					CS::instance()->leave(CS_LOAD_CS, "ee");
					CS::instance()->leave(CS_MESSAGE_CS, "e");
					MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->doAndCoDoExecByKey(
						key);
					CS::instance()->enter(CS_MESSAGE_CS, "e");
					CS::instance()->enter(CS_LOAD_CS, "ee");
					eve->setHensuu(KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL, KTROBO_GARAGE2_HENSUU_LUA_KEY_CALL_NOKEY);
				}

			
				// 変数をセットする
				// bool is_load_parts
			}
			selected_categorypart = focused_part;
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
void Garage2::pressed_button_up(Texture* tex1, Texture* tex2, Game* game) {
	
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
void Garage2::pressed_button_down(Texture* tex1, Texture* tex2, Game* game) {
	
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
void Garage2::pressed_button_left(Texture* tex1, Texture* tex2, Game* game) {

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
void Garage2::pressed_button_right(Texture* tex1, Texture* tex2, Game* game) {
	
	CS::instance()->enter(CS_MESSAGE_CS, "e");
	CS::instance()->enter(CS_LOAD_CS, "ee");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		sono->setCursorX(sono->getCursorX() - 1);
		int all_inde = sono->getCursorGroup();
		Gamen2_part* pp = 0;
		pp =MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(all_inde);
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