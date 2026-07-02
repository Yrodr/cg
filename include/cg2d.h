
/* 
   Biblioteca gráfica bidimensional com propósitos didáticos
   Todos os direitos reservados©
   
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos 
*/

#ifndef __CG2D__
#define __CG2D__

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <X11/Xlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <X11/Xutil.h>

#define TTYN "/dev/tty3" // alterar adequadamente conforme versão do SO -> ttyN, N = 1 a 7

// Número máximo de vértices (ou lados) para um polígono (ou face)
#define MAX_VERTICES 500000

// Número máximo de polígonos por objeto (ou face)
#define MAX_POLIGONOS 500000

// Número máximo de pontos para as curvas de Bèzier
#define MAX_POINTS_BEZIER 1000

// Número máximo de cores por canal RGB ou CMY
#define TARGET_COLORS 256

// Define a resolução máxima nas direções x e y
#define MAX_X 1024
#define MAX_Y 1024

// Profundidade do z-buffer -> definido para 
// compatibilidade com as rotinas 3D
#define MAX_DEEP 1e6

#define max(v1,v2) ((v1 >= v2) ? (v1) : (v2))
#define min(v1,v2) ((v1 <= v2) ? (v1) : (v2))

// Exemplo de estruturas de dados para a biblioteca de 
// funções gráficas em C considerando uma porção do 
// plano como referência para o mundo (planolândia)

// Parâmetros necessários para gerenciar uma janela no X-Window
// ou para uso direto no Frame Buffer (/dev/fb0), se permitido
// pelo sistema operacional (provavelmente com permissões 
// de super-usuário)
typedef struct __Window__ {
  // Parâmetros da XLib
  Window root;
  Display * display;
  XImage  * ximage;
  Window  so_window;
  XEvent  an_event, 
          expose_event;
  GC      gc;
  Visual  * visual;
  XGCValues values;
  XSizeHints * size_hints;
  int screen, dplanes, width, height, black, white;
  unsigned char * image32;
  
  // Parâmetros para acesso ao frame buffer (/dev/fb0)
  int fb_fd, tty_fd, fb_width, fb_height, fb_bpp,
      srd_width, srd_height, line_length, start_x, start_y;
  char * fb_data, * ttyn;
  long screensize;
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  
  bool interface;
  } so_win;
 
// Janela de visualização definida no SRU
typedef struct CG_Window {
  float xmin,
        ymin,
        xmax,
        ymax;
        } window;      
 
// Estrutura de dados para um ponto no plano (SRU 2D) com 
// uma componente homogênea (w != 0)
typedef struct Point2D {
  float x, y,
           w,  // componente homogênea 
           b;  // utilizado na estrutura tridimensional
        } point2d;
 
// Estrutura de dados para um objeto (polígono) no plano (SRU 2D)     
typedef struct Polygon {
  bool visible;
  unsigned int numbers_of_points;
  unsigned int max_numbers_of_points;
  int color;
  point2d * points;
  } polygon;
  
typedef struct Object {
  unsigned int numbers_of_polygons;
  unsigned int max_numbers_of_polygons;
  polygon * pol;
  } object2d;

// Estrutura de dados para uma componente de cor no 
// modelo aditivo RGB
typedef struct ColorValues {
  float red,
        green,
        blue,
        alpha;
        } colorvalues;

// Paleta de cores (colormap)   
typedef struct Palette {
  unsigned int numbers_of_colors;
  colorvalues * colors;
  } palette;
 
// Porta de visualização (viewport) definida no SRD     
typedef struct ViewPort {
  unsigned int xmin,
               ymin,
               xmax,
               ymax,
               off_x,
               off_y; 
  char paletteName[100];            
  palette * pal;
  int * buffer;
  float * zbuffer;
  } viewport;

// Estrutura de dados para uma grade bidimensional de 
// entradas que corresponde ao SRD
typedef struct Buffer {
  unsigned int MaxX, // número de colunas
               MaxY; // número de linhas
  int * buffer;
  } bufferdevice;

// Estrutura para uma matriz homogênea para operações
// lineares no plano - SRU
typedef struct Matrix2D {
  float a11, a12, a13,
        a21, a22, a23,
        a31, a32, a33;
        } matrix2d;
        
