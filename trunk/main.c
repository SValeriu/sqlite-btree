#include "sqliteInt.h"
#include <stdio.h>
int main(){
	const char* zFilename="test.bt";
	Btree* pBt;
	BtCursor* pCur;
	int iTable;
	int rc;
	enum {RECORD_NUM=128};
	
	void* notUsed;
	i64 nKey;
	void * pData;
	int nData;
	
	int i;
	
	//= Create a B-Tree file =
	//Open B-Tree
	rc = sqlite3BtreeOpen(zFilename,&pBt,BTREE_OMIT_JOURNAL);		
	errorHandle(rc,"can't open the data base file");

	sqlite3BtreeBeginTrans(pBt, 1);
	//Create a root page for the btree, the page no is iTable
	rc = sqlite3BtreeCreateTable(pBt, &iTable, BTREE_INTKEY|BTREE_LEAFDATA);
	errorHandle(rc,"can't create table");

	//Create a Cursor for the B-Tree
	sqlite3BtreeCursor(pBt, iTable, 1, NULL, notUsed, &pCur);
	errorHandle(rc,"can't create btree cursor");

	//= Insert data into the file =
	for(i=0; i<RECORD_NUM;i++){
		sqlite3Randomness(8,(void*)&nKey);
		
		nData=64;
		pData=sqlite3Malloc(nData);
		sqlite3Randomness(nData, pData);
		rc = sqlite3BtreeInsert(pCur,notUsed,nKey,pData,nData);
		errorHandle(rc,"can't insert btree");
	}
	
	sqlite3BtreeCommit( pBt);

	//= Dump the b-tree=
	for(i=1;i<=RECORD_NUM;i++){
		rc = sqlite3BtreePageDump(pBt,  i , 0 );
		errorHandle(rc,"can't dump btree page");
	}

    
    // Do an insert and verify that the database file grows in size.
    // Reopen the database and attempt to read the record that we wrote.
    // Do some additional inserts
    return 0;
}
