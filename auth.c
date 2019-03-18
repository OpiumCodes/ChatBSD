#include <stdio.h>
#include <string.h>
#include "mysql/mysql.h" 
#include "auth.h"

MYSQL sql_connect(){
     MYSQL mysql; 

    if(mysql_init(&mysql)==NULL) { 
        printf("\nInitialization error\n"); 
        exit(EXIT_FAILURE); 
    } 

    if (!mysql_real_connect(&mysql,"localhost","root","","users",0,NULL,0))
    {
        printf("Failed to connect to database: Error: %s\n", mysql_error(&mysql));
        exit(EXIT_FAILURE);
    }
    return mysql;
}

int create(char *usr, char *pass){

    MYSQL mysql = sql_connect();
    char query1[150],query2[150];
    sprintf(query1,"SELECT * FROM users WHERE username = '%s'",usr);
    sprintf(query2,"INSERT INTO users VALUES('%s','%s')",usr,pass);

    if (mysql_query(&mysql, query1) != 0)                   
    {                                                                                                  
        printf("Query Failure: %s\n",mysql_error(&mysql));                                                              
        exit(EXIT_FAILURE);                                                                             
    }
    MYSQL_RES *res =  mysql_store_result(&mysql);
    int nr = mysql_num_rows(res);
    if(nr > 0)
    {
        printf("USER ALREADY EXISTS\n");
        return 0;
    }

    if (mysql_query(&mysql, query2) != 0)                   
    {                                                                                                  
        printf("Query Failure: %s\n",mysql_error(&mysql));                                                              
        exit(EXIT_FAILURE);                                                                             
    }
    mysql_close(&mysql);
    
    return 1;
     
}

int login(char *usr, char *pass){

    MYSQL mysql = sql_connect();
    char query[150];
    sprintf(query,"SELECT * FROM users WHERE username = '%s' AND password = '%s'",usr,pass);

    if (mysql_query(&mysql, query) != 0)                   
    {                                                                                                  
        printf("Query Failure: %s\n",mysql_error(&mysql));                                                              
        exit(EXIT_FAILURE);                                                                             
    }
    MYSQL_RES *res =  mysql_store_result(&mysql);
    int nr = mysql_num_rows(res);
    mysql_close(&mysql);
    return nr > 0 ? 1 : 0;
     
}
