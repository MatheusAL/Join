#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

/*struct arquivo{
    ifstream f;
    int posicao,max, *buffer;
}
*/
void leLista(int *l,int size,char *x){
    int j=0;
    for(int cont=0;cont<size;cont++){
        if(x[cont]!=','){
            l[j]=atoi(&x[cont]);
            j++;
        }
    }

}
/*
void merge(char *nome,int qtdfiles,int K){
    char novo[20];
    int *buffer= new int[k];

    arquivo *arq;
    arq=(arquivo*) new arquivo[qtdfiles];

    for(int cont=0;cont<qtdfiles;cont++){
        arq[cont].f = f.open(novo);
        arq[cont].max=0;
        arq[cont].pos=0;
        arq[cont].buffer=new int[k];
        preencheBuffer(&arq[cont],k);
    }
    int menor,qtdbuffer=0;
    while(procuraMenor)
}
*/
void salva(char *nome, char **matriz, int tam,int coluna){
    ofstream file1;
    file1.open(nome);
    for(int cont=0;cont<tam;cont++){
        for(int cont2=0;cont2<coluna;cont2++){
            if(cont2==coluna-1)
                file1<<matriz[cont][cont2];
            else
                file1<<matriz[cont][cont2]<<'\t';
        }
        file1<<'\n';
    }
    file1.close();
}


int Ordena(char *nome,int m){
    srand (time(NULL));
    int cont=0,total=0,j=0,i=0;
    int coluna=0;
    char c;
    ifstream file;
    file.open(nome);
    int *aux=new int[1000];

    //Descobrir o numero de colunas
    while(true){
        c=file.get();
        if(c=='\n')
            break;
        if(c!='\t' && c!='\n'){
            aux[coluna]=c;
            coluna++;
        }    
    }
    //alocacao da matriz de tamanho M x K
    char **matriz=new char *[m];
    for(int cont=0;cont<m;cont++){
        matriz[cont]=new char[coluna];
    }
    //acabou............
    for(int cont=0;cont<coluna;cont++){
        matriz[i][cont]=aux[cont];
    }
    delete [] aux;
    //////////////////////////////////

    i=1,j=0;
    //Leitura dos dados
    while(!file.eof()){
        c=file.get();
        if((c!='\t') && (c!='\n')&&(c!='\r')){
            matriz[i][j]=c;
            j++;
            if(j==coluna){
                j=0;
                i++;
            }
            if(i==m){
                cont++;
                //qsort(matriz,m,sizeof(char),compara);
                char temp[5];
                for(int cont=0;cont<5;cont++){
                    temp[cont]= 97 + rand() % 26;;
                }
                salva(temp,matriz,m,coluna);
                i=0;
            }
        }
    }
    if(i>0){
        cont++;
        //qsort(matriz,total,sizeof(char),compara);
        char temp[5];
        for(int cont=0;cont<5;cont++){
            temp[cont]= 97 + rand() % 26;;
        }
        salva(temp,matriz,i,coluna);
    }
    
    file.close();
    for(int cont=0;cont<m;cont++){
        delete[] matriz[cont];
    }
    delete[] matriz;
    return cont;
}

/*void MergeSortExterno(char *nome,int m){
    int qtdfiles;
    char novo[20];
    qtdfiles=Ordena(nome,m);
    int cont;
    int K = m/(qtdfiles+1);
    remove(nome);
    merge(nome,qtdfiles,K);

    for(cont=0;cont<qtdfiles;cont++){
        remove(novo);
    }

}
*/

int main(int argc, char *argv[]){
    int m,j;
    char *x;
    m=atoi(argv[1]);
    x=argv[2];
    int size=strlen(x);
    int sizelista=(size+1)/2;
    int *L1=new int[sizelista];
    int *L2=new int[sizelista];
    //Leitura das listas de campos
    leLista(L1,size,x);
    x=argv[3];
    leLista(L2,size,x);
    //Término
    Ordena(argv[4],m);
    delete []L1;
    delete []L2;
    
}