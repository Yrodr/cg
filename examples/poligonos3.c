/* 
   Autor: Murillo Rodrigo Petrucelli Homem
   Departamento de Computação
   Universidade Federal de São Carlos
*/

#include "cg2d.h"
#include "exercicios.h"

int main(int argc, char ** argv) {

  bufferdevice * monitor;
  window * janela;
  viewport * porta;
  polygon * poligono;
  object2d * objeto;
  so_win par;
  int opcao, lado, raio;
  __drawline * line;
  
  __drawfill * fill;
  SetFill(&fill,NULL); // rotina default: ScanLineFill()
  
  __drawdisplay * display;
  // rotina default (parâmetro NULL): RefreshX()
  // opção para terminal tty: Display_SRD()
  SetDisplay(&display,NULL);  
                              
  print("Executando...","red");
 
  if (argc == 1) { // poligonos chamado sem parâmetros...
    opcao = 0; // utiliza por padrão o algoritmo do ponto médio da biblioteca
    lado = 6;  // define por default um polígono regular de 6 lados (ou 6 vértices)
    raio = 3;
    }
  else {
    // precisa fazer uma verificação dos valores válidos!
    opcao = atoi(argv[1]); 
    lado = atoi(argv[2]);
    raio = atoi(argv[3]);    
    }

  // opcao = 1 -> rasterização pela função Draw_line_DDA()
  // opcao = 2 -> rasterização pela função Draw_line_Other()
  // outro valor -> rasterização pelo algoritmo default já implementado
  if (opcao == 1) SetLine(&line,Draw_line_DDA);
  else if (opcao == 2) SetLine(&line,Draw_line_Other);
       else SetLine(&line,NULL); // rotina default: Bresenham
  
  monitor = CreateBuffer(600,600); // Cria um buffer (SRD) para monitor virtual
  par = InitGraf(monitor,argv[0]);  // Conversa com o SO para criar o monitor virtual
    
  // cria um polígono regular
  poligono = RegularPolygon2d(lado,raio);
  SetColorPolig2d(1,poligono);
   
  objeto = CreateObject2d(1);
  SetObject2d(poligono,objeto);
 
  // cria uma janela de visualização (coordenadas no SRU)
  janela = CreateWindow(-5.0,-5.0,5.0,5.0);

  // Cria uma viewport
  // No caso uma única saída para o dispositivo de visualização com 600x600 entradas
  // O quinto parâmetro define o mapa de cores.
  porta = CreateViewPort(1, 1, 600, 600,"default");

  // Desenha no SRD
  DrawObject(line,fill,objeto,janela,porta,"close",-1); // fechado e sem preenchimento
  // Mapeia o SRD no monitor virtual exibindo o objeto na tela 
  DumpSRD(display,porta,par);
  pausa(2);
  
  // Preenche o polígono que compõe o objeto
  DrawObject(line,fill,objeto,janela,porta,"close",3); // fechado com preenchimento
  DumpSRD(display,porta,par);
  pausa(2);
  
  // libera os ponteiros
  free(janela);
  free(porta);  
  free_object2d(objeto);
  free_bufferdevice(monitor);
  
  CloseGraf(par);
  
  print("Terminado com êxito!","blue");
 
  return 0;
  }

