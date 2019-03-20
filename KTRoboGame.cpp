#include "KTRoboGame.h"
#include "KTRoboGraphics.h"
#include "KTRoboTask.h"
#include "KTRoboClock.h"
#include "KTRoboCS.h"
#include "KTRoboGameError.h"
#include "stringconverter.h"
#include "tolua_glue/tolua_glue.h"
#include "KTRoboSceneGarage.h"
#include "KTROBOMission.h"

using namespace KTROBO;



// �^�X�N�X���b�h�̕���
// ���C���X���b�h�F�`��i���񏈗�������j
// TASK0:  �`��̂��߂̍X�V�����i�A�j���̌v�Z�����j�Ȃ�
// TASK1:  �I�u�W�F�N�g�̐����E�j������(���[�h�j�@�K�v�ȂƂ��������� 
// ���������j�������i�R���X�g���N�^�f�X�g���N�^�Ăяo���j������ꍇ��
    // ���̃X���b�h���g��Ȃ����Ƃ��m�F�܂��͎g���Ȃ���Ԃɂ��Ă���
    // �������s������
    // ���@���̂P�@�X���b�h�̃��b�N�������đ��̃X���b�h�̏���������Ȃ��悤�ȃ^�C�~���O�����
    //             ����͓ǂݍ��݃��[�h�����������Ȃ肻���ł��邱�Ƃ��l����ƗL���ȕ��@�Ƃ͂����Ȃ��悤�ȋC������
    // ���@���̂Q�@���[�h�����I�u�W�F�N�g�������Ă���R���N�V�����N���X�𑼂̃X���b�h���g�p���Ȃ��悤�Ȏd�g�݂����
    //             ����̓��[�h��p�R���N�V�����N���X����邱�Ƃ̂悤�ȋC������
    // ���@���̂Q������̓I�ɂǂ��������邩�@
    // �����̓��[�h�����I�u�W�F�N�g�����R���N�V�����N���X�����p����邱�Ƃ��l�����
    // �n�������̃^�C�~���O�ɋC�����Ȃ���΂Ȃ�Ȃ������b�N����i���[�h���Ă���ԃ��b�N���Ă�����͕��ʂ̂悤�ȋC������j
    // 

// TASK2:  �I�u�W�F�N�g�̍X�V�����EAI�H���񏈗������� ���C���i�s����
// TASK3:  �ՓˁE�ʒu�X�V�����F���񏈗�������
// TASK4:  ���͎擾����ѓ��͂̉��ߋL������

Game::Game(void)
{
	L =0;
	g = 0;
	this->timeEnd.QuadPart = 0;
	this->timeStart.QuadPart = 0;
	this->timeFreq.QuadPart = 1;
	fps = 0;
	c = 0;



	timestamp = 0;
	big_timestamp = 0;
	second = 0;
	dmsecond = 0;
	dt = 0;

	demo = 0;
	telop_texts = 0;

	for (int i = 0 ; i <TASKTHREAD_NUM; i++) {
		task_threads[i] = 0;
		g_for_task_threads[i] = 0;
		Ls[i]=0;
	}

	/*
	mesh = 0;
	mesh2 = 0;
	for (int i = 0 ; i < 11; i++) {
		mesh3[i] = 0;
	}
	*/
	
	texdayo = 0;
	//mytest_for_vt = 0;
	messages = 0;
	cltf = 0;
	cmeshs = 0;
	//te = 0;
	mesh_instanceds = 0;
	
	sound = 0;
	temp_input_shori = 0;
	//umesh_unit = 0;
	hantei = 0;
	/*
	sinai = 0;
	sfuru = 0;
	ksgene = 0;
	makers = 0;
	*/
	robodayo = 0;
	roboaitedayo = 0;
	//ss = 0;
	sap = 0;
	//gg = 0;
	renderTCB = 0;
	effect_managers = 0;
	weapon_effect_manager = 0;
	effect_suuji = 0;
	lua_ets = 0;
	rmap = 0;
}


Game::~Game(void)
{
}

void RENDERTCB(TCB* thisTCB) {
	
	Game* g = (Game*)(thisTCB->data);

	g->Run();
}


void CALCCOMBINEDTCB(TCB* thisTCB) {
	
	MeshInstanceds* mis = (MeshInstanceds*)thisTCB->data;
	Graphics* g = (Graphics*)thisTCB->Work[0];

	//if (!mis->getIsLoad()) {
	//CS::instance()->enter(CS_RENDERDATA_CS, "test");
	CS::instance()->enter(CS_DEVICECON_CS, "lock");
	mis->loadAnimeMatrixBasisToTexture(g);
	mis->loadMatrixLocalToTexture(g);
	mis->calcCombinedMatrixToTexture(g);
	mis->loadColorToTexture(g);
	CS::instance()->leave(CS_DEVICECON_CS, "unlock");
	//CS::instance()->leave(CS_RENDERDATA_CS, "test");
	//}
}




bool TempInputShori::handleMessage(int msg, void * data, DWORD time) {

	if (msg == KTROBO_INPUT_MESSAGE_ID_KEYDOWN) {
		MYINPUTMESSAGESTRUCT* input = (MYINPUTMESSAGESTRUCT*) data;
		if (input->getKEYSTATE()[VK_DOWN] & KTROBO_INPUT_BUTTON_DOWN) {

			CS::instance()->enter(CS_SOUND_CS, "enter");
			sound->stopCue(yumes[sound_index]);
			sound_index =(sound_index+1) % 7;
			sound->playCue(yumes[sound_index]);
			CS::instance()->leave(CS_SOUND_CS, "leave");
		}


	}

	if (msg == KTROBO_INPUT_MESSAGE_ID_MOUSERAWSTATE) {
		MYINPUTMESSAGESTRUCT* input = (MYINPUTMESSAGESTRUCT*) data;
		if (input->getMOUSESTATE()->mouse_l_button_pressed && input->getMOUSESTATE()->mouse_button & KTROBO_MOUSESTATE_L_DOWN) {
			float x = input->getMOUSESTATE()->mouse_x;
			float y = input->getMOUSESTATE()->mouse_y;
			MYVECTOR3 pos(x,y,1);
			MYVECTOR3 ou(0,0,0);
			MYVECTOR3 ou2(0,0,0);
			MYVECTOR3 pos2(x,y,0);
			D3D11_VIEWPORT pp = *g->getViewPort();
	//		pos.float3.y -=pp.Height;
	//		pos2.float3.y -= pp.Height;
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
			MyVec3Unproject(ou,pos,pp,proj,view,matd);
			MyVec3Unproject(ou2,pos2,pp,proj,view,matd);
			ray.dir = ou2 -ou;
			MyVec3Normalize(ray.dir,ray.dir);
			ray.dir = ray.dir*1;

			float bai = 1;
			if (ray.dir.float3.z > 0.000001f) {
				bai = ou.float3.z / ray.dir.float3.z;
			}



			ray.org = ou - ray.dir * bai;





			CS::instance()->leave(CS_MESSAGE_CS, "leave");


		}
	}

	if (msg == KTROBO_INPUT_MESSAGE_ID_MOUSEMOVE) {
		MYINPUTMESSAGESTRUCT* input = (MYINPUTMESSAGESTRUCT*) data;
			float x = input->getMOUSESTATE()->mouse_x;
			float y = input->getMOUSESTATE()->mouse_y;
			CS::instance()->enter(CS_MESSAGE_CS, "enter");
			this->x = x;
			this->y = y;
			MYVECTOR3 dvec(input->getMOUSESTATE()->mouse_dx, input->getMOUSESTATE()->mouse_dy,0);
			MYVECTOR3 vec(x,y,0);
			MYVECTOR3 tyusin(g->getViewPort()->Width/2,g->getViewPort()->Height/2,0);
			MYVECTOR3 temp = vec - tyusin;
			MYVECTOR3 gai;
			MyVec3Cross(gai,temp,dvec);


			if (gai.float3.z >0) {
				if (input->getMOUSESTATE()->mouse_r_button_pressed) {
					testdayo += 0.01f;
				}
			} else {
				if (input->getMOUSESTATE()->mouse_r_button_pressed) {
					testdayo -=0.01f;
				}
			}



			CS::instance()->leave(CS_MESSAGE_CS, "leave");
	}


	return false;
}



void LOADMESHTCB(TCB* thisTCB) {
	

	
	lua_State* L = (lua_State*)thisTCB->data;
	Task* t = (Task*)thisTCB->Work[0];
	Graphics* g = (Graphics*)thisTCB->Work[1];
	MeshInstanceds* m = (MeshInstanceds*)thisTCB->Work[2];
	
	/*
	char buff[] = "resrc/script/sample.lua.txt";
	int error=LUA_ERRERR;
	CS::instance()->enter(CS_LUAEXE_CS, "loadmeshtcb");
	try {
		error = luaL_loadfile(L, buff) || lua_pcall(L, 0, 0, 0);
	//	m->setIsLoad(false);
	}catch (GameError* err) {
		
	//	MessageBoxA(g->getHWND(), err->getMessage(), err->getErrorCodeString(err->getErrorCode()), MB_OK);
		delete err;
	}
	catch (...) {
		CS::instance()->leave(CS_LUAEXE_CS, "loadmeshtcb");
		throw new GameError(KTROBO::FATAL_ERROR, "fatal errordayo in loadmeshtcb");
	}
    if (error) {
		mylog::writelog("log/errtxt.txt", "%s", lua_tostring(L, -1));
		OutputDebugStringA(lua_tostring(L,-1));
        lua_pop(L, 1);
		CS::instance()->leave(CS_LUAEXE_CS, "loadmeshtcb");
		throw new GameError(KTROBO::WARNING, "error in lua");
    } else {
		// ����device_concs �����b�N���Ă��Ă��̏�ԂŃL�������̂��ȁH
		t->kill(thisTCB);
	}
	Sleep(1);
	CS::instance()->leave(CS_LUAEXE_CS, "loadmeshtcb");
	*/
}


