
dofile("tolua_glue/tolua.lua")

left = 1000 - 236 - 50;
right = left + 236;
top = 51+50 + 50 + 52+27+150;
bottom = top + 55;
rect = { left,right,top,bottom}


gamen2 = Gamen2:getIS(0,0)
group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "�M�d��G�𕥂��ăp�[�c���w�����܂��B�����p�͐헪�I�ɁB", 
"NO_LUA", "resrc/script/garage/gotoshop_garage_selected.lua", rect)

tex = Texture:getIS(0,0)
tex2 = Texture:getIS(0,1)

tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH,4096);
texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 1000 - 236 - 50, 150+51+50 + 52 + 50+27, 236, 50, 0, 201, 236, 55);
	
p_index = gamen2:setPartsGroupSetTex(group_index, true, texe, rect)

gps ={}
gp_map_name_to_group_index = {}

function setGpPartToGp(lgp, texe,rect, p_index) 
  lgp["gp_parts"] = lgp["gp_parts"] or {}
  p_part = {texe,rect,p_index}
  lgp["gp_parts"][p_index] = p_part
end

function setGpToGps(lgps, lgps_map, lgp, group_index, gp_name, rect)
  
  lgp["group_index"] = group_index
  lgp["name"] = gp_name
  lgp["rect"] = rect
  
  
  lgps_map[lgp["name"]] = lgp["group_index"]
  lgps[lgp["group_index"]] = lgp
end

gp = {}
shop_gindex  = group_index

setGpPartToGp(gp,texe,rect,p_index)
setGpToGps(gps,gp_map_name_to_group_index, gp, group_index, "shop", rect)



texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 1000 - 236 - 50, 50, 236, 51, 0, 48, 236, 51);
left = 1000 - 236 - 50
right = left + 236
top = 48
bottom = top + 51
rect = {left,right,top,bottom}

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "�A�Z���u�����܂��B�w���ς݂̃p�[�c���g���Ď����Ǝ��̋@�̂����܂��B", 
"NO_LUA", "resrc/script/garage/gotoassemble_garage_selected.lua", rect)
assemble_gindex = group_index
p_index = gamen2:setPartsGroupSetTex(group_index, true, texe, rect)

gp = {}
setGpPartToGp(gp,texe,rect,p_index)
setGpToGps(gps,gp_map_name_to_group_index, gp, group_index, "assemble", rect)


texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 1000 - 236 - 50,30+51+ 50 + 26, 236, 52, 0, 98, 236, 52);
left = 1000 - 236 - 50;
right = left + 236;
top = 31+50+26+50;
bottom = top + 52;
rect = {left,right,top,bottom}

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "���݂̋@�̂��t�@�C���ɕۑ����܂��B16�܂ŕۑ��ł��܂��B", 
"NO_LUA", "resrc/script/garage/gotoasmsave_garage_selected.lua", rect)
p_index = gamen2:setPartsGroupSetTex(group_index, true, texe, rect)

gp = {}
setGpPartToGp(gp,texe,rect,p_index)
setGpToGps(gps,gp_map_name_to_group_index, gp, group_index, "asmsave", rect)
asmsave_gindex = group_index
	
	
texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 1000 - 236 - 50, 100+51+50 + 52 + 25, 236, 50, 0, 150, 236, 50);
left = 1000 - 236 - 50;
right = left + 236;
top = 51+50 + 25 + 52+100;
bottom = top + 50;
rect = {left,right,top,bottom}

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "�ۑ��ς݂̋@�̂����[�h���܂��B���[�h��������ƌ��݂̋@�͎̂����܂��B", 
"NO_LUA", "resrc/script/garage/gotoasmload_garage_selected.lua", rect)
asmload_gindex = group_index

p_index = gamen2:setPartsGroupSetTex(group_index, true, texe, rect)

