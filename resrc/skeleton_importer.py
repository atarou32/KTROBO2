import sys
import bpy

meshname="boosterj"
outputfilepath = "C:/Users/ataru/project5/"
outputfileprefix="boosterj"
outputfilename = outputfilepath + outputfileprefix+".mesh"
uvname="UVMap"
armaturename="Armature"
parentbonename="doBone"

outputanimefilename = outputfilepath + outputfileprefix+".anime"
actionname = "ArmatureAction"
scenename= "Scene"
mesh = bpy.data.meshes[meshname]

vertices = mesh.vertices








class vert_cl:
    def __init__(self, index, co_x, co_y, co_z, nor_x, nor_y, nor_z):
        self.index = index
        self.co_x = co_x
        self.co_y = co_y
        self.co_z = co_z
        self.nor_x = nor_x
        self.nor_y = nor_y
        self.nor_z = nor_z
        self.uv_x = -1
        self.uv_y = -1
    
    def set_UV(self,u,v):
        self.uv_x = u
        self.uv_y = v
    
    def write_to_file(self,f):
        f.write(str(self.index))
        f.write(",")
        f.write(str(round(self.co_x,5)))
        f.write(",")
        f.write(str(round(self.co_y,5)))
        f.write(",")
        f.write(str(round(self.co_z,5)))
        f.write(",")
        f.write(str(round(self.nor_x,5)))
        f.write(",")
        f.write(str(round(self.nor_y,5)))
        f.write(",")
        f.write(str(round(self.nor_z,5)))
        f.write(",")
        f.write(str(round(self.uv_x,5)))
        f.write(",")
        f.write(str(round(self.uv_y,5)))
        f.write(",;\n")

class poly_cl:
    def __init__(self, index, nor_x, nor_y, nor_z, mat_index, vert1_inde, vert2_inde, vert3_inde):
        self.index = index
        self.nor_x = nor_x
        self.nor_y = nor_y
        self.nor_z = nor_z
        self.mat_index = mat_index
        self.vert1_inde = vert1_inde
        self.vert2_inde = vert2_inde
        self.vert3_inde = vert3_inde
    
    def write_to_file(self, f):
        f.write(str(self.index))
        f.write(",")
        f.write(str(round(self.nor_x,5)))
        f.write(",")
        f.write(str(round(self.nor_y,5)))
        f.write(",")
        f.write(str(round(self.nor_z,5)))
        f.write(",")
        f.write(str(self.mat_index))
        f.write(",")
        f.write(str(round(self.vert1_inde,5)))
        f.write(",")
        f.write(str(round(self.vert2_inde,5)))
        f.write(",")
        f.write(str(round(self.vert3_inde,5)))
        f.write(",;\n")

vert_classes = []

for index, vert in vertices.items():
    cl = vert_cl(vert.index, vert.co.x, vert.co.y, vert.co.z, vert.normal.x, vert.normal.y, vert.normal.z)
    vert_classes.insert(vert.index, cl)
    
    
    
    
    



polygons = mesh.polygons
me = bpy.data.meshes[meshname]
uv = me.uv_layers[uvname]

poly_classes = []
poly_bonus_index= len(polygons)
vert_bonus_dic = {}

def check_and_insert_vertclass(uv_layer, vertice1, loop1):
    uv_x = vert_classes[vertice1].uv_x
    uv_y = vert_classes[vertice1].uv_y
    uv_layer_x = uv_layer.data[loop1].uv.x
    uv_layer_y = uv_layer.data[loop1].uv.y
    
    if (uv_x < 0 and uv_y < 0):
        v_c = vert_classes[vertice1]
        v_c.set_UV(uv_layer_x, uv_layer_y)
       # vert_classes[vertice1] = v_c
        return 2, vertice1
    elif ((uv_x != uv_layer_x) or (uv_y != uv_layer_y)):
        #print("add new vertex "+str(vertex_inde))
        vertex_inde = len(vert_classes)
        v_c = vert_classes[vertice1]
        cl = vert_cl(vertex_inde, v_c.co_x, v_c.co_y, v_c.co_z, v_c.nor_x, v_c.nor_y, v_c.nor_z)
        cl.set_UV(uv_layer_x, uv_layer_y)
        vert_classes.insert(vertex_inde, cl)
        vert_bonus_dic[vertex_inde] = {"vert_cl":cl, "vertice_index":vertice1}
        return 1, vertex_inde
    
    else:
        # same so dont have to update   
        v_c = vert_classes[vertice1]
        v_c.set_UV(uv_layer_x, uv_layer_y)
        return 0, vertice1


