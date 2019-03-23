#include "KTRoboGamen2.h"
#include "KTROBOGameError.h"
#include "KTRoboLog.h"
#include "KTRoboCS.h"
#include "tolua_glue/tolua_glue.h"

using namespace KTROBO;

Gamen2::Gamen2()
{
	now_sonotoki = 0;
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


void Gamen2_Sonotoki::makeKoCursorGroup() {
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

Gamen2_part* Gamen2::getGamen2Part(int all_index) {


	if ((all_index >= 0) && (all_index < all_parts.size())) {
		return all_parts[all_index];
	}
}

void Gamen2::pauseWork() {
	// moveToの動きは実行されるが　クリックやセレクトをしても反応しないようにする 
					  // selectedされたときに実行される
					  // pauseから戻るのはgamen_sonotoki::enter で設定しなおされるから
	CS::instance()->enter(CS_LOAD_CS, "enterpause");
	// 現在のall_partsのis_workをコピーする
	all_parts_is_work_mae.clear();
	vector<Gamen2_part*>::iterator it = all_parts.begin();
	while (it != all_parts.end()) {
		Gamen2_part* pp = *it;
		bool t = pp->getIsWork();
		all_parts_is_work_mae.push_back(t);
		pp->setIsWork(false);
		it++;
	}

	CS::instance()->leave(CS_LOAD_CS, "enterpause");


}


void Gamen2::setCPPParts(Gamen2_part* parts, int scene_id, int parts_DEF) {
	CS::instance()->enter(CS_LOAD_CS, "cpppa");
	volatile int cppindex = this->cpp_parts.size();
	cpp_parts.push_back(parts);
	cpp_parts_map.insert(pair<pair<int, int>, int>(pair<int, int>(scene_id, parts_DEF), cppindex));

	CS::instance()->leave(CS_LOAD_CS, "cpppa");
}

int Gamen2::getCPPPartsIndex(int scene_id, int parts_DEF) {
	CS::instance()->enter(CS_LOAD_CS, "cpppa");
	volatile int tet = 0;
	if (cpp_parts_map.find(pair<int, int>(scene_id, parts_DEF)) != cpp_parts_map.end()) {
		tet = cpp_parts_map.find(pair<int, int>(scene_id, parts_DEF))->second;
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "cpppa");
		throw new GameError(KTROBO::FATAL_ERROR, "cppppa error");
	}

	CS::instance()->leave(CS_LOAD_CS, "cpppa");
	return tet;
}

void Gamen2::makeSonotoki(int scene_id, int gamen_id, char* lua_filename) {
	// rock load
	CS::instance()->enter(CS_LOAD_CS, "makesonotoki");
	sonotokis.push_back(new Gamen2_Sonotoki(scene_id, gamen_id, lua_filename));
	CS::instance()->leave(CS_LOAD_CS, "make sonotoki");

}

void Gamen2::setSonotokiMakeKo(int scene_id, int gamen_id) {
	// rock load
	CS::instance()->enter(CS_LOAD_CS, "makeko");

	if (sonotokis_map.find(pair<int, int>(scene_id, gamen_id)) != sonotokis_map.end()) {
		int inde = sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second;
		int smap = sonotokis.size();
		if ((inde < smap) && inde >= 0) {
			sonotokis[inde]->makeKoCursorGroup();
		}
		else {
			CS::instance()->leave(CS_LOAD_CS, "makeko");
			throw new GameError(FATAL_ERROR, "makeko vector error");
		}
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "makeko");
		throw new GameError(FATAL_ERROR, "makeko dont find");
	}



	CS::instance()->leave(CS_LOAD_CS, "makeko");

}
void Gamen2::setSonotokiSetGroupOnlyRenderGroup(int scene_id, int gamen_id, int all_index) {
	// rock load
	// rock load
	CS::instance()->enter(CS_LOAD_CS, "org");

	if (sonotokis_map.find(pair<int, int>(scene_id, gamen_id)) != sonotokis_map.end()) {
		int inde = sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second;
		int smap = sonotokis.size();
		if ((inde < smap) && inde >= 0) {
			sonotokis[inde]->setGroupOnlyRenderGroup(all_index);
		}
		else {
			CS::instance()->leave(CS_LOAD_CS, "org");
			throw new GameError(FATAL_ERROR, "org vector error");
		}
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "org");
		throw new GameError(FATAL_ERROR, "org dont find");
	}



	CS::instance()->leave(CS_LOAD_CS, "org");

}

