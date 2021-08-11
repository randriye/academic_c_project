/*
  Test du module directory.

  Crée un annuaire et le libère.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../include/directory.h"

int main(void)
{
    struct dir *dir = dir_create(5);
    dir_free(dir);
    printf("TEST 1 OK \n");
    return EXIT_SUCCESS;
}
