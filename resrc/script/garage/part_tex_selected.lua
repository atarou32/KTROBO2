--selected_group_inde = gamen2:getNowSonotokiCursorGroup()
-- selectÇ≥ÇÍÇΩÉOÉãÅ[ÉvÇà⁄ìÆÇ≥ÇπÇÈ
--gamen2:setPartsGroupMoveTo(selected_group_inde, 20,150,238-68,54,"2000.0")
--gamen_id_select_parts_category = 2
--gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,"NO_LUA")
--gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category,selected_group_inde)
--gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
--tex = Texture:getIS(0,0)
--tex2 = Texture:getIS(0,1)

--tex_index = tex:getTexture(KTROBO_GARAGE2_IMG_PATH,4096)
--tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH,4096)

g_parts_indexdayo = gamen2:getNowSonotokiCursorGroup()
lua_exector = LuaExector:getIS(0,0)
lua_exector:setExecCoDoUntilKey("resrc/script/garage/make_dialog_buy_parts.lua", 1)
lua_exector:doAndCoDoExecByKey(1)