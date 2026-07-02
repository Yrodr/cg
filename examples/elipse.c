/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

#include "cg2d.h"

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  window * janela;
  viewport * porta;
  float x0, y0, a, b, e;

  so_win par;
  
  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");
  
  monitor = CreateBuffer(600,600);  // Cria um monitor virtual com 600x600 entradas
  par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual
  
  // cria uma janela de visualização (coordenadas no SRU)
  janela = CreateWindow(-10.0,-10.0,10.0,10.0);
  
  // cria uma única view port
  porta = CreateViewPort(1, 1, 600, 600, "default");

  // Coordenadas do centro da elipse (SRU)
  x0 = 3.2; y0 = 2.8;
  a = 5.0; b = 2.0;
  e = elipse_mid_point(x0,y0,a,b,janela,porta,2);
  printf("Exentricidade: %f\n",e);
  DumpSRD(display,porta,par);  
  pausa(2);
  Sru2Srd(&x0,&y0,janela,porta);
  FloodFill4((int)x0,(int)y0,porta,3); 
  DumpSRD(display,porta,par);
  pausa(2);  
    
  // Coordenadas do centro da elipse (SRU)
  x0 = -3.8; y0 = -2.4;
  a = 2.5; b = 4.7;
  e = elipse_mid_point(x0,y0,a,b,janela,porta,5);
  printf("Exentricidade: %f\n",e);
  DumpSRD(display,porta,par);  
  pausa(2);
  Sru2Srd(&x0,&y0,janela,porta);
  BoundaryFill4((int)x0,(int)y0,porta,6,5);
  DumpSRD(display,porta,par);  
  pausa(3);
  
  free(janela);
  free_viewport(porta);
  free_bufferdevice(monitor);  
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");    

  return 0;
  }


