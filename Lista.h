/*
---------------------------------------------------------------------------------------------
Nome: Frederico Balc„o
Data: 26-10-2016
Curso: Engenharia Inform·tica
U.C: ComputaÁ„o Gr·fica
Ano/Semestre: 2∫Ano/1∫Semestre
Paint - OpenGL
---------------------------------------------------------------------------------------------
*/

#ifndef ListaPOO_lista_h
#define ListaPOO_lista_h

#include <iostream>

using namespace std;

template <class Item>
class lista;

// Class NO
template <class Item>
class no
{
	friend class lista<Item>;
private:
protected:
	Item * _item;                   //ponteiro para um item
	no<Item> * _proximo;            //ponteiro para o proximo no da lista
	no<Item> * _anterior;           //ponteiro para o no anterior da lista

public:
	no();                           //constructor default
	no(const no<Item>&);            //constructor com um ponteiro para no como argumento
	no(Item&);                      //constructor com um ponteiro para item como argumento
	~no() {};                        //destructor

	Item* getPonteiroItem() { return _item; };                 //get a um ponteiro para um item
	no<Item>* getPonteiroProximo() { return _proximo; };       //get a um ponteiro para o proximo no
	no<Item>* getPonteiroAnterior() { return _anterior; };     //get a um ponteiro para o no anterior

};


/*************************************************/
/* Constructor default para a classe no.         */
/* N„o recebe argumentos.                        */
/* Coloca os ponteiros para proximo e anterior a */
/* apontar para NULL.                            */
/*************************************************/
template <class Item>
no<Item>::no()
{
	_proximo = NULL;                                //iguala o ponteiro _proximo para o proximo no a NULL
	_anterior = NULL;                               //iguala o ponteiro _anterior para o no anterior a NULL
}


/*************************************************/
/* Constructor para a classe no.                 */
/* Recebe como argumento um no.                  */
/* Coloca o ponteiro _item a apontar para no->   */
/* item e os ponteiros para proximo e anterior a */
/* a apontar para no->proximo e no->anterior,    */
/* respectivamente.                              */
/*************************************************/
template <class Item>
no<Item>::no(const no<Item>& no)
{
	_item = no->item;                                //aponta _item para o ponteiro no->item
	_proximo = no->_proximo;                         //aponta o ponteiro _proximo a no>_proximo
	_anterior = no->_anterior;                       //aponta o ponteiro _anterior a no->_anterior
}


/*************************************************/
/* Constructor para a classe no.                 */
/* Recebe como argumento um item.                */
/* Coloca o ponteiro _item a apontar para o      */
/* endereco de item, e os ponteiros para proximo */
/* e anterior a apontar para NULL                */
/*************************************************/
template <class Item>
no<Item>::no(Item& item)
{
	_item = &item;                                 //aponta o ponteiro _item para o endereÁo do item recebido
	_proximo = 0;                                  //iguala o ponteiro _proximo para o proximo no a NULL
	_anterior = 0;                                 //iguala o ponteiro _anterior para o no anterior a NULL
}


// LISTA
template <class Item>
class lista
{
protected:
	no<Item>* _inicio;              //ponteiro para o no inicial da lista
	no<Item>* _fim;                 //ponteiro para o no final da lista
	int _tamanho;                   //numero de nos na lista

public:
	lista();                        //constructor default
	~lista();                       //destructor

	void cria_lista(Item&);         //cria uma lista com um elemento indicado por argumento

	void insere_inicio(Item&);      //insere um novo item no inicio da lista
	void insere_posicao(Item&, int);//insere um item na posicao indicada
	void insere_fim(Item*);         //insere um novo item no fim da lista

	void apaga_inicio();            //remove o item no inicio da lista
	Item* apaga_posicao(int);       //remove o item na posicao indicada
	void apaga_fim();               //remove o item no fim da lista

	void apaga_objecto(Item item);  //apaga o item indicado
	Item& getInicio();              //get ao ponteiro para o item no incio da lista
	Item& getPosicao(int);          //get ao ponteiro para o item na posicao indicada
	Item& getFim();                 //get ao ponteiro para o item no fim da lista

	int getTamanho();               //get ao inteiro _tamanho
	bool listaVazia();              //indica se a lista se encontra vazia ou nao

