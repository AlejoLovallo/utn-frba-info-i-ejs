#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "lib.h"

#define CANT_VENTAS 50
#define CANT_VENDEDORES 20

int main(void){

  int running = 1;

  vendedor_t listaVendedores[CANT_VENDEDORES];
  ventas_t listaVentas[CANT_VENTAS]; //Numero random

  while(running){
    switch(menu()){
      case 1: 
        //Agregar nuevo vendedor
        agregarVendedor(listaVendedores);
        break;
      case 2:
        //Ingresar nueva venta
        agregarVenta( listaVendedores);
        break;
      case 3:
        //Filtrar datos Ventas
        filtrarDatosVentas( listaVendedores, listaVentas);
        break;
      case 4:
        printf("Gracias por usar esta aplicacion!\n");
        running = 0;
        break;
      default:
        printf("ERROR! INGRESE UN CARACTER VÁLIDO\n");
        break;
    }
  }

  verVendedores();
}



