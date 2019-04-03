
tex = Texture:getIS(0,0)
tex2 = Texture:getIS(0,1)

tex_index = tex:getTexture(KTROBO_GARAGE2_IMG_PATH,4096)
tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH,4096)
next_gamen_id_now = gamen_id_now + 1

local_parts_index_dayo = g_parts_indexdayo

-- まず変数を持ってきて　外せる種類のパーツだったら外す
pg = gamen2:getHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY) 
can_hazusu = false
if (pg== KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RARM) then
can_hazusu = true
end
if (pg== KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LKATA) then
can_hazusu = true
end
if (pg== KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RKATA) then
can_hazusu = true
end
if (pg== KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LARM) then
can_hazusu = true
end
if (pg== KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_INSIDE) then
can_hazusu = true
end

if (can_hazusu == false) then

gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,next_gamen_id_now,"NO_LUA")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now)
gamen2:setSonotokiSetGroupOnlyRenderGroupFromNowSonotokiIsRender(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now,shop_gindex)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now,ok_gindex,0)
gamen2:deleteTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE)
--gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_ASSEMBLE_PARTS_WHAT,KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_MADA)
gamen2:setTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL,1, ok_gindex)


gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now)
gamen2:setPartsGroupMoveTo(ok_gindex, 600,450,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(local_parts_index_dayo, 600,320,(238-68)*2+100,27,"2000.0")

button_str = "このパーツは残念ながら外せません。"
 offdayo = (27 - 20)
texe2 = tex2:getRenderText(button_str, 600+offdayo , 380+offdayo-2, 20, (238-68)*3 ,27)
  tex2:setRenderTextColor(texe2,0xFF000000)
 
  tex2:setRenderTextIsRender(texe2,true)
  
 
  texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 600, 380, (238-68)*2+100, 27, 68, 376, 238-68, 54)

celd(0)

tex2:lightdeleteRenderTex(texe)
tex2:lightdeleteRenderText(texe2)
gamen2:deleteTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE)

gamen2:setPartsGroupMoveTo(local_parts_index_dayo,600,80,(238-68)*2+100,27,"500.0")

gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_now)





end


if (can_hazusu == true) then
-- sonotokiを作って
gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,next_gamen_id_now,"NO_LUA")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now)
gamen2:setSonotokiSetGroupOnlyRenderGroupFromNowSonotokiIsRender(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now,shop_gindex)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now,hai_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now,iie_gindex,0)
gamen2:deleteTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_ASSEMBLE_PARTS_WHAT,KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_PURGE)
gamen2:makeHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ID_ASSEMBLE_PARTS_CONFIRM,KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_MADA)

gamen2:setTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_ASSEMBLE_PARTS_CONFIRM,KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_YES, hai_gindex)
gamen2:setTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_ASSEMBLE_PARTS_CONFIRM,KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_NO, iie_gindex)
gamen2:setTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL,1, hai_gindex)
gamen2:setTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_LUA_KEY_CALL,1, iie_gindex)



gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, next_gamen_id_now)
gamen2:setPartsGroupMoveTo(hai_gindex, 600,450,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(iie_gindex, 600,520,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(local_parts_index_dayo, 600,320,(238-68)*2+100,27,"2000.0")

button_str = "このパーツを外しますか？"
 offdayo = (27 - 20)
texe2 = tex2:getRenderText(button_str, 600+offdayo , 380+offdayo-2, 20, (238-68)*3 ,27)
  tex2:setRenderTextColor(texe2,0xFF000000)
 
  tex2:setRenderTextIsRender(texe2,true)
  
 
  texe = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, 600, 380, (238-68)*2+100, 27, 68, 376, 238-68, 54)

celd(0)



hensuu = gamen2:getHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_WHAT)
tex2:lightdeleteRenderTex(texe)
tex2:lightdeleteRenderText(texe2)
gamen2:deleteTempHensuuRule(KTROBO_GAMEN2_SCENE_ID_GARAGE)
if(hensuu ~= KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_MADA) then

if (hensuu == KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_YES) then
  message = Message:getIS(0,0)
  message:makeMessage(KTROBO_MESSAGE_ID_GARAGE_ASSEMBLE_PARTS, local_parts_index_dayo, KTROBO_MESSAGE_RECEIVER_ID_SYSTEM, 
  KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_PURGE_PARTS, "0.0",true)
  gamen2:setPartsGroupMoveTo(local_parts_index_dayo,600,80,(238-68)*2+100,27,"500.0")
 
  -- 確認画面に飛ぶ
  --lua_exector = LuaExector:getIS(0,0)
  --lua_exector:setExecCoDoUntilKey("resrc/script/garage/assemble/make_dialog_sell_parts.lua", 2)
  --lua_exector:doAndCoDoExecByKey(2)
  
  
end
if (hensuu == KTROBO_GARAGE2_HENSUU_ASSEMBLE_PARTS_NO) then
gamen2:setPartsGroupMoveTo(local_parts_index_dayo,600,80,(238-68)*2+100,27,"500.0")

gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_now)
--　確認画面に飛ぶ
--lua_exector = LuaExector:getIS(0,0)
--lua_exector:setExecCoDoUntilKey("resrc/script/garage/assemble/make_dialog_equip_parts.lua", 2)
--lua_exector:doAndCoDoExecByKey(2)
end

end