#include "KTROBOQuest.h"
#include "KTRoboGame.h"
#include "tolua_glue/tolua_glue.h"

KTROBOQuest::KTROBOQuest(void)
{
}


KTROBOQuest::~KTROBOQuest(void)
{
}

using namespace KTROBO;


QUEST_SCENE::QUEST_SCENE(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader) : Scene("gamescene", 9) {
	this->g = g;
	this->hantei = hantei;
	this->tex = tex;
	this->tex2 = tex2;
	this->loader = loader;
	quest_loaded = false;
	quest_started = false;

	tikei = new TikeiMap();
	tikei->Init(hantei, MyLuaGlueSingleton::getInstance()->getColMeshInstanceds(0));

	e_manager = new EntityManager();
	e_manager->Init(g, loader,hantei);
	Entity::AtariMeshInit(g, loader);

	exampletext = new Text(L"test‚Å‚·", wcslen(L"test‚Å‚·"));

	camera_work = new CameraWork();

	bullet_c = new BulletController();
	bullet_c->Init(g, hantei, loader, NULL);
	dtime = 0;
}
QUEST_SCENE::~QUEST_SCENE(void) {
	if (tikei) {
		tikei->Del();
		delete tikei;
		tikei = 0;
	}

	if (exampletext) {
		delete exampletext;
		exampletext = 0;
	}

	if (e_manager) {
		e_manager->Del();
		delete e_manager;
		e_manager = 0;
	}

	if (camera_work) {
		delete camera_work;
		camera_work = 0;
	}

	Entity::AtariMeshDel();

	if (bullet_c) {
		bullet_c->Release();
		delete bullet_c;
		bullet_c = 0;
	}
	
}



void QUEST_SCENE::mainrenderIMPL(bool is_focused, Graphics* g, Game* game) {
	
	if (quest_loaded && quest_started) {
		MYMATRIX view;
		static float tess = 0;
		MYMATRIX te;
		tess += 0.1f;
		MYVECTOR3 lookat;
		camera_work->getLookAt(&lookat);// MYVECTOR3(0, 0, 30);
		MYVECTOR3 lookfrom;
		camera_work->getLookFrom(&lookfrom);// = MYVECTOR3(0 + 13 * sin(tess / 10.0), 13 * cos(tess / 10.0), tess / 1.0f);
		MYVECTOR3 lookup = MYVECTOR3(0, 0, 1);
		MYMATRIX rotxma;
//		MyMatrixRotationZ(rotxma, tess/100.0f);
		CS::instance()->enter(CS_DEVICECON_CS, "test");
		CS::instance()->enter(CS_RENDERDATA_CS, "test");
		camera_work->calculateView();
		camera_work->getView(&view);
//		MyMatrixMultiply(view, rotxma, view);

		game->view = view;
		game->lookfromtoat = lookat - lookfrom;
		tex->setViewProj(g, &view, g->getProj(), &lookfrom, &lookat);
		tex2->setViewProj(g, &view, g->getProj(), &lookfrom, &lookat);
		

		MYMATRIX worl;
		MyMatrixTranslation(worl, 0, 0, 15);
		camera_work->getViewOfText(&view, &worl);
		
	//	MyMatrixRotationX(mattt, tess);// -1.57f);
	//	MyMatrixMultiply(view,view, mattt);
	//	MyMatrixRotationX(mattt, test);
	
		//MyMatrixIdentity(view, view);
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			Text::setVIEWPROJ(g, &view, g->getProj());
			exampletext->renderWorld(g, 0xFFFFFFFF, &worl, 25*20, 25*100, 25*20);
		MYMATRIX proj = *g->getProj();
		MYMATRIX ans;
		camera_work->getView(&view);
		MyMatrixMultiply(ans, worl, view);
		MyMatrixMultiply(ans, ans, proj);
		MYVECTOR3 pos(0, 0, 0);
		MyVec3TransformCoord(pos, pos, ans);
		int x = (1 + pos.float3.x) * g->getScreenWidth() / 2;
		int y = g->getScreenHeight() - (1 + pos.float3.y) * g->getScreenHeight() / 2;
	//	exampletext->render(g, 0xFFFFFFFF, x, y, 31, 250, 30);
		e_manager->byouga(g,game, &game->view, g->getProj(), game->getDMSecond(), game->getTimeStamp());
		tikei->byouga(g);
			e_manager->updateAtariAndMeshInstanced(g, hantei, game->getDMSecond(),/*watches.times[TASKTHREADS_UPDATEANIMEFRAMENADO],*/ game->getTimeStamp());
	
		if (bullet_c) {
			bullet_c->byouga(g, &game->view, g->getProj(), game->getDMSecond(), game->getTimeStamp());
		}
		
		
		CS::instance()->leave(CS_RENDERDATA_CS, "test");
		CS::instance()->leave(CS_DEVICECON_CS, "test");
		
	}


}

