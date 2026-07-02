
// Superfície de revolução (em torno do eixo y na base do observador)

// Um elipsóide de revolução oblato ou achatado corresponde a uma esfera 
// comprimida ao longo do eixo z, mantendo os eixos x e y inalterados

// Preenchimento por varredura

#include "cg3d.h"

int main(int argc, char ** argv) {
  float zvp, zcp;
  object3d * ob3d_sru, * ob3d_obs, * ob3d_proj;
  vector3d * observador, * alvo, * viewup, * look; 
  matrix3d * viewMatrix, * m;
 
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
  
  janela = CreateWindow(-10.0,-10.0,10.0,10.0);
  porta = CreateViewPort(1,1,600,600,"default");

  // cria uma superfície de revolução (elipsóide oblato)
  // número de lados do polígono gerador
  // raio do polígono gerador (raio do círculo gerador)
  // número de fatias do objeto gerado
  // excentricidade (e): 0 < e < 1
  ob3d_sru = elipsoide_oblato(20,10.0,30,0.8);
  
  observador = SetVetor3d(0.0,0.0,100.0);
  alvo = SetVetor3d(0.0,0.0,0.0);
  viewup = SetVetor3d(0.0,1.0,0.0);
  viewMatrix = CreateObserver(observador,alvo,viewup);
  
  ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
  free_object3d(ob3d_sru);
  
  // a posição do observador e do alvo devem estar no referencial do observador
  setReferencial(viewMatrix,observador);
  setReferencial(viewMatrix,alvo);
 
  look = lookAt(observador,alvo); 
  normalVisibleFaces(ob3d_obs,look);    
  
  // projeção perspectiva
  // coordenadas do ponto de vista do observador
  zvp = 40.0; zcp = -40.0;
  ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
  
  // Armazena a projeção no buffer do SRD
  drawObject3d(line,fill,ob3d_proj,janela,porta,1);
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
        normalVisibleFaces(ob3d_obs,look);
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,1);
        free_object3d(ob3d_proj);        
      break;
      case 'y':
        clearDevice(porta);      
        m = SetRotMatrix3dY(10);
        TransObject3d(m,ob3d_obs);
        free(m);
        normalVisibleFaces(ob3d_obs,look);
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,1);
        free_object3d(ob3d_proj);
      break;
      case 'z':
        clearDevice(porta);
        m = SetRotMatrix3dZ(10);
        TransObject3d(m,ob3d_obs);
        free(m);
        normalVisibleFaces(ob3d_obs,look);        
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,1);
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


