#ifndef KTROBO_LOADABLE_H
#define KTROBO_LOADABLE_H

#pragma once

namespace KTROBO {
class Loadable2
{
private:
	volatile bool is_loaded;
	volatile bool is_loaded_only_for_thread; //�@���[�v���񂷃X���b�h�͂ЂƂ����ƍl����
	volatile unsigned int thread_id_for_is_loaded;

public:
	Loadable2();
	~Loadable2();
private:

	bool getIsLoaded();

	void setLoopThread();
	bool getIsLoadedForLoopThread();
	void setLoadedForLoopThread();

protected:

	void setLoaded();
public:
	bool hasLoaded(); // ���[�v���񂷃X���b�h�ŌĂ�
};

/*

  class test : public Loadable {
     void funcload();
	 void funcrender();
  };

  function funcload() {
     
	 loadsomething();
	 setLoaded();

  }
  function funcrender() {
     if (getIsLoadedForLoopThread()) {
	    
     } else {
	    if (getIsLoaded()) {
		    setLoadedForLoopThread();
        } else {
		  return;
		}
     }
	 render();
  }



*/
}
#endif