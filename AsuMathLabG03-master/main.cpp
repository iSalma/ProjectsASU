
#include "CMatrix.h"
#include "algorithm"

map < char , CMatrix >  mymap;          // a map relates every defined character as matrix with its data as CMatrix data type

int ErrorFlag=0;

string space(string s);
string remove_extra_space(string s);


void  brackets_no ( string operations);
void arrayModification(int y,int x,double*p);
void arrayModification(int y,int x,char*p);
void arrayModification(int y,int x,int*p);
string spacetrim(string x) ;           //remove any unused spaces from the input string
string Get_Result(string s1);
void BracketsHandling(string& x)  ;
void SinSearch(string& x);
void CosSearch(string& x);
void TanSearch(string& x);
void logtrighandle(string &x);
void invsearch(string &x,int y);
void expsqrt(string &x);
void hsearch(string &x,int y);
void trigsearch(string& x);

string hesab (string t);
string cleanexp(string b);

void equal_brackets(string s);


bool is_char(char s);
bool is_one_line(string s);


string chartomatrix(string matstring); // takes the very first string coming from file
string concatenate(string matstring,int rowcounter,int colcounter) ;//takes converted string and row and column counter from the rowcolcounter function  
void rowcolcounter(string matstring,int &rowcounter,int &colcounter) ;//takes string after convertion of char to matrix
string ConcatenateMatrix(string matstring);
string InnerMatrixDetection(string s);














	
int main(int argv,char* argc[])			// argv : number of parameter in the command .....argc : the parameters as strings
{
	//string  Matrix_String;		 
	string s1;
	//int flag=0;
	
	 	
if(argv>1)			// ensure that the file path added
	{
	
		ifstream infile(argc[1]);		// open the file whose path included in argc[1]
	
	
////////////////////////////////////////// MATRIX DECLARATION WITH [] ///////////////////////////////////////



	
		while (getline(infile,s1))                       //  read every line in string s1
		{
			//while(s1=="")	getline(infile,s1);
			//cout<<s1<<endl;
			
			if(s1.find('[')!=-1 )                   // if this line contains matrix declaration 
			{
				//int brackets[2];
				bool one_line = is_one_line(s1);
				string s4,s5;
				bool Semicolon_Detect;        ////    true if there is  semicolon at the end of matrix declaration
				//cout<<s1.length()<<endl;
				//flag++;
				//cout<<flag<<endl;
				if(one_line)            // if the declaration in one line only we work on s1
				{
					//for(int i=0;i<s1.length(); i++)                    // to store the names of matrix
		     		//{if(s1[i]=='\n')
						
					//||s[i]=='\n'||s[i]=='\r')    
				
					//cout<<"aaaa"<<endl;

					if(s1[s1.length()-1]==';')
						Semicolon_Detect=true;
					else
						Semicolon_Detect=false;




					for (int i=0;i<s1.length();i++)
					{
						if (s1[i]=='[')
						{
							s4=s1.substr(i,s1.length()-i);
							break;
							
						}	
					}



					//cout<<s4<<endl;
					s5=cleanexp(s4);
					//cout<<s5<<endl;
					s5=remove_extra_space(s5);
					//cout<<s5<<endl;

					s5=InnerMatrixDetection(s5);
					//cout<<s5<<endl;
					s5=ConcatenateMatrix(s5);
					//s5=cleanexp(s4);
					//cout<<s5<<endl;


					
					
					for(int i=0;i<s1.length(); i++)                    // to store the names of matrix
		     		{
						if(s1[i]==' ')//||s[i]=='\n'||s[i]=='\r')                  // we skip spaces 

							continue;

			 			else
			 			{
			 				map<char,CMatrix>::iterator it;
							it =mymap.find(s1[i]);

							if(it!=mymap.end())
								it->second=CMatrix(s5);
							else
							mymap.insert( pair < char , CMatrix > (s1[i],CMatrix(s5)));           // insert new matrix

							if(Semicolon_Detect==false) 
							cout<<s1[i]<<" ="<<endl<<mymap[s1[i]].getString()<<endl<<endl;                   // print this matrix with its data

							break;          
			 			}
					}
				
				}
				
				
				else                     //  if the declaration in more than one line 
				{
					//cout<<s1<<endl;
					string s2;

					
		 			do{
					getline(infile,s2);
					string s3=';'+s2;
					
					s1.replace(s1.length(),1,s3);
					}while (!is_one_line(s1));
					//cout<<s1<<endl;



					if(s1[s1.length()-1]==';')
						Semicolon_Detect=true;
					else
						Semicolon_Detect=false;



					for (int i=0;i<s1.length();i++)
					{
						if (s1[i]=='[')
						{
							s4=s1.substr(i,s1.length()-i);
							//cout<<s4<<endl;
							break;
						}	
					}


					
					//cout<<s1<<endl;   

					
					
					//cout<<s4<<endl;

					//s5=ConcatenateMatrix(cleanexp(s4));
					s5=cleanexp(s4);
					//cout<<s5<<endl;
					s5=remove_extra_space(s5);
					//cout<<s5<<endl;

					s5=InnerMatrixDetection(s5);
					//cout<<s5<<endl;

					s5=ConcatenateMatrix(s5);
					//cout<<s5<<endl;

					
					
					for(int i=0;i<s1.length(); i++)                   
		    		{
						if(s1[i]==' ')                  // we skip spaces and newlines

							continue;

						else
						{
							map<char,CMatrix>::iterator it;
							it =mymap.find(s1[i]);
							
							if(it!=mymap.end())
								it->second=CMatrix(s5);
							else
							mymap.insert( pair < char , CMatrix > (s1[i],CMatrix(s5)));           // insert new matrix 
							
							if(Semicolon_Detect==false) 
							cout<<s1[i]<<" ="<<endl<<mymap[s1[i]].getString()<<endl<<endl;                   // print this matrix with its data
							
							break;          
						}

				
					}
					
					
						
		

				}
		

			}



/////////////////////////////////////////  OPERATIONS     /////////////////////////////////////////////////



			else if(s1.find('=')!=-1)                      // if this line contains an operation
			{

					bool Semicolon_Detect;
					
					if(s1.find("zeros")!=-1)
					{	
						if(s1[s1.length()-1]==';')
						Semicolon_Detect=true;
					else
						Semicolon_Detect=false;


						int x=s1.find("zeros");


						int first=s1.find("(",x+1);
						int mid=s1.find(",",first+1);
						int last=s1.find(")",mid+1);
						string First=s1.substr(first+1,mid-first-1);
						string Second=s1.substr(mid+1,last-mid-1);
						first=atoi(First.c_str());
						last=atoi(Second.c_str());

						CMatrix M(first,last);

						for(int i=0;i<s1.length(); i++)                   
		    			{
						if(s1[i]==' ')                  // we skip spaces and newlines

							continue;

						else
						{
							map<char,CMatrix>::iterator it;
							it =mymap.find(s1[i]);
							
							if(it!=mymap.end())
								{it->second= M;}
							else
							{mymap.insert( pair < char , CMatrix > (s1[i],M));}           // insert new matrix 
							
							if(Semicolon_Detect==false) 
							{cout<<s1[i]<<" ="<<endl<<mymap[s1[i]].getString()<<endl<<endl;}                   // print this matrix with its data
							
							break;          
						}

				
						}
					}


					else if(s1.find("eye")!=-1)
					{	
						if(s1[s1.length()-1]==';')
						Semicolon_Detect=true;
					else
						Semicolon_Detect=false;

					int x=s1.find("eye");


						int first=s1.find("(",x+1);
						int mid=s1.find(",",first+1);
						int last=s1.find(")",mid+1);
						string First=s1.substr(first+1,mid-first-1);
						string Second=s1.substr(mid+1,last-mid-1);
						first=atoi(First.c_str());
						last=atoi(Second.c_str());
						CMatrix n (first,last);
						CMatrix M=n.eye(first,last);

						for(int i=0;i<s1.length(); i++)                   
		    			{
						if(s1[i]==' ')                  // we skip spaces and newlines

							continue;

						else
						{
							map<char,CMatrix>::iterator it;
							it =mymap.find(s1[i]);
							
							if(it!=mymap.end())
								{it->second= M;}
							else
							{mymap.insert( pair < char , CMatrix > (s1[i],M));}           // insert new matrix 
							
							if(Semicolon_Detect==false) 
							{cout<<s1[i]<<" ="<<endl<<mymap[s1[i]].getString()<<endl<<endl;}                   // print this matrix with its data
							
							break;          
						}

				
						}
					}





					else if(s1.find("ones")!=-1)
					{	

						if(s1[s1.length()-1]==';')
						Semicolon_Detect=true;
					else
						Semicolon_Detect=false;

					int x=s1.find("ones");
						int first=s1.find("(",x+1);
						int mid=s1.find(",",first+1);
						int last=s1.find(")",mid+1);
						string First=s1.substr(first+1,mid-first-1);
						string Second=s1.substr(mid+1,last-mid-1);
						first=atoi(First.c_str());
						last=atoi(Second.c_str());
						CMatrix n (first,last);
						CMatrix M=n.ones(first,last);

						for(int i=0;i<s1.length(); i++)                   
		    			{
						if(s1[i]==' ')                  // we skip spaces and newlines

							continue;

						else
						{
							map<char,CMatrix>::iterator it;
							it =mymap.find(s1[i]);
							
							if(it!=mymap.end())
								{it->second= M;}
							else
							{mymap.insert( pair < char , CMatrix > (s1[i],M));}           // insert new matrix 
							
							if(Semicolon_Detect==false) 
							{cout<<s1[i]<<" ="<<endl<<mymap[s1[i]].getString()<<endl<<endl;}                   // print this matrix with its data
							
							break;          
						}

				
						}
					}




					else if(s1.find("rand")!=-1)
					{	
						
						if(s1[s1.length()-1]==';')
						Semicolon_Detect=true;
						else
						Semicolon_Detect=false;

					int x=s1.find("random");

						int first=s1.find("(",x+1);
						int mid=s1.find(",",first+1);
						int last=s1.find(")",mid+1);
						string First=s1.substr(first+1,mid-first-1);
						string Second=s1.substr(mid+1,last-mid-1);
						first=atoi(First.c_str());
						last=atoi(Second.c_str());

						CMatrix n (first,last);
						CMatrix M=n.random(first,last);

						for(int i=0;i<s1.length(); i++)                   
		    			{
						if(s1[i]==' ')                  // we skip spaces and newlines

							continue;

						else
						{
							map<char,CMatrix>::iterator it;
							it =mymap.find(s1[i]);
							
							if(it!=mymap.end())
								{it->second= M;}
							else
							{mymap.insert( pair < char , CMatrix > (s1[i],M));}           // insert new matrix 
							
							if(Semicolon_Detect==false) 
							{cout<<s1[i]<<" ="<<endl<<mymap[s1[i]].getString()<<endl<<endl;}                   // print this matrix with its data
							
							break;          
						}

				
						}
					}


///////////////////////////////////////////// Math Operations   ////////////////////////////////////////////

					else
					{
						
						try{
						string s2,s5;
						double s3;
						equal_brackets(s1);
						if(s1.find(';')!=-1)
							Semicolon_Detect=true;
						else
							Semicolon_Detect=false;




						for (int i=0;i<s1.length();i++)
						{
							if (s1[i]=='=')
							{

								s2=s1.substr(i+1,s1.length()-i-1);
								break;
							
							}	
						}
						//cout<<s2<<endl;

						for (int i=0;i<s2.length();i++)
						{
							if(is_char(s2[i]))
							{
								map<char,CMatrix>::iterator it;
								it =mymap.find(s2[i]);
							
								if(it!=mymap.end()&& (it->second).GetnR()==1 && (it->second).GetnC()==1)
								{	
									s3=(it->second).getvalue();
									s2.replace(i,2,to_string(s3));
									//cout<<s2<<endl;
								}
							}
						}
						


							for (int i=0;i<s2.length();i++)
						{
							if(s2[i]=='.')
							{
								if(s2[i+1]=='+'||s2[i+1]=='-'||s2[i+1]=='*'||s2[i+1]=='/'||s2[i+1]=='^')
								{
									s2.erase(i,1);
								}
							}
						}
						//cout<<s2<<endl;





						

								
						



						//cout<<s2<<endl;
						s5=hesab(s2);
						//cout<<s5<<endl;


							for(int i=0;i<s1.length(); i++)                   
		    			{
							if(s1[i]==' ')                  // we skip spaces and newlines

								continue;

							else
							{
								map<char,CMatrix>::iterator it;
								it =mymap.find(s1[i]);
							
								if(it!=mymap.end())
									it->second=CMatrix(s5);
								else
								mymap.insert( pair < char , CMatrix > (s1[i],CMatrix(s5)));           // insert new matrix 
							
								if(Semicolon_Detect==false) 
								cout<<s1[i]<<" ="<<endl<<mymap[s1[i]].getString()<<endl<<endl;                   // print this matrix with its data
							
								break;          
							}

				
						}






				}


				
				catch(const char* error){cout<<"Error : "<<error<<endl;}
			}
		}

				



	


			
			










		
//////////////////////////////////////////// ONE CHAR ON THE LINE OR EMPTY LINE//////////////////////////////////////////			

			else//if((s1.length()==2))//||(s1.length()==1))   // if one char only in the line without ;
			{
				for(int i=0;i<s1.length(); i++)
				{ 
				map<char,CMatrix>::iterator it;
				it =mymap.find(s1[i]);

				if(it!=mymap.end())
					{
						cout<<(it->first)<<" =\n"<<(it->second)<<endl;
						break;
					} 
				}
				
			}
	}
		
	
	

	 infile.close();             // close the file 

   }
	//cout<<flag<<endl;

	return 0;

}

