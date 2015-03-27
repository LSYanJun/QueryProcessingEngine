#include <stdio.h>

void readFile()
{
	FILE *fp;
	if (fp = fopen("inputQuery.txt", "wb"))
		printf("%s", "Open success\n");
	else
		printf("%s", "Open fail\n");
}
void generateProg()
{

}
void connectToDatabase()
{
	//EXEC SQL CONNECT TO postgres USER postgres IDENTIFIED BY ywu;
	//EXEC SQL WHENEVER sqlerror sqlprint;
	//printf(" CUST  | PROD    | DAY | MON | YEAR | STATE | QUANT \n");
	//printf("-------+---------+-----+-----+------+-------+-------\n");
	////----------------------------------------------------------------------
	//// READ RECORDS
	////----------------------------------------------------------------------
	//EXEC SQL DECLARE mycursor CURSOR FOR SELECT * FROM sales;
	//EXEC SQL SET TRANSACTION read only;
	//// Open cursor
	//EXEC SQL OPEN mycursor;
	//// Fetch Data
	//EXEC SQL FETCH FROM mycursor INTO : sale_rec; //fetch the first row
	//while (sqlca.sqlcode == 0) 
	//{
	//	printf(" %-5s |", sale_rec.cust);   // Customer
	//	printf(" %-7s |", sale_rec.prod);   // Product
	//	printf("  %2d |", sale_rec.dd);     // Day
	//	printf("  %2d |", sale_rec.mm);     // Month
	//	printf(" %4d |", sale_rec.yy);      // Year
	//	printf(" %-5s |", sale_rec.state);  // State
	//	printf(" %5d \n", sale_rec.quant);  // Quantity
	//	EXEC SQL FETCH FROM mycursor INTO : sale_rec;
	//}
	//// Close cursor
	//EXEC SQL CLOSE mycursor;
	
}

int main()
{
	readFile();
	connectToDatabase();
	generateProg();
	return 0;
}