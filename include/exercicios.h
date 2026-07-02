#ifndef EXERCICIOS_H
#define EXERCICIOS_H

#include "cg2d.h"
#include "cg3d.h"
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

// Exercícios 1
object3d * sup_translacional(int, float, float, int, int);

// Exercícios 2
polygon * gerar_perfil_parabola(float, float, int);
object3d * solido_revolucao_y(polygon *, int, int);

// Exercícios 3
polygon * gerar_perfil_hiperbola(float, float, float, int);

// Exercício 4
point3d eval_bezier3d(point3d, point3d, point3d, point3d, float);
vector3d deriv_bezier3d(point3d, point3d, point3d, point3d, float);
object3d * tubo_bezier_concatenado(point3d *, int, float, int, int);

#endif
