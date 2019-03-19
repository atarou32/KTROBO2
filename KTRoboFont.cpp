#include "KTRoboFont.h"
#include "KTRoboGameError.h"
#include "stringconverter.h"

using namespace KTROBO;

Font::Font(void)
{
	font = 0;
	for(int i=0;i<MYFONT_TEXTURE_COUNT;i++) {
		fonttextures[i] = 0;
		fonttextureviews[i] = 0;
	}
}


Font::~Font(void)
{




	Release();

	
}

void Font::Draw(ID3D11Texture2D* tex) {



}


void Font::copyBufFromFont(UINT32** pData, char* buffer,int fsize, HDC hdc) {

	int temp = 0;
	UINT code = 0;
	int codecount = 0;
	int code_x = 0;
	int code_y = 0;
	int temp_texture_index = 0;
	char* c = &buffer[temp];
	WCHAR* onebytechars = L" 1234567890qwertyuiopasdfghjklzxcvbnmQWQERTYUIOPASDFGHJKLZXCVBNM!\"#$%&\'()=~|\\`@{[}]*:+;_?/>.<,-";
	int onebytecharslength = wcslen(onebytechars);
	int onebytecharscount=0;

	while ( temp < fsize) {

			if (onebytecharscount >= onebytecharslength) {
			char* c = &buffer[temp];
			//if(IsDBCSLeadByte((BYTE)*c)) {
		//	if ((BYTE)(*(c+1)) != 0xFF) {
			code = (BYTE)buffer[temp+1]<<8 | (BYTE)buffer[temp];
			//mylog::writelog("%d,%d,%d,\n",code,buffer[temp],buffer[temp+1]);
	
			temp = temp + 2;
			} else {
				code = onebytechars[onebytecharscount];
				onebytecharscount += 1;
			}
		//	} else {
		//		code = (BYTE)buffer[temp];
		//		temp = temp + 2;
		//	}

			// �t�H���g�r�b�g�}�b�v�擾
			TEXTMETRIC TM;
			GetTextMetrics( hdc, &TM );
			GLYPHMETRICS GM;
			CONST MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};
			DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
			BYTE *ptr = new BYTE[size];
		    GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

			// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������

		
			RECT rect;

			
			int texture_index = codecount /((MYFONT_TEXTURE_HEIGHT/MYFONT_FONTSIZE) * (MYFONT_TEXTURE_WIDTH/MYFONT_FONTSIZE));
			if (texture_index >= MYFONT_TEXTURE_COUNT-1) {
				delete[] ptr;
				delete[] buffer;
				throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "���K�t�H���g�������e�N�X�`���ɓ��肫��Ȃ�\n");
				
			}
			if (texture_index != temp_texture_index) {
				temp_texture_index = texture_index;
				code_x = 0;
				code_y = 0;
			}

			rect.left = code_x;
			rect.right = code_x + MYFONT_FONTSIZE;
			rect.top = code_y;
			rect.bottom = code_y + MYFONT_FONTSIZE;


			//hr = g->getDeviceContext()->Map(fonttextures[texture_index], 0, D3D11_MAP_WRITE, 0, &hMapR);
			D3D11_BOX box;
		
			UINT rowPtc=0;
			UINT depthPtc=0;
			memset(&box,0,sizeof(box));
			box.back = 1;
			box.front = 0;
			box.left = rect.left;
			box.right = rect.right;
			box.bottom = rect.bottom;
			box.top = rect.top;

			//font���̏�������
			 // iOfs_x, iOfs_y : �����o���ʒu(����)
			// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
			// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
			 int iOfs_x = GM.gmptGlyphOrigin.x;
			 int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
			 int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4))%4;
			 int iBmp_h = GM.gmBlackBoxY;
			 int Level = 17;
			 int x, y;
			 UINT32 Alpha, Color;
			 
			 rowPtc = 4 * ( iOfs_x +  GM.gmBlackBoxX);//* (iOfs_y+iBmp_h);
			 depthPtc = rowPtc;

			// pData = new UINT32[4096*4096];
			 //memset(pData,0x51,sizeof(UINT32)*4096*4096);
			 //FillMemory(LockedRect.pBits , LockedRect.Pitch * TM.tmHeight, 0);
			 
			 for(y=iOfs_y; y<iOfs_y+iBmp_h; y++) {
				for(x=iOfs_x; x<(int)(iOfs_x+GM.gmBlackBoxX); x++){
				   Alpha = (255 * ptr[x-iOfs_x + iBmp_w*(y-iOfs_y)]) / (Level-1);
				   if (Alpha ==0) {
					   Color = 0x00000000;//0x00FF0000;
				   } else {
				   Color = 0x00ffffff | (Alpha<<24);
				   }
				  // Color = 0xFF00FFFF;
				   BYTE* pBits = (BYTE*)pData[texture_index];
				   if (y <0 || x < 0){// || iOfs_x <0 || iOfs_y < 0 || GM.gmBlackBoxX <0 || iBmp_h < 0 ) {
					   continue;
				   }
				   memcpy(pBits + box.top*4096*4 + 4*box.right+ y*4096*4 + 4*x, &(Color), sizeof(BYTE)*4);
				}
			 }
			 
		//	 pData[depthPtc*4] = 0;
		

	
			
			
			
			/*
			if (FAILED(hr)) {
				delete[] ptr;
				delete[] buffer;
				delete[] pData;
				throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "�e�N�X�`�����b�N�������݂Ɏ��s");
			}*/

			
			
			 delete[] ptr;

			 fontindex.insert(std::make_pair(code,code_x + code_y * MYFONT_TEXTURE_WIDTH));
			 fonttexture_index.insert(std::make_pair(code, texture_index));



			 codecount = codecount + 1;
			 code_x = (code_x + MYFONT_FONTSIZE) % MYFONT_TEXTURE_WIDTH;
			 if (code_x ==0) {
				 code_y = code_y + MYFONT_FONTSIZE;
			 }

			

	}






}