/*
	try{	CMatrix x("[1 -1 -200;0 inf 200]") ;
	cout<<x.sinnh()<<endl<<endl;
    cout<<x.cossh()<<endl<<endl;
    cout<<x.tannh()<<endl<<endl;
	cout<<x.sinn()<<endl<<endl;
	cout<<x.asinn()<<endl<<endl;
    cout<<x.coss()<<endl<<endl;
    cout<<x.acoss()<<endl<<endl;
    cout<<x.atann()<<endl<<endl;
    cout<<x.tann()<<endl<<endl;






		}
		catch(const char* s){cout<<s<<endl;}

*/	



		/*
		CMatrix q(1,1,4.0);
		CMatrix a("[ 3 2.7 3 ; 11.3 76 22.9]");
		mymap.insert( pair < char , CMatrix > ('a',a));

		mymap.insert( pair < char , CMatrix > ('q',q));


		string mat1 = "[[1.2 (2*6); q a; a], [3.2+3 ;-7.8;-3.2; 1.2-2 ]3/2]";
		string mat=Char_to_Matrix(cleanexp(mat1));

		//string mat=d.substr(d.find('['),d.length()-d.find('['));   // have the string from '[' to ']'
	
	

		cout << mat << endl;
		*/




/*
CMatrix x("[3.5 -1.570796325;0.0 pi]") ;
		
	cout<<x.sinn()<<endl<<endl;
	cout<<x.coss()<<endl<<endl;
    cout<<x.tann()<<endl<<endl;


*/



























