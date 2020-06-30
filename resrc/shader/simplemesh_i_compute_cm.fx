sampler sdayo : register(s0);

sampler decalSmp {
  	Filter = MIN_MAG_MAP_POINT;//MIN_MAG_MIP_LINEAR;
  	AddressU = WRAP;
  	AddressV = WRAP;
  	AddressW = WRAP;
  	ComparisonFunc = NEVER;
  	MinLOD = 0;
  	MaxLOD = FLOAT32_MAX;
};


column_major float4x4 MyMatrixTranspose(float4x4 test) {
float4x4 a = test;
float4x4 ans;
ans._11 = a._11;
ans._12 = a._21;
ans._13 = a._31;
ans._14 = a._41;
ans._21 = a._12;
ans._22 = a._22;
ans._23 = a._32;
ans._24 = a._42;
ans._31 = a._13;
ans._32 = a._23;
ans._33 = a._33;
ans._34 = a._43;
ans._41 = a._14;
ans._42 = a._24;
ans._43 = a._34;
ans._44 = a._44;
return ans;
}

column_major float4x4 MyMatrixIdentity() {
	column_major float4x4 t;
	t = 0;
	t._11 = 1;t._22 = 1;t._33 =1; t._44 = 1;
	return t;
}

column_major float4x4 MyMatrixTranslation(float x, float y, float z) {
	column_major float4x4 ans = MyMatrixIdentity();
	ans._41 = x;
	ans._42 = y;
	ans._43 = z;
	return ans;
}


column_major float4x4 MyMatrixRotationX(float a) {
column_major float4x4 ans=(float4x4)0;
ans._11 = 1;
ans._44 = 1;
ans._22 = cos(a);
ans._32 = -sin(a);
ans._23 = sin(a);
ans._33 = cos(a);
return ans;
}

column_major float4x4 MyMatrixRotationZ(float a) {
column_major float4x4 ans=(float4x4)0;
ans._11 = cos(a);
ans._12 = sin(a);
ans._21 = -sin(a);
ans._44 = 1;
ans._22 = cos(a);
ans._33 = 1;
return ans;
}




column_major float4x4 MyMatrixMultiply2(float4x4 a, float4x4 b) {

	column_major float4x4 ans;
	ans._11 = a._11 * b._11 + a._12 * b._21 + a._13 * b._31 + a._14 * b._41;
	ans._12 = a._11 * b._12 + a._12 * b._22 + a._13 * b._32 + a._14 * b._42;
	ans._13 = a._11 * b._13 + a._12 * b._23 + a._13 * b._33 + a._14 * b._43;
	ans._14 = a._11 * b._14 + a._12 * b._24 + a._13 * b._34 + a._14 * b._44;

	ans._21 = a._21 * b._11 + a._22 * b._21 + a._23 * b._31 + a._24 * b._41;
	ans._22 = a._21 * b._12 + a._22 * b._22 + a._23 * b._32 + a._24 * b._42;
	ans._23 = a._21 * b._13 + a._22 * b._23 + a._23 * b._33 + a._24 * b._43;
	ans._24 = a._21 * b._14 + a._22 * b._24 + a._23 * b._34 + a._24 * b._44;

	ans._31 = a._31 * b._11 + a._32 * b._21 + a._33 * b._31 + a._34 * b._41;
	ans._32 = a._31 * b._12 + a._32 * b._22 + a._33 * b._32 + a._34 * b._42;
	ans._33 = a._31 * b._13 + a._32 * b._23 + a._33 * b._33 + a._34 * b._43;
	ans._34 = a._31 * b._14 + a._32 * b._24 + a._33 * b._34 + a._34 * b._44;

	ans._41 = a._41 * b._11 + a._42 * b._21 + a._43 * b._31 + a._44 * b._41;
	ans._42 = a._41 * b._12 + a._42 * b._22 + a._43 * b._32 + a._44 * b._42;
	ans._43 = a._41 * b._13 + a._42 * b._23 + a._43 * b._33 + a._44 * b._43;
	ans._44 = a._41 * b._14 + a._42 * b._24 + a._43 * b._34 + a._44 * b._44;

	return ans;
}

column_major float4x4 MyMatrixMultiply(float4x4 a, float4x4 b) {
return MyMatrixMultiply2(b,a);
}

