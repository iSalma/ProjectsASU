
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <cstring>
#include <cstdlib>
#include <stdarg.h>
#include <vector>
#include <fstream>
#include <map>
#include <math.h>
#define pi 3.14159265
//#include <cmath>
#include<limits>
using namespace std;
class CMatrix
{
	int nR, nC;
	double** values;
public:
	CMatrix();
	~CMatrix();
	//CMatrix init(int r , int c);
	int GetnR(){return nR;};
	int GetnC(){return nC;};
	CMatrix(const CMatrix& d);
	void reset();
	double getvalue();

	  	
		   enum MI { MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };
		   CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);
		   CMatrix(int nR, int nC, double first, ...);
		   CMatrix(string s);   // constructor take a string
		   void copy(string s); 
		   string getString();
		   string getString1();
		   CMatrix operator=(string s);
		   CMatrix operator=(CMatrix m);
		   CMatrix(double d);
		   void copy(double d);
		   CMatrix operator=(double d);

	
	
	
		   void setSubMatrix(int iR, int iC, CMatrix& m);
		   CMatrix getSubMatrix(int r, int c, int nr, int nc);
		   void addColumn(CMatrix& m); 
		   void addRow(CMatrix& m);
	
	
	
	
	

		   void add(CMatrix m);
		   void operator+=(CMatrix m);
		   void operator+=(double d);
		   CMatrix operator+(CMatrix m);
		   CMatrix operator+(double d);
		   void sub(CMatrix m);
		   void operator-=(CMatrix m);
		   void operator-=(double d);
		   CMatrix operator-(CMatrix m);
		   CMatrix operator-(double d);
		   CMatrix operator++();
		   CMatrix operator++(int);
		   CMatrix operator--();
		   CMatrix operator--(int);
		   CMatrix operator-();
		   CMatrix operator+();

		   friend ostream& operator <<(ostream &os,CMatrix m);
	
	
	
	           void mul(CMatrix m);
	           void operator*=(CMatrix m);
	           void operator*=(double d);
	           CMatrix operator*(CMatrix m);
	           CMatrix operator*(double d);
	
		   
	
		  // double getDeterminant();
		   //CMatrix getCofactor(int r, int c);
		   //CMatrix adjoint();
		   CMatrix inverse();
	
	
	
		   void div(CMatrix m);
		   CMatrix operator/(CMatrix m);
		   void operator/=(CMatrix m);

		   


		   void PrintMatrix();

		   CMatrix transpose ();
		   CMatrix elediv ();
	
		     CMatrix elediv (double Number);
 		     CMatrix elesub (double Number);
 		     CMatrix elepow (double Number);	   
 		     CMatrix eleadd (double Number);	   
 		     CMatrix elemul (double Number);
	
		     CMatrix random (int r, int c);	   
 		     CMatrix zeros (int r, int c);
	
		   CMatrix ones (int Number1);
		   CMatrix eye (int Number1);
		   CMatrix ones (int Number1 , int Number2);
	CMatrix eye (int Number1 , int Number2);

	
		   CMatrix  logg();
	CMatrix  logg10();
	CMatrix  expp();
	CMatrix sqrtt();


	CMatrix sinn();
	CMatrix coss();
	CMatrix tann();
	CMatrix asinn();
	CMatrix acoss();
	CMatrix atann();
	CMatrix sinnh();
	CMatrix cossh();
	CMatrix tannh();



	CMatrix power(int N);
                   CMatrix operator^(int d);
		   CMatrix InverseforPower();
		   double operator^(double d);

		   
	
};




//void arrayModification(int y,int x,double*p);

//void arrayModification(int y,int x,char *p);
//void arrayModification(int y,int x,int *p);
//string Get_Result(string s1);

//string spacetrim(string x) ;
//string hesab (string t);

//string cleanexp(string b);
