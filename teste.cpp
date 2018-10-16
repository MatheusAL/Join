#include <iostream>
using namespace std;



int main(){
    int m=5,coluna=4;
    int *x;
    char ***mtriz=new char **[m];
    for(int cont=0;cont<m;cont++){
        mtriz[cont]=new char*[coluna];
        for(int cont2=0;cont2<coluna;cont2++){
            mtriz[cont][cont2]=new char[10];
        }
    }
     for(int cont=0;cont<m;cont++){
        for(int cont2=0;cont2<coluna;cont2++){
            mtriz[cont][cont2]="teste";
        }
    }
    const char *matriz[m][coluna];

    for(int cont=0;cont<m;cont++){
        for(int cont2=0;cont2<coluna;cont2++){
            matriz[cont][cont2]="teste";
        }
    }
    for(int cont=0;cont<m;cont++){
        for(int cont2=0;cont2<coluna;cont2++){
            cout<<matriz[cont][cont2]<<" ";
        }
        cout<<'\n';
    }
}