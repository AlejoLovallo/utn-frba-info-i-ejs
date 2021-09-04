#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nombre[50];
  int legajo;
  int antiguedad;
  int ganancia[12];

} vendedor_t;

typedef struct {
  char path[50];
  int aaaa; 
  int mm;
  int dd;
  int cant;
  int monto;
  int legajo;
} ventas_t;



//FUNCIONES PRINCIPALES
int menu();
int agregarVenta( vendedor_t*);
int agregarVendedor( vendedor_t* );
int filtrarDatosVentas(vendedor_t* , ventas_t* );
//FUNCIONES PRINCIPALES

//FUNCIONES AUXILIARES
char* calcularPath(char* , char* , char* , char* );
void inicializarGanancias(vendedor_t *listaVendedores, int*);
void sacarDatosVendedor( vendedor_t* , int*);
void obtenerLegajos(int *legajos, int *cont);
void sacarDatosVentas(FILE* , ventas_t* , int* , int , int , int , char* );
void buscarVentas( ventas_t* , int , int ,int* );
void calculoComision(vendedor_t* , ventas_t*, int , int);
//FUNCIONES AUXILIARES


//FUNCIONES DE VISUALIZACION 
void verVendedores();
void imprimirResultados(vendedor_t*, int);
//FUNCIONES DE VISUALIZACION
