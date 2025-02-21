//Projecto final

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "myfuncs.h"
#include <unistd.h> // extensão para Sistemas Unix. Correr em Windows é necessário mudar para stdlib.h


typedef struct{
    int ID;
    char nome[51];
    char Tipo [20];
    int IDLocalidade;
} praia;


typedef struct{
    int ID;
    char nome[51];
}localidade;


//Inserir uma localidade
int inserirLocalidade(){
   
    localidade localidades;

    FILE *fileloc;
    fileloc = fopen ("localidades.dat", "ab+");
    
    if(fileloc==NULL){ 
        perror("Erro na abertura do ficheiro.");
    return 0;
    }

    fseek(fileloc,0,SEEK_END);
    if(ftell(fileloc) == 0){
        localidades.ID=1;
    }
    else{
        fseek(fileloc,-sizeof(localidade),SEEK_CUR);
        fread(&localidades,sizeof(localidade),1,fileloc);
        localidades.ID++;
    }

    puts("Insira uma Localidade\n");
    printf("Nome da Localidade: ");fgets(localidades.nome,51,stdin);
    localidades.nome[strcspn(localidades.nome,"\n")]='\0';
    fwrite(&localidades,sizeof(localidade),1,fileloc);
    
    fclose(fileloc);
    return localidades.ID;
}


//Listar as localidades
void listarLocalidades(){
    
    localidade localidades;

    FILE *fileloc;
    fileloc = fopen ("localidades.dat", "rb");
    
    if(fileloc==NULL){
        perror("Erro na abertura do ficheiro. Por favor insira uma localidade.");
    return;
    }

    puts("\nLista de Localidades\n");
    while (fread(&localidades,sizeof(localidade),1,fileloc)) {
        printf("%i     ",localidades.ID);
        puts(localidades.nome);
    }
    fclose(fileloc);
}


//Inserir uma Praia
void inserirPraia(){
    
    praia praias;

    FILE *filepraias;
    filepraias = fopen ("praias.dat", "ab+");
    
    if(filepraias==NULL){
        perror("Erro na abertura do ficheiro.");
    return;
    }
    
    fseek(filepraias,0,SEEK_END);
    if(ftell(filepraias) == 0){
        praias.ID=1;
    }
    else{
        fseek(filepraias,-sizeof(praia),SEEK_CUR);
        fread(&praias,sizeof(praia),1,filepraias);
        praias.ID++;
    }


    //Nome da praia
    puts("Insira uma Praia\n");
    printf("Nome da Praia: ");getstr(praias.nome,51);
    praias.nome[strcspn(praias.nome,"\n")]='\0';
    
    //Tipo de praia
    printf("Tipo de Praia (escreva O para Oceânica ou F para Fluvial):");

    char op[2];
    
    do{
    getstr (op,2);
    if(toupper(op[0]) == 'O'){
        strcpy(praias.Tipo,"Oceânica");
        break;
    }
    else if(toupper(op[0]) == 'F'){
        strcpy(praias.Tipo,"Fluvial");
        break;
    }
    else if(toupper(op[0]) != 'F' && toupper(op[0]) != 'O'){
        printf("Tipo de praia inválido. Escreva O para Oceânica ou F para Fluvial:");
    }
    }while(toupper(op[0]) != "F" || toupper(op[0]) != "O");


    //Quero saber qual o Ultimo ID
    localidade localidades;
    
    FILE *fileloc;
    fileloc = fopen("localidades.dat", "ab+");
    
    if(fileloc==NULL){ 
        perror("Erro na abertura do ficheiro.");
    return;
    }

    fseek(fileloc,0,SEEK_END);
    if(ftell(fileloc) == 0){
        localidades.ID=1;
    }
    else{
        fseek(fileloc,-sizeof(localidade),SEEK_CUR);
        fread(&localidades,sizeof(localidade),1,fileloc);
        localidades.ID;
    }
     //ID da Localidade
        printf("ID Localidade:");
        listarLocalidades();
        if(ftell(fileloc) == 0){
        printf("**Lista vazia.**\n");
    }
        printf("\nID da Localidade ou 0 para inserir nova localidade\n");
        int IDInserido=getint();
        printf("\n");

    //Validar o ID inserido
    do{
        if(IDInserido>0 && IDInserido<=localidades.ID){
        praias.IDLocalidade=IDInserido;
        }

        else if(IDInserido == 0){
            int idLocInserida = 0;
            idLocInserida=inserirLocalidade();
            if(idLocInserida==0){
                return;
            }
            praias.IDLocalidade=idLocInserida;
        }
        else{
            printf("Localidade inválida. Escreva o número correspondente à localidade ou insira 0 para adicionar uma nova localidade:");
             printf("\nID ou 0\n");
            IDInserido = getint();
        }

    }while(IDInserido<0 || IDInserido>localidades.ID);

    fwrite(&praias,sizeof(praia),1,filepraias);
    fclose(fileloc);
    fclose(filepraias);
}


