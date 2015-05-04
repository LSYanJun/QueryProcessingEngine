/*
 * File - "engine.cpp"
 * Desc - This is the EMF query process engine program for our project.
 *
 * Steps to run this program : 
 *  1. Compile and link		-$ g++ engine.cpp
 *  2. Execute			-$ ./a.out <[input file] >[output file] (i.e. ./a.out <EMFquery.txt >program.pgc)
 *  3. Run program		-read the instructions in the program file
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

//--------------------------------------
// global variables declare
//--------------------------------------
string s,n,v,f,o,g,w; // store the whole line of each operand
vector<string> vecO; // store the range of each grouping variable in a vector
vector<string> S,V,F,G,W; // seperate the whole line information into vector
int N; // the number of grouping variables
vector< vector<string> > VECO; // the two dimension vector for the range of grouping variables (VECO[0][0] means the 
				// first condition of the first grouping variable)
vector< vector<string> > aggrPrior; // store the scan order for the grouping variables
vector<string> hashPara; // store the parameters for the hash function in the program
//--------------------------------------

//--------------------------------------
// helper function forward declare
//--------------------------------------
int convertToInt(string temp); // convert string to int (atoi)
string convertToString(int temp); // convert int to string (to_string)
string attrType(string attr); // get the type of the grouping attributes
void setPrior(); // optimize the scan order for the grouping variables
void setHashPara(); // set the parameters for the hash function in the program
//--------------------------------------

//--------------------------------------
// operation function forward declare
//--------------------------------------
void readOperand(); // read and store the operands
void operandProcess(); // store the operands into easily-use struct
void writeProgram(); // write the program
//--------------------------------------

int main()
{
	readOperand();
	operandProcess();
	setPrior();
	setHashPara();
	writeProgram();
}

void readOperand()
{
	string t;
	getline(cin,t);
	if(t=="S")
	{
		getline(cin,s);
		if(s=="n") 
		{
			t=s;
			s="";
		}
		else getline(cin,t);
	}
	if(t=="n")
	{
		getline(cin,n);
		if(n=="V") 
		{
			t=n;
			n="";
		}
		else getline(cin,t);
	}
	if(t=="V")
	{
		getline(cin,v);
		if(v=="F")
		{
			t=v;
			v="";
		}
		else getline(cin,t);
	}
	if(t=="F")
	{
		getline(cin,f);
		if(f=="o")
		{
			t=f;
			f="";
		}
		else getline(cin,t);
	}
	if(t=="o")
	{
		getline(cin,o);
		while(o!="G")
		{
			vecO.push_back(o);
			getline(cin,o);
		}
		t=o;
	}
	if(t=="G")
	{
		getline(cin,g);
		if(g=="W")
		{
			t=g;
			g="";
		}
		else getline(cin,t);
	}
	if(t=="W")
	{
		getline(cin,w);
	}
}

void operandProcess()
{
	stringstream ss;
	string temp;
	ss << s;
	while(!ss.eof())
	{
		temp="";
		ss >> temp;
		if(temp=="") continue;
		if(temp[temp.size()-1]==',') temp.erase(temp.size()-1,1);
		S.push_back(temp);
	}
	N=convertToInt(n);
	ss.clear();
	ss << v;
	while(!ss.eof())
	{
		temp="";
		ss >> temp;
		if(temp=="") continue;
		if(temp[temp.size()-1]==',') temp.erase(temp.size()-1,1);
		V.push_back(temp);
	}
	ss.clear();
	ss << f;
	while(!ss.eof())
	{
		temp="";
		ss >> temp;
		if(temp=="") continue;
		if(temp[temp.size()-1]==',') temp.erase(temp.size()-1,1);
		string tempSum, tempCount;
		if(temp.find("sum")!=-1) tempSum=temp;
		else if(temp.find("count")!=-1) tempCount=temp;
		else if(temp.find("avg")!=-1)
		{
			tempSum=temp.replace(temp.find("avg"),3,"sum");
			tempCount=temp.replace(temp.find("sum"),3,"count");
		}
		if(tempSum!="")
		{
			int i;
			for(i = 0; i < F.size(); i++)
			if(F[i]==tempSum) break;
			if(i==F.size()) F.push_back(tempSum);
		}
		if(tempCount!="")
		{
			int i;
			for(i = 0; i < F.size(); i++)
			if(F[i]==tempCount) break;
			if(i==F.size()) F.push_back(tempCount);
		}
	}
	VECO.resize(N);
	for(int i = 0; i < vecO.size(); i++)
	{
		temp="";
		ss.clear();
		if(vecO[i]=="") continue;
		ss << vecO[i];
		ss >> temp;
		if(temp=="") continue;
		int tempN = convertToInt(temp);
		while(!ss.eof())
		{
			temp="";
			ss >> temp;
			if(temp=="") continue;
			if(temp[temp.size()-1]==',') temp.erase(temp.size()-1,1);
			if(temp == "and")
				temp = "&&";
			else if (temp == "or")
				temp = "||";
			VECO[tempN-1].push_back(temp);
		}
	}
	ss.clear();
	ss << g;
	while(!ss.eof())
	{
		temp = "";
		ss >> temp;
		if(temp=="") continue;
		if(temp[temp.size()-1]==',') temp.erase(temp.size()-1,1);
		if(temp == "and")
			temp = "&&";
		else if (temp == "or")
			temp = "||";
		G.push_back(temp);
	}
	ss.clear();
	ss << w;
	while(!ss.eof())
	{
		temp = "";
		ss >> temp;
		if(temp=="") continue;
		if(temp[temp.size()-1]==',') temp.erase(temp.size()-1,1);
		W.push_back(temp);
	}
}

void writeFirstPart();
void writeSecondPart();
void writeThirdPart();
void writeMFS();
void writeGroupingAttr();//assigned: Zhe Xu
void writeCompleteTable(); //assigned: Gong Cheng
void writeOutput(); //assigned: Yanjun Wu
void writeHashFunc(); //assigned: Lingzhi Yuan

void writeProgram()
{
	writeFirstPart();
	writeMFS();
	writeSecondPart();
	writeGroupingAttr();//assigned: Zhe Xu
	writeCompleteTable(); //assigned: Gong Cheng
	writeOutput(); //assigned: Yanjun Wu
	writeThirdPart();
	writeHashFunc(); //assigned: Lingzhi Yuan
}

void writeFirstPart()
{
	cout << "//--first--" << endl <<
	"/*" << endl <<
	" * File - \"sample.pgc\"" << endl <<
	" * Desc - This is the program generated by our engine." << endl <<
	" *" << endl <<
	" * Steps to run this program : " << endl <<
	" *  1. Log in to PostgreSQL server (ssh [username]@postgres.cs.stevens.edu)." << endl <<
	" *  2. In the program (L48), modify [dbname], [username], [password] to" << endl <<
	" *     yours ([dbname] is the same as your [username] by default)." << endl <<
	" *  3. Preprocessor - $ ecpg -I /usr/include/postgresql sample.pgc" << endl <<
	" *  4. Compile      - $ gcc -c -I /usr/include/postgresql/ sample.c" << endl <<
	" *  5. Link         - $ gcc -L /usr/include/postgresql/ sample.o -lecpg -o sample" << endl <<
	" *  6. Execute      - $ ./sample" << endl <<
	" */" << endl <<
	endl <<
	"#include <stdio.h>" << endl <<
	"#include <stdlib.h>" << endl <<
	"#include <string.h>" << endl <<
	endl <<
	"EXEC SQL BEGIN DECLARE SECTION;" << endl <<
	"struct {" << endl <<
	"	char	*cust;" << endl <<
	"	char	*prod;" << endl <<
	"	short    dd;" << endl <<
	"	short    mm;" << endl <<
	"	short	 yy;" << endl <<
	"	char	*state;" << endl <<
	"	long	 quant;" << endl <<
	"}	sale_rec;" << endl <<
	"EXEC SQL END DECLARE SECTION;" << endl <<
	"EXEC SQL INCLUDE sqlca;" << endl <<
	endl<<"//--end first--"<<endl;
}

