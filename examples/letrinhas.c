/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

#include "cg2d.h"
#include "exercicios.h"

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  window * janela1, * janela2;
  viewport * porta1, * porta2, * porta3, * porta4;
  polygon * poligono1, * poligono2;
  object2d * objeto1, * objeto2;
  matrix2d * m;
  so_win par;
  
  __drawline * line;
  // mudança no algoritmo default de conversão matricial
  // de segmentos de retas 
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");
  
  monitor = CreateBuffer(600,600); // Cria um monitor virtual com 600x600 entradas
  par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual
  
  poligono1 = CreatePolig2d(8);  // polígono fechado com 8 vértices
  poligono2 = CreatePolig2d(4);  // polígono fechado com 4 vértices

  SetPolig2d(SetVertex2d(-2.0,6.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(2.0,6.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(8.0,-8.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(4.0,-8.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(2.0,-4.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(-2.0,-4.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(-4.0,-8.0,1.0,0.0),poligono1);
  SetPolig2d(SetVertex2d(-8.0,-8.0,1.0,0.0),poligono1);
  SetColorPolig2d(1,poligono1); 

  SetPolig2d(SetVertex2d(1.7,-2.0,1.0,0.0),poligono2);
  SetPolig2d(SetVertex2d(-1.7,-2.0,1.0,0.0),poligono2);
  SetPolig2d(SetVertex2d(-0.3,2.0,1.0,0.0),poligono2);
  SetPolig2d(SetVertex2d(0.3,2.0,1.0,0.0),poligono2);    
  SetColorPolig2d(1,poligono2);
  
  objeto1 = CreateObject2d(1); 
  SetObject2d(poligono1,objeto1);
  objeto2 = CreateObject2d(1);   
  SetObject2d(poligono2,objeto2);    
  
  janela1 = CreateWindow(-10.0,-10.0,10.0,10.0);
  
  porta1 = CreateViewPort(1, 1, 300, 300, "default");
  porta2 = CreateViewPort(301, 1, 600, 300, "default");
  porta3 = CreateViewPort(1, 301, 300, 600, "default");
  porta4 = CreateViewPort(301, 301, 600, 600, "default");
  
  DrawObject(line,fill,objeto1,janela1,porta1,"close",1);
  DrawObject(line,fill,objeto2,janela1,porta1,"close",0); 
  DumpSRD(display,porta1,par);
  DumpSRD(display,porta2,par);
  DumpSRD(display,porta3,par);
  DumpSRD(display,porta4,par);     
  pausa(2);
 
  m = SetRotMatrix2d(-225);
  TransObject2d(m,objeto1);
  TransObject2d(m,objeto2);
  free(m);
  DrawObject(line,fill,objeto1,janela1,porta2,"close",1);
  DrawObject(line,fill,objeto2,janela1,porta2,"close",0); 
  DumpSRD(display,porta1,par);
  DumpSRD(display,porta2,par);
  DumpSRD(display,porta3,par);
  DumpSRD(display,porta4,par);
  pausa(2);

  m = SetRotMatrix2d(225);
  TransObject2d(m,objeto1);
  TransObject2d(m,objeto2);
  free(m); 
  m = SetCisMatrix2d(0.25,0.0);
  TransObject2d(m,objeto1);
  TransObject2d(m,objeto2);  
  free(m);
  DrawObject(line,fill,objeto1,janela1,porta3,"close",1);
  DrawObject(line,fill,objeto2,janela1,porta3,"close",0); 
  DumpSRD(display,porta1,par);
  DumpSRD(display,porta2,par);
  DumpSRD(display,porta3,par);
  DumpSRD(display,porta4,par);
  pausa(2);

  m = SetCisMatrix2d(-0.25,0.0);
  TransObject2d(m,objeto1);
  TransObject2d(m,objeto2);
  free(m);
  m = SetSclMatrix2d(1.5,0.5);
  TransObject2d(m,objeto1);
  TransObject2d(m,objeto2);
  free(m);
  // A resposta era simplesmente mudar a proporção da janela de visualização
  janela2 = CreateWindow(-15.0,-5.0,15.0,5.0);
  DrawObject(line,fill,objeto1,janela1,porta4,"close",1);
  DrawObject(line,fill,objeto2,janela1,porta4,"close",0);  
  DumpSRD(display,porta1,par);
  DumpSRD(display,porta2,par);
  DumpSRD(display,porta3,par);
  DumpSRD(display,porta4,par);
  pausa(4);   
 
  free(janela1);
  free_viewport(porta1);
  free_viewport(porta2);
  free_viewport(porta3); 
  free_viewport(porta4);   
  free_object2d(objeto1);
  free_object2d(objeto2);
  free_bufferdevice(monitor);  
  
  CloseGraf(par); 
  
  print("Terminado com êxito!","blue");     

  return 0;
  }


