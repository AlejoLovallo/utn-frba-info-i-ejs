#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int existeVendedor(int legajo){
    FILE *fp = fopen("vendedores.csv","r");
    int respuesta = FALSE;
    char auxVendedor[100];
    char *auxLecturaVendedor;
    int cantVendedores = 0, legajosVendedores[20];

    /**
     * if(fp == 0){
        printf("ERRROR\n");
    }else{
    
    }*
    **/
    if(fp != NULL){
        while(!feof(fp)){
            auxLecturaVendedor = fgets(auxVendedor,100,fp); //Leo de a una linea y lo guardo en un string.
            if(auxLecturaVendedor != NULL){
                strtok(auxLecturaVendedor,","); //Obtengo el nombre del vendedor
            /**
            * atoi("hola")---> no funciona
            * int x = atoi("34") --> x = 34;
            * **/
                char aux[100];
                strcpy(aux,strtok(NULL,","));
                legajosVendedores[cantVendedores] = atoi(aux); //OBTENGO LEGAJO DEL VENDEDOR.
                strtok(NULL,","); //Obtengo la antiguedad (NO ES NECESARIO HACER ESTE ULTIMO PASO)
                cantVendedores ++;
            }
        }
        fclose(fp);
    }else{
        printf("HUBO UN ERROR ABRIENDO EL ARCHIVO\n");
    }

    for(int i=0; i <= cantVendedores; i++){
        if(legajo == legajosVendedores[i]){
            printf("VENDEDOR ENCONTRADO");
            respuesta = TRUE;
        }
    }

    return respuesta;

}

void agregarVendedor(Vendedor vendedores[]){
    int legajo, antiguedad;
    char nombre[50], apellido[50];
    char auxLegajo[5];
    char auxAntiguedad[5];
    char linea[70];


    printf("Ingrese el legajo del nuevo vendedor\n");
    scanf("%d",&legajo);

    //Me fijo si existe o no
    int existe = existeVendedor(legajo);

    //Si existe, informo del error
    if(existe == TRUE){
        printf("EL VENDEDOR YA EXISTE\n");
        return;
    }

    //Si existe, cargamos el resto de los datos
    printf("Ingrese el NOMBRE del nuevo vendedor: \n");
    scanf("%s", nombre ); //Pepe

    strcat(nombre," "); //Pepe _

    printf("Ingrese el APELLIDO del nuevo vendedor: \n");
    scanf("%s", apellido ); //Pepe _ Argento

    strcat(nombre,apellido);
    //OBTENGO NOMBRE COMPLETO

    printf("Ingrese el ANTIGUEDAD (años) del nuevo vendedor: \n");
    scanf("%d", &antiguedad );

    printf("-------------------------------------------------------------------\n");

    FILE *fp = fopen("vendedores.csv","a+"); //ABRO EL ARCHIVO POSICIONADOME EN EL FINAL DEL ARCHIVO.

    if(fp != NULL){
        /**
         *  strcpy(string_destino,string_origen);
            sprintf(string_destino,<FORMA DE TRABAJO IGUAL QUE PRINTF>)
        **/
       sprintf(auxLegajo,"%d",legajo);
       sprintf(auxAntiguedad,"%d",antiguedad);

       strcpy(linea,"");
       strcat(linea,nombre); //YA TENGO EL NOMBRE COMPLETO POR LO QUE HICE ANTES
       strcat(linea,","); //Pepe Argento,
       strcat(linea,auxLegajo); //Pepe Argento,11111
       strcat(linea,","); //....
       strcat(linea,auxAntiguedad);  //...
       
       /**
        * fputs(string,file*fp);
        * 
        * while(fputs(linea,fp)==EOF){
        *   printf("ERROR AL ESCRIBIR, REINTETANDO");
        * }
        * 
        * */
       fputs("\n",fp);
       fputs(linea,fp);

       printf("VENDEDOR CARGADO\n");
       fclose(fp);
    }else{
        printf("HUBO UN ERRO AL ABRIR EL ARCHIVO\n");
        return;
    }
    return;
}


