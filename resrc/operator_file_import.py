import bpy
from bpy_extras.object_utils import AddObjectHelper, object_data_add
from mathutils import Vector
import bmesh

def read_some_data(context, filepath, self):
    print("running read_some_data...")
    f = open(filepath, 'r', encoding='utf-8')
    data = f.read()
    f.close()

    # would normally load the data here
    print(data)
    splited = data.split()
    sin_splited = []
    for splited_item in splited:
        if ('(' in splited_item):
            splited_item = splited_item.split('(')
            for sitem in splited_item:
                if (')' in sitem):
                    sitem = sitem.split(')')
                    for ssitem in sitem:
                        sin_splited.append(ssitem)
                else:
                    sin_splited.append(sitem)
        else:
            if (')' in splited_item):
                splited_item = splited_item.split(')')
                for sitem in splited_item:
                    sin_splited.append(sitem)
            else:
                sin_splited.append(splited_item)
    namedayos = []
    verts = {}
    edges= {}
    faces= {}
    sitem_size = len(sin_splited)
    for k in range(sitem_size):
        sitem = sin_splited[k]
        print(sitem)
        if ('Object' in sitem):
            print('keyis dayo='+str(k))
            print('name is ='+sin_splited[k+1])
            namedayo = sin_splited[k+1]
            namedayos.append(sin_splited[k+1])
            verts[sin_splited[k+1]] = []
            faces[sin_splited[k+1]] = []
            edges[sin_splited[k+1]] = []
            kakko = 1
            kirokul = 0
            for l in range(k+3,sitem_size):
                ssitem = sin_splited[l]
                if ('{' == ssitem):
                    kakko = kakko + 1
                if ('}' == ssitem):
                    kakko = kakko - 1
                    if (kakko == 0):
                       kirokul = l
                       break
            for l in range(k+3,kirokul):
                sitem = sin_splited[l] 
        
                if ('vertex' in sitem):
                    print('vertexcount='+str(sin_splited[l+1]))
                    vertexcount = sin_splited[l+1]
                    for i in range(int(vertexcount)):
                        x = sin_splited[l+3+3*i]
                        y = sin_splited[l+3+3*i+1]
                        z = sin_splited[l+3+3*i+2]
                        print(str(x)+','+str(-float(z))+','+str(float(y)))
                        vert = [float(x),-float(z),float(y)]
                        verts[namedayo].append(vert)
                    
                if ('face' == sitem):
                    print('face='+str(sin_splited[l+1]))
                    facecount = int(sin_splited[l+1])
                    face_c = 0
                    for i in range(l+1,kirokul):
                
                        if ('V' == sin_splited[i]):
                            if (int(sin_splited[i-1]) == 3):
                                 k1 = sin_splited[i+1]
                                 k2 = sin_splited[i+2]
                                 k3 = sin_splited[i+3]
                                 face = [int(k1),int(k2),int(k3)]
                                 faces[namedayo].append(face)
                                 face_c = face_c +1             
                                 print(str(k1)+','+str(k2)+','+str(k3))     
                            elif (int(sin_splited[i-1]) == 4):
                                 k1 = sin_splited[i+1]
                                 k2 = sin_splited[i+2]
                                 k3 = sin_splited[i+3]
                                 k4 = sin_splited[i+4]
                                 face = [int(k1),int(k2),int(k3)]
                                 faces[namedayo].append(face)
                                 face = [int(k1),int(k3), int(k4)]
                                 faces[namedayo].append(face)
                                 face_c = face_c +1             
                                 print(str(k1)+','+str(k2)+','+str(k3))
                                 print(str(k1)+','+str(k3)+','+str(k4))
                            else:
                                print('dame3')
                                return {'CANCELLED'}
            
                    if (face_c != facecount):
                        print('dame face'+str(face_c)+','+str(facecount))
                        return {'CANCELLED'}
    
    
    print(verts)
    print(faces)

    for namedayo in namedayos:
    
        mesh = bpy.data.meshes.new(namedayo)

        bm = bmesh.new()
        verts_loc = verts[namedayo]
        for v_co in verts_loc:
            bm.verts.new(v_co)

        bm.verts.ensure_lookup_table()
        for f_idx in faces[namedayo]:
            bm.faces.new([bm.verts[i] for i in f_idx])

        bm.to_mesh(mesh)
        mesh.update()

    # add the mesh as an object into the scene with this utility module
        from bpy_extras import object_utils
        object_utils.object_data_add(context, mesh, operator=self)
    
    
    
    #print('dame')
    #return {'CANCELLED'}
    return {'FINISHED'}


# ImportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ImportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator


class ImportSomeData(Operator, ImportHelper,AddObjectHelper):
    """This appears in the tooltip of the operator and in the generated docs"""
    bl_idname = "import_test.some_data"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Import Some Data"

    # ImportHelper mixin class uses this
    filename_ext = ".mqo"

    filter_glob = StringProperty(
            default="*.mqo",
            options={'HIDDEN'},
            maxlen=255,  # Max internal buffer length, longer would be clamped.
            )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    use_setting = BoolProperty(
            name="Example Boolean",
            description="Example Tooltip",
            default=True,
            )

    type = EnumProperty(
            name="Example Enum",
            description="Choose between two items",
            items=(('OPT_A', "First Option", "Description one"),
                   ('OPT_B', "Second Option", "Description two")),
            default='OPT_A',
            )

    def execute(self, context):
        return read_some_data(context, self.filepath, self)


# Only needed if you want to add into a dynamic menu
def menu_func_import(self, context):
    self.layout.operator(ImportSomeData.bl_idname, text="Text Import Operator")


def register():
    bpy.utils.register_class(ImportSomeData)
    bpy.types.INFO_MT_file_import.append(menu_func_import)


def unregister():
    bpy.utils.unregister_class(ImportSomeData)
    bpy.types.INFO_MT_file_import.remove(menu_func_import)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.import_test.some_data('INVOKE_DEFAULT')
