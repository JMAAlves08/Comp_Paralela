#include<stdio.h>
#include<stdlib.h>

int main(){

    long long a[100];
    long long b[100];
    long long c[100];
    for(int x=0; x<100; x++){
        a[x]=0;
        b[x]=0;
        c[x]=0;
    }
    for(int y=0; y<100; y++){
        for(int t=1; t<100; t++){
            b[t]++;
         a[y]=b[t-y]+c[a[t-1]];
        }
        for(int t=1; t<100; t++){
            a[t]++;
         b[y]=a[t-y]+c[a[t-1]];
        }
    }
    return 0;
}