column_major float4x4 MyMatrixInverse(float4x4 mat) {

	float detA = mat._11 * mat._22 * mat._33 * mat._44 + mat._11 * mat._23 * mat._34 * mat._42 + mat._11 * mat._24 * mat._32 * mat._43 +
		mat._12 * mat._21 * mat._34 * mat._43 + mat._12 * mat._23 * mat._31 * mat._44 + mat._12 * mat._24 * mat._33 * mat._41 +
		mat._13 * mat._21 * mat._32 * mat._44 + mat._13 * mat._22 * mat._34 * mat._41 + mat._13 * mat._24 * mat._31 * mat._42 +
		mat._14 * mat._21 * mat._33 * mat._42 + mat._14 * mat._22 * mat._31 * mat._43 + mat._14 * mat._23 * mat._32 * mat._41 -
		mat._11 * mat._22 * mat._34 * mat._43 - mat._11 * mat._23 * mat._32 * mat._44 - mat._11 * mat._24 * mat._33 * mat._42 -
		mat._12 * mat._21 * mat._33 * mat._44 - mat._12 * mat._23 * mat._34 * mat._41 - mat._12 * mat._24 * mat._31 * mat._43 -
		mat._13 * mat._21 * mat._34 * mat._42 - mat._13 * mat._22 * mat._31 * mat._44 - mat._13 * mat._24 * mat._32 * mat._41 -
		mat._14 * mat._21 * mat._32 * mat._43 - mat._14 * mat._22 * mat._33 * mat._41 - mat._14 * mat._23 * mat._31 * mat._42;

	if (detA == 0 ) {
		detA = 1;
	}
	/*
	float b11 = mat._22 * mat._33 * mat._44 + 
		mat._23 * mat._34 * mat._42 +
		mat._24 * mat._32 * mat._43 -
		mat._22 * mat._34 * mat._43 -
		mat._23 * mat._32 * mat._44 -
		mat._24 * mat._33 * mat._42;

	float b12 = mat._12 * mat._34 * mat._43 +
		mat._13 * mat._32 * mat._44 +
		mat._14 * mat._33 * mat._42 -
		mat._12 * mat._33 * mat._44 -
		mat._13 * mat._34 * mat._42 -
		mat._14 * mat._32 * mat._43;

	float b13 = mat._12 * mat._23 * mat._44 +
		mat._13 * mat._24* mat._42 +
		mat._14 * mat._22 * mat._43 -
		mat._12 * mat._24 * mat._43 - 
		mat._13 * mat._22 * mat._44 -
		mat._14 * mat._23 * mat._42;

	float b14 = mat._12 * mat._24 * mat._33 +
		mat._13 * mat._22 * mat._34 +
		+mat._14 * mat._23 * mat._32-
		mat._12 * mat._23 * mat._34 -
		mat._13 * mat._24 * mat._32 - 
		mat._14 * mat._22 * mat._33;

	float b21 = mat._21 * mat._34 * mat._43 +
		mat._23 * mat._31 * mat._44 +
		mat._24 * mat._33 * mat._41 -
		mat._21 * mat._33 * mat._44 -
		mat._23 * mat._34 * mat._41 -
		mat._24 * mat._31 * mat._43;

	float b22 = mat._11 * mat._33 * mat._44 +
		mat._13 * mat._34 * mat._41 +
		mat._14 * mat._31 * mat._43 -
		mat._11 * mat._34 * mat._43 -
		mat._13 * mat._31 * mat._44 -
		mat._14 * mat._33 * mat._41;

	float b23 = mat._11 * mat._24 * mat._43 +
		mat._13 * mat._21 * mat._44 +
		mat._14 * mat._23 * mat._41 -
		mat._11 * mat._23 * mat._44 -
		mat._13 * mat._24 * mat._41 -
		mat._14 * mat._21 * mat._43;

	float b24 = mat._11 * mat._23 * mat._34 +
		mat._13 * mat._24 * mat._31 +
		mat._14 * mat._21 * mat._33 -
		mat._11 * mat._24 * mat._33 -
		mat._13 * mat._21 * mat._34 -
		mat._14 * mat._23 * mat._31;

	float b31 = mat._21 * mat._32 * mat._44 +
		mat._22 * mat._34 * mat._41 +
		mat._24 * mat._31* mat._42 -
		mat._21 * mat._34 * mat._42 -
		mat._22 * mat._31 * mat._44 -
		mat._24 * mat._32 * mat._41;

	float b32 = mat._11 * mat._34 * mat._42 +
		mat._12 * mat._31 * mat._44 +
		mat._14 * mat._32 * mat._41 -
		mat._11 * mat._32 * mat._44 -
		mat._12 * mat._34 * mat._41 -
		mat._14 * mat._31 * mat._42;

	float b33 = mat._11 * mat._22 * mat._44 +
		mat._12 * mat._24 * mat._41 +
		mat._14 * mat._21 * mat._42 -
		mat._11 * mat._24 * mat._42 -
		mat._12 * mat._21 * mat._44 -
		mat._14 * mat._22 * mat._41;

	float b34 = mat._11 * mat._24 * mat._32 +
		mat._12 * mat._21 * mat._34 +
		mat._14 * mat._22 * mat._31 -
		mat._11 * mat._22 * mat._34 -
		mat._12 * mat._24 * mat._31 -
		mat._14 * mat._21 * mat._32;

	float b41 = mat._21 * mat._33 * mat._42 +
		mat._22 * mat._31 * mat._43 +
		mat._23 * mat._32 * mat._41 -
		mat._21 * mat._32 * mat._43 -
		mat._22 * mat._33 * mat._41 -
		mat._23 * mat._31 * mat._42;

	float b42 = mat._11 * mat._32 * mat._43 +
		mat._12 * mat._33 * mat._41 +
		mat._13 * mat._31 * mat._42 -
		mat._11 * mat._33 * mat._42 -
		mat._12 * mat._31 * mat._43 -
		mat._13 * mat._32 * mat._41;

	float b43 = mat._11 * mat._23 * mat._42 +
		mat._12 * mat._21 * mat._43 +
		mat._13 * mat._22 * mat._41 -
		mat._11 * mat._22 * mat._43 -
		mat._12 * mat._23 * mat._41 -
		mat._13 * mat._21 * mat._42;

	float b44 = mat._11 * mat._22 * mat._33 +
		mat._12 * mat._23 * mat._31 +
		mat._13 * mat._21 * mat._32 -
		mat._11 * mat._23 * mat._32 -
		mat._12 * mat._21 * mat._33 -
		mat._13 * mat._22 * mat._31;
		*/
			
	float4x4 ans;
	float b11 = mat._22 * mat._33 * mat._44 + 
		mat._23 * mat._34 * mat._42 +
		mat._24 * mat._32 * mat._43 -
		mat._22 * mat._34 * mat._43 -
		mat._23 * mat._32 * mat._44 -
		mat._24 * mat._33 * mat._42;
	ans._11 = b11 /detA;
	b11 = mat._12 * mat._34 * mat._43 +
		mat._13 * mat._32 * mat._44 +
		mat._14 * mat._33 * mat._42 -
		mat._12 * mat._33 * mat._44 -
		mat._13 * mat._34 * mat._42 -
		mat._14 * mat._32 * mat._43;
	ans._12 = b11 /detA;
	b11 = mat._12 * mat._23 * mat._44 +
		mat._13 * mat._24* mat._42 +
		mat._14 * mat._22 * mat._43 -
		mat._12 * mat._24 * mat._43 - 
		mat._13 * mat._22 * mat._44 -
		mat._14 * mat._23 * mat._42;
	ans._13 = b11 /detA;
	b11 = mat._12 * mat._24 * mat._33 +
		mat._13 * mat._22 * mat._34 +
		mat._14 * mat._23 * mat._32-
		mat._12 * mat._23 * mat._34 -
		mat._13 * mat._24 * mat._32 - 
		mat._14 * mat._22 * mat._33;
	ans._14 = b11 /detA;
	b11 = mat._21 * mat._34 * mat._43 +
		mat._23 * mat._31 * mat._44 +
		mat._24 * mat._33 * mat._41 -
		mat._21 * mat._33 * mat._44 -
		mat._23 * mat._34 * mat._41 -
		mat._24 * mat._31 * mat._43;
	ans._21 = b11 /detA;
	b11 = mat._11 * mat._33 * mat._44 +
		mat._13 * mat._34 * mat._41 +
		mat._14 * mat._31 * mat._43 -
		mat._11 * mat._34 * mat._43 -
		mat._13 * mat._31 * mat._44 -
		mat._14 * mat._33 * mat._41;
	ans._22 = b11 /detA;
	b11 = mat._11 * mat._24 * mat._43 +
		mat._13 * mat._21 * mat._44 +
		mat._14 * mat._23 * mat._41 -
		mat._11 * mat._23 * mat._44 -
		mat._13 * mat._24 * mat._41 -
		mat._14 * mat._21 * mat._43;
	ans._23 = b11 /detA;
	b11 = mat._11 * mat._23 * mat._34 +
		mat._13 * mat._24 * mat._31 +
		mat._14 * mat._21 * mat._33 -
		mat._11 * mat._24 * mat._33 -
		mat._13 * mat._21 * mat._34 -
		mat._14 * mat._23 * mat._31;
	ans._24 = b11 /detA;
	b11 = mat._21 * mat._32 * mat._44 +
		mat._22 * mat._34 * mat._41 +
		mat._24 * mat._31* mat._42 -
		mat._21 * mat._34 * mat._42 -
		mat._22 * mat._31 * mat._44 -
		mat._24 * mat._32 * mat._41;
	ans._31 = b11 /detA;
	b11 = mat._11 * mat._34 * mat._42 +
		mat._12 * mat._31 * mat._44 +
		mat._14 * mat._32 * mat._41 -
		mat._11 * mat._32 * mat._44 -
		mat._12 * mat._34 * mat._41 -
		mat._14 * mat._31 * mat._42;
	ans._32 = b11 /detA;
	b11 = mat._11 * mat._22 * mat._44 +
		mat._12 * mat._24 * mat._41 +
		mat._14 * mat._21 * mat._42 -
		mat._11 * mat._24 * mat._42 -
		mat._12 * mat._21 * mat._44 -
		mat._14 * mat._22 * mat._41;
	ans._33 = b11 /detA;
	b11 = mat._11 * mat._24 * mat._32 +
		mat._12 * mat._21 * mat._34 +
		mat._14 * mat._22 * mat._31 -
		mat._11 * mat._22 * mat._34 -
		mat._12 * mat._24 * mat._31 -
		mat._14 * mat._21 * mat._32;
	ans._34 = b11 /detA;
	b11 = mat._21 * mat._33 * mat._42 +
		mat._22 * mat._31 * mat._43 +
		mat._23 * mat._32 * mat._41 -
		mat._21 * mat._32 * mat._43 -
		mat._22 * mat._33 * mat._41 -
		mat._23 * mat._31 * mat._42;
	ans._41 = b11 /detA;
	b11 = mat._11 * mat._32 * mat._43 +
		mat._12 * mat._33 * mat._41 +
		mat._13 * mat._31 * mat._42 -
		mat._11 * mat._33 * mat._42 -
		mat._12 * mat._31 * mat._43 -
		mat._13 * mat._32 * mat._41;
	ans._42 = b11 /detA;
	b11 = mat._11 * mat._23 * mat._42 +
		mat._12 * mat._21 * mat._43 +
		mat._13 * mat._22 * mat._41 -
		mat._11 * mat._22 * mat._43 -
		mat._12 * mat._23 * mat._41 -
		mat._13 * mat._21 * mat._42;
	ans._43 = b11 /detA;
	b11 = mat._11 * mat._22 * mat._33 +
		mat._12 * mat._23 * mat._31 +
		mat._13 * mat._21 * mat._32 -
		mat._11 * mat._23 * mat._32 -
		mat._12 * mat._21 * mat._33 -
		mat._13 * mat._22 * mat._31;
	ans._44 = b11 /detA;	
	
	return ans;

}



