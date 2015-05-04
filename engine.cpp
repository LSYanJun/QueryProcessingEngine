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
vector< vector<int> > aggrPrior; // store the scan order for the grouping variables
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
string convertExp(string exp, string argu); // convert the expression to C program
string convertAggregates(string agg, string argu); // convert the aggregates
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
		if(temp == "and")
			temp = "&&";
		else if (temp == "or")
			temp = "||";
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
	"	short    day;" << endl <<
	"	short    month;" << endl <<
	"	short	 year;" << endl <<
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
	"unsigned int	hashFunc(";
	if(hashPara.size() != 0)
	{
		for(int i = 0; i < hashPara.size() - 1; i++)
		{
			string type = attrType(hashPara[i]);
			if(type.find("char") != -1) cout << "char*, ";
			else cout << type << ", ";
		}
		string type = attrType(hashPara[hashPara.size() - 1]);
		if(type.find("char") != -1) cout << "char*";
		else cout << type;
	}
	cout << ");" << endl <<
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
	"   //----------------------------------------------------------------------" << endl <<
	"   // READ RECORDS" << endl <<
	"   //----------------------------------------------------------------------" << endl <<
	"   EXEC SQL DECLARE mycursor CURSOR FOR SELECT * FROM sales;" << endl <<
	"   EXEC SQL SET TRANSACTION read only;" << endl <<
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

	for(int p = 0; p < aggrPrior.size(); p++)
	{
		cout << "   //Scan " << p + 1 << endl <<
		"   // Open cursor" << endl <<
		"   EXEC SQL OPEN mycursor;" << endl <<
		"   // Fetch Data" << endl <<
		"   EXEC SQL FETCH FROM mycursor INTO :sale_rec; //fetch the first row" << endl <<
		"   while (sqlca.sqlcode == 0) {" << endl;
		if(W.size() != 0)  // where clause condition
		{
			cout <<"    if(";
			for(int i = 0; i < W.size(); i++)
			{
				cout << convertExp(W[i], "sale_rec") << " ";
			}
			cout << ")" << endl <<
			"    {" << endl;
		}

		cout <<
		"	unsigned int hash = hashFunc(";
		if(hashPara.size() != 0)
		{
			for(int i = 0; i < hashPara.size() - 1; i++)
			cout << "sale_rec." << hashPara[i] << ", ";
			cout << "sale_rec." << hashPara[hashPara.size() - 1];
		}
		cout << ");" << endl <<
		"	unsigned int hashScan;" << endl;
		vector<int> MFvar, EMFvar; // MF 1 to 1, EMF 1 to n
		bool globalVal = false;
		for(int q = 0; q < aggrPrior[p].size(); q++) // split the MF variables and EMF variables
		{
			if(aggrPrior[p][q] == 0) 
			{
				globalVal = true; 
				continue;
			}
			bool MFflag = true; // flag for the MF/EMF variable
			int varNum = aggrPrior[p][q]; 
			for(int i = 0; i < V.size(); i++)
			{
				bool findV = false; // flag for the existance of the grouping attribute
				for(int j = 0; j < VECO[varNum - 1].size(); j++)
				{
					if(VECO[varNum - 1][j] == V[i] + "=" + V[i])
					{
						findV = true; break;
					}
				}
				if(!findV) 
				{
					MFflag = false;
					break;
				}
			}
			if(MFflag) MFvar.push_back(varNum);
			else EMFvar.push_back(varNum);
		}
		if(globalVal) // process for grouping attribute aggregates
		{
			cout <<
			"	for(i = 0; i < 500; i++)" << endl <<
			"	{" << endl <<
			"		if(MFS[i].flag == 0) continue;" << endl;
			for(int i = 0; i < F.size(); i++)
			{
				string stringVar = "_0_";
				if(F[i].find(stringVar) != -1)
				{
					if(F[i].find("sum") != -1)
					{
						string attr = F[i].substr(F[i].find_last_of('_') + 1);
						cout << "		" << convertAggregates(F[i], "MFS[i]") << "+=" << attr << ";" << endl;
					}
					else if(F[i].find("count") != -1)
					{
						cout << "		" << convertAggregates(F[i], "MFS[i]") << "++ ;" << endl;
					}
				}
			}
			cout << "	}" << endl;
		}

		if(MFvar.size() != 0) // process for MF variable
		{
			cout <<
			"	hashScan = hash;" << endl <<
			"	while(";
			for(int i = 0; i < V.size() - 1; i++) // find the exact row
			{
				if(i) cout << "	      ";
				if(attrType(V[i]).find("char") != -1)
				cout << "strcmp(MFS[hashScan]." << V[i] << ", sale_rec." << V[i] << ") != 0 || " << endl;
				else cout << "MFS[hashScan]." << V[i] << " != sale_rec." << V[i] << " || " << endl;
			}
			if(V.size() > 1) cout << "	      ";
			if(attrType(V[V.size() - 1]).find("char") != -1)
			cout << "strcmp(MFS[hashScan]." << V[V.size() - 1] << ", sale_rec." << V[V.size() - 1] << ") != 0)" << endl;
			else cout << "MFS[hashScan]." << V[V.size() - 1] << " != sale_rec." << V[V.size() - 1] << ")" << endl;
			cout <<
			"	{" << endl <<
			"		hashScan=(hashScan + 1) % 500;" << endl <<
			"	}" << endl;
		}
		for(int q = 0; q < MFvar.size(); q++) // process for MF variable
		{
			if(VECO[MFvar[q] - 1].size() == (V.size() * 2 - 1)) continue;
			cout << "	if(";
			for(int i = 0; i < VECO[MFvar[q] - 1].size(); i++)
			{
				bool GAflag = false; // flag for grouping attribute
				if(VECO[MFvar[q] - 1][i].find("&&") == -1 && VECO[MFvar[q] - 1][i].find("||") == -1)
				for(int j = 0; j < V.size(); j++)
				{
					if(VECO[MFvar[q] - 1][i] == V[j] + "=" + V[j])
					{
						GAflag = true; break;
					}
				}
				if(GAflag)
				{
					i++;
				}
				else
				{
					cout << convertExp(VECO[MFvar[q] - 1][i], "MFS[hashScan]") << " ";
				}
			}
			cout << ")" << endl << 
			"	{" << endl;
			for(int i = 0; i < F.size(); i++)
			{
				string stringVar = "_" + convertToString(MFvar[q]) + "_";
				if(F[i].find(stringVar) != -1)
				{
					if(F[i].find("sum") != -1)
					{
						string attr = F[i].substr(F[i].find_last_of('_') + 1);
						cout << "		" << convertAggregates(F[i], "MFS[hashScan]") << "+=" << attr << ";" << endl;
					}
					else if(F[i].find("count") != -1)
					{
						cout << "		" << convertAggregates(F[i], "MFS[hashScan]") << "++ ;" << endl;
					}
				}
			}
			cout << "	}" << endl;
		}
		if(EMFvar.size() != 0) // process for EMF variable
		{
			cout <<
			"	hashScan = hash;" << endl <<
			"	for(i = 0; i < 500; i++)" << endl <<
			"	{" << endl <<
			"		if(MFS[hashScan].flag == 0) break;" << endl;
			for(int q = 0; q < EMFvar.size(); q++) // process for EMF variable
			{
				cout << "		if(";
				for(int i = 0; i < VECO[EMFvar[q] - 1].size(); i++)
				{
					if(i && (VECO[EMFvar[q] - 1][i] != "&&" && VECO[EMFvar[q] - 1][i] != "||")) cout << "		   ";
					cout << convertExp(VECO[EMFvar[q] - 1][i], "MFS[hashScan]") << " ";
					if(i < VECO[EMFvar[q] - 1].size() - 1 && 
					(VECO[EMFvar[q] - 1][i] == "&&" || VECO[EMFvar[q] - 1][i] == "||")) cout << endl;
				}
				cout << ")" << endl <<
				"		{" << endl;
				for(int i = 0; i < F.size(); i++)
				{
					string stringVar = "_" + convertToString(EMFvar[q]) + "_";
					if(F[i].find(stringVar) != -1)
					{
						if(F[i].find("sum") != -1)
						{
							string attr = F[i].substr(F[i].find_last_of('_') + 1);
							cout << "			" << 
							convertAggregates(F[i], "MFS[hashScan]") << "+=" << attr << ";" << endl;
						}
						else if(F[i].find("count") != -1)
						{
							cout << "			" << 
							convertAggregates(F[i], "MFS[hashScan]") << "++;" << endl;
						}
					}
				}
				cout << "		}" << endl;
			}
			cout <<
			"		hashScan=(hashScan + 1) % 500;" << endl <<
			"	}" << endl;
		}


		if(W.size() != 0) cout << "    }" << endl;
		cout <<
	 	"     EXEC SQL FETCH FROM mycursor INTO :sale_rec; //fetch the rest rows" << endl <<
		"   }" << endl <<
		"   // Close cursor" << endl <<
		"   EXEC SQL CLOSE mycursor;" << endl <<
		"   //----------------------------------------------------------------------" << endl <<
		endl;
	}
}

