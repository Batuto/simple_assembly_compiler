#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void),
    num_identificadores = 0,
    data = 0;
FILE * input_file;
void rtrim(char *str),
     ltrim(char *str),
     trim(char *str),
     init_estructura (char * identificador, char * valor, int num);
char linea[256],
     * identificador,
     * valor,
     * upper(char * str);
struct estructura_identificador{
    char * identificador;
    char * valor;
    int direccion;
    int set;
}identificadores[50];


int main(void){
    if((input_file = fopen("program.asm", "r")) == NULL){
        printf("\nNo se ha podido abrir el archivo.\n");
        return 1;
    }

    while (fgets(linea, 256, input_file)){
        if (linea[0] == 10)
            continue;
        if (linea[0] == 46 && linea[1] == 77)  // .M
            continue;
        if (linea[0] == 46 && linea[1] == 68){  // .D
            data = 1;
            continue;
        }
        else if (linea[0] == 46 && linea[1] == 67){  // .C
            data = 0;
            continue;
        }
        if (data == 1){
            identificador = strtok(linea, "db");
            trim(identificador);
            valor = strtok(NULL, "db");
            trim(valor);
            init_estructura(identificador, valor, num_identificadores);
            printf("%d - [%s][%s]\n", num_identificadores, identificador, valor);
            num_identificadores += 1;
        }
        else{
            printf("No\n");
        }
    }
    fclose(input_file);
    return 0;
}

void init_estructura (char * identificador, char * valor, int num){
    identificadores[num].identificador = identificador;
    identificadores[num].valor = valor;
    identificadores[num].set = 1;
}

/* int main(void){ */
/*     char tmp_str[2], salto = 10; */
/*     tmp_str[1] = '\0'; */
/*     tmp_str[0] = salto; */
/*     strcat(DATA, tmp_str); */
/*     if((input_file = fopen("program.asm", "r")) == NULL){ */
/*         printf("\nNo se ha podido abrir el archivo.\n"); */
/*         return 1; */
/*     } */
/*     while (fgets(linea, 256, input_file)){ */
/*         int len = strlen(linea); */
/*         /1* printf("%s", upper(linea)); *1/ */
/*         printf("%s*%d - %d\n", linea, len, linea[len]); */
/*         if( toupper(linea[0]) == atoi(".")) */
/*             printf("*******\n"); */
/*     } */
/*     printf("\nSuccess\n"); */
/*     char * low2; */
/*     low2 = upper(low); */
/*     printf("Flag\n" ); */
/*     printf("%s\n", low); */
/*     int len = strlen(DATA); */
/*     printf("%s\n%d - %d\n",DATA, len, DATA[len-1]); */
/*     fclose(input_file); */

/* } */

void rtrim(char *str){          // Función que elimina espacios hacia la derecha
    size_t n;
    n = strlen(str);
    while (n > 0 && (isspace((unsigned char)str[n - 1]) || (unsigned char)str[n - 1] == ' ')) {
        n--;
    }
    str[n] = '\0';
}

void ltrim(char *str){          // Función que elimina espacios hacia la izquierda
    size_t n;
    n = 0;
    while (str[n] != '\0' && isspace((unsigned char)str[n])) {
        n++;
    }
    memmove(str, str + n, strlen(str) - n + 1);
}

void trim(char *str){           // Función que elimina espacios hacia la izquierda y derecha
    rtrim(str);
    ltrim(str);
}

char * upper(char * str){
    int counter = 0;
    /* char * str2; */
    /* strcpy(str2, str); */
    while (str[counter]){
        str[counter] = toupper(str[counter]);
        counter++;
    }
    /* return str2; */
    return str;
}
