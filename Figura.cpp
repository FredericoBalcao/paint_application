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

#include "Figura.h"

lista<Figura> ListaFiguras1;
lista<Figura> ListaFiguras2;
Ponto A, B;

Figura::Figura()
{
}

Figura::Figura(Ponto _a, Ponto _b, int _tipo, GLfloat _tamanhoPonto, GLfloat _larguralinha, Cor _colour, Cor _colour1, int _nr)
{
	A = _a;
	B = _b;
	tipo = _tipo;
	tamanhoPonto = _tamanhoPonto;
	larguraLinha = _larguralinha;
	colour = _colour;
	colour1 = _colour1;
	selecionada = false;
	nr = _nr;
}

Figura::~Figura()
{
}

void CriaFigura(Ponto _a, Ponto _b, int _tipo, GLfloat _tamanhoPonto, GLfloat _larguralinha, Cor _colour, Cor _colour1){
	int o;
	if (!ListaFiguras1.listaVazia()) {
		iterador < Figura > *itLista = new iterador < Figura >;
		for (itLista->initIterador(ListaFiguras1),true; !itLista->Ultimo(); itLista->Next()) {
			o = ListaFiguras1.getTamanho() + 1;
		}
	}
	else {
		o = 1;
	}
	Figura *fig = new Figura(_a, _b, _tipo, _tamanhoPonto, _larguralinha, _colour, _colour1, o);

	ListaFiguras1.insere_fim(fig);
}

void PreviewFigura(Ponto _a, Ponto _b, int _tipo, GLfloat _tamanhoPonto, GLfloat _larguralinha, Cor _colour, Cor _colour1, int _nr, bool xorType)
{
	float xA, yA, xB, yB;
	xA = _a.getX();
	yA = _a.getY();
	xB = _b.getX();
	yB = _b.getY();

	if (xorType == true) glLogicOp(GL_XOR);

	if (_tipo == PONTO) {
		
		glPointSize(_tamanhoPonto);

		glColor3f(_colour.getR(), _colour.getG(), _colour.getB());
		glBegin(GL_POINTS);
		glVertex2f(xA, yA);
		glEnd();
		glPointSize(1.0);
	}
	else if (_tipo == LINHA) {
		glLineWidth(_larguralinha);
		glColor3f(_colour1.getR(), _colour1.getG(), _colour1.getB());
		glBegin(GL_LINE_LOOP);
		glVertex2f(xA, yA);
		glVertex2f(xB, yB);
		glEnd();
		glLineWidth(1.0);
	}
	else if (_tipo == RETANGULO) {
		glColor4f(_colour.getR(), _colour.getG(), _colour.getB(), _colour.getA());
		glBegin(GL_POLYGON);
		glVertex2f(xA, yA);
		glVertex2f(xA, yB);
		glVertex2f(xB, yB);
		glVertex2f(xB, yA);
		glEnd();

		glLineWidth(_larguralinha);
		glColor4f(_colour1.getR(), _colour1.getG(), _colour1.getB(), _colour1.getA());

		glBegin(GL_LINE_LOOP);
		glVertex2f(xA, yA);
		glVertex2f(xA, yB);
		glVertex2f(xB, yB);
		glVertex2f(xB, yA);
		glEnd();
	}
	else if (_tipo == TRIANGULO) {
		glBegin(GL_TRIANGLES);
		glVertex2f(xA, yA);
		glVertex2f(((xB - xA) / 2) + xA, yB);
		glVertex2f(xB, yA);
		glEnd();

		glColor4f(_colour1.getR(), _colour1.getG(), _colour1.getB(), _colour1.getA());

		glBegin(GL_LINE_LOOP);
		glVertex2f(xA, yA);
		glVertex2f(((xB - xA) / 2) + xA, yB);
		glVertex2f(xB, yA);
		glEnd();
	}
	else if (_tipo == CIRCULO) {
		glColor4f(_colour.getR(), _colour.getG(), _colour.getB(), _colour.getA());
		glBegin(GL_TRIANGLE_FAN);

		glLineWidth(_larguralinha);
		glBegin(GL_LINE_LOOP);

		// calcular meia largura e altura
		GLfloat meiaLargura = (xB - xA) / 2;
		GLfloat meiaAltura = (yB - yA) / 2;

		// calcular o centro do X e Y
		GLfloat centroX = xA + meiaLargura;
		GLfloat centroY = yA + meiaAltura;

		// desenhar circulo
		for (int j = 0; j < 360; j++)
		{
			GLfloat angulo = j * PI / 180.0;
			GLfloat x = centroX + (cos(angulo) * meiaLargura);
			GLfloat y = centroY + (sin(angulo) * meiaAltura);
			glVertex2f(x, y);
		}
		glEnd();
	}
	else if (_tipo == POLIGONO) {
		float aux_X = xA - (xB - xA);
		float aux_Y = yB + (yB - yA);

		glColor4f(_colour.getR(), _colour.getG(), _colour.getB(), _colour.getA());
		glBegin(GL_POLYGON);
		glVertex2f(xA, yA);
		glVertex2f(xB, yB);
		glVertex2f(xA, aux_Y);
		glVertex2f(aux_X, yB);
		glEnd();

		glLineWidth(_larguralinha);

		glColor4f(_colour1.getR(), _colour1.getG(), _colour1.getB(), _colour1.getA());

		glBegin(GL_LINE_LOOP);
		glVertex2f(xA, yA);
		glVertex2f(xB, yB);
		glVertex2f(xA, aux_Y);
		glVertex2f(aux_X, yB);
		glEnd();

		glLineWidth(1.0);
	}

	if (xorType == true) glLogicOp(GL_COPY);
}