void QUEST_SCENE::renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {
	Sleep(1);
	if (quest_loaded && quest_started) {
		watches.stopWatch(TASKTHREADS_UPDATEANIMEFRAMENADO);
		watches.startWatch(TASKTHREADS_UPDATEANIMEFRAMENADO);
		CS::instance()->enter(CS_DEVICECON_CS, "test");
		CS::instance()->enter(CS_RENDERDATA_CS, "test");
	
		e_manager->updatemis(g);
		if (bullet_c) {
			bullet_c->calcUpdate(g);
		}
		CS::instance()->leave(CS_RENDERDATA_CS, "test");
		CS::instance()->leave(CS_DEVICECON_CS, "test");
	
		
	}




}

void QUEST_SCENE::aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {
	Sleep(1);

}

void QUEST_SCENE::posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {
	
	//DebugTexts::instance()->setText(g,12,L"startposimpl");
	double millisecond = game->stopWatchForButukari();//stopWatch();
	game->startWatchForButukari();
	if (millisecond > RENDERTIME_IGNORETIME) {
		CS::instance()->leave(CS_TASK_CS, "leave main", TASKTHREADS_UPDATEPOSBUTUKARI);
		//DebugTexts::instance()->setText(g,9,L"leavetask");
		Sleep(1);
		millisecond = POSBUTUKARITIME_SETTIME;
		butukari_clock.plus((float)millisecond);
		CS::instance()->enter(CS_TASK_CS, "enter main", TASKTHREADS_UPDATEPOSBUTUKARI);
		//DebugTexts::instance()->setText(g,9,L"entertask");
	}
	else if ((millisecond < POSBUTUKARITIME_SETTIME) && (millisecond > 0)) {
		CS::instance()->leave(CS_TASK_CS, "leave main", TASKTHREADS_UPDATEPOSBUTUKARI);
		butukari_clock.plus((float)millisecond);
		Sleep((DWORD(POSBUTUKARITIME_SETTIME - millisecond)) / 2);
		//	ClockWatch::wait(POSBUTUKARITIME_SETTIME - millisecond);

	/*		char buf[512];
			WCHAR wbuf[512];

			_itoa(POSBUTUKARITIME_SETTIME - millisecond,buf,10);
			stringconverter sc;
			sc.charToWCHAR(buf,wbuf);
			DebugTexts::instance()->setText(g,wcslen(wbuf),wbuf);
			//Sleep(1);
			*/
		millisecond = POSBUTUKARITIME_SETTIME;
		CS::instance()->enter(CS_TASK_CS, "enter main", TASKTHREADS_UPDATEPOSBUTUKARI);
	}
	else {

		CS::instance()->leave(CS_TASK_CS, "leave main", TASKTHREADS_UPDATEPOSBUTUKARI);
		butukari_clock.plus((float)millisecond);
		/*
				char buf[512];
				WCHAR wbuf[512];

				_itoa(POSBUTUKARITIME_SETTIME - millisecond,buf,10);
				stringconverter sc;
				sc.charToWCHAR(buf,wbuf);
				DebugTexts::instance()->setText(g,wcslen(wbuf),wbuf);
		*/
			Sleep(1);
		//	millisecond = POSBUTUKARITIME_SETTIME;
		CS::instance()->enter(CS_TASK_CS, "enter main", TASKTHREADS_UPDATEPOSBUTUKARI);
	}

	float frameTime = millisecond;
	int frame = game->getTimeStamp();//butukari_clock.getSecond();


//	CS::instance()->enter(CS_RENDERDATA_CS,"unko");

//	Sleep(5000);
	/*
	hantei->ataristart();
	hantei->maecalcdayo(g);
	hantei->calcAuInfo(g,true);
	hantei->calcKumi(g);
	hantei->calcObb(g);
	hantei->clearKekkaOfBuffer(g);
	hantei->runComputeShader(g);

	hantei->copyKekkaToBufferForCopy(g,true);

	hantei->calcKumiKuwasiku(g);
	hantei->runComputeShaderKuwasiku(g);
	hantei->copyKekkaToBufferForCopy(g,false);
	*/

	//	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());

	

	if (game && quest_loaded/* && task->getIsExecTask()*/) {
	
		//		CS::instance()->enter(CS_MESSAGE_CS, "test");

		CS::instance()->enter(CS_DEVICECON_CS, "unko");
		
		
		char buf[512];
		WCHAR wbuf[512];

		hantei->ataristart();
		hantei->maecalcdayo(g);
		hantei->maeCalcDummy(g);
		game->watches_for_keisoku.stopWatch(5);
		game->watches_for_keisoku.startWatch(6);
		hantei->calcAuInfo(g, true);
		game->watches_for_keisoku.stopWatch(6);
		game->watches_for_keisoku.startWatch(7);
		hantei->calcKumi(g);
		game->watches_for_keisoku.stopWatch(7);
		game->watches_for_keisoku.startWatch(8);
		hantei->calcObb(g);
		game->watches_for_keisoku.stopWatch(8);
		game->watches_for_keisoku.startWatch(9);
		hantei->copyCounterOfKekkaBuffer(g);
		game->watches_for_keisoku.stopWatch(9);
		game->watches_for_keisoku.startWatch(3);
		hantei->runComputeShaderAida(g);
		game->watches_for_keisoku.stopWatch(3);


		//Sleep(10000);
		//hantei->copyKekkaToBufferForCopy(g,true);

		//hantei->calcKumiKuwasiku(g);
		//hantei->runComputeShaderKuwasiku(g);


		game->watches_for_keisoku.stopWatch(2);



		game->watches_for_keisoku.startWatch(1);
		//CS::instance()->leave(CS_RENDERDATA_CS, "unko");
		//CS::instance()->leave(CS_DEVICECON_CS, "unko");
		HRESULT hr;
		//CS::instance()->enter(CS_DEVICECON_CS, "unko");
		//CS::instance()->enter(CS_RENDERDATA_CS, "unko");
		CS::instance()->enter(CS_RENDERDATA_CS, "unko");

		if ((hr = hantei->copyKekkaToBufferForCopy2(g)) == S_OK) { // copy2
			//game->rmap->update();
			game->watches_for_keisoku.stopWatch(1);
			game->watches_for_keisoku.stopWatch(0);
			double test = game->watches_for_keisoku.times[0];
			game->watches_for_keisoku.startWatch(0);
			//Robo* robodayo = game->robodayo;
			//Robo* roboaitedayo = game->roboaitedayo;

			if (hantei->canGetAns()) {
				watches.stopWatch(TASKTHREADS_UPDATEPOSBUTUKARI);
				watches.startWatch(TASKTHREADS_UPDATEPOSBUTUKARI);
				if (abs(watches.times[TASKTHREADS_UPDATEPOSBUTUKARI]) < 200) {
					dtime = dtime + watches.times[TASKTHREADS_UPDATEPOSBUTUKARI];
				}
				if (dtime > 2000) {
					e_manager->atarishori(g, &game->view, hantei, watches.times[TASKTHREADS_UPDATEPOSBUTUKARI], game->getTimeStamp());
					e_manager->moveshori(g, &game->view, hantei, watches.times[TASKTHREADS_UPDATEPOSBUTUKARI], game->getTimeStamp());
					e_manager->updatePos(g, game, this, hantei, bullet_c, watches.times[TASKTHREADS_UPDATEPOSBUTUKARI], game->getTimeStamp());

					if (bullet_c) {
						bullet_c->update(g, game, hantei, watches.times[TASKTHREADS_UPDATEPOSBUTUKARI], game->getTimeStamp());
						bullet_c->atariShori(game, hantei, &game->view, watches.times[TASKTHREADS_UPDATEPOSBUTUKARI], game->getTimeStamp());
					}
					game->weapon_effect_manager->update(watches.times[TASKTHREADS_UPDATEPOSBUTUKARI]);
				}
				hantei->setIsCalcKuwasikuGetted();
			}
		
		

		}
	

	

//		gm->posButukari(g, this, game, hantei, watches.times[TASKTHREADS_UPDATEPOSBUTUKARI], game->getTimeStamp());
		
		CS::instance()->leave(CS_RENDERDATA_CS, "unko");
		CS::instance()->leave(CS_DEVICECON_CS, "unko");
		
	}
	
}

