#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
  
	char *buscarPalabra = argv[1];
	for(int i=0; i<strlen(buscarPalabra); i++){
		buscarPalabra[i] = tolower(buscarPalabra[i]);
	}
  
  int registro2= -1;
  
  FILE *archivo1 = fopen("record1.bin", "rb");
  
  
  
  

  fseek(archivo1, 0, SEEK_END);
  long indexSize = ftell(archivo1);
  int linea1Size = 50*sizeof(char) + sizeof(int);

  /********* line1Size Testing *************
  char ejemplo[50];
  fseek(archivo1, 0, SEEK_SET);
  fread(ejemplo, sizeof(char), 50, archivo1);
  printf("Inicio en: %s \n", ejemplo);
  fseek(archivo1, linea1Size, SEEK_SET);
  fread(ejemplo, sizeof(char), 50, archivo1);
  printf("Segunda palabra en: %s \n", ejemplo);
  /**Testing*/

	int start = 0;
	int end = indexSize / linea1Size;
  int mid = (start+ end)/2;
  int exists = 0;
  while(start <= end){
    char palabraBin[50];
    fseek(archivo1, mid * linea1Size, SEEK_SET);
    fread(palabraBin, sizeof(char), 50, archivo1);
    int comparador= strcmp(palabraBin, buscarPalabra);
    
    
    if(comparador>0){
      end = mid-1;
    }else if(comparador ==0){
      fread(&registro2, sizeof(int), 1, archivo1);
      
      break;
    }else{
      start = mid+1;
    }
    mid = (start+end)/2;

  }
  fclose(archivo1);

  if(start>end){
    printf("No pudimos encontrar la palabra %s \n", buscarPalabra);
    exists=1;
  }

if(exists == 0){
    FILE *archivo2 = fopen("record2.bin","rb");
    int renglon[2];
    registro2--;
    while(renglon[1] != -1){
      fseek(archivo2, registro2 * 2 *sizeof(int), SEEK_SET);
      fread(renglon, sizeof(int),2, archivo2);
      printf("La palabra «%s» se encuentra en la línea: %d \n", buscarPalabra, renglon[0]);
      registro2++;
    }
    fclose(archivo2);
  }
  return 0;
}