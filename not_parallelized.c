#include<stdio.h>
#include <stdlib.h>
#include "mysql_drivers/sqlite3.h"
void create_db(const char* dir);
void create_table(const char*dir);
void insert_data(const char*dir);
void select_data(const char* dir);
static int  callback(void* NotUsed, int argc, char **argv, char** azColName );
int main(){

	const char*  db_dir = "new_dat.db";
	sqlite3* DB;
//	sqlite3_open(db_dir,&DB);
	// int exit = sqlite3_open(db_dir,&DB);
	create_db(db_dir);
	create_table(db_dir);
	insert_data(db_dir);
	select_data(db_dir);
}
void create_db(const char* dir){
	sqlite3*  DB;
	int exit = 0;
	exit = sqlite3_open(dir,&DB);
	sqlite3_close(DB);
}
void create_table(const char*dir){
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(dir,&DB);

	char* query = " CREATE TABLE IF NOT EXISTS contacts ( \
		contact_id INTEGER PRIMARY KEY, \
		first_name TEXT NOT NULL, \
		last_name TEXT NOT NULL, \
		email TEXT NOT NULL UNIQUE, \
		phone TEXT NOT NULL UNIQUE );";

	char* message;
	
	exit = sqlite3_exec(DB,query,NULL,0,&message);
	if(message != NULL){
		printf("%s",message);
	}
	sqlite3_close(DB);
}
void insert_data(const char*dir){
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(dir,&DB);
	char* query = "INSERT INTO contacts VALUES\
	( 21279,'Yusif','IBRAHIMOV','ioseff@mail.com',0508325841),\
	( 21270,'VASIF','MAJIDOV','vasif@mail.com',0508325842),\
	( 21271,'AGHAELI','RAHIMOV','agaeli@mail.com',0508325843),\
	( 21272,'SAMIR','SADIQOV','samir@mail.com',0508325844);";
	char* message;
	exit = sqlite3_exec(DB,query,NULL,0,&message);
	if(message != NULL){
		printf("%s",message);
	}
	
	sqlite3_close(DB);

}
void select_data(const char* dir){
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(dir,&DB);
	char* query = " SELECT * FROM contacts;";
	char* message;
	exit = sqlite3_exec(DB,query,callback,NULL,&message);
	printf("%s",message);
}
static int  callback(void* NotUsed, int argc, char **argv, char** azColName ){
	NotUsed = 0;

	for(int i=0; i<argc; i++){
		printf("%s : %s\n",azColName[i],argv[i]);
	}
	printf("\n");
	return 0;
}
