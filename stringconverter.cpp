#include "stringconverter.h"
#include "KTRoboLog.h"

stringconverter::stringconverter(void)
{
}


stringconverter::~stringconverter(void)
{
}

/*
WCHAR* stringconverter::charTowchar(const char* filename) {

	static WCHAR ans[512];
	memset(ans,0,sizeof(WCHAR)*512);
	size_t wLen = 0;
	errno_t err = 0;
	setlocale(LC_ALL,"japanese");
	err = mbstowcs_s(&wLen,ans,filename,_TRUNCATE);
	if (err != 0) {
		mylog::writelog("%s ��wchar�ϊ��Ɏ��s",filename);
		return NULL;
	}
	return ans;
}

*/

void stringconverter::charToWCHAR(const char* filename, WCHAR* ans) {

	WCHAR ans2[512];
	memset(ans2,0,sizeof(WCHAR)*511);
	size_t wLen = 0;
	errno_t err = 0;
	setlocale(LC_ALL,"japanese");
	err = mbstowcs_s(&wLen,ans2,filename,_TRUNCATE);
	if (err != 0) {
		KTROBO::mylog::writelog(KTROBO::WARNING,"%s ��wchar�ϊ��Ɏ��s",filename);
		return;
	}

	wcscpy_s(ans,511,ans2);
	return;
}
char* stringconverter::wcharTochar(const WCHAR* filename, char* buf) {
	char ans[512];
	memset(ans,0,511);
	size_t wLen = 0;
	errno_t err = 0;
	setlocale(LC_ALL,"japanese");
	err = wcstombs_s(&wLen, ans,filename,_TRUNCATE);
	if (err != 0) {
		KTROBO::mylog::writelog(KTROBO::WARNING,"%s ��char�ϊ��Ɏ��s",filename);
		return NULL;
	}
	memcpy(buf,ans,strlen(ans));
	return buf;
}

bool stringconverter::Utf8ToUtf16(wchar_t *dest, size_t dest_size, const char *src, size_t src_size)
{
                                /**/
    UINT    uCodePage;          /* �R�[�h�y�[�W */
    DWORD   dwFlags;            /* �������\�ƃ}�b�s���O�̃t���O */
    LPCSTR  lpMultiByteStr;     /* �V����������̃o�b�t�@�̃A�h���X */
    int     cchMultiByte;       /* �o�b�t�@�̃T�C�Y */
    LPWSTR  lpWideCharStr;      /* ���C�h�����̕�����̃A�h���X */
    int     cchWideChar;        /* ������̕����� */
    int     iResult = 0;
    
    uCodePage       = CP_UTF8;
    dwFlags         = 0;
    lpMultiByteStr  = src;
    cchMultiByte    = src_size;
    lpWideCharStr   = dest;
    cchWideChar     = dest_size;
    iResult = MultiByteToWideChar(uCodePage, dwFlags, lpMultiByteStr
            , cchMultiByte, lpWideCharStr, cchWideChar);
    return iResult;
}