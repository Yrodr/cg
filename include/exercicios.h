#ifndef __EXER__
#define __EXER__

// Protótipos das funções para conversão de segmentos de reta
// A rasterização é realizada diretamente no SRD

// Método incremental DDA (Digital Differential Analyser)
void Draw_line_DDA(int, int, int, int, viewport *, int);

// Método de Bresenham
void Draw_line_Other(int, int, int, int, viewport *, int);

// Preenchimento de polígonos regulares pelo método de varredura
void ScanLineFill_2(__drawline *, polygon *, window *, viewport *, int);

// Preenchimento de curvas fechadas (método recursivo)
void FloodFill8_2(int, int, viewport *, int, int);

void circulo_bresenham(int, int, int, viewport *, int);
void elipse_bresenham(int, int, int, int, viewport *, int);

polygon * BezierCurve2(point2d *, point2d *, point2d *, point2d *, int, int);
void CubicBezier2(point2d *, point2d *, point2d *, point2d *, object2d *, int);

// Exercícios da segunda avaliação prática
object3d * sup_translacional(int, float, float, int, int);

#endif