/** @brief this fn removes trailing spaces and commas in string
 *
 *
 */


string space(string s)
{
	for (int i=0; i<s.length();i++)
	{
		if((s[i]==','||s[i]==' ')&&(s[i+1]==','||s[i+1]==' '))
			{
				s.erase(i,1);
				//space(s);
			}

	}
	return(s);
	
}
string remove_extra_space(string s)
{
	return(space(space(space(space(space(space(space(space(s)))))))));
}





////////////////////////////////////////////////////////////////////////////////////////////////////








/** @brief this fn counts the numer of brackets in string
 *
 *
 */
void  brackets_no ( string operations)
{
	int bracket1 = count( operations.begin(), operations.end(), '(') ; 					
	int bracket2 = count ( operations.begin(),  operations.end(), ')') ;                                 					
	//int bracket = bracket1 + bracket2; 					
	if (bracket1!=bracket2) 
	{
		ErrorFlag=1;
	}
}

/** @brief this fn modifies string array used in calculations
 *
 *
 */
void arrayModification(int y,int x,double*p)
{
	for(int i=y;i<=x+1;i++)
	{
		*(p+(i))=*(p+i+1);
	}
}

/** @brief this fn modifies string array used in calculations
 *
 *
 */
void arrayModification(int y,int x,char *p)
{
	for(int i=y;i<=x+1;i++)
	{
		*(p+(i))=*(p+i+1);
	}
}

/** @brief this fn modifies string array used in calculations
 *
 *
 */
void arrayModification(int y,int x,int *p)
{
	for(int i=y;i<=x+1;i++)
	{
		*(p+(i))=*(p+i+1);
	}
}

/** @brief this fn removes any trailing spaces from input string
 *
 * @param x is the string to remove spaces from 
 * @sreturn x is the string after removing extra spaces
 */

string spacetrim(string x)            //remove any unused spaces from the input string
{
	for(int i=0;i<x.length();i++)
	{
		if(x[i]==' ')//||x[i]==NULL)
		{x.erase(i,1);}
	}
	return x;
}

/** @brief this fn that calculates all math exp in a string and
 * returns the result
 * @param s1 is the string to calculate its math exp
 * @return s1 is the string containing the result
 * @see hesab
 */