void BUTUKARIPOSTCB2(TCB* thisTCB) {
	

	
	AtariHantei* hantei = (AtariHantei*)thisTCB->data;
	Task* t = (Task*)thisTCB->Work[0];
	Graphics* g = (Graphics*)thisTCB->Work[1];
//	vector<UMeshUnit*>* m = (vector<UMeshUnit*>*)thisTCB->Work[2];
//	CS::instance()->enter(CS_DEVICECON_CS, "ref");
//	CS::instance()->enter(CS_RENDERDATA_CS,"def");
	//CS::instance()->enter(CS_RENDERDATA_CS,"unko");
	
/**	
	hantei->maecalcdayo(g);
	hantei->ataristart();
	hantei->calc(g);
	**/
/*
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
	
	//CS::instance()->leave(CS_RENDERDATA_CS, "unko");
	
	
//	CS::instance()->leave(CS_RENDERDATA_CS, "def");
//	CS::instance()->leave(CS_DEVICECON_CS, "ref");
	
}

void BUTUKARIPOSTCB(TCB* thisTCB) {
	

	
	AtariHantei* hantei = (AtariHantei*)thisTCB->data;
	Task* t = (Task*)thisTCB->Work[0];
	Graphics* g = (Graphics*)thisTCB->Work[1];
	//vector<UMeshUnit*>* m = (vector<UMeshUnit*>*)thisTCB->Work[2];
//	CS::instance()->enter(CS_DEVICECON_CS, "ref");
//	CS::instance()->enter(CS_RENDERDATA_CS,"def");
//	AtariHantei::compileShader(g);
//	CS::instance()->leave(CS_RENDERDATA_CS, "def");
//	CS::instance()->leave(CS_DEVICECON_CS, "ref");







	t->change(thisTCB, BUTUKARIPOSTCB2, hantei);
}



void MessageDispatcherTCB(TCB* thisTCB) {
	/*
	CS::instance()->enter(CS_TASK_CS, "ai lock", 4);
	CS::instance()->enter(CS_TASK_CS, "load lock", 3);
	CS::instance()->enter(CS_TASK_CS, "render lock",2);
	CS::instance()->enter(CS_TASK_CS, "anime lock", 1);
	CS::instance()->enter(CS_TASK_CS, "atari lock", 0);
	*/
	InputMessageDispatcher::messageDispatch();
	LuaTCBMaker::makeTCBExec();

	/*
	CS::instance()->leave(CS_TASK_CS, "atari lock",0);
	CS::instance()->leave(CS_TASK_CS, "anime lock",1);
	CS::instance()->leave(CS_TASK_CS, "render lock",2);
	CS::instance()->leave(CS_TASK_CS, "load lock", 3);
	CS::instance()->leave(CS_TASK_CS, "ai lock", 4);
	*/
}


bool Game::Init(HWND hwnd) {
	// ���Ԃ������Ȃ����� cs �ƃ^�X�N�̊ԂɈˑ��֌W������
	
	g = new Graphics();

	if (!g->Init(hwnd)) {
		throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "graphics init error");
	}

	g_for_task_threads[2] = g;

	Graphics::InitMSS(g);
	
	

	demo = new KTRoboDemoRender();
	demo->Init(g);
	
	for (int i = 0 ; i <TASKTHREAD_NUM; i++) {
		task_threads[i] = Task::factory(hwnd);
		if (i == TASKTHREADS_UPDATEMAINRENDER ) {
			g_for_task_threads[i] = g;
			g_for_task_threads[i]->setTexLoader(demo->tex_loader);
		} else {
			g_for_task_threads[i] = g->makeGraphicsOfNewDeviceContext();
			g_for_task_threads[i]->setTexLoader(demo->tex_loader);
		}
	}
	
	
	Mesh::Init(g);
	MyTokenAnalyzer::Init();

	
	c = new Clock(0,0,0);
	Text::Init(g, demo->font);

//	te = new Text(L"����������",5);
	

	KTROBO::DebugTexts::instance()->Init(g, demo->font);


	telop_texts = new TelopTexts();
	telop_texts->Init(g,demo->font);
	telop_texts->readFile(g,"resrc/sample/terop.txt",30,14,&MYVECTOR4(1,1,1,1),0.03);
	
	AtariHantei::compileShader(g);
	hantei = new AtariHantei();
	//hantei->maecalcdayo(g);



	
	
	

	MeshInstanceds::Init(g);
	mesh_instanceds = new MeshInstanceds(g, this->demo->tex_loader);
	//mesh_instanceds->setSkeleton(mesh);
	
	
	
	
	MYMATRIX kakeru;
	MyMatrixIdentity(kakeru);
	
	sound = new MySound();
	HRESULT hr = sound->initialize();

	if (FAILED(hr)) {
		throw new GameError(KTROBO::FATAL_ERROR, "error in init sound");
	}
	
	//temp_input_shori = new TempInputShori(sound,g);
	//MYMATRIX m;
	//MyMatrixIdentity(m);
	//temp_input_shori->setMAT(&m,&m,&m);
	sound->playCue(yumes[5]);//temp_input_shori->sound_index]);
	//InputMessageDispatcher::registerImpl(temp_input_shori, NULL,NULL);

	MYMATRIX worl;
	
	

	
	
	

    int error;
	//Sleep(1000);
    L = luaL_newstate();
    luaopen_base(L);
	luaopen_coroutine(L);
//	guis = new GUIs();

	lua_ets = new LuaExectors(L);
	
	cltf = new TextFromLuas(g_for_task_threads[TASKTHREADS_LOADDESTRUCT], this);
//	abs = new AnimationBuilders(demo->tex_loader);
	cmeshs = new CMeshs(g, demo->tex_loader);
	messages = new Messages();
//	aes = new ActionEditors(demo->tex_loader);
//	MyLuaGlueSingleton::getInstance()->setColActionEditors(aes);
	MyLuaGlueSingleton::getInstance()->setColCMeshs(cmeshs);
//	MyLuaGlueSingleton::getInstance()->setColGUIs(guis);
	MyLuaGlueSingleton::getInstance()->setColMessages(messages);
	MyLuaGlueSingleton::getInstance()->setColTextFromLuas(cltf);
	MyLuaGlueSingleton::getInstance()->setColMeshInstanceds(mesh_instanceds);
//	MyLuaGlueSingleton::getInstance()->setColAnimationBuilders(abs);
	MyLuaGlueSingleton::getInstance()->setColLuaExectors(lua_ets);
	MyLuaGlueSingleton::getInstance()->registerdayo(L);

	for (int i=0;i<TASKTHREAD_NUM;i++) {
	//	Ls[i] = luaL_newstate();
	//	luaL_openlibs(Ls[i]);
	//	MyLuaGlueSingleton::getInstance()->registerdayo(Ls[i]);
	}
	
	LuaTCBMaker::Init(task_threads, L);
	Texture::Init(g);
	
	Scene::Init(g_for_task_threads,this); // scene init ����@L���Ȃ����@lua���K�v�ȂƂ���luaexector ���Ă�.
	
	texdayo = new Textures(demo->tex_loader);
	MyLuaGlueSingleton::getInstance()->setColTextures(texdayo);	
	texdayo->getInstance(0)->getTexture(KTROBO_GUI_PNG,4096);
	int pp = texdayo->getInstance(1)->getTexture(KTROBO_GUI_PNG, 4096);
	
	
	MYMATRIX mat;
	MyMatrixIdentity(mat);

	effect_managers = new EffectManagers(texdayo->getInstance(0));// �ŏ��̕�
	weapon_effect_manager = new WeaponEffectManager(effect_managers->getInstance(0));
	MyLuaGlueSingleton::getInstance()->setColEffectManagers(effect_managers);


	GUI::Init(hwnd,texdayo->getInstance(0),g->getScreenWidth(),g->getScreenHeight());
	
	rmap = new RMap();
	
	rmap->Init(hantei, mesh_instanceds);
	
//	RMapSetterExample(g, this, hantei, mesh_instanceds, demo->tex_loader, rmap);

