#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Dados{
    char **matriz;
};

struct Conjunto{
    char **matriz;
    int ind;
};

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

void insertionSortConjunto(Conjunto *p, int tam, int col){
    Conjunto chave;
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

void join(char *joined, int ncol1, int ncol2, int *l1, int *l2, int size){
    Conjunto *p;
    p=new Conjunto[2];
    bool foi=false;
    ifstream *arq;
    arq=new ifstream[2];
    ofstream saida(joined);
    char *aux,*c;
    aux=new char[2];
    int cont=0,x;

    p[0].matriz=new char*[ncol1];
    p[1].matriz=new char*[ncol2];
    
    for(int j=0;j<ncol1;j++){
        p[0].matriz[j]=new char[2];
    }
    for(int j=0;j<ncol2;j++){
        p[1].matriz[j]=new char[2];
    }


    arq[0].open("Ordenado1.txt");
    arq[1].open("Ordenado2.txt");

    for(int i=0;i<2;i++){
        arq[i].getline(aux,1000000);
        c=strtok(aux,"\t");
        for(int j=0;c!=NULL;j++){
            strcpy(p[i].matriz[j],c);
            c=strtok(NULL,"\t");
        }
    }
    while(1){
        while(!foi){
            if(atoi(p[0].matriz[l1[cont]])==atoi(p[1].matriz[l2[cont]]))
                x=0;
            else if(atoi(p[0].matriz[l1[cont]])<atoi(p[1].matriz[l2[cont]]))
                x=-1;
            else
                x=1;
    
            if(x==0){
                cont++;
                if(cont==size){
                    foi=true;
                }
                continue;
            }
            else if(x<0){
                arq[0].getline(aux,1000000);
                c=strtok(aux,"\t");
                for(int j=0;c!=NULL;j++){
                    strcpy(p[0].matriz[j],c);
                    c=strtok(NULL,"\t");
                }
            }
            else{
                arq[1].getline(aux,1000000);
                c=strtok(aux,"\t");
                for(int j=0;c!=NULL;j++){
                    strcpy(p[1].matriz[j],c);
                    c=strtok(NULL,"\t");
                }
            }
            cont=0;
        }

        for(int i=0;i<size;i++){
            saida << p[0].matriz[l1[i]] << "\t";
        }

        for(int i=0;i<ncol1;i++){
            bool dif=true;
            for(int j=0;j<size;j++){
                if(i==l1[j]){
                    dif=false;
                    break;
                }    
            }
            if(dif){
                saida << p[0].matriz[i] << "\t";
            }
        }

        for(int i=0;i<ncol2;i++){
            bool dif=true;
            for(int j=0;j<size;j++){
                if(i==l2[j]){
                    dif=false;
                }    
            }
            if(dif){
                saida << p[1].matriz[i] << "\t";
            }
        }
        saida << "\n";

        cont=0;

        if(arq[0].peek()==-1)
            break;
        if(arq[1].peek()==-1)
            break;
        
        foi=false;
        
        arq[0].getline(aux,1000000);
        c=strtok(aux,"\t");
        for(int j=0;c!=NULL;j++){
            strcpy(p[0].matriz[j],c);
            c=strtok(NULL,"\t");
        }

        arq[1].getline(aux,1000000);
        c=strtok(aux,"\t");
        for(int j=0;c!=NULL;j++){
            strcpy(p[1].matriz[j],c);
            c=strtok(NULL,"\t");
        }
    }

    for(int j=0;j<ncol1;j++)
        delete []p[0].matriz[j];
    for(int j=0;j<ncol2;j++)
        delete []p[1].matriz[j];
        
    for(int i=0;i<2;i++)
        delete []p[i].matriz;
    delete []aux;
    delete []p;
    delete []arq;

}

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
    delete []aux;
    return n;
}

void grava(Dados *p, int m, int col,int num, int ind){
    ofstream saida;
    saida.open("Temp"+to_string(ind) +"_"+ to_string(num) +".txt");
    for(int i=0;i<m;i++){
        for(int j=0;j<col;j++){
            saida << p[i].matriz[j] << "\t";
        }
        saida << "\n";
    }
    saida.close();
}

