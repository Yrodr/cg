#include "cg2d.h"
#include "cg3d.h"
#include "exercicios.h"

#include <math.h>

/* IMPORTANTE: OS EXERCÍCIOS DEVEM SER REALIZADOS NESTE ARQUIVO */

// Novas funções para a conversão matricial de segmentos de reta -> rasterização
// Estas funções são chamadas pela função DrawObject()
// A função DrawObject() é responsável por verificar se os pontos de entrada
// p1 = (x1,y1) e p2 = (x2,x2) estão dentro da janela de visualização e é
// responsável pela conversão entre os "Sistemas de Referência" (SRU -> SRN -> SRD).
// Caso algum ponto esteja fora da janela, será determinado apenas o segmento
// que está dentro da janela.
// A DrawObject() garante que o ponto p1 está mais a esquerda do ponto p2
// e que a coordenadas já estejam corretamente mapeadas no SRD com valores
// inteiros positivos, podendo chamar as funções Draw_line_DDA() e Draw_line_Other().

// Método incremental DDA (Digital Differential Analyser)
void Draw_line_DDA(int x1, int y1, int x2, int y2, viewport * port, int cor) {
  int i;
  float dx, dy, x, y, step;
  
  dx = x2 - x1;
  dy = y2 - y1;
  
  if (abs(dx) >= abs(dy)) step = abs(dx);
  else step = abs(dy);
  
  dx = dx / step;
  dy = dy / step;
  x = (float) x1;
  y = (float) y1;
  i = 0;
  while (i <= step) {
    SetPixel((unsigned int)round(x),(unsigned int)round(y),cor,port);
    x = x + dx;
    y = y + dy;
    i = i + 1; 
  }  
}

void Draw_line_Other(int x1, int y1, int x2, int y2, viewport * port, int cor) {
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;
  int e2;

  while (1) {
      SetPixel(x1, y1, cor, port);
      if (x1 == x2 && y1 == y2) break;
      e2 = 2 * err;
      if (e2 > -dy) {
          err -= dy;
          x1 += sx;
      }
      if (e2 < dx) {
          err += dx;
          y1 += sy;
      }
  }
}
 

/*
int Draw_Circle8_SRD(float raio, viewport * port, int cor) {
  int cx = port->xmax / 2;
  int cy = port->ymax / 2;
  int x, y;
  float half = raio / sqrt(2);
  float raio2 = raio * raio;

  for (int i = 0; i <= (int)round(half); i++) {
      x = i;
      y = (int)round(sqrt(raio2 - x*x));

      SetPixel(cx + x, cy + y, cor, port);
      SetPixel(cx + y, cy + x, cor, port);
      SetPixel(cx + y, cy - x, cor, port);
      SetPixel(cx + x, cy - y, cor, port);
      SetPixel(cx - x, cy - y, cor, port);
      SetPixel(cx - y, cy - x, cor, port);
      SetPixel(cx - y, cy + x, cor, port);
      SetPixel(cx - x, cy + y, cor, port);
  }
  return 0;
}

int Draw_Circle4_SRD(float raio, viewport * port, int cor) {
  int cx = port->xmax / 2;
  int cy = port->ymax / 2;
  int x, y;
  float raio2 = raio * raio;

  for (int i = 0; i <= (int)round(raio); i++) {
      x = i;
      y = (int)round(sqrt(raio2 - x*x));

      SetPixel(cx + x, cy + y, cor, port);
      SetPixel(cx - x, cy + y, cor, port);
      SetPixel(cx + x, cy - y, cor, port);
      SetPixel(cx - x, cy - y, cor, port);
  }
  return 0;
}
 
int Draw_Circle2_SRD(float raio, viewport * port, int cor) {
  int cx = port->xmax / 2;
  int cy = port->ymax / 2;
  int x, y;
  float raio2 = raio * raio;

  for (int i = (int)round(-raio); i <= (int)round(raio); i++) {
      x = i;
      y = (int)round(sqrt(raio2 - x*x));

      SetPixel(cx + x, cy + y, cor, port);
      SetPixel(cx + x, cy - y, cor, port);
  }
  return 0;
}
*/