void writeOutput() //assigned: Yanjun Wu
{	string title = "";
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
	vector<int> init;
	bool globalValFlag = false;
	for(int i = 0; i < F.size(); i++)
	{
		if(F[i].find("_0_") != -1)
		{
			globalValFlag = true; break;
		}
	}
	if(globalValFlag)
	init.push_back(0);
	int count = 0;
	while(count < N)
	{
		for(int i = 0; i < VECO.size(); i++) // try to find all the variables that have the same counting priority
		{
			bool existFlag = false; // the existing flag
			for(int p = 0; p < aggrPrior.size(); p++) // if the variable's priority is set, continue
			{
				for(int q = 0; q < aggrPrior[p].size(); q++)
				{
					if(aggrPrior[p][q] == i + 1)
					{
						existFlag = true; break;
					}
				}
				if(existFlag) break;
			}
			if(existFlag) continue;
			int j = 0;
			for(; j < VECO[i].size(); j++) // try to find if there is any other variable should be counted first while not counted yet
			{
				int first = 0, second = 0;
				bool counted_prio_flag = true; // the flag for the priority, if there is any other higher 
								//priority variable that is not counted, flag = false
				while(VECO[i][j].find("_", second + 1) != -1) // find the high priority variables
				{
					counted_prio_flag = false;
					first = VECO[i][j].find("_", second + 1);
					second = VECO[i][j].find("_", first + 1);
					int prevScanNum = convertToInt(VECO[i][j].substr(first + 1, second - first - 1)); // 
					for(int p = 0; p < aggrPrior.size(); p++) // check if it is counted
					{
						for(int q = 0; q < aggrPrior[p].size(); q++)
						{
							if(aggrPrior[p][q] == prevScanNum)
							{
								counted_prio_flag = true; break; // if it is counted, flag = true
							}
						}
						if(counted_prio_flag) break; // if it is counted, flag = true
					}
					if(!counted_prio_flag) break;
				}
				if(!counted_prio_flag) break; // if it is not counted, break the whole loop, j should < VECO[i].size()
			}
			if(j == VECO[i].size()) // if there is no other variable should be counted first, set the priority
			{
				count++;
				init.push_back(i + 1);
			}
		}
		aggrPrior.push_back(init); // push back the set of variables that have the same priority
		init.clear();
	}
}