string Get_Result(string s1)
{
	int flag=0,FirstOperation=0;                                //to count the number of the operations between two brackets ()
	char elements [100]={};                    //contains the operands of the input string * , - , + , / , ^
	int places[100]={};                        //contains the index of each operand 
	string values[100]={};                     //contains all the numbers in the input string in order in string form
	double Values[100]={};					   //contains all the numbers in the input string in order in double form
	double Result;                             //contains the final result of the input string as a double form
	string result;                             //contains the final result of the input string as a string form 
	int j=0;
	int negelement;
	for (int i = 0; i < s1.length(); i++)
	{
		if (s1[i]=='+'||s1[i]=='-'||s1[i]=='*'||s1[i]=='/'||s1[i]=='^')
		{
			flag++;
			elements[j]=s1[i];
			places[j]=i;
			if (j==0)
			{
				values[j]=s1.substr(0,i);
				Values[j]=atof(values[j].c_str());
			}
			else
			{
				values[j]=s1.substr(places[j-1]+1,places[j]-places[j-1]-1);
				Values[j]=atof(values[j].c_str());
			}
			j++;
		}
	}
	if (flag==0)
	{
		return s1;
	}
	values[j]=s1.substr(places[j-1]+1,s1.size()-places[j-1]-1);
	Values[j]=atof(values[j].c_str());
	if (s1[0]=='-')
	{
		arrayModification(0,j,Values);
		arrayModification(0,j,elements);
		arrayModification(0,j,places);
		Values[0]*=(-1);
	}
	for (int i = 0; i < j; i++)
	{
		if (elements[i]=='^')
		{
			if (FirstOperation==0)
			{
				FirstOperation=1;
			}
			if (elements[i+1]=='-'&&places[i+1]==places[i]+1)
			{
				if (FirstOperation==1)
				{
					s1.erase(places[i+1],1);
				}
				else
				{
					s1.erase(places[i+1]+4,1);
				}
				arrayModification(i+1,j,Values);
				arrayModification(i+1,j,elements);
				arrayModification(i+1,j,places);
				j-=1;
				for (int k = i+1; k < j; k++)
				{
					places[k]-=1;
				}
				if (Values[i+1]>0)
				{
					Values[i+1]*=(-1);
				}
				negelement=1;
			}
			if (i==0)
			{
				Values[i+1]=pow(Values[i],Values[i+1]);
				result=to_string(Values[i+1]);
				if (negelement==1)
				{
					////////////////////////////////////////////s1.erase(0,places[i]+values[i].length()+2);
					if (places[i+1]==0)
					{
						s1.erase(0,s1.length());

					}
					else
					{
						s1.erase(0,places[i]+values[i].length()+2);
					}
					negelement=0;
				}
				else
				{
				/////////////////////////////////	//s1.erase(0,places[i]+values[i+1].length()+1);
					if (places[i+1]==0)
					{
						s1.erase(0,s1.length());

					}
					else
					{
						s1.erase(0,places[i]+values[i].length()+1);
					}
				}			
				s1.insert(0,result);
				FirstOperation=1;
			}
			else
			{
				Values[i+1]=pow(Values[i],Values[i+1]);
				result=to_string(Values[i+1]);
				if (i+1==j)
				{
					s1.erase(places[i-1]+1,s1.length()-places[i-1]-1);
				}
				else
				{
					s1.erase(places[i-1]+1,places[i+1]-places[i-1]-1);////////////////////////////////////////////////////////////////////////
				}
				s1.insert(places[i-1]+1,result);
				arrayModification(i,j,Values);
				arrayModification(i,j,elements);
				arrayModification(i,j,places);
			}
		}
	}
	for (int i = 0; i < j; i++)
	{
		if (elements[i]=='*')
		{
			if (FirstOperation==0)
			{
				FirstOperation=1;
			}		
			if (elements[i+1]=='-'&&places[i+1]==places[i]+1)
			{
				if (FirstOperation==1)
				{
					s1.erase(places[i+1],1);
				}
				else
				{
					s1.erase(places[i+1]+4,1);
				}
				arrayModification(i+1,j,Values);
				arrayModification(i+1,j,elements);
				arrayModification(i+1,j,places);
				j-=1;
				for (int k = i+1; k < j; k++)
				{
					places[k]-=1;
				}
				if (Values[i+1]>0)
				{
					Values[i+1]*=(-1);
				}
				negelement=1;
			}
			if (i==0)
			{
				Values[i+1]=Values[i]*Values[i+1];
				result=to_string(Values[i+1]);
			    if (negelement==1)
				{
					if(places[i+1]==0)
					{
						s1.erase(0,s1.length()-places[i]-1);///////////////////////////////////////////////////
					}
					else
					{
						s1.erase(0,places[i]+values[i+1].length()+2);
					}
					//s1.erase(0,places[i]+values[i+1].length()+2);
					negelement=0;
				}
				else
				{
					s1.erase(0,places[i]+values[i+1].length()+1);
				}
				s1.insert(0,result);
				arrayModification(i,j,Values);
				arrayModification(i,j,elements);
				arrayModification(i,j,places);
			}
			else
			{
				Values[i+1]=Values[i]*Values[i+1];
				result=to_string(Values[i+1]);
				if (i+1==j)
				{
					s1.erase(places[i-1]+1,places[i]+values[i+1].length()+2);///////////////////////////////////////////////////	
				}
				else
				{
					if (i==0)
					{
						s1.erase(places[i-1]+1,places[i+1]-places[i-1]-1);
					}
					else
					{
						s1.erase(places[i-1]+1,places[i+1]-places[i-1]);
					}
				}
				s1.insert(places[i-1]+1,result);
				arrayModification(i,j,Values);
				arrayModification(i,j,elements);
				arrayModification(i,j,places);
			}
		}
		if (elements[i]=='/')
		{
			if (FirstOperation==0)
			{
				FirstOperation=1;
			}
			if (elements[i+1]=='-'&&places[i+1]==places[i]+1)
			{
				if (FirstOperation==1)
				{
					s1.erase(places[i+1],1);
				}
				else
				{
					s1.erase(places[i+1]+4,1);
				}
				arrayModification(i+1,j,Values);
				arrayModification(i+1,j,elements);
				arrayModification(i+1,j,places);
				j-=1;
				for (int k = i+1; k < j; k++)
				{
					places[k]-=1;
				}
				if (Values[i+1]>0)
				{
					Values[i+1]*=(-1);
				}
				negelement=1;
			}
			if (i==0)
			{
				Values[i+1]=Values[i]/Values[i+1];
				result=to_string(Values[i+1]);
				if (negelement==1)
				{
					if(places[i+1]==0)
					{
						s1.erase(0,s1.length()-places[i]-1);///////////////////////////////////////////////////
					}
					else
					{
						s1.erase(0,places[i]+values[i+1].length()+2);
					}
					negelement=0;
				}
				else
				{
					s1.erase(0,places[i]+values[i+1].length()+1);
				}            
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=Values[i]/Values[i+1];
				result=to_string(Values[i+1]);
				if (i+1==j)
				{
					if (places[i+1]!=0)
					{
					s1.erase(places[i-1]+1,places[i+1]-places[i]-1);////////////////////////////////////////////////
					}
					else
					{
						s1.erase(places[i-1]+1,s1.length()-places[i-1]-1);
					}
				}
				else
				{
					s1.erase(places[i-1]+1,places[i+1]+4);
				}
				s1.insert(places[i-1]+1,result);
				arrayModification(i,j,Values);
				arrayModification(i,j,elements);
				arrayModification(i,j,places);
			}
		}
	}
	for (int i = 0; i < j; i++)
	{
		if (elements[i]=='+')
		{
			if (FirstOperation==0)
			{
				FirstOperation=1;
			}
			if ((elements[i+1]=='-'&&places[i+1]==places[i]+1)||Values[i+1]<0)
			{
				if (FirstOperation==1)
				{
					s1.erase(places[i]+1,1);
				}
				else
				{
					s1.erase(places[i]+4,1);
				}
			//	arrayModification(i+1,j,Values);
			//	arrayModification(i+1,j,elements);
			//	arrayModification(i+1,j,places);
				j-=1;
				for (int k = i+1; k < j; k++)
				{
					places[k]-=1;
				}
				if (Values[i+1]>0)
				{
					Values[i+1]*=(-1);
				}
				negelement=1;
			}
			if (i==0)
			{
				Values[i+1]=Values[i]+Values[i+1];
				result=to_string(Values[i+1]);
				if (negelement==1)
				{
					s1.erase(0,places[i]+values[i+1].length()+2);
					negelement=0;
				}
				else
				{
					s1.erase(0,places[i]+values[i+1].length()+1);
				}
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=Values[i]+Values[i+1];
				result=to_string(Values[i+1]);
				if (i+1==j)
				{
					s1.erase(0,places[i+1]-places[i]);
				}
				else
				{
					s1.erase(0,places[i+1]-places[i]+4);
				}
				s1.insert(0,result);
			}
		}
		if (elements[i]=='-')
		{
			if (FirstOperation==0)
			{
				FirstOperation=1;
			}
			if (elements[i+1]=='-'&&places[i+1]==places[i]+1)
			{
				if (FirstOperation==1)
				{
					s1.erase(places[i+1],1);
				}
				else
				{
					s1.erase(places[i+1]+4,1);
				}
				arrayModification(i+1,j,Values);
				arrayModification(i+1,j,elements);
				arrayModification(i+1,j,places);
				j-=1;
				for (int k = i+1; k < j; k++)
				{
					places[k]-=1;
				}
				if (Values[i+1]>0)
				{
					Values[i+1]*=(-1);
				}
				negelement=1;
			}
			if (i==0)
			{
				Values[i+1]=Values[i]-Values[i+1];
				result=to_string(Values[i+1]);
				if (negelement==1)
				{
					if(places[i+1]==0)
					{
						s1.erase(0,s1.length()-places[i]-1);///////////////////////////////////////////////////
					}
					else
					{
						s1.erase(0,places[i]+values[i+1].length()+2);
					}
					//////////////////////////////////////////////s1.erase(0,places[i]+values[i+1].length()+2);
					negelement=0;
				}
				else
				{

					//s1.erase(0,places[i]+values[i+1].length()+1);///////////////////////////////////////////////////
					
				}
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=Values[i]-Values[i+1];
				result=to_string(Values[i+1]);
				if (i+1==j)
				{
					s1.erase(0,places[i+1]-places[i]);
				}
				else
				{
					s1.erase(0,places[i+1]-places[i]+4);
				}
				s1.insert(0,result);
			}
		}
	}
	return s1;
}


////////////////////////////////////////handling the case: ex:5(10*20)//////////////////////////////////////

/** @brief this fn that handles brackets in a math exp
 *
 * @param x is the string array handle bracket priority in 
 * @see Get_Result()
 */