void Font::copyBufToTexture(UINT32** pData, char* buffer) {
	
		D3D11_MAPPED_SUBRESOURCE hMapR;

		for (int i = 0;i<MYFONT_TEXTURE_COUNT;i++) {
		HRESULT	 hr = g->getDeviceContext()->Map(fonttextures[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &hMapR);
			 if (FAILED(hr)) {

		//		 	delete[] ptr;
				delete[] buffer;
				delete[] pData;
				throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "�t�H���gmap sippai\n");
			 }
			 BYTE* mapped_pData = (BYTE*)hMapR.pData;
			 BYTE* src = (BYTE*)pData[i];
			 size_t pt = MYFONT_TEXTURE_WIDTH*4;
			 for (UINT k = 0 ; k < MYFONT_TEXTURE_HEIGHT;k++) {
			 memcpy(mapped_pData, src,pt);
			 mapped_pData += hMapR.RowPitch;
			 src += pt;

			 }
			//g->getDeviceContext()->UpdateSubresource(fonttextures[texture_index],0,0/*&box*/,&pData,rowPtc,0);//depthPtc);
			g->getDeviceContext()->Unmap(fonttextures[i],0);
		
		}

}

void Font::Init(char* filename, char* fontname, KTROBO::Graphics* g) {

	
	this->g = g;

	HRESULT hr;

	for (int i=0;i<MYFONT_TEXTURE_COUNT;i++) {

		D3D11_TEXTURE2D_DESC desc;
		memset( &desc, 0, sizeof(desc));
		desc.Width = MYFONT_TEXTURE_WIDTH;
		desc.Height = MYFONT_TEXTURE_HEIGHT;
		desc.MipLevels  = 1;//D3DX11_DEFAULT;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;//16;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ID3D11Resource* text;
		ID3D11Texture2D* tex2D;
		//hr = D3DX11CreateTextureFromFileW(g->getDevice(), L"resrc/sample/title-74.JPG", NULL,NULL, &text, NULL);
	//	tex2D = static_cast<ID3D11Texture2D*>(text);
		hr = g->getDevice()->CreateTexture2D(&desc,0,&tex2D);
		if (FAILED(hr)) {
			Release();
			throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "failed in create texture: ktrobofont");
		}

		
		// view ���쐬����
	/*	D3D11_SHADER_RESOURCE_VIEW_DESC srcDesc;
		memset(&srcDesc,0,sizeof(srcDesc));
		srcDesc.Format = desc.Format;
		srcDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srcDesc.Texture2D.MostDetailedMip = 0;
		srcDesc.Texture2D.MipLevels = desc.MipLevels;
		hr = g->getDevice()->CreateShaderResourceView(tex2D, &srcDesc, &fonttextureviews[i]);
		if (FAILED(hr)) {
			char buf[1024];
			memset(buf,0,1024);
			tex2D->Release();
			sprintf_s(buf,512,"font �e�N�X�`���ǂݍ��݂Ɏ��s");
			Release();
			throw new KTROBO::GameError(KTROBO::FATAL_ERROR, buf);
		}
		*/
		fonttextures[i] = tex2D;
		/*
		hr = D3DXCreateTexture(device,MYFONT_TEXTURE_WIDTH,MYFONT_TEXTURE_HEIGHT,1,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&this->fonttextures[i]);
		if (FAILED(hr)) {
			mylog::writelog("�t�H���g�̃e�N�X�`���쐬�Ɏ��s");
			return;
		}
		*/
	}

	// �t�H���g�̐���
   int fontsize = MYFONT_FONTSIZE;
   stringconverter sc;

