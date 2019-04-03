#include "KTRoboGamen2.h"
#include "KTROBOGameError.h"
#include "KTRoboLog.h"
#include "KTRoboCS.h"
#include "tolua_glue/tolua_glue.h"

using namespace KTROBO;

Gamen2::Gamen2(Texture* tex, Texture* tex2)
{
	now_sonotoki = 0;
	this->tex = tex;
	this->tex2 = tex2;
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
	
	CS::instance()->enter(CS_MESSAGE_CS, "gamen2sonotoki");
	CS::instance()->enter(CS_LOAD_CS, "gamen2sonotoki");
	int cg_size = cursor_group.size();
	for (int i = 0; i < cg_size; i++) {
		if (cursor_group[i]) {
			cursor_group[i]->clear();
			delete cursor_group[i];
			cursor_group[i] = 0;
		}
	}
	cursor_group.clear();
	cursor_ys.clear();
	not_cursor_but_render_group.clear();
	CS::instance()->leave(CS_LOAD_CS, "gamen2sonotoki");
	CS::instance()->leave(CS_MESSAGE_CS, "gamen2sonotoki");
	

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
	if (cursor_y >= 0 && cursor_y < cursor_group[dd]->size()) {
		cursor_ys[dd] = cursor_y;
	}
}

void Gamen2_Sonotoki::setCursorX(int cursor_x) {
	int cg_size = cursor_group.size();
	if (cg_size <= 0) {
		mylog::writelog(KTROBO::WARNING, "no cursor group\n");
		return;
	}

	if (this->cursor_x > cursor_x) {
		if (cursor_x < 0) {
			this->cursor_x = 0;
			return;
		}
		else {
			this->cursor_x = cursor_x;
		}

	}
	else if (this->cursor_x < cursor_x) {
		if (cg_size <= cursor_x) {
			this->cursor_x = cg_size - 1;
		}
		else {
			this->cursor_x = cursor_x;
		}
	}

}

void Gamen2_Sonotoki::setCursorXY(int all_index) {
	// もし見つからなかったらそのまま
	int cgsize = cursor_group.size();
	for (int i = 0; i < cgsize; i++) {
		vector<int>* gro = (cursor_group)[i];
		int grosize = gro->size();

		for (int k = 0; k < grosize; k++) {
			int ginde = (*gro)[k];
			if (all_index == ginde) {
				cursor_x = i;
				cursor_ys[i] = k;
			}

		}
	}
}
int Gamen2_Sonotoki::getCursorGroup() {

	int cg_size = cursor_group.size();
	if (cg_size <= 0) {
		return 0;
		throw new GameError(KTROBO::FATAL_ERROR, "no cursor group");
	}
	if ((cursor_x < 0) || (cursor_x >= cg_size)) {
		return 0;
		throw new GameError(KTROBO::FATAL_ERROR, "bad cursor_x");
	}
	vector<int>* gg = cursor_group[cursor_x];
	int gg_size = gg->size();
	if (gg_size <= 0) {
		return 0;
		throw new GameError(KTROBO::FATAL_ERROR, "no cursor group");
	}
	// cursor_y に関してはエラーをはかずにゲットする
	int tt = cursor_ys[cursor_x] % gg_size;
	return (*gg)[tt];
}


void Gamen2_partGroup::cleardayo(Texture* tex, Texture* tex2) {
	// texやtextの内容などをlightdeleteする vectorもクリアする
	CS::instance()->enter(CS_MESSAGE_CS, "gamen2partgroup");
	CS::instance()->enter(CS_LOAD_CS, "gamen2partgroup");
	
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
	
	CS::instance()->leave(CS_LOAD_CS, "gamen2partgroup");
	CS::instance()->leave(CS_MESSAGE_CS, "gamen2partgroup");
}