void Gamen2::setSonotokiSetGroupGroup(int scene_id, int gamen_id, int group_index, int cursor_x) {
	// rock load
	CS::instance()->enter(CS_LOAD_CS, "sgg");

	if (sonotokis_map.find(pair<int, int>(scene_id, gamen_id)) != sonotokis_map.end()) {
		int inde = sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second;
		int smap = sonotokis.size();
		if ((inde < smap) && inde >= 0) {
			sonotokis[inde]->setGroupGroup(group_index, cursor_x);
		}
		else {
			CS::instance()->leave(CS_LOAD_CS, "sgg");
			throw new GameError(FATAL_ERROR, "sgg vector error");
		}
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "sgg");
		throw new GameError(FATAL_ERROR, "sgg dont find");
	}



	CS::instance()->leave(CS_LOAD_CS, "sgg");

}
int Gamen2::getSonotokiCursorGroup(int scene_id, int gamen_id) {
	// rock load
	CS::instance()->enter(CS_LOAD_CS, "gcg");
	volatile int ans = 0;
	if (sonotokis_map.find(pair<int, int>(scene_id, gamen_id)) != sonotokis_map.end()) {
		int inde = sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second;
		int smap = sonotokis.size();
		if ((inde < smap) && inde >= 0) {
			ans = sonotokis[inde]->getCursorGroup();
		}
		else {
			CS::instance()->leave(CS_LOAD_CS, "gcg");
			throw new GameError(FATAL_ERROR, "gcg vector error");
		}
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "gcg");
		throw new GameError(FATAL_ERROR, "gcg dont find");
	}



	CS::instance()->leave(CS_LOAD_CS, "gcg");

	return ans;
}
	
	
	
	
int Gamen2::getPartsGroupgetAllIndexFromGroupIndex(int group_index) {
	// group 内のindexを返す
	CS::instance()->enter(CS_LOAD_CS, "gamen2 settexs");
	volatile int ans = 0;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		Gamen2_partGroup* pg = grouped_parts[group_index];
		ans = pg->getAllIndex();
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 settexs");
	return ans;

}
void Gamen2_Sonotoki::setIsWorkAndRenderWhenNowSonotoki(vector<Gamen2_part*>* all_parts) {
	int asize = all_parts->size();

	for (int i = 0; i < asize; i++) {
		(*all_parts)[i]->setIsWorkAndRender(false);
	}

	int xsize = cursor_group.size();
	for (int i = 0; i < xsize; i++) {
		vector<int>* gg = cursor_group[i];
		int gsize = gg->size();
		for (int k = 0; k < gsize; k++) {
			int group_index = (*gg)[k];
			if ((asize > group_index) && group_index >= 0) {
				Gamen2_part* pg = (*all_parts)[group_index];
				pg->setIsWorkAndRender(true);
			}
			else {
				mylog::writelog(KTROBO::WARNING, "group index okasiiin sonotoki\n");
			}
		}


	}

	int nsize = not_cursor_but_render_group.size();
	for (int i = 0; i < nsize; i++) {
		int inde = not_cursor_but_render_group[i];
		if ((asize > inde) && (inde >= 0)) {
			Gamen2_part* pg = (*all_parts)[inde];
			pg->setIsWorkAndRender(true);
			pg->setIsWork(false);
		}
		else {
			mylog::writelog(KTROBO::WARNING, "group index okasiiin sonotoki\n");
		}
	}


}
void Gamen2::setSonotokiNowSonotoki(int scene_id, int gamen_id) { // rock load lua_filenameが呼ばれる
	CS::instance()->enter(CS_LOAD_CS, "nowsonotoki");
	if (sonotokis_map.find(pair<int, int>(scene_id, gamen_id)) != sonotokis_map.end()) {
		// arunode
		int inde = (sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second);
		int sonosize = sonotokis.size();
		if ((inde < sonosize) && inde >= 0) {

			// is_render と is_work の話もある only render にあるものは　setis_workandrender のあとに　isworkをfalseにする
			now_sonotoki = sonotokis[inde];
			

			char now_str[1024];
			memset(now_str, 0, 1024);
			strcpy_s(now_str, 512, now_sonotoki->getLuaFilename().c_str());
			if (strcmp(KTROBO_GAMEN2_LUA_FILENAME_NO_LUA, now_str) != 0) {
				MyLuaGlueSingleton::getInstance()->getColLuaExectors(0)->getInstance(0)->setExecDoNow(now_str);
			}
		}
		else {
			CS::instance()->leave(CS_LOAD_CS, "now_sonotoki");
			throw new GameError(KTROBO::FATAL_ERROR, "now sonotoki vector out");
		}
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "now_sonotoki");
		throw new GameError(KTROBO::FATAL_ERROR, "now sonotoki cant find sonotoki");
	}
	CS::instance()->leave(CS_LOAD_CS, "now sonotoki");
}

