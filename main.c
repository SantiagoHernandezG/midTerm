#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DATA_SIZE 4
/*
Pedro Demian Godinez Cruz A01657025
Santiago Hernandez Guerrero A0127543
*/
typedef struct Record1
{
	char word[50]; // palabra o llave
	int ptr;	   // posicion de primer record2 en el archivo 2
} record1;


typedef struct Record2
{
	int line; // linea en el archivo .txt
	int next; // sig posicion dentro del archivo2
} record2;
typedef struct lista {
    int line; //linea de la palabra
    int sig; //siguiente registro en la lista
    struct node * next;
} node_t;


void displayfile1(struct Record1 record1[], struct Record1 arregloAux2[]);
void displayfile2(struct Record2 record2[]);
void display(struct Record1 record1[],struct Record2 record2[]);
void bsortDesc(struct Record1 Record1[]);
void quitarRepetidos(struct Record1 Record1[]);
int buscaBin(struct Record1 record1[], int l, int r, int x);

typedef struct palabraAux
{
	char wordAux[50];
} palabraAux;

int main()
{
	struct Record1 arregloAux[26477];
  struct Record1 arregloAux2[26477];
	struct Record1 record1[26477];
  struct Record2 record2[26477];
  int result, errno;

	FILE *file;
	char word[50];
	char ch;
	int characters, no_palabra, no_linea, pos2;


	file = fopen("alice.txt", "r");
	
	if (file == NULL)
	{
		printf("\nNo existe el archivo.\n");
		exit(EXIT_FAILURE);
	}
	/*
     * Logica ver no_palabra and no_linea.
     */
	characters = no_palabra = no_linea = pos2 = 0;
	while ((ch = fgetc(file)) != EOF)
	{
		characters++;
		/* Checar nueva line */
		if (ch == '\n' || ch == '\0')
		{
			no_linea++;
		}
		/* Checar no_palabra */
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
			fscanf(file, "%s", word);
		no_palabra++;
		int len = strlen(word);
		int i = 0;
		while (i < strlen(word))
		{
			//Quitar punctuación
			if (strchr("`().;,!?:--'", word[i]))
				memmove(&word[i], &word[i + 1], strlen(word) - i);
			else
				i++;
		}
		//Pasarlo a minisculas
		for (int i = 0; word[i]; i++)
		{
			word[i] = tolower(word[i]);
		}
		//Agregar palabra a la escturctura auxiliar
		strcpy(arregloAux[no_palabra].word, word);
		arregloAux[no_palabra].ptr = no_linea;
    strcpy(arregloAux2[no_palabra].word, word);
		arregloAux2[no_palabra].ptr = no_linea;
    record2[no_palabra].line = no_linea;
	}
	/* Incrementar no_palabra and no_linea para la ultima palabra */
	if (characters > 0)
	{
		no_palabra++;
		no_linea++;
	}
	//Metodos para crear los archivos
	bsortDesc(arregloAux);
  bsortDesc(arregloAux2);
  display(arregloAux, record2);
	quitarRepetidos(arregloAux);
	displayfile1(arregloAux,arregloAux2);
    
	fclose(file);
	return 0;
}


void displayfile1(struct Record1 arregloAux[26477], 
struct Record1 arregloAux2[26477])
{ 
	FILE *fPtr;

	int i, s;
  int aux = 0;
  int pos = 0;
  int counter = 0;
	fPtr = fopen("record1.bin", "wb");

	
	if (fPtr == NULL && fPtr == NULL)
	{
		printf("\nNo existe el archivo.\n");
		exit(EXIT_FAILURE);
	}
    for (int j = 1; j < 26477; j++)

    {
      
      if(strcmp(arregloAux2[j].word, arregloAux2[j+1].word) == 0){
      counter++;
      aux++;
      }
      else{
      counter++;
      fwrite(&arregloAux2[j].word, 50, 1, fPtr);

      pos = counter -aux;
      fwrite(&pos, 4, 1, fPtr);

      aux = 0;
      }
      }
	fclose(fPtr);
}
    
 
void display(struct Record1 arregloAux[26477], struct Record2 record2[26477])
{
  FILE *fPtr;
	int i,j,k;
	fPtr = fopen("record2.bin", "wb");
    if (fPtr == NULL && fPtr)
	{
		printf("\nNo existe el archivo.\n");
		exit(EXIT_FAILURE);
	}
    for (i = 1; i < 26477; i++)
    {
      record2[i].line = arregloAux[i].ptr;
      record2[i].next = i;
    
      fwrite(&record2[i].line, 4, 1, fPtr);

      if(strcmp(arregloAux[i].word, arregloAux[i+1].word) == 0){
        record2[i].next++;
        fwrite(&record2[i].next, 4, 1, fPtr);

      }
      else{
      record2[i].next = -1;
      fwrite(&record2[i].next, 4, 1, fPtr);
      }
      }
       
      fclose(fPtr);
}
void bsortDesc(struct Record1 record1[])
{
	int i, j, k, l, aux;

	struct Record1 temp;

	for (i = 0; i < 26477; i++)
	{
		for (j = i + 1; j < 26477; j++)
		{
			if ((strcmp(record1[i].word, record1[j].word) > 0))
			{
				temp = record1[i];
				record1[i] = record1[j];
				record1[j] = temp;
			}
		}
	}
}

void quitarRepetidos(struct Record1 record1[])
{
	int size = 26477;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			/* Si hay duplicados  */
			if (strcmp(record1[i].word, record1[j].word) == 0)
			{
				/* Borrar el duplicado */
				for (int k = j; k < size; k++)
				{
					strcpy(record1[k].word, record1[k + 1].word);
					record1[k].ptr = record1[k + 1].ptr;
				}
				/* Decrementar el tamaño del array */
				size--;
				/* Si son iguales, no incrementar j */
				j--;
			}
		}
	}
}