void BracketsHandling(string& x)                        
{
	int b;
	for (int i = 1; i <x.length(); i++)
	{
		b=i-1;
		if (x[i]=='(' )
		{
			if ( (int)x[b]>=48 && (int)x[b]<=57)
			{
				x.insert(i,"*");
				i=1;
			}
			/*else if(x[b]=='(')
			{
				x.erase(x.begin()+b);i=1;
			}*/
			else if (x[b]==')')
			{
				x.insert(i,"*");
				i=1;
			}
		}
	/*	else if (x[i]==')' && x[b]==')')
			{
				x.erase(x.begin()+b);i=1;
			}*/
		if (x[i]==')' )
		{
			if ( (int)x[i+1]>=48 && (int)x[i+1]<=57)
			{
				x.insert(i+1,"*");
				i=1;
			}}
	}
};
////////////////////////////////////////////////////////////replacing sin in the string//////////////////////////

/** @brief this fn that searches for 'sin' in a string array
 *
 * @param x is the string array to search for sin 
 * @see Get_Result()
 */
void SinSearch(string& x)
{
	string v,sub,result;
	double temp=0;
	char z=x.find("sin(");//*p=x.find("sin(");
	if ((int)z != (-1))
	{
		if (x.find(')',x.find("sin("))==-1)
		{
			ErrorFlag=1;
		}
		 sub=x.substr(x.find("sin(")+4,x.find(")",x.find("sin("))-x.find("sin(")-4);
		 //CMatrix Mresult=Get_Result(sub);
		 //temp=atof(result.c_str());
		 //CMatrix c;
	     //Mresult.sinn();
		// temp=sin(temp);
		 string temp2=Get_Result(sub);
		 double temp3=sin(atof(temp2.c_str()));
		 v=std::to_string(temp3);
		 
		 x.replace(x.find("sin("),x.find(")",x.find("sin("))-x.find("sin(")+1,'('+v+/*Mresult*/')');
	}
};

////////////////////////////////////////////////////////// replacing cos////////////////////////////////////////////////////

/** @brief this fn that searches for 'cos' in a string array
 *
 * @param x is the string array to search for cos 
 * @see Get_Result()
 */

void CosSearch(string& x)
{
	string v,sub,result;
	double temp=0;
	char z=x.find("cos(");//*p=x.find("sin(");
	if ((int)z != (-1))
	{
		if (x.find(')',x.find("cos("))==-1)
		{
			ErrorFlag=1;
		}
		 sub=x.substr(x.find("cos(")+4,x.find(")",x.find("cos("))-x.find("cos(")-4);
		 //CMatrix Mresult=Get_Result(sub);
		 //temp=atof(result.c_str());
		 //CMatrix c;
	     //Mresult.coss();
		 
		 //temp=cos(temp);
		 //v=std::to_string(temp);
		 string temp2=Get_Result(sub);
		 double temp3=cos(atof(temp2.c_str()));
		 v=std::to_string(temp3);

		 x.replace(x.find("cos("),x.find(")",x.find("cos("))-x.find("cos(")+1,'('+v+/*Mresult*/')');
	}
};

/////////////////////////////////////////////////tan replacement/////////////////////////////////////////////////

/** @brief this fn that searches for 'tan' in a string array
 *
 * @param x is the string array to search for tan 
 * @see Get_Result()
 */

void TanSearch(string& x)
{
	string v,sub,result;
	double temp=0;
	char z=x.find("tan(");//*p=x.find("sin(");
	if ((int)z != (-1))
	{
		if (x.find(')',x.find("tan("))==-1)
		{
			ErrorFlag=1;
		}
		 sub=x.substr(x.find("tan(")+4,x.find(")",x.find("tan("))-x.find("tan(")-4);
		 //CMatrix Mresult=Get_Result(sub);
		 //temp=atof(result.c_str());
		 //CMatrix c;
	     //Mresult.tann();
		 //temp=tan(temp);
		 //v=std::to_string(temp);
		 string temp2=Get_Result(sub);
		 double temp3=tan(atof(temp2.c_str()));
		 v=std::to_string(temp3);

		 x.replace(x.find("tan("),x.find(")",x.find("tan("))-x.find("tan(")+1,'('+v+/*Mresult*/')');
	}
};

///////////////////////////////////////////////////trig with no brackets//////////////////////////////

/** @brief this fn calculates log log10 sin cos tan
 *
 * @param t isxthe string array containing them 
 * @see Get_Result()
 */

void logtrighandle(string &x)
{
	string temp;
	double result;
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i]=='s' && x[i+1]=='i' && x[i+2]=='n')
		{
			while (x[i+3]>=48 && x[i+3]<=57 || x[i+3]=='.')
			{
				temp+=x[i+3];
				i++;
			}
			result=atof(temp.c_str());
			result=sin(result);
			x.replace(x.find("sin"),temp.length()+3,'('+to_string(result)+')');
		}
		else if (x[i]=='t' && x[i+1]=='a' && x[i+2]=='n')
		{
			while (x[i+3]>=48 && x[i+3]<=57 || x[i+3]=='.')
			{
				temp+=x[i+3];
				i++;
			}
			result=atof(temp.c_str());
			result=tan(result);
			x.replace(x.find("tan"),temp.length()+3,'('+to_string(result)+')');
		}
		else if (x[i]=='c' && x[i+1]=='o' && x[i+2]=='s')
		{
			while (x[i+3]>=48 && x[i+3]<=57 || x[i+3]=='.')
			{
				temp+=x[i+3];
				i++;
			}
			result=atof(temp.c_str());
			result=cos(result);
			x.replace(x.find("cos"),temp.length()+3,'('+to_string(result)+')');
		}
		else if (x[i]=='l' && x[i+1]=='o' && x[i+2]=='g' && x[i+3]=='1' && x[i+4]=='0')
		{
			if (x[i+5]=='(')
			{
			string sub=x.substr(x.find("log10(")+6,x.find(")",x.find("log10("))-x.find("log10(")-6),v;
			//CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.logg10();
			double temp1=0;
			string temp2=Get_Result(sub);
			//temp1=atof(sub.c_str());
			temp1=atof(temp2.c_str());
			temp1=log10(temp1);
			v=std::to_string(temp1);
			 x.replace(x.find("log10("),x.find(")",x.find("log10("))-x.find("log10(")+1,'('+v+/*Mresult*/')');
			}
			else{
			while (x[i+5]>=48 && x[i+5]<=57 || x[i+5]=='.')
			{
				temp+=x[i+5];
				i++;
			}
			result=atof(temp.c_str());
			result=log10(result);
			x.replace(x.find("log10"),temp.length()+5,'('+to_string(result)+')');
			}}
		else if (x[i]=='l' && x[i+1]=='o' && x[i+2]=='g' && x[i+3]!='1')
		{
			if (x[i+3]=='(')
			{
				string sub=x.substr(x.find("log(")+4,x.find(")",x.find("log("))-x.find("log(")-4),v;
			//CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.logg();
			//double temp1=0;
			//temp1=atof(sub.c_str());
			//temp1=log(temp1);
			//v=std::to_string(temp1);
			 string temp2=Get_Result(sub);
			double temp3=log(atof(temp2.c_str()));
			v=std::to_string(temp3);
				x.replace(x.find("log("),x.find(")",x.find("log("))-x.find("log(")+1,'('+v+/*Mresult*/')');
			}
			else if(x[i+3]!='1'){
			while (x[i+3]>=48 && x[i+3]<=57 || x[i+3]=='.')
			{
				temp+=x[i+3];
				i++;
			}
			result=atof(temp.c_str());
			result=log(result);
			x.replace(x.find("log"),temp.length()+3,'('+to_string(result)+')');
			}}

	}
};