void intercala(int a, int narq, int ncol, int *l, int size, int nlinhas){
    Conjunto *p;
    ifstream *arq;
    ofstream saida;
    saida.open("Ordenado"+to_string(a)+".txt");
    char *c, *aux;
    int ultimo,cont=0;
    int x;
    p=new Conjunto[narq];
    aux=new char[2];
    arq=new ifstream[narq];

    for(int i=0;i<narq;i++)
        p[i].matriz=new char*[ncol];
    
    for(int i=0;i<narq;i++)
        for(int j=0;j<ncol;j++){
            p[i].matriz[j]=new char[2];
        }

    for(int i=0;i<narq;i++){
        arq[i].open("Temp"+to_string(a)+"_"+to_string(i+1)+".txt");
        p[i].ind=i;
    }

    for(int i=0;i<narq;i++){
        arq[i].getline(aux,1000000);
        c=strtok(aux,"\t");
        for(int j=0;c!=NULL;j++){
            strcpy(p[i].matriz[j],c);
            c=strtok(NULL,"\t");
        }
    }
    
    for(int k=0;k<nlinhas;k++){
        for(int i=size-1;i>=0;i--)
            insertionSortConjunto(p,narq,l[i]);

        for(int j=0;j<narq;j++){
            if(arq[p[j].ind].is_open()){
                for(int i=0;i<ncol;i++){
                    if(i!=ncol-1)
                        saida << p[j].matriz[i] << "\t";
                    else
                        saida << p[j].matriz[i];
                }
                saida << "\n";
                ultimo=p[j].ind;
                x=j;
                break;
            }
        }

        if(arq[ultimo].peek()!=-1){
            arq[ultimo].getline(aux,1000000);
            c=strtok(aux,"\t");
            for(int j=0;c!=NULL;j++){
                strcpy(p[x].matriz[j],c);
                c=strtok(NULL,"\t");
            }
        }
        else{
            arq[ultimo].close();
            for(int j=0;j<narq;j++){
                if(arq[p[j].ind].is_open()){
                    for(int i=0;i<ncol;i++){
                        if(i!=ncol-1)
                            saida << p[j].matriz[i] << "\t";
                        else
                            saida << p[j].matriz[i];
                    }
                    saida << "\n";
                    ultimo=p[j].ind;
                    x=j;
                    break;
                }
            }
            arq[p[x].ind].getline(aux,1000000);
            c=strtok(aux,"\t");
            for(int j=0;c!=NULL;j++){
                strcpy(p[x].matriz[j],c);
                c=strtok(NULL,"\t");
            }
            nlinhas--;
        }
    }
    
    for(int i=0;i<narq;i++)
        for(int j=0;j<ncol;j++)
            delete []p[i].matriz[j];
        
    for(int i=0;i<narq;i++)
        delete []p[i].matriz;

    saida.close();
    delete []arq;
    delete []p;
    delete []aux;
}

int ordenaArquivo(char *nome, int m, int size, int *l, int ind, int &ncol, int &nlinhas){
    Dados *p;
    char *aux,*c;
    int cont=0,k;
    int numarq=0,total;
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

        for(int i=size-1;i>=0;i--){
            insertionSort(p,m,l[i]);
        }

        ++numarq;
        grava(p,m,cont,numarq,ind);

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

        for(int i=size-1;i>=0;i--){
            insertionSort(p,k,l[i]);
        }

        grava(p,k,cont,++numarq,ind);
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<cont;j++)
            delete []p[i].matriz[j];
        
    for(int i=0;i<m;i++)
        delete []p[i].matriz;
    
    ncol=cont;

    delete []p;
    delete []aux;
    file.close();
    return numarq;
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
    int size=0, narq1, narq2, ncol1, ncol2;
    int nlinhas1, nlinhas2;
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

    narq1=ordenaArquivo(argc[4],m,size,lista1,1,ncol1,nlinhas1);    //ordenas em arquivos menores com M linhas
    narq2=ordenaArquivo(argc[5],m,size,lista2,2,ncol2,nlinhas2);

    intercala(1,narq1,ncol1,lista1,size,nlinhas1);  //termina a ordenacao externa, fazendo intercalacao
    intercala(2,narq2,ncol2,lista1,size,nlinhas2);

    join(argc[6],ncol1,ncol2,lista1,lista2,size);

    delete []l1;
    delete []l2;
    delete []lista1;
    delete []lista2;

    return 0;
}