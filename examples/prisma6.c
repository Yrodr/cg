
// Exemplo da visualização do prisma de base triangular com as faces prenchidas na
// perspectiva do observador, exibido na primeira view-port e da "visão da luz" do
// objeto (prisma), exibido na segunda view-port.

// Este exemplo considera apenas a "visão" do mesmo objeto em relação a dois pontos
// de vista (observador e uma luz pontual).

// A determinação das faces visíveis para ambos (luz e observador) é baseada no z-buffer.

#include "cg3d.h"

int main(int argc, char ** argv) {
  object3d * ob3d_sru, * ob3d_obs, * ob3d_lig, * ob3d_obs_proj, * ob3d_lig_proj;
  vector3d * observador, * alvo, * viewup, * positionLigth; 
  matrix3d * m, * viewMatrix, * ligthMatrix;
  float zvp, zcp;  

  bufferdevice * monitor;
  window * janela;
  viewport * porta1, * porta2;
  so_win par;

  __drawline * line;
  SetLine(&line,NULL);
  
  __drawfill * fill;
  SetFill(&fill,NULL);
  
  __drawdisplay * display;
  SetDisplay(&display,NULL);
  
  print("Executando...","red");  
 
  monitor = CreateBuffer(800,400);
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

  observador = SetVetor3d(0.0,0.0,100.0);
  positionLigth = SetVetor3d(-100.0,100.0,0.0);  
  alvo = SetVetor3d(0.0,0.0,0.0);
  viewup = SetVetor3d(0.0,1.0,0.0);
  
  viewMatrix = CreateObserver(observador,alvo,viewup);
  ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);

  ligthMatrix = createLightBase(positionLigth,alvo);
  ob3d_lig = ConvertObjectBase(ligthMatrix,ob3d_sru);

  janela = CreateWindow(-25.0,-25.0,25.0,25.0);
  porta1 = CreateViewPort(1,1,400,400, "default");   // viewport para o objeto
  porta2 = CreateViewPort(401,1,800,400, "default"); // viewport para a luz

  // projeção perspectiva (um ponto de fuga)
  zvp = 40.0; zcp = -40.0;
  ob3d_obs_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
  free_object3d(ob3d_obs);
  ob3d_lig_proj = PerspProjBuffer(ob3d_lig,zvp,zcp);
  free_object3d(ob3d_lig);  

  // 2 para preenchimento com z-buffer 
  drawObject3d(line,fill,ob3d_obs_proj,janela,porta1,2);
  free_object3d(ob3d_obs_proj);
  
  // 2 para preenchimento com z-buffer 
  drawObject3d(line,fill,ob3d_lig_proj,janela,porta2,2);
  free_object3d(ob3d_lig_proj);  
    
  DumpSRD(display,porta1,par);
  DumpSRD(display,porta2,par);

  char opcao = 'c';
  while (opcao != 'q') {
    switch (opcao) {
      case 'x':
        clearDevice(porta1);
        clearDevice(porta2);               
        m = SetRotMatrix3dX(10);
        TransObject3d(m,ob3d_sru);
        free(m);
        ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
        ob3d_obs_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        free_object3d(ob3d_obs);
        ob3d_lig = ConvertObjectBase(ligthMatrix,ob3d_sru);
        ob3d_lig_proj = PerspProjBuffer(ob3d_lig,zvp,zcp);
        free_object3d(ob3d_lig);          
        drawObject3d(line,fill,ob3d_obs_proj,janela,porta1,2);
        free_object3d(ob3d_obs_proj);        
        drawObject3d(line,fill,ob3d_lig_proj,janela,porta2,2);
        free_object3d(ob3d_lig_proj);
      break;
      case 'y':
        clearDevice(porta1);
        clearDevice(porta2);               
        m = SetRotMatrix3dY(10);
        TransObject3d(m,ob3d_sru);
        free(m);
        ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
        ob3d_obs_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        free_object3d(ob3d_obs);
        ob3d_lig = ConvertObjectBase(ligthMatrix,ob3d_sru);
        ob3d_lig_proj = PerspProjBuffer(ob3d_lig,zvp,zcp);
        free_object3d(ob3d_lig);          
        drawObject3d(line,fill,ob3d_obs_proj,janela,porta1,2);
        free_object3d(ob3d_obs_proj);        
        drawObject3d(line,fill,ob3d_lig_proj,janela,porta2,2);
        free_object3d(ob3d_lig_proj);      
      break;
      case 'z':
        clearDevice(porta1);
        clearDevice(porta2);               
        m = SetRotMatrix3dZ(10);
        TransObject3d(m,ob3d_sru);
        free(m);
        ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
        ob3d_obs_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
        free_object3d(ob3d_obs);
        ob3d_lig = ConvertObjectBase(ligthMatrix,ob3d_sru);
        ob3d_lig_proj = PerspProjBuffer(ob3d_lig,zvp,zcp);
        free_object3d(ob3d_lig);          
        drawObject3d(line,fill,ob3d_obs_proj,janela,porta1,2);
        free_object3d(ob3d_obs_proj);        
        drawObject3d(line,fill,ob3d_lig_proj,janela,porta2,2);
        free_object3d(ob3d_lig_proj);        
      break;
      }
    DumpSRD(display,porta1,par);
    DumpSRD(display,porta2,par); 
    opcao = getchar();       
    }

  free(observador);
  free(alvo);
  free(positionLigth);
  free(janela);
  free(viewMatrix);
  free(ligthMatrix);
  free_viewport(porta1);
  free_viewport(porta2);
  free_object3d(ob3d_sru);  
  free_bufferdevice(monitor);

  CloseGraf(par);
  
  print("Terminado com êxito!","blue");  

  return 0; 
  }


