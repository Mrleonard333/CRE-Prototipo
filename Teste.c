#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese"); // < Declarando a lingua
    // ^ Se n�o funcionar cheque as configura��es de sua IDE (Western ISO 8859-1)

    // v Declarando fun��es
    int options(int *escolha);
    int sim_nao(char sn[10]);

    int tf = 0; // < TrueFalse
    int option = 0; // < Op��o do tester
    int INTarquivo = 0; // < Tamanho da lista
    int INTarquivo_2 = 0; // < Vai guardar o tamanho da lista

    char c; // < guarda os caracteres do buffer
    char SN[10]; // SIM ou N�O
    char arquivo[100]; // Nome do arquivo
    char arquivos[INTarquivo][100]; // Nome dos arquivos

    puts("[Funda��o crypto] - [CRE_Prototipo_01]\n\a");
    sleep(1); // < Aguarda um segundo
    printf("Iniciar o sistema? [S/N]: ");
    scanf("%s", &SN); // < Input
    while ((c = getchar()) != '\n' && c != EOF){}
    // ^ Limpeza do buffer do teclado [Para evitar bugs]

    if (sim_nao(SN) == 1) {return 0;}
            // v Guarda o valor no vetor de op��es escolhidas
    options(&option); // < Ativa a fun��o de op��es
    sleep(1);
    puts("\n[! Acentos ir�o bugar !]\n");
    sleep(1);
    printf("Deseja afetar mais de um arquivo? [S/N]: ");
    scanf("%s", &SN); // < Sim ou N�o
    while ((c = getchar()) != '\n' && c != EOF){}
    
    // v Se quiser afetar mais de um arquivo
    if (sim_nao(SN) == 0) {
        printf("Digite a quantidade: ");
        scanf("%d", &INTarquivo); // < Quantidade dos arquivos que ser�o guradados na lista
        while ((c = getchar()) != '\n' && c != EOF){}

        INTarquivo_2 = INTarquivo - 1; // < Guarda o tamanho da lista
        while (INTarquivo != -1) // < enquanto a quantidade dos arquivos n�o for batida
        {   
            INTarquivo--;
            if (INTarquivo == -1) {break;}

            printf("- Arquivo[%d]: ", INTarquivo);
            fgets(arquivo, 100, stdin); // < Input

            arquivo[strlen(arquivo) - 1] = 0;
            strcpy(arquivos[INTarquivo], arquivo);
        }
        // v Diz que vai afetar mais de um arquivo [True]
        tf = 1;
    } else { // < Se n�o quiser
        printf("Qual o nome do arquivo?: ");
        scanf("%s", &arquivo); // < Guarda o nome do arquivo
        while ((c = getchar()) != '\n' && c != EOF){}}

    sleep(1);
    if (tf != 1) { // Se n�o for afetar mais de um arquivo

        // v Se a op��o [Criar] foi escolhida
        if (option == 1) 
        {   FILE *f1; // < f1 vai apontar o lugar do arquivo na mem�ria
            f1 = fopen(arquivo, "r"); // < Tenta abrir o arquivo

                // v Se conseguir
            if (f1 != NULL) {puts("[! O arquivo j� existe !]"); fclose(f1);} 
            else {printf("Criadno o arquivo %s...\n", arquivo); fopen(arquivo, "w"); printf("Arquivo %s criado", arquivo);}
        }
        // v Se a op��o [Renomear] foi escolhida
        if (option == 2) 
        {   char novo[100];
            printf("Qual ser� o novo nome?: ");
            scanf("%s", novo);
            while ((c = getchar()) != '\n' && c != EOF){}

                // v Se conseguir renomear o arquivo
            if (rename(arquivo, novo) == 0) {printf("Arquivo renomeado para %s", novo);} 
            else {puts("[! Houve um erro !]");}
        }
        // v Se a op��o [Remover] foi escolhida
        if (option == 3)
        {
            printf("Apagando o arquivo %s...\n", arquivo);
            sleep(1);
                // v Se conseguir remover o arquivo
            if (remove(arquivo) == 0) {printf("Arquivo %s foi apagado", arquivo);} 
            else {puts("[! Houve um erro !]");}
        }
    } else { // < Se afetar mais de um arquivo

        // Vai fazer o mesmo, por�m em massa
        if (option == 1) 
        {   int INT = INTarquivo_2;
            FILE *f1;

            while (INT != -1) 
            {
                f1 = fopen(arquivos[INT], "r");
                if (f1 != NULL) {puts("[! Arquivo j� existente !]");}
                else {fopen(arquivos[INT], "w"); printf("Arquivo %s criado.\n", arquivos[INT]);}
                fclose(f1);
                INT--;
            }
        }
        if (option == 2) 
        {   int INT = INTarquivo_2;
            char LISTnovo[INT][100];
            char novo[100];

            while (INT != -1)
            {
                printf("[%s] - Arquivo[%d]: ", arquivos[INT], INT);
                scanf("%s", novo);
                while ((c = getchar()) != '\n' && c != EOF){}

                strcpy(LISTnovo[INT], novo);
                INT--;
            }
            
            INT = INTarquivo_2;

            while (INT != -1) 
            {
                if (rename(arquivos[INT], LISTnovo[INT]) == 0) {printf("[%s] renomeado para [%s]\n", arquivos[INT], LISTnovo[INT]);} 
                else {puts("[! Houve um erro !]\n");}
                INT--;
            }
        }
        if (option == 3) 
        {   int INT = INTarquivo_2;

            while (INT != -1) 
            {
                if (remove(arquivos[INT]) == 0) {printf("- Arquivo %s foi apagado\n", arquivos[INT]);} 
                else {puts("[! Houve um erro !]\n");}
                INT--;
            }
        }
    }
    return 0;
}

// v Vai checar a resposta de sim ou n�o
int sim_nao(char sn[10]) {if (strcmp(sn, "s") == 0 || strcmp(sn, "S") == 0) {return 0;} else {return 1;}}

                // v Guarda a escolha do tester
int options(int *escolha) {
    char c;
    sleep(1);
    puts("\n[! Antes de inciar o processo cire uma pasta para o arquivo caso n�o tenha !]");
    sleep(1);
    puts("- [1] CRIAR");
    puts("- [2] REOMEAR");
    puts("- [3] EXCLUIR");
    sleep(1);
    printf("\nO que deseja?: ");
    scanf("%d", escolha);
    while ((c = getchar()) != '\n' && c != EOF){}
}