void ScanLineFill_2(__drawline * line, polygon * pol, window * win, viewport * port, int cor) {
  int i, j, y, minY, maxY;
  int count;

  if (pol->numbers_of_points < 3) return;

  int *inter_x = (int *)malloc(pol->numbers_of_points * sizeof(int));
  point2d *pts = (point2d *)malloc(pol->numbers_of_points * sizeof(point2d));

  if (inter_x == NULL || pts == NULL) return; 

  for (i = 0; i < pol->numbers_of_points; i++) {
      pts[i].x = pol->points[i].x;
      pts[i].y = pol->points[i].y;
      Sru2Srd(&(pts[i].x), &(pts[i].y), win, port);
  }

  minY = (int)round(pts[0].y);
  maxY = (int)round(pts[0].y);
  for (i = 1; i < pol->numbers_of_points; i++) {
      if ((int)round(pts[i].y) > maxY) maxY = (int)round(pts[i].y);
      if ((int)round(pts[i].y) < minY) minY = (int)round(pts[i].y);
  }

  for (y = minY; y <= maxY; y++) {
      count = 0;
      
      for (i = 0; i < pol->numbers_of_points; i++) {
          int next = (i + 1) % pol->numbers_of_points;
          
          int x1 = (int)round(pts[i].x);
          int y1 = (int)round(pts[i].y);
          int x2 = (int)round(pts[next].x);
          int y2 = (int)round(pts[next].y);

          if (y1 == y2) continue;

          if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
              float m_inv = (float)(x2 - x1) / (y2 - y1);
              inter_x[count++] = (int)round(x1 + m_inv * (y - y1));
          }
      }

      for (i = 0; i < count - 1; i++) {
          for (j = i + 1; j < count; j++) {
              if (inter_x[i] > inter_x[j]) {
                  int temp = inter_x[i];
                  inter_x[i] = inter_x[j];
                  inter_x[j] = temp;
              }
          }
      }

      for (i = 0; i < count; i += 2) {
          if (i + 1 < count) {
              for (int x_fill = inter_x[i]; x_fill <= inter_x[i+1]; x_fill++) {
                  SetPixel(x_fill, y, cor, port);
              }
          }
      }
  }
  
  free(inter_x);
  free(pts);
}

// Preenchimento de curvas fechadas (método recursivo)
void FloodFill8_2(int x, int y, viewport * port, int new, int old) {
  // 1. Verificação de limites de segurança (Bounds Check)
  // Evita que o algoritmo tente ler ou pintar fora da janela de visualização
  if (x < port->xmin || x > port->xmax || y < port->ymin || y > port->ymax) {
      return;
  }

  // 2. Lê a cor atual do pixel na coordenada (x, y)
  int current_color = GetPixel(x, y, port);

  // 3. Condição de parada (Base da recursão)
  // Só continua se o pixel atual tiver a cor que queremos substituir (old)
  // E garante que a cor nova é diferente da velha (para evitar loop infinito)
  if (current_color == old && current_color != new) {
      
      // Pinta o pixel atual com a nova cor
      SetPixel(x, y, new, port);

      // 4. Chamadas recursivas para espalhar a tinta nas 8 direções
      // Vizinhança cruzada (cima, baixo, esquerda, direita)
      FloodFill8_2(x + 1, y, port, new, old); // Direita
      FloodFill8_2(x - 1, y, port, new, old); // Esquerda
      FloodFill8_2(x, y + 1, port, new, old); // Cima
      FloodFill8_2(x, y - 1, port, new, old); // Baixo
      
      // Vizinhança diagonal
      FloodFill8_2(x + 1, y + 1, port, new, old); // Diagonal Superior Direita
      FloodFill8_2(x - 1, y + 1, port, new, old); // Diagonal Superior Esquerda
      FloodFill8_2(x + 1, y - 1, port, new, old); // Diagonal Inferior Direita
      FloodFill8_2(x - 1, y - 1, port, new, old); // Diagonal Inferior Esquerda
  }
}
  
void circulo_bresenham(int x0, int y0, int raio, viewport * port, int cor) {
  int x = 0;
  int y = raio;
  int d = 3 - 2 * raio; 

  while (x <= y) {
      SetPixel(x0 + x, y0 + y, cor, port);
      SetPixel(x0 - x, y0 + y, cor, port);
      SetPixel(x0 + x, y0 - y, cor, port);
      SetPixel(x0 - x, y0 - y, cor, port);
      SetPixel(x0 + y, y0 + x, cor, port);
      SetPixel(x0 - y, y0 + x, cor, port);
      SetPixel(x0 + y, y0 - x, cor, port);
      SetPixel(x0 - y, y0 - x, cor, port);

      if (d < 0) {
          d = d + 4 * x + 6;
      } else {
          d = d + 4 * (x - y) + 10;
          y--;
      }
      x++;
  }
}