for index, poly in polygons.items():
    if (poly.loop_total >= 4):
        if (poly.loop_total + poly.loop_start -1 != poly.loop_indices[3]):
            print("alert"+str(poly.loop_indices[3])+str(index))
            print("   "+str(poly.loop_indices[0]))
            print("   "+str(poly.loop_indices[1]))
            print("   "+str(poly.loop_indices[2]))
            print("   "+str(poly.loop_indices[3]))
            
        b1, vertice1 = check_and_insert_vertclass(uv,  poly.vertices[0], poly.loop_start)
        b2, vertice2 = check_and_insert_vertclass(uv,  poly.vertices[1], poly.loop_start+1)
        b3, vertice3 = check_and_insert_vertclass(uv,  poly.vertices[2], poly.loop_start+2)
        b4, vertice4 = check_and_insert_vertclass(uv,  poly.vertices[3], poly.loop_start+3)
        pc1 = poly_cl(poly.index, poly.normal.x, poly.normal.y, poly.normal.z, poly.material_index, vertice1, vertice2, vertice3)
        poly_classes.insert(poly.index, pc1)
        new_index = poly_bonus_index
        poly_bonus_index = poly_bonus_index + 1
        pc2 = poly_cl(new_index, poly.normal.x, poly.normal.y, poly.normal.z, poly.material_index, vertice1, vertice3, vertice4)
        poly_classes.insert(new_index, pc2)

    else:
        b1, vertice1 = check_and_insert_vertclass(uv,  poly.vertices[0], poly.loop_start)
        b2, vertice2 = check_and_insert_vertclass(uv,  poly.vertices[1], poly.loop_start+1)
        b3, vertice3 = check_and_insert_vertclass(uv,  poly.vertices[2], poly.loop_start+2)
        pc = poly_cl(poly.index, poly.normal.x, poly.normal.y, poly.normal.z, poly.material_index, vertice1, vertice2, vertice3)
        poly_classes.insert(poly.index, pc)






parentbone = bpy.data.armatures[armaturename].bones[parentbonename]
meshobj = bpy.data.objects[meshname]
       



#print(me.materials[0].active_texture.image.name)
#print(dir(bpy.data.textures[0]))
print("now start polypoly")
print("pc = " + str(len(poly_classes)))
print("vc = " + str(len(vert_classes)))     


# uvmap


#me = bpy.data.meshes['body01']
#uv = me.uv_textures['UVMap']
#print(len(uv.data))
#print(len(me.vertices))
#print(dir(bpy.data.meshes['body01']))
#for j,face in enumerate(me.vertices):
#  face_uv = uv.data[j]
#  print(face_uv.u)


f = open(outputfilename, "w")

f.write("verts{\n")
f.write(str(len(vert_classes))+";\n")
for vc in vert_classes:
    vc.write_to_file(f)
f.write("}\n")





f.write("polygons{\n")
f.write(str(len(poly_classes))+";\n")
for pc in poly_classes:
    pc.write_to_file(f)
f.write("}\n")