//	sap = new ShudouArmPositioner(robodayo, robodayo->ap);
//	sap->Init(hwnd, texdayo->getInstance(0), L , g->getScreenWidth(),g->getScreenHeight());

	MYMATRIX jiken;

	MYVECTOR3 ppos(0,0,0);
	MyVec3TransformCoord(ppos,ppos,jiken);
	MyMatrixTranslation(jiken,ppos.float3.x,ppos.float3.y,0);//ppos.float3.z);

	
	MyMatrixRotationX(jiken,0.157);

	MYMATRIX world;
	MYMATRIX view;
	MYMATRIX proj = *g->getProj();;

	MYVECTOR3 from(25,25,12);
	MYVECTOR3 at(0,0,0);
	MYVECTOR3 up(0,0,1);
	MyMatrixIdentity(world);

	MyMatrixLookAtRH(view,from,at,up);

	
	texdayo->getInstance(0)->setViewProj(g,&view,&proj,&from,&at);
/*	effect_managers->getInstance(0)->loadFileFromLua(TASKTHREADS_UPDATEMAINRENDER,"resrc/script/effect/EFFECT_bakuhatu.lua");
	effect_managers->getInstance(0)->loadFileFromLua(TASKTHREADS_UPDATEMAINRENDER,"resrc/script/effect/EFFECT_boosterhi.lua");
	effect_managers->getInstance(0)->loadFileFromLua(TASKTHREADS_UPDATEMAINRENDER,"resrc/script/effect/EFFECT_boostertaiki.lua");
	effect_managers->getInstance(0)->loadFileFromLua(TASKTHREADS_UPDATEMAINRENDER, "resrc/script/effect/EFFECT_bakuhatu_weaponrifle.lua");
	effect_managers->getInstance(0)->loadFileFromLua(TASKTHREADS_UPDATEMAINRENDER, "resrc/script/effect/EFFECT_bakuhatu_weaponbazooka.lua");
	effect_managers->getInstance(0)->loadFileFromLua(TASKTHREADS_UPDATEMAINRENDER, "resrc/script/effect/EFFECT_bakuhatu_weaponlaserrifle.lua");
	effect_managers->getInstance(0)->loadFileFromLua(TASKTHREADS_UPDATEMAINRENDER, "resrc/script/effect/EFFECT_bakuhatu_weaponpulsegun.lua");
*/
	WeaponEffect::Init(weapon_effect_manager);

	effect_suuji = new EffectSuuji(TASKTHREADS_UPDATEMAINRENDER,effect_managers->getInstance(0));

	unsigned long work[TASK_WORK_SIZE];
	memset(work,0, sizeof(work));
	work[0] = (unsigned long)g_for_task_threads[TASKTHREADS_UPDATEANIMEFRAMENADO];

	task_threads[TASKTHREADS_UPDATEANIMEFRAMENADO]->make(CALCCOMBINEDTCB,mesh_instanceds,work,0x0000FFFF);
	
	
	
	
	memset(work,0, sizeof(work));
	work[1] = (unsigned long)g_for_task_threads[TASKTHREADS_UPDATEPOSBUTUKARI];
	work[0] = (unsigned long)task_threads[TASKTHREADS_UPDATEPOSBUTUKARI];
	//work[2] = (unsigned long)(&umesh_units);
	task_threads[TASKTHREADS_UPDATEPOSBUTUKARI]->make(BUTUKARIPOSTCB,hantei,work,0x0000FFFF);


	memset(work,0, sizeof(work));
	work[1] = (unsigned long)g_for_task_threads[TASKTHREADS_AIDECISION];
	work[0] = (unsigned long)task_threads[TASKTHREADS_AIDECISION];
	work[2] = (unsigned long)mesh_instanceds;

	task_threads[TASKTHREADS_AIDECISION]->make(LOADMESHTCB,L,work,0x0000FFFF);

	
	memset(work,0,sizeof(work));
	renderTCB = task_threads[TASKTHREADS_UPDATEMAINRENDER]->make(RENDERTCB,this,work,0x0000FFFF);
	task_threads[TASKTHREADS_AIDECISION]->make(MessageDispatcherTCB, NULL, work, 0x0000FFFF);
	
	
//	SceneGarage* sg = new SceneGarage(g, hantei,texdayo->getInstance(0), texdayo->getInstance(1), demo->tex_loader);

	

	//Game_SCENE* gs = new Game_SCENE(g,hantei,texdayo->getInstance(0), texdayo->getInstance(1), demo->tex_loader);
//	this->setScene(sg);

	return true;
}
void Game::Del() {

	

	
	/*
	vector<Scene*>::iterator scene_it = scenes.begin();
	while (scene_it != scenes.end()) {
		Scene* s = *scene_it;
		if (s) {
		s->leave();
		delete s;
		s = 0;
		}
		scene_it++;
	}
	scenes.clear();
	*/
	
	if (renderTCB) {
		KTROBO::mylog::writelog(KTROBO::INFO, "start del rendertcb");
		task_threads[TASKTHREADS_UPDATEMAINRENDER]->kill(renderTCB);
		Sleep(100);
		KTROBO::mylog::writelog(KTROBO::INFO, "end del rendertcb");
	}
	// �V�[���͕ʂ̏ꏊ�Ńf�X�g���N�g���Ăԁ@�Ƃ����Ă����������ׂăf�X�g���N�g���邱�Ƃɂ���
	int sizz = scenes.size();

	KTROBO::mylog::writelog(KTROBO::INFO, "\nscene del %d size\n", sizz);

	while(sizz) {
		this->removeScene();
		sizz--;
	}
	Scene::Del();

	KTROBO::mylog::writelog(KTROBO::INFO, "scene deleted");



	for (int i=0;i<TASKTHREAD_NUM;i++) {
		if (task_threads[i]) {
		task_threads[i]->deleteTaskWithoutLock();
		}
	}
	Sleep(1000);

	for (int i=0;i<TASKTHREAD_NUM;i++) {
		if (task_threads[i]) {
			KTROBO::mylog::writelog(KTROBO::INFO, "wait for %d",i);
		task_threads[i]->waitForTaskEnd();
		KTROBO::mylog::writelog(KTROBO::INFO,"wait end %d",i);
		}
	}
	
	if (task_threads[TASKTHREADS_UPDATEMAINRENDER]) {
	//	task_threads[TASKTHREADS_UPDATEMAINRENDER]->deleteTaskWithoutLock();
	//	Sleep(1000);
		delete task_threads[TASKTHREADS_UPDATEMAINRENDER];
		task_threads[TASKTHREADS_UPDATEMAINRENDER] = 0;
	}
	KTROBO::mylog::writelog(KTROBO::INFO, "deleted task threads");

	/*
	if (task_threads[TASKTHREADS_AIDECISION]) {
	//	task_threads[TASKTHREADS_AIDECISION]->deleteTask();
		delete task_threads[TASKTHREADS_AIDECISION];
		task_threads[TASKTHREADS_AIDECISION] = 0;
	}
	if(g_for_task_threads[TASKTHREADS_AIDECISION]) {
		g_for_task_threads[TASKTHREADS_AIDECISION]->Release();
		delete g_for_task_threads[TASKTHREADS_AIDECISION];
		g_for_task_threads[TASKTHREADS_AIDECISION] = 0;
	}


	if (task_threads[TASKTHREADS_LOADDESTRUCT]) {
	//	task_threads[TASKTHREADS_LOADDESTRUCT]->deleteTask();
		delete task_threads[TASKTHREADS_LOADDESTRUCT];
		task_threads[TASKTHREADS_LOADDESTRUCT] = 0;
	}
	if(g_for_task_threads[TASKTHREADS_LOADDESTRUCT]) {
		g_for_task_threads[TASKTHREADS_LOADDESTRUCT]->Release();
		delete g_for_task_threads[TASKTHREADS_LOADDESTRUCT];
		g_for_task_threads[TASKTHREADS_LOADDESTRUCT] = 0;
	}
	*/
	
	

	



	// ���Ԃ�ς��Ȃ����Ɓ@cs �Ɓ@�^�X�N�̊ԂɈˑ��֌W������
	for (int i = 0 ; i <TASKTHREAD_NUM; i++) {
		if (i != TASKTHREADS_UPDATEMAINRENDER) {
		if (task_threads[i]) {
	//		task_threads[i]->deleteTask();
			delete task_threads[i];
			task_threads[i] = 0;
		}
		if(g_for_task_threads[i]) {
			g_for_task_threads[i]->Release();
			delete g_for_task_threads[i];
			g_for_task_threads[i] = 0;
		}
		}
	}

	Graphics::Del();
	Scene::Del();

#if defined(DEBUG) || defined(_DEBUG)
	ID3D11Debug* m_pD3dDebug;
	HRESULT hr = S_OK;//g->getDevice()->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&m_pD3dDebug));
	if( FAILED(hr))
	{
		if(g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER]) {
		g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER]->Release();
		delete g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER];
		g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER] = 0;
		 g = 0;
	}
	    
	} else {

		if(g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER]) {
		g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER]->Release();
		delete g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER];
		g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER] = 0;
		g = 0;
		}

		// �ڍו\��
//		hr = m_pD3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

	}
#else 
	if(g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER]) {
		g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER]->Release();
		delete g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER];
		g_for_task_threads[TASKTHREADS_UPDATEMAINRENDER] = 0;
		g = 0;
		}
