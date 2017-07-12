#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void);
void rtrim(char *str),
     ltrim(char *str),
     trim(char *str);
FILE * input_file;
char linea[256],
     * upper(char * str);
char DATA[] = ".DATA";
char low[] = "police";


int main(void){
    if((input_file = fopen("program.asm", "r")) == NULL){
        printf("\nNo se ha podido abrir el archivo.\n");
        return 1;
    }
    while (fgets(linea, 256, input_file)){
        int len = strlen(linea);
        printf("%s*%d", linea, len);
        if( upper(linea) == DATA)
            printf("*\n");
    }
    printf("\nSuccess\n");
    upper(low);
    printf("%s\n", low);
    int len = strlen(DATA);
    printf("%s\n%d\n",DATA, len);
    fclose(input_file);

}

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
    while (str[counter]){
        str[counter] = toupper(str[counter]);
        counter++;
    }
    return str;
}
