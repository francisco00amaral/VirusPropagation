// 2018019123 - Francisco Jose Ramos Rebelo de Amaral
// Turma P8
#ifndef LOCAIS_H
#define LOCAIS_H

typedef struct sala local;
typedef struct sala *plocal;

struct sala{
    int idlocal;  // id num�rico do local
    int capacidade; // capacidade m�xima
    int liga[3];  // id das liga��es (-1 nos casos n�o usados)
    };

plocal iniciaLoc(int *tam);

#endif LOCAIS_H