#endif		

	
	

	// CS�Ń��b�N����
	CS::instance()->enter(CS_TASK_CS, "ai lock", 4);
		CS::instance()->enter(CS_TASK_CS, "load lock", 3);
		CS::instance()->enter(CS_TASK_CS, "render lock",2);
		CS::instance()->enter(CS_TASK_CS, "anime lock", 1);
		CS::instance()->enter(CS_TASK_CS, "atari lock", 0);
		CS::instance()->enter(CS_DEVICECON_CS, "device lock");
		CS::instance()->enter(CS_MESSAGE_CS, "message lock");
		CS::instance()->enter(CS_RENDERDATA_CS, "render lock");
/*
	if (te) {
		delete te;
		te = 0;
	}
*/

	if (messages) {
		delete messages;
		messages = 0;
	}

	Text::Del();
	
	if (lua_ets) {
		lua_ets->Del();
		delete lua_ets;
		lua_ets = 0;
	}

	if (L) {
		lua_close(L);
		L =0;
	}
	
	/*
	for (int i=0;i<TASKTHREAD_NUM;i++) {
		if (Ls[i]) {
		lua_close(Ls[i]);
		Ls[i] = 0;
		}
	}
	*/
	/*
	if (robodayo) {
		robodayo->release();
		delete robodayo;
		robodayo = 0;
	}

	if (roboaitedayo) {
		roboaitedayo->release();
		delete roboaitedayo;
		roboaitedayo = 0;
	}
	*/

	 if (cmeshs) {
		 delete cmeshs;
		 cmeshs = 0;
	 }

	 
	 if(cltf) {
		 delete cltf;
		 cltf= 0;
	 }

/*	 if (makers) {
		makers->Release();
		delete makers;
		makers = 0;
	}
	 if(ksgene) {
		ksgene->Del();
		delete ksgene;
		ksgene = 0;
	}
	*/
	 if (sap) {
		 sap->Del();
		 delete sap;
		 sap = 0;
	 }


	 WeaponEffect::Del();


	 if (effect_suuji) {
		 delete effect_suuji;
		 effect_suuji = 0;
	 }


	 if (effect_managers) {
		 delete effect_managers;
		 effect_managers = 0;
	 }
	 if (weapon_effect_manager) {
		 delete weapon_effect_manager;
		 weapon_effect_manager = 0 ;
	 }

	 if (texdayo) {
		 texdayo->setDeleteAll();
		texdayo->deletedayo();
		delete texdayo;
		texdayo = 0;
	}

	

	KTROBO::DebugTexts::instance()->Del();

	/*
	if (mytest_for_vt) {
		delete mytest_for_vt;
		mytest_for_vt = 0;
	}
	*/

	if (telop_texts) {
		telop_texts->Del();
		delete telop_texts;
		telop_texts = 0;
	}

	
	if (demo) {
		demo->Release();
		delete demo;
		demo = 0;
	}
	if (rmap) {
		rmap->Del();
		delete rmap;
		rmap = 0;
	}

	if (mesh_instanceds) {
		mesh_instanceds->Release();
		delete mesh_instanceds;
		mesh_instanceds = 0;
	}

// Graphics::del	

	MeshInstanceds::Del();

	MyTokenAnalyzer::Del();
	Mesh::Del();
	
	if (hantei) {
		delete hantei;
		hantei = 0;
	}


	AtariHantei::del();

	

	Texture::Del();
	

	/*
	if (g) {
		g->Release();
		delete g;
		g = 0;
	}
	*/
	
	
	if (c) {
		delete c;
		c = 0;
	}

	/*
	if (mesh) {
		delete mesh;
		mesh = 0;
	}

	if (mesh2) {
		delete mesh2;
		mesh2 = 0;
	}
	for (int i = 0 ; i <= 10 ; i++) {
		if (mesh3[i]) {
		delete mesh3[i];
		mesh3[i] = 0;
		}
	}
	*/

	if (sound) {
		delete sound;
		sound = 0;
	}

	if (temp_input_shori) {
		delete temp_input_shori;
		temp_input_shori = 0;
	}
	/*
	vector<UMeshUnit*>::iterator itttt = umesh_units.begin();
	while(itttt != umesh_units.end()) {

		UMeshUnit* t = *itttt;
		delete t;
		t = 0;
		itttt++;
	}
	umesh_units.clear();
	*/
	/*
	if (sinai) {
	delete sinai;
	sinai = 0;
	}

	if (sfuru) {
		delete sfuru;
		sfuru = 0;
	}

	
	if (ss) {
		delete ss;
		ss = 0;
	}*/
	/*
	if (gg) {
		gg->Release();
		delete gg;
		gg = 0;
	}
	*/
	
	CS::instance()->leave(CS_RENDERDATA_CS, "render unlock");
	CS::instance()->leave(CS_MESSAGE_CS, "message lock");
	CS::instance()->leave(CS_DEVICECON_CS, "device lock");
	CS::instance()->leave(CS_TASK_CS, "atari lock",0);
	CS::instance()->leave(CS_TASK_CS, "anime lock",1);
	CS::instance()->leave(CS_TASK_CS, "render lock",2);
	CS::instance()->leave(CS_TASK_CS, "load lock", 3);
	CS::instance()->leave(CS_TASK_CS, "ai lock", 4);

	

	



}



void Game::startWatch() {
	QueryPerformanceCounter((LARGE_INTEGER*)&this->timeStart);
}

double Game::stopWatch() {
	QueryPerformanceCounter((LARGE_INTEGER*)&this->timeEnd);
	QueryPerformanceFrequency((LARGE_INTEGER*)&this->timeFreq);
	return (timeEnd.QuadPart - timeStart.QuadPart)/(double)timeFreq.QuadPart*1000;
}




