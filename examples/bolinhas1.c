/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

#include "cg2d.h"

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  window * janela;
  viewport * porta1, * porta2, * porta3, * porta4;
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
  float d_x_1 = 0.1, d_y_1 = 0.1, d_x_2 = 0.1, d_y_2 = 0.1;  
  
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
  // veja os códigos da pasta exercicio para explicação sobre os dois últimos parâmetros
  porta1 = CreateViewPort(1, 1, 300, 300, "default");
  porta2 = CreateViewPort(301, 1, 600, 300, "default");
  porta3 = CreateViewPort(1, 301, 300, 600, "default");
  porta4 = CreateViewPort(301, 301, 600, 600, "default");
  
  obj1 = CopyObject2d(obj);
  SetColorPolig2d(1,obj1->pol);
  m = SetSftMatrix2d(-8.0,0.0);
  TransObject2d(m,obj1);
  free(m);
  
  obj2 = CopyObject2d(obj);
  SetColorPolig2d(2,obj2->pol);
  m = SetSftMatrix2d(0.0,8.0);   
  TransObject2d(m,obj2);
  free(m);
  
  obj3 = CopyObject2d(obj);
  SetColorPolig2d(3,obj3->pol);
  m = SetSftMatrix2d(8.0,0.0);  
  TransObject2d(m,obj3);
  free(m);
  
  obj4 = CopyObject2d(obj);
  SetColorPolig2d(4,obj4->pol);
  m = SetSftMatrix2d(0.0,-8.0);
  TransObject2d(m,obj4);
  free(m);
  
  free_object2d(obj);

  int count = 0;
  while (count++ < 500) {
    // para objeto 1
    p = Centroide2d(obj1,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);
    if ((cx < -8.01) || (cx > 8.01)) d_x_1 = - d_x_1;
    m = SetSftMatrix2d(d_x_1,0.0);
    TransObject2d(m,obj1);
    free(m);        
    clearDevice(porta1); // Limpa o SRD na view-port especificada
    DrawObject(line,fill,obj1,janela,porta1,"close",1); // Desenha o objeto no SRD
   
    // para objeto 2
    p = Centroide2d(obj2,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);    
    if ((cy < -8.01) || (cy > 8.01)) d_y_1 = - d_y_1;
    m = SetSftMatrix2d(0.0,d_y_1);
    TransObject2d(m,obj2);
    free(m);
    clearDevice(porta2); // Limpa o SRD na view-port especificada  
    DrawObject(line,fill,obj2,janela,porta2,"close",2); // Desenha o objeto no SRD
   
    // para objeto 3
    p = Centroide2d(obj3,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);     
    if ((cx < -8.01) || (cx > 8.01)) d_x_2 = - d_x_2;
    m = SetSftMatrix2d(d_x_2,0.0);
    TransObject2d(m,obj3);
    free(m); 
    clearDevice(porta3); // Limpa o SRD na view-port especificada
    DrawObject(line,fill,obj3,janela,porta3,"close",3); // Desenha o objeto no SRD
 
    // para objeto 4
    p = Centroide2d(obj4,0);
    cx = GetXVertex2d(p);
    cy = GetYVertex2d(p);
    free(p);     
    if ((cy < -8.01) || (cy > 8.01)) d_y_2 = - d_y_2;
    m = SetSftMatrix2d(0.0,d_y_2);
    TransObject2d(m,obj4);
    free(m);
    clearDevice(porta4); // Limpa o SRD na view-port especificada
    DrawObject(line,fill,obj4,janela,porta4,"close",4); // Desenha o objeto no SRD
    
    DumpSRD(display,porta1,par);
    DumpSRD(display,porta2,par);
    DumpSRD(display,porta3,par);
    DumpSRD(display,porta4,par);  
    }
  
  free(janela);
  free_viewport(porta1);
  free_viewport(porta2);
  free_viewport(porta3); 
  free_viewport(porta4);   
  free_object2d(obj1);
  free_object2d(obj2);
  free_object2d(obj3);
  free_object2d(obj4);
  free_bufferdevice(monitor);  
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");    

  return 0;
  }


