#include "entete.h"

int main(int argc, char **argv)
{
  int i;
  int accounts_number = atoi(argv[1]);
  int operations_number = atoi(argv[2]);
  int transaction_amount = atoi(argv[3]);
  shmid = atoi(argv[4]);
  sem = atoi(argv[5]);

  accounts = (account *) malloc(sizeof(account));
  account *shared_data = (account *) malloc(sizeof(account));

  P(NB_SEM-1);  
  shared_data = (account*)shmat(shmid, NULL, 0);
  if ( shared_data == (void *) -1) {
      perror("shmat");
      exit(1);
  }
  for(i = 0; i < accounts_number; i++)
  {
    accounts[i] = shared_data[i] ;
  }
  shmdt(shared_data);
  V(NB_SEM-1);

  for(i = 0; i < operations_number; i++)
  {
    int account_choose_credit_number = random_account_choose(accounts_number, accounts_number+1);
    credit(account_choose_credit_number, transaction_amount, shmid);
  }

}
