#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void),
    num_identificadores = 0,
    num_simbolos = 0,
    iter = 0,
    data = 0;
FILE * input_file;
void rtrim(char *str),
     ltrim(char *str),
     trim(char *str),
     init_estructura (char * identificador, char * valor, int num),
     init_simbolo (char * simbolo, int num, size_t len),
    declarations(void);
char linea[256],
     * identificador,
     * simbolo,
     * valor,
     * sec_pass,
     * upper(char * str),
     * simbolo2,
     resp[256];
struct estructura_identificador{
    char identificador[256];
    char valor[256];
    int direccion;
    int set;
}identificadores[50];
struct estructura_simbolos{
    char simbolo[256];
    int direccion;
    int set;
}simbolos[50];
struct data_struct{
    char instruction[5];
    char first[5];
    char second[5];
    char code[5];
    int wide;
}; // }values_data_struct[100];
struct data_struct values_data_mov[] = {
    {"MOV", "AL", "rmb", "A0", 2},
    {"MOV", "AX", "rmw", "A1", 2},
    {"MOV", "AL", "ib", "B0", 1},
    {"MOV", "AH", "ib", "B4", 1},
    {"MOV", "AX", "iw", "B8", 2},
    {"MOV", "DL", "ib", "B2", 1},
    {"MOV", "DH", "ib", "B6", 1},
    {"MOV", "DX", "iw", "BA", 2},
};
struct data_struct values_data_cmp[] = {
    {"CMP", "AL", "ib", "3C", 1},
    {"CMP", "AX", "iw", "3D", 2},
};
struct data_struct values_data_jmp[] = {
    {"JMP", "", "", "EB", 1},
    {"JE", "", "", "74", 1},
    {"JG", "", "", "7F", 1},
};
struct data_struct values_data_int[] = {
    {"INT", "", "", "CD", 1},
};


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
            simbolo = strtok(linea, ",");
            trim(simbolo);
            if (simbolo[0] == 111 && simbolo[1] == 114 && simbolo[2] == 103 && simbolo[3] == 32)  // org
                continue;
            size_t len = strlen(simbolo);
            if (simbolo[len-1] == 58){  // :
                init_simbolo(simbolo, num_simbolos, len);
                continue;
                }

            simbolo2 = strtok(NULL, ",");
            if (!simbolo2){
                strcpy(resp, "");
            }
            else strcpy(resp, simbolo2);
            trim(resp);
            printf("[%s][%s]\n", simbolo, resp);


            char part1[20], part2[20];
            sec_pass = strtok(simbolo, " ");
            strcpy(part1, sec_pass);
            upper(part1);
            trim(part1);
            sec_pass = strtok(NULL, " ");
            strcpy(part2, sec_pass);
            upper(part2);
            trim(part2);
            /* printf("[%s] [%s]\n", part1, part2); */
            /* printf("[%s] [%s]\n", values_data_struct[7].instruction, values_data_struct[7].first); */
            int flag = 1;
            iter = 0;
            /* if (strcmp(resp,"") == 0) */
            /*     printf(" "); */
            /* else{ */
            /*     printf(" "); */
// WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP
                /* while(flag == 1){ */
                /*     /1* if(strlen(part2)>2) *1/ */
                /*     char chop0[5], chop1[5]; */
                /*     strcpy(values_data_struct[iter].instruction, chop0); */
                /*     strcpy(values_data_struct[iter].first, chop1); */

                /*     if(strcmp(chop0, part1) == 0 && strcmp(chop1, part2) == 0){ */
                /*         printf("Yolo\n"); */
                /*         flag = 0; */
                /*     } */
                /*     if(iter > ) */
                /*         break; */

                /*     iter += 1; */
                /* } */
            /* } */

            }

    }
    fclose(input_file);
    return 0;
}

void init_estructura (char * identificador, char * valor, int num){
    /* identificadores[num].identificador = identificador; */
    strcpy(identificadores[num].identificador, identificador);
    strcpy(identificadores[num].valor, valor);
    identificadores[num].set = 1;
}

void init_simbolo (char * simbolo, int num, size_t len){
    strncpy(simbolos[num].simbolo, simbolo, len-1);
    /* simbolos[num].simbolo[len-1] = NULL; */
    /* strncpy(simbolos[num].simbolo,simbolos[num].simbolo,(len-2)); */
    simbolos[num].set = 1;
    if (num == 0)
        simbolos[0].direccion = 100;
    printf("%s\n", simbolos[num].simbolo);
    num_simbolos += 1;
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
    /* char * str2; */
    /* strcpy(str2, str); */
    while (str[counter]){
        str[counter] = toupper(str[counter]);
        counter++;
    }
    /* return str2; */
    return str;
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


