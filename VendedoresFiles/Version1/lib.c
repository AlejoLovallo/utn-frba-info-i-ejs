#include "lib.h"
#include <stdlib.h>
#include <stdio.h>

#define CANT_VENDEDORES 20

// FUNCIONES AUXILIARES 

char* calcularPath(char* aaaa, char* mm, char* dd, char* p){
  char path[50];
  strcpy(path,"");  //Limpia la memoria

  strcat(path,aaaa);

  strcat(path,mm);

  strcat(path,dd);

  strcat(path,".csv");

  strcpy(p, path);
  return p;
}

void inicializarGanancias(vendedor_t *listaVendedores,int *cont){
  for(int i = 0; i < (*cont);i++){
    for(int j= 0; j < 12; j++){
      listaVendedores[i].ganancia[j] = 0;
    }
  }
}

void imprimirVendedores(vendedor_t *listaVendedores,int *cont){
  for(int i=0; i < (*cont);i++){
    printf("NOMBRE %s\n",listaVendedores[i].nombre);
    printf("Antiguedad %d\n",listaVendedores[i].antiguedad);
    printf("Legajo %d\n",listaVendedores[i].legajo);
    for(int j = 0; j<12; j++){
      printf("Ganancia mes %d %d\n",j,listaVendedores[i].ganancia[j]);
    }
  }
}

void obtenerLegajos(int *legajos,int *cont){
  char s[100];
  char* auxPointer;
  char momentaneo[100];
  *cont = 0;
  FILE* fp = fopen("vendedores.csv","r");
  if(fp != NULL){
    while (!feof(fp)) {
      auxPointer = fgets(s,100,fp);
      if(auxPointer != NULL){
          strtok(auxPointer,",");
          legajos[*cont] = atoi(strcpy(momentaneo, strtok(NULL, ",")));
          strtok(NULL,",");
          (*cont)++;
      }
    }
    fclose( fp );
    printf("Cantidad de vendedores encontrados %d\n", *cont);
  }else{
    printf("ERROR AL ABRIR VENDEDORES.CSV\n");
  }
}

/// FUNCIONES AUXILIARES

int menu(){
  int respuesta;
  printf("-------------------------------------------------------------------\n");
  printf("-------------------------------------------------------------------\n");
  printf("-----                                                         -----\n");
  printf("-----                   OPCIONES:                             -----\n");
  printf("-----                                                         -----\n");
  printf("-----                                                         -----\n");
  printf("-----         1 - INGRESAR NUEVO VENDEDOR                     -----\n");
  printf("-----                                                         -----\n");
  printf("-----         2 - INGRESAR NUEVA VENTA                        -----\n");
  printf("-----                                                         -----\n");
  printf("-----         3 - FILTRAR DATOS VENTAS                        -----\n");
  printf("-----                                                         -----\n");
  printf("-----         4 - SALIR                                       -----\n");
  printf("-----                                                         -----\n");
  printf("-----                                                         -----\n");
  printf("-------------------------------------------------------------------\n");
  printf("-------------------------------------------------------------------\n");

  scanf("%d", &respuesta );
  return respuesta;
}

//FUNCIONES MANEJO DE VENDEDORES

int agregarVendedor( vendedor_t* listaVendedores){
  char nombre[50], apellido[50];
  char linea[100];
  char aux[2][5];
  int legajo, antiguedad,cont_vendedores,legajosVendedores[CANT_VENDEDORES];

  obtenerLegajos(legajosVendedores,&cont_vendedores);

  printf("Ingrese el LEGAJO del nuevo vendedor: \n");
  scanf("%d", &legajo );

  _Bool existeLegajo = 0;
  for(int i = 0; i <= cont_vendedores; i++){
    if(legajosVendedores[i]==legajo){
      existeLegajo = 1;
      break;
    }
  }

  if(existeLegajo){
    printf("\n\n------------ YA EXISTE UN VENDEDOR CON ESE NUMERO DE LEGAJO! ------------\n\n");
    return -1;
  }

  printf("Ingrese el NOMBRE del nuevo vendedor: \n");
  scanf("%s", nombre );
  strcat(nombre," ");

  printf("Ingrese el APELLIDO del nuevo vendedor: \n");
  scanf("%s", apellido );
  strcat(nombre,apellido);

  printf("Ingrese el ANTIGUEDAD (años) del nuevo vendedor: \n");
  scanf("%d", &antiguedad );

  printf("-------------------------------------------------------------------\n");

  if (legajo <= 0 || antiguedad <= 0){
    printf("Ingreso mal alguno de los datos.\n");
    return -1;
  }


  FILE* stream = fopen("vendedores.csv","a+");

  if(stream){
    sprintf(aux[1],"%d", antiguedad);
    sprintf(aux[0],"%d", legajo);

    strcpy(linea, "");
    strcat(linea, nombre);
    strcat(linea, ",");
    strcat(linea, aux[0]);
    strcat(linea, ",");
    strcat(linea, aux[1]);

    while (fputs(linea,stream)== EOF) printf("ERORR AL ESCRIBIR... INTENTANDO NUEVAMENTE!\n");
    while (fputs("\n",stream)== EOF) printf("ERORR AL ESCRIBIR... INTENTANDO NUEVAMENTE!\n");

    fclose( stream );
    printf("VENDEDOR CARGADO!\n");
    return 0;
  }
  printf("ERROR AL ABRIR EL ARCHIVO GENERADO\n");
  return -1;
}