f.write("materials{\n")
f.write(str(len(me.materials))+";\n")
index = 0
for material in me.materials:
    f.write(str(index)+",")
    f.write(str(round(material.diffuse_color.r,5)))
    f.write(",")
    f.write(str(round(material.diffuse_color.g,5)))
    f.write(",")
    f.write(str(round(material.diffuse_color.b,5)))
    f.write(",")
    print(dir(material.active_texture))
    print(material.active_texture)
    if (material.active_texture == None):
        f.write("none.png")
    else:
        f.write(material.active_texture.image.name)
    f.write(",;\n")
    index = index + 1

f.write("}\n")


vertex_g_index_to_bone_st_index = {}

def add_bone_info(parent_bone, bone_st):
    len_bon = len(bone_st)
    vertex_g_index = meshobj.vertex_groups[parent_bone.name].index
    vertex_g_index_to_bone_st_index[vertex_g_index] = len_bon
    bone_st.insert(len_bon,{"index":len_bon, "vertex_g_index":vertex_g_index, "bone":parent_bone})
    for child in parent_bone.children:
        add_bone_info(child, bone_st)

bonne_st = []

add_bone_info(parentbone, bonne_st)

def write_matrix(f, mat):
    mat = mat.to_4x4()
    f.write(str(round(mat[0][0],5)))
    f.write(",")
    f.write(str(round(mat[0][1],5)))
    f.write(",")
    f.write(str(round(mat[0][2],5)))
    f.write(",")
    f.write(str(round(mat[0][3],5)))
    f.write(",")
    f.write(str(round(mat[1][0],5)))
    f.write(",")
    f.write(str(round(mat[1][1],5)))
    f.write(",")
    f.write(str(round(mat[1][2],5)))
    f.write(",")
    f.write(str(round(mat[1][3],5)))
    f.write(",")
    f.write(str(round(mat[2][0],5)))
    f.write(",")
    f.write(str(round(mat[2][1],5)))
    f.write(",")
    f.write(str(round(mat[2][2],5)))
    f.write(",")
    f.write(str(round(mat[2][3],5)))
    f.write(",")
    f.write(str(round(mat[3][0],5)))
    f.write(",")
    f.write(str(round(mat[3][1],5)))
    f.write(",")
    f.write(str(round(mat[3][2],5)))
    f.write(",")
    f.write(str(round(mat[3][3],5)))
    f.write(",")
    f.write(";\n")

f.write("boneinfo{\n")
f.write(str(len(bonne_st))+";\n")
for bone_dic in bonne_st:
    f.write(str(bone_dic["index"])+",")
    f.write(bone_dic["bone"].name+",;\n")
    f.write("matrix;")
    write_matrix(f, bone_dic["bone"].matrix)
    f.write("matrix_local;")
    write_matrix(f, bone_dic["bone"].matrix_local)

f.write("}\n")
    
    
    

def write_bone_layer(f, parent_bone, offset):

    f.write(offset + "bone_layer{\n")
    f.write(offset + parent_bone.name+";\n")
    f.write(offset + str(len(parent_bone.children))+";\n")
    for child in parent_bone.children:
        write_bone_layer(f, child, offset + "  ")

    f.write(offset + "}\n")

write_bone_layer(f, parentbone, "")


class bone_weights:
    def __init__(self, vert_index):
        self.vert_index = vert_index
        self.bone_weight_dic = {}

    def setWeights(self, vertex_g_index, weight):
        self.bone_weight_dic[vertex_g_index] = weight
    
    def write_to_file(self, f, bone_st,to_bone_st_index ):
        f.write(str(self.vert_index))
        f.write(",")
        if (len(self.bone_weight_dic) == 0):
            f.write("0,;\n")
        else:
            f.write(str(len(self.bone_weight_dic))+",")
            for vertex_g_index, weight in self.bone_weight_dic.items():
                bone_st_index = to_bone_st_index[vertex_g_index]
                bone_info = bone_st[bone_st_index]
                f.write(str(bone_info["index"])+",")
                f.write(str(round(weight,5))+",")
            
            f.write(";\n")
            
            
            
        
be_dic = {}