void QUEST_SCENE::loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game) {
	Sleep(1);
	if (!quest_loaded) {
		// ƒ[ƒh‚·‚é

		CS::instance()->enter(CS_TASK_CS, "buf", TASKTHREADS_UPDATEPOSBUTUKARI);

		e_manager->loadExample1(g,loader,tex);
		tikei->loadExample1(g,loader);
		camera_work->setPlayerCharacter(e_manager->getPlayer());

		CS::instance()->leave(CS_TASK_CS, "buf", TASKTHREADS_UPDATEPOSBUTUKARI);
		quest_loaded = true;
		dtime = 0;
		quest_started = true;
	}


}

void QUEST_SCENE::enter() {
	INPUTGETBYMESSAGESTRUCT* ss = InputMessageDispatcher::getRootInputGetStruct();
	while (ss->getParent()) {
		ss = ss->getParent();
	}
	InputMessageDispatcher::registerImpl(this, NULL, ss->impl);

	Scene::enter();
}
void QUEST_SCENE::leave() {
	Scene::leave();


	InputMessageDispatcher::unregisterImpl(this);
	//	gg->Release();
	//	delete gg;
	//	gg = 0;
	//}



}
bool QUEST_SCENE::handleMessage(int msg, void* data, DWORD time) {

	if (e_manager) {
		PlayerCharacterEntity* ent = e_manager->getPlayer();
		if (ent) {
			ent->handleMessage(msg, data, time);
		}
	}
	return false;
}


