#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DATA_SIZE 4

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
    int line;
    int sig;
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

	/* Open source files in 'r' mode */
	file = fopen("alice.txt", "r");
	/* Check if file opened successfully */
	if (file == NULL)
	{
		printf("\nNo existe el archivo.\n");
		exit(EXIT_FAILURE);
	}
	/*
     * Logic to count characters, no_palabra and no_linea.
     */
	characters = no_palabra = no_linea = pos2 = 0;
	while ((ch = fgetc(file)) != EOF)
	{
		characters++;
		/* Check new line */
		if (ch == '\n' || ch == '\0')
		{
			no_linea++;
		}
		/* Check no_palabra */
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
			fscanf(file, "%s", word);
		no_palabra++;
		int len = strlen(word);
		int i = 0;
		while (i < strlen(word))
		{
			//Remove punctuation
			if (strchr("`.;,!?:--'", word[i]))
				memmove(&word[i], &word[i + 1], strlen(word) - i);
			else
				i++;
		}
		//Lower case it
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
	/* Increment no_palabra and no_linea for last word */
	if (characters > 0)
	{
		no_palabra++;
		no_linea++;
	}
	//Ordenar, quitar repeticion y escribir en archivo
	bsortDesc(arregloAux);
  bsortDesc(arregloAux2);
  display(arregloAux, record2);
	quitarRepetidos(arregloAux);
	displayfile1(arregloAux,arregloAux2);
    

	/* Close files to release resources */
	fclose(file);
	return 0;
}


void displayfile1(struct Record1 arregloAux[26477], 
struct Record1 arregloAux2[26477])
{ 
	FILE *fPtr;

	int i, s;
  int aux = 0;
  int counter = 0;
	fPtr = fopen("record1.txt", "wb");

	/* Check if file opened successfully */
	if (fPtr == NULL && fPtr == NULL)
	{
		printf("\nNo existe el archivo.\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 2896; i++)
	{
    aux = 0;
		fputs(arregloAux[i].word, fPtr);
		fputs(" ", fPtr);
    //fputs(arregloAux2[i].word, fPtr);    
    counter = 0;
    /*for (int j = 0; j < 26477; j++)
    //arregloaux youth -->904
  //record 2 linea --> 904
    {
    //if(arregloAux[i].ptr == record2[j].line)
    //{
      if(strcmp(arregloAux[i].word, arregloAux2[j].word) != 0){
          counter++;
      }
       fprintf(fPtr,"%d ", counter);
       fprintf(fPtr,"%d ", j+ 1);
    //}
    }*/
     

    fputs("\n", fPtr);
	}
	fclose(fPtr);
 
}


void display(struct Record1 arregloAux[26477], struct Record2 record2[26477])
{
  FILE *fPtr;
	int i,j,k;
	fPtr = fopen("record2.txt", "wb");
    if (fPtr == NULL && fPtr)
	{
		printf("\nNo existe el archivo.\n");
		exit(EXIT_FAILURE);
	}
    for (i = 1; i < 26477; i++)
    {
      printf("%d", i);
      printf(" ");
      printf("%s\t%d", arregloAux[i].word, arregloAux[i].ptr);
      printf("\n");
      record2[i].line = arregloAux[i].ptr;
      record2[i].next = i;
      //fprintf(fPtr, "%s ", arregloAux[i].word);
      //fputs(" ", fPtr);
      fprintf(fPtr, "%d ", record2[i].line);
      fputs(" ", fPtr);
      if(strcmp(arregloAux[i].word, arregloAux[i+1].word) == 0){
        record2[i].next++;
        fprintf(fPtr, "%d ", record2[i].next);
        fputs("\n", fPtr);
      }
      else{
      record2[i].next = -1;
      fprintf(fPtr, "%d ", record2[i].next);
      fputs("\n", fPtr);
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
			/* If any duplicate found */
			if (strcmp(record1[i].word, record1[j].word) == 0)
			{
				/* Delete the current duplicate element */
				for (int k = j; k < size; k++)
				{
					strcpy(record1[k].word, record1[k + 1].word);
					record1[k].ptr = record1[k + 1].ptr;
				}
				/* Decrement size after removing duplicate element */
				size--;
				/* If shifting of elements occur then don't increment j */
				j--;
			}
		}
	}
}
int buscaBin(struct Record1 arregloAux[], int l, int r, int x){
    int num;
    char ch;
   FILE *fptr;

   if ((fptr = fopen("record1.txt","r")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
   }	while ((ch = fgetc(fptr)) != EOF)
	{
   
   //fscanf(fptr,"%d", &num);
   //printf("Se encontro la palabra: =%d", num);
   fclose(fptr); 
   return -1;  

  }
  return 0;
}



/*
void displayfile2(struct Record2 record2[26477])
{
	FILE *fPtr;
	int i, s;
	fPtr = fopen("record2.txt", "wb");
  
	 Check if file opened successfully 
	if (fPtr == NULL && fPtr)
	{
		printf("\nNo existe el archivo.\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 26477; i++)
	{
		fprintf(fPtr, "%d ", record2[i].line);
		fputs("\n", fPtr);
	}
	fclose(fPtr);
}*/