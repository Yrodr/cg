/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

#include "cg2d.h"

// espiral de arquimedes: rho = a + b*theta
polygon * espiralArq(float, float, unsigned int);

polygon * espiralArq(float a, float b, unsigned int n) {
  float step, rho, theta, x, y;
  polygon * curva;
    
  curva = CreatePolig2d(n*360 + 1);

  step = (2.0*M_PI)/(360.0);
  for(theta=0.0;theta<(n*2.0*M_PI);theta=theta+step) {
    rho = a + b*theta;
    x = rho*cos(theta);
    y = rho*sin(theta);
    SetPolig2d(SetVertex2d(x,y,1.0,0.0),curva);
    }
    
  return curva;
  }

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  viewport * porta1, * porta2, * porta3, * porta4;
  window * janela;
  so_win par;
  polygon * curva;
  object2d * objeto;
  
  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");

  monitor = CreateBuffer(600,600); // Cria um buffer (SRD) para monitor virtual
  par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual
  
  // cria uma janela de visualização (coordenadas no SRU)
  janela = CreateWindow(-8.0,-8.0,8.0,8.0);

  // cria 4 view-ports (coordenadas no SRD)
  porta1 = CreateViewPort(1, 1, 300, 300, "default");
  porta2 = CreateViewPort(301, 1, 600, 300, "default");
  porta3 = CreateViewPort(1, 301, 300, 600, "default");
  porta4 = CreateViewPort(301, 301, 600, 600, "default");

  // objeto em coordenadas polares (rho,theta) -> Espiral de Arquimedes
  // rho = a + b*theta
  objeto = CreateObject2d(4);

  curva = espiralArq(0.0,1.0/M_PI,1);
  SetColorPolig2d(1,curva);
  SetObject2d(curva,objeto);
  
  curva = espiralArq(0.0,1.0/M_PI,2);
  SetColorPolig2d(2,curva);
  SetObject2d(curva,objeto);
  
  curva = espiralArq(0.0,1.0/M_PI,3);
  SetColorPolig2d(3,curva);
  SetObject2d(curva,objeto);
  
  curva = espiralArq(0.0,1.0/M_PI,4);
  SetColorPolig2d(4,curva);
  SetObject2d(curva,objeto);

  DrawObject(line,fill,GetObject2d(objeto,0),janela,porta1,"open",-1);
  DrawObject(line,fill,GetObject2d(objeto,1),janela,porta2,"open",-1);
  DrawObject(line,fill,GetObject2d(objeto,2),janela,porta3,"open",-1);
  DrawObject(line,fill,GetObject2d(objeto,3),janela,porta4,"open",-1);
        
  DumpSRD(display,porta1,par);
  pausa(2);
  DumpSRD(display,porta2,par);
  pausa(2);
  DumpSRD(display,porta3,par);
  pausa(2);
  DumpSRD(display,porta4,par);      
  pausa(2);

  // libera os ponteiros
  free(janela);
  free_viewport(porta1);
  free_viewport(porta2);
  free_viewport(porta3);
  free_viewport(porta4);
  free_object2d(objeto);  
  free_bufferdevice(monitor);
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");
 
  return 0;
  }


