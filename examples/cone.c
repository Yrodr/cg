
// Superfície de revolução (em torno do eixo y na base do observador)

#include "cg3d.h"

int main(int argc, char ** argv) {
  float zvp, zcp;
  object3d * ob3d_sru, * ob3d_obs, * ob3d_proj;
  vector3d * observador, * alvo, * viewup;  
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

  // cria uma superfície de revolução (cone duplo)
  // coordenadas finais do segmento de reta (assumindo a origem como ponto inicial)
  // número de pontos da reta geradora 
  // número de fatias do objeto gerado
  ob3d_sru = cone(15.0,15.0,30,30);
  
  observador = SetVetor3d(0.0,0.0,100.0);
  alvo = SetVetor3d(0.0,0.0,0.0);
  viewup = SetVetor3d(0.0,1.0,0.0);
  viewMatrix = CreateObserver(observador,alvo,viewup);
  
  ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
  free(viewMatrix);
  free_object3d(ob3d_sru);
  
  // projeção perspectiva
  // coordenadas do ponto de vista do observador
  zvp = 40.0; zcp = -40.0;
  ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
  
  // Armazena a projeção no buffer do SRD
  // O último parâmetro indica que não deve haver preenchimento (modelo wireframe)
  drawObject3d(line,fill,ob3d_proj,janela,porta,0);
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
        drawObject3d(line,fill,ob3d_proj,janela,porta,0);
        free_object3d(ob3d_proj);        
      break;
      case 'y':
        clearDevice(porta);      
        m = SetRotMatrix3dY(10);
        TransObject3d(m,ob3d_obs);
        free(m);
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,0);
        free_object3d(ob3d_proj);
      break;
      case 'z':
        clearDevice(porta);
        m = SetRotMatrix3dZ(10);
        TransObject3d(m,ob3d_obs);
        free(m);
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,0);
        free_object3d(ob3d_proj);     
      break;
      }     
   DumpSRD(display,porta,par); 
   opcao = getchar();       
   }

  free(alvo);
  free(janela);  
  free(observador);
  free_viewport(porta);
  free_object3d(ob3d_obs);
  free_bufferdevice(monitor);

  CloseGraf(par);
  
  print("Terminado com êxito!","blue");  

  return 0; 
  }


