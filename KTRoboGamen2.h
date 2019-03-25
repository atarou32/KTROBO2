#ifndef KTROBO_GAMEN2_H
#define KTROBO_GAMEN2_H

#pragma once
#include <vector>
#include "MyButukari.h"
#include <string>
#include <map>
#include "MyDefine.h"
#include "lua.hpp"
#include "tolua_glue/MyLuaGlueMakeCommon.h"


using namespace std;

namespace KTROBO {


#define KTROBO_GAMEN2_LUA_FILENAME_NO_LUA "NO_LUA"
#define KTROBO_GAMEN2_SCENE_ID_GARAGE 1
#define KTROBO_GARAGE2_IMG_PATH "resrc/img/garage2.png"
#define KTROBO_GARAGE2_INIT_LUA_FILEPATH "resrc/script/garage/init_garage.lua"

	class Texture;

	interface IGamen2 {
public:
		
		TO_LUA virtual int getCPPPartsIndex(int scene_id, int parts_DEF)=0;
		TO_LUA virtual void makeSonotoki(int scene_id, int gamen_id, char* lua_filename)=0;
		TO_LUA virtual void setSonotokiMakeKo(int scene_id, int gamen_id)=0;
		TO_LUA virtual void setSonotokiSetGroupOnlyRenderGroup(int scene_id, int gamen_id, int all_index)=0;
		TO_LUA virtual void setSonotokiSetGroupGroup(int scene_id, int gamen_id, int all_index, int cursor_x)=0;
		TO_LUA virtual int getSonotokiCursorGroup(int scene_id, int gamen_id)=0;
		TO_LUA virtual void setSonotokiNowSonotoki(int scene_id, int gamen_id)=0;
		TO_LUA virtual int getNowSonotokiCursorGroup()=0;
		TO_LUA virtual int makePartsGroup(int scene_id, char* help_text, char* lua_file_when_focused, char* lua_file_when_selected, IN_ int* rect)=0;
		TO_LUA virtual int getPartsGroupgetAllIndexFromGroupIndex(int group_index)=0;
		TO_LUA virtual int setPartsGroupSetText(int group_index, bool is_tex2, int text_index, IN_ int* rect)=0;
		TO_LUA virtual int setPartsGroupSetTex(int group_index, bool is_tex2, int tex_index, IN_ int* rect)=0;
		TO_LUA virtual bool getPartsGroupIsText(int group_index, int index)=0;
		TO_LUA virtual bool getPartsGroupIsTex2(int group_index, int index)=0;
		TO_LUA virtual void setPartsGroupMoveTo(int group_index, int x, int y, int width, int height, float time)=0;
		TO_LUA virtual bool getPartsGroupMoveFinished(int group_index)=0;
		TO_LUA virtual void setPartsGroupTenmetu(int group_index, float dt, float tenmetu_kankaku)=0;
		TO_LUA virtual bool getPartsGroupTenmetuFinished(int group_index)=0;

	};













	class Gamen2_part {
	private:
		int pid;
		static unsigned int part_id;
		bool has_touroku;
	protected:
		MYRECT rect;
		MYRECT nowRect;
		MYRECT destRect;
		float speedx;
		float speedy;
		float dt;
		float time;
		float tenmetu_dt;
		float tenmetu_time;
		float tenmetu_kankaku;
	protected:
		bool is_focused;
		bool has_is_focused_changed;
		bool is_work;
		bool is_render;
	public:

		virtual void setIsWorkAndRender(bool t) {
			is_work = t;
			is_render = t;
		}

		virtual void setIsWork(bool t) {
			is_work = t;
		}
		bool getIsRender() { return is_render; };
		bool getIsWork() { return is_work; };

		const MYRECT const * getRect() { return &nowRect; }
		virtual void setRect(MYRECT* re) {
			rect = *re;
			nowRect = *re;
			destRect = *re;
		}
		virtual void moveTo(MYRECT* dest_re, float time) {};
		virtual bool moveLoop(float dt) { return false; }; // 動き終わったらtrueを返す
		virtual void tenmetu(float time,float tenmetu_kankaku) {};
		virtual bool tenmetuLoop(float dt) { return false; };
		virtual bool focused(int x, int y) {
			if (!is_work) return false;
			unsigned int bu = getButukariStatusPoint(x, y, &nowRect);
			if (bu & BUTUKARIPOINT_IN) {
				if (is_focused) {
					return true;
				}
				else {
					has_is_focused_changed = true;
					is_focused = true;
					focusExe();
					return true;
				}

			}
			if (is_focused) {
				has_is_focused_changed = true;
				is_focused = false;
			}
			return false;

		}; // カーソルがあわされた　または　マウスで合わされた
		virtual bool selected(int x, int y) {
			if (!is_work) return false;
			if (is_focused) {
				unsigned int bu = getButukariStatusPoint(x, y, &nowRect);
				if (bu & BUTUKARIPOINT_IN) {
					selectExe();
					return true;
				}
			}
			return false;

		}; // カーソルがあわされた状態で選択ボタンが押された　またはマウスで選択しているものが押された
		virtual void unfocused(int x, int y) {
			if (!is_work) return;
			if (is_focused) {
				unsigned int bu = getButukariStatusPoint(x, y, &nowRect);
				if (bu & BUTUKARIPOINT_IN) {
				}
				else {
					is_focused = false;
					has_is_focused_changed = true;
				}

			}
		}; // カーソルが外れた