void agregarVenta(){
    int legajo, aaaa, mm, dd, cant,monto;
    char nombreArchivo[50], auxAnio[10],auxMes[10], auxDia[10], aux[50];
    char auxLegajo[10], auxMonto[10], auxCantidad[10];
    char linea[100];

    printf("Ingrese el legajo del vendedor a cargar la venta\n");
    scanf("%d",&legajo);


    //Me fijo si existe o no
    int existe = existeVendedor(legajo);

    //Si existe, informo del error
    if(existe == FALSE){
        printf("EL VENDEDOR NO EXISTE\n");
        return;
    }

      printf("Ingrese el año - mes - dia en el que se realizo la venta:\n");
      scanf("%d %d %d", &aaaa, &mm, &dd );
      printf("Ingrese la cantidad de articulos vendidos:\n");
      scanf("%d", &cant );
      printf("Ingrese el monto asociado a la venta:\n");
      scanf("%d", &monto );
      printf("-------------------------------------------------------------------\n");

      if (monto > 0 && cant > 0 && dd > 0 && dd <= 31 && mm > 0 && mm <= 12 && aaaa > 2000){
        printf("Todos los datos son validos!\n");
      }else{
        printf("ERROR! Alguno de los datos ingresado es invalido.\n");
        return;
      }
      /**
      * 2021 09 04
      * "20210904.csv"
      **/
     sprintf(auxAnio,"%.4d",aaaa);
     sprintf(auxMes,"%.2d",mm);
     sprintf(auxDia,"%.2d",dd);
     printf("no hay error\n");

     strcpy(nombreArchivo,calcularPath(auxAnio,auxMes,auxDia,aux));

     FILE *fp = fopen(nombreArchivo,"a+");

     if(fp != NULL){
         sprintf(auxCantidad,"%d",cant);
         sprintf(auxMonto,"%d",monto);
         sprintf(auxLegajo,"%d",legajo);
         strcpy(linea,"");
         strcat(linea,auxCantidad);
         strcat(linea,",");
         strcat(linea,auxMonto);
         strcat(linea,",");
         strcat(linea,auxLegajo);

        fputs(linea,fp);
        fputs("\n",fp);
        printf("VENTA CARGADA EXITOSAMENTE\n");
        fclose(fp);
     }else{
         printf("ERROR: %s\n",nombreArchivo);
         return;
     }

    return;
}

char* calcularPath(char anio[],char mes[],char dia[],char path[]){
    char aux[50];
    strcpy(aux,"");
    strcat(aux,anio);
    strcat(aux,mes);
    strcat(aux,dia);
    strcat(aux,".csv"); //AAAAMMDD.csv
    strcpy(path,aux);
    return path;
}

void obtenerVendedores(Vendedor vendedores[],int *cant_vendedores){
    char auxVendedor[100];
    char *auxLecturaVendedor;
    *cant_vendedores = 0;

    FILE *fp = fopen("vendedores.csv","r");


    if(fp!=NULL){
        while(!feof(fp)){
            auxLecturaVendedor = fgets(auxVendedor,100,fp); //Leo de a una linea y lo guardo en un string.            
            if(auxLecturaVendedor != NULL){
                strcpy(vendedores[*cant_vendedores].nombre,strtok(auxLecturaVendedor,",")); //OBTENGO EL NOMBRE

                char aux[100];
                strcpy(aux,strtok(NULL,","));
                vendedores[*cant_vendedores].legajo = atoi(aux); //OBTENGO LEGAJO DEL VENDEDOR.

                strcpy(aux,strtok(NULL,","));
                vendedores[*cant_vendedores].antiguedad = atoi(aux);

                (*cant_vendedores)++;
            }
        }
     printf("--- LEI UN TOTAL DE %d VENDEDORES",*cant_vendedores);
     fclose(fp);
    }else{
        printf("ERROR AL ABRIR EL ARCHIVO\n");
    }
}