//Listar as praias
void listarPraias(){
    
    praia praias;

    FILE *filepraias;
    filepraias = fopen ("praias.dat", "rb");
    
    if(filepraias==NULL){
        perror("Erro na abertura do ficheiro. Por favor insira uma Praia.");
    return;
    }

    puts("Lista de Praias\n");
    while (fread(&praias,sizeof(praia),1,filepraias)) {
        printf("ID: %i | ",praias.ID);
        printf("Nome: %s | ", praias.nome);
        printf("Tipo de Praia: %s | ", praias.Tipo);
        printf("ID Localidade: %i\n",praias.IDLocalidade);
    }

    printf("\n");
    fclose(filepraias);
}


//Procurar praias pelo nome
void procurarPraias(){
    
    praia praias;
    char nome[51];
    
    FILE *filepraias;
    filepraias = fopen("praias.dat","rb");
    if(filepraias==NULL) {
        perror("Erro para abrir o ficheiro.");
        return;
    }
    printf("Qual o nome da praia? ");
    getstr(nome,51);
    
    printf("\n");

    while (fread(&praias,sizeof(praia),1,filepraias)){
        if(strstrcase(praias.nome,nome)){
            printf("ID: %i\n",praias.ID);
            printf("Nome da Praia: %s\n", praias.nome);
            printf("Tipo de Praia: %s\n", praias.Tipo);
            printf("ID da Localidade: %i\n",praias.IDLocalidade);
            printf("\n");
        }
        else{
            printf("Nenhuma praia encontrada.\n");
        }
    }
    fclose(filepraias);
}


//Listar as praias por localidade
void listarPraiasLoc(){
    
    praia praias;
    int IDlocalidade;

    FILE *filepraias;
    filepraias = fopen ("praias.dat", "rb");
    
    if(filepraias==NULL){
        perror("Erro na abertura do ficheiro.");
    return;
    }

    printf("Insira o ID da localidade para procurar? Caso queira ver a lista das localidades para saber o ID escreva 0.");
    IDlocalidade=getint();

    if (IDlocalidade==0){
        listarLocalidades();
        printf("\nInsira o ID da localidade: ");
        IDlocalidade = getint();
    }
   
    puts("\nLista de Praias\n");
    bool praiaencontrada = false;
    while (fread(&praias,sizeof(praia),1,filepraias)){
        if(praias.IDLocalidade == IDlocalidade){
            printf("ID: %i\n",praias.ID);
            printf("Nome da Praia: %s\n", praias.nome);
            printf("Tipo de Praia: %s\n", praias.Tipo);
            printf("ID da Localidade: %i\n",praias.IDLocalidade);
            printf("\n");
            praiaencontrada = true;
        }
    }

    if(praiaencontrada == false){
        printf("Não foi encontrada nenhuma Praia nesta Localidade.");
    }

    printf("\n");
    fclose(filepraias);
}


