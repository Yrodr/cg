#include "cg3d.h"
#include "exercicios.h"

int main(int argc, char ** argv) {
  float zvp, zcp;
  object3d * ob3d_sru, * ob3d_obs, * ob3d_proj;
  vector3d * observador, * alvo, * viewup;  
  matrix3d * viewMatrix, * m, * m_trans;
 
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
  
  print("Executando Tubo Deslocado em Spline de Bézier...","red");
 
  monitor = CreateBuffer(600,600);
  par = InitGraf(monitor,argv[0]);
  
  janela = CreateWindow(-45.0,-45.0,45.0,45.0);
  porta = CreateViewPort(1,1,600,600,"default");

  // ==========================================
  // CRIANDO O TUBO (EXERCÍCIO 4)
  // ==========================================
  // 13 Pontos de controle modelando um caminho serpenteante (como uma hélice dupla)
  point3d pts_controle[13] = {
      {  0, -30,   0, 1.0, 0}, { 15, -20,  15, 1.0, 0}, { 15, -10, -15, 1.0, 0}, {  0,   0,   0, 1.0, 0}, // Trecho 1
      {-15,  10,  15, 1.0, 0}, {-15,  20, -15, 1.0, 0}, {  0,  30,   0, 1.0, 0}, // Trecho 2
      { 15,  40,  15, 1.0, 0}, { 15,  50, -15, 1.0, 0}, {  0,  60,   0, 1.0, 0}, // Trecho 3
      {-15,  70,  15, 1.0, 0}, {-15,  80, -15, 1.0, 0}, {  0,  90,   0, 1.0, 0}  // Trecho 4
  };

  // Cria um "cano" com perfil octogonal (8 lados), raio 3.5 e 60 subdivisões longitudinais
  ob3d_sru = tubo_bezier_concatenado(pts_controle, 8, 3.5, 60, 2);

  // Desce o objeto inteiro um pouco no eixo Y para ficar centralizado na tela
  m_trans = SetSftMatrix3d(0.0, -30.0, 0.0);
  TransObject3d(m_trans, ob3d_sru);
  free(m_trans);
  // ==========================================
  
  observador = SetVetor3d(0.0,0.0,100.0);
  alvo = SetVetor3d(0.0,0.0,0.0);
  viewup = SetVetor3d(0.0,1.0,0.0);
  viewMatrix = CreateObserver(observador,alvo,viewup);
  
  ob3d_obs = ConvertObjectBase(viewMatrix,ob3d_sru);
  free(viewMatrix);
  free_object3d(ob3d_sru);
  
  zvp = 40.0; zcp = -40.0;
  ob3d_proj = PerspProjBuffer(ob3d_obs,zvp,zcp);
  
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