void elipse_bresenham(int x0, int y0, int a, int b, viewport * port, int cor) {
  long a2 = (long)a * a;
  long b2 = (long)b * b;
  long dobroA2 = 2 * a2;
  long dobroB2 = 2 * b2;

  int x = 0;
  int y = b;
  long px = 0;
  long py = dobroA2 * y;

  double d1 = b2 - (a2 * b) + (0.25 * a2);
  
  while (px < py) {
      SetPixel(x0 + x, y0 + y, cor, port);
      SetPixel(x0 - x, y0 + y, cor, port);
      SetPixel(x0 + x, y0 - y, cor, port);
      SetPixel(x0 - x, y0 - y, cor, port);

      x++;
      px += dobroB2;
      if (d1 < 0) {
          d1 += b2 + px;
      } else {
          y--;
          py -= dobroA2;
          d1 += b2 + px - py;
      }
  }

  double d2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
  
  while (y >= 0) {
      SetPixel(x0 + x, y0 + y, cor, port);
      SetPixel(x0 - x, y0 + y, cor, port);
      SetPixel(x0 + x, y0 - y, cor, port);
      SetPixel(x0 - x, y0 - y, cor, port);

      y--;
      py -= dobroA2;
      if (d2 > 0) {
          d2 += a2 - py;
      } else {
          x++;
          px += dobroB2;
          d2 += a2 - py + px;
      }
  } 
}  

// Exercício 6: Segmento de reta em coordenadas polares
void reta_polar(int x0, int y0, float r1, float theta1, float r2, float theta2, viewport * port, int cor) {
    // 1. Converte os pontos polares para cartesianos locais para encontrar os coeficientes da reta
    float x1 = r1 * cos(theta1);
    float y1 = r1 * sin(theta1);
    float x2 = r2 * cos(theta2);
    float y2 = r2 * sin(theta2);

    // 2. Coeficientes da equação cartesiana: Ax + By + C = 0
    float A = y2 - y1;
    float B = x1 - x2;
    float C = x2 * y1 - x1 * y2;

    // 3. Organiza os limites angulares
    float min_theta = (theta1 < theta2) ? theta1 : theta2;
    float max_theta = (theta1 > theta2) ? theta1 : theta2;

    // Caso especial: se C for zero (ou muito próximo), a reta passa pela origem.
    // A equação r(theta) falharia (divisão por zero constante). 
    // Nesse caso, o ângulo é constante e variamos apenas o raio.
    if (fabs(C) < 0.001) {
        float min_r = (r1 < r2) ? r1 : r2;
        float max_r = (r1 > r2) ? r1 : r2;
        // O passo do raio é de 1 em 1 pixel
        for (float r = min_r; r <= max_r; r += 1.0) {
            int x = (int)round(x0 + r * cos(theta1));
            int y = (int)round(y0 + r * sin(theta1));
            SetPixel(x, y, cor, port);
        }
        return;
    }

    // 4. Define um passo (delta) para o ângulo. 
    // O passo deve ser pequeno o suficiente para não deixar buracos na reta.
    // É inversamente proporcional ao maior raio do segmento.
    float r_max = (r1 > r2) ? r1 : r2;
    float passo = 1.0 / (r_max > 1.0 ? r_max : 1.0); 

    // 5. Varredura angular
    for (float t = min_theta; t <= max_theta; t += passo) {
        float denominador = A * cos(t) + B * sin(t);
        
        // Evita divisão por zero caso o denominador zere em algum momento
        if (fabs(denominador) > 0.0001) { 
            float r = -C / denominador;
            
            // Converte o r(t) e t de volta para o sistema do monitor somando a origem (x0, y0)
            int x = (int)round(x0 + r * cos(t));
            int y = (int)round(y0 + r * sin(t));
            
            SetPixel(x, y, cor, port);
        }
    }
}

