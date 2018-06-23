#include <iostream>
#include "ColaPedidos.h"

using namespace std;

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

Nodo* insBraun(Nodo* nodo, Pedido p){
  if (nodo == NULL){
    return nuevoNodo(p);
  } else {
    if(masPrioridad(p, nodo->pedido)) swap(p, nodo->pedido);
    nodo->der = insBraun(nodo->der, p);
    if (impar(nodo->tam)){
      swap(nodo->izq, nodo->der);
    }
    nodo->tam++;
    return nodo;
  }
}

void encolarCP(ColaPedidos cp, Pedido p) {
    cp->raiz = insBraun(cp->raiz, p);
}

// prec: tamCP(cp) > 0
Pedido proximoCP(ColaPedidos cp) {
  return cp->raiz->pedido;
}

// prec: nodo no es NULL
Nodo* eliBraun(Nodo* nodo, Pedido& pedidoEliminado){
  if (nodo->tam == 1){
    pedidoEliminado = nodo->pedido;
    delete nodo;
    return NULL;
  } else {
    nodo->izq = eliBraun(nodo->izq, pedidoEliminado);
    if (impar(nodo->tam)) {
      swap(nodo->der, nodo->izq);
    }
    nodo->tam--;
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

Nodo* intercambiarConHijoMayor(Nodo* nodo){
  Nodo* mayor = hijoMayor(nodo);
  Pedido temp = mayor->pedido;
  mayor->pedido = nodo->pedido;
  nodo->pedido = temp;
  return mayor;
}

void bajar(Nodo* nodo){
  Nodo* padre = nodo;
  while (tieneHijoMayor(padre)){
    padre = intercambiarConHijoMayor(padre);
  }
}

// prec: tamCP(cp) > 0
void desencolarCP(ColaPedidos cp) {
  Pedido pedidoEliminado;
  cp->raiz = eliBraun(cp->raiz, pedidoEliminado);
  if (cp->raiz != NULL){
      cp->raiz->pedido = pedidoEliminado;
      bajar(cp->raiz);
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

