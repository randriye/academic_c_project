#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact
{
    char numero[20]; // numero de telephone du contact
    char nom[40]; // nom du contact
    struct contact *suivant; // pointeur vers le contact suivant
};

/*  Fonction qui affiche une liste simplement chaînée de contact*/
extern void  afficher_contact(struct contact *personne);

/*  Fonction qui à partir d'un nom, supprime le contact dans une liste simplpement
chaînée de contact
*/
extern void supprime_contact(struct contact **personne, const char *name);


/*  Fonction qui supprime la tete d'une liste simplement chaînée*/
extern void supprime_tete(struct contact **personne);

/*  Fonction qui libère une liste simplement chaînée*/
extern void libere_liste_contact(struct contact **personne);

/*  Fonction qui regarde si un contact existe*/
extern struct contact* look_up_contact(struct contact *personne, const char *name);


/*  Fonction qui insère en tête un contact dans une liste simplement chaînée*/
extern void inserer_tete_contact(struct contact **personne, struct contact *nouveau);

#endif /* _CONTACT_H_ */
