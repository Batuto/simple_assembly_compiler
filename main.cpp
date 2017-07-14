#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>


using namespace std;

int main(int argc, char *argv[]),
    bienvenida(void);
bool verificar_argumentos(int numero),
     data = false;
FILE * input_file, * output_file;
char punto = 46;
char identificador[50];

int main(int argc, char *argv[]){
    system("clear");
    bienvenida();
    /*
    if (verificar_argumentos(argc)){
    printf("\t\tArgumentos extra...\n\n\tEl programa sólo recibe nombre del archivo fuente como argumento\n");
        return 1;
    }
    char input_filename[strlen(argv[1])+1] = argv[1];
    input_filename = argv[1];
    input_file = fopen(input_filename, 'r');
    if ((input_file) == NULL){
        printf("\n\nNo se ha podido abrir el archivo «%s»\n", argv[1]);
        return 1;
    }
    */
    input_file = fopen("program.asm", "r");
    if ((input_file) == NULL){
        printf("\n\nNo se ha podido abrir el archivo.\n");
        return 1;
    }
    printf("\n\nSe ha podido abrir el archivo.\n");

    while (feof(input_file) == 0){
        char cadena[100];
        fgets(cadena, 100, input_file);
        if (cadena[0] == punto && cadena[1] == 68 ){  // D
            data = true;
    printf("\n\nPor aquí pasó\n");
            continue;
        }
        else if (cadena[0] == punto && cadena[1] == 67){  // C
            data = false;
            continue;
        }
        if (cadena[0] == punto)
            continue;

        if (data){  // Si está en el área de data, hará lo siguiente:
            int long_char;
            long_char = strlen(cadena);
            printf("> %d\n", long_char);
            for (int i = 0; i < long_char; i++){
                if (cadena[i] != 20){
                    char car = cadena[i];
                    char * caracter_temp;
                    //&caracter_temp = car;
                    strcat(identificador, caracter_temp+1);
                }
                printf("%c", cadena[i]);
            }
        }
        else  // Si no ...
            printf("%s", cadena);
    }

        printf("\n --> %s\n", identificador);
    fclose(input_file);
    return 0;
}

int bienvenida(void){
    printf("\t\tLoading...\n\n");
    return 0;
}

bool verificar_argumentos(int numero){
    if (numero > 2)
        return true;
    else
        return false;
}
