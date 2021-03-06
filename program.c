/* Processed by ecpg (4.8.0) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "program.pgc"
//--first--
/*
 * File - "sample.pgc"
 * Desc - This is the program generated by our engine.
 *
 * Steps to run this program : 
 *  1. Log in to PostgreSQL server (ssh [username]@postgres.cs.stevens.edu).
 *  2. In the program (L48), modify [dbname], [username], [password] to
 *     yours ([dbname] is the same as your [username] by default).
 *  3. Preprocessor - $ ecpg -I /usr/include/postgresql sample.pgc
 *  4. Compile      - $ gcc -c -I /usr/include/postgresql/ sample.c
 *  5. Link         - $ gcc -L /usr/include/postgresql/ sample.o -lecpg -o sample
 *  6. Execute      - $ ./sample
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* exec sql begin declare section */
 
		
		
	    
	    
		 
		
		 
	

#line 29 "program.pgc"
 struct { 
#line 22 "program.pgc"
 char * cust ;
 
#line 23 "program.pgc"
 char * prod ;
 
#line 24 "program.pgc"
 short dd ;
 
#line 25 "program.pgc"
 short mm ;
 
#line 26 "program.pgc"
 short yy ;
 
#line 27 "program.pgc"
 char * state ;
 
#line 28 "program.pgc"
 long quant ;
 } sale_rec ;
/* exec sql end declare section */
#line 30 "program.pgc"


#line 1 "/usr/include/postgresql/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#ifndef PGDLLIMPORT
#if  defined(WIN32) || defined(__CYGWIN__)
#define PGDLLIMPORT __declspec (dllimport)
#else
#define PGDLLIMPORT
#endif   /* __CYGWIN__ */
#endif   /* PGDLLIMPORT */

#define SQLERRMC_LEN	150

#ifdef __cplusplus
extern		"C"
{
#endif

struct sqlca_t
{
	char		sqlcaid[8];
	long		sqlabc;
	long		sqlcode;
	struct
	{
		int			sqlerrml;
		char		sqlerrmc[SQLERRMC_LEN];
	}			sqlerrm;
	char		sqlerrp[8];
	long		sqlerrd[6];
	/* Element 0: empty						*/
	/* 1: OID of processed tuple if applicable			*/
	/* 2: number of rows processed				*/
	/* after an INSERT, UPDATE or				*/
	/* DELETE statement					*/
	/* 3: empty						*/
	/* 4: empty						*/
	/* 5: empty						*/
	char		sqlwarn[8];
	/* Element 0: set to 'W' if at least one other is 'W'	*/
	/* 1: if 'W' at least one character string		*/
	/* value was truncated when it was			*/
	/* stored into a host variable.             */

	/*
	 * 2: if 'W' a (hopefully) non-fatal notice occurred
	 */	/* 3: empty */
	/* 4: empty						*/
	/* 5: empty						*/
	/* 6: empty						*/
	/* 7: empty						*/

	char		sqlstate[5];
};

struct sqlca_t *ECPGget_sqlca(void);

#ifndef POSTGRES_ECPG_INTERNAL
#define sqlca (*ECPGget_sqlca())
#endif

#ifdef __cplusplus
}
#endif

#endif

#line 31 "program.pgc"


//--end first--
struct {
	bool flag;
	char cust[21];
	long sum_1_quant;
	short count_1_quant;
	long sum_2_quant;
	short count_2_quant;
	long sum_3_quant;
	short count_3_quant;
} MFS[500];

//--second--
//----------------------------------------------------------------------
// FUNCTION PROTOTYPE declaration
//----------------------------------------------------------------------

