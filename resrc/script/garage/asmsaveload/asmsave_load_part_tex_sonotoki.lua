selected_group_inde = gamen2:getNowSonotokiCursorGroup()


gamen_id_asmdayo = 2000
gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo, "resrc/script/garage/asmsaveload/asmsaveload_part_tex_focused.lua")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo)
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo)



--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo,asmsave_gindex)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo,asmload_gindex)

gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo,selected_group_inde)
start_index = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START)
sa_inde = gamen2:getCPPPartsSa(KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_START, KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END)

end_index = start_index+sa_inde-1  
end_index2 = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTS_TEX_PARTSDEF_END)
for i=start_index,end_index do
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo,i,0)
end
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo,end_index2,0)

myrobo_index = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo,myrobo_index,1)

gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_asmdayo)
gamen_id_now = gamen_id_asmdayo