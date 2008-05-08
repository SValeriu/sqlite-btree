#include "sqliteInt.h"
#include "timer.h"
#include "RCconfig.h"
#include <stdio.h>
void testInsert();
void testSearch();

void testBT(){
	loadRCconfig();
	testSearch();
}
    
    // Do an insert and verify that the database file grows in size.
    // Reopen the database and attempt to read the record that we wrote.
    // Do some additional inserts
void testInsert(){
	Btree* pBt;
	BtCursor* pCur;
	int iTable;
	int rc;
	
	void* notUsed;
	i64 nKey;
	void * pData;
	int nData;
	
	int i;
	double totalTime=0;

	FILE* fp=fopen(config.BTtestcase,"r");

	//= Create a B-Tree file =
	//Open B-Tree
	rc = sqlite3BtreeOpen(config.BTdatfile,&pBt,BTREE_OMIT_JOURNAL);		
	errorHandle(rc,"can't open the data base file");

	//sqlite3BtreeSetPageSize(pBt, pageSize, -1);
	sqlite3BtreeBeginTrans(pBt, 1);

	//Create a root page for the btree, the page no is iTable
	rc = sqlite3BtreeCreateTable(pBt, &iTable, BTREE_INTKEY|BTREE_LEAFDATA);
	errorHandle(rc,"can't create table");

	//Create a Cursor for the B-Tree
	sqlite3BtreeCursor(pBt, iTable, 1, NULL, notUsed, &pCur);
	errorHandle(rc,"can't create btree cursor");
	//= end create =

	//= Insert data into the file =
	for (i=0; i<config.BTrecordnum;i++) {
		sqlite3BtreeBeginTrans(pBt, 1);

		//sqlite3Randomness(8,(void*)&nKey);
		fscanf(fp,"%lld",&nKey);
		
		nData=64;
		pData=sqlite3Malloc(nData);
		sqlite3Randomness(nData, pData);

		start_timer();
		rc = sqlite3BtreeInsert(pCur,notUsed,nKey,pData,nData);
		errorHandle(rc,"can't insert btree");
		totalTime += get_timer();

		pr_times(config.BTrecordfile, totalTime);
		
	}
	
	sqlite3BtreeCommit(pBt);
	fclose(fp);
    // generate random queries
	printf("pagesize = %d\n",sqlite3BtreeGetPageSize(pBt));

	/*
	//= Dump the b-tree=
	for(i=1;i<=RECORD_NUM;i++){
		rc = sqlite3BtreePageDump(pBt,  i , 0 );
		errorHandle(rc,"can't dump btree page");
	}
	*/

}

void testSearch(){
	
	Btree* pBt;
	BtCursor* pCur;
	int iTable;
	int rc;
	
	void* notUsed;
	//i64 nKey;
	//void * pData;
	//int nData;
	int Res;
	
	int i;
	double totalTime=0;

	FILE* fp=fopen(config.BTtestcase,"r");

	//= Create a B-Tree file =
	//Open B-Tree
	rc = sqlite3BtreeOpen(config.BTdatfile,&pBt,BTREE_OMIT_JOURNAL);		
	errorHandle(rc,"can't open the data base file");

	//Create a Cursor for the B-Tree
	sqlite3BtreeCursor(pBt, iTable, 0, NULL, notUsed, &pCur);
	errorHandle(rc,"can't create btree cursor");
	//= end create =

	//= Insert data into the file =
	for (i=0; i<config.BTrecordnum;i++) {

		start_timer();
		rc = sqlite3BtreeMoveto(pCur, notUsed, (i64)i, &Res);
		errorHandle(rc,"can't search btree");
		totalTime += get_timer();

		pr_times(config.BTrecordfile, totalTime);
		
	}
	
	fclose(fp);
    // generate random queries
	printf("pagesize = %d\n",sqlite3BtreeGetPageSize(pBt));

	/*
	//= Dump the b-tree=
	for(i=1;i<=RECORD_NUM;i++){
		rc = sqlite3BtreePageDump(pBt,  i , 0 );
		errorHandle(rc,"can't dump btree page");
	}
	*/


}


