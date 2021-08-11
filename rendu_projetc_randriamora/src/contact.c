#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../include/contact.h"

struct contact;

void afficher_contact(struct contact *personne)
{
    /*  Fonction qui affiche une liste simplement chaînée de contact.
    Ne retourne rien.
    */
    while( personne != NULL){
        printf(" [ %s, %s ] || ", personne-> nom, personne -> numero);
        personne = personne -> suivant;
    };
    printf("\n");
};

void supprime_contact(struct contact **personne, const char *name)
{
    /*  Fonction qui à partir d'un nom, supprime le contact dans une liste simplpement
chaînée de contact. 
Free l'élément supprimé
Ne retourne rien.
*/
  // CAS : LISTE VIDE
    if (*personne == NULL){
    return;
    }
  // CAS : TETE DE LISTE
    if (strcmp((*personne) -> nom, name ) == 0){
        struct contact *next = (*personne) -> suivant;
        free(*personne);
        (*personne) = next;
      return;
    }
  // CAS : CLASSIQUE
    struct contact *prec = *personne;
    struct contact *current= (*personne) -> suivant;
    while ( prec != NULL ){
        if (strcmp(current -> nom, name) == 0){
        prec -> suivant = current -> suivant;
        free(current);
        return;
    }
    prec = current;
    current = current -> suivant;
  };
}


void supprime_tete(struct contact **personne)
{
  /*  Fonction qui supprime la tete d'une liste simplement chaînée.
  Free la tête supprimée.
  Ne retourne rien.
  */
    struct contact *next = (*personne) -> suivant;
    free(*personne);
    (*personne) = next;
    return;
}



void libere_liste_contact(struct contact **personne)
{
  /*  Fonction qui libère une liste simplement chaînée.
  Ne retourne rien.
  */
  while (*personne != NULL){
    supprime_tete(personne);
  }
  free(*personne);
};

struct contact* look_up_contact(struct contact *personne, const char *name)
{
    /*  Fonction qui regarde si un contact existe.
    Retourne un pointeur vers le contact s'il existe. Sinon renvoie NULL.
    */
    struct contact *current = personne;
    while (current != NULL && strcmp(current -> nom, name) != 0){
      current = current -> suivant;
    }

    if ( strcmp( current -> nom, name) != 0){
      return NULL;
    }
    else{
      return current;
      };
};

void inserer_tete_contact(struct contact **personne, struct contact *nouveau)
{
    /*  Fonction qui insère en tête un contact dans une liste simplement chaînée
    Ne retourne rien;
    */
    (nouveau) -> suivant = *personne;
    *personne = nouveau;
}

// int main()
// {
//     struct contact p2 = {"0987654321", "ijklmnop", NULL };
//     struct contact p1 = {"0123456789", "abcdefgh", &p2};
//     struct contact nouveau = {"345", "ghkc", NULL};
//     struct contact *ptr = &p1;
//     struct contact *new = &nouveau;
//     afficher_contact(ptr);
//     printf("INSERTION CONTACT \n");
//     inserer_tete_contact(&ptr, new);
//     afficher_contact(ptr);
//     // bool test =look_up_contact( ptr, p1.nom);
//     printf("SUPPRESION CONTACT \n");
//     supprime_contact(&ptr, "ghkc");
//     afficher_contact(ptr);
//     printf("LIBERATION LISTE \n");
//     libere_liste_contact(&ptr);
//     afficher_contact(ptr);
//     printf("FIN \n");
// };
