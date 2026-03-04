#include<stdio.h>

int main(){
	size_t mi_strlen(const char *str);
	
	char texto[100] = "";
	printf("Ingresa un texto cualquiera: ");
	if (fgets(texto, sizeof(texto), stdin)) {
        size_t len = mi_strlen(texto);
        if (len > 0 && texto[len - 1] == '\n') {
            texto[len - 1] = '\0';
        }
    }
	
	printf("La longitud es: %zu\n", mi_strlen(texto));
	
	return 0;
}


size_t mi_strlen(const char *str){
	const char *inicio = str; //Guarda la posición inicial
	
	//Recorrer hasta encontrar nulo '\0'
	while(*str != '\0'){
		str++; // Aritmética de punteros: mover al siguiente char
	}
	
	//Restar punteros: dirección final - dirección inicial
	return(size_t)(str - inicio);
}
