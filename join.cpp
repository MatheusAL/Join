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

void insertionSort(Dados *p, int tam, int col){ //Insertion Sort para ordenar os dados
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

void insertionSortConjunto(Conjunto *p, int tam, int col){ // Insertion sort para ordenar o struct conjunto
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
void InsereJoined(ofstream &saida,Dados *p, int size,int ncol,int *l,int pos){ //Funçao que insere as colunas qque não estão na interseçao dos arquivos
    
    for(int i=0;i<ncol;i++){
        bool dif=true; // variavel que checa se a coluna nao está na lista de ordenaçao
        for(int j=0;j<size;j++){
            if(i==l[j]){
                dif=false; // recebe false quando a coluna pertence a lista
                break;
            }    
        }
        if(dif){ // quando dif é verdadeiro, a coluna nao pertence a lista e portanto, deve ser inserida
            saida << p[pos].matriz[i] << "\t";
        }
    }
    if(pos==1){ //condicional apenas para pular a linha
        saida<<"\n";
    }
    
}

void join(char *joined, int ncol1, int ncol2, int *l1, int *l2, int size){ //Funçao que realiza o join dos dois arquivos
    Dados *p;
    p=new Dados[2]; //2 arquivos a serem comparados
    bool foi=false;//Variavel que determina se o join deve ser feito ou não.
    ifstream *arq;
    arq=new ifstream[2]; 
    ofstream saida(joined);
    char *aux,*c;
    aux=new char[2];
    int cont=0,x;
    ////////Alocaçao de memoria para os dois arquivos.
    p[0].matriz=new char*[ncol1];
    p[1].matriz=new char*[ncol2];
    
    for(int j=0;j<ncol1;j++){
        p[0].matriz[j]=new char[2];
    }
    for(int j=0;j<ncol2;j++){
        p[1].matriz[j]=new char[2];
    }

    ////////////////////Fim da alocação/////////////////
    arq[0].open("Ordenado1.txt");
    arq[1].open("Ordenado2.txt");
    ///Carrega uma linha de cada arquivo e insere no vetor p.
    for(int i=0;i<2;i++){
        arq[i].getline(aux,1000000);
        c=strtok(aux,"\t");
        for(int j=0;c!=NULL;j++){
            strcpy(p[i].matriz[j],c);
            c=strtok(NULL,"\t");
        }
    }
    ///////////////////////////////////////////////
    while(1){ //Laço de repetição que executa ate que um dos arquivos termine
        while(!foi){ //Laço que é executado para definir quando o join deve ser feito
            if(atoi(p[0].matriz[l1[cont]])==atoi(p[1].matriz[l2[cont]])) //Comparação feita entre os dados de acordo com as colunas das listas
                x=0; // quando forem iguais
            else if(atoi(p[0].matriz[l1[cont]])<atoi(p[1].matriz[l2[cont]]))
                x=-1; //quando o dado do primeiro arquivo for menor
            else
                x=1; // quando o dado do segundo arquivo for menor
    
            if(x==0){
                cont++; // cont representa a quantidade de colunas que foram iguais, para que o join seja executado ele precisa ser igual a size( tamanho das listas)
                if(cont==size){
                    foi=true; //Quando as colunas batem, o join deve ser executado
                }
                continue;
            }
            else if(x<0){ // Linha do primeiro arquivo menor, isso significa que deve ser lida a proxima
                arq[0].getline(aux,1000000);
                c=strtok(aux,"\t");
                for(int j=0;c!=NULL;j++){
                    strcpy(p[0].matriz[j],c);
                    c=strtok(NULL,"\t");
                }
            }
            else{ //linha do segundo arquivo menor, isso significa que a proxima deve ser lida
                arq[1].getline(aux,1000000);
                c=strtok(aux,"\t");
                for(int j=0;c!=NULL;j++){
                    strcpy(p[1].matriz[j],c);
                    c=strtok(NULL,"\t");
                }
            }
            cont=0;
        }
        // JOIN==TRUE!
        for(int i=0;i<size;i++){ //Insere as colunas comuns aos dois arquivos
            saida << p[0].matriz[l1[i]] << "\t";
        }
        InsereJoined(saida,p,size,ncol1,l1,0); // Insere as colunas que sobraram do arquivo 1
        InsereJoined(saida,p,size,ncol2,l2,1); // Insere as colunas que sobraram do arquivo 2

        cont=0;

        if(arq[0].peek()==-1) //Checando se os arquivos chegaram ao fim.
            break;
        if(arq[1].peek()==-1)
            break;
        
        foi=false;
        //Quando o join de uma linha é executado, sao carregadas novas linhas dos dois arquivos.
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
        ///////////////////Fim do carregamento///////////////
    }

    ////////Deletando a memoria alocada
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

int contaLinhas(char *nome){ //Funçao utilizada para contar a quantidade de linhas do arquivo
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
    return n; //retorno do numero de linhas
}

void grava(Dados *p, int m, int col,int num, int ind){ //Funçao para salvar em arquivo
    ofstream saida;
    saida.open("Temp"+to_string(ind) +"_"+ to_string(num) +".txt"); //Definiçao dos nomes dos arquivos temporarios
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
    saida.open("Ordenado"+to_string(a)+".txt"); //arquivo final de ordenaçao
    char *c, *aux;
    int ultimo,cont=0;
    int x;
    p=new Conjunto[narq]; 
    aux=new char[2];
    arq=new ifstream[narq];
    ///Alocaçao de memoria para os dados
    for(int i=0;i<narq;i++)
        p[i].matriz=new char*[ncol];
    
    for(int i=0;i<narq;i++)
        for(int j=0;j<ncol;j++){
            p[i].matriz[j]=new char[2];
        }
    /////////////////Fim alocaçao////////////////
    for(int i=0;i<narq;i++){
        arq[i].open("Temp"+to_string(a)+"_"+to_string(i+1)+".txt"); //For para abrir todos os arquivos temporarios gerados
        p[i].ind=i;
    }

    for(int i=0;i<narq;i++){ //Carrega uma linha de cada arquivo;
        arq[i].getline(aux,1000000);
        c=strtok(aux,"\t");
        for(int j=0;c!=NULL;j++){
            strcpy(p[i].matriz[j],c);
            c=strtok(NULL,"\t");
        }
    }
    
    for(int k=0;k<nlinhas;k++){ 
        for(int i=size-1;i>=0;i--)
            insertionSortConjunto(p,narq,l[i]); //Ordena para achar o menor

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

        if(arq[ultimo].peek()!=-1){ //Caso o arquivo não tenha terminado, carrega mais uma linha
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
    ///////////////Desalocação da memoria utilizada/////////////
    for(int i=0;i<narq;i++)
        for(int j=0;j<ncol;j++)
            delete []p[i].matriz[j];
        
    for(int i=0;i<narq;i++)
        delete []p[i].matriz;

    saida.close();
    delete []arq;
    delete []p;
    delete []aux;
    ///////////////////////////////////////
}
void ordenaInterno(char *nome,int nlinhas,int size,int *lista,int &ncol,int ind){ //Funçao utilizada caso o M seja maior que nlinhas
    Dados *p;
    char *aux, *c;
    int cont=0;
    nlinhas=contaLinhas(nome); //pega o numero de linhas do arquivo
    aux=new char[2];
    p=new Dados[nlinhas];
    ifstream file;
    file.open(nome);
    file.getline(aux,1000000);
    c=strtok(aux,"\t");
    while(c!=NULL){//Descobre o número de colunas
        cont++;
        c=strtok(NULL,"\t");
    }
    //Aloca memoria para os dados
    for(int i=0;i<nlinhas;i++)
        p[i].matriz=new char*[cont];
    
    for(int i=0;i<nlinhas;i++)
        for(int j=0;j<cont;j++){
            p[i].matriz[j]=new char[2];
        }
    /////////////////////////////
    file.close(); //Arquivo é fechado para começar do 0
    file.open(nome);
    for(int i=0;i<nlinhas;i++){ //carrega todo o arquivo
        file.getline(aux,1000000);
        c=strtok(aux,"\t");
        for(int j=0;c!=NULL;j++){
            strcpy(p[i].matriz[j],c);
            c=strtok(NULL,"\t");
        }   
    }
    for(int i=size-1;i>=0;i--){ //Ordena de acordo com as colunas
        insertionSort(p,nlinhas,lista[i]);
    }
    ncol=cont;
    /////Inserção dos dados ordenados no arquivo
    ofstream saida;
    saida.open("Ordenado"+to_string(ind)+".txt");
    for(int i=0;i<nlinhas;i++){
        for(int j=0;j<ncol;j++){
            saida << p[i].matriz[j] << "\t";
        }
        saida << "\n";
    }
    saida.close();
    /////////////////////////////////////////////////
    //Desalocação da memoria
     for(int i=0;i<nlinhas;i++)
        for(int j=0;j<ncol;j++)
            delete []p[i].matriz[j];
        
    for(int i=0;i<nlinhas;i++)
        delete []p[i].matriz;
    
    delete []p;
    delete []aux;
    file.close();
    
}
int ordenaArquivo(char *nome, int m, int size, int *l, int ind, int &ncol, int &nlinhas){ //Função que ordena arquivos com m linhas e retorna a quantidade e arquivos
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
    while(c!=NULL){//Descobre o número de colunas
        cont++;
        c=strtok(NULL,"\t");
    }
    //Aloca memoria para os dados
    for(int i=0;i<m;i++)
        p[i].matriz=new char*[cont];
    
    for(int i=0;i<m;i++)
        for(int j=0;j<cont;j++){
            p[i].matriz[j]=new char[2];
        }
    ////////////////////////////////////
    file.close();
    file.open(nome);
    for(k=0;k<nlinhas/m;k++){
        for(int i=0;i<m;i++){ //Carrega m linhas
            file.getline(aux,1000000);
            c=strtok(aux,"\t");
            for(int j=0;c!=NULL;j++){
                strcpy(p[i].matriz[j],c);
                c=strtok(NULL,"\t");
            }   
        }

        for(int i=size-1;i>=0;i--){ // Ordena de acordo com a lista de colunas
            insertionSort(p,m,l[i]);
        }

        ++numarq; // número de arquivos gerados aumenta
        grava(p,m,cont,numarq,ind); // grava em um arquivo temporario

    }
    if(m*k<nlinhas){ //Se sobrar alguma linha, repete o processo...
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

        for(int i=size-1;i>=0;i--){ // Oredena de acordo com a lista de colunas
            insertionSort(p,k,l[i]);
        }

        grava(p,k,cont,++numarq,ind); //Salva em arquivo temporario
    }
    ////Desalocação da memoria////////
    for(int i=0;i<m;i++)
        for(int j=0;j<cont;j++)
            delete []p[i].matriz[j];
        
    for(int i=0;i<m;i++)
        delete []p[i].matriz;
    
    ncol=cont;

    delete []p;
    delete []aux;
    file.close();
    ///////////////////////////////////////
    return numarq;  // retorna o numero de arquivos gerados
}

void leLista(int *lista, char *str){ // Função que le as listas de colunas passadas como parametro
    char *c;
    c=strtok(str,",");
    for(int i=0;c!=NULL;i++){
        lista[i]=atoi(c);
        c=strtok(NULL,",");
    }    
}

int main(int argc, char **argv){
    int m=atoi(argv[1]); // recebe o m da linha de comando
    int *lista1,*lista2;
    int size=0, narq1, narq2, ncol1, ncol2;
    int nlinhas1, nlinhas2;
    char *l1,*l2,*c;
    l1=new char[2];
    l2=new char[2];
    strcpy(l1,argv[2]);
    strcpy(l2,argv[3]);

    c=strtok(argv[2],",");
    while(c!=NULL){ //Acha o tamanho da lista de colunas
        c=strtok(NULL,",");
        size++;
    }
    
    lista1=new int[size];
    lista2=new int[size];

    leLista(lista1,l1);
    leLista(lista2,l2);
    nlinhas1=contaLinhas(argv[4]);
    nlinhas2=contaLinhas(argv[5]);
    if(m>nlinhas1){ 
        ordenaInterno(argv[4],nlinhas1,size,lista1,ncol1,1); //Ordena internamente
    }else{
        narq1=ordenaArquivo(argv[4],m,size,lista1,1,ncol1,nlinhas1);    //ordena em arquivos menores com M linhas
        intercala(1,narq1,ncol1,lista1,size,nlinhas1);   //termina a ordenacao externa, fazendo intercalaçao
    } 
    if(m>nlinhas2){
        ordenaInterno(argv[5],nlinhas2,size,lista2,ncol2,2); //Ordena internamente
    }else{
        narq2=ordenaArquivo(argv[5],m,size,lista2,2,ncol2,nlinhas2);// ordena em arquivos menores com M linhas
         intercala(2,narq2,ncol2,lista1,size,nlinhas2); // termina a ordenaçao externa, fazendo intercalaçao
    }  

    join(argv[6],ncol1,ncol2,lista1,lista2,size); //Join entre os dois arquivos ja ordenados
    ////Desalocaçao das listas
    delete []l1;
    delete []l2;
    delete []lista1;
    delete []lista2;

    return 0;
}