// Desenha todas as figuras na área de desenho
void DesenhaFiguras()
{
	if (!ListaFiguras1.listaVazia()) {
		float xA, yA, xB, yB;
		iterador<Figura> *itLista = new iterador < Figura >; //cria iterador 

		for (itLista->initIterador(ListaFiguras1),true; !itLista->Ultimo(); itLista->Next())
		{

			xA = itLista->getObjecto().getA().getX();
			yA = itLista->getObjecto().getA().getY();
			xB = itLista->getObjecto().getB().getX();
			yB = itLista->getObjecto().getB().getY();

			// Configura a colour das figuras com base na colour selecionada
			glColor4f(itLista->getObjecto().getCor().getR(), itLista->getObjecto().getCor().getG(), itLista->getObjecto().getCor().getB(), itLista->getObjecto().getCor().getA());

			if (itLista->getObjecto().getTipo() == PONTO)
			{
				// desenha ponto
				glPointSize(itLista->getObjecto().getTamanhoPonto());
				glBegin(GL_POINTS);
				glVertex2f(xA, yA);
				glEnd();
			}
			if (itLista->getObjecto().getTipo() == LINHA)
			{
				// desenha linha
				glLineWidth(itLista->getObjecto().getLarguraLinha());
				glBegin(GL_LINES);
				glVertex2f(xA, yA);
				glVertex2f(xB, yB);
				glEnd();
			}

			if (itLista->getObjecto().getTipo() == TRIANGULO)
			{
				// desenha triangulo
				glBegin(GL_TRIANGLES);
				glVertex2f(xA, yA);
				glVertex2f(((xB - xA) / 2) + xA, yB);
				glVertex2f(xB, yA);
				glEnd();

				glColor4f(itLista->getObjecto().getCor1().getR(), itLista->getObjecto().getCor1().getG(), itLista->getObjecto().getCor1().getB(), itLista->getObjecto().getCor1().getA());

				glBegin(GL_LINE_LOOP);
				glVertex2f(xA, yA);
				glVertex2f(((xB - xA) / 2) + xA, yB);
				glVertex2f(xB, yA);
				glEnd();
			}
			if (itLista->getObjecto().getTipo() == RETANGULO)
			{
				glColor4f(itLista->getObjecto().getCor().getR(), itLista->getObjecto().getCor().getG(), itLista->getObjecto().getCor().getB(), itLista->getObjecto().getCor().getA());
				glBegin(GL_POLYGON);
				glVertex2f(xA, yA);
				glVertex2f(xA, yB);
				glVertex2f(xB, yB);
				glVertex2f(xB, yA);
				glEnd();

				glLineWidth(itLista->getObjecto().getLarguraLinha());
				glColor4f(itLista->getObjecto().getCor1().getR(), itLista->getObjecto().getCor1().getG(), itLista->getObjecto().getCor1().getB(), itLista->getObjecto().getCor1().getA());

				glBegin(GL_LINE_LOOP);
				glVertex2f(xA, yA);
				glVertex2f(xA, yB);
				glVertex2f(xB, yB);
				glVertex2f(xB, yA);
				glEnd();
				//Faz a linha tracejada para ser usada no modo de seleção
				if (itLista->getObjecto().getSelecionada() == true) {
					glColor4f(1.0,0.0,0.0,1.0);
					glEnable(GL_LINE_STIPPLE);
					glLineStipple(1, 0x00FF);
					
					glBegin(GL_LINE_LOOP);
					glVertex2f(xA, yA);
					glVertex2f(xA, yB);
					glVertex2f(xB, yB);
					glVertex2f(xB, yA);
					glEnd();
					glDisable(GL_LINE_STIPPLE);
				}
			}
			if (itLista->getObjecto().getTipo() == CIRCULO)
			{
				glColor4f(itLista->getObjecto().getCor().getR(), itLista->getObjecto().getCor().getG(), itLista->getObjecto().getCor().getB(), itLista->getObjecto().getCor().getA());
				glBegin(GL_TRIANGLE_FAN);

				glLineWidth(itLista->getObjecto().getLarguraLinha());
				glBegin(GL_LINE_LOOP);

				// calcular meia largura e altura
				GLfloat meiaLargura = (xB - xA) / 2;
				GLfloat meiaAltura = (yB - yA) / 2;

				// calcular o centro do X e Y
				GLfloat centroX = xA + meiaLargura;
				GLfloat centroY = yA + meiaAltura;

				// desenhar circulo
				for(int j = 0; j < 360; j++)
				{
					GLfloat angulo = j * PI / 180.0;
					GLfloat x = centroX + (cos(angulo) * meiaLargura);
					GLfloat y = centroY + (sin(angulo) * meiaAltura);
					glVertex2f(x, y);
				}
				glEnd();
			}
			if (itLista->getObjecto().getTipo() == POLIGONO)
			{
				float aux_X = xA - (xB - xA);
				float aux_Y = yB + (yB - yA);

				glColor4f(itLista->getObjecto().getCor().getR(), itLista->getObjecto().getCor().getG(), itLista->getObjecto().getCor().getB(), itLista->getObjecto().getCor().getA());
				glBegin(GL_POLYGON);
				glVertex2f(xA, yA);
				glVertex2f(xB, yB);
				glVertex2f(xA, aux_Y);
				glVertex2f(aux_X, yB);
				glEnd();

				glLineWidth(itLista->getObjecto().getLarguraLinha());

				glColor4f(itLista->getObjecto().getCor1().getR(), itLista->getObjecto().getCor1().getG(), itLista->getObjecto().getCor1().getB(), itLista->getObjecto().getCor1().getA());

				glBegin(GL_LINE_LOOP);
				glVertex2f(xA, yA);
				glVertex2f(xB, yB);
				glVertex2f(xA, aux_Y);
				glVertex2f(aux_X, yB);
				glEnd();

				glLineWidth(1.0);
			}

		}
	}

}

