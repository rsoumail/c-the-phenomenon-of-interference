
# Phenomeon of Interfernce using threads and manage interferences

About:
This program allows three threads to make some transactions in a bank.
It's about to do credit, debit and transfer operations without interferences occures.

To avoid the interférences we have use mutex.

One thread makes debit operations, an other makes credit operations and the third do transfer operations.

The informations like the account number in bank, operations number and transactions amount are give to the program by user.

All transactions(operations) have same amount.

## Install

Installation:
		1.open a commande line
		2.Change directory to the program's directory
		3.run make command

## Usage

Execution:

SYNOPSYS:
		./bank_transactions number-of-account number-of-operations transactions-amount


	Example: ./bank_transactions 2 5000 10000
