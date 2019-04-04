
if (gamen_id_now == 0) then
gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_now)
end

if (gamen_id_now == 2000) then
gamen_id_now = 0
gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_now)
end

if (gamen_id_now == 1000) then
gamen_id_now = 0
gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_now)
end


if (gamen_id_now >0) then
gamen_id_now = gamen_id_now - 1
gamen2:setSonotokiNowSonotoki(KTROBO_GAMEN2_SCENE_ID_GARAGE,gamen_id_now)
end

