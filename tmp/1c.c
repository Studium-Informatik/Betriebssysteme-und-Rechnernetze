#include <stdio.h>

unsigned long size (int a){
    return sizeof (a);
}

int main (int argc , char ** argv ){
    int a [8];
    printf ("%lu",size (*a));
}
