
// Preenchimento das faces visíveis utilizando o algoritmo z-buffer

// Leitura dos dados do prisma a partir de arquivos em disco

#include "cg3d.h"

int main(int argc, char ** argv) {
  object3d * ob3d_sru, * ob3d_obs, * ob3d_proj;
  vector3d * observador, * alvo, * viewup; 
  matrix3d * m, * viewMatrix;
  float zvp, zcp;

  bufferdevice * monitor;
  window * janela;
  viewport * porta;
  so_win par;
 
  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);
  
  print("Executando...","red");  
 
  monitor = CreateBuffer(600,600);
  par = InitGraf(monitor,argv[0]);
  
  ob3d_sru = GetData("../examples/data/prisma/faces.txt","../examples/data/prisma/vertices.txt");
  
  SetColorFace(&ob3d_sru->faces[0],1);   
  SetColorFace(&ob3d_sru->faces[1],2);  
  SetColorFace(&ob3d_sru->faces[2],3);
  SetColorFace(&ob3d_sru->faces[3],3);     
  SetColorFace(&ob3d_sru->faces[4],4);   
  SetColorFace(&ob3d_sru->faces[5],4);  
  SetColorFace(&ob3d_sru->faces[6],6);  
  SetColorFace(&ob3d_sru->faces[7],6);      

  observador = SetVetor3d(0.0, 0.0, 100.0);
  alvo = SetVetor3d(0.0, 0.0, 0.0);
  viewup = SetVetor3d(0.0, 1.0, 0.0);
  viewMatrix = CreateObserver(observador,alvo,viewup);
  ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
  free_object3d(ob3d_sru);  

  janela = CreateWindow(-25.0,-25.0,25.0,25.0); 
  porta = CreateViewPort(1,1,600,600,"default");

  // projeção perspectiva (um ponto de fuga)
  // coordenadas do ponto de vista do observador
  zvp = 40.0; zcp = -40.0;  
  ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
  // 2 para preenchimento com z-buffer 
  drawObject3d(line,fill,ob3d_proj,janela,porta,2);
  free_object3d(ob3d_proj);
    
  DumpSRD(display,porta,par);

  char opcao = 'c';
  while (opcao != 'q') {
    switch (opcao) {
      case 'x':
        clearDevice(porta);      
        m = SetRotMatrix3dX(10);
        TransObject3d(m,ob3d_obs);
        free(m);      
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,2);
        free_object3d(ob3d_proj);
      break;
      case 'y':
        clearDevice(porta);    
        m = SetRotMatrix3dY(10);
        TransObject3d(m,ob3d_obs);
        free(m);      
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,2);
        free_object3d(ob3d_proj);      
      break;
      case 'z':
        clearDevice(porta);     
        m = SetRotMatrix3dZ(10);
        TransObject3d(m,ob3d_obs);
        free(m);      
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,2);
        free_object3d(ob3d_proj);                
      break;
      case 'a': 
        clearDevice(porta);    
        m = SetSclMatrix3d(1.1,1.1,1.1);
        TransObject3d(m,ob3d_obs);
        free(m);      
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,2);
        free_object3d(ob3d_proj);                  
      break;
      case 'e':
        clearDevice(porta);     
        m = SetSclMatrix3d(0.9,0.9,0.9);
        TransObject3d(m,ob3d_obs);
        free(m);      
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,2);
        free_object3d(ob3d_proj);                 
      break;
      }
   DumpSRD(display,porta,par); 
   opcao = getchar();       
   }

  free(alvo);
  free(janela);
  free(observador);
  free(viewMatrix);
  free_viewport(porta); 
  free_object3d(ob3d_obs);
  free_bufferdevice(monitor);

  CloseGraf(par);
  
  print("Terminado com êxito!","blue");  

  return 0; 
  }


