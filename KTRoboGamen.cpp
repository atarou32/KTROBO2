#include "KTRoboGamen.h"
using namespace KTROBO;

Gamen::Gamen(void)
{
}


Gamen::~Gamen(void)
{
}


void KoumokuList::clicked(Gamen* gamen, GamenPart* gp, int mouse_x, int mouse_y) {
	if (!is_enable) return;
	vector<Koumoku*>::iterator it = koumokus.begin();
	while(it != koumokus.end()) {
		Koumoku* k = *it;
		if (k->clicked(mouse_x, mouse_y)) {
			setFocusedKoumoku(k,getCursorIndex(k));
		
			k->clickedExe(gamen, gp, this);
			cursor = this->getCursorIndex(k);
			setHasClicked(true);
			return;
		}
		it++;
	}
}

void KoumokuList::clickedEnter(Gamen* gamen, GamenPart* gp) {
	if (!is_enable) return;
	if (focused_koumoku) {
		focused_koumoku->clickedExe(gamen, gp, this);
	}
}
void KoumokuList::clickedUp() {
	if (!is_enable) return;
	this->cursor--;

	int size = koumokus.size();
	if (size && (cursor < 0 )) {
		cursor = size-1;
	}
	if (size) {

	setFocusedKoumoku(koumokus[cursor],cursor);
	if (!focused_koumoku->getEnabled() && this->hasEnabledKoumoku()) {
		clickedUp();
	}
	}

}


void KoumokuList::setFocusedKoumokuHyouji3Mode(Koumoku* kk,int index) {
	// �אڂ������ڈȊO�̍��ڂ�disable and disvisible
	if (!hyouji3_mode) return;
	int size = koumokus.size();

	int mae_index = index-1;
	int ato_index= index+1;
	if (mae_index < 0) {
		mae_index = size-1;
	}
	if (ato_index >= size) {
		ato_index = 0;
	}

	this->setVisible(t,false);
	this->setEnable(false);
	is_visible = true;
	koumokus[mae_index]->setVisible(t,true);
	koumokus[ato_index]->setVisible(t,true);
	kk->setVisible(t,true);
	is_enable = true;
	koumokus[mae_index]->setEnabled(true);
	koumokus[ato_index]->setEnabled(true);
	kk->setEnabled(true);




	// �אڂ������ڂ�enable and visible

	// �אڂ������ڂ̕\���ʒu�����炷
	if (koumokus.size()) {
		float dsize = (place.bottom - place.top)/koumokus.size();
		kk->setSize(t,place.left,place.top + dsize,place.right - place.left , dsize);
		koumokus[mae_index]->setSize(t,place.left + 30, place.top, place.right-place.left, dsize);
		koumokus[ato_index]->setSize(t,place.left + 30, place.top+dsize*2, place.right-place.left, dsize);
	}
}

void KoumokuList::clickedDown() {
	if (!is_enable) return;
	int size = koumokus.size();
	if (size) {
		cursor++;
		if (size <= cursor) {
			cursor = 0;
		}

		setFocusedKoumoku(koumokus[cursor],cursor);
		if (!focused_koumoku->getEnabled() && this->hasEnabledKoumoku()) {
			clickedDown();
		}
		
	}


}
void KoumokuList::moved(int mouse_x, int mouse_y) {
	if (!is_enable) return;
	int size = koumokus.size();
	for (int i =0;i<size;i++) {
		Koumoku* k = koumokus[i];
		if (k->moved(mouse_x, mouse_y)) {
			cursor = i;
			focused_koumoku = k;
			setFocusedKoumokuHyouji3Mode(focused_koumoku,cursor);
			return;
		}
	}
}

void KoumokuList::setVisible(Texture* t, bool tt) {
	is_visible = tt;
	int size = koumokus.size();
	for (int i=0;i<size;i++) {
		koumokus[i]->setVisible(t,tt);
	}

}

void KoumokuList::setEnable(bool t) {
	is_enable = t;

	int size = koumokus.size();
	for (int i=0;i<size;i++) {
		koumokus[i]->setEnabled(t);
	}

}


