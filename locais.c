// 2018019123 - Francisco Jose Ramos Rebelo de Amaral
// Turma P8
#include "locais.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

plocal iniciaLoc(int *tam){
    FILE *f;
    local aux;
    plocal locals = malloc(sizeof(local));
    char nome_fich[15];
    int i;
    printf("Locais disponiveis: E1.bin, E2.bin e E3.bin\n\n");
    printf("Nome do Local: ");
    scanf("%s",nome_fich);
    //fgets(nome_fich,sizeof(nome_fich)-1,stdin);

    f=fopen(nome_fich, "rb");

	if(!f)
	{
		printf("Erro no acesso ao local\n");
		exit(0);
	}

	if(locals == NULL){
        printf("Alocao de memoria falhou\n");
        return 0;
	}

    fseek(f, 0, SEEK_SET); // desnecessario mas confirma que o ficheiro fica no inicio;

	printf("\nA carregar o local...\n");

	while(fread(&aux, sizeof(local), 1, f) == 1){
        for(i = 0;i < 3; i++){
            if(aux.liga[i] < 0 && aux.liga[i] != (-1)){
                fclose(f);
                free(locals);
                return 0;
            }
        }

        locals = realloc(locals,sizeof(local)*((*tam)+1));

        if(locals == NULL){
                printf("Realocacao falhou.\n");
                return 0;
            }

        locals[*tam] = aux;


	    (*tam)++;
	}
	printf("total de espacos no local %s = %d\n",nome_fich,*tam);
    fclose(f);

    return locals;
}