Gamen2_part* Gamen2::getGamen2Part(int all_index) {


	if ((all_index >= 0) && (all_index < all_parts.size()) && (all_index < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		return all_parts[all_index];
	}
	else if ((all_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		//int cpp_index = all_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		int parts_def = all_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		int cpp_index = this->getCPPPartsIndex(parts_def);
		int raw_index = this->getCPPPartsRawIndex(cpp_index);
		if ((raw_index >= 0) && (raw_index < cpp_parts.size())) {
			return cpp_parts[raw_index];
		}
		else {
			mylog::writelog(KTROBO::WARNING, "out of boud allindex");
			return 0;
		}
	}
	else {
		mylog::writelog(KTROBO::FATAL_ERROR, "out of boundallindex");
		return 0;
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

	it = cpp_parts.begin();
	while (it != cpp_parts.end()) {
		Gamen2_part* pp = *it;
		bool t = pp->getIsWork();
		pp->setIsWork(false);
		it++;
	}


	CS::instance()->leave(CS_LOAD_CS, "enterpause");


}


void Gamen2::setCPPParts(Gamen2_part* parts, int parts_DEF) {
	CS::instance()->enter(CS_LOAD_CS, "cpppa");
	volatile int cppindex = this->cpp_parts.size();
	cpp_parts.push_back(parts);
	cpp_parts_map.insert(pair<int, int>(parts_DEF, cppindex));

	CS::instance()->leave(CS_LOAD_CS, "cpppa");
}
void Gamen2::clearCPPParts(int scene_id) {
	CS::instance()->enter(CS_LOAD_CS, "cpppa");
	cpp_parts.clear(); cpp_parts_map.clear(); 
	if (events_map.find(scene_id) != events_map.end()) {
		Gamen2_event* eve = events[events_map.find(scene_id)->second];
		eve->clear_cpp();
	}

	CS::instance()->leave(CS_LOAD_CS, "cpppa");
}
int Gamen2::getCPPPartsSa(int parts_DEF, int ato_parts_DEF) {
	int cpp_index = getCPPPartsIndex(parts_DEF);
	int ato_cpp_index = getCPPPartsIndex(ato_parts_DEF);
	int raw_index = getCPPPartsRawIndex(cpp_index);
	int ato_raw_index = getCPPPartsRawIndex(ato_cpp_index);
	return ato_raw_index - raw_index;
}
int Gamen2::getCPPPartsRawIndex(int cpp_parts_index) {
	CS::instance()->enter(CS_LOAD_CS, "cpppa");
	volatile int tet = 0;
	int cppp = cpp_parts_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
	if (cpp_parts_map.find(cppp) != cpp_parts_map.end()) {
		tet = cpp_parts_map.find(cppp)->second;
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "cpppa");
		throw new GameError(KTROBO::FATAL_ERROR, "cppppa error in getCPPPartsRawIndex");
	}

	CS::instance()->leave(CS_LOAD_CS, "cpppa");
	return tet;

}
int Gamen2::getCPPPartsIndex(int parts_DEF) {
	CS::instance()->enter(CS_LOAD_CS, "cpppa");
	volatile int tet = 0;
	if (cpp_parts_map.find(parts_DEF) != cpp_parts_map.end()) {
		tet = parts_DEF + /*cpp_parts_map.find(pair<int, int>(scene_id, parts_DEF))->second +*/ KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
	}
	else {
		CS::instance()->leave(CS_LOAD_CS, "cpppa");
		throw new GameError(KTROBO::FATAL_ERROR, "cppppa error in getCPPPartsIndex");
	}

	CS::instance()->leave(CS_LOAD_CS, "cpppa");
	return tet;
}

void Gamen2::makeSonotoki(int scene_id, int gamen_id, char* lua_filename) {
	// rock load
	CS::instance()->enter(CS_LOAD_CS, "makesonotoki");
	volatile int inde = sonotokis.size();
	if ((inde <=0) || (sonotokis_map.find(pair<int, int>(scene_id, gamen_id)) == sonotokis_map.end())) {
		sonotokis.push_back(new Gamen2_Sonotoki(scene_id, gamen_id, lua_filename));
		sonotokis_map.insert(pair<pair<int, int>, int>(pair<int, int>(scene_id, gamen_id), inde));
	}
	else {
		// すでにある
		sonotokis[sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second]->deletedayo(); // 初期化する
		sonotokis[sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second]->setLuaStr(lua_filename);
	}
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
void Gamen2_Sonotoki::getAllIndexOfGGANDONLYRENDERGROUP(set<int>* outdayo) {
	int size = this->not_cursor_but_render_group.size();
	for (int i = 0; i < size; i++) {
		if (outdayo->find(not_cursor_but_render_group[i]) == outdayo->end()) {
			outdayo->insert(not_cursor_but_render_group[i]);
		}
	}
	
	size = cursor_group.size();
	for (int i = 0; i < size; i++) {
		vector<int>* pp = cursor_group[i];
		int psiz = pp->size();
		for (int k = 0; k < psiz; k++) {
			int ppp = (*pp)[k];
			if (outdayo->find(ppp) == outdayo->end()) {
				outdayo->insert(ppp);
			}
		}

	}
}
void Gamen2::setSonotokiSetGroupOnlyRenderGroupFromNowSonotokiIsRender(int scene_id, int gamen_id) {

	CS::instance()->enter(CS_LOAD_CS, "org");

	if (sonotokis_map.find(pair<int, int>(scene_id, gamen_id)) != sonotokis_map.end()) {
		int inde = sonotokis_map.find(pair<int, int>(scene_id, gamen_id))->second;
		int smap = sonotokis.size();
		if ((inde < smap) && inde >= 0) {
			if (now_sonotoki) {
				// now_sonotoki のすべてのallindexをonlyrendergroupに設定する
				set<int> test;
				now_sonotoki->getAllIndexOfGGANDONLYRENDERGROUP(&test);
				set<int>::iterator it =  test.begin();
				while (it != test.end()) {
					int p = *it;
					sonotokis[inde]->setGroupOnlyRenderGroup(p);
					it++;
				}
				
			}
			else {
				mylog::writelog(KTROBO::WARNING, "there is no nowsonotoki");
			}
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

void Gamen2_part::setIsWorkAndRender(bool t)
{
	is_work = t;
	is_render = t;
}

void Gamen2_Sonotoki::setIsWorkAndRenderWhenNowSonotoki(Gamen2* gamen, vector<Gamen2_part*>* all_parts, vector<Gamen2_part*>* cpp_parts) {
	int asize = all_parts->size();
	int cppsize = cpp_parts->size();
	for (int i = 0; i < asize; i++) {
		(*all_parts)[i]->setIsWorkAndRender(false);
	}
	for (int i = 0; i < cppsize; i++) {
		(*cpp_parts)[i]->setIsWorkAndRender(false);
	}

	int nsize = not_cursor_but_render_group.size();
	for (int i = 0; i < nsize; i++) {
		int inde = not_cursor_but_render_group[i];
		if ((asize > inde) && (inde >= 0) && (inde < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
			Gamen2_part* pg = (*all_parts)[inde];
			pg->setIsWorkAndRender(true);
			pg->setIsWork(false);
		}
		else if (inde >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET) {
			//int parts_def = inde - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
			//int cppinde = 
			//int cppinde = inde - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
			//if ((cppinde >= 0) && (cppinde < cppsize)) {
			Gamen2_part* pp = gamen->getGamen2Part(inde);// (*cpp_parts)[cppinde];
				pp->setIsWorkAndRender(true);
				pp->setIsWork(false);
			/*}
			else {
				mylog::writelog(KTROBO::WARNING, "group index okasiiin sonotoki\n");
			}*/
		}
		else {
			mylog::writelog(KTROBO::WARNING, "group index okasiiin sonotoki\n");
		}
	}

	int xsize = cursor_group.size();
	for (int i = 0; i < xsize; i++) {
		vector<int>* gg = cursor_group[i];
		int gsize = gg->size();
		for (int k = 0; k < gsize; k++) {
			int group_index = (*gg)[k];
			if ((asize > group_index) && (group_index >= 0) && (group_index < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
				Gamen2_part* pg = (*all_parts)[group_index];
				pg->setIsWorkAndRender(true);
			}
			else if ((group_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
				//int cppindex = group_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
				//if ((cppindex >= 0) && (cppindex < cppsize)) {
				//	Gamen2_part* pp = (*cpp_parts)[cppindex];
				//	pp->setIsWorkAndRender(true);
				//}
				//else {
				//	mylog::writelog(KTROBO::WARNING, "group index okasiiin sonotoki\n");
				//}
				Gamen2_part* pp = gamen->getGamen2Part(group_index);
				pp->setIsWorkAndRender(true);
			}
			else {
				mylog::writelog(KTROBO::WARNING, "group index okasiiin sonotoki\n");
			}
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
			now_sonotoki->setIsWorkAndRenderWhenNowSonotoki(this, &all_parts, &cpp_parts);

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

int Gamen2::makePartsGroup(int scene_id, char* help_text, char* lua_file_when_focused, char* lua_file_when_selected, IN_ int* rect) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 makeparts");

	volatile int all_index = all_parts.size();
	volatile int group_index = grouped_parts.size();
	if (all_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET) {
		mylog::writelog(KTROBO::WARNING, "cppparts offset index koeru");
	}
	Gamen2_partGroup* pg = new Gamen2_partGroup(scene_id, all_index, group_index,tex,tex2);
	pg->setString(help_text, lua_file_when_focused, lua_file_when_selected);
	all_parts.push_back(pg);
	grouped_parts.push_back(pg);
	MYRECT re;
	re.left = rect[0]; re.right = rect[1]; re.top = rect[2]; re.bottom = rect[3];
	pg->setRect(&re);
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
	
void Gamen2::setPartsGroupIsWorkRender(int group_index, bool t) {
	// group 内のindexを返す
	CS::instance()->enter(CS_LOAD_CS, "gamen2 settexts");
	volatile int ans = 0;
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0)) {
		Gamen2_partGroup* pg = grouped_parts[group_index];
		pg->setIsWorkAndRender(t);
	}
	if ((all_index > group_index) && (group_index >= 0) && (group_index < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		Gamen2_partGroup* pg = grouped_parts[group_index];
		pg->setIsWorkAndRender(t);
	}
	else if ((group_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		int cpp_index = group_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		int csize = cpp_parts.size();
		if ((cpp_index >= 0) && (cpp_index < csize)) {
			Gamen2_part* pp = cpp_parts[cpp_index];
			pp->setIsWorkAndRender(t);
		}
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 settexts");
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
		ans = pg->setTex(tex_index, is_tex2, recto);
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
	if ((all_index > group_index) && (group_index >= 0) && (group_index < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		 pg = grouped_parts[group_index];
		
		rec.left = x;
		rec.top = y;
		rec.bottom = y + height;
		rec.right = x + width;
		pg->moveTo(&rec, time);
	}
	else if ((group_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		//int parts_def = group_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		int cpp_index = this->getCPPPartsRawIndex(group_index);
		int csize = cpp_parts.size();
		if ((cpp_index >= 0) && (cpp_index < csize)) {
			Gamen2_part* pp = cpp_parts[cpp_index];
			rec.left = x;
			rec.top = y;
			rec.bottom = y + height;
			rec.right = x + width;
			pp->moveTo(&rec, time);
		}
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 moveto");





}
	
bool Gamen2::getPartsGroupMoveFinished(int group_index) {
	// load lock

	volatile bool ans = true;
	MYRECT rec;
	Gamen2_partGroup* pg = 0;
	CS::instance()->enter(CS_LOAD_CS, "gamen2 movefinished");
	
	volatile int all_index = grouped_parts.size();

	if ((all_index > group_index) && (group_index >= 0) && (group_index < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		pg = grouped_parts[group_index];
		ans = pg->moveLoop(0);
	}
	else if ((group_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		int cpp_index = group_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		int csize = cpp_parts.size();
		if ((cpp_index >= 0) && (cpp_index < csize)) {
			Gamen2_part* pp = cpp_parts[cpp_index];
			ans = pp->moveLoop(0);
		}
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

	if ((all_index > group_index) && (group_index >= 0) && (group_index < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		pg = grouped_parts[group_index];
		pg->tenmetu(dt,tenmetu_kankaku);
	}
	else if ((group_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		int cpp_index = group_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		int csize = cpp_parts.size();
		if ((cpp_index >= 0) && (cpp_index < csize)) {
			Gamen2_part* pp = cpp_parts[cpp_index];
			pp->tenmetu(dt, tenmetu_kankaku);
		}
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 tenmetu");
}

bool Gamen2::getPartsGroupTenmetuFinished(int group_index) {

	volatile bool ans = true;
	MYRECT rec;
	Gamen2_partGroup* pg = 0;
	CS::instance()->enter(CS_LOAD_CS, "gamen2 tenfinished");
	
	volatile int all_index = grouped_parts.size();
	if ((all_index > group_index) && (group_index >= 0) && (group_index < KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		pg = grouped_parts[group_index];
		ans = pg->tenmetuLoop(0);
	}
	else if ((group_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET)) {
		int cpp_index = group_index - KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET;
		int csize = cpp_parts.size();
		if ((cpp_index >= 0) && (cpp_index < csize)) {
			Gamen2_part* pp = cpp_parts[cpp_index];
			ans = pp->tenmetuLoop(0);
		}
	}
	CS::instance()->leave(CS_LOAD_CS, "gamen2 tenfinished");

	return ans;

}

void Gamen2::Del() {
	CS::instance()->enter(CS_MESSAGE_CS, "test");
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

	events_map.clear();
	int hsize = events.size();
	for (int i = 0; i < hsize; i++) {
		if (events[i]) {
			delete events[i];
			events[i] = 0;
		}
	}

	events.clear();

	CS::instance()->leave(CS_LOAD_CS, "gamen2 del");
	CS::instance()->leave(CS_MESSAGE_CS, "test");

}


void Gamen2_partGroup::setIsWorkAndRender(bool t) {
	int size = this->tex_or_textindexs.size();
	Gamen2_part::setIsWorkAndRender(t);
	// もし点滅中だったらやめさせる
	this->tenmetu_dt = 21;
	this->tenmetu_time = 20;
	this->tenmetu_kankaku = 20;
	this->tenmetuLoop(10);

	for (int i = 0; i < size; i++) {
		int inde = tex_or_textindexs[i].index;
		if (tex_or_textindexs[i].is_text) {
			if (tex_or_textindexs[i].is_tex2) {
				tex2->setRenderTextIsRender(inde, t);
			}
			else {
				tex->setRenderTextIsRender(inde, t);
			}
		}
		else {
			if (tex_or_textindexs[i].is_tex2) {
				tex2->setRenderTexIsRender(inde, t);
			}
			else {
				tex->setRenderTexIsRender(inde, t);
			}
		}
	}


}


void Gamen2::loopForMoveToAndTenmetu(float dt) {
	CS::instance()->enter(CS_LOAD_CS, "test");
	CS::instance()->enter(CS_DEVICECON_CS, "test");
	volatile int size = all_parts.size();
	for (int i = 0; i < size; i++) {
		all_parts[i]->moveLoop(dt);
		all_parts[i]->tenmetuLoop(dt);
	}
	volatile int csz = cpp_parts.size();
	for (int i = 0; i < csz; i++) {
		cpp_parts[i]->moveLoop(dt);
		cpp_parts[i]->tenmetuLoop(dt);
	}

	CS::instance()->leave(CS_DEVICECON_CS, "test");
	CS::instance()->leave(CS_LOAD_CS, "test");
}
void Gamen2_partGroup::setIsWork(bool t) {
	Gamen2_part::setIsWork(t);
}
bool Gamen2_partGroup::selected(int x, int y) {
	if (!is_work) return false;
	if (is_focused) {
		int size = tex_or_textindexs.size();
		for (int i = 0; i < size; i++) {
			MYRECT nowre = now_rects[i];
			unsigned int bu = getButukariStatusPoint(x, y, &nowre);
			if (bu & BUTUKARIPOINT_IN) {
				selectExe();
				return true;
			}
		}
	}
	return false;

}
bool Gamen2_partGroup::focused(int x, int y) {
	if (!is_work) return false;
	int size = tex_or_textindexs.size();
	for (int i = 0; i < size; i++) {
		MYRECT nowre = now_rects[i];
		unsigned int bu = getButukariStatusPoint(x, y, &nowre);
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
	}

	if (is_focused) {
		has_is_focused_changed = true;
		is_focused = false;
	}
	
	return false;
}
void Gamen2_partGroup::unfocused(int x, int y) {
	if (!is_work) return;
	if (is_focused) {

		int size = tex_or_textindexs.size();
		bool t = true;
		for (int i = 0; i < size; i++) {
			MYRECT nowre = now_rects[i];
			unsigned int bu = getButukariStatusPoint(x, y, &nowre);
			if (bu & BUTUKARIPOINT_IN) {
				t = false;
			}
			else {
			}
		}
		if (t) {
			is_focused = false;
			has_is_focused_changed = true;
		}
	}
}
void Gamen2_partGroup::moveTo(MYRECT* dest_re, float time) {
	destRect = *dest_re;
	rect = nowRect;
	this->dt = 0;
	float lefri = destRect.left - rect.left;
	float topri = destRect.top - rect.top;
	if (time < 0.000001) {
		throw new GameError(KTROBO::WARNING, "notime\n");
	}
	speedx = lefri / time;
	speedy = topri / time;
	this->time = time; 
}
bool Gamen2_partGroup::moveLoop(float dt) {
	if (dt < 0.000001) {
		if (this->dt > time) {
			return true;
		}
		else {
			return false;
		}
	}
	if (this->dt >= time) return true;

	float dx = speedx * dt;
	float dy = speedy * dt;
	nowRect.left += dx;
	nowRect.right += dx;
	nowRect.top += dy;
	nowRect.bottom += dy;

	int size = tex_or_textindexs.size();
	for (int i = 0; i < size; i++) {
		if (tex_or_textindexs[i].is_tex2) {
			if (tex_or_textindexs[i].is_text) {
				tex2->setRenderTextPos(tex_or_textindexs[i].index, now_rects[i].left + dx, now_rects[i].top + dy);
			}
			else {
				tex2->setRenderTexPos(tex_or_textindexs[i].index, now_rects[i].left + dx, now_rects[i].top + dy);

			}
		}
		else {
			if (tex_or_textindexs[i].is_text) {
				tex->setRenderTextPos(tex_or_textindexs[i].index, now_rects[i].left + dx, now_rects[i].top + dy);
			}
			else {
				tex->setRenderTexPos(tex_or_textindexs[i].index, now_rects[i].left + dx, now_rects[i].top + dy);

			}
		}
		now_rects[i].left += dx;
		now_rects[i].right += dx;
		now_rects[i].top += dy;
		now_rects[i].bottom += dy;
	}


	this->dt += dt;
	// 動き終わったらtrueを返す
	if (this->dt > time) return true;
	return false;
}
void Gamen2_partGroup::tenmetu(float time, float tenmetu_kankaku) {
	if (is_render == false) return; // なにもしない
	is_tenmetu = true;
	this->tenmetu_dt = 0;
	this->tenmetu_kankaku = tenmetu_kankaku;
	this->tenmetu_time = time;
}
bool Gamen2_partGroup::tenmetuLoop(float dt) {
	if (!is_tenmetu) return true;
	if (dt < 0.0001) {
		if (tenmetu_dt >= tenmetu_time) {
			return true;
		}
		else {
			return false;
		}
	}
	if (is_tenmetu &&(tenmetu_dt >= tenmetu_time)) {
		is_render = true;
		int size = tex_or_textindexs.size();
		for (int i = 0; i < size; i++) {
			if (tex_or_textindexs[i].is_tex2) {
				if (tex_or_textindexs[i].is_text) {
					tex2->setRenderTextIsRender(tex_or_textindexs[i].index,true);
				}
				else {
					tex2->setRenderTexIsRender(tex_or_textindexs[i].index, true);

				}
			}
			else {
				if (tex_or_textindexs[i].is_text) {
					tex->setRenderTextIsRender(tex_or_textindexs[i].index, true);
				}
				else {
					tex->setRenderTexIsRender(tex_or_textindexs[i].index, true);

				}
			}

		}
		is_tenmetu = false;

		return true;
	}


	tenmetu_dt += dt;

	float unk = tenmetu_dt / tenmetu_kankaku;
	int un = floor(unk);
	bool is_render = false;
	if (un % 2 == 0) {
		is_render = true;
	}
	int size = tex_or_textindexs.size();
	for (int i = 0; i < size; i++) {
		if (tex_or_textindexs[i].is_tex2) {
			if (tex_or_textindexs[i].is_text) {
				tex2->setRenderTextIsRender(tex_or_textindexs[i].index, is_render);
			}
			else {
				tex2->setRenderTexIsRender(tex_or_textindexs[i].index, is_render);

			}
		}
		else {
			if (tex_or_textindexs[i].is_text) {
				tex->setRenderTextIsRender(tex_or_textindexs[i].index,is_render);
			}
			else {
				tex->setRenderTexIsRender(tex_or_textindexs[i].index, is_render);

			}
		}

	}


	return false;
}


Gamen2_event::Gamen2_event(int scene_id) {
	this->scene_id = scene_id;
	for (int i = 0; i < KTROBO_GAMEN2_EVENT_MAX; i++) {
		hensuu[i] = 0;
	}
}
Gamen2_event::~Gamen2_event() {

	gihiandh.clear();

}

void Gamen2_event::makeHensuu(int hensuu_id, int default_hensuu) {
	if ((hensuu_id >= 0) && (hensuu_id < KTROBO_GAMEN2_EVENT_MAX)) {
		hensuu[hensuu_id] = default_hensuu;
	}
	else {
		mylog::writelog(KTROBO::WARNING, "there is out of hensuu_id\n");
	}

}
int Gamen2_event::getHensuu(int hensuu_id) {
	if ((hensuu_id >= 0) && (hensuu_id < KTROBO_GAMEN2_EVENT_MAX)) {
		return hensuu[hensuu_id];
	}
	else {
		mylog::writelog(KTROBO::WARNING, "there is out of hensuu_id\n");
		return 0;
	}

}


void Gamen2_event::setHensuu(int hensuu_id, int hensusu) {
	if ((hensuu_id >= 0) && (hensuu_id < KTROBO_GAMEN2_EVENT_MAX)) {
		hensuu[hensuu_id] = hensusu;
	}
	else {
		mylog::writelog(KTROBO::WARNING, "there is out of hensuu_id\n");
		
	}

}

void Gamen2::setTempHensuuRule(int scene_id, int hensuu_id, int hensuu, int group_index) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 sethensuurule");
	Gamen2_event* e = 0;

	if (events_map.find(scene_id) != events_map.end()) {
		e = events[events_map.find(scene_id)->second];
	}
	else {
		int esize = events.size();
		events_map.insert(pair<int, int>(scene_id, esize));
		e = new Gamen2_event(scene_id);
		events.push_back(e);
	}
	e->setTempHensuuRule(hensuu_id, hensuu, group_index);

	CS::instance()->leave(CS_LOAD_CS, "gamen2 sethensuurule");
}
void Gamen2::deleteTempHensuuRule(int scene_id) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 sethensuurule");
	Gamen2_event* e = 0;

	if (events_map.find(scene_id) != events_map.end()) {
		e = events[events_map.find(scene_id)->second];
	}
	else {
		int esize = events.size();
		events_map.insert(pair<int, int>(scene_id, esize));
		e = new Gamen2_event(scene_id);
		events.push_back(e);
	}
	e->clear_temp();

	CS::instance()->leave(CS_LOAD_CS, "gamen2 sethensuurule");
}

void Gamen2_event::setTempHensuuRule(int hensuu_id, int hensuu, int group_index) {
	temp_gihiandh.push_back(pair<int, pair<int, int>>(group_index, pair<int, int>(hensuu_id, hensuu)));
}

void Gamen2_event::setHensuuRule(int hensuu_id, int hensuu, int group_index) {
	if (group_index >= KTROBO_GAMEN2_CPPPARTS_INDEX_OFFSET) {
		gihiandh_forcpp.push_back(pair<int, pair<int, int>>(group_index, pair<int, int>(hensuu_id, hensuu)));
	}
	else {
		gihiandh.push_back(pair<int, pair<int, int>>(group_index, pair<int, int>(hensuu_id, hensuu)));
	}
}

void Gamen2_event::selected(int group_index) {
	int size = gihiandh.size();
	for (int i = 0; i < size; i++) {
		if (group_index == gihiandh[i].first) {
			pair<int, int> pp = gihiandh[i].second;
			int hi = pp.first;
			int h = pp.second;
			setHensuu(hi, h);
		}
	}
	int cppsize = gihiandh_forcpp.size();
	for (int i = 0; i < cppsize; i++) {
		if (group_index == gihiandh_forcpp[i].first) {
			pair<int, int> pp = gihiandh_forcpp[i].second;
			int hi = pp.first;
			int h = pp.second;
			setHensuu(hi, h);
		}
	}

	int temp_size = temp_gihiandh.size();
	for (int i = 0; i < temp_size; i++) {
		if (group_index == temp_gihiandh[i].first) {
			pair<int, int> pp = temp_gihiandh[i].second;
			int hi = pp.first;
			int h = pp.second;
			setHensuu(hi, h);
		}
	}
}

void Gamen2::setHensuuRule(int scene_id, int hensuu_id, int hensuu, int group_index) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 sethensuurule");
	Gamen2_event* e=0;
	
	if (events_map.find(scene_id) != events_map.end()) {
		e = events[events_map.find(scene_id)->second];
	}
	else {
		int esize = events.size();
		events_map.insert(pair<int, int>(scene_id, esize));
		e = new Gamen2_event(scene_id);
		events.push_back(e);
	}
	e->setHensuuRule(hensuu_id, hensuu, group_index);

	CS::instance()->leave(CS_LOAD_CS, "gamen2 sethensuurule");
}
void Gamen2::makeHensuu(int scene_id, int hensuu_id, int default_hensuu) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 makehensuu");
	Gamen2_event* e = 0;
	if (events_map.find(scene_id) != events_map.end()) {
		e = events[events_map.find(scene_id)->second];
	}
	else {
		int esize = events.size();
		events_map.insert(pair<int, int>(scene_id, esize));
		e = new Gamen2_event(scene_id);
		events.push_back(e);
	}
	e->makeHensuu(hensuu_id, default_hensuu);

	CS::instance()->leave(CS_LOAD_CS, "gamen2 makehensuu");
}

Gamen2_event* Gamen2::getEvent(int scene_id) {
	Gamen2_event* e = 0;
	if (events_map.find(scene_id) != events_map.end()) {
		e = events[events_map.find(scene_id)->second];
	}
	return e;
}

int Gamen2::getHensuu(int scene_id, int hensuu_id) {
	CS::instance()->enter(CS_LOAD_CS, "gamen2 makehensuu");
	volatile int ans = 0;
	Gamen2_event* e = 0;
	if (events_map.find(scene_id) != events_map.end()) {
		e = events[events_map.find(scene_id)->second];
		ans = e->getHensuu(hensuu_id);
	}

	CS::instance()->leave(CS_LOAD_CS, "gamen2 makehensuu");


	return ans;

}