float getValueFromTexColor(float4 color) {
    float ans = 0;
    float code = 0.1 * 1/255.0f;

    uint r = floor((color.x + code)*255);
    uint g = floor((color.y + code)*255);
    uint b = floor((color.z + code)*255);
    uint a = floor((color.w + code)*255);
    uint gu = a + (b << 8) + (g << 16) + (r <<24);
    ans = asfloat(gu);
    return ans;
}



column_major float4x4 getMatrixFromTex(Texture2D tex, float2 texcoord, int tex_width, int tex_height) {
column_major float4x4 ans;

float xcode = 0.5f/(float)tex_width;
float ycode = 0.5f/(float)tex_height;

float4 color[16];
float value[16];
uint i = 0;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 1;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 2;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 3;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 4;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 5;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 6;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 7;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 8;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 9;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 10;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 11;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 12;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 13;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 14;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);
i = 15;
color[i] = tex.SampleLevel(decalSmp, float2(texcoord.x + xcode + xcode*2*i, texcoord.y + ycode),0);
value[i] = getValueFromTexColor(color[i]);

ans._11 = value[0];
ans._21 = value[1];
ans._31 = value[2];
ans._41 = value[3];
ans._12 = value[4];
ans._22 = value[5];
ans._32 = value[6];
ans._42 = value[7];
ans._13 = value[8];
ans._23 = value[9];
ans._33 = value[10];
ans._43 = value[11];
ans._14 = value[12];
ans._24 = value[13];
ans._34 = value[14];
ans._44 = value[15];