// Exercício 7: Circunfência em coordenadas polares
void circulo_polar(int x0, int y0, int raio, viewport * port, int cor) {
    if (raio <= 0) return;

    // O segredo das curvas polares em matrizes de pixels é o "passo" (delta) angular.
    // O comprimento de um arco é dado por s = raio * delta_theta.
    // Para que o avanço na tela seja de aproximadamente 1 pixel (evitando buracos),
    // definimos o passo como 1 / raio.
    float passo = 1.0 / raio;
    float dois_pi = 2.0 * M_PI;

    for (float theta = 0.0; theta < dois_pi; theta += passo) {
        // Converte de polar para cartesiano e translada para o centro (x0, y0)
        int x = (int)round(x0 + raio * cos(theta));
        int y = (int)round(y0 + raio * sin(theta));

        // Plota o pixel no buffer da viewport
        SetPixel(x, y, cor, port);
    }
}

// Exercício 8: Curva r = sin(6*theta) + 2 em coordenadas polares 
void curva_polar(int x0, int y0, float escala, viewport * port, int cor) {
    // O raio máximo teórico da equação sin(6*theta) + 2 é 3.
    // Multiplicado pela escala, temos o raio máximo em pixels.
    float max_raio_pixels = 3.0 * escala; 
    
    // O passo para manter a curva sem buracos é 1 sobre o raio máximo
    float passo = 1.0 / max_raio_pixels;
    float dois_pi = 2.0 * M_PI;

    for (float theta = 0.0; theta < dois_pi; theta += passo) {
        // 1. Calcula o r para o theta atual segundo a equação matemática
        float r = sin(6.0 * theta) + 2.0;
        
        // 2. Converte para coordenadas cartesianas aplicando o fator de escala
        int x = (int)round(x0 + escala * r * cos(theta));
        int y = (int)round(y0 + escala * r * sin(theta));

        // 3. Desenha na tela
        SetPixel(x, y, cor, port);
    }
}
/* EXERCÍCIOS:

1) Implemente as rotinas Draw_line_DDA() e Draw_line_Other().

2) Implemente uma rotina para preenchimento de polígonos baseada na abordagem por varredura (veja o pseudo-código disponibilizado no moodle).

	void ScanLineFill_2(__drawline *, polygon *, window *, viewport *, int);

3) Implemente uma rotina para preenchimento de curvas fechadas baseada em recursividade.

	void FloodFill8_2(int, int, viewport *, int, int);

4) Implemente uma rotina para conversão matricial de um arco de circuferência.

	void circulo_bresenham(int, int, int, viewport *, int);

5) Implemente uma rotina para conversão matricial de uma elipse.

	void elipse_bresenham(int, int, int, int, viewport *, int);
	
6) Implemente uma rotina para traçar um seguimento de reta em coordenadas polares.

7) Implemente uma rotina para traçar uma circunfência em coordenadas polares.

8) Implemente uma rotina para traçar a curva dada por r = sin(6*theta) + 2.	
	
Para os exercícios 4 e 5, veja as considerações abaixo.

A forma implícita geral de uma cônica é:

F(x,y) = Ax² + Bxy + Cy² + Dx + Ey + F = 0

Se A diferente de C, temos uma elipse;
Se aparece o termo xy, temos uma rotação da figura;
Se só um termo quadrático aparece, temos uma parábola.

Assuma A = C e B = 0, temos a equação de uma circunfêrencia, dada por:

F(x,y) = x² + y² + Dx + Ey + F = 0

Considere apenas o caso de um arco de circunferência de 45°, em particular o arco de x = 0, y = R a x = y = 2^{-1/2}R.

Podemos utilizar um raciocínio similar ao algoritmo do ponto médio para linhas mas agora para o traçado de um arco de circunferência. 

Se (x,y) é um ponto da circunferência, F(x,y) = 0. 

Determine qual é o erro de partida, isto é, a variável de decisão que será utilizada para determinar qual a próxima entrada a ser preenchida e descreva quais são essas entradas baseadas no sinal da variável de decisão.

Implemente um código baseado nessa abordagem e que desenhe uma circunferência (utilize as propriedades de simetria da figura).

*/

