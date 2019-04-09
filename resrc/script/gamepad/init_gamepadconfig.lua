
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

moveforward_st = [[前進する際のキーを設定します。]]
movebackward_st = [[後退する際のキーを設定します。]]
moveleft_st = [[左横移動する際のキーを設定します。]]
moveright_st = [[右横移動する際のキーを設定します。]]
turnleft_st = [[左旋回移動する際のキーを設定します。]]
turnright_st = [[右旋回移動する際のキーを設定します。]]
lookup_st = [[視点上移動のキーを設定します。]]
lookdown_st = [[視点下移動のキーを設定します。]]
boostonoff_st = [[ブーストのオンオフキーを設定します。]]
jump_st = [[ジャンプキーを設定します。]]
boostmove_st = [[ブースト移動のキーを設定します。]]
rarm_st = [[右腕武器の発射キーを設定します。]]
larm_st = [[左腕武器の発射キーを設定します。]]
rkata_st = [[右肩武器の発射キーを設定します。]]
lkata_st = [[左肩武器の発射キーを設定します。]]
inside_st = [[インサイド武器の発射キーを設定します。]]
select_st = [[決定ボタンのキーを設定します。]]
back_st = [[戻るボタンのキーを設定します。]]


moveforward_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "前進キー", "moveforward_key",moveforward_st ,"NO_LUA","resrc/script/gamepad/modoru_now.lua",156,100,28)
movebackward_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "後退キー", "movebackward_key", movebackward_st ,"NO_LUA","resrc/script/gamepad/modoru_now.lua",156,160,28)
moveleft_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "左移動キー", "moveleft_key", moveleft_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,220,28)
moveright_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "右移動キー", "moveright_key",moveright_st  ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,280,28)
turnleft_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左旋回キー", "turnleft_key", turnleft_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,340,28)
turnright_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右旋回キー", "turnright_key", turnright_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,400,28)
lookup_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"上視点移動キー", "lookup_key", lookup_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,460,28)
lookdown_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"下視点移動キー", "lookdown_key", lookdown_st  ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,520,28)
boostonoff_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"ブーストオンオフキー", "boostonoff_key", boostonoff_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,580,28)
jump_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"ジャンプキー", "jump_key",jump_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,640,28)
boostmove_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"ブースト移動キー", "boostmove_key", boostmove_st ,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,700,28)
rarm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右腕武器発射キー", "rarm_key", rarm_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
larm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左腕武器発射キー", "larm_key", larm_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
rkata_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右肩武器発射キー", "rkata_key", rkata_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
lkata_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左肩武器発射キー", "lkata_key", lkata_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
inside_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"インサイド発射キー", "inside_key", inside_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
select_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"決定ボタンキー", "select_key", select_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)
back_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"戻るボタンキー", "back_key", back_st,"NO_LUA", "resrc/script/gamepad/modoru_now.lua", 156,760,28)




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
