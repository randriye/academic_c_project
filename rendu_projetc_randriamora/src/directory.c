#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/contact.h"
// #include <contact.c>
#include "../include/hash.h"
// #include <hash.c>
#include <sys/types.h>
#include <stdbool.h>

/*
  Structure de données représentant un annuaire.
  A 3 champs : un pointeur de pointeur d'un tableau de contact et un nb de contact
*/

struct dir
{
  uint32_t len;
  struct contact **tab;
  uint32_t nbc;
};

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
  Retourne un pointeur de cet annuaire.
*/
struct dir *dir_create(uint32_t len)
{
    struct contact **tableau = malloc(sizeof(struct contact) * len);
    for ( uint32_t i = 0; i < len; i++){
      tableau[i] = NULL;
    }
    
    struct dir *annuaire = malloc(sizeof(struct dir));
    annuaire -> len = len;
    annuaire -> tab = tableau;
    annuaire -> nbc = 0;
    return annuaire;
};
/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    printf("Dictionnaire : \n");
    uint32_t n = dir -> len;
    for (uint32_t i = 0; i < n ; i++){
        printf( "dir[%u] :  ", i);
        if((dir -> tab)[i] != NULL){
        afficher_contact((dir -> tab)[i]);
        }
        else{ printf(" \n");
        }
    }
}
/*
  Fonction qui crée un nouveau tableau de contact deux fois plus grand.
  Retourne son pointeur du pointeur.
*/
struct contact **size_up(struct dir *dir)
{
  uint32_t old_len = dir -> len;
  uint32_t new_len = old_len * 2;
  // CREATION NOUVEAU TAB
  struct contact **new_tab = malloc(sizeof(struct contact) * new_len);
  for ( uint32_t j = 0; j < new_len; j++){
      new_tab[j] = NULL;
    }
  // ON REMPLIT LE NOUVEAU TABLEAU AVEC LES ELEMENTS DE L'ANCIEN
  for ( uint32_t i = 0; i < old_len; i++){
    struct contact *current = (dir -> tab)[i];
    while( current != NULL){
        uint32_t new_hash = (hash(current -> nom) % new_len);
        struct contact *tmp  = current -> suivant;
        inserer_tete_contact( &new_tab[new_hash], current);
        current = tmp;

    }
  }
  return new_tab;
};

/*
  Fonction qui crée un nouveau tableau de contact deux fois plus petit.
  Retourne son pointeur du pointeur.
*/

struct contact **size_down(struct dir *dir)
{
  uint32_t old_len = dir -> len;
  uint32_t new_len = old_len / 2;
  // DECLARATION NOUVEAU TAB
  struct contact **new_tab = malloc(sizeof(struct contact) * new_len);
  for ( uint32_t j = 0; j < new_len; j++){
      new_tab[j] = NULL;
    }
  for ( uint32_t i = 0; i < old_len; i++){
    struct contact *current = (dir -> tab)[i];
    while( current != NULL){
        uint32_t new_hash = (hash(current -> nom) % new_len);
        struct contact *tmp  = current -> suivant;
        inserer_tete_contact( &new_tab[new_hash], current);
        current = tmp;

    }
  }
  return new_tab;
};

/*
  Fonction qui décide si on doit modifier la taille du tableau d'un annuaire.
  Fait appel à size_up et size_down. 
  Fait le remplacement de l'ancien tableau par le nouveau. et Free l'ancien.
  Ne retourne rien.
*/
void resize(struct dir *dir)
{
  uint32_t nb_contact = (dir) -> nbc;
  uint32_t taille = (dir) -> len;
  
  if ( (float) nb_contact >= 0.75 * (float) taille){
    struct contact **new_tab = size_up(dir);
    free(dir -> tab);
    dir -> tab = new_tab;
    dir -> len *= 2;

    return;
  }
  else if ((float) nb_contact <= 0.15 * (float) taille && taille / 2 >= 10){
    struct contact **new_tab = size_down(dir);
    free( dir -> tab);
    dir -> tab = new_tab;
    dir -> len /= 2;
    return;
  }
};
/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, char *num)
{
  uint32_t hash_value = (hash(name) % (dir -> len));
  struct contact *exist = look_up_contact((dir -> tab)[hash_value], name);
    if (exist != NULL){
    char *old_num = malloc(sizeof(char) * 20);
    strcpy(exist -> numero, num);
    return old_num;
    }
    else {
      struct contact *nouveau = malloc(sizeof(struct contact));
      strcpy(nouveau -> nom, name);
      strcpy((nouveau) -> numero, num);
      nouveau -> suivant = NULL;
      inserer_tete_contact(&(dir -> tab)[hash_value], nouveau );
      dir -> nbc ++;
      dir_print(dir);
      resize(dir);
      return NULL;
    };
};

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t hash_value = (hash(name) % (dir -> len));
    bool vide = ((dir->tab)[hash_value] == NULL);
    if (vide == 1){
      return NULL;
    }
    else{
      struct  contact *exist = look_up_contact((dir -> tab)[hash_value], name);
      return exist -> numero;
    };
};
/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    uint32_t valeur_hash = (hash(name) % (dir -> len));
    struct contact  *exist= look_up_contact( (dir -> tab)[valeur_hash], name);
    if (exist != NULL){
      supprime_contact( &(dir -> tab)[valeur_hash], name);
      dir -> nbc --;
      resize(dir);
    }
    else{ return;};
};

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    uint32_t n = dir -> len;
    for (uint32_t i = 0; i < n ; i++){
      if ((dir -> tab)[i] != NULL){
      libere_liste_contact( &((dir -> tab)[i]));
      };
    };
    free((dir -> tab));
    free(dir);
}

