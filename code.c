/**
 * Hecho por Emilly Sancho y Daniegl Bogarin
 * para TI2402 - Algoritmos y estructuras de datos
 * Profesora: Maria Jose Artavia.
 * IS 2020 - Proyecto 2 - 29/07/2020
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <vector>     
using namespace std;
#define NOMBRE_SIZE 50
#define PROVINCIA_SIZE 50

//--------------- DEFINICION-DE-ESTRUCTURAS----------//
typedef struct nodoVertice nodoVertice;
typedef struct nodoArista nodoArista;

//----------------------ARISTA----------------------//
struct nodoArista
{
	char origen[NOMBRE_SIZE];
	char destino[NOMBRE_SIZE];
	int tiempo;
	int distancia;	
	nodoArista *siguiente;
};

typedef struct listaAristas
{
	nodoArista *inicio;
}listaAristas;

listaAristas *listaAristasNueva(){
	listaAristas *A;
	A = (listaAristas*)malloc(sizeof(listaAristas));
	A->inicio = NULL;
	return A;
}

void insertarArista(listaAristas *A, nodoArista a){
	nodoArista *n, *aux;
	if(A->inicio == NULL){
		A->inicio = (nodoArista*)malloc(sizeof(nodoArista));
		strcpy(A->inicio->origen, a.origen);
		strcpy(A->inicio->destino, a.destino);
		A->inicio->tiempo = a.tiempo;
		A->inicio->distancia = a.distancia;
		A->inicio->siguiente = NULL;
	}	
	else{
		n = A->inicio;
		while(n!=NULL){
			aux = n;
			n = n->siguiente;
		}
		aux->siguiente = (nodoArista*)malloc(sizeof(nodoArista));
		strcpy(aux->siguiente->origen, a.origen);
		strcpy(aux->siguiente->destino,a.destino); 
		aux->siguiente->tiempo = a.tiempo;
		aux->siguiente->distancia = a.distancia;
		aux->siguiente->siguiente = NULL;

	}
}

//void mostrarAristas(listaAristas *A, char v[NOMBRE_SIZE]){
	
//	for(nodoArista *i = A->inicio; i!=NULL; i=i->siguiente){
//		printf("\t\t-> %s, tiempo: %i.\n", i->destino, i->tiempo);
//	}
//}


int eliminarArista(listaAristas *A, char d[NOMBRE_SIZE]){
	nodoArista *a, *anterior = NULL;
	a = A->inicio; 

	if(A->inicio == NULL){
		return 1;
	}
	if(strcmp(A->inicio->destino, d)==0){
		A->inicio = A->inicio->siguiente;
		free(a);
		return 0;
	}

	else{
		anterior = A->inicio;
		a = anterior->siguiente;

		while(a!=NULL){
			if(strcmp(a->destino,d)==0 ){
				anterior->siguiente = a->siguiente;
				free(a);
				return 0;
				break;
			}
			if(strcmp(a->destino,d)==0 && a->siguiente == NULL){
				anterior->siguiente = NULL;
				return 0;
				break;
			}
			else{
				anterior = a;
				a = a->siguiente;
			}
		}

	return 1;

	}
}

//-------------VERTICE------------//
struct nodoVertice
{
	char nombre[NOMBRE_SIZE];
	char provincia[PROVINCIA_SIZE];
	int poblacion;	
	listaAristas *aristas;
	nodoVertice *siguiente;
};

typedef struct listaVertices
{
	nodoVertice *inicio;
}listaVertices;

listaVertices *listaVerticesNueva(){
	listaVertices *V;
	V = (listaVertices*)malloc(sizeof(listaVertices));
	V->inicio = NULL;
	return V;
}

void insertarVertice(listaVertices *V, nodoVertice v){
	nodoVertice *n, *aux;
	if(V->inicio == NULL){
		V->inicio = (nodoVertice*)malloc(sizeof(nodoVertice));
		strcpy(V->inicio->nombre, v.nombre);
		strcpy(V->inicio->provincia, v.provincia);
		V->inicio->poblacion = v.poblacion;
		V->inicio->aristas = v.aristas;
		V->inicio->siguiente = NULL;
	}	
	else{
		n = V->inicio;
		while(n!=NULL){
			aux = n;
			n = n->siguiente;
		}
		aux->siguiente = (nodoVertice*)malloc(sizeof(nodoVertice));
		strcpy(aux->siguiente->nombre, v.nombre);
		strcpy(aux->siguiente->provincia, v.provincia);
		aux->siguiente->poblacion = v.poblacion;
		aux->siguiente->aristas = v.aristas;
		aux->siguiente->siguiente = NULL;
	}
}

//void mostrarVertices(listaVertices *V){
//	printf("\tVertices:\n");
//	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
//		printf("\t%s, %s, población: %i.\n", i->nombre, i->provincia, i->poblacion);
//	}
//}

nodoVertice* consultarVertice(listaVertices *V, char n[NOMBRE_SIZE]){
	nodoVertice *v = V->inicio;
	while(v!=NULL){
		if(strcmp(v->nombre,n)==0){
			return v;
		}
		v = v->siguiente;
	}
	printf("\n\t****ERROR****\n\t%s no existe como vertice, por favor insertelo. \n", n );
	return NULL;
}

int eliminarVertice(listaVertices *V, char n[NOMBRE_SIZE], char p[PROVINCIA_SIZE]){
	nodoVertice *v, *anterior = NULL;
	v = V->inicio; 

	
	if(strcmp(V->inicio->nombre,n)==0 && strcmp(V->inicio->provincia,p)==0){
		V->inicio = V->inicio->siguiente;
		free(v);
		return 0;
	}

	else{
		anterior = V->inicio;
		v = anterior->siguiente;

		while(v!=NULL){
			if(strcmp(v->nombre,n)==0 && strcmp(v->provincia,p)==0){
				anterior->siguiente = v->siguiente;
				free(v);
				return 0;
				break;
			}
			if(strcmp(v->nombre,n)==0 && strcmp(v->provincia,p)==0 && v->siguiente == NULL){
				anterior->siguiente = NULL;
				return 0;
				break;
			}
			else{
				anterior = v;
				v = v->siguiente;
			}
		}

	return 1;

	}

}
//-------------HEAD--MAX-----------//
void swap(int*a,int*b)
{
  int temp=*b;
  *b=*a;
  *a =temp;
}
void heapify(vector<int> &hT, int i)
{
  int size = hT.size();
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < size && hT[l]>hT[largest])
    largest = l;
  if (r < size && hT[r] > hT[largest])
    largest = r;

  if (largest!=i)
  {
    swap(&hT[i], &hT[largest]);
    heapify(hT, largest);
  }
}
void insert(vector<int> &hT, int newNum)
{
  int size = hT.size();
  if (size == 0)
  {
    hT.push_back(newNum);
  }
  else
  {
    hT.push_back(newNum);
    for (int i = size / 2 - 1; i >= 0; i--)
    {
      heapify(hT, i);
    }
  }
}

void printArray(vector<int> &hT)
{
  for (int i = 0; i < hT.size(); ++i)
    cout << hT[i] << " ";
  cout<<"\n";
}

//----------- MAIN--Y--PRUEBAS------------//
int main()
{
	  vector<int> heapTree;

  insert(heapTree, 3);
  insert(heapTree, 4);
  insert(heapTree, 9);
  insert(heapTree, 5);
  insert(heapTree, 2);

  cout << "Max-Heap array: ";
  printArray(heapTree);
	int accion;
	listaVertices *V;
	V = listaVerticesNueva();

	nodoVertice tempVertice;
	nodoArista tempArista; 

	printf("\n*** Menu principal: *** \n");
	printf("1\t Crear VERTICE.\n");
	printf("2\t Eliminar VERTICE.\n");
	printf("3\t Mostrar lista de vertices.\n");
	printf("4\t Crear ARISTA.\n");
	printf("5\t Eliminar ARISTA.\n");
	printf("6\t Mostrar lista de aristas.\n");
	printf("0\t Salir.\n");
	

	while(free){
		printf("\nSeleccione una accion a realizar: ");
		scanf("%i", &accion);
		if(accion == 0 || accion > 6){
			break;
		}

		if(accion == 1){
			listaAristas *A;
			A = listaAristasNueva(); 
			tempVertice.aristas = A;

			printf("\tInserte el NOMBRE del vertice a crear: ");
			fgets(tempVertice.nombre, NOMBRE_SIZE, stdin);
			scanf("%[^\n]", tempVertice.nombre);

			printf("\tInserte la PROVINCIA del vertice: ");
			fgets(tempVertice.provincia, PROVINCIA_SIZE, stdin);
			scanf("%[^\n]", tempVertice.provincia);

			printf("\tInserte la POBLACION del vertice: ");
			scanf("%i", &tempVertice.poblacion);

			insertarVertice(V, tempVertice);
		}

		if(accion == 2){
			if(V->inicio == NULL)
			{
				printf("\t***ERROR*** \n\tNo hay vertices para borrar.\n");		
			}
			else{
				printf("\tInserte el NOMBRE del vertice a borrar: ");
				fgets(tempVertice.nombre, NOMBRE_SIZE, stdin);
				scanf("%[^\n]", tempVertice.nombre);

				printf("\tInserte la PROVINCIA del vertice: ");
				fgets(tempVertice.provincia, PROVINCIA_SIZE, stdin);
				scanf("%[^\n]", tempVertice.provincia);

				if(eliminarVertice(V,tempVertice.nombre,tempVertice.provincia) == 1){
					printf("\t***ERROR***\n\tEse vertice no existe \n");
				}
			}
		}

		if(accion == 3){
		//	mostrarVertices(V);
		}

		if(accion == 4){
			printf("\tInserte el ORIGEN de la arista: ");
			
			fgets(tempArista.origen, NOMBRE_SIZE, stdin);
			scanf("%[^\n]", tempArista.origen);
			nodoVertice *tempV = consultarVertice(V,tempArista.origen);

			if(tempV!=NULL){
				printf("\tInserte el DESTINO de la arista: ");
				fgets(tempArista.destino, NOMBRE_SIZE, stdin);
				scanf("%[^\n]", tempArista.destino);

				if(consultarVertice(V,tempArista.destino)!=NULL){
					printf("\tInserte el TIEMPO de viaje: ");
					scanf("%i", &tempArista.tiempo);

					printf("\tInserte la DISTANCIA de viaje: ");
					scanf("%i", &tempArista.distancia);
					
					insertarArista(tempV->aristas, tempArista);
				}
			}
	
		}
		if(accion == 5){
			printf("\tInserte el ORIGEN de la arista a borrar: ");
			fgets(tempArista.origen, NOMBRE_SIZE, stdin);
			scanf("%[^\n]", tempArista.origen);
			nodoVertice *tempV = consultarVertice(V,tempArista.origen);

			if(tempV!=NULL){
				printf("\tInserte el DESTINO de la arista: ");
				fgets(tempArista.destino, NOMBRE_SIZE, stdin);
				scanf("%[^\n]", tempArista.destino);

				if(consultarVertice(V,tempArista.destino)!=NULL){
					if(eliminarArista(tempV->aristas, tempArista.destino)==1){
						printf("\t***ERROR*** \n\tEsta arista no existe.\n");
					}
				}
			}
			
		}

		//if(accion == 6){
		//	printf("\n\tAristas por vertice:\n");
			//for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
			//	if(i->aristas->inicio != NULL){
			//		printf("\t%s:\n", i->nombre);
			//		mostrarAristas(i->aristas,i->nombre);
			//	}
				
		//	}
	//	}
	}

	return 0;
}
