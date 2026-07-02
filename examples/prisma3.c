
// Este código assume o observador virtal parado em relação ao SRU, "olhando para a origem";

// É realizada a conversão para a base do observador seguida de uma projeção perspectiva
// de um prisma de base triangular;

// Consideramos os vetores normais às faces do prisma e o vetor de visão do 
// observador virtual para determinar apenas as arestas vísiveis (modelo mais 
// realista da cena) retirando as ambiguidades de visualização do 
// prisma (ideia de superfícies limitantes);

// Apenas as arestas "visíveis" são projetadas no plano de visualização considerando 
// um modelo wireframe (modelo de arame) do objeto;

// A orientação da base do observador é negativa em relação a regra da mão direita;

// As faces são preenchidas utilizando um algoritmo de varredura (scanline).

#include "cg3d.h"

int main(int argc, char ** argv) {
  object3d * ob3d_sru, * ob3d_obs, * ob3d_proj;
  face * f1, * f2, * f3, * f4, * f5;
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

  // Criando 5 faces para um prisma de base triangular
  f1 = CreateFace(3);  
  SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 0),f1);
  SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 0),f1);
  SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 0),f1);
  SetColorFace(f1,1);

  f2 = CreateFace(3);
  SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 0),f2);
  SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 0),f2);
  SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 0),f2);
  SetColorFace(f2,2);
  
  f3 = CreateFace(4);
  SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 0),f3);
  SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 0),f3);
  SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 0),f3);
  SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 0),f3);
  SetColorFace(f3,3);
    
  f4 = CreateFace(4);
  SetPointFace(SetVertex3d(15.0, 10.0, -8.660254, 1.0, 0),f4);
  SetPointFace(SetVertex3d(-15.0, 10.0, -8.660254, 1.0, 0),f4);
  SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 0),f4);
  SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 0),f4);
  SetColorFace(f4,4);
  
  f5 = CreateFace(4);
  SetPointFace(SetVertex3d(15.0, 0.0, 8.660254, 1.0, 0),f5);
  SetPointFace(SetVertex3d(-15.0, 0.0, 8.660254, 1.0, 0),f5);
  SetPointFace(SetVertex3d(-15.0, -10.0, -8.660254, 1.0, 0),f5);
  SetPointFace(SetVertex3d(15.0, -10.0, -8.660254, 1.0, 0),f5);
  SetColorFace(f5,5);
  
  ob3d_sru = CreateObject3d(5);
  SetObject3d(f1,ob3d_sru);
  SetObject3d(f2,ob3d_sru);
  SetObject3d(f3,ob3d_sru);
  SetObject3d(f4,ob3d_sru);
  SetObject3d(f5,ob3d_sru);

  observador = SetVetor3d(0.0, 0.0, 100.0);
  alvo = SetVetor3d(0.0, 0.0, 0.0);
  viewup = SetVetor3d(0.0, 1.0, 0.0);
  viewMatrix = CreateObserver(observador,alvo,viewup); // Matriz de visualização
  ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
  free_object3d(ob3d_sru);
  
  janela = CreateWindow(-25.0,-25.0,25.0,25.0);  // janela para o prisma no SRU
  porta = CreateViewPort(1,1,600,600,"default"); // viewport para o SRD     
  
  // a posição do observador e do alvo devem estar no referencial do observador
  setReferencial(viewMatrix,observador);
  setReferencial(viewMatrix,alvo);
 
  look = lookAt(observador,alvo); 
  normalVisibleFaces(ob3d_obs,look);  // Elimina as arestas que estão "escondidas" no SRU
  
  // projeção perspectiva (um ponto de fuga)
  // coordenadas do ponto de vista do observador
  zvp = 40.0; zcp = -40.0;
  ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);   
  
  // Armazena a projeção no buffer do SRD
  // O último parâmetro indica que cada face deve ser preenchida com a
  // cor previamente definida utilizando um algoritmo de varredura
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
  free(observador);
  free(viewMatrix);
  free(janela);
  free_viewport(porta); 
  free_object3d(ob3d_obs);
  free_bufferdevice(monitor);

  CloseGraf(par);
  
  print("Terminado com êxito!","blue");  

  return 0; 
  }


