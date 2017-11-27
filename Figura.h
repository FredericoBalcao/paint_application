/*
---------------------------------------------------------------------------------------------
Nome: Frederico Balcão
Data: 26-10-2016
Curso: Engenharia Informática
U.C: Computação Gráfica
Ano/Semestre: 2ºAno/1ºSemestre
Paint - OpenGL
---------------------------------------------------------------------------------------------
*/

#pragma once
#ifndef FIGURA_h
#define FIGURA_h
#include <iostream>
#include <GL/glut.h>
#include "Lista.h"
#include "Cor.h"
#include "Ponto.h"
#define PONTO 1
#define LINHA 2
#define TRIANGULO 3
#define RETANGULO 4
#define CIRCULO 5
#define POLIGONO 6

using namespace std;

//Classe para a Figura Geométrica
class Figura 
{
public:
	Figura();
	Figura(Ponto _a, Ponto _b, int _tipo, GLfloat _tamanhoPonto, GLfloat _larguralinha, Cor _cor, Cor _cor1, int _nr);
	virtual ~Figura();
	void setTipo(int _tipo);
	void setTamanhoPonto(float _tamanho);
	void setLarguraLinha(float _largura);
	int getTipo();
	void setA(Ponto _a);
	void setB(Ponto _b);
	Ponto getA();
	Ponto getB();
	void setNr(int i);
	int getNr();
	GLfloat getTamanhoPonto();
	GLfloat getLarguraLinha();
	void setSelecionada(bool _s);
	bool getSelecionada();
	Cor getCor();
	Cor getCor1();
protected:
	bool selecionada = false;
	int tipo;
	int nr;
	Ponto A, B;
	GLfloat tamanhoPonto;
	GLfloat larguraLinha;
	Cor colour, colour1;
};

void CriaFigura(Ponto _a, Ponto _b, int _tipo, GLfloat _tamanhoPonto, GLfloat _larguralinha, Cor _cor, Cor _cor1);
void PreviewFigura(Ponto _a, Ponto _b, int _tipo, GLfloat _tamanhoPonto, GLfloat _larguralinha, Cor _cor, Cor _cor1, int _nr, bool xorType);
void DesenhaFiguras();
void ApagaFigura();
void ApagaFiguras();
void SelecionaFigura(Ponto A);
void moverFiguras(Ponto a, Ponto b);

//funções auxiliares
float CalculaDistancia(Ponto _a, Ponto _b);
float CalculaArea(Ponto _a, Ponto _b, Ponto _c);
bool VerificaDentroTriangulo(Ponto _a, Ponto _b, Ponto _c, Ponto _p);
float vericaDentroQuadrado(Ponto A, Ponto B, Ponto P);
bool verificaListaFiguras2Vazia();
float maximo(float a, float b);
float minimo(float a, float b);
void Texto(char *string, float x, float y);

// Right-click menu 
enum RIGHT_CLICK_MENU
{
	CLEAR, EXIT
};
//para o uso do PI
const GLfloat PI = 3.142;
#endif