void writeSecondPart()
{
	cout << "//--second--" << endl <<
	"//----------------------------------------------------------------------" << endl <<
	"// FUNCTION PROTOTYPE declaration" << endl <<
	"//----------------------------------------------------------------------" << endl << endl <<
	"void	initialMFS();" << endl <<
	"unsigned int	hashFunc(char*);" << endl << endl <<
	"//----------------------------------------------------------------------" << endl <<
	"int main(int argc, char* argv[])" << endl <<
	"//----------------------------------------------------------------------" << endl <<
	"{" << endl <<
	"   int i;" << endl <<
	"   initialMFS();" << endl <<
	"   //----------------------------------------------------------------------" << endl <<
	"   // DATABASE CONNECTION" << endl <<
	"   //----------------------------------------------------------------------" << endl <<
	"   EXEC SQL CONNECT TO cs562@localhost:5432 USER postgres IDENTIFIED BY cs562;" << endl <<
	"   EXEC SQL WHENEVER sqlerror sqlprint;" << endl <<
	endl<<"//--end second--"<<endl;
}

void writeThirdPart()
{
	cout << "//--third--" << endl <<
	"   return 0;" << endl <<
	"}" << endl << endl <<	
	"void	initialMFS()" << endl <<
	"{" << endl <<
	"	int i;" << endl <<
	"	for(i = 0; i < 500; i++)" << endl <<
	"	{" << endl <<
	"		MFS[i].flag=0;" << endl <<
	"	}" << endl <<
	"}" << endl <<
	endl<<"//--end third--"<<endl;
}

