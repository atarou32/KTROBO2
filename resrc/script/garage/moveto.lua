
dofile("tolua_glue/tolua.lua")


gamen2:setPartsGroupMoveTo(group_index, 500,510,236,55,"2000.0")
celd(0)

gamen2:setPartsGroupMoveTo(group_index, 1000,510,236,55,"2000.0")
celd(1)



hairetu ={}
rect = { 100,100,236,55 }
hairetu[1] = rect

gamen2:setPartsGroupMoveTo(group_index, rect[1],rect[2],rect[3],rect[4],"2000.0")
celd(2)
rect = { 300,400,236,55 }


gamen2:setPartsGroupMoveTo(group_index, hairetu[1][1],hairetu[1][2],hairetu[1][3],hairetu[1][4],"2000.0")

celd(3)


gamen2:setPartsGroupMoveTo(group_index, rect[1],rect[2],rect[3],rect[4],"2000.0")