gp = {}
setGpPartToGp(gp,texe,rect,p_index)
setGpToGps(gps,gp_map_name_to_group_index, gp, group_index, "asmload", rect)


function setButton(tex,tex2, gpx, gp_map, button_str, button_id_str, help_text, focus_lua_str, select_lua_str, x, y, text_height)
  
  gp ={}
  width = 238-68
  if (#button_str > 5*2) then
    -- 2 bai
    width = width * 2
  end
    
  left = x
  right = left + width
  top = y
  bottom = top + 54
  rect ={left,right,top,bottom}
  
  group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, help_text,focus_lua_str,
  select_lua_str, rect)

  tex_index = tex:getTexture(KTROBO_GARAGE2_IMG_PATH,4096);
  tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH, 4096)
  
  offdayo = (54 - text_height)/2
  texe2 = tex2:getRenderText(button_str, x + offdayo , y +offdayo, text_height, width- 2*offdayo ,54)
  tex2:setRenderTextColor(texe2,0xFF000000)
  left = x+offdayo
  right = left + width-2*offdayo
  top = y +offdayo
  bottom = top + 54 -2*offdayo
  rect ={left,right,top,bottom}
  p_index = gamen2:setPartsGroupSetText(group_index, true, texe2, rect)
 -- tex:setRenderTextIsRender(texe2,false)
  setGpPartToGp(gp, texe2,rect,p_index)
  
  texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, x, y, width, 54, 68, 376, 238-68, 54)
  left = x
  right = left + 238-68
  top = y
  bottom = top + 54
  rect ={left,right,top,bottom}
  p_index = gamen2:setPartsGroupSetTex(group_index, true, texe, rect)

  setGpPartToGp(gp,texe,rect,p_index)
  setGpToGps(gpx,gp_map, gp, group_index, button_id_str, rect)
  return group_index
end

