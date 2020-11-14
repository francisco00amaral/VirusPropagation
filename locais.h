// 2018019123 - Francisco Jose Ramos Rebelo de Amaral
// Turma P8
#ifndef LOCAIS_H
#define LOCAIS_H

typedef struct sala local;
typedef struct sala *plocal;

struct sala{
    int idlocal;  // id numérico do local
    int capacidade; // capacidade máxima
    int liga[3];  // id das ligações (-1 nos casos não usados)
    };

plocal iniciaLoc(int *tam);

#endif LOCAIS_H
