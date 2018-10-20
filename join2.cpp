#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
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
int compara(const void *a, const void *b) {
    
    int x=(strcmp((*(struct dados*)a).matriz[0], (*(struct dados *) b).matriz[0]));
    
    return x;
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
void salva(char **nome,int namefile,dados *p, int tam,int coluna){ //funçao para salvar no arquivo
    ofstream file1;
    file1.open(nome[namefile]);
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
    //Vetor para guardar os nomes dos arquivos, depois isso vai ser feito na funçao mergesortexterno
    char **temp=new char*[100];//ex
    for(int cont=0;cont<100;cont++){
        temp[cont]=new char[11];
    }
    for(int cont=0;cont<100;cont++){
        for(int namefile=0;namefile<11;namefile++){
            if(namefile==10)
                temp[cont][namefile]='\0';
            else
                temp[cont][namefile]= 97 + rand() % 26;;
        }
    }
    /////////NOMES DEFINIDOS//////////////

    ifstream file;
    file.open(nome);
    dados *p=new dados[m];
    char *auxiliar=new char[1000000];//alocaçao de tamanho desnecessario para ler a linha
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
        int size=0;;
        file.getline(auxiliar,10000,'\n');
        s=strtok(auxiliar,"\t");
        while(s){
            size=strlen(s);
            p[i].matriz[j]=new char[size+1];
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
            qsort(p,m,sizeof(dados),compara);
            salva(temp,cont,p,m,coluna);
            i=0;
            cont++;
        }
    }
    if(i>0){ // se sobrarem linhas
        cont++;
        qsort(p,i,sizeof(dados),compara);
        /*for(int namefile=0;namefile<10;namefile++){
            temp[cont][namefile]= 97 + rand() % 26;;
        }*/
        salva(temp,cont,p,i,coluna);
        
    }
    file.close();
    //desaloca tamanho desnecessario
    for(int i=100;i>cont;i--){
        delete[] temp[i];
    }
    delete []temp;
    /*for(int i=100;i>cont;i--){
        free(temp[cont]);
    }
    free(temp);*/
    //desaloca matriz
    for(int cont=0;cont<m;cont++){
        for(int cont2=0;cont2<coluna;cont2++){
            delete[] p[cont].matriz[cont2];
        }
        delete [] p[cont].matriz;
    }
    delete []p;
    delete []auxiliar;
    return cont; // futuramente o numero de arquivos criados
}

/*void MergeSortExterno(char *nome,int m){ //funçao futura
    int qtdfiles;
    //alocaçao dos nomes dos vetores devera ser feita aqui
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