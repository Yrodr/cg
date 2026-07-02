#include "cg2d.h"

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  viewport * porta1, * porta2, * porta3, 
           * porta4, * porta5, * porta6,
           * porta7, * porta8, * porta9;
  so_win par;
  int i, j, min, step;
 
  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);

  print("Executando...","red");

  monitor = CreateBuffer(900,900);
  par = InitGraf(monitor,argv[0]);
  
  porta1 = CreateViewPort(1, 1, 300, 300, "p&b");
  porta2 = CreateViewPort(301, 1, 600, 300, "default");
  porta3 = CreateViewPort(601, 1, 900, 300, "gray");
  porta4 = CreateViewPort(1, 301, 300, 600, "red");
  porta5 = CreateViewPort(301, 301, 600, 600, "green");
  porta6 = CreateViewPort(601, 301, 900, 600, "blue");
  porta7 = CreateViewPort(1, 601, 300, 900, "cyan");
  porta8 = CreateViewPort(301, 601, 600, 900, "magenta");
  porta9 = CreateViewPort(601, 601, 900, 900, "yellow");
  
  min = 22; 
    
  for(i=min;i<porta1->ymax-porta1->ymin+1-min;i++) {
    for(j=min;j<porta1->xmax-porta1->xmin+1-min;j++) {
      if (i < (porta1->xmax-porta1->xmin+1)/2.0) SetPixel(i,j,0,porta1);
      else SetPixel(i,j,1,porta1);
      }
    }

  step = (porta1->xmax-porta1->xmin+1-2*min)/8;
  for(i=min;i<porta2->ymax-porta2->ymin+1-min;i++) {
    for(j=min;j<porta2->xmax-porta2->xmin+1-min;j++) {
      if (i <= min + step)
        SetPixel(i,j,0,porta2);
      if ((i > min + step)&&(i <= min + 2*step))
        SetPixel(i,j,1,porta2);
      if ((i > min + 2*step)&&(i <= min + 3*step))
        SetPixel(i,j,2,porta2);
      if ((i > min + 3*step)&&(i <= min + 4*step))
        SetPixel(i,j,3,porta2);
      if ((i > min + 4*step)&&(i <= min + 5*step))
        SetPixel(i,j,4,porta2);
      if ((i > min + 5*step)&&(i <= min + 6*step))
        SetPixel(i,j,5,porta2);
      if ((i > min + 6*step)&&(i <= min + 7*step))
        SetPixel(i,j,6,porta2);
      if (i > min + 7*step)
        SetPixel(i,j,7,porta2);                     
      }
    }

  for(i=min;i<porta3->ymax-porta3->ymin+1-min;i++) {
    for(j=min;j<porta3->xmax-porta3->xmin+1-min;j++) {
     SetPixel(i,j,i-min,porta3);
     } 
   }          

  for(i=min;i<porta4->ymax-porta4->ymin+1-min;i++) {
    for(j=min;j<porta4->xmax-porta4->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta4); 
      }
    }

  for(i=min;i<porta5->ymax-porta5->ymin+1-min;i++) {
    for(j=min;j<porta5->xmax-porta5->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta5);
      }
    }
    
  for(i=min;i<porta6->ymax-porta6->ymin+1-min;i++) {
    for(j=min;j<porta6->xmax-porta6->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta6);
      }
    }
    
  for(i=min;i<porta7->ymax-porta7->ymin+1-min;i++) {
    for(j=min;j<porta7->xmax-porta7->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta7);
      }
    }
    
  for(i=min;i<porta8->ymax-porta8->ymin+1-min;i++) {
    for(j=min;j<porta8->xmax-porta8->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta8);
      }
    }
    
  for(i=min;i<porta9->ymax-porta9->ymin+1-min;i++) {
    for(j=min;j<porta9->xmax-porta9->xmin+1-min;j++) {
      SetPixel(i,j,i-min,porta9);
      }
    }                

  DumpSRD(display,porta1,par);
  DumpSRD(display,porta2,par);
  DumpSRD(display,porta3,par);
  DumpSRD(display,porta4,par);
  DumpSRD(display,porta5,par);
  DumpSRD(display,porta6,par);
  DumpSRD(display,porta7,par);
  DumpSRD(display,porta8,par);
  DumpSRD(display,porta9,par);
                
  pausa(8);
  
  SaveBufferImage(argv[0],porta7);

  free_viewport(porta1);
  free_viewport(porta2);
  free_viewport(porta3);
  free_viewport(porta4);
  free_viewport(porta5);
  free_viewport(porta6);
  free_viewport(porta7);
  free_viewport(porta8);
  free_viewport(porta9);  
  free_bufferdevice(monitor);
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");

  return 0;
  }