	no<Item>* getPonteiroInicio() { return _inicio; }; //get ao ponteiro para o no inicial
	no<Item>* getPointeiroFim() { return _fim; };      //get ao ponteiro para o no final

	void print(ostream& os) const;  //print a lista

};


template <class Item>
ostream& operator<<(ostream& os, const lista<Item>&); //?


													  /*************************************************/
													  /* Funcao que apaga o item indicado.             */
													  /* Recebe como argumento o item a apagar         */
													  /* Percorre a lista e apaga o item se o encontar */
													  /*************************************************/
template <class Item>
void lista<Item>::apaga_objecto(Item item)
{
	no<Item> *aux = _inicio;                            //cria um no auxiliar a apontar para o no inicio
	int a = 0;                                          //cria uma vari·vel int a igual a 0

	if (aux == 0)                                       //se o no auxiliar for igual a 0 sai do metodo
		return;
	if (aux->_proximo == 0)                             //se o ponteiro proximo do no auxiliar for igual a 0 apaga o no auxiliar e iguala o no inicio a 0
	{
		delete aux;
		_inicio = 0;
	}
	else
	{
		no<Item> *anterior = 0;                         //se o ponteiro proximo do no auxiliar nao for igual a 0 cria um no anterior igual a 0

		do
		{
			if (aux->_item == &item)                    //se o item do no auxiliar for igual ao endereÁo do item iguala a vari·vel a a 1 e faz break ao ciclo
			{
				a = 1;
				break;
			}
			anterior = aux;                             //aponta o no anterior ao no auxiliar
			aux = aux->_proximo;                        //aponta o no auxiliar ao proximo no
		} while (aux != 0);                             //enquanto o no auxiliar for diferente de 0 faz o ciclo

		if (a != 1)                                     //se a vari·vel for diferente de 1 faz return
		{
			return;
		}
		if (anterior != 0)                              //se o no anterior for diferente de 0 aponta o ponteiro _proximo do no ao ponteiro _proximo do no auxiliar
		{
			anterior->_proximo = aux->_proximo;
		}
		else
		{
			if (anterior == 0)                          //se o no anterior for igual a 0 aponta o ponteiro _inicio ao ponteiro _proximo do no inicio|
			{
				_inicio = _inicio->_proximo;
			}
			delete aux;                                 //apaga o no auxiliar
		}
	}
}

/*************************************************/
/* Constructor default para a classe lista.      */
/* N„o recebe argumentos.                        */
/* Coloca os ponteiros _inicio e _fim a NULL e o */
/* inteiro _tamanho a zero                       */
/*************************************************/
template <class Item>
lista<Item>::lista()
{
	_inicio = 0;                                        //aponta o ponteiro inicio a 0
	_fim = 0;                                           //aponta o ponteiro fim a 0
	_tamanho = 0;                                       //iguala o tamanho a 0
}


/***************************************************/
/* Constructor para a classe lista.                */
/* Recebe um item como argumento.                  */
/* Aloca memoria para o novo no, coloca o ponteiro */
/* a apontar para o item indicado e os ponteiros   */
/* para proximo e para o anterior para NULL        */
/***************************************************/
template <class Item>
void lista<Item>::cria_lista(Item& item)
{
	_inicio = new no<Item>;                             //cria um novo no e aponta o _inicio da lista a esse no
	_inicio->_item = &item;                             //aponta o item do inciio ao endereÁo do item recebido
	_inicio->_proximo = 0;                              //iguala o ponteiro _proximo do inicio a 0
	_inicio->_anterior = 0;                             //iguala o ponteiro _anterior do inicio a 0

	_fim = _inicio;                                     //iguala o fim da lista ao inicio
}


/***************************************************/
/* Destructor para a classe lista.                 */
/* Nao recebe argumentos.                          */
/* Liberta a memoria alocada a lista               */
/***************************************************/
template <class Item>
lista<Item>::~lista()
{
	if (_inicio != 0)                                   //se o _inicio da lista for diferente de 0 cria um no auxiliar a apontar para o ponteiro proximo do inicio
	{
		no<Item> *aux = _inicio->_proximo;
		while (aux != 0)                                //enquanto o no auxiliar for diferente de 0 apaga o anterior e iguala ao proximo
		{
			delete aux->_anterior;
			aux = aux->_proximo;
		}
		delete _fim;                                    //apaga o fim da lista
	}
}