KoumokuList::~KoumokuList(){
		if (koumokus.size()) {
		vector<Koumoku*>::iterator it = koumokus.begin();
		while(it != koumokus.end()) {
			Koumoku* k = *it;
			
			delete k;
			k = 0;

			it++;
		}
		koumokus.clear();
		}
};

void KoumokuList::setEnableKoumoku(int index) {
	if (!is_enable) return;
	int size = koumokus.size();
	if ((index > 0) && (size > index)) {
		koumokus[index]->setEnabled(true);
	}
}
void KoumokuList::setDisableKoumoku(int index) {
	if (!is_enable) return;
	int size = koumokus.size();
	if ((index > 0) && (size > index)) {
		koumokus[index]->setEnabled(false);
	}

}

void KoumokuList::setSize(Texture* t, int x, int y, int width, int height) {
	place.left = x;
	place.top = y;
	place.right = x + width;
	place.bottom = y + height;
	// ���ڂ�����ꍇ�͂��̃T�C�Y���ݒ肷��
	int size = koumokus.size();
	if (size) {
		float dheight = height / (float)size;

		for (int i = 0 ; i<size;i++) {
			koumokus[i]->setSize(t, x,y + dheight * i , width, dheight);
		}
	}
}

void KoumokuList::byouga(Graphics* g, GUI* gui, float dsecond, int stamp) {
	if (!is_visible) return;

	int size = koumokus.size();


	for (int i=0;i<size;i++) {
		Koumoku* k  = koumokus[i];
		k->byouga(g,gui,dsecond,stamp,getHasClicked());
	}

	if (focused_koumoku) {
		focused_koumoku->focusedByouga(g,gui,dsecond, stamp,getHasClicked());
	}

	if (getHasClicked()) {
		setHasClicked(false);
	}
}





bool Koumoku::clicked(int mouse_x, int mouse_y) {
	if (!is_enable) return false;
	if (getButukariStatusPoint(mouse_x,mouse_y, &place) & BUTUKARIPOINT_IN) {
		return true;
	}
	return false;
}

bool Koumoku::moved(int mouse_x, int mouse_y) {
	if (!is_enable) return false;
	if (getButukariStatusPoint(mouse_x,mouse_y, &place) & BUTUKARIPOINT_IN) {
		return true;
	}
	return false;
}

void Koumoku::setEnabled(bool t) {
	this->is_enable = t;
}

void Koumoku::setSize(Texture* t,int x, int y, int width, int height) {
	place.left = x;
	place.right = x + width;
	place.top = y;
	place.bottom = y + height;

	t->setRenderTextPos(gui_koumoku_name_id,x,y);
	t->setRenderTexPos(gui_koumoku_name_bg_id,x,y);
	t->setRenderTexWH(gui_koumoku_name_bg_id,width,height);


}

int Koumoku::getID() {
	return clicked_id;
}


void Koumoku::clickedExe(Gamen* gamen, GamenPart* gp, KoumokuList* kl) { // set_enable ��false �̂Ƃ��̓��^�[�����邱�� 
	if (!this->getEnabled()) return;
	if (kl->getHyouji3Mode()) {
		int temp = kl->getCursorIndex(this);
		int cursor = kl->getCursor();
		if (cursor == kl->getKoumokuSize()-1) {
			if (cursor == temp) {
				_exedayo(gamen,gp,kl);
			} else {
				if (temp == 0) {
					kl->clickedDown();
				} else {
					kl->clickedUp();
				}
			}
		} else if(cursor == 0) {
			if (temp == cursor) {
				_exedayo(gamen,gp,kl);
			} else {
				if (temp == 1) {
					kl->clickedDown();
				} else {
					kl->clickedUp();
				}
			}
		}else {

		if (cursor > temp) {
			kl->clickedUp();
		} else if(cursor < temp) {
			
			kl->clickedDown();
			
		} else {
			// ����������
			_exedayo(gamen,gp,kl);
		}
		}
	} else {

		// ����������
		_exedayo(gamen,gp,kl);
	}
}