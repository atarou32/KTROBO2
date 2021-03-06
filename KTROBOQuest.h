#ifndef KTROBOQUEST_H
#define KTROBOQUEST_H

/*
 クエストクラスの概要

 KTROBOではクエストがある。
 クエストには配信期間がある。
 クエストの受注上限が設定されている。
 クエストには受けることができる場所（NPC)がある。
 クエストの状態には　受諾状態、達成状態、非受諾状態、未受諾状態がある。
 クエストが達成された状態または受諾状態から破棄することができる。
 クエストが達成された状態から報酬を受けることができる。報酬を受けたあと、非受諾状態になる。
 非受諾状態と未受諾状態の違いは未受諾では受諾できるが、非受諾状態では一定時間過ぎないと受諾できない。

 クエストの種類
 １．デイリークエスト
 ２．ウィークリークエスト
 ３．通常クエスト

 クエストの達成時受諾制限
 １．一週間ごと
 ２．一回のみ
 ３．三日ごと
 ４．一日ごと

 クエストの達成種類
 １．アイテムの納品
 ２．特定のNPCから話を聞く
 ３．特定の敵を撃破する
 ４．特定のミッションのクリア
 ５．特定の状態を満たす

 クエストの属性
 
 クエストID
 クエスト名
 クエスト説明（開発者用のデータ説明など）
 クエスト概要（ゲーム画面で表示するコメント）
 クエスト受注期間（クエストを受注できる期間）
 クエスト達成種類タイプ（クエストの種類の１から５）
 クエスト達成条件ID（より具体的な達成条件を識別する）
 クエスト報酬ID（具体的な報酬を識別）
 クエスト受注場所（NPCID）
 クエスト受注時NPCセリフ
 クエスト達成時NPCセリフ

 デイリークエストの実装
 
 デイリークエストの仕様
 毎日２４：００にクエストのラインナップが変更される（１４日周期で元に戻る）
 達成されていないまた報酬を受けていない達成されたデイリークエストは毎日２４：００自動破棄される
 同じクエストでも破棄されることに注意

 ウィークリークエストの実装

 ウィークリークエストの仕様
 毎日曜日２４：００にクエストのラインナップが変更される（４回で元に戻る）
 達成されていないまた報酬を受けていない達成されたデイリークエストは毎日曜日２４：００自動破棄される
 同じクエストをラインナップにおいても破棄されることに注意

*/

#pragma once
#include "KTRoboScene.h"
#include "KTRoboInput.h"
#include "KTRoboAtari.h"
#include "KTRoboTexture.h"
#include "KTRoboEntity.h"
#include "KTRoboCameraWork.h"
#include "KTRoboBullet.h"

class KTROBOQuest
{
public:
	KTROBOQuest(void);
	~KTROBOQuest(void);
};


namespace KTROBO {



	class QUEST_SCENE : public Scene, public INPUTSHORICLASS {

	private:
		Graphics* g;
		AtariHantei* hantei;
		Texture* tex;
		Texture* tex2;
		MyTextureLoader* loader;
		Text* exampletext;
	
		Clock butukari_clock;
		ClockWatches watches;
		bool quest_loaded;
		bool quest_started;
		EntityManager* e_manager;
		TikeiMap* tikei;
		CameraWork* camera_work;
		BulletController* bullet_c;
		float dtime;
	public:
		QUEST_SCENE(Graphics* g, AtariHantei* hantei, Texture* tex, Texture* tex2, MyTextureLoader* loader);
		~QUEST_SCENE(void);

	public:
		void mainrenderIMPL(bool is_focused, Graphics* g, Game* game);
		void renderhojyoIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
		void aiIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
		void posbutukariIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);
		void loaddestructIMPL(Task* task, TCB* thisTCB, Graphics* g, Game* game);

		void enter();
		void leave();
		bool handleMessage(int msg, void* data, DWORD time);
	};







}


#endif