/***************************************************/
/* Insere um item no incio da fila.                */
/* Recebe um item como argumento.                  */
/* Aloca memoria para o novo no. Coloca o ponteiro */
/* _item a apontar para o endereco do item indicado*/
/* e reajusta os ponteiros para proximo e anterior */
/* dos nos afectados                               */
/***************************************************/
template <class Item>
void lista<Item>::insere_inicio(Item& item)
{
	no<Item>* aux = 0;                                  //cria um no auxiliar e iguala a 0

	if (_inicio == 0)                                   //se inicio for igual a 0 cria um novo no e iguala o no auxiliar a esse no
	{
		aux = new no<Item>;
		aux->_item = &item;                             //aponta o item do no auxiliar ao endereÁo do item recebido
		aux->_proximo = 0;                              //aponta o ponteiro proximo para 0 do no auxiliar
		aux->_anterior = 0;                              //aponta o ponteiro anterior do no auxiliar para 0
		_inicio = 0;                                    //iguala o inicio a 0
		_fim = 0;                                       //iguala o fim a 0
	}
	else
	{
		aux = new no<Item>;                             //se o inicio for diferente de 0 cria um novo no e iguala o auxiliar a esse no
		aux->_item = &item;                             //aponta o item do no auxiliar ao endereÁo do item recebido
		aux->_proximo = _inicio;                        //aponta o ponteiro proximo do no auxiliar ao inicio
		_inicio->_anterior = aux;                       //aponta o ponteiro anterior do inicio ao no auxiliar
		_inicio = aux;                                  //iguala o inicio ao no auxiliar
	}

	_tamanho++;                                         //incrementa o tamanho

}


/***************************************************/
/* Insere um item no fim da fila.                  */
/* Recebe um item como argumento.                  */
/* Aloca memoria para o novo no. Coloca o ponteiro */
/* _item a apontar para o endereco do item indicado*/
/* e reajusta os ponteiros para proximo e anterior */
/* dos nos afectados                               */
/***************************************************/
template <class Item>
void lista<Item>::insere_fim(Item *item)
{
	no<Item>* aux;                                      //cria um no auxiliar

	if (_inicio == 0)                                   //se o inicio for igual a 0 cria um novo no e iguala o no auxiliar a esse no
	{
		aux = new no<Item>;
		aux->_item = item;                             //aponta o ponteiro do no auxiliar ao endereÁo do item recebido
		aux->_proximo = 0;                              //aponta o ponteiro proximo para 0 do no auxiliar
		aux->_anterior = 0;                             //aponta o ponteiro anterior do no auxiliar para 0
		_inicio = aux;                                  //iguala o inicio ao no auxiliar
		_fim = aux;                                     //iguala o fim ao no auxiliar
	}
	else                                                //se o inicio for diferente de 0 cria um novo no e iguala o no auxiliar a esse no
	{
		aux = new no<Item>;
		aux->_item = item;                             //aponta o ponteiro do no auxiliar ao endereÁo do item recebido
		aux->_proximo = 0;                              //aponta o ponteiro proximo para 0 do no auxiliar
		aux->_anterior = _fim;                          //aponta o ponteiro anterior do no auxiliar para o fim
		_fim->_proximo = aux;                           //aponta o ponteiro proximo do fim para o no auxiliar
		_fim = aux;                                     //iguala o fim ao no auxiliar
	}

	_tamanho++;                                         //incrementa o tamanho
}

/***************************************************/
/* Indica se a liste estÅEvazia.                   */
/* Retorna 1 se assim for.                         */
/***************************************************/
template <class Item>
bool lista<Item>::listaVazia()
{
	return(_inicio == 0);                               //ve se o inicio da lista ÅEigual a 0
}


