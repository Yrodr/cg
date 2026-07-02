#include "cg2d.h"
#include "exercicios.h"

int main(int argc, char ** argv) {
  bufferdevice * monitor;
  window * janela;
  viewport * porta;
  polygon * poligono;
  object2d * objeto;
  float x0, y0, a, b, raio;
  int cor;
  so_win par;
  
  __drawline * line;
  SetLine(&line, Draw_line_Other);
  
  __drawfill * fill;
  SetFill(&fill, ScanLineFill2);
  
  __drawdisplay * display;
  SetDisplay(&display, NULL);

  print("Executando testes da P1 e P2...", "red");
  
  monitor = CreateBuffer(600, 600);
  par = InitGraf(monitor, argv[0]);
  
  janela = CreateWindow(-10.0, -10.0, 10.0, 10.0);
  porta = CreateViewPort(1, 1, 600, 600, "default");
  
  // --- Testes P1: Primitivas Raster ---
  
  // 1. Círculos (SRD)
  raio = 50;
  Draw_Circle8_SRD(raio, porta, 1);
  Draw_Circle4_SRD(raio + 15, porta, 2);
  Draw_Circle2_SRD(raio + 30, porta, 3);  

  // 2. Preenchimento (FloodFill8)
  Draw_line_Other(100, 100, 200, 100, porta, 1);
  Draw_line_Other(200, 100, 200, 200, porta, 1);
  Draw_line_Other(200, 200, 100, 200, porta, 1);
  Draw_line_Other(100, 200, 100, 100, porta, 1);
  FloodFill8_2(150, 150, porta, 2, 0);

  // 3. Bresenham (Círculo e Elipses)
  circulo_bresenham(120, 450, 70, porta, 1);
  
  // Elipses (SRU convertido para SRD)
  a = 3.0; b = 2.0; x0 = 6.5; y0 = 6.0;
  Sru2Srd(&x0, &y0, janela, porta);
  point2srd(&a, janela, porta); point2srd(&b, janela, porta);
  elipse_bresenham((int)x0, (int)y0, (int)a, (int)b, porta, 2);

  // --- Espaço para implementação da P2 ---
  /* Aqui você adicionará as chamadas para:
     - BezierCurve2(...)
     - Rotinas de superfície translacional
     - Sólidos de revolução
  */

  // Mapeia o SRD no monitor
  DumpSRD(display, porta, par);
  pausa(10);
 
  // Limpeza
  free(janela);
  free_viewport(porta);
  free_bufferdevice(monitor);  
  CloseGraf(par);
  
  print("Terminado com êxito!", "blue");    
  return 0;
}