		void touroku() { has_touroku = true; };
		bool getTouroku() { return has_touroku; };
		Gamen2_part() {
			pid = part_id; part_id++; has_touroku = false; is_focused = false; has_is_focused_changed = false;
			time = 0;
			speedx=0;
			speedy=0;
			dt=0;
			tenmetu_dt=0;
			tenmetu_time=0;
			tenmetu_kankaku=0;
	
			is_work=true;
			is_render=true;
			
			
			
			/* color = 0xFFFFFFFF;*/
		};
		~Gamen2_part() {};
		virtual const char* getHelpString() {
			return "default help string";
		}

		virtual const char* getFocusedLua() {
			return KTROBO_GAMEN2_LUA_FILENAME_NO_LUA;
		};
		virtual const char* getSelectedLua() {
			return KTROBO_GAMEN2_LUA_FILENAME_NO_LUA;
		};

		

		virtual void focusExe() {};
		virtual void selectExe() {};
	};


	struct GAMEN2_PARTGROUPSTRUCT {
		int index;
		bool is_text;
		bool is_tex2;
	};

	class Gamen2_partGroup : public Gamen2_part {
	public:
		Gamen2_partGroup(int scene_id,int all_index, int group_index, Texture* tex, Texture* tex2) : Gamen2_part() {
			this->scene_id = scene_id;
			this->group_index = group_index;
			this->all_index = all_index;
			is_use = true;
			help_text = KTROBO_GAMEN2_LUA_FILENAME_NO_LUA;
			selected_lua = KTROBO_GAMEN2_LUA_FILENAME_NO_LUA;
			focused_lua = KTROBO_GAMEN2_LUA_FILENAME_NO_LUA;
			this->tex = tex;
			this->tex2 = tex2;

		};
		~Gamen2_partGroup() {};
		bool getIsUse(){ return is_use; }; // 外部でCS_LOAD_CSをロックすること
		void setString(char* help_text, char* focused_lua, char* selected_lua);
		void cleardayo(Texture* tex, Texture* tex2); // texやtextの内容などをlightdeleteする vectorもクリアする
		int setText(int text_index, bool is_tex2,IN_ int* recto);
		int setTex(int tex_index, bool is_tex2, IN_ int* recto);
		int getAllIndex() { return all_index; };
	private:
		Texture* tex;
		Texture* tex2;
		bool is_use;
		int scene_id;
		int all_index;
		int group_index;
		vector<MYRECT> now_rects; // これにマウスの動きのフォーカス判定にも使用する
		vector<MYRECT> dest_rects;
		vector<MYRECT> rects;
		vector<GAMEN2_PARTGROUPSTRUCT> tex_or_textindexs;

		// rects および　textindexs help_text に関しては　外部からロードされる可能性があるので使うときは CS_LOAD_CS のロックをかける

		string help_text;
		string focused_lua;
		string selected_lua;
	public:
		const char* getHelpString() {
			return help_text.c_str();
		};
		const char* getFocusedLua() {
			return focused_lua.c_str();
		};
		const char* getSelectedLua() {
			return selected_lua.c_str();
		};
		virtual void setIsWorkAndRender(bool t);
		virtual void setIsWork(bool t);
		virtual bool selected(int x, int y);
		virtual bool focused(int x, int y);
		virtual void unfocused(int x, int y);
		virtual void moveTo(MYRECT* dest_re, float time);
		virtual bool moveLoop(float dt); // 動き終わったらtrueを返す
		virtual void tenmetu(float time, float tenmetu_kankaku);
		virtual bool tenmetuLoop(float dt);

		vector<GAMEN2_PARTGROUPSTRUCT>* getTexOrTextIndexs() { return &tex_or_textindexs; };
	};

	class Gamen2_Sonotoki {
	public:
		Gamen2_Sonotoki(int scene_id, int gamen_id, char* lua_filename) {
			this->scene_id = scene_id;
			this->gamen_id = gamen_id;
			cursor_x = 0;
			this->lua_filename = lua_filename;
		};
		~Gamen2_Sonotoki() {};
	private:
		int scene_id;
		int gamen_id;
		vector<int> not_cursor_but_render_group;
		vector<vector<int>*> cursor_group; // sonotokiで保管しているint は　group_indexではなくて　all_indexであることに注意
		int cursor_x;
		vector<int> cursor_ys;
		string lua_filename;
	public:
		string getLuaFilename() { return lua_filename; };

