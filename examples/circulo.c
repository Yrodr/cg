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
  float x0, y0, raio;

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

  // Coordenadas do centro da circunferência (SRU) 
  x0 = 3.0;
  y0 = 3.0;
  // raio da circunferência no SRU  
  raio = 2.5;
  
  circle_mid_point(x0,y0,raio,janela,porta,1);
  
  // Coordenadas do centro da circunferência (SRU) 
  x0 = -3.0;
  y0 = -3.0;
  // raio da circunferência no SRU  
  raio = 2.0;
  
  circle_mid_point(x0,y0,raio,janela,porta,6);  
  
  // Mapeia o SRD no monitor virtual exibindo o objeto na tela 
  DumpSRD(display,porta,par);
  pausa(5);
  
  free(janela);
  free_viewport(porta);
  free_bufferdevice(monitor);  
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");    

  return 0;
  }


