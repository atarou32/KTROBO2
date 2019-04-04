tex = Texture:getIS(0,0)
tex2 = Texture:getIS(0,1)

tex_index = tex:getTexture(KTROBO_GARAGE2_IMG_PATH, 4096)
tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH,4096)

button_str = [[機体構成のセーブに成功]]
x = 500
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


