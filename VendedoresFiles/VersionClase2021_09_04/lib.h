typedef struct {
    char nombre[50];
    int legajo;
    int antiguedad;
    int ganancia[12]; //GANANCIA DE CADA MES
} Vendedor;

typedef struct{
    int cantProductos;
    int montoTotal;
    int legajo;
} Venta;


void agregarVendedor(Vendedor vendedores[]);
int existeVendedor(int legajo);

/**
 * OPCION 1: APROVECHO QUE YA TENGO TODOS LOS VENDEDORES GUARDADOS 
 * EN EL ARRAY
 * **/
//void agregarVenta(Vendedor vendedores[]);

/**
 * OPCION 2: 
 * VUELVO A LEER EL ARCHIVO Y CONSULTAR POR LOS LEGAJOS
 * **/
void agregarVenta();

char* calcularPath(char anio[], char mes[],char dia[],char path[]);

void filtrarVentas(Venta ventas[],Vendedor vendedores[]);

void obtenerVendedores(Vendedor vendedores[],int *cant_vendedores);

void buscarVentas(Venta ventas[],int aaaa, int mm,int *cant_ventas);

void calcularComsiones(Venta ventas[],Vendedor vendedores[],int cant_ventas,int cant_vendedores,int mes);

void inicializarGanancias(Vendedor vendedores[], int *cant_vendedores);

void imprimirResultados(Vendedor vendedores[],int mes);