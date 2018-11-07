#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Dados{
    char **matriz;
};

int contaLinhas(char *nome){
    char *aux;
    int n=0;
    aux=new char[2];
    ifstream arq;
    arq.open(nome);
    
    while(arq.getline(aux,1000000)){
        ++n;
    }
    arq.close();
    return n;
}

void grava(Dados *p, int m, int col,int num, int ind){
    ofstream saida;
    char *c=new char[2];
    saida.open("Temp"+ to_string(ind) +"_"+ to_string(num) +".txt");
    for(int i=0;i<m;i++){
        for(int j=0;j<col;j++){
            saida << p[i].matriz[j] << "\t";
        }
        saida << "\n";
    }
    saida.close();
}

void trocaPonteiro(Dados *&a, Dados *&b){
    Dados *temp=a;
    a=b;
    b=temp;
}

void insertionSort(Dados *p, int tam, int col){
    Dados chave;
    int j;
    for(int i=1;i<tam;i++){
        chave=p[i];
        j=i-1;
        
        while((j>=0) && (atoi(p[j].matriz[col])>atoi(chave.matriz[col]))){
            p[j+1]=p[j];
            j--;
        }
        p[j+1]=chave;
    }
}

void ordenaArquivo(char *nome, int m, int *l, int ind){
    Dados *p;
    char *aux,*c;
    int cont=0,k;
    int nlinhas,numarq=0,total;
    nlinhas=contaLinhas(nome);
    aux=new char[2];
    p=new Dados[m];
    ifstream file;
    file.open(nome);
    file.getline(aux,1000000);
    c=strtok(aux,"\t");
    while(c!=NULL){
        cont++;
        c=strtok(NULL,"\t");
    }
    for(int i=0;i<m;i++)
        p[i].matriz=new char*[cont];
    
    for(int i=0;i<m;i++)
        for(int j=0;j<cont;j++){
            p[i].matriz[j]=new char[2];
        }
    
    
    file.close();
    file.open(nome);
    for(k=0;k<nlinhas/m;k++){
        for(int i=0;i<m;i++){
            file.getline(aux,1000000);
            c=strtok(aux,"\t");
            for(int j=0;c!=NULL;j++){
                strcpy(p[i].matriz[j],c);
                c=strtok(NULL,"\t");
            }
            
        }

        insertionSort(p,m,l[1]);
        insertionSort(p,m,l[0]);

        ++numarq;
        cout << numarq << endl;
        grava(p,m,cont,numarq,ind);

        for(int i=0;i<m;i++){
            for(int j=0;j<cont;j++)
                cout << p[i].matriz[j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    if(m*k<nlinhas){
        file.getline(aux,1000000);
        c=strtok(aux,"\t");
        for(k=0;!file.eof();k++){
            for(int j=0;c!=NULL;j++){
                strcpy(p[k].matriz[j],c);
                c=strtok(NULL,"\t");
            }
            file.getline(aux,1000000);
            c=strtok(aux,"\t");
        }

        insertionSort(p,k,l[1]);
        insertionSort(p,k,l[0]);

        grava(p,k,cont,++numarq,ind);

        for(int i=0;i<k;i++){
            for(int j=0;j<cont;j++)
                cout << p[i].matriz[j] << " ";
            cout << endl;
        }
        cout << endl;
    }
    file.close();
}

void leLista(int *lista, char *str){
    char *c;
    c=strtok(str,",");
    for(int i=0;c!=NULL;i++){
        lista[i]=atoi(c);
        c=strtok(NULL,",");
    }    
}

int main(int argv, char **argc){
    int m=atoi(argc[1]);
    int *lista1,*lista2;
    int size=0;
    char *l1,*l2,*c;
    l1=new char[2];
    l2=new char[2];
    strcpy(l1,argc[2]);
    strcpy(l2,argc[3]);

    c=strtok(argc[2],",");
    while(c!=NULL){
        c=strtok(NULL,",");
        size++;
    }
    
    lista1=new int[size];
    lista2=new int[size];

    leLista(lista1,l1);
    leLista(lista2,l2);

    ordenaArquivo(argc[4],m,lista1,1);
    ordenaArquivo(argc[5],m,lista2,2);

  /*  for(int i=0;i<size;i++)
        cout << lista1[i] << endl;*/

    return 0;
}