
dofile("tolua_glue/tolua.lua")

left = 1000 - 236 - 50;
right = left + 236;
top = 51+50 + 50 + 52+27+150;
bottom = top + 55;
rect = { left,right,top,bottom}


gamen2 = Gamen2:getIS(0,0)

tex = Texture:getIS(0,0)
tex2 = Texture:getIS(0,1)

tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH,4096);
--texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 1000 - 236 - 50, 150+51+50 + 52 + 50+27, 236, 50, 0, 201, 236, 55);

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



--texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 1000 - 236 - 50, 50, 236, 51, 0, 48, 236, 51);
left = 1000 - 236 - 50
right = left + 236
top = 48
bottom = top + 51
rect = {left,right,top,bottom}



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
  bottom = top + 30
  rect ={left,right,top,bottom}
  
  group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, help_text,focus_lua_str,
  select_lua_str, rect)

  tex_index = tex:getTexture(KTROBO_GARAGE2_IMG_PATH,4096);
  tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH, 4096)
  
  offdayo = (30 - text_height)/2
  texe2 = tex2:getRenderText(button_str, x + offdayo , y +offdayo, text_height, width- 2*offdayo ,30)
  tex2:setRenderTextColor(texe2,0xFF000000)
  left = x+offdayo
  right = left + width-2*offdayo
  top = y +offdayo
  bottom = top + 30 -2*offdayo
  rect ={left,right,top,bottom}
  p_index = gamen2:setPartsGroupSetText(group_index, true, texe2, rect)
 -- tex:setRenderTextIsRender(texe2,false)
  setGpPartToGp(gp, texe2,rect,p_index)
  
  texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, x, y, width, 30, 68, 376, 238-68, 54)
  left = x
  right = left + 238-68
  top = y
  bottom = top + 30
  rect ={left,right,top,bottom}
  p_index = gamen2:setPartsGroupSetTex(group_index, true, texe, rect)

  setGpPartToGp(gp,texe,rect,p_index)
  setGpToGps(gpx,gp_map, gp, group_index, button_id_str, rect)
  return group_index
end

