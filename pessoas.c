// 2018019123 - Francisco Jose Ramos Rebelo de Amaral
// Turma P8
#include "locais.h"
#include "pessoas.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pontpessoa iniciaPessoa(int *total,pontpessoa p,int tam,plocal loctab){
        FILE *fp;
        char nome_fich[15];
        pessoa Teste;
        // char state = 'I';
        printf("Ficheiros disponiveis: pessoasA.txt e pessoasB.txt\n\n");

        printf("Nome do ficheiro: ");
        scanf("%s",nome_fich);
        //fgets(nome_fich,sizeof(nome_fich)-1,stdin);

        fp=fopen(nome_fich, "r");
        if(!fp)
        {
		printf("Erro no acesso ao ficheiro %s\n",nome_fich);
		exit(0);
        }


    while(!feof(fp)){
        if(fscanf(fp, "%s%d %c %d\n", Teste.id,&Teste.idade,&Teste.estado,&Teste.dias)<4){
            /* if(Teste.estado == 'I'){
                    printf("%s is imune!\n",Teste.id);
            }
            else{
                printf("%s is healthy!\n",Teste.id);
            } */
            Teste.dias = 0;
            /* printf("Nome= %s\n",Teste.id);
            printf("Idade = %d\n",Teste.idade);
            printf("Estado = %c\n",Teste.estado);

            printf("Dias infetado = %d\n\n",Teste.dias); */
        }
        /* else{
            printf("\n%s is sick!\n",Teste.id);
            printf("Nome= %s\n",Teste.id);
            printf("Idade = %d\n",Teste.idade);
            printf("Estado = %c\n",Teste.estado);
            printf("Dias infetado = %d\n\n",Teste.dias);
        } */

        if(Teste.idade <= 0){
                printf("Person %s age is incorrect\n Program will now end!\n", Teste.id);
                exit(0);
            }
        if(Teste.dias < 0){
                printf("Days infected of the person %s invalid\n Program will now end\n", Teste.id);
                exit(0);
            }
        (*total)++;

         p = criaLista(Teste,p,tam,loctab);
    }
    //*(total) = i;
    printf("numero total de pessoas inseridas na simulacao = %d\n", *total);
    fclose(fp);

    return p;
}


void preenche(pontpessoa p,pessoa Teste,int tam,plocal tab){
    int random = 0;
    int i,j=0;
    int random2 = 0; // para o caso da capacidade da sala estar cheia e ter de realocar a pessoa para outra sala
    random = intUniformRnd(0,tam-1); // arranja o random
    random2 = intUniformRnd(0,tam-1);
    //printf("1- %d\t2- %d\n",random,random2);
    p->idade = Teste.idade;
    p->estado = Teste.estado;
    p->dias = Teste.dias;
    p->localizacao = random; // inteiro para o array de locais
    // printf("Localizacao inicial = %d\n",p->localizacao);
    strcpy(p->id, Teste.id);
    // system("pause");
    /*printf("%s\n",p->id);
    printf("%c\n", p->estado);
    printf("%d\n",p->idade);
    printf("%d\n",p->dias);*/
    // printf("1111capacidade esta a %d\n",tab[random].capacidade);

    for(i=0;i<tam;i++){
        if(tab[i].capacidade == 0){
            j++;
        }
    }

    if(j == i){
        printf("Nao ha salas vazias,pessoa nao ira ser adicionada\n");
        return;
    }

     if((tab[random].capacidade) == 0){
        printf("local cheio, pessoa %s vai ser realocada\n",p->id);
        while(random == random2){
            //printf("eram iguais\n");
            random2 = intUniformRnd(0,tam-1);
            //printf("2 v2- %d",random2);
            //system("pause");
        }
        p->localizacao = random2;
        printf("Localizacao updated = %d\n",p->localizacao);
       (tab[random].capacidade)++;
    }
    (tab[random].capacidade)--;

	p->prox = NULL;
}

pontpessoa criaLista(pessoa Teste, pontpessoa p,int tam,plocal loctab){
    pontpessoa novo,aux;

    //1. Alocar espaco
    novo = malloc(sizeof(pessoa));
    if(novo == NULL){
        printf("Erro na alocacao de memoria\n");
        return p;
    }

    preenche(novo,Teste,tam,loctab);

    if(p == NULL)// Lista vazia
        p = novo;
    else{
        aux = p;
        while(aux->prox != NULL)
            aux = aux->prox;
            aux->prox = novo;
    }
    return p;
}



