//#include <cstdio>
#include <iostream>

#include "ColaPedidos.h"
#include "PapaNoel.h"

struct PapaNoelRepr {
	int fechaDeHoy;
	ColaPedidos pedidosFuturos;
	int cantPedidosDeHoy;
	Pedido* pedidosDeHoy;
};

// O(1)
PapaNoel iniciarPN() {
  PapaNoel pn = new PapaNoelRepr;
  pn->fechaDeHoy = 0;
  pn->pedidosFuturos = nuevaCP();
  pn->cantPedidosDeHoy = 0;
  pn->pedidosDeHoy = NULL;
  return pn;
}

//O(1)
Fecha fechaActualPN(PapaNoel p) {
  return p->fechaDeHoy;
}

// prec: fecha f es posterior a fecha actual
// -- Es una eleccion no registrar el pedido en el array pedidosDeHoy
// - O(log n)
void registrarPedidoPN(PapaNoel p, Fecha f, Id x) {
  Pedido pedido;

  pedido.persona = x;
  pedido.fechaEntrega = f;
  pedido.estado = Pendiente;
  encolarCP(p->pedidosFuturos, pedido); // O(log n)
}

// TODO check medio.... etc
// O(log n) ?
Estado estadoPedidoId(Pedido* pedidos, int desde, int hasta, Id x){
  if (hasta < desde || pedidos == NULL)
    return Inexistente;
  int medio = desde + (hasta - desde) / 2;
  if (pedidos[medio].persona > x)
    return estadoPedidoId(pedidos, desde, medio-1, x);
  else if (pedidos[medio].persona < x)
    return estadoPedidoId(pedidos, medio+1, hasta, x);
  else
    return pedidos[medio].estado;
}

// O(log H) H es total pedidos para fechaHoy
// prec: no
Estado estadoPedidoPN(PapaNoel p, Id x) {
  estadoPedidoId(p->pedidosDeHoy, 0, p->cantPedidosDeHoy, x);
}


void entregarPedidoPN(PapaNoel p, Id x) {
  //COMPLETAR
}

void registrarMalComportamientoPN(PapaNoel p, Id x) {
	// COMPLETAR
}

#define pp \
    std::cout << "$ " << " fechas " << primero.fechaEntrega << " " << p->fechaDeHoy<< std::endl;\
    std::cout << "capacidad " << capacidadArray << std::endl;\
    std::cout << "array " << array << std::endl;\
    std::cout << "i " << i ;\
    std::cout << "p->cantPedidosDeHoy" << p->cantPedidosDeHoy  << std::endl;\
    std::cout << "tamCP(p->pedidosFuturos) = " << tamCP(p->pedidosFuturos) << std::endl;\
    std::cout << "array--persona " << array[0].persona << std::endl;\
    std::cout << "array--persona " << array[1].persona << std::endl;\
    std::cout << "array--persona " << array[2].persona << std::endl;\
    std::cout << "array--persona " << array[3].persona << std::endl;\
    std::cout << "array--persona " << array[4].persona << std::endl;\
    std::cout << "array--persona " << array[5].persona << std::endl;\
    std::cout << "array--persona " << array[6].persona << std::endl;\
    std::cout << "array--persona " << array[7].persona << std::endl;

void duplicarTamArreglo(Pedido*& array, int& capacidadArray){
  Pedido* nuevo = new Pedido[2 * capacidadArray];
  for (int i = 0; i < capacidadArray ; i++)
    nuevo[i] = array[i];
  delete [] array;
  capacidadArray *= 2;
  array = nuevo;
}

// prec: p->cantPedidosDeHoy > 0 ????? 
// O(H + M . log P) 
// H pedidos Hoy (antes de avanzar de dia)
// M cant pedidos para la fecha de mañana
// P total de pedidos cargados
void avanzarDiaPN(PapaNoel p){
  p->cantPedidosDeHoy = 0;
  if (p->pedidosDeHoy != NULL ) delete [] p->pedidosDeHoy; // O(1)?

  int largoArreglo = 1;
  p->pedidosDeHoy = new Pedido[largoArreglo];
  p->fechaDeHoy++;
    int i = 0;
  while (tamCP(p->pedidosFuturos)){
    Pedido pedido = proximoCP(p->pedidosFuturos);
    if (pedido.fechaEntrega == p->fechaDeHoy){
      p->pedidosDeHoy[i] = pedido;
      p->cantPedidosDeHoy++;
      i++;
      if (i == largoArreglo)
	duplicarTamArreglo(p->pedidosDeHoy, largoArreglo);

      desencolarCP(p->pedidosFuturos);
    } else 
      break;
  }
  //int l = p->cantPedidosDeHoy;
  //std::cout << l << "# " << std::endl; 
  //while(l) std::cout << p->pedidosDeHoy[l].persona << "/" << p->pedidosDeHoy[l--].fechaEntrega << std::endl; 
}
 

void finalizarPN(PapaNoel p) {
  delete p->pedidosDeHoy;
  destruirCP(p->pedidosFuturos);
  delete p;
}

