/**
 * Hecho por Emilly Sancho y Daniegl Bogarin
 * para TI2402 - Algoritmos y estructuras de datos
 * Profesora: Maria Jose Artavia.
 * IS 2020 - Proyecto 2 - 29/07/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>     

#define NOMBRE_SIZE 50
#define PROVINCIA_SIZE 50
//--------------- DEFINICION DE ESTRUCTURAS
typedef struct nodoVertice nodoVertice;
typedef struct nodoArista nodoArista;

//--------------------------------------ARISTA
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

void mostrarAristas(listaAristas *A, char v[NOMBRE_SIZE]){
	
	for(nodoArista *i = A->inicio; i!=NULL; i=i->siguiente){
		printf("\t\t-> %s, tiempo: %i.\n", i->destino, i->tiempo);
	}
}


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

//--------------------------------------VERTICE
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

void mostrarVertices(listaVertices *V){
	printf("\tVertices:\n");
	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
		printf("\t%s, %s, población: %i.\n", i->nombre, i->provincia, i->poblacion);
	}
}

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


//--------------- MAIN Y PRUEBAS
int main()
{
	int accion;
	listaVertices *V;
	V = listaVerticesNueva();

	nodoVertice tempVertice;
	nodoArista tempArista; 
	int pasajerosMinimosTren, pasajerosMinimosBus, pasajerosMinimosTaxi, pasajerosMinimosVehiculo = 0;
	int pasajerosMaximosTren, pasajerosMaximosBus, pasajerosMaximosTaxi, pasajerosMaximosVehiculo = 0;
	int simulacionesTren, simulacionesBus, simulacionesTaxi, simulacionesVehiculo = 0;

//--------------	EJEMPLOS 
	{
	listaAristas *g = listaAristasNueva(); 
	listaAristas *u = listaAristasNueva();
	listaAristas *lc = listaAristasNueva();
	listaAristas *t = listaAristasNueva();
	listaAristas *sc = listaAristasNueva();
	listaAristas *p = listaAristasNueva();
	listaAristas *sr = listaAristasNueva();
	listaAristas *lf = listaAristasNueva();
	
	nodoVertice gv;
	nodoVertice uv;
	nodoVertice lcv;
	nodoVertice tv;
	nodoVertice scv;
	nodoVertice pv;
	nodoVertice srv;
	nodoVertice lfv;

	strcpy(gv.nombre,"Guatuso"); strcpy(gv.provincia,"Alajuela"); gv.poblacion = 12000; gv.aristas = g;
	strcpy(uv.nombre,"Upala"); strcpy(uv.provincia,"Alajuela"); uv.poblacion = 13000; uv.aristas = u;
	strcpy(lcv.nombre,"Los Chiles"); strcpy(lcv.provincia,"Alajuela"); lcv.poblacion = 14000; lcv.aristas = lc; 
	strcpy(tv.nombre,"Tilaran"); strcpy(tv.provincia,"Guanacaste"); tv.poblacion = 15000; tv.aristas = t;
	strcpy(scv.nombre,"San Carlos"); strcpy(scv.provincia,"Alajuela"); scv.poblacion = 16000; scv.aristas = sc;
	strcpy(pv.nombre,"Pital"); strcpy(pv.provincia,"Alajuela"); pv.poblacion = 17000; pv.aristas = p;
	strcpy(srv.nombre,"San Ramon"); strcpy(srv.provincia,"Alajuela"); srv.poblacion = 18000; srv.aristas = sr;
	strcpy(lfv.nombre,"La Fortuna"); strcpy(lfv.provincia,"Alajuela"); lfv.poblacion = 19000; lfv.aristas = lf;

	insertarVertice(V,gv);
	insertarVertice(V,uv);
	insertarVertice(V,lcv);
	insertarVertice(V,tv);
	insertarVertice(V,scv);
	insertarVertice(V,pv);
	insertarVertice(V,srv);
	insertarVertice(V,lfv);

	nodoArista g_t; strcpy(g_t.origen,"Guatuso"); strcpy(g_t.destino,"Tilaran"); g_t.tiempo = 10; g_t.distancia = 80; 
	nodoArista g_u; strcpy(g_u.origen,"Guatuso"); strcpy(g_u.destino,"Upala"); g_u.tiempo = 5; g_u.distancia = 40;
	nodoArista t_lc; strcpy(t_lc.origen,"Tilaran"); strcpy(t_lc.destino,"Los Chiles"); t_lc.tiempo = 6; t_lc.distancia = 120;
	nodoArista t_sc; strcpy(t_sc.origen,"Tilaran"); strcpy(t_sc.destino,"San Carlos"); t_sc.tiempo = 9; t_lc.distancia = 90;
	nodoArista t_sr; strcpy(t_sr.origen,"Tilaran"); strcpy(t_sr.destino,"San Ramon"); t_sr.tiempo = 14; t_lc.distancia = 60;
	nodoArista sr_g; strcpy(sr_g.origen,"San Ramon"); strcpy(sr_g.destino,"Guatuso"); sr_g.tiempo = 2; sr_g.distancia = 95;
	nodoArista sr_lf; strcpy(sr_lf.origen,"San Ramon"); strcpy(sr_lf.destino,"La Fortuna"); sr_lf.tiempo = 12; sr_lf.distancia = 35;
	nodoArista sc_g; strcpy(sc_g.origen,"San Carlos"); strcpy(sc_g.destino,"Guatuso"); sc_g.tiempo = 3; sc_g.distancia = 80;
	nodoArista sc_p; strcpy(sc_p.origen,"San Carlos"); strcpy(sc_p.destino,"Pital"); sc_p.tiempo = 4; sc_p.distancia = 40;
	nodoArista sc_sr; strcpy(sc_sr.origen,"San Carlos"); strcpy(sc_sr.destino,"San Ramon"); sc_sr.tiempo = 9; sc_sr.distancia = 30;
	nodoArista u_sc; strcpy(u_sc.origen,"Upala"); strcpy(u_sc.destino,"San Carlos"); u_sc.tiempo = 5; u_sc.distancia = 120;
	nodoArista u_lf; strcpy(u_lf.origen,"Upala"); strcpy(u_lf.destino,"La Fortuna"); u_lf.tiempo = 9; u_lf.distancia = 85;
	nodoArista u_lc; strcpy(u_lc.origen,"Upala"); strcpy(u_lc.destino,"Los Chiles"); u_lc.tiempo = 7; u_lc.distancia = 15;
	nodoArista lf_sc; strcpy(lf_sc.origen,"La Fortuna"); strcpy(lf_sc.destino,"San Carlos"); lf_sc.tiempo = 6; lf_sc.distancia = 30;
	nodoArista p_u; strcpy(p_u.origen,"Pital"); strcpy(p_u.destino,"Upala"); p_u.tiempo = 1; p_u.distancia = 150;
	nodoArista p_lf; strcpy(p_lf.origen,"Pital"); strcpy(p_lf.destino,"La Fortuna"); p_lf.tiempo = 15; p_lf.distancia = 70;
	nodoArista lc_p; strcpy(lc_p.origen,"Los Chiles"); strcpy(lc_p.destino,"Pital"); lc_p.tiempo = 3; lc_p.distancia = 45;

	insertarArista(gv.aristas, g_t);
	insertarArista(gv.aristas, g_u);
	insertarArista(tv.aristas, t_lc);
	insertarArista(tv.aristas, t_sc);
	insertarArista(tv.aristas, t_sr);
	insertarArista(srv.aristas, sr_g);
	insertarArista(srv.aristas, sr_lf);
	insertarArista(scv.aristas, sc_g);
	insertarArista(scv.aristas, sc_p);
	insertarArista(scv.aristas, sc_sr);
	insertarArista(uv.aristas, u_sc);
	insertarArista(uv.aristas, u_lf);
	insertarArista(uv.aristas, u_lc);
	insertarArista(lfv.aristas, lf_sc);
	insertarArista(pv.aristas, p_u);
	insertarArista(pv.aristas, p_lf);
	insertarArista(lcv.aristas, lc_p);
	}
//-----------------------------------------------------
	while(free){
		printf("\n*** Menu principal: *** \n");
		printf("1\t Construcion y edicion del grafo\n");
		printf("2\t Configuracion inicial\n");
		printf("3\t Simulacion\n");
		printf("4\t Estadisticas\n");
		printf("0\t Salir.\n");
		printf("\nSeleccione una accion de menu realizar: ");
		scanf("%i", &accion);
			if(accion == 0 || accion > 4){
				break;
			}
			
			if(accion == 1){
				printf("\n*** Menu del GRAFO: *** \n");
				printf("1\t Crear VERTICE.\n");
				printf("2\t Eliminar VERTICE.\n");
				printf("3\t Mostrar lista de vertices.\n");
				printf("4\t Crear ARISTA.\n");
				printf("5\t Eliminar ARISTA.\n");
				printf("6\t Mostrar lista de aristas.\n");
				printf("0\t Salir del grafo.\n");

				while(free){
				printf("\nSeleccione una accion de grafo a realizar: ");
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
					}//fin accion 1 del grafo

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
					}//fin accion 2 del grafo

					if(accion == 3){
						mostrarVertices(V);
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
				
					}//fin accion 4 del grafo
					
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
						
					}//fin accion 5 del grafo

					if(accion == 6){
						printf("\n\tAristas por vertice:\n");
						for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
							if(i->aristas->inicio != NULL){
								printf("\t%s:\n", i->nombre);
								mostrarAristas(i->aristas,i->nombre);
							}
							
						}
					} //fin accion 6 del grafo
				}//fin del while del grafo
			}//fin if accion 1 del menu principal

			if(accion == 2){
				printf("\n*** Menu de Configuracion: ***\n");
				printf("\tInserte la cantidad MINIMA de pasajeros para el TREN: ");
				scanf("%i", &pasajerosMinimosTren);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el TREN: ");
				scanf("%i", &pasajerosMaximosTren);	
				printf("\tInserte la cantidad MINIMA de pasajeros para el BUS: ");
				scanf("%i", &pasajerosMinimosBus);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el BUS: ");
				scanf("%i", &pasajerosMaximosBus);
				printf("\tInserte la cantidad MINIMA de pasajeros para el TAXI: ");
				scanf("%i", &pasajerosMinimosTaxi);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el TAXI: ");
				scanf("%i", &pasajerosMaximosTaxi);
				printf("\tInserte la cantidad MINIMA de pasajeros para el VEHICULO: ");
				scanf("%i", &pasajerosMinimosVehiculo);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el VEHICULO: ");
				scanf("%i", &pasajerosMaximosVehiculo);
				printf("\tGRACIAS!\n");
			}//fin accion 3 del menu principal
			
			if(accion == 3){ 
				//METER AQUI EL CODIGO DE LA SIMULACION

			}

	}//fin while del menu principal

	return 0;
}