///////////////////////////////////////////////////////////invsearch/////////////////////////////////////////////////

/** @brief this fn calculates asin acos atan
 *
 * @param x is the string array containing them 
 * @see Get_Result()
 */

void invsearch(string &x,int y)
{
	string temp;
	double result;
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i]=='a' && x[i+1]=='s' && x[i+2]=='i' && x[i+3]=='n')
		{
			if (x[i+4]=='(')
			{
			string sub=x.substr(x.find("asin(")+5,x.find(")",x.find("asin("))-x.find("asin(")-5),v;
			//CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.asinn();
			//double temp1=0;
			//temp1=asin(temp1);
			//v=std::to_string(temp1);
			string temp2=Get_Result(sub);
			 double temp3=asin(atof(temp2.c_str()));
			 v=std::to_string(temp3);
 
			x.replace(x.find("asin("),x.find(")",x.find("asin("))-x.find("asin(")+1,'('+v+/*Mresult*/')');
			}
		
			else{
			while (x[i+4]>=48 && x[i+4]<=57 || x[i+4]=='.')
			{
				temp+=x[i+4];
				i++;
			}
			result=atof(temp.c_str());
			result=asin(result);
			x.replace(x.find("asin"),temp.length()+4,'('+to_string(result)+')');
			}}
		
		
		else if (x[i]=='a' && x[i+1]=='t' && x[i+2]=='a' && x[i+3]=='n')
		{
			if (x[i+4]=='(')
			{
			string sub=x.substr(x.find("atan(")+5,x.find(")",x.find("atan("))-x.find("atan(")-5);
			//CMatrix Mresult=Get_Result(sub);
			 //	temp=atof(result.c_str());
		 //		CMatrix c;
	     //		Mresult.atann();
			 //double temp1=0;
			 //temp1=atan(temp1);
			 //string v=std::to_string(temp1);
			string temp2=Get_Result(sub);
			 double temp3=sin(atof(temp2.c_str()));
			 string v=std::to_string(temp3);
 
			x.replace(x.find("atan("),x.find(")",x.find("atan("))-x.find("atan(")+1,'('+v+/*Mresult*/')');
			}
			else 
			
			{while (x[i+4]>=48 && x[i+4]<=57 || x[i+4]=='.')
				{
				temp+=x[i+4];
				i++;
				}
				result=atof(temp.c_str());
				result=atan(result);
				x.replace(x.find("atan"),temp.length()+4,'('+to_string(result)+')');
			}}

		else if (x[i]=='a' && x[i+1]=='c' && x[i+2]=='o' && x[i+3]=='s')
		{
			if (x[i+4]=='(')
			{
			string	sub=x.substr(x.find("acos(")+5,x.find(")",x.find("acos("))-x.find("acos(")-5);
			 //CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.acoss();
			//double temp1=0;
			//temp1=acos(temp1);
			//string v=std::to_string(temp1);
			string temp2=Get_Result(sub);
			 double temp3=acos(atof(temp2.c_str()));
			 string v=std::to_string(temp3);

		 x.replace(x.find("acos("),x.find(")",x.find("acos("))-x.find("acos(")+1,'('+v+/*Mresult*/')');
	
			}
			else{
			while (x[i+4]>=48 && x[i+4]<=57 || x[i+4]=='.')
			{
				temp+=x[i+4];
				i++;
			}
			result=atof(temp.c_str());
			result=acos(result);
			x.replace(x.find("acos"),temp.length()+4,'('+to_string(result)+')');
			}}}
};

///////////////////////////////////////////////////hsearch////////////////////////////////////////////////////////////////

/** @brief this fn calculates sinh cosh tanh
 *
 * @param t ix the string containing them
 * 
 * @see Get_Result()
 */

void hsearch(string& x,int y)
{
	if (y==0)
	{
		string sub=x.substr(x.find("sinh(")+5,x.find(")",x.find("sinh("))-x.find("sinh(")-5),v;
			//CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.sinnh();
			//double temp1=0;
			//temp1=sinh(temp1);
			 //v=std::to_string(temp1);
			string temp2=Get_Result(sub);
			double temp3=sinh(atof(temp2.c_str()));
			v=std::to_string(temp3);
	 
		x.replace(x.find("sinh("),x.find(")",x.find("sinh("))-x.find("sinh(")+1,'('+v+/*Mresult*/')');
	}
	else if (y==1)
	{
		string sub=x.substr(x.find("cosh(")+5,x.find(")",x.find("cosh("))-x.find("cosh(")-5),v;
			//CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.cossh();
			//double temp1=0;
			//temp1=cosh(temp1);
			//v=std::to_string(temp1);
		string temp2=Get_Result(sub);
		 double temp3=cosh(atof(temp2.c_str()));
		 v=std::to_string(temp3);
	 
		x.replace(x.find("cosh("),x.find(")",x.find("cosh("))-x.find("cosh(")+1,'('+v+/*Mresult*/')');
	}
	else if (y==2)
	{
		string sub=x.substr(x.find("tanh(")+5,x.find(")",x.find("tanh("))-x.find("tanh")-5),v;
			//CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.tannh();
			/*double temp1=0;
			temp1=tanh(temp1);
			v=std::to_string(temp1);*/
			string temp2=Get_Result(sub);
			 double temp3=tanh(atof(temp2.c_str()));
			v=std::to_string(temp3);
	
		x.replace(x.find("tanh("),x.find(")",x.find("tanh("))-x.find("tanh(")+1,'('+v+/*Mresult*/')');
	}
};
/////////////////////////////////////////////////////exponential & sqrt calculations/////////////////////////////////////////////

/** @brief this fn calculates square roots of matrix
 *
 * @param x is the string  array conaining sqrt 
 *
 */

void expsqrt(string &x)
{
	string temp;
	double result,temp1=0;
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i]=='s' && x[i+1]=='q' && x[i+2]=='r' && x[i+3]=='t')
		{
			if (x[i+4]=='(')
			{
			string sub=x.substr(x.find("sqrt(")+5,x.find(")",x.find("sqrt("))-x.find("sqrt(")-5),v;
			//CMatrix Mresult=Get_Result(sub);
			//temp=atof(result.c_str());
			//CMatrix c;
			//Mresult.sqrtt();
			// temp1=sqrt(temp1);
			//v=std::to_string(temp1);
			string temp2=Get_Result(sub);
		 double temp3=sqrt(atof(temp2.c_str()));
		 v=std::to_string(temp3);

			 x.replace(x.find("sqrt("),x.find(")",x.find("sqrt("))-x.find("sqrt(")+1,'('+v+/*Mresult*/')');
			}
		
			else{
			while (x[i+4]>=48 && x[i+4]<=57 || x[i+4]=='.')
			{
				temp+=x[i+4];
				i++;
			}
			result=atof(temp.c_str());
			result=sqrt(result);
			x.replace(x.find("sqrt"),temp.length()+4,'('+to_string(result)+')');
			}}
		
		
		else if (x[i]=='e' && x[i+1]=='x' && x[i+2]=='p')      ////////////////////////warning
		{
			if (x[i+3]=='(')
			{
			string sub=x.substr(x.find("exp(")+4,x.find(")",x.find("exp("))-x.find("exp(")-4);
			//CMatrix Mresult=Get_Result(sub);
			 //	temp=atof(result.c_str());
				temp1=atof(sub.c_str());
		 //		CMatrix c;
	     //		Mresult.expp();
			 // temp1=exp(temp1);
			 //string v=std::to_string(temp1);
				string temp2=Get_Result(sub);
		 double temp3=exp(atof(temp2.c_str()));
		string v=std::to_string(temp3);

			 x.replace(x.find("exp("),x.find(")",x.find("exp("))-x.find("exp(")+1,'('+v+/*Mresult*/')');
			}
			else 
			
			{while (x[i+3]>=48 && x[i+3]<=57 || x[i+3]=='.')
				{
				temp+=x[i+3];
				i++;
				}
				result=atof(temp.c_str());
				result=exp(result);
				x.replace(x.find("exp"),temp.length()+3,'('+to_string(result)+')');
			}}}
};
/////////////////////////////////////////////////////summing fn///////////////////////////////////////////////////////