void Game::Run() {

	//throw new GameError(KTROBO::FATAL_ERROR, "test");

	double millisecond = stopWatch();
	startWatch();
	WCHAR test[512];
	char test2[1024];
	memset(test2, 0, sizeof(1024));
	memset(test, 0, sizeof(WCHAR) * 512);


	if (millisecond > RENDERTIME_IGNORETIME) {
		CS::instance()->leave(CS_MAINTHREAD_CS, "leave main");
		//Sleep(1);
		millisecond = RENDERTIME_SETTIME;
		c->plus((float)millisecond);
		CS::instance()->enter(CS_MAINTHREAD_CS, "enter main");
	}
	else if (millisecond < RENDERTIME_SETTIME) {
		CS::instance()->leave(CS_MAINTHREAD_CS, "leave main");
		c->plus((float)millisecond);
		Sleep(DWORD(RENDERTIME_SETTIME - millisecond));
		millisecond = RENDERTIME_SETTIME;
		CS::instance()->enter(CS_MAINTHREAD_CS, "enter main");
	}
	else {
		CS::instance()->leave(CS_MAINTHREAD_CS, "leave main");
		c->plus((float)millisecond);
		//Sleep(1);
		CS::instance()->enter(CS_MAINTHREAD_CS, "enter main");
	}
	CS::instance()->enter(CS_SOUND_CS, "enter");
	if (sound) {
		sound->run();
	}
	CS::instance()->leave(CS_SOUND_CS, "leave");


	big_timestamp = c->getBigTimeStamp();

	dt = (float)millisecond;
	dmsecond = (float)millisecond;// c->getDMSecond();
	second = c->getSecond();

	frameTime = (float)millisecond;
	if (millisecond > 0) {
		//fps = (int)(1000 / (float)millisecond);
	}

	static int byouga_count = 0;
	static int byouga_count_second = 0;

	if (c->getSecond() != byouga_count_second) {
		byouga_count_second = c->getSecond();
		fps = byouga_count;
		byouga_count = 0;
	}
	byouga_count++;
	if (byouga_count >= (int)(1000 / (float)RENDERTIME_SETTIME)) {
		// �`�悵�Ȃ��Ń��^�[������
	//	return;
	}



	//demo->Render(g);
	float clearColor[4] = {
		0.3f,0.4f,0.8f,1.0f };
	CS::instance()->enter(CS_DEVICECON_CS, "test");
	
	if (telop_texts->isRenderFinished()) {
	//	telop_texts->readFile(g, "resrc/sample/KTROBO.txt", 30, 14, &MYVECTOR4(1, 1, 1, 1), 0.1);
	}
	else {
		telop_texts->plusTime(g, millisecond);
	}
	CS::instance()->leave(CS_DEVICECON_CS, "test");
	//demo->Render(g);

	static float frame = 0;
	static int frameint = 0;
	frame += millisecond / (float)RENDERTIME_SETTIME;
	timestamp = c->getTimeStamp();




	unsigned short animf[KTROBO_MESH_INSTANCED_BONE_MAX];
	unsigned short animl[KTROBO_MESH_INSTANCED_BONE_MAX];
	float animw[KTROBO_MESH_INSTANCED_BONE_MAX];

	/*
	if (frameint != (int)(frame*5)) {
		frameint = (int)(frame*5);
		if (frame >40) {
			frame = 0;
		}
	//frame = 30.001;
*/



	float testcc = frame / 60.00f;
	bool is_calc_anime = true;
	static float mae_testcc = 0;
	if (testcc - mae_testcc > 1 / 12.0f) {
		mae_testcc = testcc;
		is_calc_anime = true;

		//mesh->animate(testcc, true);
		//mesh2->animate(testcc, true);
		for (int i = 0; i <= 10; i++) {
			//	mesh3[i]->animate(testcc, true);
		}
	}
	else {
		is_calc_anime = false;
	}

	//}

	//frame = 30.001;

	MYMATRIX world;
	//	MYMATRIX view;
	MYMATRIX proj = *g->getProj();
	MyMatrixIdentity(world);
	MYVECTOR3 a(25, 25, 12);
	//	MYVECTOR3 a(0,10,40);
	MYVECTOR3 b(0, 0, 0);
	MYVECTOR3 up(0, 0, 1);
	//	MyMatrixLookAtRH(view, a, b, up);
	//	MyMatrixPerspectiveFovRH(proj, 1, g->getScreenWidth() / (float)g->getScreenHeight(), 1, 1000);


	MYMATRIX worldforg;










	MYMATRIX temp_world;
	MyMatrixTranslation(temp_world, 0, 0, 0);
	//	mesh_i->setWorld(&temp_world);
	//	mesh_instanceds->setViewProj(g, &view,&proj, &MYVECTOR4(1,1,-10,1));





	CS::instance()->enter(CS_DEVICECON_CS, "render game");

	CS::instance()->enter(CS_MESSAGE_CS, "render");




	MYMATRIX rotzmat;
	//MyMatrixRotationZ(rotzmat, temp_input_shori->testdayo);
	//	MyMatrixMultiply(view,rotzmat,view);
	MYVECTOR3 tesdt;
	tesdt = b - a;
	MyVec3TransformNormal(tesdt, tesdt, rotzmat);
	a = b - tesdt;
	//	MyMatrixLookAtRH(view, a, b, up);
	char bbuf[512];
	memset(bbuf, 0, 512);
//	sprintf_s(bbuf, "%d,%d,%d,%d", fps, byouga_count
//		, temp_input_shori->x, temp_input_shori->y);
//	WCHAR bbufdayo[512];
//	memset(bbufdayo, 0, sizeof(WCHAR) * 512);
	stringconverter scc;
	CS::instance()->enter(CS_RENDERDATA_CS, "render");
//	scc.charToWCHAR(bbuf, bbufdayo);
	CS::instance()->leave(CS_RENDERDATA_CS, "render");
//	te->changeText(bbufdayo, wcslen(bbufdayo));
	CS::instance()->leave(CS_MESSAGE_CS, "render");

	CS::instance()->leave(CS_DEVICECON_CS, "render game");

	memset(animf, 0, sizeof(animf));
	memset(animl, 0, sizeof(animl));
	memset(animw, 0, sizeof(animw));
	static int count = 0;
	count++;

	//int bsize = mesh2->Bones.size();

	//if (count % 2 ==0) {
	//for (int i=0;i<bsize; i++) {

	//	MeshBone* bone = mesh2->Bones[i];
	//	mesh2->calculateOffsetMatrixToGetMinMaxAndWeight(bone, frame, &animl[i], &animf[i], &animw[i]);
	//	animf[i] = floor(frame);////floor(frame);//count * 0.3;
	//	animl[i] =ceil(frame);//count * 0.3;
	//	animw[i] = animl[i]- frame;
		//animw[i] = 1;//1- animw[i];
	//}




	CS::instance()->enter(CS_DEVICECON_CS, "render game");





	ID3D11RenderTargetView* v = g->getRenderTargetView();
	g->getDeviceContext()->OMSetRenderTargets(1, &v, Mesh::pDepthStencilView);
	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());
	g->getDeviceContext()->ClearRenderTargetView(g->getRenderTargetView(), clearColor);
	g->getDeviceContext()->ClearDepthStencilView(Mesh::pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	KTROBO::DebugTexts::instance()->render(g);
	if (!telop_texts->isRenderFinished()) {
		telop_texts->render(g);
	}
	/*
	if (te) {
		te->render(g, 0xFFFF00FF, 10, 0, 30, 450, 40);
	}
	*/
	CS::instance()->leave(CS_DEVICECON_CS, "render game");

	for (int i = 0; i < TASKTHREAD_NUM; i++) {
		ID3D11CommandList* pd3dCommandList = 0;

		if (i == TASKTHREADS_UPDATEMAINRENDER) continue;
		//CS::instance()->leave(CS_DEVICECON_CS, "render game");
		CS::instance()->enter(CS_DEVICECON_CS, "un");

		HRESULT hr = S_OK;
		if (g_for_task_threads[i] && task_threads[i] && task_threads[i]->getIsExecTask()) {
			//Sleep(1000);
			hr = g_for_task_threads[i]->getDeviceContext()->FinishCommandList(FALSE, &pd3dCommandList);
		}
		CS::instance()->leave(CS_DEVICECON_CS, "un");
		//CS::instance()->enter(CS_DEVICECON_CS, "render game");
		if (FAILED(hr)) {
			throw new GameError(KTROBO::FATAL_ERROR, "failed in finishing list");
		}

		CS::instance()->enter(CS_DEVICECON_CS, "enter executelist");
		if (pd3dCommandList) {
			g->getDeviceContext()->ExecuteCommandList(pd3dCommandList, false);
			pd3dCommandList->Release();
			pd3dCommandList = 0;
		}
		CS::instance()->leave(CS_DEVICECON_CS, "leave executelist");
	}
	CS::instance()->enter(CS_DEVICECON_CS, "render game");
	v = g->getRenderTargetView();
	g->getDeviceContext()->OMSetRenderTargets(1, &v, Mesh::pDepthStencilView);
	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());

	static float f = 0;
	f = frame;
	while (f > 3000) {
		f = f - 3000;
	}



	MyMatrixRotationZ(worldforg, 0);//frame/600.00f);
//	MYMATRIX unkoko;
//	MyMatrixRotationY(unkoko,frame/10.00f);
//	MyMatrixMultiply(worldforg,worldforg,unkoko);
	for (int i = 0; i < 11; i++) {

		MyMatrixScaling(world, 0.6, 0.6, 0.6);
		MyMatrixTranslation(world, 0, 0, 0);
		MyMatrixMultiply(world, world, worldforg);
		if (i == 1) {
			MYMATRIX tt;
			//		MyMatrixTranslation(tt,0,-4,0);
			//		MyMatrixScaling(world,2,2,2);
			//		MyMatrixMultiply(world,world,tt);
			//		MyMatrixMultiply(world, world,worldforg);
		}
		//		mesh3[i]->draw(g, &world, &view, &proj);

	}
	//	mesh3[7]->draw(g,&world,&view,&proj);
	//	mesh3[8]->draw(g,&world,&view,&proj);
	//	mesh3[0]->draw(g, &world, &view, &proj);
	//	mesh3[10]->draw(g, &world, &view, &proj);

	//	mesh->draw(g, &world,&view,&proj);
	static float ccc;
	ccc = frame / 60.00f;// * RENDERTIME_SETTIME;
	int tesss = sizeof(MESH_VERTEX);
	char bbf[512];
	sprintf_s(bbf, 512, "%f,%d", ccc, tesss);
	WCHAR bbc[512];
	bbc[511] = 0;
	stringconverter ssf;
	ssf.charToWCHAR(bbf, bbc);
	//DebugTexts::instance()->setText(g,wcslen(bbc), bbc);


	MyMatrixScaling(world, 0.6, 0.6, 0.6);
	MyMatrixTranslation(world, 0, 0, 0);
	MyMatrixMultiply(world, world, worldforg);
	//mesh2->draw(g, &world, &view, &proj);
	RAY testdray;
	CS::instance()->enter(CS_MESSAGE_CS, "test");
//	testdray.org = temp_input_shori->ray.org;
//	testdray.dir = temp_input_shori->ray.dir;
//	MyVec3Normalize(testdray.dir, testdray.dir);
//	testdray.dir = testdray.dir * 50;
	/*
	int sb = mesh2->Bones.size();
	bool is_ma=false;
	for (int i=0;i<sb;i++) {
	MeshBone* vv = mesh2->Bones[i];

		if (vv->houkatuobbuse) {

			OBB henkanobb = vv->houkatuobb;
			MYMATRIX henkanmat;
			MYMATRIX idenmat;
			MyMatrixIdentity(idenmat);
			//MyMatrixIdentity(world);
			MyMatrixMultiply(henkanmat,vv->combined_matrix,world);
			MyVec3TransformCoord(henkanobb.c,henkanobb.c,henkanmat);
			MyVec3TransformNormal(henkanobb.u[0],henkanobb.u[0],henkanmat);

			henkanobb.e.float3.x = henkanobb.e.float3.x * MyVec3Length(henkanobb.u[0]);
			MyVec3Normalize(henkanobb.u[0],henkanobb.u[0]);



			MyVec3TransformNormal(henkanobb.u[1],henkanobb.u[1],henkanmat);
			henkanobb.e.float3.y = henkanobb.e.float3.y * MyVec3Length(henkanobb.u[1]);
			MyVec3Normalize(henkanobb.u[1],henkanobb.u[1]);
			MyVec3TransformNormal(henkanobb.u[2],henkanobb.u[2],henkanmat);
			henkanobb.e.float3.z = henkanobb.e.float3.z * MyVec3Length(henkanobb.u[2]);
			MyVec3Normalize(henkanobb.u[2],henkanobb.u[2]);

			if (TestSegmentOBB(&testdray,&henkanobb)) {
				WCHAR buf[512];
				memset(buf,0,sizeof(WCHAR)*512);
				stringconverter sc;
				sc.charToWCHAR(vv->bone_name,buf);
				//DebugTexts::instance()->setText(g,wcslen(buf),buf);
			//	g->drawOBB(g,0xFFFFFFFF,&idenmat,&view,&proj,&henkanobb);
				is_ma = true;
			}	else {
			//	g->drawOBB(g,0xFFFF2222,&idenmat,&view,&proj,&henkanobb);
			}

		}

	}
	*/
	CS::instance()->leave(CS_MESSAGE_CS, "testt");
	CS::instance()->enter(CS_MESSAGE_CS, "test");