pontpessoa adicionaPessoa(pontpessoa p,plocal l,int *tam_pessoas,int tam){
    pontpessoa novo,aux;
    int i;
    int destino,sitio;
    int flag = 0;

    //1. Alocar espaco
    novo = malloc(sizeof(pessoa));
    if(novo == NULL)
        return p;

    // 2. Preencher
    printf("Id da sala: ");
    scanf("%d",&destino);
    printf("Identificador: ");
	scanf(" %99[^\n]",novo->id);
	printf("Idade: ");
	scanf(" %d", &novo->idade);
	printf("Numero de dias de infecao: ");
	scanf("%d", &novo->dias);
	novo->estado = 'D';


    for(i=0;i<tam;i++){
        if(l[i].idlocal == destino){
            flag = 1;
            sitio = i;
            break;
        }
    }

    if(flag == 0){
        printf("Id de sala nao existe\n");
        return p;
    }

    if(l[sitio].capacidade == 0){
        printf("Local com o id %d esta cheio,pessoa nao sera adicionada\n",l[sitio].capacidade);
        return p;
    }


    p->localizacao = sitio;

     if(p == NULL)// Lista vazia
        p = novo;
    else{
        aux = p;
        while(aux->prox != NULL)
            aux = aux->prox;
            aux->prox = novo;
    }
    (*tam_pessoas)++;

    return p;
}


pontpessoa movePessoas(pontpessoa p,plocal l,int tam,int total){
    pontpessoa novo;
    novo = p;
    int contador=0;

    int idOrigem=0,idDestino=0,num;
    int aux=0;
    int i,j,flag=0,flag1=0;
    int origem; // guarda-me a posicao do array de locais onde ta o id de origem
    int destino; // guarda-me a posicao do array de locais onde ta o id de destino
    // verificacoes
    do{printf("Id de origem: ");
    scanf("%d",&idOrigem);
    }while(idOrigem < 0);

    do{printf("Id destino: ");
    scanf("%d",&idDestino);
    }
    while(idDestino < 0 );

    for(j=0;j<tam;j++){
        if(l[j].idlocal == idDestino){
            flag1 = 1;
            destino = j;
            break;
        }
    }

    for(i=0;i<tam;i++){
        if(l[i].idlocal == idOrigem){
            flag = 1;
            origem = i;
            break;
        }
    }
    if(flag == 0){
        printf("Id de origem nao existe\n");
        return p;
    }

    if(flag1 == 0){
        printf("Id de destino nao existe\n");
        return p;
    }
    //printf("O id de origem %d esta na posicao %d\n",idOrigem,m);
    //printf("O id de origem %d esta na posicao %d\n",idDestino,k);

    do{
    	printf("Numero de pessoas a mover: ");
    	scanf("%d",&num);
	}while(num < 0);

	if(l[destino].capacidade == 0){
        printf("Sala cheia, pessoas nao irao ser movidas");
        return p;
	}


    // verificar as ligacoes;

    // fazer uma X = random e quando outra Y for = X eq entra e transfere; GARANTE RANDOMIZA?O

    while(novo != NULL){
        if(novo->localizacao == origem)
            contador++;

        novo = novo->prox;
    }

    if(contador == 0){
    	printf("Nao ha pessoas nesse id para mover!\n");
        return p;
    }

    if(contador < num)
        num = contador;


    novo = p;

    if(novo == NULL)
        printf("nao ha vazias para mover!\n");
    else
        while(aux != num){
              while(novo != NULL){
                    if(novo->localizacao == origem){
                        if(probEvento((float)num/(float)contador) == 1){
                            novo->localizacao = destino;
                            aux++;
                        }
                if(aux == num)
                    break;
                    }
                novo = novo->prox;
              }
              novo = p;
        }
    return p;
}

pontpessoa taxaDiss(pontpessoa p,int tamp){
    int num_infetados = tamp *0.05;
    // printf("\n\t\nOK OKO %d",num_infetados);
    pontpessoa novo;
    char saude = 'S';
    int aux=0;
    int conta = 0;
    int infected = 0;

    novo = p;

    if(num_infetados == 0)
        return p;

    while(novo != NULL){
        if(novo->estado == saude){
            aux++;
        }
        novo = novo->prox;
    }

    if(aux==0){
        return p;
    }

    if(aux < num_infetados){
        num_infetados = aux;
    }

    novo = p;

    if(novo == NULL){
        printf("nao ha pessoas para avancar na iteracao\n");
        return p;
        }
    else
        while(conta != num_infetados){
                while(novo != NULL){
                    if(novo->estado == saude){
                            //printf("entrou1\n");
                        if(probEvento((float)num_infetados/(float)tamp)){
                            //printf("entrou2\n");
                            novo->estado = 'D';
                            infected++;
                            conta++;
                        }
                if(conta == num_infetados)
                    break;
                }
                novo = novo->prox;
            }
        novo = p;
    }

    printf("\n%d Pessoas contrairam o virus nesta iteracao!\n",infected);

    return p;
}