return ans;
}

column_major float4x4 getMatrixFromVecF(float4 vo, float4 vt, float4 vthr, float4 vf) {
column_major float4x4 ans;
ans._11 = vo.x;
ans._21 = vo.y;
ans._31 = vo.z;
ans._41 = vo.w;
ans._12 = vt.x;
ans._22 = vt.y;
ans._32 = vt.z;
ans._42 = vt.w;
ans._13 = vthr.x;
ans._23 = vthr.y;
ans._33 = vthr.z;
ans._43 = vthr.w;
ans._14 = vf.x;
ans._24 = vf.y;
ans._34 = vf.z;
ans._44 = vf.w;
return ans;
}




Texture2D basisTex : register(t0); // matrix_basis_texture
Texture2D localTex : register(t1); // matrix_local_texture
Texture2D comTex: register(t2); // matrix_combined_texture
#define KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT 4096
#define KTROBO_SHADER_VALUE_LOCALTEX_WIDTH_HEIGHT 512
#define KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT 512
#define KTROBO_COMBINED_MATRIX_CONTROL_VALUE_ROOT_BONE 0x01
#define KTROBO_COMBINED_MATRIX_CONTROL_VALUE_CONNECT_WITHOUT_MATRIX_LOCAL 0x02
#define KTROBO_COMBINED_MATRIX_CONTROL_VALUE_VOFFSET 0x04
#define KTROBO_MESH_BONE_NULL 0xFFFF
#define KTROBO_MESH_INSTANCED_ANIME_MATRIX_BASIS_NUM_MAX 512
#define KTROBO_MESH_INSTANCED_BONE_MAX 32


