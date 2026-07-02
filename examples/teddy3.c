
// Este código assume o observador virtal parado em relação ao SRU, "olhando para a origem";

// É realizada a conversão para a base do observador seguida de uma projeção perspectiva
// de um objeto complexo (teddy);

// Consideramos os vetores normais às faces do objeto e o vetor de visão do 
// observador virtual para determinar apenas as arestas vísiveis (modelo mais 
// realista da cena) retirando as ambiguidades de visualização do 
// objeto (ideia de superfícies limitantes);

// Apenas as arestas "visíveis" são projetadas no plano de visualização considerando 
// um modelo wireframe (modelo de arame) do objeto;

// A orientação da base do observador é negativa em relação a regra da mão direita;

// Utilizando o conjunto de dados do modelo teddy;

// Preenchimento por varredura.

#include "cg3d.h"

int main(int argc, char ** argv) {
  object3d * ob3d_sru, * ob3d_obs, * ob3d_proj;
  vector3d * observador, * alvo, * viewup, * look;  
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
  
  janela = CreateWindow(-20.0,-20.0,20.0,20.0);
  porta = CreateViewPort(1,1,600,600,"yellow");

  // Utilizando o conjunto de dados do modelo teddy
  ob3d_sru = GetData("../examples/data/teddy/faces.txt","../examples/data/teddy/vertices.txt");
  SetColorObject3d(ob3d_sru,porta,128);

  observador = SetVetor3d(0.0,0.0,80.0);
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

  // projeção perspectiva (um ponto de fuga)
  // coordenadas do ponto de vista do observador
  zvp = 40.0; zcp = -45.0;  
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
      case 'a':
        clearDevice(porta);      
        m = SetSclMatrix3d(1.1,1.1,1.1);
        TransObject3d(m,ob3d_obs);
        free(m);
        normalVisibleFaces(ob3d_obs,look);        
        ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        drawObject3d(line,fill,ob3d_proj,janela,porta,1);
        free_object3d(ob3d_proj);   
      break;
      case 'e':
        clearDevice(porta);      
        m = SetSclMatrix3d(0.9,0.9,0.9);
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
  free(look);
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


