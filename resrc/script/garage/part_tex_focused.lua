selected_group_inde = gamen2:getNowSonotokiCursorGroup()

--gamen_id_parts_category = 3
--gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category, "NO_LUA")
--gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category)

--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,shop_gindex)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,selected_group_inde)
start_index = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START)
sa_inde = gamen2:getCPPPartsSa(KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END)
end_index = start_index + sa_inde -1
end_index2 =   gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END)
for i=start_index,end_index do
--gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category,i,0)
gamen2:setPartsGroupMoveTo(i,1200,150,(238-68)*2+100,27,"500.0")
end
gamen2:setPartsGroupMoveTo(end_index2,1200,150,(238-68)*2+100,27,"500.0")
--gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_parts_category)

if (selected_group_inde ~= end_index2) then

if (selected_group_inde > start_index) then
gamen2:setPartsGroupMoveTo(selected_group_inde-1,700,40,(238-68)*2+100,27,"500.0")

end
if (selected_group_inde < end_index) then
gamen2:setPartsGroupMoveTo(selected_group_inde+1,700,120,(238-68)*2+100,27,"500.0")
end

end

if (selected_group_inde == end_index2) then
gamen2:setPartsGroupMoveTo(end_index,700,40,(238-68)*2+100,27,"500.0")
end
if (selected_group_inde == end_index) then
gamen2:setPartsGroupMoveTo(end_index2,700,120,(238-68)*2+100,27,"500.0")
end

gamen2:setPartsGroupMoveTo(selected_group_inde,600,80,(238-68)*2+100,27,"500.0")