void aumentadias(pontpessoa p){
    pontpessoa novo;

    novo = p;

    if(novo == NULL){
        printf("nao ha pessoas para avancar na iteracao\n");
        return;
        }
    while(novo != NULL){
        novo->dias++;
        novo = novo->prox;
        }
}

void probRecuperacao(pontpessoa p){
    pontpessoa novo;
    novo = p;
    float taxa;
    int imune=0;
    int saudavel = 0;
    char doente = 'D';
    if(novo == NULL){
        printf("nao ha pessoas para avancar na iteracao\n");
        return;
        }
    while(novo!= NULL){
            if(novo->estado == doente){
                taxa = (float)1/(float)(novo->idade);
                // printf("%f",taxa);
                if(probEvento(taxa) == 1){
                    novo->estado = 'S';
                    saudavel++;
                    novo->dias = 0;
                    if(probEvento(0.2) == 1){
                        // printf("esta imune\n");
                        imune++;
                        novo->estado = 'I';
                    }
                    // printf("entra\n");
                }
            }
        novo = novo->prox;
    }
    printf("%d pessoas ficaram saudaveis e %d ficaram imunes devido a recuperacao!\n",saudavel,imune);
}

void duracaoMax(pontpessoa p){
    // dividir idade da pessoa por dez e somar aos 5
    pontpessoa novo;
    int dezenas;
    char doente = 'D';
    int saudavel=0;
    int imune=0;

    novo = p;

    if(novo == NULL){
        printf("nao ha pessoas para avancar na iteracao\n");
        return;
        }

    while(novo!= NULL){
        // printf("%s %d\n",novo->id,novo->idade);
        dezenas = (novo->idade)/10;
        //printf("dias = %d",dezenas);
        if(novo->estado == doente){
            if(novo->dias >= (5+dezenas)){
                //printf("here we go");
                novo->estado = 'S';
                novo->dias = 0;
                saudavel++;
                if(probEvento(0.2) == 1){
                        // printf("esta imune\n");
                        novo->estado = 'I';
                        imune++;
                    }
            }
        }
    novo = novo->prox;
}
    printf("%d pessoas ficaram saudaveis e %d ficaram imunes devido a ultrapassarem a duracao maxima do virus!\n",saudavel,imune);
}



void apresentaEstat(pontpessoa p,plocal l,int tampessoas,int tam){
    pontpessoa novo;
    novo = p;
    char doente = 'D';
    char imune = 'I';
    char saude = 'S';

    float taxaS,taxaD,taxaI;
    int s=0,d=0,i=0;

    if(novo == NULL){
        printf("Nao ha pessoas carregadas para a simulacao\n");
    }
    printf("\n\n\t\t--------------- Estatistica ----------------\n\n");
    printf("Identificador\tIdade\tEstado\tDias\tSala\t   Id do local\n");

        while(novo!=NULL){
            if(novo->estado == saude)
                s++;
            if(novo->estado == doente)
                d++;
            if(novo->estado == imune)
                i++;

            printf("%-10s\t%d\t%c\t%d\tsala = %d\tid do local = %d\n",novo->id,novo->idade,novo->estado,novo->dias,novo->localizacao, l[novo->localizacao].idlocal);

            novo = novo->prox;

        }

        taxaS = ((float)s/tampessoas) * 100;
        taxaD = ((float)d/tampessoas) * 100;
        taxaI = ((float)i/tampessoas) * 100;

        printf("Total de pessoas a participar na simulacao= %d\n",tampessoas);
        printf("Numero de espacos no local = %d\n",tam);
        printf("Taxa de pessoas saudaveis = %.2f%%\n",taxaS);
        printf("Taxa de pessoas doentes = %.2f%%\n",taxaD);
        printf("Taxa de pessoas imunes = %.2f%%\n",taxaI);
}



