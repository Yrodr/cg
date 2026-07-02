/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

#include "cg2d.h"

int main(int argc, char ** argv) {

 bufferdevice * monitor;
 window * janela;
 viewport * porta;
 object2d * ob2d;
 point2d * b0, * b1, * b2, * b3;
 so_win par;
 
 __drawline * line;
 SetLine(&line,NULL);
  
 __drawfill * fill;
 SetFill(&fill,NULL);
  
 __drawdisplay * display;
 SetDisplay(&display,NULL);
 
 print("Executando...","red");
 
 monitor = CreateBuffer(600,600); // Cria um monitor virtual
 par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual
 
 janela = CreateWindow(-30.0,-30.0,30.0,30.0);
 porta = CreateViewPort(1, 1, 600, 600, "default");
 
 // Pontos de controle iniciais para uma curva de Bézier cúbica
 // Poderiam ser quaisquer conjuntos de 4 pontos no plano
 b0 = SetVertex2d(-20.0,-20.0,1.0,0.0);
 b1 = SetVertex2d(-10.0,10.0,1.0,0.0);
 b2 = SetVertex2d(10.0,10.0,1.0,0.0);
 b3 = SetVertex2d(20.0,-20.0,1.0,0.0);
 
 // Gera uma curva de Bézier com 4 pontos de controle (polinômio de grau 3)
 ob2d = CreateObject2d(1);
 CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);

 DrawObject(line,fill,ob2d,janela,porta,"open",1);
 // As variáveis controles são polígonos 
 // (pequenas circunferências que sinalizam a posição dos pontos de controle)
 // A função no código é apenas para ajudar a identificar a posição
 // dos pontos de controle
 // Essas variáveis poderiam ser retiradas sem prejuízo ao funcionamento do código 
 ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
 
 // Faz o display dos resultados na tela do computador
 DumpSRD(display,porta,par);
 free_object2d(ob2d);

 char opcao = '0', sentido;
 float x, y;
 while (opcao != 'q') {
   switch (opcao) {
      case '1': // altera a posição do primeiro ponto de controle
        x = GetXVertex2d(b0);
        y = GetYVertex2d(b0);
        printf("Primeiro ponto de controle: (%.2f,%.2f)\n",x,y);
              sentido = '0';
              while (sentido != 'q') {
                switch (sentido) {
                  case 'r':
                    clearDevice(porta);
                    x = GetXVertex2d(b0);
                    y = GetYVertex2d(b0);
                    printf("movendo para a direita -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x+1,b0);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);  
                  break;
                  case 'l':
                    clearDevice(porta);
                    x = GetXVertex2d(b0);
                    y = GetYVertex2d(b0);                
                    printf("movendo para a esquerda -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x-1,b0);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);                    
                  break;
                  case 'u':
                    clearDevice(porta);
                    x = GetXVertex2d(b0);
                    y = GetYVertex2d(b0);
                    printf("movendo para cima -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y+1,b0);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);                    
                  break;
                  case 'd':
                    clearDevice(porta);
                    x = GetXVertex2d(b0);
                    y = GetYVertex2d(b0);               
                    printf("movendo para baixo -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y-1,b0);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                    break;
                  }
                sentido = getchar(); 
                }
      break;
      case '2': // altera a posição do segundo ponto de controle
        x = GetXVertex2d(b1);
        y = GetYVertex2d(b1);
        printf("Segundo ponto de controle: (%.2f,%.2f)\n",x,y);
              sentido = '0';
              while (sentido != 'q') {
                switch (sentido) {
                  case 'r':
                    clearDevice(porta);
                    x = GetXVertex2d(b1);
                    y = GetYVertex2d(b1);
                    printf("movendo para a direita -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x+1,b1);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'l':
                    clearDevice(porta);
                    x = GetXVertex2d(b1);
                    y = GetYVertex2d(b1);                
                    printf("movendo para a esquerda -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x-1,b1);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'u':
                    clearDevice(porta);
                    x = GetXVertex2d(b1);
                    y = GetYVertex2d(b1);
                    printf("movendo para cima -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y+1,b1);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'd':
                    clearDevice(porta);
                    x = GetXVertex2d(b1);
                    y = GetYVertex2d(b1);               
                    printf("movendo para baixo -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y-1,b1);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  }
                sentido = getchar(); 
                }      
      break;
      case '3': // altera a posição do terceiro ponto de controle
        x = GetXVertex2d(b2);
        y = GetYVertex2d(b2);
        printf("Terceiro ponto de controle: (%.2f,%.2f)\n",x,y);
              sentido = '0';
              while (sentido != 'q') {
                switch (sentido) {
                  case 'r':
                    clearDevice(porta);
                    x = GetXVertex2d(b2);
                    y = GetYVertex2d(b2);
                    printf("movendo para a direita -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x+1,b2);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'l':
                    clearDevice(porta);
                    x = GetXVertex2d(b2);
                    y = GetYVertex2d(b2);                
                    printf("movendo para a esquerda -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x-1,b2);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'u':
                    clearDevice(porta);
                    x = GetXVertex2d(b2);
                    y = GetYVertex2d(b2);
                    printf("movendo para cima -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y+1,b2);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'd':
                    clearDevice(porta);
                    x = GetXVertex2d(b2);
                    y = GetYVertex2d(b2);               
                    printf("movendo para baixo -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y-1,b2);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  }
                sentido = getchar(); 
                }      
      break;
      case '4': // altera a posição do quarto ponto de controle
        x = GetXVertex2d(b3);
        y = GetYVertex2d(b3);
        printf("Quarto ponto de controle: (%.2f,%.2f)\n",x,y);
              sentido = '0';
              while (sentido != 'q') {
                switch (sentido) {
                  case 'r':
                    clearDevice(porta);
                    x = GetXVertex2d(b3);
                    y = GetYVertex2d(b3);
                    printf("movendo para a direita -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x+1,b3);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'l':
                    clearDevice(porta);
                    x = GetXVertex2d(b3);
                    y = GetYVertex2d(b3);                
                    printf("movendo para a esquerda -> (%.2f,%.2f)\n",x,y);            
                    SetXVertex2d(x-1,b3);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'u':
                    clearDevice(porta);
                    x = GetXVertex2d(b3);
                    y = GetYVertex2d(b3);
                    printf("movendo para cima -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y+1,b3);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  case 'd':
                    clearDevice(porta);
                    x = GetXVertex2d(b3);
                    y = GetYVertex2d(b3);               
                    printf("movendo para baixo -> (%.2f,%.2f)\n",x,y);            
                    SetYVertex2d(y-1,b3);
                    ob2d = CreateObject2d(1);
                    CubicBezier(b0,b1,b2,b3,ob2d,MAX_POINTS_BEZIER,1);
                    DrawObject(line,fill,ob2d,janela,porta,"open",-1);                    
                    ShowControl(line,fill,b0,b1,b2,b3,janela,porta);
                    DumpSRD(display,porta,par);
                    free_object2d(ob2d);
                  break;
                  }
                sentido = getchar(); 
                }      
      break;          
      }
   opcao = getchar();      
   }

 free(b0);
 free(b1);
 free(b2);
 free(b3);
 
 free(janela);
 free_viewport(porta);
 free_bufferdevice(monitor);
 
 CloseGraf(par);
 
 print("Terminado com êxito!","blue");
  
 return 0;
 }


