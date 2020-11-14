// 2018019123 - Francisco Jose Ramos Rebelo de Amaral
// Turma P8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "locais.h"
#include "pessoas.h"

void clrScreen(){
    system("@cls||clear");
}


int main(){

    initRandom();
    int i=0;
    int flag=0;
    plocal loctab = NULL;
    pontpessoa pesstab = NULL;
    pontpessoa tab1=NULL;
    pontpessoa tab2 = NULL;
    pontpessoa tab3 = NULL;
    int iteracoes = 0;
    int tam = 0; // tamanho locais
    int tam_pessoas=0; // tamanho pessoas
    int k=0;
    int option;

    printf("###########################################################################\n");
    printf("#             Propagacao de um Virus - Francisco Amaral 2018019123        #\n");
    printf("#                                      _   _                              #\n");
    printf("#                                    .-_; ;_-.                            #\n");
    printf("#                                   / /     \\ \\                           #\n");
    printf("#                                  | |       | |                          #\n");
    printf("#                                   \\ \\.---./ /                           #\n");
    printf("#                               .-\"\~   .---.   ~\"\-.                       #\n");
    printf("#                             ,`.-~/ .'`---`'. \\~-.`,                     #\n");
    printf("#                             '`   | | \\(_)/ | |   `'                     #\n");
    printf("#                             ,    \\  \\ | | /  /    ,                     #\n");
    printf("#                             ;`'.,_\\  `-'-'  /_,.'`;                     #\n");
    printf("#                              '-._  _.-'^'-._  _.-'                      #\n");
    printf("#                                  ``         ``                          #\n");

    // -------- FASE PREPARACAO ------------ //
    loctab = iniciaLoc(&tam);

    for(i=0;i<tam;i++){
        printf("ID = %d\n",loctab[i].idlocal);
        printf("\tcapacidade = %d\n",loctab[i].capacidade);
        printf("Ligacoes: [%d]  [%d]  [%d]\n\n", loctab[i].liga[0], loctab[i].liga[1], loctab[i].liga[2]);
    }
    printf("Local carregado com sucesso!\n\n");
    pesstab = iniciaPessoa(&tam_pessoas,pesstab,tam,loctab);

    i = 0;

do{
    printf("\n\n\t\t--------------- MENU ----------------\n\n");
    printf("\t 1 - Avancar 1 iteracao na simulacao\n\n");
    printf("\t 2 - Apresentar estatistica\n\n");
    printf("\t 3 - Adicionar doente\n\n");
    printf("\t 4 - Transferir pessoas\n\n");
    printf("\t 5 - Voltar iteracoes atras\n\n");
    printf("\t 6 - Terminar simulacao\n\n");



    do{
    scanf("%d", &option);
    }while(option>6 || option<1);
    // clrScreen();
    // printf("limpa")
    fseek(stdin,0,SEEK_END); // limpar o buffer
// FASE SIMULAÇÃO
// PREPARAR A TAXA DE DISSEMINAÇÃO



    switch (option) {
 // ---------- FASE PREPARACAO --- FEITA ----------------
    case 1:
        pesstab = taxaDiss(pesstab,tam_pessoas);
        probRecuperacao(pesstab);
        duracaoMax(pesstab);
        aumentadias(pesstab);
        if(i == 0){
            tab3 = avancaIte(pesstab);
            }
        if(i == 1){
            tab2 = avancaIte(tab3);
            tab3 = avancaIte(pesstab);
            }

        if(i == 2){
            tab1 = avancaIte(tab2);
            tab2 = avancaIte(tab3);
            tab3 = avancaIte(pesstab);
            flag = 1;
            }
        /* pontpessoa b2 = tab2;
        while(b2 != NULL){
            printf("B2 -> %s\n",b2->id);
            b2 = b2->prox;
        }
        pontpessoa b = tab1;
        while(b != NULL){
            printf("B1 = %s",b->id);
            b = b->prox;
        }
       pontpessoa b3 = tab3;
        while(b3 != NULL){
            printf("B3 -> %s\n",b3->id);
            b3 = b3->prox;
            system("pause");
        } */ // DEBUGGING
       /* if(i >= 3){
            tab1 = tab2;
            tab2 = tab3;
            tab3 = pesstab;

            tab1 = avancaIte(tab2);
            tab2 = avancaIte(tab3);
            tab3 = avancaIte(pesstab);
            i=0;
            break;
        }*/
        i++;
        k++;
        if(flag == 1)
            i=2;
        /* printf("AQUI K2%d\n",k);
        printf("AQUI I2 %d\n",i);
        printf("???\n"); */
        break;
    case 2:
        apresentaEstat(pesstab,loctab,tam_pessoas,tam);
        break;
    case 3:
         pesstab = adicionaPessoa(pesstab,loctab,&tam_pessoas,tam);
        break;
    case 4:
        pesstab = movePessoas(pesstab,loctab,tam,tam_pessoas);
        break;
    case 5:
        do{
        printf("Numero de iteracoes a andar para tras (minimo de 1 maximo de 3 | -1 para sair desta opcao): ");
        scanf("%d",&iteracoes);
        }while(iteracoes < 1 && iteracoes > 4);
        if(iteracoes == -1)
            break;
        if(k == 0){
            printf("nao ha iteracoes para tras\n");
            break;
        }
        if(iteracoes > k){
            printf("nao ha %d iteracoes da simulacao no historico\n",iteracoes);
            break;
        }
        if(iteracoes == 1){
            pesstab = avancaIte(tab3);
        }
        if(iteracoes == 2){
            pesstab = avancaIte(tab2);
        }
        if(iteracoes == 3){
            pesstab = avancaIte(tab1);
        }
        break;
    case 6:
        writeReport(pesstab,loctab,tam_pessoas,tam,k);
        writelastIt(pesstab,loctab);
        break;
    default:
        break;
    }
    }while(option != 6);




    libertaLista(pesstab);
    libertaLista(tab1);
    libertaLista(tab2);
    libertaLista(tab3);


    free(loctab);

    return 0;
}
