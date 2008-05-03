#include "sqliteInt.h"
#include <stdio.h>
int main(){
	const char* zFilename="test.bt";
	Btree* pBt;
	BtCursor* pCur;
	int iTable;
	int rc;
	
	void* notUsed;
	i64 nKey;
	void * pData;
	int nData;
	
	//= Create a B-Tree file =
	//Open B-Tree
	rc = sqlite3BtreeOpen(zFilename,&pBt,BTREE_OMIT_JOURNAL);
	if(rc!=SQLITE_OK){	
		fprintf(stderr,"can't open the data base file\n");
	}

	sqlite3BtreeBeginTrans(pBt, 1);
	//Create a root page for the btree, the page no is iTable
	rc = sqlite3BtreeCreateTable(pBt, &iTable, BTREE_INTKEY|BTREE_LEAFDATA);
	if(rc!=SQLITE_OK)	fprintf(stderr,"can't create table\n");

	//Create a Cursor for the B-Tree
	sqlite3BtreeCursor(pBt, iTable, 1, NULL, notUsed, &pCur);
	if(rc!=SQLITE_OK)	fprintf(stderr,"can't create btree cursor\n");

	nKey = 777;
	nData=11;
	pData=sqlite3Malloc(nData);
	
	//= Insert data into the file =
	rc = sqlite3BtreeInsert(pCur,notUsed,nKey,pData,nData);
	if(rc!=SQLITE_OK)	fprintf(stderr,"can't create btree cursor\n");

	sqlite3BtreeCommit( pBt);
	printf("rc = %d\n",rc);
    
    // Do an insert and verify that the database file grows in size.
    // Reopen the database and attempt to read the record that we wrote.
    // Do some additional inserts
    return 0;
}