		int getCursorX() { return cursor_x; };
		int getCursorY();// { return cursor_ys[cursor_x]; };
		void setCursorX(int cursor_x);
		void setCursorY(int cursor_y);
		int getCursorGroup();
		void makeKoCursorGroup(); // cursor_group にvector<int*>* を入れる
		void deletedayo(); // デストラクタを呼ぶ前にdeletedayoを呼ぶ

		void setGroupOnlyRenderGroup(int group_index);
		void setGroupGroup(int group_index, int cursor_x);
		void setIsWorkAndRenderWhenNowSonotoki(vector<Gamen2_part*>* all_parts);
	};

	class Gamen2 : public IGamen2
	{
	private:
		vector<Gamen2_part*> cpp_parts; // 外部から入れ込まれた画面パーツ cpp_parts に関しては　デストラクタなどを呼ばない
		vector<Gamen2_partGroup*> grouped_parts; // 画面２の関数から作られた　画面パーツ
		vector<Gamen2_part*> all_parts;
	
		vector<bool> all_parts_is_work_mae;

		vector<Gamen2_Sonotoki*> sonotokis; // lua_file から作られる
		map<pair<int,int>, int> sonotokis_map;
		map<pair<int, int>, int> cpp_parts_map; // scene_id, parts_DEF kara cpp_parts noindex
		Gamen2_Sonotoki* now_sonotoki;

		void pauseWork(); // moveToの動きは実行されるが　クリックやセレクトをしても反応しないようにする 
						  // selectedされたときに実行される
						  // pauseから戻るのはgamen_sonotoki::enter で設定しなおされるから
	public:
		//void backFromPauseWork(); // pauseを呼んだ時のis_workに戻るlua_file_when_selected の最後に呼ぶ

		void setCPPParts(Gamen2_part* parts, int scene_id, int parts_DEF);
		int getCPPPartsIndex(int scene_id, int parts_DEF);

		void makeSonotoki(int scene_id, int gamen_id, char* lua_filename); // rock load
		void setSonotokiMakeKo(int scene_id, int gamen_id); // rock load
		void setSonotokiSetGroupOnlyRenderGroup(int scene_id, int gamen_id, int all_index); // rock load
		void setSonotokiSetGroupGroup(int scene_id, int gamen_id, int all_index, int cursor_x); // rock load
		int getSonotokiCursorGroup(int scene_id, int gamen_id); // rock load
		void setSonotokiNowSonotoki(int scene_id, int gamen_id); // rock load lua_filenameが呼ばれる

		int getNowSonotokiCursorGroup();
		Gamen2_Sonotoki* getNowSonotoki(); // cursor_groupを呼ぶために使うので　外部でCS_LOAD_CSをロックする
		Gamen2_part* getGamen2Part(int all_index);


		int makePartsGroup(int scene_id, char* help_text, char* lua_file_when_focused, char* lua_file_when_selected, IN_ int* rect); 
		// grouip_indexを返す has_is_focused_changedのときだけfocusedのルーアファイルが呼ばれる
		int getPartsGroupgetAllIndexFromGroupIndex(int group_index);

		int setPartsGroupSetText(int group_index, bool is_tex2, int text_index, IN_ int* rect); // group 内のindexを返す left right top bottom の順番
		int setPartsGroupSetTex(int group_index, bool is_tex2, int tex_index, IN_ int* rect); // group 内のindexを返す
		bool getPartsGroupIsText(int group_index, int index); // 該当のindexの要素がtextであるか
		bool getPartsGroupIsTex2(int group_index, int index); // 該当のindexの要素がtex２を使っているか
		void setPartsGroupMoveTo(int group_index,int x, int y, int width, int height, float time); // load lock
		bool getPartsGroupMoveFinished(int group_index); // load lock
		void setPartsGroupTenmetu(int group_index, float dt, float tenmetu_kankaku);
		bool getPartsGroupTenmetuFinished(int group_index);
	//	void setPartsGroupSetRect(int group_index, int index, IN_ int* rect);

		void Del();
		void loopForMoveToAndTenmetu(float dt);


		Gamen2(Texture* tex, Texture* tex2);
		~Gamen2();
	private:
		Texture* tex;
		Texture* tex2;
	};


	class Gamen2s{
	private:
		Texture* tex;
		Texture* tex2;
	public:
		Gamen2s(Texture* tex, Texture* tex2) {
			inst = 0;
			this->tex = tex;
			this->tex2 = tex2;
		};
		~Gamen2s() {
			if (inst) {
				inst->Del();
				delete inst;
				inst = 0;
			}
		};

		
		Gamen2* inst;

	public:
		Gamen2* getInstance(int index) {
			if (inst) {
				return inst;
			}
			inst = new Gamen2(tex,tex2);
			return inst;
		};
		Gamen2* getInterface(int index) {
			if (inst) {
				return inst;

			}
			inst = new Gamen2(tex,tex2);
			return inst;
		};
		int makeInst() {
			// 実際のmakeはluaに渡す前にすべてやってしまうこと
			if (inst) {
			}
			else {
				inst = new Gamen2(tex,tex2);
			}
			return 0;
		};

	};
}


#endif