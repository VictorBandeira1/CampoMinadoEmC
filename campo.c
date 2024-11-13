#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int system(const char *string);

enum estados{
    VAZIO,
    BOMBA,
    BANDEIRA,
    BLOCO_1,
    BLOCO_2,
    BLOCO_3,
    BLOCO_4,
    BLOCO_5,
    BLOCO_6,
    BLOCO_7,
    BLOCO_8,
};

struct Bloco{
    enum estados estado;
    bool selecionado;
};

//É BEM INTUITIVO
void limpaTela(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

//INICIA OS VALORES DOS BLOCOS DO CAMPO MMINADO, SENÃO ELES FICAM ALEATÓRIOS
void iniciaCampo(int tamanho, struct Bloco matriz[tamanho][tamanho]){
    for (int i = 0; i < tamanho; i++){
        for (int j = 0; j < tamanho; j++){
            matriz[i][j].estado = VAZIO;
            matriz[i][j].selecionado = false;
        }
    }
}

//IMPRIME UM BLOCO DO CAMPO, CHECANDO SE ELE FOI SELECIONADO OU NÃO
void imprimeBloco(struct Bloco bloco, bool selecionado){
    const char SIMBOLOS[11] = {' ', '@', '>', '1', '2', '3', '4', '5', '6', '7', '8'};
    if (selecionado){
        printf("| %c ", SIMBOLOS[bloco.estado]);
    } else {
        printf("| # ");
    }
}

//É MAIS ESTÉTICO ISSO
void linha(int n){
    printf("\n");
    for (int i = 0; i <= n*4; i++){
        printf("=");
    }
    printf("\n");
}

//ESSE TAMBÉM É ESTÉTICO
void coordenadaX(int tamanho){
    const char LETRAS[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("  A");
    for (int i = 1; i < tamanho; i++){
        printf("   %c", LETRAS[i]);
    }
    printf("\n");
}

//MOSTRA O CAMPO POR INTEIRO
void imprimeCampo(int tamanho, struct Bloco matriz[tamanho][tamanho]){
    linha(tamanho);
    for (int y = 0; y < tamanho; y++){
        for (int x = 0; x < tamanho; x++){
            imprimeBloco(matriz[y][x], matriz[y][x].selecionado);
        }
        printf("| %i", y+1);
        linha(tamanho);
    }
    coordenadaX(tamanho);
}

//SELECIONA UM BLOCO FAZENDO ELE SER CONSIDERADO SELECIONADO
void selecionaBloco(int x, int y, int tamanho, struct Bloco matriz[tamanho][tamanho]){
    matriz[y][x].selecionado = true;
}

//RETORNA A POSIÇÃO DA LETRA NO ALFABETO
int indexLetra(char letra, int tamanho){
    const char LETRAS[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < tamanho; i++){
        if (LETRAS[i] == letra){
            return i;
        }
    }
    return -1;
}

//INCOMPLETO
void colocaBombas(int dificuldade, int tamanho, struct Bloco matriz[tamanho][tamanho]){
    int nBombas = (tamanho*tamanho) * (0.1 * dificuldade);
    printf("%i", nBombas);
}

int main() {
    char tecla;
    int cod_tecla;
    int tamanho = -99, x = -99, y = -99, dificuldade = -99;
    char opc, temp;

    printf("Bem vindo ao campo minado\n");
    while (tamanho < 10 || tamanho > 26){
        printf("Digite o tamanho da lateral do campo(MIN:10 MAX:26): ");
        scanf("%i", &tamanho);
        limpaTela();
    }
    
    while (dificuldade < 1 || dificuldade > 3){
        printf("Escolha a dificuldade\n");
        printf("1 - Fácil\n");
        printf("2 - Médio\n");
        printf("3 - Difícil\n");
        printf("-> ");
        scanf("%i", &dificuldade);
        limpaTela();
    }

    struct Bloco campo[tamanho][tamanho];

    iniciaCampo(tamanho, campo);

    colocaBombas(dificuldade, tamanho, campo);

    while (true){
        printf("%i %i\n", x, y);
        //imprimeCampo(tamanho, campo);

        /*printf("X: ");
        scanf(" %c", &opc);

        printf("Y: ");
        scanf("%i", &y);*/
        
        while (1) {
            if ( kbhit() ) {
  
                tecla = getch();
                system("cls");

                cod_tecla = (int)tecla;
                if (cod_tecla == 27){return 0;}//sai do jogo
                if (cod_tecla == 72){
                    //printf("CIMA");
                    y--;
                    break;
                } else if (cod_tecla == 75){
                    //printf("ESQUERDA");
                    x--;
                    break;
                } else if (cod_tecla == 77){
                    //printf("DIREITA");
                    x++;
                    break;
                } else if (cod_tecla == 80){
                    //printf("BAIXO");
                    y++;
                    break;
                }
         
            }
        }

        if (y == 0){
            limpaTela();
            break;
        }
        
        if (isalpha(opc)){

            opc = toupper(opc);
            x = indexLetra(opc, tamanho);
            y--;

            //printf("%i %i", x, y); debug 2

            if (x >= 0 && x < tamanho && y >= 0 && y < tamanho){
                //printf("debug 1");
                selecionaBloco(x, y, tamanho, campo);
            }
        }
        limpaTela();
    }

    return 0;
}