//	temp_input_shori->setMAT(&world, &view, &proj);
	CS::instance()->leave(CS_MESSAGE_CS, "testt");
	//	texdayo->getInstance(0)->setViewProj(g,&view,&proj,&a,&b);
	//	texdayo->getInstance(1)->setViewProj(g,&view, &proj,&a,&b);

	MYVECTOR3 testr(0, 0, -10);
	MYMATRIX rotX;
	static float ff = 0;
	ff += 0.01f;
	MyMatrixRotationX(rotX, 0);
	MyVec3TransformNormal(testr, testr, rotX);
	//	texdayo->getInstance(0)->setRenderBillBoardPos(0,&rotX);

	CS::instance()->leave(CS_DEVICECON_CS, "render game");
	/*
	static Mesh* mm = mesh;
	if (ff > 3.0f) {
		CS::instance()->enter(CS_DEVICECON_CS, "lock");
		for (int i=0;i<100;i++) {
	//	mesh_instanceds->changeInstanceMeshSkeleton(mesh_is[i]->getInstanceIndex(), mm,mm);
		}
		CS::instance()->leave(CS_DEVICECON_CS, "unlock");
		ff = 0;
		if (mm == mesh ) {
			mm = mesh2;
		} else {
			mm = mesh;
		}

	}*/

	CS::instance()->enter(CS_DEVICECON_CS, "render game");

	mesh_instanceds->setViewProj(g, &view, &proj, &MYVECTOR4(testr.float3.x, testr.float3.y, testr.float3.z, 1));
	/*
	OBB testobb = mesh2->houkatuobb;

	MYMATRIX idenmat;
	MyMatrixIdentity(idenmat);

	if (is_ma) {
//		g->drawRAY(g,0xFF000000,&idenmat,&view,&proj,50,&testdray);
	} else {
	//	g->drawRAY(g,0xFFFFFFFF,&idenmat,&view,&proj,50,&testdray);
	}

	if (TestSegmentOBB(&temp_input_shori->ray,&testobb)) {
//		g->drawOBB(g,0xFF000000,&idenmat,&view,&proj,&testobb);
	} else {
//		g->drawOBB(g,0xFF888888,&idenmat,&view,&proj,&testobb);
	}

	*/


	//g->drawRAY(g,0xFFFF0000,&idenmat,&view,&proj,50,&temp_input_shori->ray);
	RAY tempray;

	tempray.org = MYVECTOR3(50, 50, 0);
	tempray.dir = MYVECTOR3(-50, -50, frame / 60.0f);





	OBB kousi;
	kousi.e.float3.x = 30;
	kousi.e.float3.y = 30;
	kousi.e.float3.z = 1;
	kousi.c = MYVECTOR3(0, 0, 0);
	for (int i = -10; i < 10; i++) {
		for (int k = -10; k < 10; k++) {
			kousi.c.float3.x = 30 * i;
			kousi.c.float3.y = 30 * k;
			kousi.c.float3.z = 0;
			//		g->drawOBB(g,0xFFFFFFFF,&idenmat,&view,&proj,&kousi);
		}
	}


	MYMATRIX idenmat;
	MyMatrixIdentity(idenmat);

	//if (TestSegmentOBB(&tempray, &mesh2->houkatuobb)) {
	//	g->drawRAY(g,0xFFFF00FF,&idenmat,&view,&proj,50/*MyVec3Length(tempray.dir)*/,&tempray);
	//	g->drawOBB(g,0xFFFFFF00,&idenmat,&view,&proj,&mesh2->houkatuobb);
	//} else {
	//	g->drawRAY(g,0xFF000000,&idenmat,&view,&proj,50/*MyVec3Length(tempray.dir)*/,&tempray);
	//}

