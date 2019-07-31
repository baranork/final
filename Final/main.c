#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Funciones.h"

int main()
{
    LinkedList* listaPeliculas = ll_newLinkedList();
        LinkedList* depurada = ll_newLinkedList();


    int r;
    int opcion;
    int t;
    char archivo[30];
    int flag = 0;


    do{
            printf("Ingrese el nombre del archivo a cargar: ");
    fflush(stdin);
    gets(&archivo);
    r = controller_loadFromText(archivo, listaPeliculas);
    fflush(stdin);

    if(r == 1){
        printf("No se ha podido cargar el archivo\n\nDesea intentarlo de nuevo?\n  1. Si\n  2. No\n");
        scanf("%d", &opcion);
        if(opcion == 2){
            exit(0);
        }
    }
    fflush(stdin);
    system("cls");
    }while(r != 0);


    do
    {
        printf("1. Listar\n2. Ordenar por ID\n3. Depurar\n4. Filtrar\n5. Salir\n6. Lista Filtrada\n");
        fflush(stdin);
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
                controller_ListEmployee(listaPeliculas);
            break;
        case 2:
                ll_sort(listaPeliculas, ePelicula_CompareByID, 1);
                controller_ListEmployee(listaPeliculas);

            break;
        case 3:
            depurarPeliculas(listaPeliculas);
            break;
        case 4:
            fflush(stdin);


                    ll_deleteLinkedList(depurada);
        LinkedList* depurada = ll_newLinkedList();
                ll_filter(listaPeliculas, depurada);

            break;
        case 6:
            controller_ListEmployee(depurada);

            break;

        }
        fflush(stdin);
        system("pause");
        system("cls");
    }while(opcion != 5);





    return 0;
}
