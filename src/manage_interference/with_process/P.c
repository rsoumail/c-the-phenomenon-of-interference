#include "entete.h"
// defintion de la structure de la fonction de verouillage du semaphore
int P (int sem_num){

	struct sembuf buffer;
	buffer.sem_num = sem_num;
	// on essai de décrémenter
	buffer.sem_op = -1;
	//SEM_UNDO :permet , si le processus était tué au mauvais moment de remettre le sémaphore dans son etat précédant
	buffer.sem_flg = SEM_UNDO;
	return (semop(sem,&buffer,1));
}
