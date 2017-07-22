#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void),
    is_digit(char * str),
    is_namber(char * str),
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
    * lower(char * str),
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
    char code[6];
    int wide;
}; // }values_data_struct[100];
struct data_struct values_data_mov[] = {
    {"MOV", "AL", "rmb", "A0", 2},
    {"MOV", "AX", "rmw", "A1", 2},
    {"MOV", "AL", "ib", "B0", 1},
    {"MOV", "AH", "ib", "B4", 1},
    {"MOV", "AX", "iw", "B8", 2},
    {"MOV", "DL", "ib", "B2", 1},
    {"MOV", "DL", "AL", "88 C2", 1},
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
            char chop0[5], chop1[5];
            int flag = 1;
            iter = 0;
            if (strcmp(resp,"") == 0) {
                /* printf(" "); */
                if (strcmp(part1,"INT") == 0){
                char pop[5];
                size_t lent = strlen(part2);
                strncpy(pop, part2, lent-1);
                /* printf("%s %0x\n", values_data_int[0].code, (int)strtol(part2, NULL,16)); */
                printf("%s %0x\n", values_data_int[0].code, (int)strtol(pop, NULL,16));
                }
                if (strcmp(part1,"JMP") == 0){
                lower(part2);
                printf("%s %s\n", values_data_jmp[0].code, part2);
                }
                if (strcmp(part1,"JE") == 0){
                lower(part2);
                printf("%s %s\n", values_data_jmp[1].code, part2);
                }
                if (strcmp(part1,"JG") == 0){
                lower(part2);
                printf("%s %s\n", values_data_jmp[2].code, part2);
                }

            }
            else{
                if (strcmp(part1, "MOV") == 0){
                    while(iter < 100){
                        if (strcmp(values_data_mov[iter].first, part2) == 0){
                            if ((is_digit(resp) == 1) && (strcmp(values_data_mov[iter].second, "ib") == 0)){  // Se encarga del MOV reg «entero»
                                printf("%s %02x\n", values_data_mov[iter].code, (int)strtol(resp,NULL,10));
                                break;
                            }
                            else
                            if (strcmp(upper(strtok(resp, " ")), "OFFSET") == 0){
                                printf("Message\n");
                                break;
                            }
                            else
                            if (strcmp(upper(resp), values_data_mov[iter].second) == 0){
                                printf("%s\n", values_data_mov[iter].code);
                                break;
                            }
                            /* flag = 0; */
                        }
                    iter += 1;
                    }

                    iter = 0;
                }

                if (strcmp(part1, "CMP") == 0){
                    iter = 0;
                }
// WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP
                /* while(flag == 1){ */
                /*     /1* if(strlen(part2)>2) *1/ */

                /*     if(strcmp(chop0, part1) == 0 && strcmp(chop1, part2) == 0){ */
                /*         printf("Yolo\n"); */
                /*         flag = 0; */
                /*     } */
                /*     if(iter > ) */
                /*         break; */

                /*     iter += 1; */
                /* } */
            }

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
char * lower(char * str){
    int counter = 0;
    while (str[counter]){
        str[counter] = tolower(str[counter]);
        counter++;
    }
    return str;
}
int is_digit(char * str){
    size_t len = strlen(str);
    int i;
    for(i = 0; i<len; i+=1){
        if(isdigit(str[i]) == 0)
            return 0;
    }
    return 1;
}
int is_namber(char * str){
    size_t len = strlen(str);
    if (len > 5)
        return 0;
    if (toupper(str[len-1]) == 'H'){
    char newstr[5];
    strncpy(str, newstr, len-1);
    if (is_digit(newstr) == 1)
        return 1;
    else return 0;
    }
    else return is_digit(str);
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