//FUNCIONES MANEJO DE VENDEDORES

// FUNCIONES MANEJO DE VENTAS

int agregarVenta( vendedor_t* listaVendedores){
  int cont_vendedores, mm, aaaa, dd, legajo, monto, cant, legajosVendedores[CANT_VENDEDORES];
  char path[50];
  char p[50];
  char linea[100];
  char aux[3][5];

  printf("Ingrese el LEGAJO del vendedor a cargar la venta: \n");
  scanf("%d", &legajo );

  obtenerLegajos(legajosVendedores,&cont_vendedores);

  _Bool existeLegajo = 0;
  for(int i = 0; i <= cont_vendedores; i++){
    if(legajosVendedores[i]==legajo){
      existeLegajo = 1;
      break;
    }
  }

  if(!existeLegajo){
    printf("\n\n------------ NO EXISTE UN VENDEDOR CON ESE NUMERO DE LEGAJO! ------------\n\n");
    return -1;
  }

  printf("Ingrese el año - mes - dia en el que se realizo la venta:\n");
  scanf("%d %d %d", &aaaa, &mm, &dd );
  printf("Ingrese la cantidad de articulos vendidos:\n");
  scanf("%d", &cant );
  printf("Ingrese el monto asociado a la venta:\n");
  scanf("%d", &monto );
  printf("-------------------------------------------------------------------\n");

  if (monto > 0 && cant > 0 && dd > 0 && dd <= 31 && mm >0 && mm <= 12 && aaaa > 2000){
    printf("Todos los datos son validos!\n");
  }else{
    printf("ERROR! Alguno de los datos ingresado es invalido.\n");
    return -1;
  }

  //Creamos el archivo listo para guardar
  sprintf(aux[0],"%.4d", aaaa);
  sprintf(aux[1],"%.2d", mm);
  sprintf(aux[2],"%.2d", dd);
  strcpy(path, calcularPath( aux[0],  aux[1],  aux[2],  p));

  FILE* ventaArchivo;
  ventaArchivo = fopen(path,"a+");

  //Si se puede escribimos en el final del archivo otra linea.
  if(ventaArchivo){
    sprintf(aux[0],"%d", cant);
    sprintf(aux[1],"%d", monto);
    sprintf(aux[2],"%d", legajo);
    strcpy(linea, "");
    strcat(linea, aux[0]);
    strcat(linea, ",");
    strcat(linea, aux[1]);
    strcat(linea, ",");
    strcat(linea, aux[2]);
    while (fputs(linea,ventaArchivo)== EOF) printf("ERORR AL ESCRIBIR... INTENTANDO NUEVAMENTE!\n");
    while (fputs("\n",ventaArchivo)== EOF) printf("ERORR AL ESCRIBIR... INTENTANDO NUEVAMENTE!\n");
    fclose( ventaArchivo );
    printf("VENTA CARGADA!\n");
    return 0;
  }
  printf("ERROR AL ABRIR EL ARCHIVO GENERADO\n");
  return -1;
}

void sacarDatosVendedor( vendedor_t* lista, int* contador ){
  char s[100];
  char* auxPointer;
  char momentaneo[100];
  *contador = 0;
  FILE* fp = fopen("vendedores.csv","r");
  
  if(fp != NULL){
    while (!feof(fp)) {
      auxPointer = fgets(s,100,fp);
      if(auxPointer != NULL){
          strcpy(lista[*contador].nombre, strtok(auxPointer, ","));
          lista[*contador].legajo = atoi(strcpy(momentaneo, strtok(NULL, ",")));
          lista[*contador].antiguedad = atoi(strcpy(momentaneo, strtok(NULL, ",")));
          (*contador)++;
      }
    }
    fclose( fp );
  }else{
    printf("ERROR AL ABRIR VENDEDORES.CSV\n");
  }
}

