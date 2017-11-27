/*
---------------------------------------------------------------------------------------------
Nome: Frederico Balc�o
Data: 26-10-2016
Curso: Engenharia Inform�tica
U.C: Computa��o Gr�fica
Ano/Semestre: 2�Ano/1�Semestre
Paint - OpenGL
---------------------------------------------------------------------------------------------
*/

#pragma once
#ifndef COR_h
#define COR_h
#include <iostream>
#include <GL/glut.h>
#include "Lista.h"

using namespace std;

//COR
class Cor
{
public:
	Cor();
	virtual ~Cor();
	void setR(float _r);
	void setG(float _g);
	void setB(float _b);
	void setA(float _a);
	float getR();
	float getG();
	float getB();
	float getA();
protected:
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
	float a = 0.0; //alpha
};


#endif