moveforward_st = [[�O�i����ۂ̃L�[��ݒ肵�܂��B]]
movebackward_st = [[��ނ���ۂ̃L�[��ݒ肵�܂��B]]
moveleft_st = [[�����ړ�����ۂ̃L�[��ݒ肵�܂��B]]
moveright_st = [[�E���ړ�����ۂ̃L�[��ݒ肵�܂��B]]
turnleft_st = [[������ړ�����ۂ̃L�[��ݒ肵�܂��B]]
turnright_st = [[�E����ړ�����ۂ̃L�[��ݒ肵�܂��B]]
lookup_st = [[���_��ړ��̃L�[��ݒ肵�܂��B]]
lookdown_st = [[���_���ړ��̃L�[��ݒ肵�܂��B]]
boostonoff_st = [[�u�[�X�g�̃I���I�t�L�[��ݒ肵�܂��B]]
jump_st = [[�W�����v�L�[��ݒ肵�܂��B]]
boostmove_st = [[�u�[�X�g�ړ��̃L�[��ݒ肵�܂��B]]
rarm_st = [[�E�r����̔��˃L�[��ݒ肵�܂��B]]
larm_st = [[���r����̔��˃L�[��ݒ肵�܂��B]]
rkata_st = [[�E������̔��˃L�[��ݒ肵�܂��B]]
lkata_st = [[��������̔��˃L�[��ݒ肵�܂��B]]
inside_st = [[�C���T�C�h����̔��˃L�[��ݒ肵�܂��B]]
select_st = [[����{�^���̃L�[��ݒ肵�܂��B]]
back_st = [[�߂�{�^���̃L�[��ݒ肵�܂��B]]


moveforward_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "�O�i�L�[", "moveforward_key",moveforward_st ,"NO_LUA","resrc/script/gamepad/modoru_now.lua",156,100,28)
movebackward_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "��ރL�[", "movebackward_key", movebackward_st ,"NO_LUA","resrc/script/gamepad/modoru_now.lua",156,160,28)
moveleft_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "���ړ��L�[", "moveleft_key", moveleft_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,220,28)
moveright_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "�E�ړ��L�[", "moveright_key",moveright_st  ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,280,28)
turnleft_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"������L�[", "turnleft_key", turnleft_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,340,28)
turnright_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�E����L�[", "turnright_key", turnright_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,400,28)
lookup_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�㎋�_�ړ��L�[", "lookup_key", lookup_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,460,28)
lookdown_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�����_�ړ��L�[", "lookdown_key", lookdown_st  ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,520,28)
boostonoff_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�u�[�X�g�I���I�t�L�[", "boostonoff_key", boostonoff_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,580,28)
jump_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�W�����v�L�[", "jump_key",jump_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,640,28)
boostmove_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�u�[�X�g�ړ��L�[", "boostmove_key", boostmove_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,700,28)
rarm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�E�r���픭�˃L�[", "rarm_key", rarm_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
larm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"���r���픭�˃L�[", "larm_key", larm_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
rkata_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�E�����픭�˃L�[", "rkata_key", rkata_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
lkata_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�������픭�˃L�[", "lkata_key", lkata_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
inside_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�C���T�C�h���˃L�[", "inside_key", inside_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
select_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"����{�^���L�[", "select_key", select_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
back_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"�߂�{�^���L�[", "back_key", back_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)




gamen_id_gamepad_start = 0

gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GAMEPAD,gamen_id_gamepad_start,"resrc/script/gamepad/initgo_gamepad.lua")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start)


gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,moveforward_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,movebackward_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,moveleft_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,moveright_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,turnleft_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,turnright_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,lookup_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,lookdown_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,boostonoff_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,jump_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,boostmove_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,rarm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,larm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,rkata_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,lkata_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,inside_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,select_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start,back_gindex,0)



mf_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVEFORWARD)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, mf_cpp )
mb_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVEBACKWARD)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, mb_cpp )
ml_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVELEFT)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, ml_cpp )
mr_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVERIGHT)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, mr_cpp )
tl_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_TURNLEFT)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, tl_cpp )
tr_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_TURNRIGHT)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, tr_cpp )
lu_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LOOKUP)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, lu_cpp )
ld_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LOOKDOWN)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, ld_cpp )

boo_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_BOOSTONOFF)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, boo_cpp )
jump_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_JUMP)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, jump_cpp )
bm_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_BOOSTMOVE)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, bm_cpp )
rarm_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_RARM)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, rarm_cpp )

larm_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LARM)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, larm_cpp )
rkata_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_RKATA)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, rkata_cpp )
lkata_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LKATA)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, lkata_cpp )
inside_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_INSIDE)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, inside_cpp )


s_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_SELECT)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, s_cpp )
b_cpp = gamen2:getCPPPartsIndex(KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_BACK)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start, b_cpp )









gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, gamen_id_gamepad_start)
gamen_id_now = gamen_id_gamepad_start












gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED_MADA)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVEFORWARD)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, moveforward_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVEFORWARD, moveforward_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, movebackward_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVEBACKWARD, movebackward_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, moveleft_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVELEFT, moveleft_gindex)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, moveright_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_MOVERIGHT, moveright_gindex)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, turnleft_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_TURNLEFT, turnleft_gindex)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, turnright_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_TURNRIGHT, turnright_gindex)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, lookup_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LOOKUP, lookup_gindex)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, lookdown_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LOOKDOWN, lookdown_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, boostonoff_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_BOOSTONOFF, boostonoff_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, jump_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_JUMP, jump_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, boostmove_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_BOOSTMOVE, boostmove_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, rarm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_RARM, rarm_gindex)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, larm_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LARM, larm_gindex)



gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, rkata_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_RKATA, rkata_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, lkata_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_LKATA, lkata_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, inside_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_INSIDE, inside_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, select_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_SELECT, select_gindex)


gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_SELECTED, KTROBO_GAMEPAD_HENSUU_BUTTON_SELECTED, back_gindex)
gamen2:setHensuuRule(KTROBO_GAMEN2_SCENE_ID_GAMEPAD, KTROBO_GAMEPAD_HENSUU_ID_BUTTON_PARTSDEF, KTROBO_GAMEPAD_CPPPARTS_PARTSDEF_BACK, back_gindex)
