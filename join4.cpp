#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct arquivo{
    ifstream f;
    int posicao,tammax;
    char ***buffer;
};

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

/*int procuramenor(arquivos *arquivo, int qtdfiles,int m,int*menor){
    int i,idx=-1,x;
    for(int cont=0;cont<qtdfiles;cont++){
        if(arq[cont].pos<arq[cont].tammax){
            if(idx=-1)
                idx=i;
            else{
                x=strcmp(arq[cont].buffer[arq[i].pos],arq[idx].buffer[arq[idx].pos])
                if(x==0)
                    idx=i;
            }
        }
    }
    if(idx !=-1){
        *menor=arq[idx].buffer[arq[idx].pos];
        arq[idx].pos++;
        if(arq[idx].pos==arq[idx].tammax)
            preencheBuffer(&arq[idx],m);
        return 1;
    }
    else
        return 0;
}*/


void carregaDados(arquivo *arquivo,int K,int coluna){
    int i=0,j=0;
    arquivo->posicao=0;
    arquivo->tammax=0;
    char *auxiliar=new char[1000000];
    for(int cont=0;cont<K;cont++){
        arquivo->buffer[cont]=new char*[coluna];
    }
    for(int cont=0;cont<K;cont++){
        if(!arquivo->f.eof()){
            char *s;
            int size=0;
            arquivo->f.getline(auxiliar,10000,'\n');
            s=strtok(auxiliar,"\t");
            while(s){
                size=strlen(s);
                arquivo->buffer[i][j]=new char[size+1];
                strcpy((arquivo->buffer[i][j]),s);
                j++;
                s=strtok(NULL,"\t");
                if(j==coluna){
                    j=0;
                    i++;
                }
            }
        }
        else{
            arquivo->f.close();
            break;
        }
    }

    delete [] auxiliar;
}
void mergeex(char *nome,int qtdfiles,int m,int *L,int sizelista,char **temp,int coluna){
    //char novo[20];
    dados *buffer= new dados[m];
    arquivo *arq;
    arq=(arquivo*) new arquivo[qtdfiles];
    for(int cont=0;cont<qtdfiles;cont++){
        arq[cont].f.open(temp[cont]);
        arq[cont].tammax=0;
        arq[cont].posicao=0;
        arq[cont].buffer=new char**[m];
        carregaDados(&arq[cont],m,coluna);
    }
    int menor,qtdbuffer=0;
    /*while(procuraMenor(arq,qtdfiles,m,&menor)==1){
        buffer[qtdbuffer]=menor;
        qtdbuffer++;
        if(qtdbuffer==m){
            salva(temp,buffer,qtdbuffer);
            qtdbuffer=0;
        }
    }*/
    //liberando a memoria dos arquivos, colunas e itens
    for(int cont=0;cont<qtdfiles;cont++){
        for(int cont2=0;cont2<m;cont2++){
            for(int cont3=0;cont3<coluna;cont3++){
                delete [] arq[cont].buffer[cont2][cont3];
            }
            delete[] arq[cont].buffer[cont2];
        }
        delete [] arq[cont].buffer;
    }
    delete []arq;
    delete []buffer;
}

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


int Ordena(char *nome,int m,int *L,int sizelista,char **temp,int &coluna){
    int cont=0,j=0,i=0;
    //int coluna=0;
    char *findcol;
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
        int size=0;
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
    /*for(int i=0;i<100;i++){
        delete[] temp[i];
    }
    delete []temp;*/
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

void MergeSortExterno(char *nome,int m,int *L,int sizelista){ //funçao futura
    srand (time(NULL));
    int qtdfiles,coluna=0;
    char **temp;
    temp=new char*[100];
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
    //alocaçao dos nomes dos vetores devera ser feita aqui
    qtdfiles=Ordena(nome,m,L,sizelista,temp,coluna);
    int cont;
    //int K = m/(qtdfiles+1);
    //remove(nome);
    mergeex(nome,qtdfiles,m,L,sizelista,temp,coluna);
    /*for(cont=0;cont<qtdfiles;cont++){ //desalocaçao dos nomes?
        remove(novo);
    }*/
    for(int i=0;i<100;i++){
        delete[] temp[i];
    }
    delete []temp;
}
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
    //Ordena(argv[4],m,L1,sizelista);
    MergeSortExterno(argv[4],m,L1,sizelista);
    delete []L1;
    delete []L2;
    
}