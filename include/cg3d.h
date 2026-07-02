
/* 
   Biblioteca gráfica tridimensional com propósitos didáticos
   Todos os direitos reservados©
   
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos 
*/

#ifndef __CG3D__ 
#define __CG3D__ 

#include <cg2d.h>

#define MAX_LIGHTS 8

#define VISIBLE_THRESHOLD 200

typedef struct Point3D {
  float x, y, z;
  float w;   
  float nx, ny, nz;
  float b;
  } point3d;
 
typedef point3d vector3d; 
     
typedef struct Face {
  bool visible;
  unsigned int numbers_of_points;
  unsigned int max_numbers_of_points;
  int color;
  float nx, ny, nz;
  int n;
  float ra, rd, rs;
  int face_no;
  point3d * points;
  } face;

typedef struct Object3D {
  unsigned int numbers_of_faces;   
  unsigned int max_numbers_of_faces;  
  face * faces;
  } object3d;

typedef struct Matrix3D {
  float a11, a12, a13, a14,
        a21, a22, a23, a24,
        a31, a32, a33, a34,
        a41, a42, a43, a44;
        } matrix3d;
 
typedef struct {
  bool on;
  int color;
  float ia, id;
  point3d * lightPosition;
  point3d * lightTarget;
  viewport * light_port;   
  matrix3d * lightMatrix;
  } punctual_light; 

typedef struct {
  unsigned int numbers_of_lights;
  unsigned int max_numbers_of_lights;
  punctual_light * light;
  } lights;

// manipulação de pontos e vetores
float Modulo3d(vector3d *);
float InnerProduct3d(vector3d *, vector3d *);
vector3d * Versor3d(vector3d *);
vector3d * VectorProduct3d(vector3d *, vector3d *);
point3d * SetVertex3d(float, float, float, float, float);
point3d * SetVetor3d(float, float, float);

// faces
face * CreateFace(unsigned int);
bool beInFace(point3d *, face *);
bool FaceView(face *, vector3d *);
void isFaceVisible(face *, bool);
void normalVisibleFaces(object3d *, vector3d *);
int GetColorFace(face *);
point3d * GetNormalFace(face *);
void SetNormalFace(face *);
void SetNormalFaceObj(object3d *);
int NFaces(object3d * );
face * copyFace3d(face *);
face * getFace3d(object3d *, unsigned int);
void SetPointFace(point3d *, face *);
void SetColorFace(face *, int);

// objetos
object3d * CreateObject3d(unsigned int);
void SetObject3d(face *, object3d *);
object2d * Obj3dtoObj2d(object3d *);
object3d * Obj2dtoObj3d(object2d *);
object3d * copyObject3d(object3d *);
object3d * GetData(const char *, const char *);
void SetColorObject3d(object3d *, viewport *, int);
void objectVisible(object3d *);
void objectInVisible(object3d *);

// matrizes, projeções, mudanças de base e referênciais
point3d * centre_object(object3d *);
matrix3d * invMatrix(matrix3d *); // apenas para viewMatrix
matrix3d * SetRotMatrix3dX(float);
matrix3d * SetRotMatrix3dY(float);
matrix3d * SetRotMatrix3dZ(float);
matrix3d * SetSclMatrix3d(float, float, float);
matrix3d * SetSftMatrix3d(float, float, float);
matrix3d * ComposeMatrix3D(matrix3d * m1, matrix3d * m2);
matrix3d * Persp_Proj_Matr(float, float);
void LinearTransf3d(matrix3d *, vector3d *);
void TransObject3d(matrix3d *, object3d *);
object2d * ParalProj(object3d *, float);
object2d * PerspProj(object3d *, float, float);
void setReferencial(matrix3d *, vector3d *);
object3d * ConvertObjectBase(matrix3d *, object3d *);
vector3d * lookAt(vector3d *, vector3d *);
matrix3d * CreateObserver(vector3d *, vector3d *, vector3d *);
void switchOrientation(matrix3d *);

// luzes
lights * CreatePontualLights(int);
void SetLigthParameters(lights *, vector3d *, vector3d *, float, float, int, viewport *);
void LigthOn(lights *, int, bool);
void SetFaceLigthReflection(face *, float, float, int);
void SetObjectLigthReflection(object3d *, float, float, int);
void clearLightBuffer(lights *, int);
void lightVisibleFaces(object3d * ob, lights *);
matrix3d * createLightBase(vector3d *, vector3d *);

// preenchimento buffer SRD
void drawObject3d(__drawline *, __drawfill *, object3d *, window *, viewport *, int);

// z-buffer
float area3(point3d *, point3d *, point3d *);
void planeZ(point3d *, point3d *, point3d *, float *, float *, float *);
bool insideTriangle(point3d *, point3d *, point3d *, point3d *);
void rasterTriangle(face *, point3d *, point3d *, point3d *, viewport *);
void fillBuffer(face *, viewport *);
int * bufferVisibleFaces(object3d *, window *, viewport *, int *);
object3d * PerspProjBuffer(object3d *, float, float);
int visibleFaces(object3d *, viewport *, int *);

// Superfícies de revolução (superfície rotacional ou de simetria radial)
// (em torno do eixo y)
object3d * torus(int, float, int, float);               // toro de revolução
object3d * sphere(int, float, int);                     // esfera de revolução
object3d * cone(float, float, int, int);                // cone (duplo) de revolução
object3d * elipsoide_oblato(int, float, int, float);    // elipsóide oblato (em z)
object3d * elipsoide_prolato(int, float, int, float);   // elipsóide prolato (em x)

// libera ponteiros
void free_face(face *);
void free_lights(lights *);
void free_object3d(object3d *);

#endif