polygon * BezierCurve2(point2d * p0, point2d * p1, point2d * p2, point2d * p3, int n, int color) {
    // 1. Aloca o polígono que conterá os n pontos amostrados da curva
    polygon * curva = CreatePolig2d(n);
    if (curva == NULL) return NULL;
    
    // Define a cor da estrutura do polígono
    SetColorPolig2d(color, curva);
    
    // 2. Calcula o passo de variação do parâmetro t
    // Para obter exatamente n pontos, dividimos o intervalo [0, 1] por (n - 1)
    float step = 1.0 / (n - 1);
    float t;
    
    for (int i = 0; i < n; i++) {
        t = i * step;
        
        // Polinómios de base de Bernstein para curvas cúbicas
        float b0 = (1.0 - t) * (1.0 - t) * (1.0 - t); // (1-t)³
        float b1 = 3.0 * (1.0 - t) * (1.0 - t) * t;   // 3(1-t)²t
        float b2 = 3.0 * (1.0 - t) * t * t;           // 3(1-t)t²
        float b3 = t * t * t;                         // t³
        
        // Interpolação das coordenadas X e Y
        float x = b0 * p0->x + b1 * p1->x + b2 * p2->x + b3 * p3->x;
        float y = b0 * p0->y + b1 * p1->y + b2 * p2->y + b3 * p3->y;
        
        // 3. Insere o vértice calculado na estrutura do polígono
        // O terceiro e quarto parâmetros são mantidos como 1.0 e 0.0 para homogeneidade e 3D
        SetPolig2d(SetVertex2d(x, y, 1.0, 0.0), curva);
    }
    
    return curva;
}
  
void CubicBezier2(point2d * b0, point2d * b1, point2d * b2, point2d * b3, object2d * ob2d, int color) {
    polygon * curva;
    
    // Gera a curva chamando a função de cálculo com o número máximo de pontos definido pela biblioteca
    curva = BezierCurve2(b0, b1, b2, b3, MAX_POINTS_BEZIER, color);
    
    // Associa o polígono gerado ao objeto bidimensional de saída
    SetObject2d(curva, ob2d);
}
////////////////////////////////////////////////////////////////////////////////////////

// EXERCÍCIOS PARA A SEGUNDA AVALIAÇÃO PRÁTICA
// Devem ser realizados neste arquivo

// 1) Considere a rotina para geração de um polígono regular. Implemente uma rotina que
// dado um polígono com n lados e raio r, gere uma superfície translacional com 
// passo s na direção do eixo y e m seções.

// 2) Considere a equação para o parabolóide elíptico e implemente uma rotina que dada 
// uma seção plana da curva, gere um sólido de revolução em torno do eixo y.

// 3) Considere a equação para o parabolóide hiperbólico e implemente uma rotina que dada 
// uma seção plana da curva, gere um sólido de revolução em torno do eixo y.
  
// 4) Desenvolva uma rotina que concatene 4 curvas de Bézier e desloque um polígono regular
// sobre a curva de forma de o vetor normal à face do polígono seja paralelo a reta 
// tangente à curva, descrevendo uma trajetória no espaço em m passos.


// Exercício 1 (3D): Superfície Translacional
// n: número de lados do polígono regular (perfil da seção transversal)
// r: raio do polígono base
// s: passo (tamanho do deslocamento no eixo Y entre cada seção)
// m: número de seções totais (m >= 2, ou seja, ao menos 1 "passo")
// cor: cor aplicada à superfície