void buscarVentas(Venta ventas[],int aaaa,int mm,int *cant_ventas){
    FILE *fp;
    char auxAnio[5], auxMes[5], auxDia[5], nombreArchivo[50], auxPath[50];
    *cant_ventas = 0;
    char auxVenta[100], aux[100];
    char *auxLecturaVenta;

    sprintf(auxAnio,"%.4d",aaaa);
    sprintf(auxMes,"%.2d",mm);


    for(int dia = 1; dia <= 31; dia ++){
        sprintf(auxDia,"%.2d",dia);
        strcpy(nombreArchivo,calcularPath(auxAnio,auxMes,auxDia,auxPath));
        fp = fopen(nombreArchivo,"r");

        //NOS PREGUNTAMOS SI EXISTE O NO EL ARCHIVO
        if(fp != NULL){
            printf("NOMBRE DEL ARCHIVO ENCONTRADO %s \n",nombreArchivo);
            while(!feof(fp)){
                auxLecturaVenta = fgets(auxVenta,100,fp);
                if(auxLecturaVenta != NULL){
                    strcpy(aux,strtok(auxLecturaVenta,","));//OBTUVE CANT PRODUCTOS
                    ventas[*cant_ventas].cantProductos = atoi(aux);
                    strcpy(aux,strtok(NULL,","));
                    ventas[*cant_ventas].montoTotal = atoi(aux);
                    strcpy(aux,strtok(NULL,","));
                    ventas[*cant_ventas].legajo = atoi(aux);
                    (*cant_ventas)++;
                }
            }
            fclose(fp);
        }

    }   

}

void inicializarGanancias(Vendedor vendedores[],int *cont){
  for(int i = 0; i < (*cont);i++){
    for(int j= 0; j < 12; j++){
      vendedores[i].ganancia[j] = 0;
    }
  }
}

/**
 * 
 * ITERACION  CALCULO COMISIONES
PRIMERO VENTAS
SEGUNDO VENDEDORES
1111 == 4323 NO
1111 == 3428 NO
SIGO...

PRIMERO VENDEDORES
SEGUNDO VENTAS
4323 == 1111 NO
3428 == 1111 NO
**/

void calcularComisiones(Venta ventas[],Vendedor vendedores[],int cant_ventas,int cant_vendedores,int mes){
    for(int y = 0; y < cant_ventas  ; y++){
        for(int x = 0; x < cant_vendedores ; x++){
            //NOS PREGUNTAMOS SI COINCIDEN LOS LEGAJOS DE LAS VENTAS CON LOS DE LOS VENDEDORES
            if(ventas[y].legajo == vendedores[x].legajo){
                //PORQUE EL ARRAY VA DE 0-11 meses con 0 Como ENERO
                // COMISION POR VENT =  MONTO * (ANTIGUEDAD / 100)
                vendedores[x].ganancia[mes-1] += ventas[y].montoTotal * (vendedores[x].antiguedad / 100);
            }
        }
    }
}

void imprimirResultados(){
    return ;
}

void filtrarVentas(Venta ventas[],Vendedor vendedores[]){
    int aaaa,mm, cant_vendedores, cant_ventas;

    printf("Ingrese el año por el que quiera filtrar:\n");
    scanf("%d", &aaaa );
    printf("Ingrese el mes por el que quiera filtrar:\n");
    scanf("%d", &mm );
    printf("-------------------------------------------------------------------\n");

    //Obtengo vendedores
    obtenerVendedores(vendedores,&cant_vendedores);

    //BUSCAR VENTAS
    buscarVentas(ventas,aaaa,mm,&cant_ventas);

    //CALCULAR COMISIONES
    inicializarGanancias(vendedores,&cant_vendedores);
    calcularComisiones(ventas,vendedores,cant_ventas,cant_vendedores,mm);

    //ImprimirResultados
    imprimirResultados(vendedores,mm);

    return;
}


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