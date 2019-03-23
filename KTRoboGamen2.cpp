#include "KTRoboGamen2.h"
#include "KTROBOGameError.h"
#include "KTRoboLog.h"
#include "KTRoboCS.h"

using namespace KTROBO;

Gamen2::Gamen2()
{
}


Gamen2::~Gamen2()
{
}



void Gamen2_Sonotoki::setGroupOnlyRenderGroup(int group_index) {
	not_cursor_but_render_group.push_back(group_index);
}

void Gamen2_Sonotoki::setGroupGroup(int group_index, int cursor_x) {
	int cg_size = cursor_group.size();
	if (cg_size <= 0) {
		throw new GameError(FATAL_ERROR, "no cursorgroup please call makekocursorgroup\n");
	}
	if (cursor_x < 0) {
		throw new GameError(FATAL_ERROR, "bad cursor_x in setgroupgroup\n");
	}
	int cx = cursor_x % cg_size;
	cursor_group[cx]->push_back(group_index);
}


int Gamen2_Sonotoki::makeKoCursorGroup() {
	// cursor_group にvector<int*>* を入れる
	vector<int>* tte = new vector<int>();
	cursor_group.push_back(tte);
	cursor_ys.push_back(0);

}
void Gamen2_Sonotoki::deletedayo() {
	CS::instance()->enter(CS_LOAD_CS, "gamen2sonotoki");
	CS::instance()->enter(CS_MESSAGE_CS, "gamen2sonotoki");

	int cg_size = cursor_group.size();
	for (int i = 0; i < cg_size; i++) {
		if (cursor_group[i]) {
			cursor_group[i]->clear();
			delete cursor_group[i];
			cursor_group[i] = 0;
		}
	}
	cursor_group.clear();
	CS::instance()->leave(CS_MESSAGE_CS, "gamen2sonotoki");
	CS::instance()->leave(CS_LOAD_CS, "gamen2sonotoki");

}
int Gamen2_Sonotoki::getCursorY() { 
	
	int cg_size = cursor_group.size();
	if (cg_size <= 0) {
		mylog::writelog(KTROBO::WARNING, "no cursor group\n");
		return 0;
	}
	
	return cursor_ys[cursor_x % cg_size]; 

}

void Gamen2_Sonotoki::setCursorY(int cursor_y) {
	int cg_size = cursor_group.size();
	if (cg_size <= 0) {
		mylog::writelog(KTROBO::WARNING, "no cursor group\n");
		return;
	}
	int dd = cursor_x % cg_size;
	cursor_ys[dd] = cursor_y;
}

void Gamen2_Sonotoki::setCursorX(int cursor_x) {
	int cg_size = cursor_group.size();
	if (cg_size <= 0) {
		mylog::writelog(KTROBO::WARNING, "no cursor group\n");
		return;
	}

	if (this->cursor_x > cursor_x) {
		if (cursor_x < 0) {
			while (cursor_x < 0) {
				cursor_x = cursor_x + cg_size;
			}
			this->cursor_x = cursor_x % cg_size;
			return;
		}

	}
	else if (this->cursor_x < cursor_x) {
		if (cg_size <= cursor_x) {
			while (cursor_x >= cg_size) {
				cursor_x = cursor_x - cg_size;
			}
			this->cursor_x = cursor_x % cg_size;
		}
	}

}
int Gamen2_Sonotoki::getCursorGroup() {

	int cg_size = cursor_group.size();
	if (cg_size <= 0) {
		throw new GameError(KTROBO::FATAL_ERROR, "no cursor group");
	}
	if ((cursor_x <= 0) || (cursor_x >= cg_size)) {
		throw new GameError(KTROBO::FATAL_ERROR, "bad cursor_x");
	}
	vector<int>* gg = cursor_group[cursor_x];
	int gg_size = gg->size();
	if (gg_size <= 0) {
		throw new GameError(KTROBO::FATAL_ERROR, "no cursor group");
	}
	// cursor_y に関してはエラーをはかずにゲットする
	int tt = cursor_ys[cursor_x] % gg_size;
	return (*gg)[tt];
}


