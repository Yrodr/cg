/*
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

// Exemplo do traçado de uma circunferência diretamente no SRD
// Considerando uma simetria de ordem 8, 4 e 2

#include "cg2d.h"
#include "exercicios.h"

// Protótipos das funções para conversão de arcos de circunferência
// A rasterização é realizada diretamente no SRD com simetria de ordem 8, 4 e 2
// Método incremental DDA (Digital Differential Analyser)
int Draw_Circle8_SRD(float, viewport *, int);
int Draw_Circle4_SRD(float, viewport *, int);
int Draw_Circle2_SRD(float, viewport *, int);

int Draw_Circle8_SRD(float raio, viewport * port, int cor) {
  // escreve diretamente no SRD
  // simetria de ordem 8
  int i, x, y, centro;
  float half, x2, y2, raio2;
  
  half = raio/sqrt(2.0);
  centro = (int) (port->xmax)/2;

  raio2 = raio*raio; 
  for(i=0;i<=(int)round(half);i++) {
    x = i + centro;
    x2 = (x - centro)*(x - centro);
    y2 = raio2 - x2;
    y = (int) round(sqrt(y2)) + centro;
    SetPixel(x,y,cor,port); 
    SetPixel(y,x,cor,port);
    SetPixel(y,port->xmax-x,cor,port);
    SetPixel(x,port->ymax-y,cor,port);
    SetPixel(port->xmax-x,port->ymax-y,cor,port);
    SetPixel(port->ymax-y,port->xmax-x,cor,port);
    SetPixel(port->ymax-y,x,cor,port);
    SetPixel(port->xmax-x,y,cor,port);                           
    }
    
  return 0;
  }

int Draw_Circle4_SRD(float raio, viewport * port, int cor) {
  // escreve diretamente no SRD
  // simetria de ordem 4
  int i, x, y, centro;
  float x2, y2, raio2;
 
  centro = (int) (port->xmax)/2;

  raio2 = raio*raio; 
  for(i=0;i<=(int)raio;i++) {
    x = i + centro;
    x2 = (x - centro)*(x - centro);
    y2 = raio2 - x2;
    y = (int) round(sqrt(y2)) + centro;
    SetPixel(x,y,cor,port);
    SetPixel(x,port->ymax-y,cor,port);    
    SetPixel(port->xmax-x,y,cor,port);
    SetPixel(port->xmax-x,port->ymax-y,cor,port);
    }
    
  return 0;
  }
 
int Draw_Circle2_SRD(float raio, viewport * port, int cor) {
  // escreve diretamente no SRD
  // simetria de ordem 2
  int i, x, y, centro;
  float x2, y2, raio2;
 
  centro = (int) (port->xmax)/2;

  raio2 = raio*raio; 
  for(i=(int)-raio;i<=(int)raio;i++) {
    x = i + centro;
    x2 = (x - centro)*(x - centro);
    y2 = raio2 - x2;
    y = (int) round(sqrt(y2)) + centro;
    SetPixel(x,y,cor,port);
    SetPixel(x,port->ymax-y,cor,port);
    }
    
  return 0;  
  }

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  viewport * porta;
  so_win par;
  float raio;
  int cor;
  
  __drawline * line;
  SetLine(&line,Draw_line_DDA);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");  

  monitor = CreateBuffer(600,600); // Cria um buffer (SRD) para monitor virtual
  par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual

  // Cria uma viewport
  // No caso uma única saída para o dispositivo de visualização com 600x600 entradas
  porta = CreateViewPort(1, 1, 600, 600, "default");
  // "default" define 8 cores (preto, vermelho, verde, azul, ciano, magenta, amarelo e branco)
  // "gray" define 256 tons de cinza
  // "red" define 256 tons de vermelho (primeira cor primária no modelo RGB)
  // "green" define 256 tons de verde (segunda cor primária no modelo RGB)  
  // "blue" define 256 tons de azul (terceira cor primária no modelo RGB)
  // "cyan" define 256 tons de ciano (primeira cor no modelo CMY)
  // "magenta" define 256 tons de magenta (segunda cor no modelo CMY)
  // "yellow" define 256 tons de amarelo (terceira cor no modelo CMY)
  // "p&b" define apenas duas cores: preto e branco

  // Desenha no SRD
  raio = 150;
  cor = 1;
  // Draw_Circle8_SRD(): função definida e implementada no arquivo exercicios.c
  Draw_Circle8_SRD(raio,porta,cor);
  
  // EXERCÍCIOS: REFAÇA O EXERCÍCIO CONSIDERANDO AS SIMETRIAS DE ORDEM 4 E 2
  Draw_Circle4_SRD(raio+15,porta,cor+1);
  Draw_Circle2_SRD(raio+30,porta,cor+2);    
  
  // Mapeia o SRD no monitor virtual exibindo o objeto na tela 
  DumpSRD(display,porta,par);
  pausa(5);
  
  // libera os ponteiros
  free(porta);  
  free_bufferdevice(monitor);
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");
 
  return 0;
  }
  

