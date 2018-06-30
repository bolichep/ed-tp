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

struct PapaNoelTest {
	int fechaDeHoy;
	ColaPedidos pedidosFuturos;
	int cantPedidosDeHoy;
	Pedido* pedidosDeHoy;
};	

typedef ColaPedidosTest* ColaPediTes;
typedef PapaNoelTest* PapaNoelTes;

void printPedido(Pedido pedido){
//  if (pedido == NULL) return;
  cout << " Pedido: " << endl;
  cout << "   persona: " << pedido.persona;
  cout << "   fechaEn: " << pedido.fechaEntrega;
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

void printPedidosDeHoy(Pedido* pedidos, int len){
  cout << "Pedidos de Hoy: " << len << " --"<<endl;
  for (int i = 0; len != 0 ; len--, i++)
    printPedido(pedidos[i]);
}
  
/*
struct PapaNoelRepr {
	int fechaDeHoy;
	ColaPedidos pedidosFuturos;
	int cantPedidosDeHoy;
	Pedido* pedidosDeHoy;
};	
*/
void printPNT(PapaNoelTes pn){
  cout << "\033[33m";
  cout << " Fecha Hoy: " << pn->fechaDeHoy;
  cout << " Cant Pedidos Hoy: " << pn->cantPedidosDeHoy << endl;
  cout << "\033[0m";
  printCPT((ColaPediTes) pn->pedidosFuturos);
  cout << pn->pedidosDeHoy << " " << pn->cantPedidosDeHoy;
//  printPedidosDeHoy(pn->pedidosDeHoy, pn->cantPedidosDeHoy);
}

void printIdsFut(PapaNoelTes pn){
  // PapaNoel np = 
  //while (tamCP(pn->pedidosFuturos)){
    cout << proximoCP(pn->pedidosFuturos).persona << " " ;
  //  //desencolarCP(pn->pedidosFuturos);
  //}
  cout << endl;
}
void printIdsHoy(PapaNoelTes pn){
  cout << "pedidos hoy " << pn->cantPedidosDeHoy << endl;
  while (pn->cantPedidosDeHoy){
    cout << pn->pedidosDeHoy[pn->cantPedidosDeHoy].persona << " " ;
    pn->cantPedidosDeHoy--;
  }
  cout << endl;
}

int main() {
  /*
	ColaPedidos cp = nuevaCP();
        ColaPediTes snif = (ColaPediTes)cp;
	cout << "Initial Tam: " << tamCP(cp)<< endl;

	Pedido p;
	p.persona = 1000; p.fechaEntrega = 99; p.estado = MalComportamiento;
	encolarCP(cp, p);
	p.estado = Pendiente; encolarCP(cp, p); 
	p.estado = Pendiente; encolarCP(cp, p);
	p.estado = Entregado; encolarCP(cp, p);
	printCPT(snif);
	cout << tamCP(cp)<< endl;
	cout << p.persona << " " << p.fechaEntrega << " " << p.estado << endl;


	Pedido q;
	q.persona = 123; q.fechaEntrega = 88; q.estado = Pendiente;
	encolarCP(cp, q); 
	printCPT((ColaPediTes)cp);
	cout << q.persona << " " << q.fechaEntrega << " " << q.estado << endl;

	PapaNoel santa = iniciarPN();
	registrarPedidoPN(santa, 1, 17);
	registrarPedidoPN(santa, 3, 19);
	registrarPedidoPN(santa, 2, 23);
	registrarPedidoPN(santa, 1, 32);
	registrarPedidoPN(santa, 1, 56);
	registrarPedidoPN(santa, 1, 83);
	registrarPedidoPN(santa, 1, 93);
	registrarPedidoPN(santa, 1, 43);
	//desencolarPN(santa);
	avanzarDiaPN(santa);
	cout << "Fecha actual: " << fechaActualPN(santa) << endl;
	printPNT((PapaNoelTes)santa);
	avanzarDiaPN(santa);
	cout << "Fecha actual: " << fechaActualPN(santa) << endl;
	printPNT((PapaNoelTes)santa);
	avanzarDiaPN(santa);
	cout << "Fecha actual: " << fechaActualPN(santa) << endl;
	finalizarPN(santa);

*/

	PapaNoel p = iniciarPN();
	registrarPedidoPN(p, 1, 15);
	registrarPedidoPN(p, 2, 25);
	registrarPedidoPN(p, 1, 19);
	registrarPedidoPN(p, 2, 29);
	registrarPedidoPN(p, 1, 11);
	registrarPedidoPN(p, 2, 21);
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 11) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 15) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 19) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 21) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 25) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 29) << endl;
	 cout << "Fecha Actual  0: " << fechaActualPN(p)  << endl;
	avanzarDiaPN(p);
	 cout << "Estado pedido 1: " << fechaActualPN(p)  << endl;
	printPNT((PapaNoelTes)p);
	 cout << "Estado pedido 1: " << estadoPedidoPN(p, 11) << endl;
	 cout << "Estado pedido 1: " << estadoPedidoPN(p, 15) << endl;
	 cout << "Estado pedido 1: " << estadoPedidoPN(p, 19) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 21) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 25) << endl;
	 cout << "Estado pedido 0: " << estadoPedidoPN(p, 29) << endl;
	finalizarPN(p);
/*
	PapaNoel p = iniciarPN();
	registrarPedidoPN(p, 1, 15);
	registrarPedidoPN(p, 2, 25);
	registrarPedidoPN(p, 3, 19);
	registrarPedidoPN(p, 2, 29);
	registrarPedidoPN(p, 1, 11);
	registrarPedidoPN(p, 3, 21);
	printIdsFut((PapaNoelTes)p);
	avanzarDiaPN(p);
	printIdsFut((PapaNoelTes)p);
	avanzarDiaPN(p);
	printIdsHoy((PapaNoelTes)p);
	//cout << "15 # " << estadoPedidoPN(p,15) << endl;
	//cout << "10 # " << estadoPedidoPN(p,10) << endl;
	//cout << "25 # " << estadoPedidoPN(p,25) << endl;
	entregarPedidoPN(p,1); // dummy test

*/
//	destruirCP(cp);
	return 0;
}

