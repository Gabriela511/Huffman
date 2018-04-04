/**********************************************************
		A L G O R I T M O   D E   H U F F M A N 
     	  BY: Gabriela Alejandra Pérez Arteaga
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

	int cont=0;
typedef struct datos nodo;

struct datos{
    char letra;
	int frecuencia;
	nodo *siguiente;
	nodo *izq;
	nodo *der;
};

struct cola{
	nodo *delante;
	nodo *atras;
};


/**********************************************************
FUNCIONES : Cola dinamica a prioridad
BY: Gabriela Alejandra Pérez Arteaga
**********************************************************/

nodo *nuevo(char letra, int frecuencia){
    nodo *q=(nodo*)malloc(sizeof(nodo));
        if(!q) perror("No hay memoria");
    q->letra=letra;
    q->frecuencia=frecuencia;
    return q;
}


void encolar(struct cola *q, char letra, int frecuencia, nodo *p, int op){
    /*CREA NODOS NUEVOS */
    if(op==1){
    	nodo *aux=nuevo(letra, frecuencia);
    aux->siguiente=NULL;
    if(q->delante==NULL)        //formar al primer elemento
        q->delante=aux;
    else
        (q->atras)->siguiente=aux;
    q->atras=aux;           //apuntador apunta al ultimo elemento
	}
	/*UTILIZA EL ARBOL*/
	if(op==2){
		nodo *aux = p;
		aux->siguiente=NULL;
		if(q->delante==NULL)        //formar al primer elemento
       		q->delante=aux;
   		else
        	(q->atras)->siguiente=aux;
    	q->atras=aux;  
	}
}

/* FUNCION NUEVA*/
nodo *desencolar(struct cola *q){				//desencola y forma en arbol. regresa nodo desencolado
	nodo *temp;
	if(q->delante!=NULL){
		temp = q->delante;
		q->delante = (q->delante)->siguiente;

	}else 		printf(" Cola vacía ");
	return temp;
}
/* FIN FUNCION NUEVA*/ 

void ordenarpriori(struct cola *q){
    nodo *aux1, *aux2;
    nodo *izq_aux, *der_aux;
    int p_aux;
    char c_aux;

    aux1=q->delante;
    while(aux1->siguiente != NULL){
        aux2=aux1->siguiente;
        while(aux2!=NULL){
            if(aux1->frecuencia > aux2->frecuencia){
                p_aux=aux1->frecuencia;			//	ENTERO
                c_aux=aux1->letra;      // CARACTER
                izq_aux = aux1->izq;
                der_aux = aux1->der;

                aux1->frecuencia = aux2->frecuencia;
                aux1->letra = aux2->letra;        //caracter
                aux1->izq = aux2->izq;
                aux1->der = aux2->der;

                aux2->frecuencia = p_aux;
                aux2->letra = c_aux;
                aux2->izq = izq_aux;
                aux2->der = der_aux;
            }
           aux2=aux2->siguiente;
        }
        aux1=aux1->siguiente;
    }
}

void insertarc(struct cola *q, char c, int f, nodo *p, int op){
	encolar(q, c, f, p, op);
    ordenarpriori(q);
}

/**********************************************************
FUNCIONES : Árbol Binario
BY: Gabriela Alejandra Pérez Arteaga
**********************************************************/
nodo *Nuevo(){
    nodo *q=(nodo*)malloc(sizeof(nodo));
    if(!q){ perror("\n\tERROR");
    exit(1);}
    return(q);
}

nodo *insertar(char c, int f, nodo *p, nodo *t1, nodo *t2){
    if(p==NULL){
        p=Nuevo();
        p->letra=c;
        p->frecuencia=f;
        p->izq=t1;
        p->der=t2;
        return(p);
    }
    if(f < p->frecuencia) p->izq=insertar(c, f,p->izq, t1, t2);
    else p->der=insertar(c, f,p->der, t1, t2);
    return(p);
}

void ver(int nivel, nodo *p){
    int i;
    if(p!=NULL){
        ver(nivel+1, p->der);
        printf("\n");
        for(i=0; i<nivel; i++)printf("   ");
        printf("%c:%d ", p->letra, p->frecuencia);
        ver(nivel+1, p->izq);
    }
}

int eshoja(nodo *p){
	return !(p->izq) && !(p->der);
}

void codigos(nodo *p, int code[], int top){
	int i;
	if(p->izq){
		code[top]=0;
		codigos(p->izq, code, top+1);
	}
	if(p->der){
		code[top]=1;
		codigos(p->der, code, top+1);
	}
	if(eshoja(p)){
		printf("\n %c : ", p->letra);
    	for (i = 0; i < top; ++i) 	printf("%d", code[i]);
	}
}

/**********************************************************
						APLICACIONES
					Código de Huffman
BY: Gabriela Alejandra Pérez Arteaga
**********************************************************/
int main(){

   char *nombre = "texto.txt";
   FILE *archivo = fopen(nombre, "r");
   char *buffer = NULL;
   char alfabeto[26]= {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r','s', 't', 'u', 'w', 'x', 'y', 'z'};
   int code[10];
   struct cola q;			//cola
   nodo *p = NULL;			//ARBOL HUFFMAN
   nodo *aux =  NULL;		//arbol aux
   nodo *t1 = NULL; 		//temporal 1
   nodo *t2 = NULL;			//temporal 2
   q.delante=NULL;
   q.atras=NULL;
   int i, c, ln, j, frec=0, x=0, cont, top=0;

   printf("\n---------------------------------------------------------\n\t A L G O R I T M O    D E    H U F F M A N \n--------------------------------------------------------- ");
   if(archivo==NULL){
        printf(" -- This file could not open --");
        return -1;
   }else{
          printf("\n -- Archivo abierto existosamente. -- \n");
   }
   						/* Abre el archivo */  
   while(!feof(archivo)){
    buffer=(char*)malloc(sizeof(char));
    fgets(buffer, 254, archivo);
    printf(" Contenido del archivo :: \n\t\t ------------- \n");
    printf(" %s ", buffer);
    					/*Contador caracteres */
   	ln=strlen(buffer);
   	for(i=0; i<=25; i++){
   		frec=0;
   			for(j=0; j<ln; j++){
   				if(alfabeto[i]==buffer[j]){
   					frec=frec+1;
   				}
   			}
   		if(frec!=0){
   			c=alfabeto[i];
   			insertarc(&q, c, frec, p, 1);
   			x=x+1;
   			}
   		}			//fin for recorre la línea
	}
						/* FIN DE PRIMERA COLA */


	while((q.delante)->siguiente!=NULL){
		aux=NULL;
		t1=desencolar(&q);				//Temporal 1
		t2=desencolar(&q);				//Temporal 2
		frec = (t1->frecuencia) + (t2->frecuencia);
		aux = insertar(' ', frec, aux, t1, t2);
	/* Formar arbol en cola */
		insertarc(&q, c, frec, aux, 2);
		p = aux;		
	}

	printf("\n---------------------------------------------------------\n\t\t Arbol de Huffman \n--------------------------------------------------------- ");
	ver(0, p);
	printf("\n---------------------------------------------------------\n\t Tabla de Codigo \n--------------------------------------------------------- ");
	codigos(p, code, top);
	free(p);
	free(aux);
	free(t1);
	free(t2);
	close(archivo);
	return 0;
}