/****************************************************/
/* Insere um item na posicao indicada.              */
/* Recebe um item e um inteiro como argumento.      */
/* Percorre a lista ate encontrar a posicao indicada*/
/* Aloca memoria para o novo no. Coloca o ponteiro  */
/* _item a apontar para o endereco do item indicado */
/* e reajusta os ponteiros para proximo e anterior  */
/* dos nos afectados                                */
/****************************************************/
template <class Item>
void lista<Item>::insere_posicao(Item& item, int posicao)
{
	no<Item>* aux;                                    //cria um no auxiliar
	no<Item>* novo;                                   //cria um no novo
	int i = 0;                                        //cria uma vari·vel int i e iguala a 0

	novo = new no<Item>;
	novo->_item = &item;                              //aponta o ponteiro item do no novo para o endereÁo do item recebido
	novo->_proximo = 0;                               //aponta o ponteiro proximo do no novo para 0
	novo->anterior = 0;                               //aponta o ponteiro anterior do no novo para 0

	aux = new no<Item>;
	aux = _inicio;                                    //aponta o no auxiliar para o inicio
	if (posicao >= 0 && posicao <= _tamanho)          //ve se a posiÁao recebida estÅEentre 0 e o tamanho da lista
	{
		while (i != posicao && aux->_proximo != 0)    //enquanto i for diferente da posiÁao e o ponteiro proximo do no auxiliar for diferente de 0
		{
			aux = aux->_proximo;                      //iguala o no auxiliar ao proximo
			i++;                                      //incrementa| a variavel i
		}

		if (posicao == 0)                             //se a posiÁao recebida for igual a 0 aponta o ponteiro proximo do no novo a 0
		{
			novo->_proximo = 0;
			aux->anterior = novo;                       // aponta o ponteiro anterior do no auxiliar ao no novo
			novo->_anterior = 0;                        //aponta o ponteiro anterior do no novo a 0
			_inicio = 0;                                //iguala o inicio a 0
			_tamanho++;                                 //incrementa o tamanho
		}
		else
		{
			if (posicao == _tamanho)                    //se a posiÁao for igual ao tamanho aponta o ponteiro proximo do no novo a 0
			{
				novo->_proximo = 0;
				novo->_anterior = aux;                  //aponta o ponteiro anterior do no novo ao no auxiliar
				aux->_proximo = novo;                   // aponta o ponteiro proximo do no auxiliar ao no novo
				_fim = novo;                            //iguala o fim ao no novo
			}
			else
			{
				novo->_anterior = aux->_anterior;       //se a posiÁao n„o for igual ao tamanho aponta o ponteiro anterior do no novo ao anterior do no auxiliar
				aux->_anterior->_proximo = novo;        //aponta o ponteiro anterior e proximo do no auxiliar ao no novo
				novo->_proximo = aux;                   //aponta o ponteiro proximo do no novo ao no auxiliar
				aux->_anterior = novo;                  //aponta o ponteiro anterior do no auxiliar ao no novo
				_tamanho++;                             //incrementa o tamanho
			}
		}
	}
}


/***************************************************/
/* Retorna o numero de items actualmente na lista. */
/***************************************************/
template <class Item>
int lista<Item>::getTamanho()
{
	return _tamanho;                                    //devolve o valor do tamanho da lista
}


/****************************************************/
/* Apaga um item no inicio da lista.                */
/* Nao recebe argumentos.                           */
/* Coloca o ponteiro inicio a apontar para o proximo*/
/* e liberta a memoria alocada ao no a ser apagado  */
/****************************************************/
template <class Item>
void lista<Item>::apaga_inicio()
{
	no<Item> *aux;                                      //cria um novo no auxiliar

	if (_inicio != 0)                                   //se o inicio for diferente de 0 iguala o no auxiliar ao inicio
	{
		aux = _inicio;
		_inicio = _inicio->_proximo;                    //iguala o inicio ao ponteiro proximo do inicio
		_inicio->_anterior = 0;                         //aponta o ponteiro anterior do inicio a 0
		delete aux;                                     //apaga a variavel auxiliar
		_tamanho--;                                     //decrementa o tamanho
	}
}