//   LOGFONT lf = {fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
 //  CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("�������t�H���gL")};
 //  if(!(font = CreateFontIndirect(&lf))){
  
   WCHAR buf[512];
   sc.charToWCHAR(filename,buf);
   if (AddFontResourceEx(buf,FR_PRIVATE,NULL) >0) {
   } else {
	   throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "�t�H���g�̃��\�[�X��������̂Ɏ��s");
   }

   sc.charToWCHAR(fontname, buf);
   if (!(font = CreateFont(fontsize,0,0,0,0,FALSE,FALSE,FALSE,SHIFTJIS_CHARSET,OUT_TT_ONLY_PRECIS,CLIP_DEFAULT_PRECIS,
   PROOF_QUALITY, FIXED_PITCH | FF_MODERN, buf))) {
	   throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "�t�H���g�̐����Ɏ��s");
   }

   

	
	FILE* fp;
	errno_t t = fopen_s(&fp, MYFONT_KANJI_TXT, "rb");
	if (t != 0) {
		char buf[1024];
		memset(buf,0,1024);
		sprintf_s(buf,512, "myfont kanji_all_error errcode=%d",t);
		throw new KTROBO::GameError(KTROBO::FATAL_ERROR, buf);
	}
		/* �t�@�C���T�C�Y�𒲍� */
	fpos_t fsize;
	fpos_t fsize_all=0;
	fseek(fp,0,SEEK_END); 
	fgetpos(fp,&fsize);
	//mylog::writelog("fsizedayo:%d fsize_all=%d\n",(int)fsize,(int)fsize_all);
	if (fsize > 10000000 || fsize == 0) {
		fclose(fp);
		char buf[1024];
		memset(buf,0,1024);
		sprintf_s(buf,512, "kanji_all�͑傫������ �܂��͂�����������@%d",fsize);
		throw new KTROBO::GameError(KTROBO::FATAL_ERROR, buf);
		
	}
	char* buffer=new char[(unsigned int)fsize+1];
	fseek(fp,0,SEEK_SET);
	//buffer[fsize]='\0';
	size_t readsize=0;
	while (fsize_all < fsize) {
		if (readsize > fsize - fsize_all) {

			fclose(fp);
			char buf[1024];
			memset(buf,0,1024);
			sprintf_s(buf,512, "%s ��kanji_all�̓ǂݍ��݂ŕs� %d %d",filename,readsize,fsize);
			
			delete[] buffer;
			throw new KTROBO::GameError(KTROBO::FATAL_ERROR, buf);
		}

		readsize = fread_s(&buffer[fsize_all],(size_t)(fsize-fsize_all),1,(size_t)(fsize-fsize_all),fp);
		fsize_all = readsize + fsize_all;
		fseek(fp,(long)fsize_all,SEEK_SET);
		//mylog::writelog("%d:size %d:readsize %d:fsize\n",(int)fsize_all,(int)readsize,(int)fsize);
	}
	buffer[fsize]='\0';
	fclose(fp);
	
	
	
	
	  // �f�o�C�X�R���e�L�X�g�擾
   // �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
   HDC hdc = GetDC(NULL);
   HFONT oldFont = (HFONT)SelectObject(hdc, font);
   bool is=false;
   // �����R�[�h�擾