int Gamen2::getNowSonotokiCursorGroup() {
	CS::instance()->enter(CS_LOAD_CS, "nowsonotoki");
	if (now_sonotoki) {
		volatile int nw = now_sonotoki->getCursorGroup();
		CS::instance()->leave(CS_LOAD_CS, "now sonotoki");
		return nw;

	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "now sonotoki");
		throw new GameError(FATAL_ERROR, "okasii sonotoki");
	}
	CS::instance()->leave(CS_LOAD_CS, "now sonotoki");
}


Gamen2_Sonotoki* Gamen2::getNowSonotoki() {
	// cursor_groupを呼ぶために使うので　外部でCS_LOAD_CSをロックする
	return now_sonotoki; // NULL が返る可能性もある
}
void Gamen2_partGroup::setString(char* help_text, char* focused_lua, char* selected_lua) {
	this->help_text = help_text;
	this->focused_lua = focused_lua;
	this->selected_lua = selected_lua;
}

int Gamen2::makePartsGroup(int scene_id, char* help_text, char* lua_file_when_focused, char* lua_file_when_selected) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 makeparts");

	volatile int all_index = all_parts.size();
	volatile int group_index = grouped_parts.size();
	Gamen2_partGroup* pg = new Gamen2_partGroup(scene_id, all_index, group_index);
	pg->setString(help_text, lua_file_when_focused, lua_file_when_selected);
	all_parts.push_back(pg);
	grouped_parts.push_back(pg);
	CS::instance()->leave(CS_LOAD_CS, "gamen2 makeparts");
	return group_index;
}
// grouip_indexを返す has_is_focused_changedのときだけfocusedのルーアファイルが呼ばれる

int Gamen2::setPartsGroupSetText(int group_index, bool is_tex2, int text_index, IN_ int* recto) {
	// group 内のindexを返す
	CS::instance()->enter(CS_LOAD_CS, "gamen2 settexts");
	volatile int ans = 0;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		Gamen2_partGroup* pg = grouped_parts[group_index];
		ans = pg->setText(text_index, is_tex2, recto);
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 settexts");
	return ans;
}
	

int Gamen2_partGroup::setText(int text_index, bool is_tex2, IN_ int* recto) {
	GAMEN2_PARTGROUPSTRUCT st;
	st.index = text_index;
	st.is_tex2 = is_tex2;
	st.is_text = true;
	int ans = tex_or_textindexs.size();
	tex_or_textindexs.push_back(st);
	MYRECT redayo;
	redayo.left = recto[0];
	redayo.right = recto[1];
	redayo.top = recto[2];
	redayo.bottom = recto[3];
	rects.push_back(redayo);
	now_rects.push_back(redayo);
	dest_rects.push_back(redayo);
	return ans;
};
int Gamen2_partGroup::setTex(int tex_index, bool is_tex2, IN_ int* recto) {

	GAMEN2_PARTGROUPSTRUCT st;
	st.index = tex_index;
	st.is_tex2 = is_tex2;
	st.is_text = false;
	int ans = tex_or_textindexs.size();
	tex_or_textindexs.push_back(st);
	MYRECT redayo;
	redayo.left = recto[0];
	redayo.right = recto[1];
	redayo.top = recto[2];
	redayo.bottom = recto[3];
	rects.push_back(redayo);
	now_rects.push_back(redayo);
	dest_rects.push_back(redayo);
	return ans;
};
	
	
	
	
	
	
	
