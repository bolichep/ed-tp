#include <cstdio>
#include "ColaPedidos.h"

struct Nodo {
	int tam;
	Pedido pedido;
	Nodo* izq;
	Nodo* der;
};

struct ColaPedidosRepr {
	Nodo* raiz;
};

ColaPedidos nuevaCP() {
  ColaPedidos cp;
  cp = new ColaPedidosRepr;
  cp->raiz = NULL; // mmmmmmm
  return cp;
}

// sin precondiciones: Total
int tamCP(ColaPedidos cp) {
  return cp->raiz==NULL?0:cp->raiz->tam;
}

bool masPrioridad(Pedido p1, Pedido p2){
  return p1.fechaEntrega < p2.fechaEntrega 
    ||
    (p1.fechaEntrega == p2.fechaEntrega && p1.persona < p2.persona);
}

Pedido menorPrioridad(Pedido p1, Pedido p2){
  Pedido menorP = p2;
  if (not masPrioridad(p1, p2)){
    menorP = p1;
  }
  return menorP;
}

Pedido mayorPrioridad(Pedido p1, Pedido p2){
  Pedido mayorP = p2;
  if (masPrioridad(p1, p2)){
    mayorP = p1;
  }
  return mayorP;
}

Nodo* nuevoNodo(Pedido p){
  Nodo* n = new Nodo;
  n->tam = 1;
  n->pedido = p;
  n->izq = NULL;
  n->der = NULL;
  return n;
}

bool impar(int i){
  return i % 2 == 1;
}

bool par(int i){
  return not impar(i);
}

void swapNodo(Nodo*& n1, Nodo*& n2){
  Nodo* tmp = n1;
  n1 = n2;
  n2 = tmp;
}

Nodo* insBraun(Nodo* nodo, Pedido p, int tam){
  if (nodo == NULL){
    return nuevoNodo(p);
  } else {
    Pedido menor = menorPrioridad(p, nodo->pedido);
    nodo->pedido = mayorPrioridad(p, nodo->pedido);
    nodo->der = insBraun(nodo->der, menor, (tam-1)/2);
    if (impar(tam)){
      swapNodo(nodo->izq, nodo->der);
    }
    nodo->tam++;
    return nodo;
  }
}

void encolarCP(ColaPedidos cp, Pedido p) {
    cp->raiz = insBraun(cp->raiz, p, 
	// encolar no tiene prec
	cp->raiz==NULL?0:cp->raiz->tam); 
}

// prec: tamCP(cp) > 0
Pedido proximoCP(ColaPedidos cp) {
  return cp->raiz->pedido;
}

Nodo* eliminar(Nodo* nodo, Pedido& pedidoEliminado, int tam){
  if (tam == 1){
    pedidoEliminado = nodo->pedido;
    delete nodo;
    return NULL;
  } else {
    nodo->izq = eliminar(nodo->izq, pedidoEliminado, tam/2);
    if (impar(tam)) {
      swapNodo(nodo->der, nodo->izq);
    }
    return nodo;
  }
}

bool tieneHijoMayor(Nodo* nodo){ //prec: nodo not NULL

  return (nodo->izq != NULL && masPrioridad(nodo->izq->pedido, nodo->pedido)) 
    ||   (nodo->der != NULL && masPrioridad(nodo->der->pedido, nodo->pedido));
}

Nodo* hijoMayor(Nodo* nodo){
  if (nodo->der != NULL && masPrioridad(nodo->der->pedido, nodo->izq->pedido)){
    return nodo->der;
  } else {
    return nodo->izq;
  }
}

void intercambiarConHijoMayor(Nodo* nodo){
  Nodo* mayor = hijoMayor(nodo);
  Pedido temp = mayor->pedido;
  mayor->pedido = nodo->pedido;
  nodo->pedido = temp;
}

void bajar(Nodo* nodo){
  Nodo* padre = nodo;
  while (tieneHijoMayor(padre)){
    intercambiarConHijoMayor(padre);
    padre = hijoMayor(padre);
  }
}

// prec: tamCP(cp) > 0
void desencolarCP(ColaPedidos cp) {
  Pedido pedidoEliminado;
  cp->raiz = eliminar(cp->raiz, pedidoEliminado, cp->raiz->tam);
  if (cp->raiz != NULL){
    cp->raiz->tam--;
    if (cp->raiz->tam > 0) {
      cp->raiz->pedido = pedidoEliminado;
      bajar(cp->raiz);
    }
  }
}

void destruirNodo(Nodo* nodo){
  if (nodo != NULL){
    destruirNodo(nodo->izq);
    destruirNodo(nodo->der);
  }
}

void destruirCP(ColaPedidos cp) {
  destruirNodo(cp->raiz);
}

