#include "cg2d.h"

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  viewport * porta1, * porta2, * porta3, * porta4;
  so_win par;
  int i, j, min;
 
  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");

  monitor = CreateBuffer(600,600);
  par = InitGraf(monitor,argv[0]);
    
  porta1 = CreateViewPort(1, 1, 300, 300, "rainbow1");
  porta2 = CreateViewPort(301, 1, 600, 300, "rainbow2");
  porta3 = CreateViewPort(1, 301, 300, 600, "rainbow3");
  porta4 = CreateViewPort(301, 301, 600, 600, "rainbow4");
 
  min = 22;
  
  for(i=min;i<porta1->ymax-porta1->ymin+1-min;i++) {
    for(j=min;j<porta1->xmax-porta1->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta1);
      }
    }
    
  for(i=min;i<porta1->ymax-porta1->ymin+1-min;i++) {
    for(j=min;j<porta1->xmax-porta1->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta2);
      }
    }
    
  for(i=min;i<porta1->ymax-porta1->ymin+1-min;i++) {
    for(j=min;j<porta1->xmax-porta1->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta3);
      }
    }
    
  for(i=min;i<porta1->ymax-porta1->ymin+1-min;i++) {
    for(j=min;j<porta1->xmax-porta1->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta4);
      }
    }        

  DumpSRD(display,porta1,par);
  DumpSRD(display,porta2,par);
  DumpSRD(display,porta3,par);
  DumpSRD(display,porta4,par);
             
  pausa(8);

  free_viewport(porta1);
  free_viewport(porta2);
  free_viewport(porta3);
  free_viewport(porta4);  
  free_bufferdevice(monitor);
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");

  return 0;
  }