/****************************************************/
/* Apaga um item no final da lista.                 */
/* Nao recebe argumentos.                           */
/* Coloca o ponteiro fim a apontar para o anterior  */
/* e liberta a memoria alocada ao no a ser apagado  */
/****************************************************/
template <class Item>
void lista<Item>::apaga_fim()
{
	no<Item> *aux;                                      //cria um novo no auxiliar
	if (_inicio != 0)                                   //ve se o inicio ÅEdiferente de 0
	{
		if (_inicio != _fim)                            //se o inicio for diferente do fim iguala o no auxiliar ao fim
		{
			aux = _fim;
			_fim = _fim->_anterior;                     //iguala o fim ao ponteiro anterior do fim
			_fim->_proximo = 0;                         //aponta o ponteiro proximo do fim a 0
			delete aux;                                 //apaga o no auxiliar
		}
		else                                            //se o inicio for igual ao fim
		{
			delete _inicio;                             //apaga o inicio
			_inicio = 0;                                //iguala o inicio a 0
			_fim = 0;                                   //iguala o fim a 0
		}
		_tamanho--;                                     //decrementa o tamanho
	}
}


/****************************************************/
/* Remove um item na posicao indicada.              */
/* Recebe um inteiro como argumento.                */
/* Percorre a lista ate encontrar a posicao indicada*/
/* e reajusta os ponteiros para proximo e anterior  */
/* dos nos afectados.                                */
/****************************************************/
template <class Item>
Item* lista<Item>::apaga_posicao(int posicao)
{
	int i = 0;                                              //cria uma vari·vel int i e iguala a 0
	no<Item> *aux;                                          //cria um no auxiliar

	if (posicao <= (_tamanho - 1) && posicao >= 0)          //se a posiÁao estiver entre o tamanho -1 e 0
	{
		aux = _inicio;                                      //iguala o no auxiliar ao inicio
		if (_inicio == _fim)                                //se o inicio for igual ao fim
		{
			aux = _inicio;                                  //iguala o no auxiliar ao inicio
			_inicio = 0;                                    //iguala o inicio a 0
			_fim = 0;                                       //iguala o fim a 0
			_tamanho--;                                     //decrementa o tamanho
			return aux->_item;                              //devolve o item do no auxiliar
		}
		else
		{
			if (posicao == 0)                               //se o inicio for diferente do fim ve se a posiÁao recebida ÅEigual a 0
			{
				_inicio = aux->_proximo;                    //iguala o inicio ao ponteiro proximo do no auxiliar
				_inicio->_anterior = 0;                     //aponta o ponteiro anterior do inicio a 0
				aux->_proximo = 0;                          //aponta o ponteiro proximo do no auxiliar a 0
				aux->_anterior = 0;                         //aponta o ponteiro anterior do no auxiliar a 0
				_tamanho--;                                 //decrementa o tamanho
				return aux->_item;                          //devolve o item do no auxiliar
			}
			else
			{
				if (posicao == (_tamanho - 1))              //se a posiÁao for igual ao tamanho -1
				{
					aux = _fim;                             //iguala o no auxiliar ao fim
					_fim = aux->_anterior;                  //iguala o fim ao ponteiro anterior do no auxiliar
					_fim->_proximo = 0;                     //aponta o ponteiro proximo do fim a 0
					aux->_proximo = 0;                      //aponta o ponteiro proximo do no auxiliar a 0
					aux->_anterior = 0;                     //aponta o ponteiro anterior do no auxiliar a 0
					_tamanho--;                             //decrementa o tamanho
					return aux->_item;                      //devolve o item do no auxiliar
				}
				else
				{
					while (i < posicao)                     //enquanto i for menor que a posiÁao recebida
					{
						aux = aux->_proximo;                //iguala o no auxiliar ao proximo
						i++;                                //incrementa i
					}
					aux->_anterior->_proximo = aux->_proximo;       //
					aux->_proximo->_anterior = aux->_anterior;      //
					aux->_proximo = 0;                              //aponta o ponteiro proximo do no auxiliar a 0
					aux->_anterior = 0;                             //aponta o ponteiro anterior do no auxiliar a 0
					_tamanho--;                                     //decrementa o tamanho
					return aux->_item;                              //devolve o item do no auxiliar
				}
			}
		}
	}
	return 0;
}

/****************************************************/
/* Retorna o ponteiro para o item apontado pelo no  */
/* inicial.                                         */
/****************************************************/
template <class Item>
Item& lista<Item>::getInicio()
{
	return _inicio->_item;                                          //devolve o item do inicio
}


/****************************************************/
/* Retorna o ponteiro para o item apontado pelo no  */
/* final.                                           */
/****************************************************/
template <class Item>
Item& lista<Item>::getFim()
{
	return _fim->_item;                                         //devolve o item do fim
}


