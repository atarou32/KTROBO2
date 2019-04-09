
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

head_st = [[頭部パーツはロボの計算能力を主に決定します。この部位が優秀だと機動性およびロック機能に秀でます。]]
body_t =[[コアパーツはロボの装甲性能、インサイドの装備可不可を決定します。]]
arm_t = [[腕部パーツはロボの武器への二次決定的なエネルギー供給率、リロード性能を決定します。]]
leg_t = [[脚部パーツはロボの積載量、機動性能を決定します。脚部はロボの性能決定に大きな影響を及ぼします。]]
booster_t = [[ブースタパーツはロボの機動性能、ブースト時の挙動を決定します。]]
engine_t = [[エンジンパーツはロボのエネルギープール性能およびエネルギー供給能力を決定します。]]
fcs_t = [[FCSパーツはロボのロック武器のロック性能を決定します。]]
rarm_t = [[右手武器です。様々な種類のパーツがそろっています。]]
larm_t =  [[左手武器です。様々な種類のパーツがそろっています。]]
rkata_t = [[右肩武器です。　肩武器は種類は少ないものの強力な武器が多い印象です。]]
lkata_t = [[左肩武器です。　肩武器は種類は少ないものの強力な武器が多い印象です。]]
inside_t =[[インサイド武器です。　コアパーツが装備可能なものの場合のみ装備できます。]]
head_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "頭部パーツ", "head_part",head_st ,"NO_LUA","resrc/script/garage/partscategory_garage_selected.lua",156,100,28)
body_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "コアパーツ", "core_part", body_t ,"NO_LUA","resrc/script/garage/partscategory_garage_selected.lua",156,160,28)
arm_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "腕部パーツ", "arm_part", arm_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,220,28)
leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "脚部パーツ", "leg_part",leg_t  ,"NO_LUA", "resrc/script/garage/selectpartscategory_garage_selected.lua", 156,280,28)
booster_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"ブースタ", "booster_part", booster_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,340,28)
engine_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"エンジン", "engine_part", engine_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,400,28)
fcs_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"FCS", "fcs_part", fcs_t ,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,460,28)
rarm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右腕武器", "rarm_part",rarm_t  ,"NO_LUA", "resrc/script/garage/selectpartscategory2_garage_selected.lua", 156,520,28)
larm_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左腕武器", "larm_part", larm_t,"NO_LUA", "resrc/script/garage/selectpartscategory2_garage_selected.lua", 156,580,28)
rshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"右肩武器", "rshoul_part",rkata_t ,"NO_LUA", "resrc/script/garage/selectpartscategory3_garage_selected.lua", 156,640,28)
lshoul_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"左肩武器", "lshoul_part", lkata_t ,"NO_LUA", "resrc/script/garage/selectpartscategory3_garage_selected.lua", 156,700,28)
inside_gindex = setButton(tex,tex2,gps,gp_map_name_to_group_index,"インサイド", "inside_part", inside_t,"NO_LUA", "resrc/script/garage/partscategory_garage_selected.lua", 156,760,28)


k2_leg_t =  [[軽量二脚パーツは機動性能にすぐれ、一撃離脱が得意です。半面装甲は低いです。]]          
t2_leg_t  =[[中量二脚パーツはバランスにすぐれ、いろいろな場面に対応できます。]]                    
j2_leg_t  =[[重量二脚パーツは装甲も厚いが機動性能もそこそこそなわっています。]]                   
tank_leg_t  =[[タンク脚パーツは正面からの決戦および拠点防衛に適しています。機動性能は低いです。]]    
k4_leg_t  =[[四脚パーツは積載量が高く、様々な種類の武器の装備および装甲を厚くするのが可能です。]]  
reverse_leg_t =[[逆関節型脚部パーツはジャンプ性能が高く、立体的な機動をとることが可能です。]]          

handgun_at =[[ハンドガンパーツは攻撃性能は低いですが衝撃を与えることが可能です。近距離から中距離で能力を発揮できます。]]
machinegun_at=[[マシンガンパーツは近距離用のロックオン武器で短いリロード性能により連射能力で殺傷性を出しています。]]      
shotgun_at =[[ショットガンパーツは至近距離用のロックオン武器です。扱いには慣れを必要とします。]]                        
rifle_at =[[ライフルパーツは標準的なロックオン武器で近距離から中距離において活躍します。]]                            
bazooka_at=[[バズーカパーツは攻撃性能の高いロックオン武器でリロード性能は低いものの一発が大きいのが特徴です。]]        
sniperrifle_at =  [[スナイパーライフルパーツは長距離から攻撃可能なロックオン武器です。]]                           



grenede_at= [[グレネードパーツは中近距離用の武器で着弾後爆発します。]]                                             
missile_at=[[ミサイルパーツは誘導性能を持ったミサイルを発射する武器です。]]                                       
rocket_at=[[ロケットパーツはノーロックオン武器で発射後直進します。当てるには相当な熟練が必要です。]]             
hanabigun_at=[[ハナビガンパーツはノーロックオン武器です。使ってみてのお楽しみです。]]                               
pulsegun_at=[[パルスガンパーツはエネルギー武器で使用にロボのエネルギーを必要とします。至近距離で有効な武器です。]] 
plazumagun_at=[[プラズマガンパーツはエネルギー武器です。弾速が遅いのが特徴です。]]                                   
energyrifle_at=[[エネルギーライフルパーツはエネルギー武器です。　ライフルのエネルギー武器版といった感じです。]]       
blade_at=[[ブレードパーツは極至近距離にて堅実な刃にて物理的ダメージを与えます。]]                               
energyblade_at=[[エネルギーブレードパーツは極至近距離にて超高密度なエネルギー刃を発生し、対象を破壊します。]]         
pile_at=[[パイルパーツは超至近距離にて爆発する杭を対象に打ち込んで一撃必殺的なダメージを与えます。]]           




