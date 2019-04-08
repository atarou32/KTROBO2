
dofile("tolua_glue/tolua.lua")

tex = Texture:getIS(0,0)
tex2 = Texture:getIS(0,1)

tex_index = tex:getTexture(KTROBO_GARAGE2_IMG_PATH, 4096)
tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH,4096)


mes = Message:getIS(0,0)
msgsi = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
msg_siz = mes:getMessageIndexsFromMsgId(KTROBO_MESSAGE_ID_GARAGE_ASSEMBLE_ERROR_TO_LUA,msgsi)
msg_ids = {}
sender_ids = {}
receiver_ids = {}
msgs = {}
fmsgs = {}
for i=1,msg_siz do
  msg_ids[i] = 0
  sender_ids[i] = 0
  receiver_ids[i] = 0
  msgs[i] = 0
  fmsgs[i] = 0
end

mes:getMsgBody(msg_siz,msgsi, msg_ids, sender_ids, receiver_ids, msgs, fmsgs)





button_str = [[é∏îsÇµÇ‹ÇµÇΩ]]
for i=1,msg_siz do

  if (tonumber(msgs[i]) == KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_PURGE_FAILED) then
  button_str = [[íEíÖÇ…é∏îsÇµÇ‹ÇµÇΩ]]
  end
  if (tonumber(msgs[i]) == KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_SELL_FAILED_USED_IN_ASM) then
  button_str = [[ç\ê¨Ç…ä‹ÇﬁÇÃÇ≈îÑÇÍÇ‹ÇπÇÒ]]
  end
  if (tonumber(msgs[i]) == KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_SELL_FAILED_NO_ITEM) then
  button_str = [[ÇªÇÃÉpÅ[ÉcÇÕîÑÇÍÇ‹ÇπÇÒ]]
  end
  if (tonumber(msgs[i]) == KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_EQUIP_FAILED_NO_ITEM) then
  button_str = [[ÇªÇÃÉpÅ[ÉcÇÕëïíÖÇ≈Ç´Ç‹ÇπÇÒ]]
  end
  if (tonumber(msgs[i]) == KTROBO_MESSAGE_MSG_GARAGE_ASSEMBLE_ERROR_TO_LUA_EQUIP_FAILED ) then
  button_str = [[ëïíÖÇ…é∏îsÇµÇ‹ÇµÇΩ]]
  end
end




x = 400
y = 350
offdayo = 5
text_height = 22
width = (238-68)*2
texeddd = tex2:getRenderText(button_str, x + offdayo , y +offdayo, text_height, width- 2*offdayo ,54)
tex2:setRenderTextIsRender(texeddd,true)
tex2:setRenderTextColor(texeddd,0xFF000000)
texe2ddd = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, x, y, width, 54, 68, 376, 238-68, 54)

local g_texsunk = g_texsunk or {}
local g_textsunk = g_textsunk or {}
g_texsunk[texe2ddd] = texe2ddd
g_textsunk[texeddd] = texeddd

for key, value in pairs(g_textsunk) do
tex2:setRenderTextIsRender(value,true)
end
for key, value in pairs(g_texsunk) do
tex2:setRenderTexIsRender(value,true)
end

celd(0)


for key, value in pairs(g_textsunk) do
tex2:setRenderTextIsRender(value,false)
end
for key, value in pairs(g_texsunk) do
tex2:setRenderTexIsRender(value,false)
end

celd(1)


for key, value in pairs(g_textsunk) do
tex2:setRenderTextIsRender(value,true)
end
for key, value in pairs(g_texsunk) do
tex2:setRenderTexIsRender(value,true)
end

celd(2)


for key, value in pairs(g_textsunk) do
tex2:lightdeleteRenderText(value)
end
for key, value in pairs(g_texsunk) do
tex2:lightdeleteRenderTex(value)
end