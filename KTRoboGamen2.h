#ifndef KTROBO_GAMEN2_H
#define KTROBO_GAMEN2_H

#pragma once
#include <vector>
#include "MyButukari.h"
#include <string>
#include <map>
#include "KTRoboTexture.h"

using namespace std;

namespace KTROBO {

	class Gamen2_part {
	private:
		int pid;
		static unsigned int part_id;
		bool has_touroku;

		MYRECT rect;
		MYRECT nowRect;
		MYRECT destRect;
		float speed;
		float dt;
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


		virtual void setRect(MYRECT* re) {
			rect = *re;
			nowRect = *re;
			destRect = *re;
		}
		virtual void moveTo(MYRECT* dest_re, float time) {};
		virtual bool moveLoop(float dt) { return false; }; // �����I�������true��Ԃ�
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

		}; // �J�[�\�������킳�ꂽ�@�܂��́@�}�E�X�ō��킳�ꂽ
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

		}; // �J�[�\�������킳�ꂽ��ԂőI���{�^���������ꂽ�@�܂��̓}�E�X�őI�����Ă�����̂������ꂽ
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
		}; // �J�[�\�����O�ꂽ

		void touroku() { has_touroku = true; };
		bool getTouroku() { return has_touroku; };
		Gamen2_part() {
			pid = part_id; part_id++; has_touroku = false; is_focused = false; has_is_focused_changed = false;/* color = 0xFFFFFFFF;*/
		};
		~Gamen2_part() {};
		virtual char* getHelpString() {
			return "default help string";
		}

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
		Gamen2_partGroup(int scene_id,int all_index, int group_index) : Gamen2_part() {
			this->scene_id = scene_id;
			this->group_index = group_index;
			this->all_index = all_index;
			is_use = true;
		};
		~Gamen2_partGroup() {};
		bool getIsUse(){ return is_use; }; // �O����CS_LOAD_CS�����b�N���邱��

		void cleardayo(Texture* tex, Texture* tex2); // tex��text�̓��e�Ȃǂ�lightdelete���� vector���N���A����
	private:
		bool is_use;
		int scene_id;
		int all_index;
		int group_index;
		vector<MYRECT> now_rects; // ����Ƀ}�E�X�̓����̃t�H�[�J�X����ɂ��g�p����
		vector<MYRECT> dest_rects;
		vector<MYRECT> rects;
		vector<GAMEN2_PARTGROUPSTRUCT> tex_or_textindexs;

		// rects ����с@textindexs help_text �Ɋւ��Ắ@�O�����烍�[�h�����\��������̂Ŏg���Ƃ��� CS_LOAD_CS �̃��b�N��������

		string help_text;



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
		vector<vector<int>*> cursor_group;
		int cursor_x;
		vector<int> cursor_ys;
		string lua_filename;
	public:
		const char* getLuaFilename() { return lua_filename.c_str(); };

		int getCursorX() { return cursor_x; };
		int getCursorY() { return cursor_ys[cursor_x]; };
		void setCursorX(int cursor_x);
		void setCursorY(int cursor_y);
		int getCursorGroup();
		int makeKoCursorGroup(); // cursor_group ��vector<int*>* ������
		void deletedayo(); // �f�X�g���N�^���ĂԑO��deletedayo���Ă�

		void setGroupOnlyRenderGroup(int group_index);
		void setGroupGroup(int group_index, int cursor_x);

	};

	class Gamen2
	{
	private:
		vector<Gamen2_part*> cpp_parts; // �O��������ꍞ�܂ꂽ��ʃp�[�c cpp_parts �Ɋւ��Ắ@�f�X�g���N�^�Ȃǂ��Ă΂Ȃ�
		vector<Gamen2_partGroup*> grouped_parts; // ��ʂQ�̊֐�������ꂽ�@��ʃp�[�c
		vector<Gamen2_part*> all_parts;
		vector<bool> all_parts_is_work;
		vector<bool> all_parts_is_work_mae;

		vector<Gamen2_Sonotoki*> sonotokis; // lua_file ��������
		map<pair<int,int>, int> sonotokis_map;
		map<pair<int, int>, int> cpp_parts_map; // scene_id, parts_DEF kara all_parts noindex

		void pauseWork(); // moveTo�̓����͎��s����邪�@�N���b�N��Z���N�g�����Ă��������Ȃ��悤�ɂ��� 
						  // selected���ꂽ�Ƃ��Ɏ��s�����
						  // pause����߂�̂�gamen_sonotoki::enter �Őݒ肵�Ȃ�����邩��
	public:
		//void backFromPauseWork(); // pause���Ă񂾎���is_work�ɖ߂�lua_file_when_selected �̍Ō�ɌĂ�

		void setCPPParts(Gamen2_part* parts, int scene_id, int parts_DEF);
		int getCPPPartsIndex(int scene_id, int parts_DEF);

		void makeSonotoki(int scene_id, int gamen_id, char* lua_filename); // rock load
		void setSonotokiMakeKo(int scene_id, int gamen_id); // rock load
		void setSonotokiSetGroupOnlyRenderGroup(int scene_id, int gamen_id, int group_index); // rock load
		void setSonotokiSetGroupGroup(int scene_id, int gamen_id, int group_index, int cursor_x); // rock load
		int getSonotokiCursorGroup(int scene_id, int gamen_id); // rock load
		void setSonotokiNowSonotoki(int scene_id, int gamen_id); // rock load lua_filename���Ă΂��

		int getNowSonotokiCursorGroup();
		Gamen2_Sonotoki* getNowSonotoki(); // cursor_group���ĂԂ��߂Ɏg���̂Ł@�O����CS_LOAD_CS�����b�N����



		int makePartsGroup(int scene_id, char* help_text, char* lua_file_when_focused, char* lua_file_when_selected); 
		// grouip_index��Ԃ� has_is_focused_changed�̂Ƃ�����focused�̃��[�A�t�@�C�����Ă΂��

		int setPartsGroupSetText(int group_index, bool is_tex2, int text_index); // group ����index��Ԃ�
		int setPartsGroupSetTex(int group_index, bool is_tex2, int tex_index); // group ����index��Ԃ�
		int getPartsGroupIsText(int group_index, int index); // �Y����index�̗v�f��text�ł��邩
		int getPartsGroupIsTex2(int group_index, int index); // �Y����index�̗v�f��tex�Q���g���Ă��邩
		void setPartsGroupMoveTo(int group_index,int x, int y, int width, int height, float time); // load lock
		bool getPartsGroupMoveFinished(int group_index); // load lock
		void setPartsGroupTenmetu(int group_index, float dt, float tenmetu_kankaku);
		bool getPartsGroupTenmetuFinished(int group_index);




		Gamen2();
		~Gamen2();
	};

}


#endif