for vert in vertices:
    groups = vert.groups
    be = bone_weights(vert.index)
    if (len(groups) == 0):
        print("no group")
    else:
        for g in groups:
            for b_dic in bonne_st:
                if (b_dic["vertex_g_index"] == g.group):
                    be.setWeights(b_dic["vertex_g_index"], g.weight)
                    print(str(g.weight))
    
    be_dic[vert.index] = be

# for_bonus_verts
for vert_inde, vert_dic in vert_bonus_dic.items():
    groups = vertices[vert_dic["vertice_index"]].groups
    be = bone_weights(vert_inde)
    if (len(groups) == 0):
        print("no group")
    else:
        for g in groups:
            for b_dic in bonne_st:
                if (b_dic["vertex_g_index"] == g.group):
                    be.setWeights(b_dic["vertex_g_index"], g.weight)
    
    be_dic[vert_inde] = be


f.write("boneweights{\n")
f.write(str(len(be_dic))+";\n")
for key,be in be_dic.items():
    be.write_to_file(f,bonne_st, vertex_g_index_to_bone_st_index)

f.write("}\n")


f.close()
print("poly end")

#print(bpy)

#print(bpy.data)

#print(dir(bpy))
#print(dir(bpy.data.meshes[0]))
#print(dir(bpy.data.armatures))
#print(dir(bpy.data.meshes[0].uv_textures["UVMap"]))

#for x in bpy.data.meshes:
#    print(x)
#    print(dir(x))


#print(bpy.data.meshes["body01"])
#body01 = bpy.data.meshes["body01"]

#print(dir(body01.polygons))
#print(body01.polygons)

#for vert_index,vert in body01.polygons.items():
#    print(vert_index)
#    print(vert)
#    print(dir(vert))
#    print(vert.index)
#    print(vert.normal)  
#    print(vert.material_index)
#    print(vert.loop_indices)
#    print(vert.loop_start)
#    print(vert.loop_total)
#    print(vert.vertices)
#    for x in vert.vertices:
#        print(x)
#        print(dir(x))

#print(bpy.data.objects)
#print(bpy.data.meshes[0])
#vert = bpy.data.meshes[0].vertices[0]
#for vert in bpy.data.meshes[0].vertices:
#    print(vert)
#    print(dir(vert))
#    print(vert.co)
#    print(vert.index)
#    print(vert.normal)
#    print(vert.groups[0])

frame_array = []

for key in bpy.data.actions[actionname].fcurves: 
    for marker in key.keyframe_points:
        frame = marker.co.x
        frame_array.append(frame)
    break

scene = bpy.data.scenes[scenename]
bonne_anime_st = {}

for bone_dic in bonne_st:
    bonne_anime_st[bone_dic["bone"].name] = {"bone":bone_dic["bone"].name, "index":bone_dic["index"]}
    bonne_anime_st[bone_dic["bone"].name]["frames"] = {}
for frame in frame_array:
    scene.frame_set(frame)
    bones = bpy.data.objects[armaturename].pose.bones
    for inde, bon in bones.items():
        bonne_anime_st[bon.name]["frames"][frame] = {"matrix":bon.matrix.to_4x4(), "matrix_basis":bon.matrix_basis.to_4x4()}


print("start anime")
f = open(outputanimefilename, "w")
f.write("animsets{\n")
f.write(str(len(bonne_anime_st))+";\n")

for bone_name, bonne_dic in bonne_anime_st.items():
    
    f.write("anim{\n")
    f.write(bone_name+";\n")
    f.write("keys{\n")
    f.write(str(len(bonne_dic["frames"]))+";\n")
    for frame, mat_dic in bonne_dic["frames"].items():
        f.write(str(frame)+";\n")
        f.write("matrix;")
        write_matrix(f, mat_dic["matrix"])
        f.write("matrix_basis;")
        write_matrix(f, mat_dic["matrix_basis"])
    f.write("}\n")    
    f.write("}\n")
    

f.write("}\n")




f.close()

print("anime end")