//Alterar Localidade
void alterarLocalidade(){
    
    localidade localidades;
    
    fpos_t pos;
    int ID;

    FILE*fileloc;
    fileloc = fopen("localidades.dat","rb+");
    if(fileloc==NULL) {
        perror("Erro");
        return;
    }
    printf("Qual o ID da Localidade que quer alterar? Caso pretenda ver a lista de Localidades insira 0.\n");
    ID=getint();
    fgetpos(fileloc,&pos);

    if(ID == 0){
        listarLocalidades();
        printf("Qual o ID da localidade que quer alterar?");
        ID=getint();
        fgetpos(fileloc,&pos);
    }

    while (fread(&localidades,sizeof(localidade),1,fileloc)){           
        if(ID == localidades.ID){
            puts("Localidade:");
            printf("%i ",localidades.ID);
            puts(localidades.nome);
            printf("Alterar(S/N)?");
            char op[2];
            getstr(op,2);
            if(toupper(op[0])=='S'){
                puts("Dados da localidade a alterar\n");
                printf("Nome: ");
                getstr(localidades.nome,51);
                fsetpos(fileloc,&pos);
                fwrite(&localidades,sizeof(localidade),1,fileloc);
                fflush(fileloc);
                printf("Localidade alterada com suscesso");
            }
        }
        fgetpos(fileloc,&pos);
    }
    fclose(fileloc);
    
}


//Alterar Praia
void alterarPraia(){
    
    praia praias; 

    fpos_t pos;
    int ID;

    FILE *filepraia;
    filepraia = fopen ("praias.dat", "rb+");
    
    if(filepraia == NULL){ 
        perror("Erro na abertura do ficheiro.");
    return;
    }

    printf("Insira o ID da praia que pertende alterar? Caso queira ver a lista das Praias insira 0.\n");
    ID=getint();

    if (ID == 0){
        listarPraias();
        printf("Qual o ID da praia que quer alterar?\n");
        ID=getint();
    }

    fgetpos(filepraia,&pos);

    while (fread(&praias,sizeof(praia),1,filepraia)){
        
        if(ID == praias.ID){
            puts("\nPraia a alterar:\n");
            printf("ID: %i\n",praias.ID);
            printf("Nome da Praia: %s\n",praias.nome);
            printf("Tipo da Praia: %s\n",praias.Tipo);
            printf("ID da Localidade: %i\n",praias.IDLocalidade);
            
            //confirmação para alterar e alterar
            printf("\nTem a certeza que pretende alterar (S/N)?\n");
            char op[2];
            getstr(op,2);
            if(toupper(op[0])=='S'){
                //Nome da praia
                puts("\nDados da Praia a alterar\n");
                printf("Nome da Praia: ");
                getstr(praias.nome,51);
                praias.nome[strcspn(praias.nome,"\n")]='\0';
    
                //Tipo de praia
                printf("Tipo de Praia (escreva O para Oceânica ou F para Fluvial):");

                char es[2];
    
                do{
                getstr (es,2);
                if(toupper(es[0]) == 'O'){
                    strcpy(praias.Tipo,"Oceânica");
                    break;
                }
                else if(toupper(es[0]) == 'F'){
                    strcpy(praias.Tipo,"Fluvial");
                    break;
                }
                else if(toupper(es[0]) != 'F' && toupper(es[0]) != 'O'){
                    printf("Tipo de praia inválido. Escreva O para Oceânica ou F para Fluvial:");
                }
                }while(toupper(es [0]) != "F" || toupper(es [0]) != "O");

                //ID da Localidade
                printf("ID Localidade (verifique se a localidade se encontra listada abaixo e indique o número correspondente. Caso contrário insira 0 para adiciona uma nova localidade):");
                listarLocalidades();
                printf("Insira o ID da localidade ou 0 para inserir uma localidade nova.");
                int idInserido=getint();


                //Quero saber qual o Ultimo ID
                localidade localidades;
                
                FILE *fileloc;
                fileloc = fopen ("localidades.dat", "rb");
                
                if(fileloc==NULL){ 
                    perror("Erro na abertura do ficheiro.");
                return;
                }

                fseek(fileloc,0,SEEK_END);
                if(ftell(fileloc) == 0){
                    localidades.ID=1;
                }
                else{
                    fseek(fileloc,-sizeof(localidade),SEEK_CUR);
                    fread(&localidades,sizeof(localidade),1,fileloc);
                }

                //Validar o ID inserido
                do{
                    if(idInserido>0 && idInserido<=localidades.ID){
                    praias.IDLocalidade=idInserido;
                    }

                    else if(idInserido==0){
                        int idLocInserida = 0;
                        idLocInserida=inserirLocalidade();
                        if(idLocInserida==0){
                            return;
                        }
                        praias.IDLocalidade=idLocInserida;
                    }
                    else{
                        printf("Localidade inválida. Escreva o número correspondente à localidade ou insira 0 para adicionar uma nova localidade:");
                        printf("\nID ou 0\n");
                        idInserido = getint();
                    }

                }while(idInserido<0 || idInserido>localidades.ID);
                
                fsetpos(filepraia,&pos);
                fwrite(&praias,sizeof(praia),1,filepraia);
                printf("Praia alterada com sucesso.");
                fflush(filepraia);
                fclose(fileloc);
            }
        }
        fgetpos(filepraia,&pos);
    }
    fclose(filepraia);
}