float CalculaDistancia(Ponto _a, Ponto _b) {
		float i;
		i = sqrt(pow(_a.getX() - _b.getX(), 2) + pow(_a.getY() - _b.getY(), 2));
		return i;
}

float CalculaArea(Ponto _a, Ponto _b, Ponto _c)
{
	return abs((_a.getX()*(_b.getY() - _c.getY()) + _b.getX()*(_c.getY() - _a.getY()) + _c.getX()*(_a.getY() -_b.getY())) / 2.0);
}

/*
float CalculaArea(Ponto p1, Ponto p2, Ponto p3)
{
	return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) - (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
}
*/

/*bool VerificaDentroTriangulo(Ponto pt, Ponto v1, Ponto v2, Ponto v3)
{
	bool b1, b2, b3;

	b1 = CalculaArea(pt, v1, v2) < 0.0f;
	b2 = CalculaArea(pt, v2, v3) < 0.0f;
	b3 = CalculaArea(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}
*/

//verifica se está dentro do triangulo para ser usada no ApagaFigura()
bool VerificaDentroTriangulo(Ponto _a, Ponto _b, Ponto _c, Ponto _p) //Pontos _a, _b e _c para cálculo com o ponto _p que é o ponto clicado pelo rato 
{
		//calcula a área do triangulo _a_b_c
		float area0 = CalculaArea(_a, _b, _c);

		//calcula a área do triangulo _p_b_c
		float area1 = CalculaArea(_p, _b, _c);

		//calcula a área do triangulo _p_a_c
		float area2 = CalculaArea(_a, _p, _c);

		//calcula a área do triangulo _p_a_b
		float area3 = CalculaArea(_a, _b, _p);

		//verifica se a soma da area1, area2 e area3 é igual à area0
		return (area0 == area1 + area2 + area3);
}