int Gamen2::setPartsGroupSetTex(int group_index, bool is_tex2, int tex_index, IN_ int* recto) {
	// group 内のindexを返す
	CS::instance()->enter(CS_LOAD_CS, "gamen2 settexs");
	volatile int ans = 0;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		Gamen2_partGroup* pg = grouped_parts[group_index];
		ans = pg->setText(tex_index, is_tex2, recto);
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 settexs");
	return ans;


}
	
	
bool Gamen2::getPartsGroupIsText(int group_index, int index) {
	// 該当のindexの要素がtextであるか

	CS::instance()->enter(CS_LOAD_CS, "gamen2 istext");
	volatile bool ans = true;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		Gamen2_partGroup* pg = grouped_parts[group_index];
		volatile int size = pg->getTexOrTextIndexs()->size();
		if ((size > index) && (index >= 0)) {
			ans = (*pg->getTexOrTextIndexs())[index].is_text;
		}
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 istext");
	return ans;

}
	
	
	
	
bool Gamen2::getPartsGroupIsTex2(int group_index, int index) {
	// 該当のindexの要素がtex２を使っているか

	CS::instance()->enter(CS_LOAD_CS, "gamen2 istex");
	volatile bool ans = true;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		Gamen2_partGroup* pg = grouped_parts[group_index];
		volatile int size = pg->getTexOrTextIndexs()->size();
		if ((size > index) && (index >= 0)) {
			ans = (*pg->getTexOrTextIndexs())[index].is_tex2;
		}
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 istex");
	return ans;


}
	
	
	
	
	
	
	
void Gamen2::setPartsGroupMoveTo(int group_index, int x, int y, int width, int height, float time) {
	// load lock
	MYRECT rec;
	Gamen2_partGroup* pg = 0;
	CS::instance()->enter(CS_LOAD_CS, "gamen2 moveto");
	volatile bool ans = true;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		 pg = grouped_parts[group_index];
		
		rec.left = x;
		rec.top = y;
		rec.bottom = y + height;
		rec.right = x + width;
		pg->moveTo(&rec, time);
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 moveto");





}
	
bool Gamen2::getPartsGroupMoveFinished(int group_index) {
	// load lock

	volatile bool ans = true;
	MYRECT rec;
	Gamen2_partGroup* pg = 0;
	CS::instance()->enter(CS_LOAD_CS, "gamen2 movefinished");
	volatile bool ans = true;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		pg = grouped_parts[group_index];
		ans = pg->moveLoop(0);
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 movefinished");

	return ans;

}
	
	
void Gamen2::setPartsGroupTenmetu(int group_index, float dt, float tenmetu_kankaku) {
	// load lock
	MYRECT rec;
	Gamen2_partGroup* pg = 0;
	CS::instance()->enter(CS_LOAD_CS, "gamen2 tenmetu");
	volatile bool ans = true;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		pg = grouped_parts[group_index];
		pg->tenmetu(dt, tenmetu_kankaku);
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 tenmetu");
}

bool Gamen2::getPartsGroupTenmetuFinished(int group_index) {

	volatile bool ans = true;
	MYRECT rec;
	Gamen2_partGroup* pg = 0;
	CS::instance()->enter(CS_LOAD_CS, "gamen2 tenfinished");
	volatile bool ans = true;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		pg = grouped_parts[group_index];
		ans = pg->tenmetuLoop(0);
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 tenfinished");

	return ans;

}

void Gamen2::Del(Texture* tex, Texture* tex2) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 del");
	cpp_parts.clear();
	all_parts.clear();
	all_parts_is_work_mae.clear();
	sonotokis_map.clear();
	cpp_parts_map.clear();
	int size = sonotokis.size();
	for (int i = 0; i < size; i++) {
		if (sonotokis[i]) {
			sonotokis[i]->deletedayo();
			delete sonotokis[i];
			sonotokis[i] = 0;
		}
	}
	sonotokis.clear();

	int ssize = grouped_parts.size();
	for (int i = 0; i < ssize; i++) {
		if (grouped_parts[i]) {
			grouped_parts[i]->cleardayo(tex,tex2);
			delete grouped_parts[i];
			grouped_parts[i] = 0;
		}
	}
	grouped_parts.clear();

	CS::instance()->leave(CS_LOAD_CS, "gamen2 del");


}