void writeMFS()
{
	cout <<
	"struct {" << endl <<
	"	bool flag;" << endl;
	for(int i = 0; i < V.size(); i++)
	{
		string type = attrType(V[i]);
		if(type.find("char")!=-1)
			cout << "	char " << V[i] << type.substr(4) << ";" << endl;
		else
			cout << "	" <<type << " " << V[i] << ";" << endl;
	}
	for(int i = 0; i < F.size(); i++)
	{
		if(F[i].find("sum")!=-1) cout << "	long " << F[i] << ";" << endl;
		else cout << "	short " << F[i] << ";" << endl;
	}
	cout << "} MFS[500];" << endl << endl;
}

void writeGroupingAttr()//assigned: Zhe Xu
{

}

void writeCompleteTable() //assigned: Gong Cheng
{
	cout << 
	"   //optimization relative aggrigate functions  assigned: Gong Cheng" << endl;
	cout <<
	"   for(i = 0; i < " << aggrPrior.size() - 1 << "; i++)" << endl <<
	"   {" << endl <<
	"	   // Open cursor" << endl <<
	"	   EXEC SQL OPEN mycursor;" << endl <<
	"	   // Fetch Data" << endl <<
	"	   EXEC SQL FETCH FROM mycursor INTO :sale_rec; //fetch the first row" << endl <<
	"	   while (sqlca.sqlcode == 0) {" << endl <<
	"		unsigned int hash = hashFunc(";
	if(hashPara.size() != 0)
	{
		for(int i = 0; i < hashPara.size() - 1; i++)
		cout << "sale_rec." << hashPara[i] << ", ";
		cout << "sale_rec." << hashPara[hashPara.size() - 1];
	}
	cout << ");" << endl <<
	"		while(strcmp(MFS[hash].cust,sale_rec.cust)!=0)" << endl <<
	"		{" << endl <<
	"			hash=(hash+1)%500;" << endl <<
	"		}" << endl <<
	"		if(strcmp(sale_rec.state,\"NY\")==0)" << endl <<
	"		{" << endl <<
	"			MFS[hash].sum_1_quant+=sale_rec.quant;" << endl <<
	"			MFS[hash].count_1_quant++;" << endl <<
	"		}" << endl <<
	"		else if(strcmp(sale_rec.state,\"CT\")==0)" << endl <<
	"		{" << endl <<
	"			MFS[hash].sum_2_quant+=sale_rec.quant;" << endl <<
	"			MFS[hash].count_2_quant++;" << endl <<
	"		}" << endl <<
	"		else if(strcmp(sale_rec.state,\"NJ\")==0)" << endl <<
	"		{" << endl <<
	"			MFS[hash].sum_3_quant+=sale_rec.quant;" << endl <<
	"			MFS[hash].count_3_quant++;" << endl <<
	"		}" << endl <<
 	"	     EXEC SQL FETCH FROM mycursor INTO :sale_rec; //fetch the rest rows" << endl <<
	"	   }" << endl <<
	"	   // Close cursor" << endl <<
	"	   EXEC SQL CLOSE mycursor;" << endl <<
	"	   //----------------------------------------------------------------------" << endl <<
	"   }" << endl <<
	endl;
}

