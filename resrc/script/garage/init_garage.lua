
dofile("tolua_glue/tolua.lua")

left = 1000 - 236 - 50;
right = left + 236;
top = 51+50 + 50 + 52+27+150;
bottom = top + 55;
rect = { left,right,top,bottom}


gamen2 = Gamen2:getIS(0,0)
group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "貴重なGを払ってパーツを購入します。ご利用は戦略的に。", 
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

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "アセンブルします。購入済みのパーツを使って自分独自の機体を作ります。", 
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

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "現在の機体をファイルに保存します。16個まで保存できます。", 
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

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "保存済みの機体をロードします。ロード完了すると現在の機体は失われます。", 
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
  tex_index2 = tex:getTexture(KTROBO_GARAGE2_IMG_PATH, 4096)
  
  offdayo = (54 - text_height)/2
  texe2 = tex:getRenderText(button_str, x + offdayo , y +offdayo, text_height, width- 2*offdayo ,54)
  tex:setRenderTextColor(texe2,0xFF000000)
  left = x+offdayo
  right = left + width-2*offdayo
  top = y +offdayo
  bottom = top + 54 -2*offdayo
  rect ={left,right,top,bottom}
  p_index = gamen2:setPartsGroupSetText(group_index, false, texe2, rect)
 -- tex:setRenderTextIsRender(texe2,false)
  setGpPartToGp(gp, texe2,rect,p_index)
  
  texe = tex:getRenderTex(tex_index2, 0xFFFFFFFF, x, y, width, 54, 68, 376, 238-68, 54)
  left = x
  right = left + 238-68
  top = y
  bottom = top + 54
  rect ={left,right,top,bottom}
  p_index = gamen2:setPartsGroupSetTex(group_index, false, texe, rect)

  setGpPartToGp(gp,texe,rect,p_index)
  setGpToGps(gpx,gp_map, gp, group_index, button_id_str, rect)
  return group_index
end


head_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "頭部パーツ", "head_part", "testdayo","NO_LUA","resrc/script/garage/partscategory_garage_selected.lua",156,100,28)
body_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "コアパーツ", "core_part",  "testdayo","NO_LUA","resrc/script/garage/partscategory_garage_selected.lua",156,160,28)
arm_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "腕部パーツ", "arm_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,220,28)
leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "脚部パーツ", "leg_part",  "testdayo","NO_LUA", "resrc/script/garage/selectpartscategory_garage_selected.lua", 156,280,28)
booster_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"ブースタ", "booster_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,340,28)
engine_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"エンジン", "engine_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,400,28)
fcs_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"FCS", "fcs_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,460,28)
rarm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右腕武器", "rarm_part",  "testdayo","NO_LUA", "resrc/script/garage/selectpartscategory2_garage_selected.lua", 156,520,28)
larm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左腕武器", "larm_part",  "testdayo","NO_LUA", "resrc/script/garage/selectpartscategory2_garage_selected.lua", 156,580,28)
rshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右肩武器", "rshoul_part",  "testdayo","NO_LUA", "resrc/script/garage/selectpartscategory3_garage_selected.lua", 156,640,28)
lshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左肩武器", "lshoul_part",  "testdayo","NO_LUA", "resrc/script/garage/selectpartscategory3_garage_selected.lua", 156,700,28)
inside_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"インサイド", "inside_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,760,28)

k2_leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "軽量二脚", "k2_leg_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,100,28)
t2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "中量二脚", "t2_leg_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,160,28)
j2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "重量二脚", "j2_leg_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,220,28)
tank_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "タンク", "tank_leg_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,280,28)
k4_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "四脚", "k4_leg_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,340,28)
reverse_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "逆関節", "reverse_leg_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,400,28)

handgun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハンドガン", "handgun_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,100,28)
machinegun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "マシンガン", "machinegun_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,160,28)
shotgun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ショットガン", "shotgun_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,220,28)
rifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ライフル", "rifle_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,280,28)
bazooka_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "バズーカ", "bazooka_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,340,28)
sniperrifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "スナイパーライフル", "sniperrifle_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,400,28)
grenede_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "グレネード", "grenede_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,460,28)
missle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ミサイル", "missile_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,520,28)
rocket_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ロケット", "rocket_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,580,28)
hanabigun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハナビガン", "hanabigun_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,640,28)
pulsegun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パルスガン", "pulsegun_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,700,28)
plazumagun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "プラズマガン", "plazumagun_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,100,28)
energyrifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "エネルギーライフル", "energyrifle_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,160,28)
blade_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ブレード", "blade_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,220,28)
energyblade_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "エネルギーブレード", "energybladea_arm_part",  "testdayo","resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,280,28)
pile_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パイル", "pile_arm_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,340,28)

arm_gindex_start = handgun_arm_gindex
arm_gindex_end = pile_arm_gindex


chaingun_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "チェインガン", "chaingun_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,400,28)
grenede_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "グレネード", "grenede_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,460,28)
hanabi_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハナビ", "hanabi_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,520,28)
missile_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ミサイル", "missile_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,580,28)
plazuma_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "プラズマ", "plazuma_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,640,28)
pulse_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パルス", "pulse_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,700,28)
raser_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "レーザー", "raser_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,760,28)
rocket_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ロケット", "rocket_shoul_part",  "testdayo","NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,840,28)
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
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,shop_gindex)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,assemble_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,asmsave_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,asmload_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start,shop_gindex,0)
gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_start)
gamen_id_now = gamen_id_garage_start
--texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 0, 50, 236, 51, 0, 48, 136, 51);
--gamen2:setPartsGroupMoveTo(group_index, 0,10,236,55,"6000.0")

--LuaExector:getIS(0,0):setExecCoDoUntilTime("resrc/script/garage/moveto.lua", 2)

gamen_id_garage_shop_start = 1
gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_garage_shop_start, "resrc/script/garage/start_garage_shop.lua")
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

gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_IS_LOAD_PARTS, KTROBO_GARAGE2_HENSUU_IS_LOAD_PARTS_NO)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_HEAD)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY2, KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY2_LEG_K2)

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
