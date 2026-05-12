#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>

using namespace std;

struct Producto {
    string codigo;
    string nombre;
    int cantidad;
    double precio;
};

int BuscarProducto(const vector<Producto>& inventario, const string& codigo) {
    for (size_t i = 0; i < inventario.size(); ++i) {
        if (inventario[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void MostrarMenu() {
    printf("      GadgetXpress - Inventario\n");
    printf("1. Agregar nuevo producto\n");
    printf("2. Listar todos los productos\n");
    printf("3. Actualizar cantidad de un producto\n");
    printf("4. Generar reporte de bajo inventario\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
}

void AgregarProducto(vector<Producto>& inventario) {
    char buffer_codigo[50];
    printf("\n--- Agregar Producto ---\n");
    printf("Ingrese el codigo: ");
    scanf("%49s", buffer_codigo);
    string codigo = buffer_codigo;

    if (BuscarProducto(inventario, codigo) != -1) {
        printf("[Error] Ya existe un producto con el codigo '%s'.\n", codigo.c_str());
        return;
    }

    Producto nuevo_producto;
    nuevo_producto.codigo = codigo;

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    char buffer_nombre[100];
    printf("Ingrese el nombre: ");
    fgets(buffer_nombre, sizeof(buffer_nombre), stdin);

    size_t len = strlen(buffer_nombre);
    if (len > 0 && buffer_nombre[len - 1] == '\n') {
        buffer_nombre[len - 1] = '\0';
    }
    nuevo_producto.nombre = buffer_nombre;

    printf("Ingrese la cantidad inicial: ");
    scanf("%d", &nuevo_producto.cantidad);

    printf("Ingrese el precio: ");
    scanf("%lf", &nuevo_producto.precio);

    inventario.push_back(nuevo_producto);
    printf("[Exito] Producto agregado correctamente al inventario.\n");
}

void ListarProductos(const vector<Producto>& inventario) {
    if (inventario.empty()) {
        printf("\n[Info] El inventario esta vacio.\n");
        return;
    }

    printf("\n--- Inventario Completo ---\n");
    printf("%-10s %-25s %-10s %-10s\n", "CODIGO", "NOMBRE", "CANTIDAD", "PRECIO");
    printf("---------------------------------------------------------\n");

    for (size_t i = 0; i < inventario.size(); ++i) {
        printf("%-10s %-25s %-10d $%.2f\n",
            inventario[i].codigo.c_str(),
            inventario[i].nombre.c_str(),
            inventario[i].cantidad,
            inventario[i].precio);
    }
}

void ActualizarCantidad(vector<Producto>& inventario) {
    char buffer_codigo[50];
    printf("\n--- Actualizar Stock ---\n");
    printf("Ingrese el codigo del producto: ");
    scanf("%49s", buffer_codigo);
    string codigo = buffer_codigo;

    int indice = BuscarProducto(inventario, codigo);

    if (indice == -1) {
        printf("[Error] El producto no existe en el inventario.\n");
        return;
    }

    int nueva_cantidad;
    printf("Producto actual: %s (Stock: %d)\n", inventario[indice].nombre.c_str(), inventario[indice].cantidad);
    printf("Ingrese la nueva cantidad total: ");
    scanf("%d", &nueva_cantidad);

    if (nueva_cantidad < 0) {
        printf("[Error] La cantidad no puede ser negativa.\n");
    }
    else {
        inventario[indice].cantidad = nueva_cantidad;
        printf("[Exito] Stock actualizado correctamente.\n");
    }
}

void GenerarReporteBajoInventario(const vector<Producto>& inventario) {
    const int kUmbralBajo = 5;
    bool encontrados = false;

    printf("\n--- Reporte: Bajo Inventario (Menos de %d unidades) ---\n", kUmbralBajo);

    for (size_t i = 0; i < inventario.size(); ++i) {
        if (inventario[i].cantidad < kUmbralBajo) {
            printf("- %s (Codigo: %s) | Quedan: %d unidades.\n",
                inventario[i].nombre.c_str(),
                inventario[i].codigo.c_str(),
                inventario[i].cantidad);
            encontrados = true;
        }
    }

    if (!encontrados) {
        printf("[Info] Todos los productos tienen un nivel de stock saludable.\n");
    }
}

int main() {
    vector<Producto> inventario;
    int opcion;

    do {
        MostrarMenu();

        if (scanf("%d", &opcion) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            opcion = 0;
        }

        switch (opcion) {
        case 1: AgregarProducto(inventario); break;
        case 2: ListarProductos(inventario); break;
        case 3: ActualizarCantidad(inventario); break;
        case 4: GenerarReporteBajoInventario(inventario); break;
        case 5: printf("\nSaliendo del sistema de GadgetXpress. Hasta pronto.\n"); break;
        default: printf("\n[Error] Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}