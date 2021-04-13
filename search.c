#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char *buscarPalabra = argv[1];
	for(int i=0; i<strlen(buscarPalabra); i++){
		buscarPalabra[i] = tolower(buscarPalabra[i]);
	}
	int start = 0;
	int end = 26477;
}