float maximo(float a, float b) { return a>b ? a : b; }
float minimo(float a, float b) { return a>b ? b : a; }

float vericaDentroQuadrado(Ponto A, Ponto B, Ponto P)
{
	return (P.getX() >= minimo(A.getX(), B.getX()) &&
		P.getX() <= maximo(A.getX(), B.getX()) &&
		P.getY() >= minimo(A.getY(), B.getY()) &&
		P.getY() <= maximo(A.getY(), B.getY()));
}

void SelecionaFigura(Ponto A) {
	float aux_X, aux_Y;
	aux_X = A.getX();
	aux_Y = A.getY();
	float distancia, aux = 9999999; //valor máximo a ser atingido

	iterador<Figura> *itLista = new iterador < Figura >;
	/* Verifica qual o elemento mais proximo*/
	for (itLista->initIterador(ListaFiguras1); !itLista->Ultimo(); itLista->Next()) {
		if (itLista->getObjecto().getTipo() == RETANGULO) {

			if (vericaDentroQuadrado(itLista->getObjecto().getA(), itLista->getObjecto().getB(), A)) {

				//distancia = sqrt(pow(itLista->getObjecto().getB().getX() - aux_X, 2) + pow(itLista->getObjecto().getB().getY() - aux_Y, 2));
				//if (aux > distancia) {
					//aux = distancia;
				if (itLista->getObjecto().getSelecionada() == false) {
					itLista->getObjecto().setSelecionada(true);
					ListaFiguras2.insere_fim(itLista->getPonteiroObjecto());
				}
				else if (itLista->getObjecto().getSelecionada() == true) {
					itLista->getObjecto().setSelecionada(false);
				}
			
				break;
				//}
			}
		}
		else if (itLista->getObjecto().getTipo() == TRIANGULO) {
			Ponto C = Ponto(aux_X, aux_Y);
			float x = itLista->getObjecto().getA().getX() - (itLista->getObjecto().getB().getX() - itLista->getObjecto().getA().getX());
			float y = itLista->getObjecto().getB().getY();

			if (VerificaDentroTriangulo(itLista->getObjecto().getA(), itLista->getObjecto().getB(), C, A)) {
				//distancia = sqrt(pow(itLista->getObjecto().getB().getX() - aux_X, 2) + pow(itLista->getObjecto().getB().getY() - aux_Y, 2));
				//if (aux > distancia) {
					//aux = distancia;
				if (itLista->getObjecto().getSelecionada() == false) {
					itLista->getObjecto().setSelecionada(true);
					ListaFiguras2.insere_fim(itLista->getPonteiroObjecto());
				}
				else if (itLista->getObjecto().getSelecionada() == true) {
					itLista->getObjecto().setSelecionada(false);
				}
			
				break;
			    //}
			}
		}
		else if (itLista->getObjecto().getTipo() == POLIGONO) {

			float x = itLista->getObjecto().getA().getX() - (itLista->getObjecto().getB().getX() - itLista->getObjecto().getA().getX());
			float y = itLista->getObjecto().getB().getY() + (itLista->getObjecto().getB().getY() - itLista->getObjecto().getA().getY());

			Ponto C0 = Ponto(x, itLista->getObjecto().getB().getY());
			Ponto C1 = Ponto(itLista->getObjecto().getA().getX(), y);
			if (VerificaDentroTriangulo(itLista->getObjecto().getA(), C0, itLista->getObjecto().getB(), A) || VerificaDentroTriangulo(itLista->getObjecto().getB(), C0, C1, A)) {

				//distancia = sqrt(pow(itLista->getObjecto().getB().getX() - aux_X, 2) + pow(itLista->getObjecto().getB().getY() - aux_Y, 2));
				//if (aux > distancia) {
					//aux = distancia;
				if (itLista->getObjecto().getSelecionada() == false) {
					itLista->getObjecto().setSelecionada(true);
					ListaFiguras2.insere_fim(itLista->getPonteiroObjecto());
				}
				else if (itLista->getObjecto().getSelecionada() == true) {
					itLista->getObjecto().setSelecionada(false);
				}
				break;
			  //}
			}
		}
		else if (itLista->getObjecto().getTipo() == CIRCULO) {

			float dx = abs(aux_X - itLista->getObjecto().getA().getX());
			float dy = abs(aux_Y - itLista->getObjecto().getA().getY());
			float R = (itLista->getObjecto().getB().getX() - itLista->getObjecto().getA().getX());


			if (((dx < R) && (dy < R)) && dx + dy <= R) {

				//distancia = sqrt(pow(itLista->getObjecto().getB().getX() - aux_X, 2) + pow(itLista->getObjecto().getB().getY() - aux_Y, 2));
				//if (aux > distancia) {
					//aux = distancia;
				if (itLista->getObjecto().getSelecionada() == false) {
					itLista->getObjecto().setSelecionada(true);
					ListaFiguras2.insere_fim(itLista->getPonteiroObjecto());
				}
				else if (itLista->getObjecto().getSelecionada() == true) {
					itLista->getObjecto().setSelecionada(false);
				
				}
			break;
			}
		}

		else if (itLista->getObjecto().getTipo() == LINHA) {
			float dis = CalculaDistancia(A, itLista->getObjecto().getB()) + CalculaDistancia(A, itLista->getObjecto().getA());
			if (dis <= CalculaDistancia(itLista->getObjecto().getA(), itLista->getObjecto().getB()) + 1) {

				//distancia = CalculaDistancia(A, itLista->getObjecto().getB());
				//if (aux > distancia) {
					//aux = distancia;
				if (itLista->getObjecto().getSelecionada() == false) {
					itLista->getObjecto().setSelecionada(true);
					ListaFiguras2.insere_fim(itLista->getPonteiroObjecto());
				}
				else if (itLista->getObjecto().getSelecionada() == true) {
					itLista->getObjecto().setSelecionada(false);
				
				}
			
				break;
			}
		}
		else if (itLista->getObjecto().getTipo() == PONTO) {

			float dx = abs(aux_X - itLista->getObjecto().getA().getX());
			float dy = abs(aux_Y - itLista->getObjecto().getA().getY());
			float R = (10 - itLista->getObjecto().getA().getX());


			if (((dx < R) && (dy < R)) && dx + dy <= R) {
				//distancia = sqrt(pow(itLista->getObjecto().getB().getX() - aux_X, 2) + pow(itLista->getObjecto().getB().getY() - aux_Y, 2));
				//if (aux > distancia) {
					//aux = distancia;
				//}
				if (itLista->getObjecto().getSelecionada() == false) {
					itLista->getObjecto().setSelecionada(true);
					ListaFiguras2.insere_fim(itLista->getPonteiroObjecto());
				}
				else if (itLista->getObjecto().getSelecionada() == true) {
					itLista->getObjecto().setSelecionada(false);
				
				}
				break;
			}
		}
	}
	printf("Figura Selecionada\n");
}

