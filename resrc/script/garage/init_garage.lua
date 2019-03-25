
dofile("tolua_glue/tolua.lua")

left = 1000 - 236 - 50;
right = left + 236;
top = 51+50 + 50 + 52+27+150;
bottom = top + 55;
rect = { left,right,top,bottom}


gamen2 = Gamen2:getIS(0,0)
group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "shop", 
"resrc/script/garage/gotoshop_garage_focus.lua", "resrc/script/garage/gotoshop_garage_selected.lua", rect)

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

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "assemble", 
"resrc/script/garage/gotoassemble_garage_focus.lua", "resrc/script/garage/gotoassemble_garage_selected.lua", rect)
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

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "asmsave", 
"resrc/script/garage/gotoasmsave_garage_focus.lua", "resrc/script/garage/gotoasmsave_garage_selected.lua", rect)
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

group_index = gamen2:makePartsGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, "asmload", 
"resrc/script/garage/gotoasmload_garage_focus.lua", "resrc/script/garage/gotoasmload_garage_selected.lua", rect)
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


head_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "頭部パーツ", "head_part", "testdayo","NO_LUA","NO_LUA",156,100,28)
body_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "コアパーツ", "core_part",  "testdayo","NO_LUA","NO_LUA",156,160,28)
arm_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "腕部パーツ", "arm_part",  "testdayo","NO_LUA", "NO_LUA", 156,220,28)
leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "脚部パーツ", "leg_part",  "testdayo","NO_LUA", "NO_LUA", 156,280,28)
booster_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"ブースタ", "booster_part",  "testdayo","NO_LUA", "NO_LUA", 156,340,28)
engine_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"エンジン", "engine_part",  "testdayo","NO_LUA", "NO_LUA", 156,400,28)
fcs_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"FCS", "fcs_part",  "testdayo","NO_LUA", "NO_LUA", 156,460,28)
rarm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右腕武器", "rarm_part",  "testdayo","NO_LUA", "NO_LUA", 156,520,28)
larm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左腕武器", "larm_part",  "testdayo","NO_LUA", "NO_LUA", 156,580,28)
rshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右肩武器", "rshoul_part",  "testdayo","NO_LUA", "NO_LUA", 156,640,28)
lshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左肩武器", "lshoul_part",  "testdayo","NO_LUA", "NO_LUA", 156,700,28)
inside_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"インサイド", "inside_part",  "testdayo","NO_LUA", "NO_LUA", 156,760,28)

k2_leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "軽量二脚", "k2_leg_part",  "testdayo","NO_LUA", "NO_LUA", 50,100,28)
t2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "中量二脚", "t2_leg_part",  "testdayo","NO_LUA", "NO_LUA", 50,160,28)
j2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "重量二脚", "j2_leg_part",  "testdayo","NO_LUA", "NO_LUA", 50,220,28)
tank_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "タンク", "tank_leg_part",  "testdayo","NO_LUA", "NO_LUA", 50,280,28)
k4_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "四脚", "k4_leg_part",  "testdayo","NO_LUA", "NO_LUA", 50,340,28)
reverse_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "逆関節", "reverse_leg_part",  "testdayo","NO_LUA", "NO_LUA", 50,400,28)

handgun_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハンドガン", "handgun_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,100,28)
machinegun_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "マシンガン", "machinegun_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,160,28)
shotgun_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ショットガン", "shotgun_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,220,28)
rifle_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ライフル", "rifle_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,280,28)
bazooka_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "バズーカ", "bazooka_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,340,28)
sniperrifle_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "スナイパーライフル", "sniperrifle_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,400,28)
grenede_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "グレネード", "grenede_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,460,28)
missle_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ミサイル", "missile_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,520,28)
rocket_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ロケット", "rocket_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,580,28)
hanabigun_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハナビガン", "hanabigun_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,640,28)
pulsegun_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パルスガン", "pulsegun_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 450,700,28)
plazumagun_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "プラズマガン", "plazumagun_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 600,100,28)
energyrifle_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "エネルギーライフル", "energyrifle_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 600,160,28)
blade_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ブレード", "blade_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 600,220,28)
energyblade_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "エネルギーブレード", "energybladea_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 600,280,28)
pile_rarm_g_index =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パイル", "pile_rarm_part",  "testdayo","NO_LUA", "NO_LUA", 600,340,28)



--gamen2:setPartsGroupMoveTo(group_index, 0,10,236,55,"6000.0")

--LuaExector:getIS(0,0):setExecCoDoUntilTime("resrc/script/garage/moveto.lua", 2)