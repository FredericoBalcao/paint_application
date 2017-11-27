/*
---------------------------------------------------------------------------------------------
Nome: Frederico Balcão
Data: 26-10-2016
Curso: Engenharia Informática
U.C: Computação Gráfica
Ano/Semestre: 2ºAno/1ºSemestre
Paint - OpenGL
------------------------------------------------------------------------------------------------------------------------------------------------------------
Para a utilização deste Paint, temos duas áreas, uma de trabalho e uma área de ferramentas.
Inicialmente temos que clicar com o botão direito do rato na área de trabalho para definir uma cor de fundo ou cor de linha (opcionais) nas opções 
de sub-menus antes de desenhar uma figura. A cor de fundo representa uma figura preenchida e uma cor de linha representa uma figura vazia (só com a linha).
Quando a cor selecioanda aparecer na área de ferramentas, basta escolhermos a figura que queremos e começar a desenhar na área de trabalho.
Para desenhar, clicamos num ponto qualquer na área de trabalho e arrastamos o rato até a figura estar completa/desenhada pelo utilizador, após estar 
desenhada, clicamos uma 2vez nessa mesma área para colocar a figura estável.
Para a opção de "Marcar", clicamos no ícone relativo à mesma e com o botão esquerdo do rato selecionamos a(s) figura(s) desenhadas, e se quisermos
apagar a figura basta clicarmos na tecla DEL, se quisermos mover basta arrastar a mesma para outra posição.
Temos também a opção pela interação com o botão direito do rato na área de trabalho, com submenus de alterar o tamanho do ponto(1.0 a 6.0) e a 
largura da linha(1.0 a 6.0).
Foram usadas duas listas (uma principal e outra auxiliar) para as funcionalidades de selecionar, apagar e mover a(s) figura(s).
A qualquer momento se quisermos sair do paint basta com o botão direito do rato na área de trabalho, escolher o submenu de "Sair do Paint".
-----------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "lista.h"
#include "Figura.h"
#include "Cor.h"
#include "Ponto.h"
#include <Windows.h>

#define Area 50 //representa a separação das áreas de trabalho e ferramentas, utilizada na função do rato

using namespace std;

enum CODIGO_COR
{
	RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, BLACK, TRANS
};

Cor corF, corL;
int modo = 0;
GLfloat tamanho_ponto = 1.0;
GLfloat largura_linha = 1.0;  //espessura
			
GLint largura;	// Altura e Largura da janela
GLint altura;
int contador=1, nr=0; //faz a contagem dos cliques do rato
Ponto inicio, fim, aux1=inicio;//para o display e motion
bool var = false;
//Ponto Del;
Ponto a, b;


// Cor Menu de fundo
void CorMenuF(GLint cod)
{
	if (cod == RED) // vermelho
	{
		corF.setR(1.0);
		corF.setG(0.0);
		corF.setB(0.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Vermelho");
	}
	else if (cod == GREEN) // Verde
	{
		corF.setR(0.0);
		corF.setG(1.0);
		corF.setB(0.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Verde");
	}
	else if (cod == BLUE) // Azul
	{
		corF.setR(0.0);
		corF.setG(0.0);
		corF.setB(1.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Azul");
	}
	else if (cod == CYAN) // Cyan
	{
		corF.setR(0.0);
		corF.setG(1.0);
		corF.setB(1.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Cyan");
	}
	else if (cod == MAGENTA) // Magenta
	{
		corF.setR(1.0);
		corF.setG(0.0);
		corF.setB(1.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Magenta");
	}
	else if (cod == YELLOW) // Amarelo
	{
		corF.setR(1.0);
		corF.setG(1.0);
		corF.setB(0.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Amarelo");
	}
	else if (cod == WHITE) // Branco
	{
		corF.setR(1.0);
		corF.setG(1.0);
		corF.setB(1.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Branco");
	}
	else if (cod == BLACK) // Preto
	{
		corF.setR(0.0);
		corF.setG(0.0);
		corF.setB(0.0);
		corF.setA(1.0);
		printf("Cor Selecionada de Fundo: Preto");
	}
	else if (cod == TRANS) //transparnte
	{
		corF.setR(0.0);
		corF.setG(0.0);
		corF.setB(0.0);
		corF.setA(0.0);
		printf("Cor Selecionada de Fundo: Transparente");
	}
	glutPostRedisplay();
}

// Cor Menu de linha
void CorMenuL(GLint cod)
{
	if (cod == RED) // vermelho
	{
		corL.setR(1.0);
		corL.setG(0.0);
		corL.setB(0.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Vermelho");
	}
	else if (cod == GREEN) // Verde
	{
		corL.setR(0.0);
		corL.setG(1.0);
		corL.setB(0.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Verde");
	}
	else if (cod == BLUE) // Azul
	{
		corL.setR(0.0);
		corL.setG(0.0);
		corL.setB(1.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Azul");
	}
	else if (cod == CYAN) // Cyan
	{
		corL.setR(0.0);
		corL.setG(1.0);
		corL.setB(1.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Cyan");
	}
	else if (cod == MAGENTA) // Magenta
	{
		corL.setR(1.0);
		corL.setG(0.0);
		corL.setB(1.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Magenta");
	}
	else if (cod == YELLOW) // Amarelo
	{
		corL.setR(1.0);
		corL.setG(1.0);
		corL.setB(0.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Amarelo");
	}
	else if (cod == WHITE) // Branco
	{
		corL.setR(1.0);
		corL.setG(1.0);
		corL.setB(1.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Branco");
	}
	else if (cod == BLACK) // Preto
	{
		corL.setR(0.0);
		corL.setG(0.0);
		corL.setB(0.0);
		corL.setA(1.0);
		printf("Cor Selecionada de Linha: Preto");
	}
	else if (cod == TRANS) //transparnte
	{
		corL.setR(0.0);
		corL.setG(0.0);
		corL.setB(0.0);
		corL.setA(0.0);
		printf("Cor Selecionada de Linha: Transparente");
	}
	glutPostRedisplay();
}

// Tamanho do ponto Menu
void TamanhoPontoMenu (GLint tam)
{
	if (tam == 1.0) 
	{
		tamanho_ponto = 1.0;
		printf("Tamanho de Ponto Selecionado: 1.0");
	}
	else if (tam == 2.0) 
	{
		tamanho_ponto = 2.0;
		printf("Tamanho de Ponto Selecionado: 2.0");
	}
	else if (tam == 3.0) 
	{
		tamanho_ponto = 3.0;
		printf("Tamanho de Ponto Selecionado: 3.0");
	}
	else if (tam == 4.0) 
	{
		tamanho_ponto = 4.0;
		printf("Tamanho de Ponto Selecionado: 4.0");
	}
	else if (tam == 5.0) 
	{
		tamanho_ponto = 5.0;
		printf("Tamanho de Ponto Selecionado: 5.0");
	}
	else if (tam == 6.0) 
	{
		tamanho_ponto = 6.0;
		printf("Tamanho de Ponto Selecionado: 6.0");
	}
}

// Largura de linha Menu
void LarguraLinhaMenu(GLint l)
{
	if (l == 1.0) // 1.0
	{
		largura_linha = 1.0;
		printf("Largura de Linha Selecionado: 1.0");
	}
	else if (l == 2.0) 
	{
		largura_linha = 2.0;
		printf("Largura de Linha Selecionado: 2.0");
	}
	else if (l == 3.0) 
	{
		largura_linha = 3.0;
		printf("Largura de Linha Selecionado: 3.0");
	}
	else if (l == 4.0) 
	{
		largura_linha = 4.0;
		printf("Largura de Linha Selecionado: 4.0");
	}
	else if (l == 5.0) 
	{
		largura_linha = 5.0;
		printf("Largura de Linha Selecionado: 5.0");
	}
	else if (l == 6.0) 
	{
		largura_linha = 6.0;
		printf("Largura de Linha Selecionado: 6.0");
	}
	glutPostRedisplay();
}

// Mouse Right-Click Menu
void rightClickMenu(GLint op)
{
	switch (op)
	{
	case CLEAR:
		ApagaFiguras();
		break;

	case EXIT:
		exit(0);
	}
}

// Criar um menu no right-click mouse
void criarMouseMenu()
{
	GLint cor_f, cor_l, tp_menu, ll_menu, a_menu;  //cor_menu , tamanho da linha menu, largura da linha menu

	// Criar sub-menus para cores
	cor_l = glutCreateMenu(CorMenuL);
	glutAddMenuEntry("Vermelho", RED);
	glutAddMenuEntry("Verde", GREEN);
	glutAddMenuEntry("Azul", BLUE);
	glutAddMenuEntry("Cyan", CYAN);
	glutAddMenuEntry("Magenta", MAGENTA);
	glutAddMenuEntry("Amarelo", YELLOW);
	glutAddMenuEntry("Branco", WHITE);
	glutAddMenuEntry("Preto", BLACK);

	cor_f = glutCreateMenu(CorMenuF);
	glutAddMenuEntry("Vermelho", RED);
	glutAddMenuEntry("Verde", GREEN);
	glutAddMenuEntry("Azul", BLUE);
	glutAddMenuEntry("Cyan", CYAN);
	glutAddMenuEntry("Magenta", MAGENTA);
	glutAddMenuEntry("Amarelo", YELLOW);
	glutAddMenuEntry("Branco", WHITE);
	glutAddMenuEntry("Preto", BLACK);
	glutAddMenuEntry("Transparente", TRANS);

	// Criar sub-menus para tamanho do ponto
	tp_menu = glutCreateMenu(TamanhoPontoMenu);
	glutAddMenuEntry("1.0", 1.0);
	glutAddMenuEntry("2.0", 2.0);
	glutAddMenuEntry("3.0", 3.0);
	glutAddMenuEntry("4.0", 4.0);
	glutAddMenuEntry("5.0", 5.0);
	glutAddMenuEntry("6.0", 6.0);

	// Criar sub-menus para largura de linha 
	ll_menu = glutCreateMenu(LarguraLinhaMenu);
	glutAddMenuEntry("1.0", 1.0);
	glutAddMenuEntry("2.0", 2.0);
	glutAddMenuEntry("3.0", 3.0);
	glutAddMenuEntry("4.0", 4.0);
	glutAddMenuEntry("5.0", 5.0);
	glutAddMenuEntry("6.0", 6.0);
	// Criar menu principal
	glutCreateMenu(rightClickMenu);
	glutAddSubMenu("Cor de Fundo", cor_f);
	glutAddSubMenu("Cor da Linha", cor_l);
	glutAddSubMenu("Tamanho do Ponto", tp_menu);
	glutAddSubMenu("Largura de Linha", ll_menu);
	glutAddMenuEntry("Apagar (Clear)", CLEAR);
	glutAddMenuEntry("Sair do Paint", EXIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Selecionar o modo de desenho pelo rato
void SelecionarModo(GLint x, GLint y, GLint mod)
{
	if (y > altura - 50) 
	{	
		printf("Modo Selecionado: Ferramentas\n");
		printf("Figura Selecionada: Ponto\n");
		modo = PONTO;
		var = false;
	}
	else if (y > altura - 100) 
	{
		printf("Modo Selecionado: Ferramentas\n");
		printf("Figura Selecionada: Linha\n");
		modo = LINHA;
		var = false;
	}
	else if (y > altura - 150) 
	{
		printf("Modo Selecionado: Ferramentas\n");
		printf("Figura Selecionada: Triangulo \n");
		modo = TRIANGULO;
		var = false;
	}
	else if (y > altura - 200) 
	{
		printf("Modo Selecionado: Ferramentas\n");
		printf("Figura Selecionada: Rectangulo \n");
		modo = RETANGULO;
		var = false;
	}
	else if (y > altura - 250) 
	{
		printf("Modo Selecionado: Ferramentas\n");
		printf("Figura Selecionada: Circulo\n");
		modo = CIRCULO;
		var = false;
	}
	else if (y > altura - 300)
	{
		printf("Modo Selecionado: Ferramentas\n");
		printf("Figura Selecionada: Poligono\n");
		modo = POLIGONO;
		var = false;
	}
	else if (y > altura - 350)
	{
		var = true;
		modo = 0;
		printf("Modo de Figura Selecionada\n");
	}
}

// Desenhar o contorno em torno do modo selecionado
void DesenhaContorno()
{
	if(modo == 0){
		return;
	}
	if (modo == PONTO) 
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, altura - 2);
		glVertex2i(49, altura - 2);
		glVertex2i(49, altura - 49);
		glVertex2i(2, altura - 49);
		glEnd();
	}
	else if (modo == LINHA)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, altura - 51);
		glVertex2i(49, altura - 51);
		glVertex2i(49, altura - 99);
		glVertex2i(2, altura - 99);
		glEnd();
	}
	else if (modo == TRIANGULO) 
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, altura - 101);
		glVertex2i(49, altura - 101);
		glVertex2i(49, altura - 149);
		glVertex2i(2, altura - 149);
		glEnd();
	}
	else if (modo == RETANGULO) 
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, altura - 151);
		glVertex2i(49, altura - 151);
		glVertex2i(49, altura - 199);
		glVertex2i(2, altura - 199);
		glEnd();
	}
	else if (modo == CIRCULO) 
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, altura - 201);
		glVertex2i(49, altura - 201);
		glVertex2i(49, altura - 249);
		glVertex2i(2, altura - 249);
		glEnd();
	}
	else if (modo == POLIGONO)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(2, altura - 251);
		glVertex2i(49, altura - 251);
		glVertex2i(49, altura - 299);
		glVertex2i(2, altura - 299);
		glEnd();
	}
}

// Desenha ícones do menu lateral (todos com cor preta)
void DesenhaIconeMenu()
{
	// para ponto
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(25, altura - 25);
	glEnd();

	// para linha
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(10, altura - 90);
	glVertex2i(40, altura - 60);
	glEnd();

	// para triangulo 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(25, altura - 110);
	glVertex2i(10, altura - 135);
	glVertex2i(40, altura - 135);
	glEnd();

	// para retangulo
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(10, altura - 160);
	glVertex2i(10, altura - 185);
	glVertex2i(40, altura - 185);
	glVertex2i(40, altura - 160);
	glEnd();

	// para circulo 
	GLint aux1 = 210;
	GLfloat aux2 = PI * 2.0;
	GLfloat raio = 15.0;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i < aux1; i++)
	{
		glVertex2f(25 + (raio * cos(i *  aux2 / aux1)), (altura - 226) + (raio * sin(i * aux2 / aux1)));
	}

	glEnd();

	//poligono
	glBegin(GL_QUADS);
	glVertex2i(25, altura - 251);
	glVertex2i(49, altura - 275);
	glVertex2i(25, altura - 299);
	glVertex2i(1, altura - 275);
	glEnd();

	//escrever o texto no ícone para a opção de seleção
	char *texto1 = "MARCAR";
	Texto(texto1, 3, altura-331);

	//quadrado que mostra a cor da fundo selecionada
	glColor3f(corF.getR(), corF.getG(), corF.getB());
	glBegin(GL_QUADS);
	glVertex2i(2, altura - 351);
	glVertex2i(49, altura - 351);
	glVertex2i(49, altura - 399);
	glVertex2i(2, altura - 399);
	glEnd();

	//quadrado que mostra a cor da linha selecionada
	glColor3f(corL.getR(), corL.getG(), corL.getB());
	glBegin(GL_QUADS);
	glVertex2i(2, altura - 401);
	glVertex2i(49, altura - 401);
	glVertex2i(49, altura - 449);
	glVertex2i(2, altura - 449);
	glEnd();

	//escrever o texto de ajuda
	char *texto2 = "- Ajuda:";
	Texto(texto2, 51, altura - 559);
	char *texto3 = "-> Desenhar, Mover, Selecionar e Apagar Figura - BOTAO ESQUERDO DO RATO";
	Texto(texto3, 51, altura - 569);
	char *texto4 = "-> Alterar Cor de Fundo e Linha, Tamanho de Ponto, Largura de Linha e Sair - BOTAO DIREITO DO RATO";
	Texto(texto4, 51, altura - 579);
	char *texto5 = "-> Obs.: Necessario escolher uma cor antes de desenhar uma figura, no menu dinamico com o botao direito do rato";
	Texto(texto5, 51, altura - 589);
	char *texto6 = "-> Obs.: Necessario dar dois clicks no rato apos desenhar a figura, para que a mesma fique desenhada";
	Texto(texto6, 51, altura - 599);
	char *texto7 = "-> Opcao de Marcar no Menu - seleciona a(s) figura(s) para apagar ou mover";
	Texto(texto7, 51, altura - 609);
}

// desenhar menu principal
void DesenhaMenu()
{
	// para menu lateral
	glColor3f(0.0, 1.0, 1.0);   //barra lateral 
	glRectf(0, 0, 50, altura);
	glColor3f(0.0, 0.0, 0.0);    //barra das caixas
	glLineWidth(2.0);
	glBegin(GL_LINES);

	// para linha de fundo
	glVertex2i(1, 1);
	glVertex2i(50, 1);

	// para linha da esquerda
	glVertex2i(1, 1);
	glVertex2i(1, altura);

	// para linha da direita
	glVertex2i(50, 1);
	glVertex2i(50, altura);

	// para linha de cima
	glVertex2i(1, altura - 1);
	glVertex2i(50, altura - 1);

	GLint distancia = 50;

	// desenha 9 linhas para cada ícone
	for (int i = 1; i <= 9; i++)
	{
		if (i == 8) {
			glColor3f(1.0, 1.0, 1.0);    //mete uma linha branca entre as caixas que separam as cores de fundo
			glVertex2i(1, altura - distancia);
			glVertex2i(50, altura - distancia);
		}
		else { //mete uma linha preta na separação das outras caixas
			glColor3f(0.0, 0.0, 0.0); 
			glVertex2i(1, altura - distancia);
			glVertex2i(50, altura - distancia);
		}
		distancia = distancia + 50;
	}
	

	glEnd();
}

// Desenha Menu Interface
void DesenhaMenuInterface()
{
	// desenha menu principal
	DesenhaMenu();

	// desenha contorno
	DesenhaContorno();

	// desenha ícone menu
	DesenhaIconeMenu();

	glutPostRedisplay();
}


// Inicializar o menu e área de desenho 
void initArea(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(x1, x2, y1, y2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, largura, 0, altura);
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);	//cor de fundo da área de trabalho
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//para fazer a transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(50, 0, largura - 50, altura);

	initArea(0, 1, 0, 1);

	DesenhaFiguras();

	if (contador == 2) {
		PreviewFigura(inicio, aux1, modo, tamanho_ponto, largura_linha, corF, corL, nr, true); 
		//o aux1 foi colocado  no B por ser o último ponto a ser feito entre A e B
	}

	glViewport(0, 0, 50, altura);

	initArea(0, 51, 0, altura);

	DesenhaMenuInterface();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glClearColor(0.8, 0.8, 0.8, 0.8);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	glFlush();

	// definir novos valores de largura e altura da janela
	largura = w;
	altura = h;
}

void rato(int button, int state, int x, int y){
	float aux_x, aux_y;
	aux_x = (float)(x - Area) / (largura - Area);
	aux_y = (float)(altura - y) / altura;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x > Area && modo != 0 && var == false)
		{
			if (contador == 1) {//clicado 1 vez

				inicio = Ponto(aux_x, aux_y);
				aux1 = inicio;
				if (modo == PONTO) {
					CriaFigura(inicio, fim, modo, tamanho_ponto, largura_linha, corF, corL);

					//fim = Ponto(aux_x, aux_y);
					contador = 1;
				}
				else {//senao for ponto mete as coordenadas do inicio e incrementa o contador
					//inicio = Ponto(aux_x, aux_y);
					contador++;
				}
			}//se for clicado na segunda vez
			else if (contador == 2) {
				//faz as restantes figuras
				fim = Ponto(aux_x, aux_y);
				CriaFigura(inicio, fim, modo, tamanho_ponto, largura_linha, corF, corL);
				contador = 1;
			}
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x <= Area) {
			SelecionarModo(x, altura - y, glutGetModifiers());
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && var == true && x > Area) {
		Ponto aux = Ponto(aux_x, aux_y);
		SelecionaFigura(aux);
	}
	if (x > Area && !verificaListaFiguras2Vazia()) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
															  
			b = Ponto(aux_x, aux_y);
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			a = Ponto(aux_x, aux_y);
			moverFiguras(b, a);
		}
	}
}


//movimento
void motion(int x, int y)
{
	float aux_x, aux_y;

		aux_x = (float)(x - Area) / (largura - Area);
		aux_y = (float)(altura - y) / altura;
	if (x > Area) { //Area definida como define, por causa do tamanho das caixas que estão na barra lateral 

		aux1 = Ponto(aux_x, aux_y);
		printf("Posicao (%i,%i)\n", x, y);
	}
}

void keyboard(unsigned char op, int x, int y) {
	switch (op)
	{
	case 127:
		ApagaFigura();
		break;
	}
	printf("%i", op);
}

//função para glutPassiveMotionFunc
void move(int x, int y){
	if (x < Area) {
		printf("Modo de Ferramentas Ativo\n");
	}
	if (x > Area) {
		printf("Modo de Trabalho Ativo\n");
	}
	printf("Posicao (%i,%i)\n", x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 620); 
	glutInitWindowPosition(150, 50); 
	glutCreateWindow("Paint CG");
	init();

	criarMouseMenu();

	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(rato);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(move);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}