column_major float4x4 getZeroKAKUDAI(float4x4 a) {
column_major float4x4 ans = a;
float3 vo = float3(a._11,a._12, a._13);
float3 vt = float3(a._21,a._22, a._23);
float3 vtt = float3(a._31,a._32,a._33);
float vo_len = length(vo);
float vt_len = length(vt);
float vtt_len = length(vtt);
if (vo_len ==0) vo_len=1;
if (vt_len==0) vt_len=1;
if (vtt_len==0) vtt_len=1;
ans._11 = ans._11 / vo_len;
ans._12 = ans._12 / vo_len;
ans._13 = ans._13 / vo_len;
ans._21 = ans._21 / vt_len;
ans._22 = ans._22 / vt_len;
ans._23 = ans._23 / vt_len;
ans._31 = ans._31 / vtt_len;
ans._32 = ans._32 / vtt_len;
ans._33 = ans._33 / vtt_len;
return ans;
}

column_major float4x4 getCombinedMatrixdayo(uint instance_index, uint bone_index) {
column_major float4x4 ans;

uint texel_per_bone = 16;
uint texel_per_instance = KTROBO_MESH_INSTANCED_BONE_MAX * texel_per_bone;
uint place = texel_per_instance * instance_index + texel_per_bone* bone_index;
uint x = place % KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;
uint y = place / KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;
float xoffset = 1/(float)KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;
float yoffset = 1/(float)KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;

float2 tex_coord = float2(x*xoffset, y*yoffset);
ans = getMatrixFromTex(comTex, tex_coord, KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT,
 KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT);
 
return MyMatrixTranspose(ans);
}










column_major float4x4 getLocalMatrix(uint skeleton_index, uint bone_index) {
column_major float4x4 ans;
uint texel_per_bone = 16;
uint texel_per_skeleton = KTROBO_MESH_INSTANCED_BONE_MAX * texel_per_bone;
uint place = texel_per_skeleton * skeleton_index + texel_per_bone* bone_index;
uint x = place % KTROBO_SHADER_VALUE_LOCALTEX_WIDTH_HEIGHT;
uint y = place / KTROBO_SHADER_VALUE_LOCALTEX_WIDTH_HEIGHT;
float xoffset = 1/(float)KTROBO_SHADER_VALUE_LOCALTEX_WIDTH_HEIGHT;
float yoffset = 1/(float)KTROBO_SHADER_VALUE_LOCALTEX_WIDTH_HEIGHT;

float2 tex_coord = float2(x*xoffset, y*yoffset);
ans = getMatrixFromTex(localTex, tex_coord, KTROBO_SHADER_VALUE_LOCALTEX_WIDTH_HEIGHT,
 KTROBO_SHADER_VALUE_LOCALTEX_WIDTH_HEIGHT);

return ans;
}














