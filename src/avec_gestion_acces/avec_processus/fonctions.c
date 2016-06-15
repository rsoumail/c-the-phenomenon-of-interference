#include "fonctions.h"

int random_account_choose(int maximum, int choose)
{
  int i;
  i = rand()%(maximum-0) +0;
  while(i == choose)
  {
    i = rand()%(maximum-0) +0;
  }
  return i;
}

int random_account_amount(int minimum, int maximum)
{
  int balance;
  balance = rand()%(maximum-minimum) +minimum;
  return balance;
}

int bank_balance(account *accounts, int accounts_number)
{
  int bank_balance_ = 0,i;
  for(i = 0; i < accounts_number; i++)
  {
    bank_balance_ = bank_balance_ + accounts[i].balance;
  }
  return bank_balance_;
}

void init_bank_accounts(account *accounts, int accounts_number)
{
  int i;
  for(i = 0; i < accounts_number; i++)
  {
    int balance_ = random_account_amount(100000, 1000000);
    accounts[i].number = i + random_account_amount(1000000,2000000);
    accounts[i].balance = balance_;
  }
}


void credit(int account_number, int transaction_amount, int shmid)
{
  P(NB_SEM-1);
  account account_for_credit;
  account *shared_data = (account *) malloc(sizeof(account));
  shared_data = (account*)shmat(shmid, NULL, 0);
  if ( shared_data == (void *) -1) {
      perror("shmat");
      exit(1);
  }
  account_for_credit = shared_data[account_number];
  account_for_credit.balance = account_for_credit.balance + transaction_amount;
  shared_data[account_number] = account_for_credit;
  shmdt(shared_data);
  V(NB_SEM-1);
}


void debit(int account_number, int transaction_amount, int shmid)
{
  P(NB_SEM-1);
  account account_for_debit;
  account *shared_data = (account *) malloc(sizeof(account));
  shared_data = (account*)shmat(shmid, NULL, 0);
  if ( shared_data == (void *) -1) {
      perror("shmat");
      exit(1);
  }
  account_for_debit = shared_data[account_number];
  account_for_debit.balance = account_for_debit.balance - transaction_amount;
  shared_data[account_number] = account_for_debit;
  shmdt(shared_data);
  V(NB_SEM-1);
}


void transfer(int source_account_number, int destination_account_number, int transaction_amount, int shmid)
{
  debit(source_account_number, transaction_amount, shmid);
  credit(destination_account_number, transaction_amount, shmid);
}