typedef void __drawline(int, int, int, int, viewport *, int);
typedef void __drawfill(__drawline *, polygon *, window *, viewport *, int);
typedef void __drawdisplay(viewport *, so_win);

// Determina qual será o algoritmo de conversão de segmentos de reta no SRD
void SetLine(__drawline **, __drawline *);

// Determina qual será o algoritmo de preenchimento de polígonos no SRD
// Apenas para preenchimentos baseados em varredura (scanline)
void SetFill(__drawfill **, __drawfill *);

// Determina qual será o algoritmo para a exposição do SRD no monitor real
void SetDisplay(__drawdisplay **, __drawdisplay *);

/* Conversão entre os Sistemas de Referências */
point2d * Sru2Srn(point2d *, window *);
point2d * Srn2Srd(point2d *, viewport *);
void Sru2Srd(float *, float *, window *, viewport *);
void point2srd(float *, window *, viewport *);
 
/* Sistemas de referências, janelas e viewports */
window * CreateWindow(float, float, float, float);
viewport * CreateViewPort(unsigned int, unsigned int, unsigned int, unsigned int, char *);
bufferdevice * CreateBuffer(unsigned int, unsigned int);
bool InWin(point2d *, window *);
bool InPort(point2d *, viewport *);

/* Cria pontos, polígonos e objetos no mundo */
point2d * SetVertex2d(float, float, float, float);
float GetXVertex2d(point2d *);
float GetYVertex2d(point2d *);
void SetXVertex2d(float, point2d *);
void SetYVertex2d(float, point2d *);
void SetPolig2d(point2d *, polygon *);
void SetColorPolig2d(int, polygon *);
object2d * CreateObject2d(unsigned int);
void SetObject2d(polygon *, object2d *);
polygon * CreatePolig2d(unsigned int);
polygon * RegularPolygon2d(unsigned int, float);
polygon * CopyPolygon2d(polygon *);
object2d * CopyObject2d(object2d *);
polygon * GetPolygon2d(object2d *, unsigned int); // retorna um polígono de um objeto composto
object2d * GetObject2d(object2d *, unsigned int); // retorna um objeto de um objeto composto

/* Centro geométrico de objetos e polígonos */
point2d * Centroide2d(object2d *, unsigned int); // calcula o centro geométrico de um objeto
point2d * CentroidePol2d(polygon *); // calcula o centro geométrico de um polígono

/* Curva de Bèzier cúbica */
void ShowControl(__drawline *, __drawfill *, point2d *, point2d *, point2d *, point2d *, window *, viewport *);
void CubicBezier(point2d *, point2d *, point2d *, point2d *, object2d *, int, int);
polygon * BezierCurve(point2d *, point2d *, point2d *, point2d *, int, int);

/* Funções para criar e gerenciar uma paleta de cores */
palette * CreatePalette(unsigned int);
void SetColor(float, float, float, float, palette *);
colorvalues * GetColor(unsigned int, palette *);
palette * ColorMap(char *);
palette * Rainbow(unsigned int);

/* Conversão entre sistemas de cores */
void rgb_hsv(colorvalues *);
void hsv_rgb(colorvalues *);

/* Funções para conversão matricial e rasterização no SRD */
/* Algoritmo DDA (Digital Differential Analyzer) incremental para segmentos de retas */
/* A função draw_line_DDA() não deve ser chamada diretamente */
void draw_line_DDA(int, int, int, int, viewport *, int);
/* Algoritmo DDA (Digital Differential Analyzer) para circunferências */
void draw_circle_DDA(int, int, int, viewport *, int);  // versão geradora de vetores
void draw_circle_DDA8(int, int, int, viewport *, int); // versão coordenadas polares
/* A função line_mid_point() não deve ser chamada diretamente */
void line_mid_point(int, int, int, int, viewport *, int);
void circle_mid_point(float, float, float, window *, viewport *, int);
float elipse_mid_point(float, float, float, float, window *, viewport *, int);

/* Funções para pontos e segmentos de reta que podem ser chamadas diretamente */
void drawPoint(float, float, window *, viewport *);
void drawLine(__drawline *, float, float, float, float, window *, viewport *);