column_major float4x4 getOffsetMatrix(uint anime_first_index, 
uint anime_last_index, float anime_first_weight, 
uint skeleton_index, uint bone_index) {

column_major float4x4 ans;

uint texel_per_bone = KTROBO_MESH_INSTANCED_ANIME_MATRIX_BASIS_NUM_MAX * 16;
uint texel_per_skeleton = KTROBO_MESH_INSTANCED_BONE_MAX * texel_per_bone;
uint place = texel_per_skeleton * skeleton_index + texel_per_bone * bone_index + anime_first_index * 16;
uint x = place % KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT;
uint y = place / KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT;
float xoffset = 1/(float)KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT;
float yoffset = 1/(float)KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT;

float2 tex_coord = float2(x*xoffset, y*yoffset);
column_major float4x4 anime_first_matrix = getMatrixFromTex(basisTex, tex_coord, KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT, KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT);
place = texel_per_skeleton * skeleton_index + texel_per_bone * bone_index + anime_last_index * 16;
x = place % KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT;
y = place / KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT;
tex_coord = float2(x*xoffset, y*yoffset);
column_major float4x4 anime_last_matrix = getMatrixFromTex(basisTex, tex_coord,  KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT, KTROBO_SHADER_VALUE_BASISTEX_WIDTH_HEIGHT);
ans = anime_first_matrix * anime_first_weight + anime_last_matrix *  (1- anime_first_weight);







// ans �̊g��k�������𖳂���
ans = getZeroKAKUDAI(ans);
return ans;
}
/*
float4 getPosFromIndex(uint instance_index, uint bone_index) {
    float4 ans;

uint texel_per_bone = 16;
uint texel_per_instance = KTROBO_MESH_INSTANCED_BONE_MAX * texel_per_bone;
uint place = texel_per_instance * instance_index + texel_per_bone* bone_index;
uint x = place % KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;
uint y = place / KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;
float xoffset = 2/(float)KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;
float yoffset = 2/(float)KTROBO_SHADER_VALUE_COMBINEDTEX_WIDTH_HEIGHT;
ans.x =  -1 + x * xoffset;
ans.y = 1 - y*yoffset;
ans.z = 0.0f;
ans.w = 1.0f;
return ans;
}

*/



/*
struct VSInput {
uint is_calc : IS_CALC;
uint is_calc_finished : IS_CALC_FINISHED;
uint depth : DEPTH;

uint instance_index : INSTANCE_INDEX;
uint skeleton_index : SKELETON_INDEX;
uint pinstance_index : PINSTANCE_INDEX;
uint pskeleton_index : PSKELETON_INDEX;
uint anime_first_index : ANIME_FIRST_INDEX;
uint anime_last_index : ANIME_LAST_INDEX;
uint ctlv: CTLV;
uint bone_index : BONE_INDEX;
uint pbone_index : PBONE_INDEX;
float AnimeWeight :  ANIME_WEIGHT;
float4 kakeruMONE : KAKERUMONE;
float4 kakeruMTWO : KAKERUMTWO;
float4 kakeruMTHREE : KAKERUMTHREE;
float4 kakeruMFOUR : KAKERUMFOUR;
};
*/

/*


input {
uint depth;
uint instance_index : INSTANCE_INDEX;
uint skeleton_index : SKELETON_INDEX;
uint pinstance_index : PINSTANCE_INDEX;
uint pskeleton_index : PSKELETON_INDEX;
uint anime_first_index : ANIME_FIRST_INDEX;
uint anime_last_index : ANIME_LAST_INDEX;
uint ctlv: CTLV;
uint bone_index : BONE_INDEX;
uint pbone_index : PBONE_INDEX;
float AnimeWeight :  ANIME_WEIGHT;
float4 kakeruMONE : KAKERUMONE;
float4 kakeruMTWO : KAKERUMTWO;
float4 kakeruMTHREE : KAKERUMTHREE;
float4 kakeruMFOUR : KAKERUMFOUR;
};

output {
uint4 indexs : INDEXS;
float4 cb_one : CBMONE;
float4 cb_two : CBMTWO;
float4 cb_three : CBMTHREE;
float4 cb_four : CBMFOUR;
}
*/