void ApagaFigura() {
	if (!ListaFiguras2.listaVazia()) {
		iterador<Figura> *itLista1 = new iterador < Figura >;
		iterador<Figura> *itLista2 = new iterador < Figura >;
		for (itLista1->initIterador((ListaFiguras2), true); !itLista1->Ultimo(); itLista1->initIterador(ListaFiguras2)) {
			if (!ListaFiguras1.listaVazia()) {
				int i = 0;
				for (itLista2->initIterador((ListaFiguras1), true); !itLista2->Ultimo(); itLista2->Next()) {

					if (itLista1->getObjecto().getNr() == itLista2->getObjecto().getNr()) {
						ListaFiguras1.apaga_posicao(i);
						ListaFiguras2.apaga_fim();
						break;
					}
					i++;
				}
			}
			if (ListaFiguras1.listaVazia()) {
				break;
			}
		}
	}
	printf("Figura Apagada!\n");
}

void ApagaFiguras(){
	iterador<Figura> *itLista = new iterador < Figura >;

	for (itLista->initIterador(ListaFiguras1, true); !itLista->Ultimo(); itLista->initIterador(ListaFiguras1, true)) {

		ListaFiguras1.apaga_fim();
	}
	for (itLista->initIterador(ListaFiguras2, true); !itLista->Ultimo(); itLista->initIterador(ListaFiguras2, true)) {

		ListaFiguras2.apaga_fim();
	}
}