object3d * sup_translacional(int n, float r, float s, int m, int cor) {

  if (n < 3 || m < 2) return NULL; // polígono válido e ao menos 2 seções

  int num_faces = n * (m - 1) + 2; // faces laterais entre seções consecutivas + 2 tampas
  object3d * obj = CreateObject3d(num_faces);

  // Gera o perfil (polígono regular) que será transladado
  polygon * perfil = RegularPolygon2d((unsigned int)n, r);

  // Gera as m seções (anéis) empilhadas ao longo do eixo Y.
  point3d ** anel = (point3d **) malloc(m * sizeof(point3d *));
  float y0 = -((m - 1) * s) / 2.0;

  for (int i = 0; i < m; i++) {
    float y = y0 + i * s;
    anel[i] = (point3d *) malloc(n * sizeof(point3d));
    for (int k = 0; k < n; k++) {
      anel[i][k].x = perfil->points[k].x;
      anel[i][k].y = y;
      anel[i][k].z = perfil->points[k].y;
      }
    }

  // Faces laterais: cada aresta (k, k+1) do anel i é ligada à mesma
  for (int i = 0; i < m - 1; i++) {
    for (int k = 0; k < n; k++) {
      int kk = (k + 1) % n;

      face * f = CreateFace(4);
      SetPointFace(SetVertex3d(anel[i][k].x,    anel[i][k].y,    anel[i][k].z,    1.0, 0), f);
      SetPointFace(SetVertex3d(anel[i+1][k].x,  anel[i+1][k].y,  anel[i+1][k].z,  1.0, 0), f);
      SetPointFace(SetVertex3d(anel[i+1][kk].x, anel[i+1][kk].y, anel[i+1][kk].z, 1.0, 0), f);
      SetPointFace(SetVertex3d(anel[i][kk].x,   anel[i][kk].y,   anel[i][kk].z,   1.0, 0), f);
      SetColorFace(f, cor);
      isFaceVisible(f, true);
      SetObject3d(f, obj);
      }
    }

  // Tampa da base (anel 0): mesma ordem do perfil -> normal para -Y
  face * base = CreateFace(n);
  for (int k = 0; k < n; k++)
    SetPointFace(SetVertex3d(anel[0][k].x, anel[0][k].y, anel[0][k].z, 1.0, 0), base);
  SetColorFace(base, cor);
  isFaceVisible(base, true);
  SetObject3d(base, obj);

  // Tampa do topo (anel m-1): ordem invertida -> normal para +Y
  face * topo = CreateFace(n);
  for (int k = n - 1; k >= 0; k--)
    SetPointFace(SetVertex3d(anel[m-1][k].x, anel[m-1][k].y, anel[m-1][k].z, 1.0, 0), topo);
  SetColorFace(topo, cor);
  isFaceVisible(topo, true);
  SetObject3d(topo, obj);

  // Calcula as normais de todas as faces do objeto de uma só vez
  SetNormalFaceObj(obj);

  // Libera as estruturas auxiliares (o objeto 3D final permanece de pé)
  free_polygon(perfil);
  for (int i = 0; i < m; i++) free(anel[i]);
  free(anel);

  return obj;
  }

// Gera a seção plana de uma parábola: y = a * x^2
// max_x: até onde a curva vai no eixo x (define a largura da "boca" do paraboloide)
// passos: número de pontos (resolução da curva)
polygon * gerar_perfil_parabola(float a, float max_x, int passos) {
    if (passos < 2) return NULL;
    
    polygon * perfil = CreatePolig2d(passos);
    float step = max_x / (passos - 1);
    
    for (int i = 0; i < passos; i++) {
        float x = i * step;
        float y = a * x * x; // Equação da parábola no plano
        SetPolig2d(SetVertex2d(x, y, 1.0, 0), perfil);
    }
    return perfil;
}

// Exercício 2 (3D): Sólido de revolução em torno do eixo Y
// perfil: polígono 2D contendo a seção plana (metade da parábola, do centro para a direita)
// m: número de fatias (setores radiais do sólido)
// cor: cor do objeto final
object3d * solido_revolucao_y(polygon * perfil, int m, int cor) {
    if (perfil == NULL || m < 3) return NULL;

    int n = perfil->numbers_of_points;
    object3d * obj = CreateObject3d((n - 1) * m);

    // Aloca a matriz de pontos 3D: [fatia_radial][ponto_do_perfil]
    point3d ** malha = (point3d **) malloc(m * sizeof(point3d *));
    float delta_theta = 2.0 * M_PI / m;

    for (int j = 0; j < m; j++) {
        malha[j] = (point3d *) malloc(n * sizeof(point3d));
        float theta = j * delta_theta;
        
        for (int i = 0; i < n; i++) {
            // Rotação matemática em torno do eixo Y
            malha[j][i].x = perfil->points[i].x * cos(theta);
            malha[j][i].y = perfil->points[i].y;
            malha[j][i].z = -perfil->points[i].x * sin(theta);
        }
    }

    // Constrói as faces da malha costurando a fatia atual com a próxima
    for (int j = 0; j < m; j++) {
        int j_next = (j + 1) % m; // Para fechar a última fatia com a primeira (360 graus)

        for (int i = 0; i < n - 1; i++) {
            // Verifica se o ponto está tocando o eixo Y para evitar faces degeneradas
            bool pole_i = (fabs(perfil->points[i].x) < 0.0001);
            
            face * f = NULL;
            if (pole_i) {
                // Se for a base do paraboloide no eixo Y, usamos um triângulo em vez de quadrilátero
                f = CreateFace(3);
                SetPointFace(SetVertex3d(malha[j][i].x, malha[j][i].y, malha[j][i].z, 1.0, 0), f);
                SetPointFace(SetVertex3d(malha[j_next][i+1].x, malha[j_next][i+1].y, malha[j_next][i+1].z, 1.0, 0), f);
                SetPointFace(SetVertex3d(malha[j][i+1].x, malha[j][i+1].y, malha[j][i+1].z, 1.0, 0), f);
            } else {
                // Corpo do paraboloide: criamos faces de 4 lados (Quadriláteros)
                f = CreateFace(4);
                SetPointFace(SetVertex3d(malha[j][i].x, malha[j][i].y, malha[j][i].z, 1.0, 0), f);
                SetPointFace(SetVertex3d(malha[j_next][i].x, malha[j_next][i].y, malha[j_next][i].z, 1.0, 0), f);
                SetPointFace(SetVertex3d(malha[j_next][i+1].x, malha[j_next][i+1].y, malha[j_next][i+1].z, 1.0, 0), f);
                SetPointFace(SetVertex3d(malha[j][i+1].x, malha[j][i+1].y, malha[j][i+1].z, 1.0, 0), f);
            }

            SetColorFace(f, cor);
            isFaceVisible(f, true);
            SetObject3d(f, obj);
        }
    }

    SetNormalFaceObj(obj); // Fundamental para não bugar a iluminação / visibilidade da lib

    // Libera a matriz temporária
    for (int j = 0; j < m; j++) {
        free(malha[j]);
    }
    free(malha);

    return obj;
}

