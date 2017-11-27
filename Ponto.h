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

