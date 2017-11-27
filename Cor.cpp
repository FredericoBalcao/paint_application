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

#include "Cor.h"

Cor::Cor()
{
}

Cor::~Cor()
{
}

void Cor::setR(float _r)
{
	r = _r;
}

void Cor::setG(float _g)
{
	g = _g;
}

void Cor::setB(float _b)
{
	b = _b;
}

void Cor::setA(float _a)
{
	a = _a;
}

float Cor::getR()
{
	return r;
}

float Cor::getG()
{
	return g;
}

float Cor::getB()
{
	return b;
}

float Cor::getA()
{
	return a;
}
