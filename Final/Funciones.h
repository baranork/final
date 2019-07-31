#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


typedef struct
{
    int id;
    char nombre[128];
    int anio;
    char genero[70];
}ePelicula;

int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee);
int parser_ePeliculaFromText(FILE* pFile , LinkedList* pArrayListEmployee);
ePelicula* ePelicula_new();
ePelicula* ePelicula_newParametros(char* idStr,char* nombreStr,char* anioStr, char* generoStr);
int ePelicula_CompareByID(void* e1,void* e2);




