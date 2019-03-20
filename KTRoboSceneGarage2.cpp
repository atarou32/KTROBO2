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

	garage_impl->load(hantei, tex, tex2, loader);



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


bool SceneGarage2::handleMessage(int msg, void* data, DWORD time) {

	return false;
}



Garage2::Garage2() : Loadable2() {

};
Garage2::~Garage2() {

};

void Garage2::load(AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader) {

}