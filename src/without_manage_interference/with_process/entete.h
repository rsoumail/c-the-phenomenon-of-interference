#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include<sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h> /* permet de récupérer les codes d’erreur */
#include <string.h>
#include "structures.h"

int sem, shmid, key,i;

account *accounts;
size_t size; // la taille de


