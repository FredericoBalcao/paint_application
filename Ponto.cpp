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

#include "Ponto.h"

Ponto::Ponto()
{
}

Ponto::Ponto(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Ponto::setX(float _x)
{
	x = _x;
}

float Ponto::getX()
{
	return x;
}

void Ponto::setY(float _y)
{
	y = _y;
}

float Ponto::getY()
{
	return y;
}

Ponto::~Ponto()
{
}
