// 2018019123 - Francisco Jose Ramos Rebelo de Amaral
// Turma P8
#ifndef PESSOAS_H
#define PESSOAS_H

typedef struct persons pessoa;
typedef struct persons* pontpessoa;

struct persons{
    char id[200];
    int idade;
    char estado;
    int dias;
    pontpessoa prox;
    int localizacao;
    };

pontpessoa iniciaPessoa(int *total,pontpessoa p,int tam,plocal tab);
pontpessoa criaLista(pessoa Teste, pontpessoa p,int tam,plocal tab);
void preenche(pontpessoa p,pessoa Teste,int tam,plocal tab);
pontpessoa adicionaPessoa(pontpessoa p,plocal local,int *tam_pessoas,int tam);
pontpessoa movePessoas(pontpessoa p,plocal l,int tam,int total);
pontpessoa taxaDiss(pontpessoa p,int tamp);
pontpessoa avancaIte(pontpessoa p);
void aumentadias(pontpessoa p);
void probRecuperacao(pontpessoa p);
void duracaoMax(pontpessoa p);
void apresentaEstat(pontpessoa p,plocal l,int tampessoas,int tam);
void writeReport(pontpessoa p,plocal l,int tampessoas,int tam,int k);
void writelastIt(pontpessoa p,plocal l);
void libertaLista(pontpessoa p);



#endif PESSOAS_H