bool verificaListaFiguras2Vazia() {
	return (ListaFiguras2.listaVazia());
	printf("Lista Vazia!\n");
}

void moverFiguras(Ponto a, Ponto b) {
	iterador<Figura> *itLista1 = new iterador < Figura >;
	iterador<Figura> *itLista2 = new iterador < Figura >;
	if (!ListaFiguras2.listaVazia()) {
		float dis_x1, dis_x2, dis_x3, dis_y1, dis_y2, dis_y3;
		Ponto _A, _B;

		for (itLista1->initIterador((ListaFiguras2), true); !itLista1->Ultimo(); itLista1->Next()) {
			if (!ListaFiguras1.listaVazia()) {
				for (itLista2->initIterador((ListaFiguras1), true); !itLista2->Ultimo(); itLista2->Next()) {
					if (itLista1->getObjecto().getNr() == itLista1->getObjecto().getNr()) {

						dis_x1 = itLista1->getObjecto().getA().getX() + (b.getX() - a.getX());
						dis_x2 = itLista1->getObjecto().getB().getX() + (b.getX() - a.getX());
					

						dis_y1 = itLista1->getObjecto().getA().getY() + (b.getY() - a.getY());
						dis_y2 = itLista1->getObjecto().getB().getY() + (b.getY() - a.getY());
						
						_A = Ponto(dis_x1, dis_y1);
						_B = Ponto(dis_x2, dis_y2);
						
						itLista2->getObjecto().setA(_A);
						itLista2->getObjecto().setB(_B);
						
						itLista2->getObjecto().setSelecionada(false);
					}
				}
			}
			else {
				break;
			}
		}
	}
	for (itLista1->initIterador((ListaFiguras2), true); !itLista1->Ultimo(); itLista1->initIterador(ListaFiguras2)) {

		ListaFiguras2.apaga_fim();
	}

}

void Texto(char *string, float x, float y)
{
	glColor3f(0.0, 0.0, 0.0);
	char *c;
	glRasterPos3f(x, y, 0);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void Figura::setTipo(int _tipo)
{
	tipo = _tipo;
}

void Figura::setTamanhoPonto(float _tamanho)
{
	tamanhoPonto = _tamanho;
}

void Figura::setLarguraLinha(float _largura)
{
	larguraLinha = _largura;
}

int Figura::getTipo()
{
	return tipo;
}

void Figura::setA(Ponto _a)
{
	A = _a;
}

void Figura::setB(Ponto _b)
{
	B = _b;
}

Ponto Figura::getA()
{
	return A;
}

Ponto Figura::getB()
{
	return B;
}

void Figura::setNr(int i)
{
	nr = i;
}

int Figura::getNr()
{
	return nr;
}

GLfloat Figura::getTamanhoPonto()
{
	return tamanhoPonto;
}

GLfloat Figura::getLarguraLinha()
{
	return larguraLinha;
}

void Figura::setSelecionada(bool _s)
{
	selecionada = _s;
}

bool Figura::getSelecionada()
{
	return selecionada;
}

Cor Figura::getCor()
{
	return colour;
}

Cor Figura::getCor1()
{
	return colour1;
}