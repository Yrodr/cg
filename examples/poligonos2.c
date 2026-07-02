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
  polygon * poligono1, * poligono2;
  object2d * objeto;
  so_win par;
  
  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");

  monitor = CreateBuffer(640,480); // Cria um monitor virtual
  par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual
    
  // cria dois objetos bidimensionais
  poligono1 = CreatePolig2d(5);  // polígono fechado com 5 vértices
  poligono2 = CreatePolig2d(4);  // polígono fechado com 4 vértices
  
  // Insere as coordenadas (x,y) dos pontos representados no SRU em cada objeto
  // O terceiro parâmetro será discutido em aula futura (componente homogênea)
  // O quarto parâmetro é para compatibilidade com a extensão 3D
  SetPolig2d(SetVertex2d(-9.0,-8.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(-7.0,-3.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(-4.0,-4.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(-3.0,-6.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(-6.0,-9.0,1.0,0.0),poligono1);
  SetColorPolig2d(1,poligono1);
  
  SetPolig2d(SetVertex2d(-6.0,-2.0,1.0,0.0),poligono2);
  SetPolig2d(SetVertex2d(-1.0,-2.0,1.0,0.0),poligono2);
  SetPolig2d(SetVertex2d(-1.0,-6.0,1.0,0.0),poligono2);
  SetPolig2d(SetVertex2d(-6.0,-6.0,1.0,0.0),poligono2);
  SetColorPolig2d(3,poligono2);
 
  objeto = CreateObject2d(2);  // objeto composto por 2 polígonos
  SetObject2d(poligono1,objeto);
  SetObject2d(poligono2,objeto);
 
  // cria uma janela de visualização (coordenadas no SRU)
  janela = CreateWindow(-10.0,-10.0,0.0,0.0);

  // Cria uma viewport
  // no caso uma única saída para o dispositivo de visualização com 640x480 entradas
  porta = CreateViewPort(1, 1, 640, 480, "default");

  // Desenha no SRD
  DrawObject(line,fill,objeto,janela,porta,"close",-1);  // desenha o objeto com 2 polígonos
  // Mapeia o SRD no monitor virtual exibindo o objeto na tela 
  DumpSRD(display,porta,par);
  pausa(2);

  ScanFill(line,fill,GetPolygon2d(objeto,0),janela,porta,1); // preenche o 1º poligono
  DumpSRD(display,porta,par);
  pausa(2);

  ScanFill(line,fill,GetPolygon2d(objeto,1),janela,porta,3); // preenche o 2º poligono
  DumpSRD(display,porta,par);
  pausa(2);
 
  // libera os ponteiros
  free(janela);
  free_viewport(porta);  
  free_object2d(objeto);
  free_bufferdevice(monitor);
    
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");
 
  return 0;
  }

