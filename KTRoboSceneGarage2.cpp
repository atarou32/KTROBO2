#include "KTRoboSceneGarage2.h"

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
	garage_impl->render(g, &view, g->getProj());
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

	garage_impl = new Garage2();

	Scene::enter();


}


void SceneGarage2::leave() {

	Scene::leave();
/*
	if (gg) {
		InputMessageDispatcher::unregisterImpl(gg);
		gg->Release();
		delete gg;
		gg = 0;
	}
*/

}

void Garage2::render(Graphics* g, MYMATRIX* view, MYMATRIX* proj) {
	if (robog) {
		robog->render(g, view, proj);
	}
	if (robog2) {
		robog2->render(g, view, proj);
	}
	if (robog3) {
		robog3->render(g, view, proj);
	}

	if (robog4) {
		robog4->render(g, view, proj);
	}

	if (robog5) {
		robog5->render(g, view, proj);
	}

}

bool SceneGarage2::handleMessage(int msg, void* data, DWORD time) {

	return false;
}



Garage2::Garage2() : Loadable2() {
	robog = 0;
	robog2 = 0;
	robog3 = 0;
	robog4 = 0;
	robog5 = 0;
	
};
Garage2::~Garage2() {
	if (robog) {
		delete robog;
			robog = 0;
	}

	if (robog2) {
		delete robog2;
			robog2 = 0;
	}

	if (robog3) {
		delete robog3;
			robog3 = 0;
	}

	if (robog4) {
		delete robog4;
			robog4 = 0;
	}

	if (robog5) {
		delete robog5;
			robog5 = 0;
	}

};

void Garage2::atoload(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader) {
	if (!robog->getTouroku()) {
		robog->load(g, loader, hantei);
		robog->robo->atarihan->setXYZ(0, 3, 0);
		robog->touroku();
		return;
	}

	if (!robog2->getTouroku()) {
		robog2->load(g, loader, hantei);
		robog2->robo->atarihan->setXYZ(0, 6, 0);
		robog2->touroku();
		return;
	}

	if (!robog3->getTouroku()) {
		robog3->load(g, loader, hantei);
		robog3->robo->atarihan->setXYZ(0, 9, 0);
		robog3->touroku();
		return;
	}
	if (!robog4->getTouroku()) {
		robog4->load(g, loader, hantei);
		robog4->robo->atarihan->setXYZ(0, -19, 0);
		robog4->touroku();
		return;
	}
	if (!robog5->getTouroku()) {
		robog5->load(g, loader, hantei);
		robog5->robo->atarihan->setXYZ(0, 19, 0);
		robog5->touroku();
		return;
	}



}


void Garage2::load(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader) {
	
	if (hasLoaded()) {
		atoload(g, hantei, tex, tex2, loader);
		return;
	}
	robog = new MyRobo_Garage2();
	robog2 = new MyRobo_Garage2();
	robog3 = new MyRobo_Garage2();
	robog4 = new MyRobo_Garage2();
	robog5 = new MyRobo_Garage2();
//	robog->load(g, loader, hantei);

	setLoaded();
	
}


MyRobo_Garage2::MyRobo_Garage2() : Loadable2(), Garage2_part() {
	robo = 0;
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

void MyRobo_Garage2::render(Graphics* g, MYMATRIX* view, MYMATRIX* proj) {

	if (hasLoaded()) {
		robo->byouga(g, view, proj);
	}
	else {
		// haribote->render(g, view, proj);
		haribote_render(g, view, proj);
	}
}

void MyRobo_Garage2::load(Graphics* g, MyTextureLoader* loader, AtariHantei* hantei) {
	// user/MyRobo.robodat を開いて該当のパーツのロボを作る
	robo = new Robo();
	robo->init(g, loader, hantei);
	
	setLoaded();
}

unsigned int Garage2_part::part_id = 0;