//	mesh->draw(g, &world, &view, &proj);
	//texdayo->getInstance(0)->setViewProj(g,&view,&proj,&a,&b);
	//texdayo->setRenderBillBoardPos(0,&world);

	/*
	MyMatrixTranslation(world,4,0,0);
	mesh2->draw(g,&world,&view,&proj);

	MyMatrixTranslation(world,0,0,4);
	mesh2->draw(g,&world,&view,&proj);
	*/

	//float cc[] = {1.0f,1.0f,0.3f,1.0f};
	//mesh_instanceds->loadAnimeMatrixBasisToTexture(g);


	MYVECTOR3 p1(0, 10, 10 + 30);
	MYVECTOR3 p2(10, frame, 10 + 30);
	MYVECTOR3 p3(0, 0, -40);

	p3.float3.z += frame * 3;//;

	MYVECTOR3 q1(100, 0, 10);
	MYVECTOR3 q2(0, 100, 10);
	MYVECTOR3 q3(-100, -100, 10);

	TRIANGLEDAYO t1;
	TRIANGLEDAYO t2;
	t1.x = p1;
	t1.y = p2;
	t1.z = p3;
	t2.x = q1;
	t2.y = q2;
	t2.z = q3;

	MYVECTOR3 k_a;
	int t = hanteiTRIANGLEDAYO(&t1, &t2, &k_a);

	//MyMatrixIdentity(world);
	RAY ra;
	ra.org = k_a - MYVECTOR3(0, 0, 1);
	ra.dir = MYVECTOR3(0, 0, 1);//k_a;

	if (t == YATTEYARU_TRIANGLE_KOUSA) {
		//	g->drawRAY(g,0xFF00FFFF,&world,&view,&proj,100,&ra);
		//	g->drawTriangle(g,0xFF00FFFF,&world,&view,&proj,&t1.x,&t1.y,&t1.z);
		//	g->drawTriangle(g,0xFF00FFFF,&world,&view,&proj,&t2.x,&t2.y,&t2.z);
	}
	else {
		//	g->drawTriangle(g,0xFFFFFFFF,&world,&view,&proj,&t1.x,&t1.y,&t1.z);
		//	g->drawTriangle(g,0xFFFFFFFF,&world,&view,&proj,&t2.x,&t2.y,&t2.z);
	}
	CS::instance()->enter(CS_RENDERDATA_CS, "render game");

	{
		static float bui = 0;
		bui = bui - 4.98*0.0001f * millisecond / 1000 * millisecond / 1000;
		static float bb = 0;
		bb = bb + bui * millisecond;
		/*UMeshUnit* umesh_unit = umesh_units[0];
		umesh_unit->setDT(millisecond/1000);
		umesh_unit->setV(&MYVECTOR3(0,0,bui));

	umesh_unit->setROTXYZ(0,0,0);
	umesh_unit->setSCALEXYZ(1,1,1);*/
	//umesh_unit->setXYZ(0,0,0);//testcc,testcc,bb);//5-testcc/*-testcc*/);

		float frame_a = testcc;
		bool com = true;

		//	umesh_unit->calcAnimeFrame(1,&frame_a,&com);
		//	umesh_unit->calcJyusinAndR();
		bool calcom = true;
		//umesh_unit->draw(g,&view,&proj,1, &testcc,&calcom,true, false/*is_calc_anime*/, false,true);
	}


	{
		static float bui = 0;
		bui = bui - 4.98*0.0001f * millisecond / 1000 * millisecond / 1000;
		static float bb = 0;
		bb = bb + bui * millisecond;
		//		UMeshUnit* umesh_unit = umesh_units[1];
				//umesh_unit->setDT(millisecond/1000);
				//umesh_unit->setV(&MYVECTOR3(0,0,bui));

		//	umesh_unit->setROTXYZ(0,0,0);
		//	umesh_unit->setSCALEXYZ(1,1,1);
		//	umesh_unit->setXYZ(testcc,testcc,bb);//5-testcc/*-testcc*/);
			//float frame_a=testcc;
		//	bool com=true;

		//	umesh_unit->calcAnimeFrame(1,&frame_a,&com);
		float frame_a = testcc;
		bool com = true;
		//	umesh_unit->setSCALEXYZ(1,1,1);
		//	umesh_unit->setXYZ(0,3,-5);//5-testcc/*-testcc*/);
			//umesh_unit->calcAnimeFrame(1,&frame_a,&com);

			//sinai->umesh_unit->setSCALEXYZ(3,3,3);
		MYVECTOR3 oo;
		MYVECTOR3 moto(0, 1.9, -0.20);
		oo = oo + moto;
//		temp_input_shori->getPos(&oo);
		//	sfuru->setKAMAE(temp_input_shori->getRotY(),0,&oo);
		//	sinai->umesh_unit->setROTXYZ(temp_input_shori->getRotY(),0,0);
		//	sinai->umesh_unit->setXYZ(oo.float3.x,oo.float3.y,oo.float3.z);//10*sin(testcc),-4,10*cos(testcc));
		//	sinai->umesh_unit->calcAnimeFrame(1,&frame_a,&com);
		//	sinai->umesh_unit->calcJyusinAndR();
		//	MYVECTOR3 p = sinai->getHidaritePos();
		OBB b;
		MYVECTOR3 p = MYVECTOR3(-0.78, -3.02, 6.15);
		b.c = p;
		b.e = MYVECTOR3(0.3, 0.3, 0.3);
	//	g->drawOBBFill(g, 0xFFFF0000FF, &idenmat, &view, &proj, &b);

		/*	 p = sinai->getMigitePos();*/
		p = MYVECTOR3(-1.56, -0.36, 6.4);
		b.c = p;
		b.e = MYVECTOR3(0.3, 0.3, 0.3);
//		g->drawOBBFill(g, 0xFFFF00FFFF, &idenmat, &view, &proj, &b);

		//umesh_unit->calcJyusinAndR();
		//ss->nigiraseru(g,&view, &proj);




	//	float t = this->ksgene->getNigiruhitoAnimeTemp();

	//	this->makers->getInstance(0)->update(testcc,sfuru);
	//	sfuru->men_furaseru(g,&view,&proj,testcc,t);
	//	SinaiNigiru sn(sinai, umesh_unit);
	//	sn.setDefaultAnimeFrameAll(testcc);
	//	sn.nigiraseru(g,&view,&proj);

		bool calcom = true;

		//umesh_unit->draw(g,&view,&proj,1, &testcc,&calcom,true, false/*is_calc_anime*/, false,true);

	}

	//rmap->update();

	CS::instance()->leave(CS_RENDERDATA_CS, "render game");
	CS::instance()->leave(CS_DEVICECON_CS, "device game");
	lua_ets->getInstance(0)->doLoop(this->c->getTimeStamp());
	CS::instance()->enter(CS_DEVICECON_CS, "device game");

	static float tester = 0;
	tester += 0.1f;

	//	UMeshUnit* umesh_unit = umesh_units[2+30];
		//umesh_unit->setXYZ(0,0,205);
		//umesh_unit->setROTXYZ(0,0,0);//1.57+tester/1000.0f,tester/100.00f,0);

		//umesh_unit->calcJyusinAndR();
		//mesh_is[2+30]->setWorld(&umesh_unit->world);
	for (int i = 0; i < 75; i++) {
		{
			//		UMeshUnit* umesh_unit = umesh_units[i];
			//	umesh_unit->setROTXYZ(0,0,0);//testcc/3.00f);
			//	umesh_unit->setSCALEXYZ(2,2,1);
			//	umesh_unit->setXYZ(0,0,0);
			//	umesh_unit->calcJyusinAndR();
			bool calcom = true;
			//	umesh_unit->calcJyusinAndR();
			//	umesh_unit->draw(g,&view,&proj,1, &testcc,&calcom,true, false/*is_calc_anime*/, false,true);
		}
	}
	/*
	{
		UMeshUnit* um2 = umesh_units[0];
		UMeshUnit* um1 = umesh_units[1];
		TRIANGLEDAYO tri1;
		for (int inde =0;inde < um1->meshs[0]->mesh->FaceCount;inde++) {

			if (!um1->meshs[0]->indexs) continue;
			if (!um1->meshs[0]->vertexs) continue;
			UINT inde1 = um1->meshs[0]->indexs[3*inde];
			UINT inde2 = um1->meshs[0]->indexs[3*inde+1];
			UINT inde3 = um1->meshs[0]->indexs[3*inde+2];
			MESH_VERTEX* v1 = &um1->meshs[0]->vertexs[inde1];
			MESH_VERTEX* v2 = &um1->meshs[0]->vertexs[inde2];
			MESH_VERTEX* v3 = &um1->meshs[0]->vertexs[inde3];
			tri1.x = v1->pos;
			tri1.y = v2->pos;
			tri1.z = v3->pos;

			MyVec3TransformCoord(tri1.x,tri1.x,um1->world);
			MyVec3TransformCoord(tri1.y,tri1.y,um1->world);
			MyVec3TransformCoord(tri1.z,tri1.z,um1->world);
			for (int h=0;h<KTROBO_MESH_BONE_MAX;h++) {
				if (um2->meshs[0]->is_bone_obbs_use[h] && hanteiTRIANGLETOOBB(&tri1,&um2->meshs[0]->bone_obbs[h])) {
					DebugTexts::instance()->setText(g,3,L"ata");
				}
			}
		}
	}
	*/

	/*
	{
		UMeshUnit* umesh_unit = umesh_units[2];
	umesh_unit->setROTXYZ(0,0.5,0.5);
	umesh_unit->setSCALEXYZ(1,1,1);
	umesh_unit->setXYZ(testcc,-testcc,0);
	umesh_unit->calcJyusinAndR();
	bool calcom = true;
	umesh_unit->draw(g,&view,&proj,1, &testcc,&calcom,false, false, true,true);
	}*/
	/*
	for(int i=0;i<1;i++)
	{
	UMeshUnit* umesh_unit = umesh_units[3+i];
//	umesh_unit->setROTXYZ(0,0.5,0.5);
//	umesh_unit->setSCALEXYZ(3,3,0.2);
//	umesh_unit->setXYZ(testcc,-testcc/2,0);
	//umesh_unit->calcJyusinAndR();
	bool calcom = true;
	umesh_unit->draw(g,&view,&proj,1, &testcc,&calcom,true, false, false,true);
	}
	*/
	//	mesh_instanceds->calcCombinedMatrixToTexture(g);
	//	mesh_instanceds->loadColorToTexture(g);


	//	mesh_instanceds->loadAnimeMatrixBasisToTexture(g);
	//	mesh_instanceds->loadMatrixLocalToTexture(g);
	//	mesh_instanceds->calcCombinedMatrixToTexture(g);
		//mesh_instanceds->loadColorToTexture(g);

		//watches_for_keisoku.startWatch(0);
	////	mesh_instanceds->render(g);
	mesh_instanceds->render(g);



	//g->getDeviceContext()->ClearRenderTargetView(mesh_instanceds->anime_matrix_basis_texture->target_view, cc);
	//demo->Render(g, mesh_instanceds->combined_matrix_texture);



	CS::instance()->enter(CS_RENDERDATA_CS, "ee");


	demo->Render(g, mesh_instanceds->anime_matrix_basis_texture);
	//	demo->Render(g, mesh_instanceds->matrix_local_texture);
		/*
		sinai->draw(g,&view,&proj);
		*/
	MyMatrixTranslation(world, 3, 0, 1);





	static float h = 0.0f;
	h += 0.001f;
	MYMATRIX wor;
	MyMatrixIdentity(wor);
	//	MyMatrixRotationZ(wor,h);
	MYMATRIX r1;
	MyMatrixTranslation(r1, 0, 0, h / 100.0f);
	if (h > 100) {
		h = 1;
	}
	CS::instance()->leave(CS_RENDERDATA_CS, "ee");
	static int coun = 0;
	coun++;


	unsigned int color = 0xFF00FF00 + ((int)(coun) % 256);
	/*	texdayo->setRenderTexColor(0,0xFFFFFF00+(coun)%256);
		texdayo->setRenderBillBoardColor(0,color);*/





		//	inputtext->render(g);
		//	but->render(g);

	MYMATRIX te;
	MyMatrixTranslation(world, f / 200.0f, f / 200.0f, 0);
	//MyMatrixRotationZ(te,f);
