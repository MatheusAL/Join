#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
using namespace std;

void leLista(int *l,int size,char *x){
    int j=0;
    for(int cont=0;cont<size;cont++){
        if(x[cont]!=','){
            l[j]=atoi(&x[cont]);
            j++;
        }
    }

}

int main(int argc, char *argv[]){
    int m,j;
    char *x;
    ifstream file1;
    ifstream file2;
    ofstream file3;
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

    delete []L1;
    delete []L2;
    
}