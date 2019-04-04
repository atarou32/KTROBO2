#ifndef KTROBOMESSAGE_H
#define KTROBOMESSAGE_H

#pragma once
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "tolua_glue/MyLuaGlueMakeCommon.h"
#include "vector"
#include "MyDefine.h"

using namespace std;
namespace KTROBO {

class MyMStruct {
public:
	int msg_id;
	int sender_id;
	int receiver_id;
	int msg;
	float fmsg;
	bool is_use;
	bool is_need_to_send;
	MyMStruct() {
		msg_id = 0;
		sender_id = 0;
		receiver_id = 0;
		msg = 0;
		fmsg = 0;
		is_use = false;
		is_need_to_send = false;
	}
};
#define KTROBO_MESSAGE_MYMSTRUCT_SIZE 128
#define KTROBO_MESSAGE_ID_ANIMATIONBUILDER_BONE_PUSHED 1
#define KTROBO_MESSAGE_ID_ANIMATIONBUILDER_HON_MESH_AFTER 2
#define KTROBO_MESSAGE_ID_ACTIONEDITOR_LOAD_AFTER 3
#define KTROBO_MESSAGE_ID_GARAGE_SHOP_BUY_PARTS 4
#define KTROBO_MESSAGE_ID_GARAGE_ASSEMBLE_PARTS 5
#define KTROBO_MESSAGE_ID_GARAGE_ASSEMBLE_ERROR_TO_LUA 6
#define KTROBO_MESSAGE_ID_GARAGE_ASMSAVELOAD_SAVELOAD 7

// sender_id g_index msg 
#define KTROBO_MESSAGE_MSG_GARAGE_SHOP_BUY_PARTS 0
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_EQUIP_PARTS 0
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_PURGE_PARTS 1
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_SELL_PARTS 2
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_PURGE_FAILED 0
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_SELL_FAILED_USED_IN_ASM 1
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_SELL_FAILED_NO_ITEM 2
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_EQUIP_FAILED_NO_ITEM 3
#define KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_EQUIP_FAILED 4



#define KTROBO_MESSAGE_RECEIVER_ID_SYSTEM 0
#define KTROBO_MESSAGE_SENDER_ID_SYSTEM 0

interface IMessage {
public:
	TO_LUA virtual void makeMessage(int msg_id, int sender_id, int receiver_id, int msg, float fmsg, bool is_need_to_send)=0;
	TO_LUA virtual int getMessageIndexsFromMsgId(int msg_id, OUT_ int* get_msgs)=0;// TEMPHAIRETU_SIZE �܂ł����Ƃ�Ȃ�
	TO_LUA virtual int getMessageIndexsFromReceiverId(int receiver_id, OUT_ int* get_msgs)=0;
	TO_LUA virtual void getMsgBody(int mindex_len, int* msg_indexs, OUT_ int* msg_ids, OUT_ int* sender_ids, OUT_ int* receiver_ids, OUT_ int* msgs, OUT_ float* fmsgs)=0;// msgs�͗v�f��32�ȉ��̔z��ɂ��邱�� msgbody��ǂ񂾏u�ԂɃ��b�Z�[�W�͏��������
};
class Message : public IMessage
{
private:
	MyMStruct structs[KTROBO_MESSAGE_MYMSTRUCT_SIZE];
public:
	Message(void);
	~Message(void);
	void makeMessage(int msg_id, int sender_id, int receiver_id, int msg, float fmsg, bool is_need_to_send);
	int getMessageIndexsFromMsgId(int msg_idm, OUT_ int* get_msgs);
	int getMessageIndexsFromReceiverId(int receiver_id, OUT_ int* get_msgs);
	void getMsgBody(int mindex_len, int* msg_indexs, OUT_ int* msg_ids, OUT_ int* sender_ids, OUT_ int* receiver_ids, OUT_ int* msgs, OUT_ float* fmsgs);// msgs�͗v�f��32�ȉ��̔z��ɂ��邱��
};

class Messages {
	
private:
	vector<Message*> messages;
public:
	int makeInst();
	

	Message* getInstance(int index);

	IMessage* getInterface(int index);

	Messages() {}
	~Messages() {
		Release();
	}

	void Release() {
		int size = messages.size();
		for (int i= 0; i<size;i++) {
			delete messages[i];
			messages[i] = 0;
		}
		messages.clear();
	}
};

}

#endif