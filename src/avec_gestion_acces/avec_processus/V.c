#include "entete.h"
// defintion de la structure de la fonction de liberation du semaphore
int V (int sem_num){

	struct sembuf buffer;
	buffer.sem_num = sem_num;
	// on incrémente 
	buffer.sem_op = 1;
	buffer.sem_flg = SEM_UNDO;
	return (semop(sem,&buffer,1));
}