/** @brief this fn finds trig fns in a string
 * and calls the correspnding fn to calculate
 * @param x is the string array under test 
 * @see invsearch()
 * @see hsearch
 * @see SinSearch
 * @see CosSearch
 * @see TanSearch
 * @see logtrighandle
 * @see expsqrt
 *
 */

void trigsearch(string& x)
{
	char z=x.find("sin("),z1=x.find("cos("),z2=x.find("tan("),z3=x.find("acos"),z4=x.find("asin"),z5=x.find("atan");
	string sub="0",temp;
	char z6=x.find("sinh"),z7=x.find("cosh"),z8=x.find("tanh");
	while ((int)z4 !=-1)
	{
		z4=x.find("asin");
		invsearch(x,0);
	}
	while ((int)z3 !=-1)
	{
		z3=x.find("acos");
		invsearch(x,1);
	}
		while ((int)z5 !=-1)
	{
		z5=x.find("atan");
		invsearch(x,2);
	}
		while ((int)z6 !=-1)
	{
		z6=x.find("sinh");
		hsearch(x,0);
	}
		while ((int)z7 !=-1)
	{
		z7=x.find("cosh");
		hsearch(x,1);
	}
		while ((int)z8 !=-1)
	{
		z8=x.find("tanh");
		hsearch(x,2);
	}
		
	while((int)z != -1)
	{
		z=x.find("sin(");
		SinSearch(x);
	}
	while ((int)z1 != (-1))
	{
		z1=x.find("cos(");
		CosSearch(x);
	}
	while ((int)z2 != (-1))
	{
		z2=x.find("tan(");
		TanSearch(x);
	}
	int i=0;
	while ((x.find("sin",i)!=-1 || x.find("cos",i)!=-1 || x.find("tan",i)!=-1 ||x.find("log",i)!=-1) && i<x.length())
	{
		i++;
		logtrighandle(x);
	}
	i=0;
	while((x.find("exp")!=-1 || x.find("sqrt")!=-1)&& i<x.length())
	{
		i++;
		expsqrt(x);
	}
	
//return sub;
}





/** @brief this fn calculates any math expressions in string
 *
 * @param t is the string to be calculated 
 * @return R is the string containing result
 * @see Get_Result()
 */

string hesab (string t)
{
	//string t="L= ( ( 2 . 3 +-5+-10 -2.3)+5)*2/0-(-5*-2)";
	//string t="L=(-4^3)+(2-2)sin(1.34))";
	//string t="A = 5.5 + 12 * sin(0.4) + 2.2^4;";
	brackets_no(t);
	t=spacetrim(t);
	BracketsHandling(t);
	trigsearch(t);
	BracketsHandling(t);
	if (ErrorFlag==1)
	{
		 std:: cout<<"parse error:"<<endl<<"syntax error"<<endl;
		 ErrorFlag=0;
	}
	else
	{
	string s1=t.substr(t.find('=',0)+1,t.length()-t.find('=',0));      //gets the string that should be calculated
	string op;
	string R;
	string operand=t.substr(0,t.find('=',0)+1);   //the name of the variable that we will store the result in
	for(int i=0;i<s1.length();i++)
	{
		if(s1[i]==')')
		{int k=i;
			do
			{
				k--;
			}
			while(s1[k] !='(');        
		 	op=s1.substr(k+1,(i)-(k+1));     //gets the string that between the brackets () 
			//cout<<op<<endl;
			R=Get_Result(op);      //gets the result of the string that between the brackets and stores it in R
		//	cout<<R<<endl;
			s1.erase(k,i-k+1);    //removes the brackets and the string that has been calculated
			s1.insert(k,R);       //inserts R at the old opening of the bracket (
			i=0;
		}
	}
	//cout<<t<<endl;  
	R=Get_Result(s1);
	return R;
	//cout<<operand<<R<<endl;
	}
	
	//return 0;
}





/** @brief this fn replaces any math expression
 *  with its value
 * @param b is the string under test 
 * @return s is the string after calculations
 * @see hesab()
 *
 */

string cleanexp(string b)
{
	//cout<<b<<endl;

	//string b="A = [[2.0[3.4;2.4 ;(3.5+9.1)] 2^3 -3+1.2 15/3]]";
	char x[1000000];
	strcpy (x,b.c_str());
	//char x[]="[[2.0[3.4;2.4 ;(3.5+9.1)] 2^3 -3+ 1.2 15 / 3]]";
	string s=x;
	const char* spearators = "[] ;,";
	char* token = strtok(x, spearators);
	string array[100000];
	string array2[100000];
	int indeces[100000];
	int g=0;
	while(token)
	{	
		
		array[g]= token;
		g++;
		token = strtok(NULL, spearators);
	}
	for (int i=0;i<=g;i++)
	{
		if(i!=0)
		indeces[i]=s.find(array[i],indeces[i-1]);
		else
		indeces[i]=s.find(array[i]);
	}
	for (int i=0;i<g;i++)
	{
		//cout<<array[i];
		array2[i]=hesab(array[i]);
		//cout<<array2[i]<<endl;
	}
	for(int i=g;i>=0;i--)
	{
		s.replace(indeces[i],array[i].length(),array2[i]);
	}
	//cout<<s<<endl;
	return s;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @brief this fn counts the number of brackets and throws error
 *	if there are missing brackets
 * @param s is the s under test 
 *
 */

void equal_brackets(string s)
{
	int open_bracket_count=0;
	int close_bracket_count=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='(')
			open_bracket_count++;

	}	
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==')')
			close_bracket_count++;

	}	
	//cout<<open_bracket_count<<close_bracket_count<<endl;
	if(close_bracket_count!=open_bracket_count){
		throw("parse error");}

}

/** @brief this fn fins if char between A-Z or a-z
 *
 * @param s is the char under test 
 *
 */

bool is_char(char s)
{
	if(  ( (s>='A') && (s<='Z') )   ||  ((s>='a') && (s<='z') )  )
		return true;
	else
		return false;
}
bool is_one_line(string s)
{
	int open_bracket_count=0;
	int close_bracket_count=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='[')
			open_bracket_count++;

	}	
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==']')
			close_bracket_count++;

	}	
	//cout<<open_bracket_count<<close_bracket_count<<endl;
	if(close_bracket_count==open_bracket_count){
		return true;
	}
	else{//cout<<"yes"<<endl;
		return false;
	}

}