// Gerar a seção plana de uma hipérbole no plano XY
// a: raio mínimo no centro (cintura do sólido)
// b: fator de abertura vertical
// max_y: define a altura do sólido (variando de -max_y até +max_y)
// passos: número de pontos na curva (resolução vertical)
polygon * gerar_perfil_hiperbola(float a, float b, float max_y, int passos) {
    if (passos < 2) return NULL;
    
    polygon * perfil = CreatePolig2d(passos);
    // Varia de -max_y até max_y para criar um sólido simétrico e centrado
    float step = (2.0 * max_y) / (passos - 1);
    
    for (int i = 0; i < passos; i++) {
        float y = -max_y + i * step;
        // Isolando x na equação da hipérbole: x = a * sqrt(1 + (y^2 / b^2))
        float x = a * sqrt(1.0 + (y * y) / (b * b));
        
        SetPolig2d(SetVertex2d(x, y, 1.0, 0), perfil);
    }
    return perfil;
}

// Avalia o ponto da Curva de Bézier Cúbica em 3D para um dado 't' (0.0 a 1.0)
point3d eval_bezier3d(point3d p0, point3d p1, point3d p2, point3d p3, float t) {
    float u = 1.0 - t;
    float b0 = u * u * u;
    float b1 = 3 * u * u * t;
    float b2 = 3 * u * t * t;
    float b3 = t * t * t;
    
    point3d p;
    p.x = b0 * p0.x + b1 * p1.x + b2 * p2.x + b3 * p3.x;
    p.y = b0 * p0.y + b1 * p1.y + b2 * p2.y + b3 * p3.y;
    p.z = b0 * p0.z + b1 * p1.z + b2 * p2.z + b3 * p3.z;
    return p;
}

// Calcula o vetor derivada (tangente) da Curva de Bézier Cúbica
vector3d deriv_bezier3d(point3d p0, point3d p1, point3d p2, point3d p3, float t) {
    float u = 1.0 - t;
    float c0 = 3 * u * u;
    float c1 = 6 * u * t;
    float c2 = 3 * t * t;
    
    vector3d d;
    d.x = c0 * (p1.x - p0.x) + c1 * (p2.x - p1.x) + c2 * (p3.x - p2.x);
    d.y = c0 * (p1.y - p0.y) + c1 * (p2.y - p1.y) + c2 * (p3.y - p2.y);
    d.z = c0 * (p1.z - p0.z) + c1 * (p2.z - p1.z) + c2 * (p3.z - p2.z);
    return d;
}