cbuffer c0 {
uint depth;
uint vertex_num;
uint offset;
uint offsett;
};

RWByteAddressBuffer rwBuf :register(u0);
RWByteAddressBuffer ansBuf : register(u1);



uint getDepth(uint place) {
return asuint(rwBuf.Load(place));

}


column_major float4x4 getCombinedMatrix(uint place) {
// asfloat( rwBuffer1.Load3(4) );
uint instance_index = asuint(rwBuf.Load(place+4));//input.instance_index;
uint skeleton_index = asuint(rwBuf.Load(place+8));//input.skeleton_index;
uint parent_instance_index = asuint(rwBuf.Load(place+12));//input.pinstance_index;
uint parent_skeleton_index = asuint(rwBuf.Load(place+16));//input.pskeleton_index;
uint bone_index = asuint(rwBuf.Load(place+32));//input.bone_index;
uint parent_bone_index = asuint(rwBuf.Load(place+36));//input.pbone_index;
uint anime_first_index = asuint(rwBuf.Load(place+20));//input.anime_first_index;
uint anime_last_index = asuint(rwBuf.Load(place+24));//input.anime_last_index;
float anime_first_weight = asfloat(rwBuf.Load(place+40));//input.AnimeWeight;
float4 kakeruMONE = asfloat(rwBuf.Load4(place+ 44));
float4 kakeruMTWO = asfloat(rwBuf.Load4(place+60));
float4 kakeruMTHREE = asfloat(rwBuf.Load4(place+76));
float4 kakeruMFOUR = asfloat(rwBuf.Load4(place+92));
column_major float4x4 kakeru_matrix = MyMatrixTranspose(getMatrixFromVecF(kakeruMONE, kakeruMTWO, kakeruMTHREE, kakeruMFOUR));
uint controlvalue = asuint(rwBuf.Load(place+28));//input.ctlv;
uint is_root_bone = KTROBO_COMBINED_MATRIX_CONTROL_VALUE_ROOT_BONE & controlvalue;
uint connect_without_matrix_local = KTROBO_COMBINED_MATRIX_CONTROL_VALUE_CONNECT_WITHOUT_MATRIX_LOCAL & controlvalue;
uint vertex_offset = (KTROBO_COMBINED_MATRIX_CONTROL_VALUE_VOFFSET &controlvalue) >> 2;
column_major float4x4 ans_cm;




ans_cm = MyMatrixIdentity();

if ((parent_bone_index != KTROBO_MESH_BONE_NULL)&& (is_root_bone ==0)) {
    column_major float4x4 par_rest;
    column_major float4x4 temp_matrix;
    column_major  float4x4 b_matrix_local = getLocalMatrix(skeleton_index, bone_index);
    column_major  float4x4 pb_combined_matrix = getCombinedMatrixdayo(parent_instance_index, parent_bone_index);
    column_major  float4x4 b_offset_matrix = getOffsetMatrix(anime_first_index, anime_last_index, anime_first_weight, skeleton_index, bone_index);
    
    temp_matrix = MyMatrixMultiply(pb_combined_matrix, b_matrix_local/*, pb_combined_matrix*/);
    par_rest = MyMatrixInverse(temp_matrix);
    ans_cm = MyMatrixMultiply(MyMatrixMultiply(MyMatrixMultiply(temp_matrix, b_offset_matrix),par_rest), pb_combined_matrix);
}

if (parent_bone_index == KTROBO_MESH_BONE_NULL) {
     column_major float4x4 b_matrix_local= getLocalMatrix(skeleton_index, bone_index);
     column_major float4x4 mat_inv = MyMatrixInverse(b_matrix_local);
     column_major float4x4 b_offset_matrix = getOffsetMatrix(anime_first_index, anime_last_index, anime_first_weight, skeleton_index, bone_index);
     ans_cm = MyMatrixMultiply(b_matrix_local, MyMatrixMultiply(b_offset_matrix, mat_inv));
}

if ((parent_bone_index != KTROBO_MESH_BONE_NULL) && is_root_bone > 0 && connect_without_matrix_local >0) {
     column_major float4x4 b_matrix_local =  getLocalMatrix(skeleton_index, bone_index);
     column_major float4x4 par_rest;
     column_major float4x4 temp_matrix;
     column_major float4x4 bp_combined_matrix = getCombinedMatrixdayo(parent_instance_index, parent_bone_index);
     column_major float4x4 b_offset_matrix = getOffsetMatrix(anime_first_index, anime_last_index, anime_first_weight, skeleton_index, bone_index);
     column_major float4x4 tem = MyMatrixMultiply(kakeru_matrix, b_matrix_local);
    temp_matrix = MyMatrixMultiply(bp_combined_matrix, tem);
    par_rest = MyMatrixInverse(temp_matrix);
//    ans_cm = MyMatrixMultiply(bp_combined_matrix, MyMatrixMultiply(par_rest, MyMatrixMultiply(b_offset_matrix, temp_matrix)));


   ans_cm = MyMatrixMultiply(temp_matrix, MyMatrixMultiply(b_offset_matrix, MyMatrixMultiply(par_rest, bp_combined_matrix)));




}

if ((parent_bone_index != KTROBO_MESH_BONE_NULL) && is_root_bone > 0 && connect_without_matrix_local ==0) {
     column_major float4x4 b_matrix_local = getLocalMatrix(skeleton_index, bone_index);
     column_major float4x4 pb_matrix_local = getLocalMatrix(parent_skeleton_index, parent_bone_index);
     column_major float4x4 pb_combined_matrix = getCombinedMatrixdayo(parent_instance_index, parent_bone_index);
     column_major float4x4 b_offset_matrix = getOffsetMatrix(anime_first_index, anime_last_index, anime_first_weight, skeleton_index, bone_index);
     column_major float4x4 tem = MyMatrixMultiply(kakeru_matrix, b_matrix_local);
     column_major float4x4 p = MyMatrixInverse(tem);
  //  ans_cm = MyMatrixMultiply(p, MyMatrixMultiply(pb_matrix_local, pb_combined_matrix));
   ans_cm = MyMatrixMultiply(pb_combined_matrix, MyMatrixMultiply(pb_matrix_local, p));


}

return ans_cm;

}