pontpessoa avancaIte(pontpessoa p){
    pontpessoa aux,novo,fim;
    novo = NULL;
    aux = p;
    fim = NULL;

    if(p == NULL){
        printf("lista vazia\n");
        return p;
    }

    while(aux != NULL){
            // para o primeiro no
        if(novo == NULL){
            novo = malloc(sizeof(pessoa));
            if(novo == NULL){
                printf("Erro na alocacao de memoria\n");
                return p;
            }
            novo->idade = aux->idade;
            novo->estado = aux->estado;
            novo->dias = aux->dias;
            novo->localizacao = aux->localizacao;
            strcpy(novo->id,aux->id);
            novo->prox = NULL;
            fim = novo;
        }
        else{
            fim->prox = malloc(sizeof(pessoa));
            if(fim->prox == NULL){
                printf("Erro na alocacao de memoria\n");
                return p;
            }
            fim = fim->prox;
            fim->idade = aux->idade;
            fim->estado = aux->estado;
            fim->dias = aux->dias;
            fim->localizacao = aux->localizacao;
            strcpy(fim->id, aux->id);
            fim->prox = NULL;
        }
        aux = aux ->prox;
    }

    fim = novo;

    /*while(fim != NULL){
        printf("%s\n",fim->id);
        printf("CHECK%d\n",fim->dias);
        printf("CHECK CHECK %d\n",fim->idade);
        system("pause");
        fim = fim->prox;
    } */

    return novo;
}

void writeReport(pontpessoa p,plocal l,int tampessoas,int tam,int k){
	char doente = 'D';
    char imune = 'I';
    char saude = 'S';
    pontpessoa novo;
    novo = p;

    float taxaS,taxaD,taxaI;
    int s=0,d=0,i=0;
    FILE *f;

    f = fopen("report.txt","wt");

    if(!f){
        fprintf(stderr,"Erro a aceder ao ficheiro report.txt para escrita.\n");
        return;
    }
    // escreve no ficheiro
    fprintf(f,"Foram efetuadas %d iteracoes nesta simulacao\n",k);
    fprintf(f,"Populacao existente na simulacao\n");
    fprintf(f,"\nIdentificador\tIdade\tEstado\tDias\tSala\tId do local\n\n");


    while(novo != NULL){
    	if(novo->estado == saude)
             s++;
        if(novo->estado == doente)
             d++;
        if(novo->estado == imune)
              i++;
        fprintf(f,"%-10s\t%d\t%c\t%d\t%d\t%d\n",novo->id,novo->idade,novo->estado,novo->dias,novo->localizacao, l[novo->localizacao].idlocal);
        fprintf(f,"\n");
        novo = novo->prox;
    }

    taxaS = ((float)s/tampessoas) * 100;
    taxaD = ((float)d/tampessoas) * 100;
    taxaI = ((float)i/tampessoas) * 100;

    fprintf(f,"Total de pessoas a participar na simulacao= %d\n",tampessoas);
    fprintf(f,"Numero de espacos no local = %d\n",tam);
    fprintf(f,"Taxa de pessoas saudaveis = %.2f%%\n",taxaS);
    fprintf(f,"Taxa de pessoas doentes = %.2f%%\n",taxaD);
    fprintf(f,"Taxa de pessoas imunes = %.2f%%\n",taxaI);

    fclose(f);
}


void writelastIt(pontpessoa p,plocal l){
    FILE *f;
    pontpessoa novo;
    novo = p;
    char nome_fich[100];

    printf("Nome para guardar o ficheiro: ");
    fgets(nome_fich,sizeof(nome_fich)-1,stdin);
    nome_fich[strlen(nome_fich) - 1] = '\0';

    f = fopen(nome_fich,"wt");

    if(!f){
        fprintf(stderr,"Erro a aceder ao ficheiro %s para escrita.\n",nome_fich);
        return;
    }
    // escreve no ficheiro
    fprintf(f,"Estado da populacao na ultima iteracao da simulacao\n");
    fprintf(f,"\nIdentificador\tIdade\tEstado\tDias\tSala\tId do local\n\n");


    while(novo != NULL){
        fprintf(f,"%-10s\t%d\t%c\t%d\t%d\t%d\n",novo->id,novo->idade,novo->estado,novo->dias,novo->localizacao, l[novo->localizacao].idlocal);
        fprintf(f,"\n");
        novo = novo->prox;
    }
    fclose(f);
}


void libertaLista(pontpessoa p){

        pontpessoa aux;

        while(p != NULL){
            aux = p;
            p = p->prox;
            free(aux);
        }
}