/****************************************************/
/* Retorna o ponteiro para o item apontado pelo no  */
/* na posicao indicada.                             */
/* Recebe como argumentos um inteiro correspondente */
/* a posicao.                                       */
/* Percore a lista ate a posicao indicada e retorna */
/* um ponteiro para o item apontado pelo no indicado*/
/****************************************************/
template <class Item>
Item& lista<Item>::getPosicao(int posicao)
{
	no<Item> *aux = _inicio;

	if (posicao <= _tamanho - 1)
	{
		for (int i = 0; i < posicao; i++)
		{
			aux = aux->_proximo;
		}
		return aux->_item;
	}
	cout << "Posicao Inexistente!!" << endl;
}


/****************************************************/
/* Imprime o conteudo da lista para o ecran.        */
/****************************************************/
template <class Item>
void lista<Item>::print(ostream& os) const
{
	no<Item> *aux = _inicio;
	if (aux != 0)
	{
		while (aux != 0)
		{
			os << *(aux->_item) << flush;
			os << endl;
			aux = aux->_proximo;
		}
	}
	else
	{
		cout << endl << "A Lista esta VAZIA" << endl;
	}
}


/****************************************************/
/* ???????????????????????????????????????????????  */
/****************************************************/
template <class Item>
ostream& operator<<(ostream& os, const lista<Item>& lista)
{
	lista.print(os);
	return os;
}


// ITERADOR
template <class Item>
class iterador
{
private:
protected:
	no<Item> *_ponteiro;        //ponteiro para o no indicado pelo iterador
	bool _direccao;             //Determina a direccao do movimento do iterador
								//0 = Inicio -> Fim ; 1 = Fim -> Inicio

public:
	iterador();                                     //constructor default do iterador
	iterador(const iterador<Item>&);                //constructor do iterador
	iterador(lista<Item>&, bool = 0);               //constructor do iterador
	~iterador() {};                                  //destructor

	void initIterador(lista<Item>&, bool = 0);      //inicializa o iterador
	void Next();                                    //move o iterador para o proximo no
	bool Ultimo();                                  //retorna _ponteiro a NULL

	Item& getObjecto();                             //get ao item apontado pelo no apontado pelo iterador
	Item* getPonteiroObjecto();                     //get ao ponteiro do item apontado pelo no apontado pelo iterador
};



/*************************************************/
/* Constructor default para a classe iterador.   */
/* N„o recebe argumentos.                        */
/* Coloca os _ponteiro a NULL e _dereccao a 0    */
/*************************************************/
template <class Item>
iterador<Item>::iterador()
{
	_ponteiro = 0;
	_direccao = 0;
}


/*************************************************/
/* Constructor para a classe iterador.           */
/* N„o recebe argumentos.                        */
/* Coloca os ponteiros _inicio e _fim a NULL e o */
/* inteiro _tamanho a zero                       */
/*************************************************/
template <class Item>
iterador<Item>::iterador(const iterador<Item>& it)
{
	_ponteiro = it->_ponteiro;
	_direccao = it->_direccao;
}

template <class Item>
iterador<Item>::iterador(lista<Item>& l, bool dir)
{
	_direccao = dir;
	if (!dir)
	{
		_ponteiro = l.getPonteiroInicio();
	}
	else
	{
		_ponteiro = l.getPointeiroFim();
	}
}

template <class Item>
void iterador<Item>::initIterador(lista<Item>& l, bool dir)
{
	_direccao = dir;
	if (!dir)
	{
		_ponteiro = l.getPonteiroInicio();
	}
	else
	{
		_ponteiro = l.getPointeiroFim();
	}
}

template <class Item>
void iterador<Item>::Next()
{
	if (!_direccao)
	{
		_ponteiro = _ponteiro->getPonteiroProximo();
	}
	else
	{
		_ponteiro = _ponteiro->getPonteiroAnterior();
	}
}

template <class Item>
bool iterador<Item>::Ultimo()
{
	return (_ponteiro == 0);
}

template <class Item>
Item& iterador<Item>::getObjecto()
{
	return *(_ponteiro->getPonteiroItem());
}

template <class Item>
Item* iterador<Item>::getPonteiroObjecto()
{
	return (_ponteiro->getPonteiroItem());
}

#endif
#pragma once