void Gamen2_partGroup::cleardayo(Texture* tex, Texture* tex2) {
	// texやtextの内容などをlightdeleteする vectorもクリアする

	CS::instance()->enter(CS_LOAD_CS, "gamen2partgroup");
	CS::instance()->enter(CS_MESSAGE_CS, "gamen2partgroup");
	vector<GAMEN2_PARTGROUPSTRUCT>::iterator it =  tex_or_textindexs.begin();
	while (it != tex_or_textindexs.end()) {
		GAMEN2_PARTGROUPSTRUCT* ii = &(*it);
		if (ii->is_text) {
			if (ii->is_tex2) {
				tex2->lightdeleteRenderText(ii->index);
			}
			else {
				tex->lightdeleteRenderText(ii->index);
			}
		}
		else {
			if (ii->is_tex2) {
				tex2->lightdeleteRenderTex(ii->index);
			}
			else {
				tex->lightdeleteRenderTex(ii->index);
			}
		}



		it++;
	}

	now_rects.clear();
	dest_rects.clear();
	rects.clear();

	tex_or_textindexs.clear();


	is_use = false;
	CS::instance()->leave(CS_MESSAGE_CS, "gamen2partgroup");
	CS::instance()->leave(CS_LOAD_CS, "gamen2partgroup");

}



void Gamen2::pauseWork() {
	// moveToの動きは実行されるが　クリックやセレクトをしても反応しないようにする 
					  // selectedされたときに実行される
					  // pauseから戻るのはgamen_sonotoki::enter で設定しなおされるから
}


void Gamen2::setCPPParts(Gamen2_part* parts, int scene_id, int parts_DEF) {

}

int Gamen2::getCPPPartsIndex(int scene_id, int parts_DEF) {

}

void Gamen2::makeSonotoki(int scene_id, int gamen_id, char* lua_filename) {
	// rock load
}

void Gamen2::setSonotokiMakeKo(int scene_id, int gamen_id) {
	// rock load


}
void Gamen2::setSonotokiSetGroupOnlyRenderGroup(int scene_id, int gamen_id, int group_index) {
	// rock load


}

void Gamen2::setSonotokiSetGroupGroup(int scene_id, int gamen_id, int group_index, int cursor_x) {
	// rock load


}
int Gamen2::getSonotokiCursorGroup(int scene_id, int gamen_id) {
	// rock load



}
	
	
	
	
	
	
void Gamen2::setSonotokiNowSonotoki(int scene_id, int gamen_id) { // rock load lua_filenameが呼ばれる
}

int Gamen2::getNowSonotokiCursorGroup() {

}


Gamen2_Sonotoki* Gamen2::getNowSonotoki() {
	// cursor_groupを呼ぶために使うので　外部でCS_LOAD_CSをロックする

}


int Gamen2::makePartsGroup(int scene_id, char* help_text, char* lua_file_when_focused, char* lua_file_when_selected) {


}
// grouip_indexを返す has_is_focused_changedのときだけfocusedのルーアファイルが呼ばれる

int Gamen2::setPartsGroupSetText(int group_index, bool is_tex2, int text_index) {
	// group 内のindexを返す

}
	
	
	
	
	
	
	
	
int Gamen2::setPartsGroupSetTex(int group_index, bool is_tex2, int tex_index) {
	// group 内のindexを返す



}
	
	
int Gamen2::getPartsGroupIsText(int group_index, int index) {
	// 該当のindexの要素がtextであるか





}
	
	
	
	
int Gamen2::getPartsGroupIsTex2(int group_index, int index) {
	// 該当のindexの要素がtex２を使っているか


}
	
	
	
	
	
	
	
void Gamen2::setPartsGroupMoveTo(int group_index, int x, int y, int width, int height, float time) {
	// load lock








}
	
bool Gamen2::getPartsGroupMoveFinished(int group_index) {
	// load lock






}
	
	
void Gamen2::setPartsGroupTenmetu(int group_index, float dt, float tenmetu_kankaku) {
	
}

bool Gamen2::getPartsGroupTenmetuFinished(int group_index) {

}

