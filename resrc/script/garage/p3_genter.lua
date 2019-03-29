selected_group_inde = gamen2:getNowSonotokiCursorGroup()
-- selectÇ≥ÇÍÇΩÉOÉãÅ[ÉvÇà⁄ìÆÇ≥ÇπÇÈ

gamen2:setPartsGroupMoveTo(rshoul_gindex, 1200,150,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(lshoul_gindex, 1200,150,238-68,54,"2000.0")

hensu = gamen2:getHensuu(KTROBO_GAMEN2_SCENE_ID_GARAGE,KTROBO_GARAGE2_HENSUU_ID_PARTSCATEGORY)
selected_group_inde = lshoul_gindex
if (hensu == KTROBO_GARAGE2_HENSUU_PARTS_CATEGORY_RKATA) then
  selected_group_inde = rshoul_gindex
end
  
gamen2:setPartsGroupMoveTo(selected_group_inde, 20,150,238-68,54,"2000.0")

gamen2:setPartsGroupMoveTo(chaingun_shoul_gindex,700,20+10,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(grenede_shoul_gindex,700,80+10,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(hanabi_shoul_gindex ,700,140+10,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(missile_shoul_gindex ,700,200+10,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(plazuma_shoul_gindex,700,260+10,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(pulse_shoul_gindex ,700,320+10,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(raser_shoul_gindex,700,380+10,238-68,54,"2000.0")
gamen2:setPartsGroupMoveTo(rocket_shoul_gindex ,700,440+10,238-68,54,"2000.0")


--gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
--gamen_id_now = gamen_id_select_parts_category