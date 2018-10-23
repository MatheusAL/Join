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
void merge(dados *p,dados *aux,int s, int q, int m,int *L,int sizelista){ //Intercala	
    int tam= m-s;
	int i = s; //Cursor 1
	int j = q; //Cursor 2
	int k = 0;//Cursor para aux
    int x=0;
    int l=0; 
	while(i<q && j<m){
		if(strcmp(p[i].matriz[L[l]],p[j].matriz[L[l]])==0){
            while(true){
                //x=strcmp(p[i].matriz[0],p[j].matriz[0]);
                if(x<0){
                    aux[k++]=p[i++];
                    break;
                }
                if(x>0){
                    aux[k++]=p[j++];
                    break;
                }
                l++;
                x=strcmp(p[i].matriz[L[l]],p[j].matriz[L[l]]);
            }
        }
        else{
        	l=0;
        if(strcmp(p[i].matriz[L[l]],p[j].matriz[L[l]])<0)
			aux[k++] = p[i++];
		else
			aux[k++] = p[j++];
        }
	}
	while(i < q) //Dois while para preencher o restante
		aux[k++] = p[i++];
	while(j < m)
		aux[k++] = p[j++];
	for(k=0;k < tam; k++) //transferindo o ordenado p/ o original
		p[s+k].matriz = aux[k].matriz;
}

void mergeSort(dados *p,dados *aux,  int i, int m,int *L,int sizelista){ //Divide and conquer
	if(i<m-1){
		int meio= (i+m)/2;
		mergeSort(p,aux,i,meio,L,sizelista);
		mergeSort(p,aux,meio,m,L,sizelista);
		merge(p,aux,i,meio,m,L,sizelista); /* intercala */
	}
}

void mergeonly(dados *p, int m,int *L,int sizelista){
    dados *aux=new dados[m];
    mergeSort(p,aux,0,m,L,sizelista);
    delete[]aux;
}

/*
void mergeexterrrr(char *nome,int qtdfiles,int K){
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


int Ordena(char *nome,int m,int *L,int sizelista){
    srand (time(NULL));
    int cont=0,j=0,i=0;
    int coluna=0;
    char *findcol;
    //Vetor para guardar os nomes dos arquivos, depois isso vai ser feito na funçao mergesortexterno
    char **temp;
    temp=new char*[100];//ex
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
    file.getline(auxiliar,1000000,'\n');
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
            j++;
            s=strtok(NULL,"\t");
            if(j==coluna){
                j=0;
                i++;
            }
        }
        if(i==m){ //quando sao lidas m linhas salva o arquivo
            mergeonly(p,m,L,sizelista);
            salva(temp,cont,p,m,coluna);
            i=0;
            cont++;
            for(int cont=0;cont<m;cont++){
                for(int cont2=0;cont2<coluna;cont2++){
                    delete[] p[cont].matriz[cont2];
                }
            }
        }
    }
    if(i>0){ // se sobrarem linhas
        cont++;
        mergeonly(p,m,L,sizelista);
        salva(temp,cont,p,i,coluna);
        for(int cont=0;cont<i;cont++){
            for(int cont2=0;cont2<coluna;cont2++){
                delete[] p[cont].matriz[cont2];
            }
        }  
    }  
    file.close();
    //desaloca tamanho desnecessario
    for(int i=0;i<100;i++){
        delete[] temp[i];
    }
    delete []temp;
    //desaloca matriz
    for(int cont=0;cont<m;cont++){
        /*for(int cont2=0;cont2<coluna;cont2++){
            delete[] p[cont].matriz[cont2];
        }*/
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
    Ordena(argv[4],m,L1,sizelista);
    delete []L1;
    delete []L2;
    
}
