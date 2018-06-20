#include <iostream>

using namespace std;

#include "src/ColaPedidos.h"
#include "src/PapaNoel.h"

#include "src/Test.h"

struct Node {
	int tam;
	Pedido pedido;
	Node* izq;
	Node* der;
};

struct ColaPedidosTest {
	Node* root;
};

typedef ColaPedidosTest* ColaPediTes;

void printPedido(Pedido pedido){
  cout << " Pedido: " << endl;
  cout << "   persona: " << pedido.persona << endl;
  cout << "   fechaEn: " << pedido.fechaEntrega << endl;
  cout << "   estado : " << pedido.estado << endl;
}

void printNodePedido(Node* ptr){
  if (ptr != NULL){
    cout << "Tam: " << ptr->tam ;
    printPedido(ptr->pedido);
    printNodePedido(ptr->izq);
    printNodePedido(ptr->der);
  }
}

void printCPT(ColaPediTes cpt){
  printNodePedido(cpt->root);
}

int main() {
	ColaPedidos cp = nuevaCP();
        ColaPediTes snif = (ColaPediTes)cp;
	cout << tamCP(cp)<< endl;

	Pedido p,r;
	p.persona = 1000;
	p.fechaEntrega = 99;
	p.estado = Entregado;

	r.persona = 777;
	r.fechaEntrega = 45;
	r.estado = Entregado;

	encolarCP(cp, p);
	p.persona = 300;
	p.fechaEntrega = 49;
	encolarCP(cp, p);
	p.persona = 345;
	p.fechaEntrega = 9;
	encolarCP(cp, p);
	p.persona = 246;
	p.fechaEntrega = 2;
	encolarCP(cp, p);
	encolarCP(cp, r);
	printCPT(snif);
	cout << tamCP(cp)<< endl;
	cout << p.persona << " " << p.fechaEntrega << " " << p.estado << endl;
	cout << r.persona << " " << r.fechaEntrega << " " << r.estado << endl;


	Pedido q;
	q.persona = 123;
	q = proximoCP(cp);
	cout << q.persona << " " << q.fechaEntrega << " " << q.estado << endl;
	/*
	ASSERT_EQ(q.persona, 1000);
	ASSERT_EQ(q.fechaEntrega, 99);
	ASSERT_EQ(q.estado, Entregado);
	*/

	destruirCP(cp);
	return 0;
}

