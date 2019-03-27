#include "KTRoboSceneGarage2.h"
#include "KTRoboGame.h"
#include "tolua_glue/tolua_glue.h"

using namespace KTROBO;

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




}


void SceneGarage2::aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {

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

	garage_impl->load(g, hantei, tex, tex2, loader);


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

	CS::instance()->enter(CS_LOAD_CS, "ee");
	CS::instance()->enter(CS_MESSAGE_CS, "e");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		try {
			int focused_group_all_index = sono->getCursorGroup();
			Gamen2_part* focused_part = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(focused_group_all_index);
			if (focused_part) {

				tex1->setRenderTexPos(cursor_tex, focused_part->getRect()->left - 70, focused_part->getRect()->top);
			}


		}
		catch (GameError* err) {
			// 無視する
		}
		catch (...) {
			CS::instance()->leave(CS_MESSAGE_CS, "e");
			CS::instance()->leave(CS_LOAD_CS, "ee");
			
		}
	}
	CS::instance()->leave(CS_MESSAGE_CS, "e");
	CS::instance()->leave(CS_LOAD_CS, "ee");


}

void Garage2::render(Graphics* g,Texture* tex,Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {
	CS::instance()->enter(CS_RENDERDATA_CS, "render");
	if (robog) {
		robog->render(g, tex2,view, proj);










	}

	if (gtex_g) {
		gtex_g->render(g, tex2, view, proj);
	}
	CS::instance()->leave(CS_RENDERDATA_CS, "render");
}

bool SceneGarage2::handleMessage(int msg, void* data, DWORD time) {
	MYINPUTMESSAGESTRUCT* input = (MYINPUTMESSAGESTRUCT*)data;
	int x = input->getMOUSESTATE()->mouse_x;
	int y = input->getMOUSESTATE()->mouse_y;


	garage_impl->setCursorTexPosToCursorPos(tex, tex2, game);

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
			garage_impl->mouse_clicked_up(tex,tex2,game, x, y);
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
		}
	}
	/*
	if (msg == KTROBO_INPUT_MESSAGE_ID_KEYDOWN) {


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
};

void Garage2::atoload(Graphics* g, AtariHantei* hantei, Texture* tex1, Texture* tex2, MyTextureLoader* loader) {
	if (!robog->getTouroku()) {
		robog->load(g, tex1,tex2, loader, hantei);
		robog->robo->atarihan->setXYZ(0, 0, 0);
		robog->touroku();
		return;
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

	CS::instance()->enter(CS_LOAD_CS, "ee");
	CS::instance()->enter(CS_MESSAGE_CS, "e");
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
				pp->unfocused(x, y);

			}
		}


		cgsize = cg->size();
		for (int i = 0; i < cgsize; i++) {
			vector<int>* gro = (*cg)[i];
			int grosize = gro->size();

			for (int k = 0; k < grosize; k++) {
				int ginde = (*gro)[k];
				Gamen2_part* pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(ginde);
				if (pp->focused(x, y)) {
					if (pp != focused_part) {
						char test[1024];
						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getHelpString());
						tex2->setRenderTextChangeText(help_text, test);
						focused_part = pp;
						sono->setCursorXY(pp->getAllIndex());

						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getFocusedLua());
						if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
							MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
						}


					}
					CS::instance()->leave(CS_MESSAGE_CS, "e");
					CS::instance()->leave(CS_LOAD_CS, "ee");
					return;
				}
			}
		}


		if (focused_part != 0) {
			focused_part = 0;
			char test[1024];
			memset(test, 0, 1024);
			mystrcpy(test, 1024, 0, this->getHelpStringWhenNoneFocused());
			tex2->setRenderTextChangeText(help_text, test);
		}
	}
	CS::instance()->leave(CS_MESSAGE_CS, "e");
	CS::instance()->leave(CS_LOAD_CS, "ee");


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


	CS::instance()->enter(CS_LOAD_CS, "ee");
	CS::instance()->enter(CS_MESSAGE_CS, "e");
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
				pp->unfocused(x, y);

			}
		}


		cgsize = cg->size();
		for (int i = 0; i < cgsize; i++) {
			vector<int>* gro = (*cg)[i];
			int grosize = gro->size();

			for (int k = 0; k < grosize; k++) {
				int ginde = (*gro)[k];
				Gamen2_part* pp = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(ginde);
				if (pp->focused(x, y)) {
					if (pp != focused_part) {
						char test[1024];
						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getHelpString());
						tex2->setRenderTextChangeText(help_text, test);
						focused_part = pp;
						sono->setCursorXY(pp->getAllIndex());

						memset(test, 0, 1024);
						mystrcpy(test, 1024, 0, pp->getFocusedLua());
						if (strcmp(test, KTROBO_GAMEN2_LUA_FILENAME_NO_LUA) != 0) {
							MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(test);
						}


					}
					CS::instance()->leave(CS_MESSAGE_CS, "e");
					CS::instance()->leave(CS_LOAD_CS, "ee");
					return;
				}
			}
		}


		if (focused_part != 0) {
			focused_part = 0;
			char test[1024];
			memset(test, 0, 1024);
			mystrcpy(test, 1024, 0, this->getHelpStringWhenNoneFocused());
			tex2->setRenderTextChangeText(help_text, test);
		}
	}
	CS::instance()->leave(CS_MESSAGE_CS, "e");
	CS::instance()->leave(CS_LOAD_CS, "ee");





}

void Garage2::mouse_clicked_up(Texture* tex, Texture* tex2, Game* game, int x, int y) {
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

	CS::instance()->enter(CS_LOAD_CS, "ee");
	CS::instance()->enter(CS_MESSAGE_CS, "e");
	Gamen2_Sonotoki* sono = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getNowSonotoki();
	if (sono) {
		int focused_group_all_index = sono->getCursorGroup();
		Gamen2_part* focused_part = MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->getGamen2Part(focused_group_all_index);
		if (focused_part->selected(x, y)) {
			// lua ファイルを呼ぶ
			MyLuaGlueSingleton::getInstance()->getColGamen2s(0)->getInstance(0)->pauseWork();
			selected_categorypart = focused_part;
			char strdayo[1024];
			memset(strdayo, 0, 1024);
			mystrcpy(strdayo, 1024, 0, focused_part->getSelectedLua());
			if (strcmp(KTROBO_GAMEN2_LUA_FILENAME_NO_LUA, strdayo) != 0) {
				MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(strdayo);
			}
		}
	}
	CS::instance()->leave(CS_MESSAGE_CS, "e");
	CS::instance()->leave(CS_LOAD_CS, "ee");

}

void Garage2::load(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader) {
	
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
	cursor_tex = tex->getRenderTex(tex_index2, 0xFFFFFFFF, 100, 100, 67, 490 - 437, 0, 437, 67, 490 - 437);
	
	help_text_waku = tex->getRenderTex(tex_index2,0x000000FF,10,g->getScreenHeight()-55+11,g->getScreenWidth()-20,20, 18, 390, 1, 1);
	//tex->setRenderTexIsRender(help_text_waku, false);
}


MyRobo_Garage2::MyRobo_Garage2() : Loadable2(), Gamen2_part() {
	robo = 0;
	tex_waku = 0;
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
		ggg3.TopLeftX = 50;
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

void MyRobo_Garage2::load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	// user/MyRobo.robodat を開いて該当のパーツのロボを作る
	robo = new Robo();
	robo->init(g, loader, hantei);
	int tex_index2  = tex1->getTexture(KTROBO_GARAGE2_IMG_PATH);
	tex_haikei = tex1->getRenderTex(tex_index2, 0xFFFFFFFF, 50, 350, 400, 400, 18, 390, 1, 1);
	tex1->setRenderTexColor(tex_haikei, 0xAAAAAAFF);
	int tex_index = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
//	tex_waku = tex2->getRenderTex(tex_index, 0xFFFFFFFF, 0, 0, 238, 46, 0, 0, 238, 46);
	tex_waku = tex2->getRenderTex(tex_index, 0xFFFFFFFF, 50,350,400,400, 245, 0, 200, 200);
	MYRECT re;
	re.left = 50;
	re.right = 50 + 400;
	re.top = 350;
	re.bottom = 350 + 400;
	setRect(&re);
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
	int tex_index2 = tex2->getTexture(KTROBO_GARAGE2_IMG_PATH);
	texe = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, 5, 5, 236, 46, 0, 0, 236, 46);
	MYRECT re;
	re.left = 5;
	re.right = 236+5;
	re.top = 5;
	re.bottom = 46+5;
	this->setRect(&re);
	tex_waku = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, 5, 5, g->getScreenWidth()-10, g->getScreenHeight()-10 , 245, 0, 200, 200);
	
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