/*   TCHAR *c = _T("��");
   UINT code = 0;
#if _UNICODE
   // unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
     code = (UINT)*c;
#else
   // �}���`�o�C�g�����̏ꍇ�A
   // 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
   // 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
   if(IsDBCSLeadByte(*c))
      code = (BYTE)c[0]<<8 | (BYTE)c[1];
   else
      code = c[0];
#endif
	  */
 


	
	
	
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
	







   UINT32* pData[MYFONT_TEXTURE_COUNT];

	
		


	for (int i=0;i<MYFONT_TEXTURE_COUNT;i++) {
		pData[i] = new UINT32[MYFONT_TEXTURE_WIDTH*MYFONT_TEXTURE_HEIGHT];
		memset(pData[i],0x00,sizeof(UINT32)*MYFONT_TEXTURE_WIDTH*MYFONT_TEXTURE_HEIGHT);
	}
	
	this->copyBufFromFont(pData,buffer,fsize,hdc);
	this->copyBufToTexture(pData,buffer);
	
	for (int i = 0;i<MYFONT_TEXTURE_COUNT;i++) {
	
		delete[] pData[i];
	}

	
   // �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
   SelectObject(hdc, oldFont);
   DeleteObject(font);
   font = 0;
   ReleaseDC(NULL, hdc);
   delete[] buffer;

   WCHAR bu[512];
   sc.charToWCHAR(filename,bu);
   if (RemoveFontResourceEx(bu,FR_PRIVATE, NULL) > 0) {
   }else {
	   throw new KTROBO::GameError(KTROBO::FATAL_ERROR,"�t�H���g�̃��\�[�X�J���Ɏ��s");
	   return;
   }





   
	for (int i=0;i<MYFONT_TEXTURE_COUNT;i++) {

		D3D11_TEXTURE2D_DESC desc;
		/*memset( &desc, 0, sizeof(desc));
		desc.Width = MYFONT_TEXTURE_WIDTH;
		desc.Height = MYFONT_TEXTURE_HEIGHT;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;//DYNAMIC;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE;

		ID3D11Texture2D* tex2D;
		hr = g->getDevice()->CreateTexture2D(&desc,0,&tex2D);
		if (FAILED(hr)) {
			Release();
			throw new KTROBO::GameError(KTROBO::FATAL_ERROR, "failed in create texture: ktrobofont");
		}*/

		fonttextures[i]->GetDesc(&desc);
		// view ���쐬����
		D3D11_SHADER_RESOURCE_VIEW_DESC srcDesc;
		memset(&srcDesc,0,sizeof(srcDesc));
		srcDesc.Format = desc.Format;
		srcDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srcDesc.Texture2D.MostDetailedMip = 0;
		srcDesc.Texture2D.MipLevels = desc.MipLevels;
		hr = g->getDevice()->CreateShaderResourceView(fonttextures[i], &srcDesc, &fonttextureviews[i]);
		if (FAILED(hr)) {
			char buf[1024];
			memset(buf,0,1024);
			//tex2D->Release();
			sprintf_s(buf,512,"font �e�N�X�`���ǂݍ��݂Ɏ��s");
			Release();
			throw new KTROBO::GameError(KTROBO::FATAL_ERROR, buf);
		}
		
		//fonttextures[i] = tex2D;
		/*
		hr = D3DXCreateTexture(device,MYFONT_TEXTURE_WIDTH,MYFONT_TEXTURE_HEIGHT,1,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&this->fonttextures[i]);
		if (FAILED(hr)) {
			mylog::writelog("�t�H���g�̃e�N�X�`���쐬�Ɏ��s");
			return;
		}
		*/
	}


  
   return;
 
}

void Font::Release() {

	for(int i=0;i<MYFONT_TEXTURE_COUNT;i++) {
		if (fonttextures[i]) {
			fonttextures[i]->Release();
			fonttextures[i] = 0;
		}
		if (fonttextureviews[i]) {
			fonttextureviews[i]->Release();
			fonttextureviews[i] = 0;
		}
	}
}