// Exercício 4: Tubo deslocado sobre 4 curvas de Bézier concatenadas
// pts: array contendo exatos 13 pontos (P0 a P12)
// n_lados: lados do polígono que forma o cano (ex: 4=quadrado, 8=octógono)
// raio: espessura do cano
// m_passos: quantidade de seções transversais
// cor: cor do objeto
object3d * tubo_bezier_concatenado(point3d * pts, int n_lados, float raio, int m_passos, int cor) {
    if (m_passos < 2 || n_lados < 3) return NULL;

    point3d ** malha = (point3d **) malloc(m_passos * sizeof(point3d *));
    polygon * perfil = RegularPolygon2d((unsigned int)n_lados, raio);

    float step = 1.0 / (m_passos - 1);
    
    for (int i = 0; i < m_passos; i++) {
        float u = i * step;            // 'u' varia de 0.0 a 1.0 cobrindo as 4 curvas
        int c = (int)(u * 4.0);        // Identifica qual sub-curva usar (0, 1, 2 ou 3)
        if (c >= 4) c = 3;             // Garante o limite no final do trajeto
        
        float t = u * 4.0 - c;         // Converte para 't' local (0.0 a 1.0) dentro da sub-curva
        if (u >= 1.0) t = 1.0;

        // Pega os 4 pontos de controle que regem o trecho atual
        point3d p0 = pts[c*3];
        point3d p1 = pts[c*3 + 1];
        point3d p2 = pts[c*3 + 2];
        point3d p3 = pts[c*3 + 3];

        // Avalia posição da trilha e o vetor tangente
        point3d pos = eval_bezier3d(p0, p1, p2, p3, t);
        vector3d T = deriv_bezier3d(p0, p1, p2, p3, t);
        
        // Normaliza a tangente (O eixo Z do polígono no espaço local)
        float norm_T = sqrt(T.x*T.x + T.y*T.y + T.z*T.z);
        if (norm_T > 0.0001) { T.x /= norm_T; T.y /= norm_T; T.z /= norm_T; }
        else { T.x = 0; T.y = 1; T.z = 0; } // Fallback de segurança

        // Define um vetor "Cima" auxiliar. Se a tangente for muito vertical, usa o eixo X
        vector3d up = {0.0, 1.0, 0.0};
        if (fabs(T.y) > 0.99) { up.x = 1.0; up.y = 0.0; up.z = 0.0; }

        // Cria o eixo X local (Normal: Tangente X Up)
        vector3d N; 
        N.x = T.y*up.z - T.z*up.y; N.y = T.z*up.x - T.x*up.z; N.z = T.x*up.y - T.y*up.x;
        float norm_N = sqrt(N.x*N.x + N.y*N.y + N.z*N.z);
        N.x /= norm_N; N.y /= norm_N; N.z /= norm_N;

        // Cria o eixo Y local (Binormal: Normal X Tangente)
        vector3d B;
        B.x = N.y*T.z - N.z*T.y; B.y = N.z*T.x - N.x*T.z; B.z = N.x*T.y - N.y*T.x;

        // Aplica a base ortogonal local aos vértices 2D para colocá-los no espaço 3D
        malha[i] = (point3d *) malloc(n_lados * sizeof(point3d));
        for (int k = 0; k < n_lados; k++) {
            float px = perfil->points[k].x;
            float py = perfil->points[k].y;
            
            // Transformação Linear: P3D = Pos + px*N + py*B
            malha[i][k].x = pos.x + px * N.x + py * B.x;
            malha[i][k].y = pos.y + px * N.y + py * B.y;
            malha[i][k].z = pos.z + px * N.z + py * B.z;
        }
    }

    // Costura das Faces entre os anéis gerados
    int num_faces = n_lados * (m_passos - 1);
    object3d * obj = CreateObject3d(num_faces);

    for (int i = 0; i < m_passos - 1; i++) {
        for (int k = 0; k < n_lados; k++) {
            int k_next = (k + 1) % n_lados;
            face * f = CreateFace(4);
            
            // Os 4 pontos do quadrilátero lateral
            SetPointFace(SetVertex3d(malha[i][k].x, malha[i][k].y, malha[i][k].z, 1.0, 0), f);
            SetPointFace(SetVertex3d(malha[i][k_next].x, malha[i][k_next].y, malha[i][k_next].z, 1.0, 0), f);
            SetPointFace(SetVertex3d(malha[i+1][k_next].x, malha[i+1][k_next].y, malha[i+1][k_next].z, 1.0, 0), f);
            SetPointFace(SetVertex3d(malha[i+1][k].x, malha[i+1][k].y, malha[i+1][k].z, 1.0, 0), f);

            SetColorFace(f, cor);
            isFaceVisible(f, true);
            SetObject3d(f, obj);
        }
    }

    SetNormalFaceObj(obj);

    for (int i = 0; i < m_passos; i++) free(malha[i]);
    free(malha);
    free_polygon(perfil);

    return obj;
}