void writeOutput() //assigned: Yanjun Wu
{
	string title = "";
	string subTitle = "";
	string temp = "";
	for (int i = 0; i < S.size(); i++)
	{
		temp = S[i];
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
		if (S[i] == "cust")
		{
			title += " CUST  |";
			subTitle += "-------+";
		}
		else if (S[i] == "prod")
		{
			title += " PROD    |";
			subTitle += "---------+";
		}
		else
		{
			title += " " + temp + " |";
			subTitle += " ";
			for(int j = 0;j < temp.length(); j++)
				subTitle += "-";
			subTitle += " +";
		}
	}
	title.replace(title.length() - 1, 1, "\\n");
	subTitle.replace(subTitle.length() - 1, 1, "\\n");
	cout << 
   		"	//----------------------------------------------------------------------" << endl <<
  		"	// PRINT TITLE" << endl <<
   		"	//----------------------------------------------------------------------" << endl <<
   		"	printf(\"" << title << "\");" << endl <<
	 	"	printf(\"" << subTitle << "\");" << endl <<
		"	for(i = 0; i < 500; i++)" << endl <<
		"	{" << endl <<
		"		if(MFS[i].flag==0) continue;" << endl;
	
	cout <<
		"		long avg_1_quant, avg_2_quant, avg_3_quant;" << endl <<
		"		if(MFS[i].count_1_quant==0) avg_1_quant=0;" << endl <<
		"		else avg_1_quant=MFS[i].sum_1_quant/MFS[i].count_1_quant;" << endl <<
		"		if(MFS[i].count_2_quant==0) avg_2_quant=0;" << endl <<
		"		else avg_2_quant=MFS[i].sum_2_quant/MFS[i].count_2_quant;" << endl <<
		"		if(MFS[i].count_3_quant==0) avg_3_quant=0;" << endl <<
		"		else avg_3_quant=MFS[i].sum_3_quant/MFS[i].count_3_quant;" << endl <<
		"		if(avg_1_quant>avg_2_quant && avg_1_quant>avg_3_quant)" << endl <<
		"		{" << endl <<
		"			printf(\" %-5s |\",MFS[i].cust);   // Customer" << endl <<
		"			printf(\" %11ld |\",avg_1_quant);  // avg(x.sale)" << endl <<
		"			printf(\" %11ld |\",avg_2_quant);  // avg(y.sale)" << endl <<
		"			printf(\" %11ld \\n\",avg_3_quant);  // avg(z.sale)" << endl <<
		"		}" << endl <<
		"	}" << endl;
}

void writeHashFunc() //assigned: Lingzhi Yuan
{

}

int convertToInt(string temp)
{
	int tempN = 0;
	for(int i = 0; i < temp.length(); i++)
	{
		if(i!=0) tempN *= 10;
		else tempN = 0;
		tempN += temp[i]-48;
	}
	return tempN;
}

string convertToString(int temp)
{
	string tempS;
	stringstream ss;
	ss << temp;
	ss >> tempS;
	return tempS;
}

string attrType(string attr)
{
	if(attr=="cust" || attr=="prod") return "char[21]";
	else if(attr=="quant") return "long";
	else if(attr=="state") return "char[3]";
	else return "short";
}

void setPrior()
{
	vector<string> init;
	for(int i = 0; i < F.size(); i++)
	{
		if(F[i].find("_0_") != -1) init.push_back(F[i]);
	}
	int count = 0;
	while(count < N)
	{
		for(int i = 0; i < VECO.size(); i++)
		{
			bool existFlag = false;
			string variableNum = "_" + convertToString(i + 1) + "_";
			for(int p = 0; p < aggrPrior.size(); p++)
			{
				for(int q = 0; q < aggrPrior[p].size(); q++)
				{
					if(aggrPrior[p][q].find(variableNum) != -1)
					{
						existFlag = true; break;
					}
				}
				if(existFlag) break;
			}
			if(existFlag) continue;
			int j = 0;
			for(; j < VECO[i].size(); j++)
			{
				int first = 0, second = 0;
				bool counted_prio_flag = true;
				while(VECO[i][j].find("_", second + 1) != -1)
				{
					counted_prio_flag = false;
					first = VECO[i][j].find("_", second + 1);
					second = VECO[i][j].find("_", first + 1);
					string prevScanNum = VECO[i][j].substr(first, second - first + 1); 
					for(int p = 0; p < aggrPrior.size(); p++)
					{
						for(int q = 0; q < aggrPrior[p].size(); q++)
						{
							if(aggrPrior[p][q].find(prevScanNum) != -1)
							{
								counted_prio_flag = true; break;
							}
						}
						if(counted_prio_flag) break;
					}
					if(!counted_prio_flag) break;
				}
				if(!counted_prio_flag) break;
			}
			if(j == VECO[i].size())
			{
				count++;
				for(int p = 0; p < F.size(); p++)
				{
					if(F[p].find(variableNum) != -1) init.push_back(F[p]);
				}
			}
		}
		aggrPrior.push_back(init);
		init.clear();
	}
}

void setHashPara()
{
	for(int i = 0; i < V.size(); i++)
	{
		string tempS = "="+V[i];
		bool flag1 = true;
		for(int p = 0; p < VECO.size(); p++)
		{
			bool flag2 = false;
			for(int q = 0; q < VECO[p].size(); q++)
			{
				if(VECO[p][q].find(tempS) != -1)
				{
					flag2 = true; break;
				}
			}
			if(!flag2)
			{
				flag1 = false; break;
			}
		}
		if(flag1) hashPara.push_back(V[i]);
	}
}




