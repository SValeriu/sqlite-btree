#include "sqliteInt.h"
#include "os.h"
#include "timer.h"
#include "RCconfig.h"
#include <stdio.h>

static int rc;
void testOverwrite();
void testOverwrite1();
void testRead();
void testAppend();

/* main test function */
void testOS(){
	
	loadRCconfig();
	show_profile();
	if(config.operation==OVERWRITE) 		testOverwrite1();
	else if(config.operation==APPEND) 		testAppend();
	else if(config.operation==READ) 		testRead();
	else									printf("No such operation test.");
	//sqlite3OsCurrentTime(&BeginTime);
	
    /*
     * Write a file with nPages, then overwrite it, finally delete it
     * Then rewrite it with nPages+1, loop in this way 
     */

 	

}
void testOverwrite(){
	OsFile id;/* I don't like the implementation since OSFile need to create by myself*/
	int Readonly;
	
	int i,nPages;
	double time;
	
	char * buf=sqlite3Malloc(config.pagesize);
	rc = sqlite3OsOpenReadWrite( config.datfile, &id, &Readonly);
	errorHandle(rc, "can't open the file");

	for(nPages=1; nPages<=config.pagenum; nPages++){
		
		printf("overwrite %d pages!\n",nPages);
		
		start_timer();
		for(i=0;i<nPages;i++){
			sqlite3Randomness(config.pagesize, buf);
			rc = sqlite3OsWrite(&id, buf, config.pagesize);
			errorHandle(rc, "overwrites error");
		}
		time = get_timer();
		
		pr_times(config.recordfile, time);
	}
	rc= sqlite3OsClose(&id);
	errorHandle(rc, "can't close the file");

    //TODO can't find the defintion, do it later
    //sqlite3Free((void *)buf);
}

void testOverwrite1(){
	
	OsFile id;/* I don't like the implementation since OSFile need to create by myself*/
	int Readonly;

	int i,nPages;
	double time;
	
	char * buf=sqlite3Malloc(config.pagesize);

	for(nPages=1; nPages<=config.pagenum; nPages++){
		
		printf("write %d pages!\n",nPages);
		
		rc = sqlite3OsOpenReadWrite( config.datfile, &id, &Readonly);
		errorHandle(rc, "can't open the file");
		
		start_timer();
		for(i=0;i<nPages;i++){
			sqlite3Randomness(config.pagesize, buf);
			rc = sqlite3OsWrite(&id, buf, config.pagesize);
			errorHandle(rc, "write error");
		}
		time = get_timer();
		pr_times(config.recordfile, time);
		
		rc= sqlite3OsClose(&id);
		errorHandle(rc, "can't close the file");

		rc = sqlite3OsDelete(config.datfile);
		errorHandle(rc, "can't delete the file");
	}
    //TODO can't find the defintion, do it later
    //sqlite3Free((void *)buf);
}

void testAppend(){
	
	OsFile id;/* I don't like the implementation since OSFile need to create by myself*/
	int Readonly;

	int i,nPages;
	double time;
	
	char * buf=sqlite3Malloc(config.pagesize);
	rc = sqlite3OsOpenReadWrite( config.datfile, &id, &Readonly);
	errorHandle(rc, "can't open the file");

	for(nPages=1; nPages<=config.pagenum; nPages++){
		
		printf("append %d pages!\n",nPages);
		
		
		start_timer();
		for(i=0;i<nPages;i++){
			sqlite3Randomness(config.pagesize, buf);
			rc = sqlite3OsWrite(&id, buf, config.pagesize);
			errorHandle(rc, "write error");
		}
		time = get_timer();
		pr_times(config.recordfile, time);
				

	}
	rc= sqlite3OsClose(&id);
	errorHandle(rc, "can't close the file");

    //TODO can't find the defintion, do it later
    //sqlite3Free((void *)buf);
}

void testRead(){
	OsFile id;/* I don't like the implementation since OSFile need to create by myself*/

	int i,nPages;
	double time;
	
	char * buf=sqlite3Malloc(config.pagesize);
	rc = sqlite3OsOpenReadOnly( config.datfile, &id);
	errorHandle(rc, "can't open the file");

	for(nPages=1; nPages<=config.pagenum; nPages++){
		
		printf("read %d pages!\n",nPages);
		
		
		start_timer();
		for(i=0;i<nPages;i++){
			rc = sqlite3OsRead(&id, buf, config.pagesize);
			errorHandle(rc, "read error");
		}
		time = get_timer();
		pr_times(config.recordfile, time);
				

	}
	rc= sqlite3OsClose(&id);
	errorHandle(rc, "can't close the file");

    //TODO can't find the defintion, do it later
    //sqlite3Free((void *)buf);
}

