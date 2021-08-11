#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


/* Fonction qui calcule et renvoie la valeur de hachage d'une chaine de caractère */
uint32_t hash(const char *str)
{   
    uint32_t h = 5381;
    uint32_t compteur = 0;
    char c = str[compteur];
    while ( c !=  '\0'){
        h = 33 * h + (uint32_t) c;
        c = str[compteur++];
    };
    return h;
}
// void main()
// {

// const char chaine[] = "abcd";
// uint32_t valeur = hash(chaine);

// }