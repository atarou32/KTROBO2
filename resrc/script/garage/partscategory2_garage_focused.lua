selected_group_inde = gamen2:getNowSonotokiCursorGroup()
-- select‚³‚ê‚½ƒOƒ‹[ƒv‚ðˆÚ“®‚³‚¹‚é




for i=arm_gindex_start,arm_gindex_end do
  gamen2:setPartsGroupMoveTo(i,      1200,10+80     ,238-68     ,54,"700.0")

end

bool_dayo = false
if (selected_group_inde > arm_gindex_start) then
  if (selected_group_inde == gindex_now_pc2_start) then
    -- ˆêŒÂ‰º‚É‚¸‚ç‚·
    gindex_now_pc2_start = gindex_now_pc2_start-1
    gindex_now_pc2_end = gindex_now_pc2_end -1
    i = gindex_now_pc2_start 
    gamen2:setPartsGroupMoveTo(gindex_now_pc2_start,         770,10+20     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+1,      700,10+80     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+2,         700,10+140     ,(238-68)     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+3,           700,10+200     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+4,         700,10+260     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+5,     700,10+320     ,(238-68)     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+6,         700,10+380     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+7,          700,10+440     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+8,          770,10+500     ,238-68     ,54,"1000.0")
    bool_dayo = true
  end
end

if (selected_group_inde < arm_gindex_end) then
  if (selected_group_inde == gindex_now_pc2_end) then
    gindex_now_pc2_start = gindex_now_pc2_start + 1
    gindex_now_pc2_end = gindex_now_pc2_end + 1
    i = gindex_now_pc2_start
      gamen2:setPartsGroupMoveTo(gindex_now_pc2_start,         770,10+20     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+1,      700,10+80     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+2,         700,10+140     ,(238-68)     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+3,           700,10+200     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+4,         700,10+260     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+5,     700,10+320     ,(238-68)   ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+6,         700,10+380     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+7,          700,10+440     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+8,          770,10+500     ,238-68     ,54,"1000.0")
    bool_dayo = true
  end
end

if (bool_dayo == false) then
i = gindex_now_pc2_start
    gamen2:setPartsGroupMoveTo(gindex_now_pc2_start,         770,10+20     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+1,      700,10+80     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+2,         700,10+140     ,(238-68)     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+3,           700,10+200     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+4,         700,10+260     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+5,     700,10+320     ,(238-68)     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+6,         700,10+380     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+7,          700,10+440     ,238-68     ,54,"1000.0")
    gamen2:setPartsGroupMoveTo(i+8,          770,10+500     ,238-68     ,54,"1000.0")


end

--gamen2:setPartsGroupMoveTo(selected_group_inde, 20,250,238-68,54,"2000.0")
--gamen_id_select_parts_category = 2
--gamen2:makeSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_select_parts_category,"NO_LUA")
--gamen2:setSonotokiMakeKo(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)
--gamen2:setSonotokiSetGroupOnlyRenderGroup(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category,selected_group_inde)
--gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE, gamen_id_select_parts_category)