//	MyMatrixMultiply(world,te,world);
	//texdayo->getInstance(0)->setRenderBillBoardIsRender(0,false);

	//texdayo->getInstance(0)->setRenderBillBoardPos(0, &world);
	//watches_for_keisoku.stopWatch(0);
	bool is_sleep = false;

	/*
	{
		WCHAR buff[512];
		char buf[128];
		char str[128];
		memset(buf,0,128);

		for (int i=0;i<10;i++) {
		memset(str,0,128);
		GamenGARAGE_partsParam::getSuutiChara((int)(watches_for_keisoku.times[i]*100),str);
		strcat_s(buf,str);
		strcat_s(buf,",");
	//	GamenGARAGE_partsParam::getSuutiChara((int)(sizeof(AtariUnitAns)),str);
	//	strcat_s(buf,str);
		}
		strcat_s(buf,"ac:");
		GamenGARAGE_partsParam::getSuutiChara((int)hantei->getAtattaCount(), str);
		strcat_s(buf,str);
		strcat_s(buf,",");
		GamenGARAGE_partsParam::getSuutiChara((int)hantei->icounter.counter, str);
		strcat_s(buf,str);
		strcat_s(buf,",");

		GamenGARAGE_partsParam::getSuutiChara((int)robodayo->atarihan->y, str);
		strcat_s(buf,str);
		strcat_s(buf,",");
		GamenGARAGE_partsParam::getSuutiChara((int)robodayo->atarihan->z, str);
		strcat_s(buf,str);
		stringconverter sc;
		sc.charToWCHAR(buf,buff);

	//	DebugTexts::instance()->setText(g,wcslen(buff),buff);
		if (watches_for_keisoku.times[5] > 10) {
			mylog::writelog(KTROBO::INFO, buf);
			mylog::writelog(KTROBO::INFO, "\n\n");
		}
	}
	*/

	watches_for_keisoku.startWatch(1);
	texdayo->createIndexBuffer(g);
	texdayo->updateIndexBuffer(g);
	texdayo->sendinfoToVertexTexture(g);
	watches_for_keisoku.stopWatch(1);


	/*

	if(TestOBBOBB(&hantei->umesh_units[0]->meshs[0]->bone_obbs[0],&hantei->umesh_units[1]->meshs[0]->bone_obbs[0])) {
		MYMATRIX iden;
		MyMatrixTranslation(iden,0,0,5);
	//	g->drawOBB(g,0xFF0000FF,&iden,&view,&proj,&umesh_units[0]->meshs[0]->bone_obbs[0]);
	}
	*/

	CS::instance()->enter(CS_RENDERDATA_CS, "unko");
	/*
		watches_for_keisoku.startWatch(2);
		watches_for_keisoku.startWatch(5);
		hantei->maecalcdayo(g);
		watches_for_keisoku.stopWatch(5);
		watches_for_keisoku.startWatch(6);
		hantei->ataristart();
		hantei->calc(g);
		watches_for_keisoku.stopWatch(6);
		watches_for_keisoku.startWatch(7);
		hantei->copyKekkaForBufferCopy(g);
		watches_for_keisoku.stopWatch(7);
		watches_for_keisoku.startWatch(8);
		hantei->calc(g);
		watches_for_keisoku.stopWatch(8);
		watches_for_keisoku.startWatch(9);
		hantei->copyKekkaForBufferCopy(g);
		watches_for_keisoku.stopWatch(9);
		watches_for_keisoku.stopWatch(2);
	*/
	//	CS::instance()->leave(CS_RENDERDATA_CS, "unko");
	//	CS::instance()->enter(CS_RENDERDATA_CS,"unko");
	/*
		hantei->maecalcdayo(g);
		hantei->ataristart();
		hantei->calc(g);
		hantei->copyKekkaForBufferCopy(g);
		hantei->calc(g);
		hantei->copyKekkaForBufferCopy(g);
	*/

	effect_suuji->update(&lookfromtoat);
	CS::instance()->leave(CS_RENDERDATA_CS, "unko");
	effect_managers->update(frameTime, (int)frame);
	weapon_effect_manager->update(frameTime);
	OBB rec;
	rec.c = MYVECTOR3(0, 0, 0);
	//g->drawOBBFill(g, 0xFFFF0000, &idenmat, &view, g->getProj(), &rec);

	OBB re;
	re.c = MYVECTOR3(10, 10, 10);

	//g->drawOBBFill(g, 0xFFFFFF00, &idenmat, &view, g->getProj(), &re);


	CS::instance()->enter(CS_RENDERDATA_CS, "unko");
	watches_for_keisoku.startWatch(3);
	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());


	CS::instance()->leave(CS_RENDERDATA_CS, "unko");

	mesh_instanceds->render(g);
	CS::instance()->enter(CS_RENDERDATA_CS, "unko");
	if (robodayo) {
		robodayo->byouga(g, &view, &proj);
	}
	if (roboaitedayo) {
	roboaitedayo->byouga(g, &view, &proj);
	}
	static int robodayo_boostereffect_count = 0;
	robodayo_boostereffect_count++;
	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());


	if (robodayo && robodayo->atarihan) {
		//	robodayo->atarihan->setXYZ(robodayo->atarihan->x + temp_input_shori->testdayo, robodayo->atarihan->y, robodayo->atarihan->z);
		//robodayo->atarishori(g, &view, hantei, frameTime, (int)frame);
		//	robodayo->fireUpdate(g,demo->tex_loader, &view, hantei, frameTime, (int)frame, this, 	texdayo->getInstance(0)); 
		//robodayo->atarihan->setV(&MYVECTOR3(temp_input_shori->testdayo/100.0f,0, robodayo->atarihan->v.float3.z));
		//robodayo->atarihan->calcJyusinAndR();

		if (robodayo_boostereffect_count % 2 == 0) {
			robodayo->boosterEffect(this, g, frameTime, timestamp);
		}

		if (sap) {
			CS::instance()->leave(CS_RENDERDATA_CS, "unko");
			bool t = sap->update();
			CS::instance()->enter(CS_RENDERDATA_CS, "unko");
			robodayo->aphelper->setNoCalcYet(false);
		}
		//sap->update();
	}


	if (roboaitedayo && roboaitedayo->atarihan) {
		//	robodayo->atarihan->setXYZ(robodayo->atarihan->x + temp_input_shori->testdayo, robodayo->atarihan->y, robodayo->atarihan->z);
		//robodayo->atarishori(g, &view, hantei, frameTime, (int)frame);
		//roboaitedayo->fireUpdate(g,demo->tex_loader, &view, hantei, frameTime, (int)frame, this, 	texdayo->getInstance(0)); 
		//robodayo->atarihan->setV(&MYVECTOR3(temp_input_shori->testdayo/100.0f,0, robodayo->atarihan->v.float3.z));
		//roboaitedayo->atarihan->calcJyusinAndR();

		if (robodayo_boostereffect_count % 2 == 0) {
			roboaitedayo->boosterEffect(this, g, frameTime, timestamp);
		}


		/*
		if (sap->update()) {
		robodayo->aphelper->setNoCalcYet(false);
		}
		*/
		//sap->update();
	}


	//if (hantei->canGetAns()) {
		if (robodayo && robodayo->atarihan) {
				//	robodayo->atarishori(g, &view, hantei, frameTime, (int)frame);
//					robodayo->calcAim(g, &view, frameTime, (int)frame);
					robodayo->aim(g, &view);
				}

				if (roboaitedayo->atarihan) {
			//		roboaitedayo->atarishori(g, &view, hantei, frameTime, (int)frame);
		//			roboaitedayo->atariAim(g, &view, frameTime, (int)frame);
				}
		hantei->drawKekka(g,&this->view,g->getProj());
		
	//}
	watches_for_keisoku.stopWatch(3);

	rmap->byougaHojyo(g, &this->view, g->getProj());


	CS::instance()->leave(CS_RENDERDATA_CS, "unko");

//	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());
/*	CS::instance()->enter(CS_RENDERDATA_CS, "unko");
	if (hantei->canGetAns()) {
		hantei->drawKekka(g,&view,&proj);
	}
	CS::instance()->leave(CS_RENDERDATA_CS, "unko");
*/	
	g->getDeviceContext()->OMSetRenderTargets(1, &v, Mesh::pDepthStencilView);
	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());
	//g->getDeviceContext()->ClearRenderTargetView(g->getRenderTargetView(),clearColor);
	g->getDeviceContext()->ClearDepthStencilView(Mesh::pDepthStencilView,  D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1.0f, 0 );
	//CS::instance()->leave(CS_RENDERDATA_CS, "unko");
	if (robodayo) {
		robodayo->byougaRay(g, &view, &proj);
	}	
	//CS::instance()->enter(CS_RENDERDATA_CS, "unko");
	
	watches_for_keisoku.startWatch(4);
	texdayo->getInstance(0)->renderBill(g);
	texdayo->deletedayo();
	texdayo->getInstance(0)->renderTex(g);
	

	g->getDeviceContext()->OMSetRenderTargets(1, &v, Mesh::pDepthStencilView);
	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());
	//g->getDeviceContext()->ClearRenderTargetView(g->getRenderTargetView(),clearColor);
	g->getDeviceContext()->ClearDepthStencilView(Mesh::pDepthStencilView,  D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1.0f, 0 );
	
	texdayo->getInstance(0)->renderText(g);

	int siz = scenes.size();
	if (siz) {
		Scene* now_scene = scenes.back();
		for (int i=0;i<siz;i++) {
			Scene* s = scenes[i];
			if (now_scene != s) {
				s->mainrender(false);
			}
		}
		now_scene->mainrender(true);
	}
	


	g->getDeviceContext()->OMSetRenderTargets(1, &v, Mesh::pDepthStencilView);
	g->getDeviceContext()->RSSetViewports(1, g->getViewPort());
	//g->getDeviceContext()->ClearRenderTargetView(g->getRenderTargetView(),clearColor);
	g->getDeviceContext()->ClearDepthStencilView(Mesh::pDepthStencilView,  D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1.0f, 0 );
	

	

	texdayo->render(g,1);
	watches_for_keisoku.stopWatch(4);
	/*
	CS::instance()->enter(CS_RENDERDATA_CS, "unko");
	gg->byouga(g,NULL,frameTime, (int)frame);

	CS::instance()->leave(CS_RENDERDATA_CS, "unko");
	*/
	g->getSwapChain()->Present(0,0);


	static int s = 0;
	if (c->getSecond() != s) {
	}
	CS::instance()->leave(CS_DEVICECON_CS, "render game");
	/*if (is_sleep) {
		Sleep(3000);
	}*/

}