#include "entete.h"
int key = 19;
int main(int argc, char **argv)
{
  char shmid_char[30], sem_char[30];
  int process_debit_pid, process_credit_pid, process_transfer_pid;
  int accounts_number = atoi(argv[1]);
  int operations_number = atoi(argv[2]);
  int transaction_amount = atoi(argv[3]);
  int account_choose, bank_balance_before_transactions, bank_balance_after_transactions, result, i;
  transactions_infos *transactions_infos_ = (transactions_infos*)malloc(sizeof(transactions_infos));

  transactions_infos_->transactions_number = operations_number;
  transactions_infos_->transactions_amount = transaction_amount;
  transactions_infos_->accounts_number = accounts_number;

  accounts = (account *) malloc(sizeof(account));
  account *shared_data = (account *) malloc(sizeof(account));


  init_bank_accounts(accounts, accounts_number);

  bank_balance_before_transactions= bank_balance(accounts, accounts_number);

  shmid = shmget(key,accounts_number*sizeof(account), IPC_CREAT | 0755);
  if(shmid == -1)
  {
    perror("Erreur lors de la création du segment de mémoire partagée :");
    exit(EXIT_FAILURE);
  }
  
  shared_data = (account*)shmat(shmid, NULL, 0);
  if ( shared_data == (void *) -1)
  {
    perror("shmat");
    exit(1);
  }
  for(i = 0; i < accounts_number; i++)
  {
    shared_data[i] = accounts[i];
  }
  shmdt(shared_data);//déttachement du segment de mémoire partagée

  sprintf(shmid_char,"%d",shmid);
  
  
  if ((sem =semget(IPC_PRIVATE, NB_SEM, 0666))== -1)
  {
    perror("semget :");
    exit(-1);
  }
  /*initialisation des sémaphores */
  for ( i = 0; i<NB_SEM;i++)
  {
    if(semctl(sem , i,SETVAL ,1)== -1)
    {
      perror("semctl :"); 
    }
  }

  sprintf(sem_char,"%d",sem);

  process_debit_pid = fork();
  if(process_debit_pid == 0)
  {
    execlp("./process_debit","process_debit_pid", argv[1], argv[2], argv[3],shmid_char,sem_char, NULL);
    perror("execlp"); 
    exit(EXIT_SUCCESS);
  }
  process_credit_pid = fork();
  if(process_credit_pid == 0)
  {
    execlp("./process_credit","process_credit_pid", argv[1], argv[2], argv[3],shmid_char,sem_char, NULL);
    perror("execlp"); 
    exit(EXIT_SUCCESS);
  }
  process_transfer_pid = fork();
  if(process_transfer_pid == 0)
  {
    execlp("./process_transfer","process_transfer_pid", argv[1], argv[2], argv[3],shmid_char,sem_char, NULL);
    perror("execlp"); 
    exit(EXIT_SUCCESS);
  }
  else
  {
    wait(NULL);
    wait(NULL);
    wait(NULL);

    shared_data = (account *) shmat(shmid, NULL, IPC_NOWAIT);//attachement au segment de mémoire partagée
    for(i = 0; i < accounts_number; i++)
    {
    accounts[i] = shared_data[i] ;
    }
    shmdt(shared_data);//déttachement du segment de mémoire partagée

    shmctl(shmid,IPC_RMID,NULL);
    semctl(sem,0,IPC_RMID,0);

    bank_balance_after_transactions = bank_balance(accounts, accounts_number);

    if(bank_balance_after_transactions != bank_balance_before_transactions)
      printf("Il y a eu d'interférences \n");
    else
      printf("Il n'y a pas d'interférences \n");
  }
}


