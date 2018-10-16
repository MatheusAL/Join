#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>

int Ordena(char *nome){
    int V[N];
    int cont=0,total=0,j=0,i=0;
    char novo[20],c;
    ifstream file;
    file.open(nome);
    while(!file.eof){
        c=file.get()
        if(c!='\t' && c!='\n')
            file>>matriz[j][i];
        
    }
}


void MergeSortExterno(char *nome){
    int qtdfiles;
    char novo[20];
    qtdfiles=Ordena(nome);
    int cont;
    int K = N/(qtdfiles+1);
    remove(nome);
    merge(nome,qtdfiles,K);

    for(cont=0;cont<qtdfiles;cont++){
        remove(novo);
    }

}


int main(int argc,char *argv[]){


    int m;
    m=atoi(argv[1]);

    MergeSortExterno(argv[2]);
}