#include "sqliteInt.h"
#include <stdio.h>

void genRandom();
void genSequence();
void genLab();
enum {RECORD_LIM=30000};
void genTestCase(){
	genRandom("rnd.dat");
	genSequence("seq.dat");
}

void genRandom(const char * zFilename){
  FILE* fp = fopen(zFilename,"w");
  i64 key;
  int i;
  
  for(i=0; i<RECORD_LIM;i++){
  	sqlite3Randomness(8, &key);
  	fprintf(fp,"%lld\n",key);
  }
  fclose(fp);
  
}
void genSequence(const char * zFilename){
  FILE* fp = fopen(zFilename,"w");
  int i;
  
  for(i=0; i<RECORD_LIM;i++){
  	fprintf(fp,"%d\n",i);
  }
  fclose(fp);
}
void genLab(){

}