void setHashPara()
{
	if(VECO.size() == 0) return;
	for(int i = 0; i < V.size(); i++)
	{
		string tempS = "="+V[i];
		bool flag1 = true; // flag for the hash parameter
		for(int p = 0; p < VECO.size(); p++)
		{
			bool flag2 = false; // flag for the existance of the grouping attribute in the range of the grouping variable
			for(int q = 0; q < VECO[p].size(); q++)
			{
				if(VECO[p][q].find(tempS) != -1 && (VECO[p][q].find(tempS) + tempS.length()) == VECO[p][q].length())
				{
					flag2 = true; break;
				}
			}
			if(!flag2)
			{
				flag1 = false; break;
			}
		}
		if(flag1) hashPara.push_back(V[i]); // if true, it should be one of the hash parameter
	}
}

string convertExp(string exp, string argu)
{
	if(exp == "&&" || exp == "||") return exp;
	int first = exp.find_first_not_of('(');
	int second = exp.find_first_of("=<>");
	int third = exp.find_last_not_of(')');
	string parenLeft, parenRight;
	for(int i = 0; i < first; i++) parenLeft += "(";
	for(int i = third + 1; i < exp.length(); i++) parenRight += ")";

	string attribute = exp.substr(first, second - first);
	if(attribute == "cust" || attribute == "prod" || attribute == "state")
	{
		attribute = "sale_rec." + attribute;
		if(exp.find("='") != -1)
		{
			string value = exp.substr(exp.find("=") + 1, third - exp.find("="));
			value[0]='\"'; value[third - exp.find("=") - 1] = '\"';
			string convert;
			return parenLeft + "strcmp(" + attribute + ", " + value + ") == 0" + parenRight;
		}
		else if(exp.find("<>'") != -1)
		{
			string value = exp.substr(exp.find("<>") + 2, third - exp.find("<>") - 1);
			value[0]='\"'; value[third - exp.find("<>") - 2] = '\"';
			return parenLeft + "strcmp(" + attribute + ", " + value + ") != 0" + parenRight;
		}
		else if(exp.find("=") != -1)
		{
			string value = argu + "." + exp.substr(exp.find("=") + 1, third - exp.find("="));
			return parenLeft + "strcmp(" + attribute + ", " + value + ") == 0" + parenRight;
		}
		else if(exp.find("<>") != -1)
		{
			string value = argu + "." + exp.substr(exp.find("<>") + 2, third - exp.find("<>") - 1);
			return parenLeft + "strcmp(" + attribute + ", " + value + ") != 0" + parenRight;
		}
	}
	else
	{
		if(exp.find(attribute, second) != -1)
		{
			int valueStart = exp.find_first_not_of("=<>", second);
			string value = exp.substr(valueStart);
			value = argu + "." + value;
			attribute = "sale_rec." + attribute;
			return parenLeft + attribute + exp.substr(second, valueStart - second) + value; 
		}
		else
		{
			attribute = "sale_rec." + attribute;
			string value = convertAggregates(exp.substr(second), argu);
			return parenLeft + attribute + value; 
		}
	}
}
string convertAggregates(string agg, string argu)
{
	int first = 0, second = 0;
	if(agg.find_first_of("()+-*/", second) != 0)
	{
		if(agg.find_first_of("()+-*/", second) != -1)
		{
			second = agg.find_first_of("()+-*/", second);
			string tempA = agg.substr(first, second - first - 1);
			if(tempA.find("sum") != -1)
			{
				string tempB = tempA;
				tempB.replace(tempB.find("sum"), 3, argu + ".sum");
				agg.replace(agg.find(tempA), tempA.length(), tempB);
				second += tempB.length() - tempA.length();
			}
			else if(tempA.find("count") != -1)
			{
				string tempB = tempA;
				tempB.replace(tempB.find("count"), 5, argu + ".count");
				agg.replace(agg.find(tempA), tempA.length(), tempB);
				second += tempB.length() - tempA.length();
			}
			else if(tempA.find("avg") != -1)
			{
				string tempB = tempA, tempC = tempA;
				tempB.replace(tempB.find("avg"), 3, argu + ".sum");
				tempC.replace(tempC.find("avg"), 3, argu + ".count");
				tempC = "(" + tempB + "/" + tempC + ")";
				agg.replace(agg.find(tempA), tempA.length(), tempC);
				second += tempC.length() - tempA.length();
			}
		}
		else
		{
			second = agg.length();
			string tempA = agg.substr(first, second - first);
			if(tempA.find("sum") != -1)
			{
				string tempB = tempA;
				tempB.replace(tempB.find("sum"), 3, argu + ".sum");
				agg.replace(agg.find(tempA), tempA.length(), tempB);
				second += tempB.length() - tempA.length();
			}
			else if(tempA.find("count") != -1)
			{
				string tempB = tempA;
				tempB.replace(tempB.find("count"), 5, argu + ".count");
				agg.replace(agg.find(tempA), tempA.length(), tempB);
				second += tempB.length() - tempA.length();
			}
			else if(tempA.find("avg") != -1)
			{
				string tempB = tempA, tempC = tempA;
				tempB.replace(tempB.find("avg"), 3, argu + ".sum");
				tempC.replace(tempC.find("avg"), 3, argu + ".count");
				tempC = "(" + tempB + "/" + tempC + ")";
				agg.replace(agg.find(tempA), tempA.length(), tempC);
				second += tempC.length() - tempA.length();
			}
		}
	}
	while(agg.find_first_of("()+-*/", second) != -1)
	{
		first = agg.find_first_of("()+-*/", second);
		second = agg.find_first_of("()+-*/", first + 1);
		if(second == -1)
		{
			
		}
		if(second - first == 1) continue;
		string tempA = agg.substr(first + 1, second - first - 1);
		if(tempA.find("sum") != -1)
		{
			string tempB = tempA;
			tempB.replace(tempB.find("sum"), 3, argu + ".sum");
			agg.replace(agg.find(tempA), tempA.length(), tempB);
			second += tempB.length() - tempA.length();
		}
		else if(tempA.find("count") != -1)
		{
			string tempB = tempA;
			tempB.replace(tempB.find("count"), 5, argu + ".count");
			agg.replace(agg.find(tempA), tempA.length(), tempB);
			second += tempB.length() - tempA.length();
		}
		else if(tempA.find("avg") != -1)
		{
			string tempB = tempA, tempC = tempA;
			tempB.replace(tempB.find("avg"), 3, argu + ".sum");
			tempC.replace(tempC.find("avg"), 3, argu + ".count");
			tempC = "(" + tempB + "/" + tempC + ")";
			agg.replace(agg.find(tempA), tempA.length(), tempC);
			second += tempC.length() - tempA.length();
		}
	}
	first = 0;
	while(agg.find("=", first) != -1)
	{
		first = agg.find("=", first);
		agg.replace(first, 1, "==");
		first += 2;
	}
	first = 0;
	while(agg.find("<>", first) != -1)
	{
		first = agg.find("<>", first);
		agg.replace(first, 2, "!=");
	}
	return agg;
}


