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
class Ponto
{
public:
	Ponto();
	Ponto(float _x, float _y);
	void setX(float _x);
	float getX();
	void setY(float _y);
	float getY();
	~Ponto();
protected:
	float x, y;
};

