#include "KTRoboSceneGarage2.h"
#include "KTRoboGame.h"

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

void Garage2::render(Graphics* g,Texture* tex,Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {
	if (robog) {
		robog->render(g, tex2,view, proj);










	}

}

bool SceneGarage2::handleMessage(int msg, void* data, DWORD time) {

	return false;
}



Garage2::Garage2() : Loadable2() {
	robog = 0;
	gtex_g = 0;

	
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
	

};

void Garage2::atoload(Graphics* g, AtariHantei* hantei, Texture* tex1, Texture* tex2, MyTextureLoader* loader) {
	if (!robog->getTouroku()) {
		robog->load(g, tex1,tex2, loader, hantei);
		robog->robo->atarihan->setXYZ(0, 0, 0);
		robog->touroku();
		return;
	}

	



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

	setLoaded();
	
}


MyRobo_Garage2::MyRobo_Garage2() : Loadable2(), Garage2_part() {
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
	int tex_index2  = tex1->getTexture("resrc/img/garage2.png");
	tex_haikei = tex1->getRenderTex(tex_index2, 0xFFFFFFFF, 50, 350, 400, 400, 18, 390, 1, 1);
	tex1->setRenderTexColor(tex_haikei, 0xAAAAAAFF);
	int tex_index = tex2->getTexture("resrc/img/garage2.png");
//	tex_waku = tex2->getRenderTex(tex_index, 0xFFFFFFFF, 0, 0, 238, 46, 0, 0, 238, 46);
	tex_waku = tex2->getRenderTex(tex_index, 0xFFFFFFFF, 50,350,400,400, 245, 0, 200, 200);
	setLoaded();
}

void Garage2Tex_Garage2::render(Graphics* g, Texture* tex2, MYMATRIX* view, MYMATRIX* proj) {

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

}

void Garage2Tex_Garage2::load(Graphics* g, Texture* tex1, Texture* tex2, MyTextureLoader* loader, AtariHantei* hantei) {
	int tex_index2 = tex2->getTexture("resrc/img/garage2.png");
	texe = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, 10, 10, 236, 46, 0, 0, 236, 46);
	MYRECT re;
	re.left = 10;
	re.right = 236+10;
	re.top = 10;
	re.bottom = 46+10;
	this->setRect(&re);
	tex_waku = tex2->getRenderTex(tex_index2, 0xFFFFFFFF, 10, 10, g->getScreenWidth()-20, g->getScreenHeight()-20 , 245, 0, 200, 200);

}





unsigned int Garage2_part::part_id = 0;