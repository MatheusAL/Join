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
struct dados{
    char **matriz;

};

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
void salva(char *nome, dados *p, int tam,int coluna){ //funçao para salvar no arquivo
    ofstream file1;
    file1.open(nome);
    for(int cont=0;cont<tam;cont++){
        for(int cont2=0;cont2<coluna;cont2++){
            if(cont2==coluna-1){
                file1<<p[cont].matriz[cont2];
            }
            else{
                file1<<p[cont].matriz[cont2]<<'\t';
            }
        }
        file1<<'\n';
    }
    file1.close();
}


int Ordena(char *nome,int m){
    srand (time(NULL));
    int cont=0,j=0,i=0;
    int coluna=0;
    char c,*findcol;
    ifstream file;
    file.open(nome);
    dados *p=new dados[m];
    char *auxiliar=new char[1000000];
    //ACHA AQUANTIDADE DE COLUNAS
    file.getline(auxiliar,10000,'\n');
    findcol=strtok(auxiliar,"\t");
    while(findcol){
        coluna++;
        findcol=strtok(NULL,"\t");
    }
    //alocaçao das colunas
    for(int cont=0;cont<m;cont++){
        p[cont].matriz=new char*[coluna];
    }
    file.close();// fecha aqui pra começar a leitura do 0.
    //fim alocacao colunas


    //////////Leitura dos dados
    file.open(nome);
    while(!file.eof()){
        char *s;
        file.getline(auxiliar,10000,'\n');
        s=strtok(auxiliar,"\t");
        while(s){
            int size=strlen(s);
            p[i].matriz[j]=new char[size];
            strcpy((p[i].matriz[j]),s);
            //cout<<p[i].matriz[j]<<'\t';
            j++;
            s=strtok(NULL,"\t");
            if(j==coluna){
                j=0;
                i++;
            }    
        }
        if(i==m){ //quando sao lidas m linhas salva o arquivo
            cont++;
            //qsort(matriz,m,sizeof(char),compara);
            char temp[5];
            for(int cont=0;cont<5;cont++){
                temp[cont]= 97 + rand() % 26;;
            }
            salva(temp,p,m,coluna);
            i=0;
        }
    }
    if(i>0){ // se sobrarem linhas
        cont++;
        //qsort(matriz,i,sizeof(char),compara);
        char temp[5];
        for(int cont=0;cont<5;cont++){
            temp[cont]= 97 + rand() % 26;;
        }
        salva(temp,p,i,coluna);
    }
    file.close();
    //desaloca matriz
    for(int cont=0;cont<m;cont++){
        delete[] p[cont].matriz;
    }
    delete []auxiliar;
    return cont; // futuramente o numero de arquivos criados
}

/*void MergeSortExterno(char *nome,int m){ //funçao futura
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