void	initialMFS();
unsigned int	hashFunc(char*);
//----------------------------------------------------------------------
int main(int argc, char* argv[])
//----------------------------------------------------------------------
{
   int i;
   initialMFS();
   //----------------------------------------------------------------------
   // DATABASE CONNECTION
   //----------------------------------------------------------------------
   { ECPGconnect(__LINE__, 0, "cs562@localhost:5432" , "postgres" , "cs562" , NULL, 0); }
#line 61 "program.pgc"

   /* exec sql whenever sqlerror  sqlprint ; */
#line 62 "program.pgc"

   //----------------------------------------------------------------------
   // READ RECORDS
   //----------------------------------------------------------------------
   /* declare mycursor cursor for select * from sales */
#line 66 "program.pgc"

   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set transaction read only", ECPGt_EOIT, ECPGt_EORT);
#line 67 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 67 "program.pgc"


//--end second--
   // group by grouping attributes,  assigned: Zhe Xu
   // Open cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare mycursor cursor for select * from sales", ECPGt_EOIT, ECPGt_EORT);
#line 72 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 72 "program.pgc"

   // Fetch Data
	   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 74 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 74 "program.pgc"
 //fetch the first row
   while (sqlca.sqlcode == 0) {
	unsigned int hash = hashFunc(sale_rec.cust);
	while(MFS[hash].flag!=false)
	{
		if(strcmp(sale_rec.cust, MFS[hash].cust) == 0) break;
		else hash=(hash + 1) % 500;
	}
	if(MFS[hash].flag==false)
	{
		for(i = 0; sale_rec.cust[i]!='\0'; i++)
			MFS[hash].cust[i] = sale_rec.cust[i];
		MFS[hash].cust[i] = '\0';
		MFS[hash].sum_1_quant = 0;
		MFS[hash].count_1_quant = 0;
		MFS[hash].sum_2_quant = 0;
		MFS[hash].count_2_quant = 0;
		MFS[hash].sum_3_quant = 0;
		MFS[hash].count_3_quant = 0;
		MFS[hash].flag = 1;
	}
      { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 95 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 95 "program.pgc"
 //fetch the rest rows
   }
   // Close cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close mycursor", ECPGt_EOIT, ECPGt_EORT);
#line 98 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 98 "program.pgc"

   //----------------------------------------------------------------------
   //optimization relative aggrigate functions  assigned: Gong Cheng
   //Scan 1
   // Open cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare mycursor cursor for select * from sales", ECPGt_EOIT, ECPGt_EORT);
#line 103 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 103 "program.pgc"

   // Fetch Data
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 105 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 105 "program.pgc"
 //fetch the first row
   while (sqlca.sqlcode == 0) {
	unsigned int hash = hashFunc(sale_rec.cust);
	unsigned int hashScan;
	hashScan = hash;
	while(strcmp(MFS[hashScan].cust, sale_rec.cust) != 0)
	{
		hashScan=(hashScan + 1) % 500;
	}
	if(strcmp(sale_rec.state, "NY") == 0 )
	{
		MFS[hashScan].sum_1_quant+= sale_rec.quant;
		MFS[hashScan].count_1_quant++ ;
	}
	if(strcmp(sale_rec.state, "CT") == 0 )
	{
		MFS[hashScan].sum_2_quant+= sale_rec.quant;
		MFS[hashScan].count_2_quant++ ;
	}
	if(strcmp(sale_rec.state, "NJ") == 0 )
	{
		MFS[hashScan].sum_3_quant+= sale_rec.quant;
		MFS[hashScan].count_3_quant++ ;
	}
     { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 129 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 129 "program.pgc"
 //fetch the rest rows
   }
   // Close cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close mycursor", ECPGt_EOIT, ECPGt_EORT);
#line 132 "program.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 132 "program.pgc"

   //----------------------------------------------------------------------

	//----------------------------------------------------------------------
	// PRINT TITLE
	//----------------------------------------------------------------------
	printf(" CUST  | AVG_1_QUANT | AVG_2_QUANT | AVG_3_QUANT \n");
	printf("-------+ ----------- + ----------- + ----------- \n");
	for(i = 0; i < 500; i++)
	{
		if(MFS[i].flag==0) continue;
		long avg_1_quant, avg_2_quant, avg_3_quant;
		if(MFS[i].count_1_quant==0) avg_1_quant=0;
		else avg_1_quant=MFS[i].sum_1_quant/MFS[i].count_1_quant;
		if(MFS[i].count_2_quant==0) avg_2_quant=0;
		else avg_2_quant=MFS[i].sum_2_quant/MFS[i].count_2_quant;
		if(MFS[i].count_3_quant==0) avg_3_quant=0;
		else avg_3_quant=MFS[i].sum_3_quant/MFS[i].count_3_quant;
		if(avg_1_quant>avg_2_quant && avg_1_quant>avg_3_quant)
		{
			printf(" %-5s |",MFS[i].cust);   // Customer
			printf(" %11ld |",avg_1_quant);  // avg(x.sale)
			printf(" %11ld |",avg_2_quant);  // avg(y.sale)
			printf(" %11ld \n",avg_3_quant);  // avg(z.sale)
		}
	}
//--third--
   return 0;
}

void	initialMFS()
{
	int i;
	for(i = 0; i < 500; i++)
	{
		MFS[i].flag=0;
	}
}

//--end third--
  //assigned: Lingzhi Yuan
unsigned int	hashFunc(char* cust)
{
	int i;
	unsigned int hash = 0;
	char* temp[50];
	for(i = 0; cust[i]!='\0'; i++)
	{
		hash = (hash<<4)^(hash>>28)^cust[i];
	}
	return (hash%500);
}
