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
  polygon * poligono;
  object2d * obj, * obj1, * obj2, * obj3, * obj4;
  point2d * p;
  matrix2d * m;
  so_win par;
  
  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");
  
  float cx, cy; // centro do objeto no SRU
  
  monitor = CreateBuffer(600,600); // Cria um monitor virtual com 600x600 entradas
  par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual
  
  // cria um polígono regular centrado na origem
  // a cor do polígono é associada ao indice 0 da palheta   
  poligono = RegularPolygon2d(20,1.0); 
  obj = CreateObject2d(1);
  SetObject2d(poligono,obj); // o polígono é descartado
  			     // qualquer referência a ele passa a ser através do objeto
  // cria uma janela de visualização (coordenadas no SRU)
  janela = CreateWindow(-10.0,-10.0,10.0,10.0); 

  // cria 4 view-ports (coordenadas no SRD)
  porta = CreateViewPort(1, 1, 600, 600, "default");
  
  obj1 = CopyObject2d(obj);
  SetColorPolig2d(1,obj1->pol);
  m = SetSftMatrix2d(8.0,0.0);
  TransObject2d(m,obj1);
  free(m);
  
  obj2 = CopyObject2d(obj);
  SetColorPolig2d(2,obj2->pol);
  m = SetSftMatrix2d(0.0,8.0);   
  TransObject2d(m,obj2);
  free(m);
  
  obj3 = CopyObject2d(obj);
  SetColorPolig2d(3,obj3->pol);
  m = SetSftMatrix2d(7.761140,3.88057);  
  TransObject2d(m,obj3);
  free(m);
  
  obj4 = CopyObject2d(obj);
  SetColorPolig2d(4,obj4->pol);
  m = SetSftMatrix2d(4.146413,6.219620);
  TransObject2d(m,obj4);
  free(m);
  
  free_object2d(obj);
  
  float d1 = 0.1, d2 = 0.1, d3 = 0.1, d4 = 0.1;
  
  int count = 0;
  while (count++ < 500) {
    clearDevice(porta); // Limpa o SRD na view-port especificada
    
    // para objeto 1
    p = Centroide2d(obj1,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);
    if ((cx < -8.1) || (cx > 8.1)) d1 = - d1;
    m = SetSftMatrix2d(d1,0.0);
    TransObject2d(m,obj1);
    free(m);
    DrawObject(line,fill,obj1,janela,porta,"close",1); // Desenha o objeto no SRD
 
    // para objeto 2
    p = Centroide2d(obj2,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);    
    if ((cy < -8.1) || (cy > 8.1)) d2 = - d2;
    m = SetSftMatrix2d(0.0,d2);
    TransObject2d(m,obj2);
    free(m); 
    DrawObject(line,fill,obj2,janela,porta,"close",2); // Desenha o objeto no SRD

    // para objeto 3
    p = Centroide2d(obj3,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);     
    if ((cx < -7.77) || (cx > 7.77)) d3 = - d3;
    m = SetSftMatrix2d(d3,d3*0.5);
    TransObject2d(m,obj3);
    free(m);
    DrawObject(line,fill,obj3,janela,porta,"close",3); // Desenha o objeto no SRD
   
    // para objeto 4
    p = Centroide2d(obj4,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);     
    if ((cy < -6.22) || (cy > 6.22)) d4 = - d4;  
    m = SetSftMatrix2d((d4/1.5),d4);
    TransObject2d(m,obj4);
    free(m);
    DrawObject(line,fill,obj4,janela,porta,"close",4); // Desenha o objeto no SRD
    
    DumpSRD(display,porta,par);
    }

  free(janela);
  free_viewport(porta);
  free_object2d(obj1);
  free_object2d(obj2);
  free_object2d(obj3);
  free_object2d(obj4);
  free_bufferdevice(monitor);
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");    

  return 0;
  }