/** @brief this fn convert any char in the input string to matrix
 *
 * @param matstring the input string
 * @return matstring in string form after converting chars 
 *
 */


string chartomatrix(string matstring) // takes the very first string coming from file
{
    string resultstring;
    int OBC=1;
    int CBC=0;
    int spaceflag;

for(int x1=1;x1<matstring.length();x1++)     //matstring is the main matrix string
                    {

                        map<char,CMatrix>::iterator it3;
                        it3=mymap.find(matstring[x1]);

                        if(matstring[x1]=='[')
                        {
                            OBC++;
                            int closepos=matstring.find(']',x1);
                            x1=closepos;
                        }
                        else if(matstring[x1]==']')
                        {
                            CBC--;
                        }
                        else if(it3==mymap.end())
                        {
                            if(matstring[x1]!='[' && matstring[x1]!=' ' && matstring[x1]!=';' && matstring[x1]!=']' && matstring[x1]!=',')
                        {
                            int spacesemibrac=0;
                            for(int i=x1;i<matstring.length();i++)
                            {
                                if(matstring[i]==' ' || matstring[i]==';' || matstring[i]=='[' || i==matstring.length()-1)
                                {
                                    spacesemibrac=i;
                                    break;
                                }
                            }
                            string part1=matstring.substr(0,x1);
                            string middle=matstring.substr(x1,spacesemibrac-x1);
                            string part2=matstring.substr(spacesemibrac);
                            matstring=part1+"["+middle+"]"+part2;
                            x1=spacesemibrac+1;

                        }
                        }
                    }

  for(int x1=0;x1<matstring.length();x1++) //mat is the main matrix string
                    {
                        map<char,CMatrix>::iterator it3;
                        it3=mymap.find(matstring[x1]);
                        if(it3!=mymap.end())
                        {
                            CMatrix inner;
                            inner = it3->second;
                            string matrixstring=inner.getString1();
                            int innerpos = x1;
                            string firstpart=matstring.substr(0,innerpos);
                            string secondpart=matstring.substr(innerpos+1);
                            resultstring=firstpart+matrixstring+secondpart;
                            matstring=resultstring;
                        }
                    }
    return matstring;
}

/** @brief this fn makes concatenation of multiple matrices
 *
 * @param matstring the inputstring after modification
 * @param rowcounter the max number of rows of the bigmatrix
 * @param colcounter the max number of columns of the bigmatrix
 * @return the concatenated matrix
 *
 */

string concatenate(string matstring,int rowcounter,int colcounter) //takes converted string and row and column counter from the rowcolcounter function  
{
int OBC1=1;
int CBC1=0;
int r=0;
int c=0;

CMatrix bigmatrix(rowcounter,colcounter);
CMatrix innermat2;
for(int x11=1;x11<matstring.length();x11++)
{
    int innertrue=matstring.find('[',1);
    if(innertrue==std::string::npos)
    {
        break;
    }
    if(matstring[x11]=='[')
    {
        OBC1++;
        int closepos2=matstring.find(']',x11);
        if(closepos2!=std::string::npos){ CBC1++; }
        string temp999=matstring.substr(x11,closepos2-x11+1);
        int inneragain=temp999.find('[',1);
        x11=closepos2;

        if(inneragain!=std::string::npos)
        {
            //recursion part
        }
        else
        {
            CMatrix innermat(temp999);
            innermat2=innermat;
            bigmatrix.setSubMatrix(r,c,innermat);
            c+=innermat.GetnC()-1;
        }
    }
    else if(matstring[x11]==' ' && matstring[x11-1]==';')
    {
        continue;
    }
    else if(matstring[x11]==' ' || matstring[x11]==',')
    {
        c++;
    }
    else if(matstring[x11]==';')
    	{
        r+=innermat2.GetnR();
        c=0;
    	}
	}
	return bigmatrix.getString1();
}

/** @brief this fn compute the max number of rows&columns for the bigmatrix
 *
 * @param matstring the inputstring after modofication
 * @param rowcounter compute number of rows in matstring
  * @param colcounter compute number of col in matstring
  * @return max number of rows and columns by refrence
 *
 */

void rowcolcounter(string matstring,int &rowcounter,int &colcounter) //takes string after convertion of char to matrix
{
rowcounter=0;
colcounter=0;   //close bracket counter
int matcounter=0;
int semicounter=0;
int oldsemi=0;
int semiflag=0;
int firstsemi;
int nomatrix;
int flagdone=0;
vector < CMatrix > matrixarray;
if(matstring[0]=='[')   //first bracket
{
    int OBC=0;   //open bracket counter
    int CBC=0;
    int posbrac=0; //position of close bracket
    OBC++;
    for(int x3=1;x3<matstring.length();x3++)
    {
        if(matstring[x3]=='[')
        {
            posbrac=matstring.find(']',posbrac+1);
            OBC++;
            string tempmat=matstring.substr(x3,posbrac-x3+1);
            CMatrix tempmatrix(tempmat);
            matrixarray.push_back(tempmatrix);
            if(semiflag==0)
            {
                rowcounter+=matrixarray[matcounter].GetnR();
                semiflag=1;
            }
            matcounter++;
        }
        if(matstring[x3]==']')
        {
            CBC++;
        }
        if(matstring[x3]==';')
        {
            if(OBC==CBC+1)
            {
                semicounter++;
                semiflag=0;
            }
        }

        if((semicounter==1 || x3==matstring.length()-1) && flagdone==0)
                {
                    //cout<<"size "<<CBC<<endl;
                    //firstsemi=x3;
                    if(x3==matstring.length()-1)
                    {
                        nomatrix=CBC-1;
                    }
                    else {nomatrix=CBC;}
                    flagdone=1;

                     for(int y=0;y<nomatrix;y++)
                {

                    colcounter+=matrixarray[y].GetnC();
                }
                }

    }
    //cout<<rowcounter<<endl;
    //cout<<colcounter<<endl;
}
}



/** @brief this fn makes overall aggregation for the concatenation functions
 *
 * @param matstring the inputstring 
 * @return newmat the string of concatenated matrix
 *
 */

string ConcatenateMatrix(string matstring)
{
    int rows,columns;
    string newmat;
    matstring=chartomatrix(matstring);
    rowcolcounter(matstring,rows,columns);
    newmat=concatenate(matstring,rows,columns);
    return newmat;
}


string InnerMatrixDetection(string s)
{
	for(int i=1; i<s.length(); i++)
	{
		if (s[i]=='[')
		for (int j=i-1; j<s.length();j++)
		{
			if(s[j]==']')
			{
				string x=s.substr(i,j-i+1);
				if(is_one_line(x))
				{
					//cout<<x<<endl;
					s.replace(i,x.length(),ConcatenateMatrix(x));
					//s.replace(i,x.length(),"[a]");
					
					//cout<<"B"<<endl;
					break;
				}


			}
			
			}	
		}
		
		//cout<<s<<endl;
		return s;
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////

















