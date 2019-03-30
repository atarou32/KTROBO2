tex = Texture:getIS(0,0)
tex2 = Texture:getIS(0,1)

tex_index = tex:getTexture(KTROBO_GARAGE2_IMG_PATH, 4096)
tex_index2 = tex2:getTexture(KTROBO_GARAGE2_IMG_PATH,4096)

button_str = "çwì¸Ç…ê¨å˜ÇµÇ‹ÇµÇΩ"
x = 500
y = 350
offdayo = 5
text_height = 22
width = (238-68)*2
texeddd = tex2:getRenderText(button_str, x + offdayo , y +offdayo, text_height, width- 2*offdayo ,54)
tex2:setRenderTextIsRender(texeddd,true)
tex2:setRenderTextColor(texeddd,0xFF000000)
texe2ddd = tex2:getRenderTex(tex_index2, 0xFFFFFFFF, x, y, width, 54, 68, 376, 238-68, 54)

tex2:setRenderTextIsRender(texeddd,false)
tex2:setRenderTexIsRender(texe2ddd,false)

celd(1)
tex2:setRenderTextIsRender(texeddd,true)
tex2:setRenderTexIsRender(texe2ddd,true)

celd(2)
tex2:setRenderTextIsRender(texeddd,false)
tex2:setRenderTexIsRender(texe2ddd,false)

celd(3)
tex2:setRenderTextIsRender(texeddd,true)
tex2:setRenderTexIsRender(texe2ddd,true)

celd(4)
tex2:setRenderTextIsRender(texeddd,false)
tex2:setRenderTexIsRender(texe2ddd,false)

celd(3)
tex2:setRenderTextIsRender(texeddd,true)
tex2:setRenderTexIsRender(texe2ddd,true)

celd(4)
tex2:setRenderTextIsRender(texeddd,false)
tex2:setRenderTexIsRender(texe2ddd,false)


tex2:lightdeleteRenderText(texeddd)
tex2:lightdeleteRenderTex(texe2ddd)