#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

#define TRUE 1

int main(){

    Vendedor vendedores[20];

    Venta ventas[20];
    
    //agregarVendedor(vendedores);

    agregarVenta();

    filtrarVentas(ventas,vendedores);

    return 0;
}



/**
int main(){

    int running = TRUE;

    Vendedor vendedores[20];

    Venta ventas[20];

    while(running){
    switch(menu()){
      case 1: 
        //Agregar nuevo vendedor
        agregarVendedor(vendedores);
        break;
      case 2:
        //Ingresar nueva venta
        agregarVenta( vendedores);
        break;
      case 3:
        //Filtrar datos Ventas
        filtrarDatosVentas( vendedores, ventas);
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

    return 0;
}
**/