void exportar(){
    
    praia praias;
    localidade localidades;
    
    FILE *fileexportar;
    fileexportar = fopen ("praias.csv","w");
    
    if(fileexportar==NULL){
        perror("Erro na abertura do ficheiro.");
    return;
    }

    FILE*filepraias;
    filepraias = fopen ("praias.dat","rb");

    if(filepraias == NULL){
        perror("Erro na abertura do ficheiro.");
    return;
    }

    FILE*fileloc;
    fileloc = fopen ("localidades.dat","rb");

    if(fileloc == NULL){
        perror("Erro na abertura do ficheiro.");
    return;
    }

    fprintf(fileexportar,"Nome Localidade; Nome Praia; Tipo Praia\n");

    while (fread(&praias,sizeof(praia),1,filepraias)) {
        while (fread(&localidades,sizeof(localidade),1,fileloc)){
            if(localidades.ID == praias.IDLocalidade){
                fprintf(fileexportar,"%s; %s; %s\n",localidades.nome,praias.nome,praias.Tipo);
            }
        }    
        rewind(fileloc);
    }
    fclose(fileexportar);
    fclose(fileloc);
    fclose(filepraias);
}


int main (){
    int op;
    do{
        system("clear");
        puts("Menu: \n");
        puts("1 - Inserir Praia");
        puts("2 - Inserir Localidade");
        puts("3 - Listar Praias");
        puts("4 - Listar Localidades");
        puts("5 - Listar Praias por Localidade");
        puts("6 - Procurar Praia");
        puts("7 - Alterar Localidade");
        puts("8 - Alterar Praia");
        puts("9 - Exportar Praias para ficheiro CSV");
        puts("0 - Sair");
        printf("\nEscolha:");
        op=getint();
        switch(op){
            //para que o default não aconteça com o zero
            case 0:
            break;

            case 1:
            inserirPraia();
            printf("Praia inserida com suscesso. Enter para voltar ao menu...");
            getchar();
            break;

            case 2:
            inserirLocalidade();
            printf("Localidade inserida com suscesso. Enter para voltar ao menu...");
            getchar();
            break;

            case 3:
            listarPraias();
            printf("Enter para voltar ao menu...");
            getchar();
            break;

            case 4:
            listarLocalidades(); 
            printf("Enter para voltar ao menu...");
            getchar();
            break;

            case 5:
            listarPraiasLoc(); 
            printf("Enter para voltar ao menu...");
            getchar();
            break;

            case 6:
            procurarPraias(); 
            printf("Enter para voltar ao menu...");
            getchar();
            break;

            case 7:
            alterarLocalidade(); 
            printf("Localidade alterada com suscesso. Enter para voltar ao menu...");
            getchar();
            break;

            case 8:alterarPraia();
            printf("Praia alterada com suscesso. Enter para voltar ao menu...");
            getchar();
            break;

            case 9:
            exportar(); 
            break;

            default:
            printf("Inseriu um número inválido. Enter para voltar ao menu...");
            getchar();
            break;
        }
    }while(op!=0);    
    return 0;
}
