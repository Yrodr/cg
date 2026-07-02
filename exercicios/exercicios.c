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
//
// Ideia: RegularPolygon2d(n,r) já sabe gerar os n vértices de um polígono
// regular no plano (x,y) do SRU 2D. Aqui esse polígono é reaproveitado como
// "perfil": copiamos os seus n pontos m vezes -- cada cópia (uma "seção" ou
// "anel") deslocada s unidades a mais no eixo Y -- e ligamos anéis
// consecutivos com faces laterais (quadriláteros), fechando a base e o topo
// com duas faces poligonais de n lados (para gerar um sólido fechado).
object3d * sup_translacional(int n, float r, float s, int m, int cor) {

  if (n < 3 || m < 2) return NULL; // polígono válido e ao menos 2 seções

  int num_faces = n * (m - 1) + 2; // faces laterais entre seções consecutivas + 2 tampas
  object3d * obj = CreateObject3d(num_faces);

  // 1) Gera o perfil (polígono regular) que será transladado
  polygon * perfil = RegularPolygon2d((unsigned int)n, r);

  // 2) Gera as m seções (anéis) empilhadas ao longo do eixo Y.
  //    O par (x,y) do polígono 2D é reaproveitado como (x,z) no espaço 3D;
  //    a altura de cada anel é dada pelo passo s. O sólido fica centralizado
  //    em torno de y = 0 (metade das seções abaixo, metade acima).
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

  // 3) Faces laterais: cada aresta (k, k+1) do anel i é ligada à mesma
  //    aresta do anel i+1, formando um quadrilátero. A ordem dos pontos
  //    segue a regra da mão direita para que a normal aponte para fora
  //    (para longe do eixo Y). Essa ordem foi validada testando
  //    SetNormalFace() e comparando com a direção radial esperada.
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

  // 4) Tampa da base (anel 0): mesma ordem do perfil -> normal para -Y
  face * base = CreateFace(n);
  for (int k = 0; k < n; k++)
    SetPointFace(SetVertex3d(anel[0][k].x, anel[0][k].y, anel[0][k].z, 1.0, 0), base);
  SetColorFace(base, cor);
  isFaceVisible(base, true);
  SetObject3d(base, obj);

  // 5) Tampa do topo (anel m-1): ordem invertida -> normal para +Y
  face * topo = CreateFace(n);
  for (int k = n - 1; k >= 0; k--)
    SetPointFace(SetVertex3d(anel[m-1][k].x, anel[m-1][k].y, anel[m-1][k].z, 1.0, 0), topo);
  SetColorFace(topo, cor);
  isFaceVisible(topo, true);
  SetObject3d(topo, obj);

  // 6) Calcula as normais de todas as faces do objeto de uma só vez
  SetNormalFaceObj(obj);

  // 7) Libera as estruturas auxiliares (o objeto 3D final permanece de pé)
  free_polygon(perfil);
  for (int i = 0; i < m; i++) free(anel[i]);
  free(anel);

  return obj;
  }