void DrawObject(__drawline *, __drawfill *, object2d *, window *, viewport *, char *, int);

/* Preenchimento de polígonos */
// A função ScanFill() é responsável por chamar as funções de preenchimento 
// baseadas em varredura: ScanLineFill(), ScanLineFill2() e ScanLineFill3(),
// escondendo algumas estruturas de baixo nível
// As variantes ScanLineFill2() e ScanLineFill3() são
// deixadas como exercícios e não estão implementadas
void ScanFill(__drawline *, __drawfill *, polygon *, window *, viewport *, int);
void ScanLineFill(__drawline *, polygon *, window *, viewport *, int);
void BoundaryFill4(int, int, viewport *, int, int);
void FloodFill4(int, int, viewport *, int);

/* Construção das matrizes homogêneas para as operações lineares */
matrix2d * SetRotMatrix2d(float); // cria uma matriz para a operação de rotação
matrix2d * SetSftMatrix2d(float, float); // cria uma matriz para a operação de deslocamento
matrix2d * SetSclMatrix2d(float, float); // cria uma matriz para a operação de escalonamento
matrix2d * SetSpltMatrix2d(float, float); // cria uma matriz para a operação de espelhamento
matrix2d * SetCisMatrix2d(float, float); // cria uma matriz para a operação de cisalhamento
matrix2d * ComposeMatrix2d(matrix2d *, matrix2d *); // composição de matrizes

/* Operações lineares sobre poligonos e pontos (vetores) no SRU 2D */
void LinearTransf2d(matrix2d *, point2d *);
void TransPolig2d(matrix2d *, polygon *);

/* Operações lineares sobre objetos no SRU 2D */
void TransObject2d(matrix2d *, object2d *);

/* Funções para acesso ao buffer do dispositivo de visualização (SRD) */
void SetPixel(int, int, int, viewport *);
int GetPixel(int, int, viewport *);
void SetBPixel(int, int, float, viewport *);
float GetBPixel(int, int, viewport *);
void ChangeColorDevice(int, int, viewport *);
void clearDevice(viewport *);

/* Visualiza o buffer (SRD) no monitor virtual */
so_win InitGraf(bufferdevice *, char *);
void CloseGraf(so_win);
/* Visualiza o buffer do SRD utilizando o X-Window System */
void RefreshX(viewport *, so_win);
/* Visualiza o buffer do SRD diretamente em um terminal tty */
/* Esta função escreve diretamente no framebuffer através da interface /dev/fb0 */
/* Provavelmente, precisa de permissões de super-usuário */
void Display_SRD(viewport *, so_win);
/* Gerencia os ponteiros para as funções de visualização */
void DumpSRD(__drawdisplay *, viewport *, so_win);
/* Exporta uma imagem como PPM (formato de texto) */
void SaveBufferImage(char *, viewport *);

/* Funções auxiliares (recorte de primitivas) */
point2d * InterX(point2d *, point2d *, float);
point2d * InterY(point2d *, point2d *, float);

/* Auxiliares para interpolação */
float area2(point2d *, point2d *, point2d *);
bool BeInPol(point2d *, polygon *);
float InnerProduct2d(point2d *, point2d *);

/* funções auxiliares para detecção de colisão entre polígonos */
point2d * perpendicular(point2d *);
void projectPolygon(polygon *, point2d *, float *, float *);
bool overlap(float, float, float, float);
bool vertex_outside_window(point2d *, window *);
bool polygon_collision_polygon(polygon *, polygon *);
bool polygon_collision_win(polygon *, window *);
bool polygon_collision(polygon *, polygon *, window *);

/* Auxiliares de propósito geral */
void Swap(int *, int *);
void Swapf(float *, float *);
void SwapPoints2d(point2d *, point2d *);
void pausa(int);
void print(char *, char *);
float alef(float, float);

/* funções auxiliares para gerenciamento de liberação de memória */
void free_polygon(polygon *);
void free_palette(palette *);
void free_object2d(object2d *);
void free_viewport(viewport *);
void free_bufferdevice(bufferdevice *);

#endif