k2_leg_gindex = setButton(tex,tex2, gps,gp_map_name_to_group_index, "軽量二脚", "k2_leg_part",          k2_leg_t           ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,100,28)
t2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "中量二脚", "t2_leg_part",          t2_leg_t          ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,160,28)
j2_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "重量二脚", "j2_leg_part",            j2_leg_t        ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,220,28)
tank_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "タンク", "tank_leg_part",             tank_leg_t     ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,280,28)
k4_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "四脚", "k4_leg_part",             k4_leg_t           ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,340,28)
reverse_leg_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "逆関節", "reverse_leg_part",     reverse_leg_t       ,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 50,400,28)

handgun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハンドガン", "handgun_arm_part",    handgun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,100,28)
machinegun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "マシンガン", "machinegun_arm_part",machinegun_at ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,160,28)
shotgun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ショットガン", "shotgun_arm_part",  shotgun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,220,28)
rifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ライフル", "rifle_arm_part",       rifle_at      ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,280,28)
bazooka_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "バズーカ", "bazooka_arm_part",    bazooka_at     ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,340,28)
sniperrifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "スナイパーライフル", "sniperrifle_arm_part",sniperrifle_at,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,400,28)
grenede_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "グレネード", "grenede_arm_part",           grenede_at              ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,460,28)
missle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ミサイル", "missile_arm_part",                 missile_at           ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,520,28)
rocket_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ロケット", "rocket_arm_part",                        rocket_at     ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,580,28)
hanabigun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハナビガン", "hanabigun_arm_part",                  hanabigun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,640,28)
pulsegun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パルスガン", "pulsegun_arm_part",                 pulsegun_at      ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 450,700,28)
plazumagun_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "プラズマガン", "plazumagun_arm_part",           plazumagun_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,100,28)
energyrifle_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "エネルギーライフル", "energyrifle_arm_part",     energyrifle_at  ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,160,28)
blade_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ブレード", "blade_arm_part",                              blade_at            ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,220,28)
energyblade_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "エネルギーブレード", "energybladea_arm_part",         energyblade_at   ,"resrc/script/garage/partscategory2_garage_focused.lua", "resrc/script/garage/partscategory2_garage_selected.lua", 800,280,28)
pile_arm_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パイル", "pile_arm_part",                      pile_at                ,              "NO_LUA"                      , "resrc/script/garage/partscategory2_garage_selected.lua", 800,340,28)

arm_gindex_start = handgun_arm_gindex
arm_gindex_end = pile_arm_gindex

hai_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "ハイ", "hai", "提案に承諾します。", "NO_LUA", "NO_LUA",100,150,28)
iie_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "イイエ", "iie", "提案を却下します。", "NO_LUA", "NO_LUA",100,150,28)

sellp_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "売却", "sellp", "パーツを売却します。", "NO_LUA", "NO_LUA",100,150,28)
equipp_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "装着", "equipp", "パーツを装着します。", "NO_LUA", "NO_LUA",100,150,28)

ok_gindex = setButton(tex,tex2, gps, gp_map_name_to_group_index, "OK", "ok", "この世の中だまってうなずくしかない時もある。", "NO_LUA", "NO_LUA",100,150,28)



chaingun_st = [[チェインガンは殺傷能力の高い弾を連続で発射します。]]
grenede_st = [[グレネード砲は着弾すると爆発する弾を一定間隔で発射します。]]
hanabi_st = [[ハナビ砲は使ってみてのお楽しみです。]]
missile_st = [[ミサイル砲は誘導性能を持つミサイル弾を発射します。複数ロックすると複数発射できます。]]
plazuma_st =[[プラズマ砲はエネルギー武器です。弾速は遅いです。]]
pulse_st =[[パルス砲はエネルギー武器です。至近距離で効力を発揮します。]]
raser_st = [[レーザー砲はエネルギー武器です。花形の武器です。]]
rocket_st = [[ロケット砲はノーロック武器です。腕武器に同期して発射されます。]]


chaingun_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "チェインガン", "chaingun_shoul_part",  chaingun_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,400,28)
grenede_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "グレネード", "grenede_shoul_part",  grenede_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,460,28)
hanabi_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ハナビ", "hanabi_shoul_part",  hanabi_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,520,28)
missile_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ミサイル", "missile_shoul_part",  missile_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,580,28)
plazuma_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "プラズマ", "plazuma_shoul_part",  plazuma_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,640,28)
pulse_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "パルス", "pulse_shoul_part",  pulse_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,700,28)
raser_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "レーザー", "raser_shoul_part",  raser_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,760,28)
rocket_shoul_gindex =  setButton(tex,tex2, gps,gp_map_name_to_group_index, "ロケット", "rocket_shoul_part",  rocket_st,"NO_LUA", "resrc/script/garage/partscategory2_garage_selected.lua", 800,840,28)
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