int filtrarDatosVentas(vendedor_t* listaVendedores, ventas_t* listaVentas){
  int cont_vendedores;
  int contadorDeVentas;
  int mm;
  int aaaa;

  printf("Ingrese el año por el que quiera filtrar:\n");
  scanf("%d", &aaaa );
  printf("Ingrese el mes por el que quiera filtrar:\n");
  scanf("%d", &mm );
  printf("-------------------------------------------------------------------\n");

  sacarDatosVendedor(listaVendedores, &cont_vendedores);

  buscarVentas(listaVentas, aaaa, mm, &contadorDeVentas);

  inicializarGanancias(listaVendedores,&cont_vendedores);

  imprimirVendedores(listaVendedores,&cont_vendedores);

  calculoComision(listaVendedores, listaVentas, cont_vendedores, contadorDeVentas);

  imprimirResultados(listaVendedores, cont_vendedores);
  return 0;
}

void buscarVentas(ventas_t* listaVentas, int aaaa, int mm, int* contadorDeVentas){
  FILE* stream; 
  char path[50], p[50];
  char aux[3][5];
  *contadorDeVentas = 0;

  sprintf(aux[0],"%.4d", aaaa);
  sprintf(aux[1],"%.2d", mm);

  for(int dd = 1; dd <= 31; dd++){
    sprintf(aux[2],"%.2d",dd);      //TRANSFORMA EL DIA EN UN STRING
    strcpy(path, calcularPath(aux[0] , aux[1], aux[2], p) );
    stream = fopen(path,"r");
    if (stream != NULL){
      printf("STREAM NOMBRE: %s\n",path);
      printf("ENCONTRE VENTA EN DIA: %d\n",dd);
      sacarDatosVentas(stream, listaVentas, contadorDeVentas, aaaa, mm, dd, path);
      fclose( stream );
    }
  }
}

void sacarDatosVentas(FILE* stream, ventas_t* lista, int* contador, int aaaa, int mm, int dd, char* path){
  char s[100];
  char* pointer;
  char momentaneo[100];
  while (!feof(stream)) {
    pointer = fgets(s ,100 ,stream);
    if(pointer != NULL){
        lista[*contador].cant = atoi(strcpy(momentaneo, strtok(pointer, ",")));
        printf("CANTIDAD ENCONTRADA %d\n",lista[*contador].cant);
        lista[*contador].monto = atoi(strcpy(momentaneo, strtok(NULL, ",")));
        printf("MONTO ENCONTRADA %d\n",lista[*contador].monto);
        lista[*contador].legajo = atoi(strcpy(momentaneo, strtok(NULL, ",")));
        printf("LEGAJO ENCONTRADA %d\n",lista[*contador].legajo);
        strcpy(lista[*contador].path, path);

        lista[*contador].aaaa = aaaa;
        lista[*contador].mm = mm;
        lista[*contador].dd = dd;
        (*contador)++;
    }
  }
}


// FUNCIONES DE VISUALIZACION / RESULTADOS

void verVendedores(){
  char s[100], *auxPointer, momentaneo[100];
  FILE* fp = fopen("vendedores.csv","r");
  
  if(fp != NULL){
    while (!feof(fp)) {
      auxPointer = fgets(s,100,fp);
      if(auxPointer != NULL){
          printf("Nombre: %s",strtok(auxPointer,","));
          printf("- Legajo %d",atoi(strcpy(momentaneo,strtok(NULL,","))));
          printf("- Antiguedad %d\n",atoi(strcpy(momentaneo,strtok(NULL,","))));
      }
    }
    fclose( fp );
  }else{
    printf("ERROR AL ABRIR VENDEDORES.CSV\n");
  }
}

void calculoComision(vendedor_t* listaVendedores, ventas_t* listaVentas, int cont_vendedores, int contadorDeVentas){
  for( int y = 0; y <= contadorDeVentas-1; y++){
    for( int x = 0; x <= cont_vendedores-1; x++){

      if(listaVendedores[x].legajo == listaVentas[y].legajo){
        listaVendedores[x].ganancia[listaVentas[y].mm-1] += (listaVentas[y].monto * listaVendedores[x].antiguedad) / 100;
        //printf("llegue [%d][%d]: ganancia: '%d' monto:'%d' antiguedad:'%d' \n",y ,x ,listaVendedores[x].ganancia[listaVentas[y].mm-1],listaVentas[y].monto,listaVendedores[x].antiguedad );
      }
    }
  }
}

void imprimirResultados(vendedor_t* lista, int cont_vendedores){
  for(int x = 0; x <= cont_vendedores-1; x++){
    printf("\n\nVendedor: %s\n\n",lista[x].nombre);
    for(int i = 0; i <= 11; i++){
      printf("Ganancia del Mes[%d]: $%d\n",i+1, lista[x].ganancia[i] );
    }
  }
}