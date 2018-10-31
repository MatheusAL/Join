#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

/*struct arquivo{
    ifstream f;
    int posicao,tammax;
    char ***buffer;
};*/

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
void salva2(char ***vetorcompara,int linha,int coluna,ofstream &saida){
    for(int cont=0;cont<coluna;cont++){
            if(cont==coluna-1){
                saida<<vetorcompara[linha][cont];
            }
            else{
                saida<<vetorcompara[linha][cont]<<'\t';
            }
    }
    saida<<'\n';
}
void encontramenor(ifstream *arquivo,char ***vetorcompara,int qtdfiles,int *L){ //começo da funçao para encontrar o menor
    int x,l=0,cont=0;
        x=strcmp(vetorcompara[cont][L[l]],vetorcompara[cont+1][L[l]]); 
}


void carregaDados(ifstream *arquivo,int linha,char ***vetorcompara,int coluna){
    int j=0;
    char *auxiliar=new char[1000000];
    char *s;
    int size=0;
    arquivo[linha].getline(auxiliar,10000,'\n');
    s=strtok(auxiliar,"\t");
    while(s){
        size=strlen(s);
        vetorcompara[linha][j]=new char[size+1];
        strcpy((vetorcompara[linha][j]),s);
        j++;
        s=strtok(NULL,"\t");
        if(j==coluna){
            break;   
        }
    }
    delete [] auxiliar;
}
void mergeex(char *nome,int qtdfiles,int m,int *L,int sizelista,char **temp,int coluna){
    //criaçao do vetor que sera usado para encontrar o menor
    char ***vetorcompara= new char**[qtdfiles];
    for(int cont=0;cont<qtdfiles;cont++){
        vetorcompara[cont]=new char*[coluna];
    }
    ///////////////////
    ifstream *arquivo=new ifstream[qtdfiles];//criaçao do vetor de ifstream contendo o nome de cada arquivo
    for(int cont=0;cont<qtdfiles;cont++){
        arquivo[cont].open(temp[cont]);
        carregaDados(arquivo,cont,vetorcompara,coluna); //preenche uma linha do vetor
    }
    //escreve o conteudo atual do vetor (teste apenas)
    for(int cont=0;cont<qtdfiles;cont++){
        cout<<"arquivo: "<<cont<<endl;
        for(int cont2=0;cont2<coluna;cont2++){
            cout<<vetorcompara[cont][cont2]<<'\t';
        }
        cout<<'\n';
    }
    /////////
    
    //encontramenor() aqui é chamada a funçao de encontrar o menor valor 

    //liberando a memoria dos arquivos, colunas e itens
    for(int cont=0;cont<qtdfiles;cont++){
        for(int cont2=0;cont2<coluna;cont2++){
            delete [] vetorcompara[cont][cont2];
        }
        delete []vetorcompara[cont];
    }
    delete []arquivo;
    delete []vetorcompara;
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
