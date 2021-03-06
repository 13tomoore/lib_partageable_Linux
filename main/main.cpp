
#include <iostream>
#include <dlfcn.h>
#include <string.h>

int main(int argc, char ** argv)
{
    char *nomComposant = argv[1];
    void *openComposant;
    char *error;
    
    openComposant = dlopen (nomComposant, RTLD_LOCAL|RTLD_LAZY);
    if (!openComposant) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    
    int data1=3;
	int data2=5;
    
    int (*composantFonction)(int,int);
    int valeur;
    char* (*composantVersion)();
    char *version;
    if(strcmp ("./libComposant1.so", nomComposant) == 0){
        composantFonction = (int (*)(int, int)) dlsym(openComposant, "_Z10composant1ii");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        composantVersion=(char* (*)()) dlsym(openComposant, "_Z20getComposant1Versionv");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        version=composantVersion();    
        std::cout << "Version pour composant " << nomComposant << " : " << version << std::endl;
    }else if(strcmp ("./libComposant2.so", nomComposant) == 0){
        composantFonction = (int (*)(int, int)) dlsym(openComposant, "_Z10composant2ii");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
    }
    
    valeur=composantFonction(data1,data2);    
    std::cout << "Valeur pour composant " << nomComposant << " : " << valeur << std::endl;
    
}