head_st = [[�����p�[�c�̓��{�̌v�Z�\�͂���Ɍ��肵�܂��B���̕��ʂ��D�G���Ƌ@��������у��b�N�@�\�ɏG�ł܂��B]]
body_t =[[�R�A�p�[�c�̓��{�̑��b���\�A�C���T�C�h�̑����s�����肵�܂��B]]
arm_t = [[�r���p�[�c�̓��{�̕���ւ̓񎟌���I�ȃG�l���M�[�������A�����[�h���\�����肵�܂��B]]
leg_t = [[�r���p�[�c�̓��{�̐ύڗʁA�@�����\�����肵�܂��B�r���̓��{�̐��\����ɑ傫�ȉe�����y�ڂ��܂��B]]
booster_t = [[�u�[�X�^�p�[�c�̓��{�̋@�����\�A�u�[�X�g���̋��������肵�܂��B]]
engine_t = [[�G���W���p�[�c�̓��{�̃G�l���M�[�v�[�����\����уG�l���M�[�����\�͂����肵�܂��B]]
fcs_t = [[FCS�p�[�c�̓��{�̃��b�N����̃��b�N���\�����肵�܂��B]]
rarm_t = [[�E�蕐��ł��B�l�X�Ȏ�ނ̃p�[�c��������Ă��܂��B]]
larm_t =  [[���蕐��ł��B�l�X�Ȏ�ނ̃p�[�c��������Ă��܂��B]]
rkata_t = [[�E������ł��B�@������͎�ނ͏��Ȃ����̂̋��͂ȕ��킪������ۂł��B]]
lkata_t = [[��������ł��B�@������͎�ނ͏��Ȃ����̂̋��͂ȕ��킪������ۂł��B]]
inside_t =[[�C���T�C�h����ł��B�@�R�A�p�[�c�������\�Ȃ��̂̏ꍇ�̂ݑ����ł��܂��B]]
head_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "�����p�[�c", "head_part",head_st ,"NO_LUA","resrc/script/garage/partscategory_garage_selected.lua",156,100,28)
body_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "�R�A�p�[�c", "core_part", body_t ,"NO_LUA","resrc/script/garage/partscategory_garage_selected.lua",156,160,28)
arm_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "�r���p�[�c", "arm_part", arm_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,220,28)
leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "�r���p�[�c", "leg_part",leg_t  ,"NO_LUA", "resrc/script/garage/selectpartscategory_garage_selected.lua", 156,280,28)
booster_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�u�[�X�^", "booster_part", booster_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,340,28)
engine_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�G���W��", "engine_part", engine_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,400,28)
fcs_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"FCS", "fcs_part", fcs_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,460,28)
rarm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�E�r����", "rarm_part",rarm_t  ,"NO_LUA", "resrc/script/garage/selectpartscategory2_garage_selected.lua", 156,520,28)
larm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"���r����", "larm_part", larm_t,"NO_LUA", "resrc/script/garage/selectpartscategory2_garage_selected.lua", 156,580,28)
rshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�E������", "rshoul_part",rkata_t ,"NO_LUA", "resrc/script/garage/selectpartscategory3_garage_selected.lua", 156,640,28)
lshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"��������", "lshoul_part", lkata_t ,"NO_LUA", "resrc/script/garage/selectpartscategory3_garage_selected.lua", 156,700,28)
inside_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�C���T�C�h", "inside_part", inside_t,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,760,28)


k2_leg_t =  [[�y�ʓ�r�p�[�c�͋@�����\�ɂ�����A�ꌂ���E�����ӂł��B���ʑ��b�͒Ⴂ�ł��B]]          
t2_leg_t  =[[���ʓ�r�p�[�c�̓o�����X�ɂ�����A���낢��ȏ�ʂɑΉ��ł��܂��B]]                    
j2_leg_t  =[[�d�ʓ�r�p�[�c�͑��b���������@�����\�������������Ȃ���Ă��܂��B]]                   
tank_leg_t  =[[�^���N�r�p�[�c�͐��ʂ���̌��킨��ы��_�h�q�ɓK���Ă��܂��B�@�����\�͒Ⴂ�ł��B]]    
k4_leg_t  =[[�l�r�p�[�c�͐ύڗʂ������A�l�X�Ȏ�ނ̕���̑�������ё��b����������̂��\�ł��B]]  
reverse_leg_t =[[�t�֐ߌ^�r���p�[�c�̓W�����v���\�������A���̓I�ȋ@�����Ƃ邱�Ƃ��\�ł��B]]          

handgun_at =[[�n���h�K���p�[�c�͍U�����\�͒Ⴂ�ł����Ռ���^���邱�Ƃ��\�ł��B�ߋ������璆�����Ŕ\�͂𔭊��ł��܂��B]]
machinegun_at=[[�}�V���K���p�[�c�͋ߋ����p�̃��b�N�I������ŒZ�������[�h���\�ɂ��A�˔\�͂ŎE�������o���Ă��܂��B]]      
shotgun_at =[[�V���b�g�K���p�[�c�͎��ߋ����p�̃��b�N�I������ł��B�����ɂ͊����K�v�Ƃ��܂��B]]                        
rifle_at =[[���C�t���p�[�c�͕W���I�ȃ��b�N�I������ŋߋ������璆�����ɂ����Ċ��􂵂܂��B]]                            
bazooka_at=[[�o�Y�[�J�p�[�c�͍U�����\�̍������b�N�I������Ń����[�h���\�͒Ⴂ���̂̈ꔭ���傫���̂������ł��B]]        
sniperrifle_at =  [[�X�i�C�p�[���C�t���p�[�c�͒���������U���\�ȃ��b�N�I������ł��B]]                           



grenede_at= [[�O���l�[�h�p�[�c�͒��ߋ����p�̕���Œ��e�㔚�����܂��B]]                                             
missile_at=[[�~�T�C���p�[�c�͗U�����\���������~�T�C���𔭎˂��镐��ł��B]]                                       
rocket_at=[[���P�b�g�p�[�c�̓m�[���b�N�I������Ŕ��ˌ㒼�i���܂��B���Ă�ɂ͑����ȏn�����K�v�ł��B]]             
hanabigun_at=[[�n�i�r�K���p�[�c�̓m�[���b�N�I������ł��B�g���Ă݂Ă̂��y���݂ł��B]]                               
pulsegun_at=[[�p���X�K���p�[�c�̓G�l���M�[����Ŏg�p�Ƀ��{�̃G�l���M�[��K�v�Ƃ��܂��B���ߋ����ŗL���ȕ���ł��B]] 
plazumagun_at=[[�v���Y�}�K���p�[�c�̓G�l���M�[����ł��B�e�����x���̂������ł��B]]                                   
energyrifle_at=[[�G�l���M�[���C�t���p�[�c�̓G�l���M�[����ł��B�@���C�t���̃G�l���M�[����łƂ����������ł��B]]       
blade_at=[[�u���[�h�p�[�c�͋Ɏ��ߋ����ɂČ����Ȑn�ɂĕ����I�_���[�W��^���܂��B]]                               
energyblade_at=[[�G�l���M�[�u���[�h�p�[�c�͋Ɏ��ߋ����ɂĒ������x�ȃG�l���M�[�n�𔭐����A�Ώۂ�j�󂵂܂��B]]         
pile_at=[[�p�C���p�[�c�͒����ߋ����ɂĔ�������Y��Ώۂɑł�����ňꌂ�K�E�I�ȃ_���[�W��^���܂��B]]           




k2_leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "�y�ʓ�r", "k2_leg_part",          k2_leg_t           ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,100,28)
t2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "���ʓ�r", "t2_leg_part",          t2_leg_t          ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,160,28)
j2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�d�ʓ�r", "j2_leg_part",            j2_leg_t        ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,220,28)
tank_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�^���N", "tank_leg_part",             tank_leg_t     ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,280,28)
k4_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�l�r", "k4_leg_part",             k4_leg_t           ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,340,28)
reverse_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�t�֐�", "reverse_leg_part",     reverse_leg_t       ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,400,28)

handgun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�n���h�K��", "handgun_arm_part",    handgun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,100,28)
machinegun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�}�V���K��", "machinegun_arm_part",machinegun_at ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,160,28)
shotgun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�V���b�g�K��", "shotgun_arm_part",  shotgun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,220,28)
rifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "���C�t��", "rifle_arm_part",       rifle_at      ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,280,28)
bazooka_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�o�Y�[�J", "bazooka_arm_part",    bazooka_at     ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,340,28)
sniperrifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�X�i�C�p�[���C�t��", "sniperrifle_arm_part",sniperrifle_at,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,400,28)
grenede_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�O���l�[�h", "grenede_arm_part",           grenede_at              ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,460,28)
missle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�~�T�C��", "missile_arm_part",                 missile_at           ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,520,28)
rocket_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "���P�b�g", "rocket_arm_part",                        rocket_at     ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,580,28)
hanabigun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�n�i�r�K��", "hanabigun_arm_part",                  hanabigun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,640,28)
pulsegun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�p���X�K��", "pulsegun_arm_part",                 pulsegun_at      ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,700,28)
plazumagun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�v���Y�}�K��", "plazumagun_arm_part",           plazumagun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,100,28)
energyrifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�G�l���M�[���C�t��", "energyrifle_arm_part",     energyrifle_at  ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,160,28)
blade_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�u���[�h", "blade_arm_part",                              blade_at            ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,220,28)
energyblade_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�G�l���M�[�u���[�h", "energybladea_arm_part",         energyblade_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,280,28)
pile_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�p�C��", "pile_arm_part",                      pile_at                ,              "NO_LUA"                      , "resrc/script/garage/partscategory2_garage_selected.lua", 800,340,28)

arm_gindex_start = handgun_arm_gindex
arm_gindex_end = pile_arm_gindex

hai_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "�n�C", "hai", "��Ăɏ������܂��B", "NO_LUA", "NO_LUA",100,150,28)
iie_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "�C�C�G", "iie", "��Ă��p�����܂��B", "NO_LUA", "NO_LUA",100,150,28)

sellp_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "���p", "sellp", "�p�[�c�𔄋p���܂��B", "NO_LUA", "NO_LUA",100,150,28)
equipp_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "����", "equipp", "�p�[�c�𑕒����܂��B", "NO_LUA", "NO_LUA",100,150,28)

ok_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "OK", "ok", "���̐��̒����܂��Ă��Ȃ��������Ȃ���������B", "NO_LUA", "NO_LUA",100,150,28)



chaingun_st = [[�`�F�C���K���͎E���\�͂̍����e��A���Ŕ��˂��܂��B]]
grenede_st = [[�O���l�[�h�C�͒��e����Ɣ�������e�����Ԋu�Ŕ��˂��܂��B]]
hanabi_st = [[�n�i�r�C�͎g���Ă݂Ă̂��y���݂ł��B]]
missile_st = [[�~�T�C���C�͗U�����\�����~�T�C���e�𔭎˂��܂��B�������b�N����ƕ������˂ł��܂��B]]
plazuma_st =[[�v���Y�}�C�̓G�l���M�[����ł��B�e���͒x���ł��B]]
pulse_st =[[�p���X�C�̓G�l���M�[����ł��B���ߋ����Ō��͂𔭊����܂��B]]
raser_st = [[���[�U�[�C�̓G�l���M�[����ł��B�Ԍ`�̕���ł��B]]
rocket_st = [[���P�b�g�C�̓m�[���b�N����ł��B�r����ɓ������Ĕ��˂���܂��B]]


chaingun_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�`�F�C���K��", "chaingun_shoul_part",  chaingun_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,400,28)
grenede_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�O���l�[�h", "grenede_shoul_part",  grenede_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,460,28)
hanabi_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�n�i�r", "hanabi_shoul_part",  hanabi_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,520,28)
missile_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�~�T�C��", "missile_shoul_part",  missile_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,580,28)
plazuma_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�v���Y�}", "plazuma_shoul_part",  plazuma_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,640,28)
pulse_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "�p���X", "pulse_shoul_part",  pulse_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,700,28)
raser_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "���[�U�[", "raser_shoul_part",  raser_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,760,28)
rocket_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "���P�b�g", "rocket_shoul_part",  rocket_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,840,28)
--]]



gamen2:setPartsGroupIsWorkRender(head_gindex,false)


--TO_LUA virtual void makeSonotoki(int scene_id, int gamen_id, char* lua_filename)=0;
--TO_LUA virtual void setSonotokiMakeKo(int scene_id, int gamen_id)=0;
--TO_LUA virtual void setSonotokiSetGroupOnlyRenderGroup(int scene_id, int gamen_id, int all_index)=0;
--TO_LUA virtual void setSonotokiSetGroupGroup(int scene_id, int gamen_id, int all_index, int cursor_x)=0;
--TO_LUA virtual int getSonotokiCursorGroup(int scene_id, int gamen_id)=0;
--TO_LUA virtual void setSonotokiNowSonotoki(int scene_id, int gamen_id)=0;
--TO_LUA virtual int getNowSonotokiCursorGroup()=0;
gamen_id_garage_start = 0

gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_garage_start,"resrc/script/garage/start_garage.lua")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start)
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,shop_gindex)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,assemble_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,asmsave_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,asmload_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,shop_gindex,0)
robog = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,robog,1)

gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start)
gamen_id_now = gamen_id_garage_start
--texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 0, 50, 236, 51, 0, 48, 136, 51);
--gamen2:setPartsGroupMoveTo(group_index, 0,10,236,55,"6000.0")

--LuaExector:getIS(0,0):setExecCoDoUntilTime("resrc/script/garage/moveto.lua", 2)

gamen_id_garage_shop_start = 1
gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start, "resrc/script/garage/start_garage_shop.lua")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start)
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,shop_gindex)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,head_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,body_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,leg_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,booster_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,engine_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,fcs_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,rarm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,larm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,rshoul_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,lshoul_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,inside_gindex,0)
robog = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start,robog,1)

gamen_id_garage_assemble_start = 1000
gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start, "resrc/script/garage/start_garage_assemble.lua")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start)
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,assemble_gindex)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,head_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,body_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,leg_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,booster_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,engine_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,fcs_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,rarm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,larm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,rshoul_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,lshoul_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,inside_gindex,0)
robog = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_assemble_start,robog,1)


















gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_FIRSTCATEGORY, KTROBO_GARAGE2_HENSUU_FIRSTCATEGORY_SHOP)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_NO)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_HEAD)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_K2)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL, KTROBO_GARAGE2_HENSUU_LUA_KEY_CALL_NOKEY)





gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_FIRSTCATEGORY, KTROBO_GARAGE2_HENSUU_FIRSTCATEGORY_SHOP, shop_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_FIRSTCATEGORY, KTROBO_GARAGE2_HENSUU_FIRSTCATEGORY_ASSEMBLE, assemble_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_FIRSTCATEGORY, KTROBO_GARAGE2_HENSUU_FIRSTCATEGORY_ASMLOAD, asmload_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_FIRSTCATEGORY, KTROBO_GARAGE2_HENSUU_FIRSTCATEGORY_ASMSAVE, asmsave_gindex)

gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, asmload_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, asmsave_gindex)





gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, head_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, body_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, booster_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, engine_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, fcs_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, inside_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, k2_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, t2_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, j2_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, tank_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, k4_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, reverse_leg_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, handgun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, machinegun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, shotgun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, rifle_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, bazooka_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, sniperrifle_arm_gindex) 
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, grenede_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, missle_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, rocket_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, hanabigun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, pulsegun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, plazumagun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, energyrifle_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, blade_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, energyblade_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, pile_arm_gindex)

gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, chaingun_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, grenede_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, hanabi_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, missile_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, plazuma_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, pulse_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, raser_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_YES, rocket_shoul_gindex)

gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_HEAD   ,head_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_BODY   ,body_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_ARM   ,arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LEG   ,leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_BOOSTER   ,booster_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_ENGINE   ,engine_gindex) 
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_FCS   ,fcs_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RARM   ,rarm_gindex) 
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LARM   ,larm_gindex) 
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RKATA   ,rshoul_gindex) 
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LKATA   ,lshoul_gindex) 
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_INSIDE   ,inside_gindex) 

gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_K2, k2_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_T2, t2_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_J2, j2_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_TANK, tank_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_4, k4_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_REVERSE, reverse_leg_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_HANDGUN, handgun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_MACHINEGUN, machinegun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_SHOTGUN, shotgun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_RIFLE, rifle_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_BAZOOKA, bazooka_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_SNIPERRIFLE, sniperrifle_arm_gindex) 
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_GRENEDE, grenede_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_MISSILE, missle_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ROCKET, rocket_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_HANABIGUN, hanabigun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PULSEGUN, pulsegun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PLAZUMAGUN, plazumagun_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ENERGYRIFLE, energyrifle_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_BLADE, blade_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_ENERGYBLADE, energyblade_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_ARM_PILE, pile_arm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_CHAINGUN, chaingun_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_GRENEDE, grenede_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_HANABI, hanabi_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_MISSILE, missile_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_PLAZUMA, plazuma_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_PULSE, pulse_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_RASER, raser_shoul_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_ROCKET, rocket_shoul_gindex)




--gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_IS_, hai_gindex)
--gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_KATA_ROCKET, iie_gindex)
