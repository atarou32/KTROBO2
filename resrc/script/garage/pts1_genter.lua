--selected_group_inde = gamen2:getNowSonotokiCursorGroup()
-- パーツのテクス
-- selectされたグループを移動させる
--gamen2:setPartsGroupMoveTo(selected_group_inde, 20,150,238-68,54,"2000.0")
--gamen_id_select_parts_category = 2
--gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,"NO_LUA")
--gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category,selected_group_inde)
--gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)

--gamen_id_parts_category = 3
--gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category, "NO_LUA")
--gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category)
pg = gamen2:getHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY) 
--if (pg== KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LEG) then
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,leg_gindex)
gamen2:setPartsGroupMoveTo(leg_gindex, 20,150,238-68,54,"2000.0")
--end

if (pg==KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RARM) then
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,rarm_gindex)
gamen2:setPartsGroupMoveTo(rarm_gindex, 20,150,238-68,54,"2000.0")
end


if (pg==KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LARM) then
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,larm_gindex)
gamen2:setPartsGroupMoveTo(larm_gindex, 20,150,238-68,54,"2000.0")
end


if (pg==KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RKATA) then
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,rshoul_gindex)
gamen2:setPartsGroupMoveTo(rshoul_gindex, 20,150,238-68,54,"2000.0")
end


if (pg==KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_LKATA) then
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,lshoul_gindex)
gamen2:setPartsGroupMoveTo(lshoul_gindex, 20,150,238-68,54,"2000.0")
end


--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,shop_gindex)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,selected_group_inde)
start_index = gamen2:getCPPPartsIndex(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START)
end_index =   gamen2:getCPPPartsIndex(KTROBO_GAMEN2_SCENE_ID_GARAGE, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END)
for i=start_index,end_index do
--gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,i,0)
gamen2:setPartsGroupMoveTo(i,1200,150,(238-68)*2+100,27,"1500.0")
end
--gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category)
--gamen_id_now = gamen_id_parts_category
ss_i = gamen2:getNowSonotokiCursorGroup()
if ((ss_i <start_index) or (ss_i >end_index)) then
ss_i = start_index
end

if (ss_i > start_index) then
gamen2:setPartsGroupMoveTo(ss_i-1,700,40,(238-68)*2+100,27,"500.0")

end
if (ss_i < end_index) then
gamen2:setPartsGroupMoveTo(ss_i+1,700,120,(238-68)*2+100,27,"500.0")
end
gamen2:setPartsGroupMoveTo(ss_i,600,80,(238-68)*2+100,27,"500.0")


--gamen2:setPartsGroupMoveTo(start_index+1,700,120,(238-68)*2+100,27,"1500.0")
--gamen2:setPartsGroupMoveTo(ss_i,600,80,(238-68)*2+100,27,"1500.0")
