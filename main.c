#include "sqliteInt.h"
int main(){
	Btree* btree;
	//sbtree = sqlite3MallocZero( sizeof(Btree) );
	int rc = sqlite3BtreeOpen("test.bt",&btree,1);
    // Open a B-Tree
	
	printf("rc = %d\n",rc);
    
    // Do an insert and verify that the database file grows in size.
    // Reopen the database and attempt to read the record that we wrote.
    // Do some additional inserts
    return 0;
}
