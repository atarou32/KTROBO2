selected_group_inde = gamen2:getNowSonotokiCursorGroup()
-- selectÇ≥ÇÍÇΩÉOÉãÅ[ÉvÇà⁄ìÆÇ≥ÇπÇÈ
--gamen2:setPartsGroupMoveTo(selected_group_inde, 20,150,238-68,54,"2000.0")
gamen_id_select_parts_category = 2
gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,"resrc/script/garage/p2_genter.lua")
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category,selected_group_inde)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category,shop_gindex)
gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category,assemble_gindex)

gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,handgun_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,machinegun_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,shotgun_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,rifle_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,bazooka_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,sniperrifle_arm_gindex,0) 
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,grenede_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,missle_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,rocket_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,hanabigun_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,pulsegun_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,plazumagun_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,energyrifle_arm_gindex,0) 
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,blade_arm_gindex,0)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,energyblade_arm_gindex,0) 
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,pile_arm_gindex,0)
robog = gamen2:getCPPPartsIndex(KTROBO_GARAGE2_CPPPARTS_PARTSDEF_MYROBO)
gamen2:setSonotokiSetGroupGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category,robog,1)

--gamen2:setPartsGroupMoveTo(handgun_arm_gindex,         770,10+20     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(machinegun_arm_gindex,      700,10+80     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(shotgun_arm_gindex,         700,10+140     ,(238-68)*2     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(rifle_arm_gindex,           700,10+200     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(bazooka_arm_gindex,         700,10+260     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(sniperrifle_arm_gindex,     700,10+320     ,(238-68)*2     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(grenede_arm_gindex,         700,10+380     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(missle_arm_gindex,          700,10+440     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(rocket_arm_gindex,          770,10+500     ,238-68     ,54,"2000.0")
gindex_now_pc2_start = handgun_arm_gindex
gindex_now_pc2_end = rocket_arm_gindex

--gamen2:setPartsGroupMoveTo(hanabigun_arm_gindex,       1200,10+560     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(pulsegun_arm_gindex,        1200,10+620     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(plazumagun_arm_gindex,      1200,10+680     ,(238-68)*2     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(energyrifle_arm_gindex,     1200,10+740     ,(238-68)*2     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(blade_arm_gindex,           1200,10+800     ,238-68     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(energyblade_arm_gindex,     1200,10+860     ,(238-68)*2     ,54,"2000.0")
--gamen2:setPartsGroupMoveTo(pile_arm_gindex,            1200,10+920     ,238-68     ,54,"2000.0")







gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
gamen_id_now = gamen_id_select_parts_category