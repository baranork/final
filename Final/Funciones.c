#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones.h"
#include "LinkedList.h"

int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = 1;
    int contador = 0;
    FILE* f;

    f = fopen(path, "r");

    if(f != NULL)
    {
        parser_ePeliculaFromText(f, pArrayListEmployee);
        retorno = 0;
    }

    //fread(pArrayListEmployee, sizeof(LinkedList), 4, f);
    fclose(f);
    return retorno;
}

int parser_ePeliculaFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    char id[4];
    char anio[5];
    char genero[20];
    char nombre[70];
    int r;
    ePelicula* unaPelicula = ePelicula_new();

    fscanf(pFile, "%[^,],%[^,],%[^\n]\n", id, nombre, anio, genero);

    do
    {
        r = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, anio, genero);
        if(r==4)
        {
            unaPelicula=ePelicula_newParametros(id, nombre, anio, genero);
            ll_add(pArrayListEmployee,unaPelicula);
        }
    }
    while(!feof(pFile));


    return 1;
}



ePelicula* ePelicula_new()
{
    ePelicula* unaPelicula;
    unaPelicula=(ePelicula*)malloc(sizeof(ePelicula));
    if(unaPelicula==NULL)
    {
        printf("\nNo hay espacio suficiente.\n");
        system("pause");
    }
    return unaPelicula;
}

ePelicula* ePelicula_newParametros(char* idStr,char* nombreStr,char* anioStr, char* generoStr)
{
    int id;
    int anio;

    ePelicula* unaPelicula=ePelicula_new();

    id = atoi(idStr);
    anio = atoi(anioStr);
    int ra, rb, rc, rd;

    if(unaPelicula != NULL)
    {
        ra = ePelicula_setId(unaPelicula, id);
        rb = ePelicula_setNombre(unaPelicula, nombreStr);
        rc = ePelicula_setAnio(unaPelicula, anio);
        rd = ePelicula_setGenero(unaPelicula, generoStr);
    }
    /*if(ra==1 || rb==1 || rc==1 || rd==1)
    {
        printf("Hubo un error con la carga de datos. Por favor, intentelo de nuevo");
    }*/

    return unaPelicula;
}



int ePelicula_setId(ePelicula* this,int id)
{
    int r = 1;

    if(id>0 && this!=NULL)
    {
        this->id = id;
        r = 0;
    }

    return r;
}
int ePelicula_getId(ePelicula* this,int* id)
{
    int r = 1;

    if(this != NULL)
    {
        *id = this->id;
        r = 0;
    }
    return r;
}







int ePelicula_setNombre(ePelicula* this,char* nombre)
{
    int r = 1;

    if(this!=NULL)
    {
        strcpy(this->nombre, nombre);
        r = 0;
    }

    return r;
}


int ePelicula_getNombre(ePelicula* this, char* nombre)
{
    int r = 1;

    if(this!=NULL)
    {
        strcpy(nombre, this->nombre);
        r = 0;
    }

    return r;
}



int ePelicula_setAnio(ePelicula* this,int anio)
{
    int r = 1;


    if(anio>0 && this!=NULL)
    {
        this->anio = anio;
        r = 0;
    }

    return r;
}
int ePelicula_getAnio(ePelicula* this,int* anio)
{
    int r = 1;

    if(this != NULL)
    {
        *anio = this->anio;
        r = 0;
    }
    return r;
}


int ePelicula_setGenero(ePelicula* this,char* genero)
{
    int r = 1;

    if(this!=NULL)
    {
        strcpy(this->genero, genero);
        r = 0;
    }

    return r;
}


int ePelicula_getGenero(ePelicula* this, char* genero)
{
    int r = 1;

    if(this!=NULL)
    {
        strcpy(genero, this->genero);
        r = 0;
    }

    return r;
}

int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int id;
    char nombre[70];
    char genero[50];
    int anio;
    int len;
    int i;
    int contador = 0;

    ePelicula* peliculaAMostrar;

    len = ll_len(pArrayListEmployee);

    printf("ID   NOMBRE                                               ANIO    GENERO   \n");

    for(i=0; i<len; i++)
    {
        peliculaAMostrar = ll_get(pArrayListEmployee, i);
        if(peliculaAMostrar!=NULL)
        {
            ePelicula_getId(peliculaAMostrar, &id);
            ePelicula_getNombre(peliculaAMostrar, nombre);
            ePelicula_getAnio(peliculaAMostrar, &anio);
            ePelicula_getGenero(peliculaAMostrar, genero);
            printf("%-2d - %-50s - %4d - %4s \n", id, nombre, anio, genero);
            contador++;
        }

    }


    return 1;
}

int ePelicula_CompareByID(void* e1,void* e2)
{
    int r=-1;
    ePelicula* pelicula1;
    ePelicula* pelicula2;

    if(e1!=NULL && e2!=NULL)
    {
        pelicula1=(ePelicula*)e1;
        pelicula2=(ePelicula*)e2;
        if(pelicula1->id > pelicula2->id)
        {
            r = 1;
        }
        else if(pelicula1->id == pelicula2->id)
        {
            r = 0;
        }
    }
    return r;

}


int depurarPeliculas(LinkedList* this)
{
    int returnAux =-1;
    int i;
    int j;
    Node* aux;
    Node* element1;
    Node* element2;
    ePelicula* pelicula1;
    ePelicula* pelicula2;


    for(i=0; i<(ll_len(this)-1); i++)
    {
        element1=ll_get(this,i);

        for(j=i+1; j<ll_len(this); j++)
        {
            element2=ll_get(this,j);


            pelicula1=(ePelicula*)element1;
            pelicula2=(ePelicula*)element2;
            if(pelicula1->id == pelicula2->id)
            {
                strcat(pelicula1->genero, "|");
                strcat(pelicula1->genero, pelicula2->genero);
                ll_pop(this, ll_indexOf(this, pelicula2));
            }

        }
    }
}


int agruparPorGenero(void* e1, char genero){
    int r=-1;
    ePelicula* pelicula1;
    ePelicula* pelicula2;

    pelicula1=(ePelicula*)e1;
    if(strcmp(pelicula1->genero, genero)==0){
        r = 0;
    }
    return r;

}
