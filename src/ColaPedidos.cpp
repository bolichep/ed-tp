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

void desencolarCP(ColaPedidos cp) {
	// COMPLETAR
}

void destruirCP(ColaPedidos cp) {
  //TODO: destruir correctamenteS
  delete cp->raiz;
  delete cp;
}