float2 getIndexs(uint place) {
float2 indexs;
indexs.x = asuint(rwBuf.Load(place+4));
indexs.y = asuint(rwBuf.Load(place+32));
return indexs;
}

// group �ɂ�max�C���X�^���X�̐����w�肷��
// numthreads �ɂ�maxbonenum �̐����w�肷��
[numthreads(32,1,1)]
void CalcCS(uint gtid: SV_GroupIndex, uint3 gid: SV_GroupID )
{
//uint iid = gtid;
//uint b_index = gid.x;
uint struct_idx = gid.x * 32 + gtid;
uint byte_per_instance;
uint byte_per_bone;
uint place = struct_idx * 27 * 4;

if (struct_idx >= vertex_num) {
return;
}

// depth ���擾
uint dep = getDepth(place);
if (dep != depth) {
return;
}

 column_major float4x4 cb = getCombinedMatrix(place);
float2 indexs = getIndexs(place);

column_major float4x4 ans_cm = cb;

uint index = struct_idx * 20 * 4;
uint instance_id = indexs.x;
uint bone_index = indexs.y;
// �v�Z���ʂ��o�t�Ɋi�[����
ansBuf.Store(index + 16, asuint(ans_cm._11));
ansBuf.Store(index + 16 + 4* 1, asuint(ans_cm._12));
ansBuf.Store(index + 16+4*2, asuint(ans_cm._13));
ansBuf.Store(index + 16+4*3, asuint(ans_cm._14));
                       
ansBuf.Store(index + 16+4*4, asuint(ans_cm._21));
ansBuf.Store(index + 16+4*5, asuint(ans_cm._22));
ansBuf.Store(index + 16+4*6, asuint(ans_cm._23));
ansBuf.Store(index + 16+4*7, asuint(ans_cm._24));
                        
ansBuf.Store(index + 16+4*8, asuint(ans_cm._31));
ansBuf.Store(index + 16+4*9, asuint(ans_cm._32));
ansBuf.Store(index + 16+4*10, asuint(ans_cm._33));
ansBuf.Store(index + 16+4*11, asuint(ans_cm._34));
              
ansBuf.Store(index + 16+4*12, asuint(ans_cm._41));
ansBuf.Store(index + 16+4*13, asuint(ans_cm._42));
ansBuf.Store(index + 16+4*14, asuint(ans_cm._43));
ansBuf.Store(index + 16+4*15, asuint(ans_cm._44));






ansBuf.Store(index, instance_id);
ansBuf.Store(index+4, bone_index);
ansBuf.Store(index+8, bone_index);
ansBuf.Store(index+12, bone_index);




}













