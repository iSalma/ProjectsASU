/*! A matrix class to be used in c++
 *         used to create a Matlab like program
 *
 *  This is a CMatrix class that is designed by students in the
 *  ASU Faculty of Engineering. It is designed to read files from
 *  the user and containing operations like those performed on
 *  octave and matlab and desplay the answer on the terminal.
 *
 * Completed on: 28/1/2018
 */

#include "CMatrix.h"




////////////////////////////////////////////////        CONSTRUCTOR       //////////////////////////////////////////////////////

/** A constructor.
 *
 *  Used to construct an empty matrix and set 
 *  initial values to 0
 *
 */
CMatrix::CMatrix()
{
	nR = nC = 0; 
	values = NULL;
}


//////////////////////////////////////////////        DESTRUCTOR         //////////////////////////////////////////////////////

/** A destrucor.
 *
 *  Used to delete the values and set the pointers
 *  to Null when program is terminated
 *
 *  @see reset()
 */

CMatrix::~CMatrix()
{
	reset();
}


double CMatrix::getvalue()
{return values[0][0];
}

////////////////// Constructor takes number of rows and columns and initializes with zeros///////////////////
/*
CMatrix CMatrix::init(int r , int c)
{
	nR=r;
	nC=c;

	if ((nR*nC) == 0) 
	{ 
		values = NULL; return;
	}

	values = new double*[r];
	for(int i=0;i<r;i++)
	{
		values[i] = new double[c]; 
		for(int j=0;j<c;j++)
		values[i][j]=0;

	}


}
*/




////////////////////////////////////////////      COPY CONSTRUCTOR      /////////////////////////////////////////////////////

/** A copy constructor.
 *
 *  Used to enable copying of matrices
 *  
 *  @param CMaatrix &d is a matrix
 *
 */

CMatrix::CMatrix(const CMatrix &d)
{
	if(d.nR==0 && d.nC==0)
	{
		nR=nC=0;
		values=NULL;
		return;
	}

	nR=d.nR;
	nC=d.nC;
	values = new double*[nR];
	for(int i=0;i<nR;i++)
	{
		values[i] = new double[nC]; 
		for(int j=0;j<nC;j++)
		values[i][j]=d.values[i][j];

	}

}


//////////////////////////////////////////////              RESET             /////////////////////////////////////////////////


/** A reset function.
 *
 *  Used to clear the values of matrix and set 
 *  pointers to Null called by the destructor
 *
 *  @see ~CMatrix()
 *
 */


void CMatrix::reset() 
{ 
	if (values) 
{ 
	for (int i = 0; i<nR; i++)
	delete[] values[i]; 
delete[] values; 
}
nR = nC = 0; 
values = NULL;
}





/////////////////////////////////////////////       FOR DEFFERENT INPUTS        ///////////////////////////////////////////////////

/** A constructor.
 *
 *  Used to construct an initialized matrix and set 
 *  initial values to initializationValue
 *
 */

CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue) 
{ 
	this->nR = nR;
	this->nC = nC; 
if ((nR*nC) == 0) 
{ 
	values = NULL; return;
}
values = new double*[nR]; 
for (int iR = 0; iR<nR; iR++) 
{ 
	values[iR] = new double[nC]; 
   for (int iC = 0; iC<nC; iC++) 
    { 
	switch (initialization) 
      {
        case MI_ZEROS: values[iR][iC] = 0; break; 
        case MI_ONES: values[iR][iC] = 1; break; 
	case MI_EYE: values[iR][iC] = (iR == iC) ? 1 : 0; break; 
	case MI_RAND: values[iR][iC] = (rand() % 1000000) / 1000000.0; break; 
	case MI_VALUE: values[iR][iC] = initializationValue;
	break; 
      } 
    } 
  } 
}


/** A constructor.
 *
 *  @brief Used to construct matrix and set values
 *  @param nR is number of rows nC is columns 
 *  and first is the first of multiple values for matrix
 */


CMatrix::CMatrix(int nR, int nC, double first, ...)
{
	this->nR = nR;
	this->nC = nC; 
	if ((nR*nC) == 0) 
	{ 
		values = NULL; return;
	}
	values = new double*[nR];
	va_list va;
	va_start(va, first);

	for (int iR = 0; iR<nR; iR++)
	{
		values[iR] = new double[nC];

	for (int iC = 0; iC<nC; iC++) 
	{ 
		values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, double); 
	} 
	}
	va_end(va);
}










/////////////////////////////////////////////////      STRING INPUT         ////////////////////////////////////////////////////



/** A constructor.
 *
 *  @brief Used to construct matrix and set 
 *  @param s is a string input from user
 *  @see copy(s)
 */

CMatrix::CMatrix(string s)                    // constructor takes string 
{
	nR = nC = 0; 
	values = NULL;
	copy(s);
}






/** @brief this an operator overloading fn
 *	@return this matrix
 *  @see copy(string s)
 */


CMatrix CMatrix::operator=(string s)
{
	copy(s);
	return *this;
}





void CMatrix::copy(string s) 
{ 
reset();
char* buffer = new char[s.length()+1]; 
strncpy(buffer,s.c_str(),s.length()+1);
//char* lineContext; 
const char* lineSeparators = ";\r\n";   ///we removed \n from separators
char* line = strtok(buffer, lineSeparators); 
char* Remainlines=strtok(NULL, "");
while(line) 
{ 
	CMatrix row; 
	//char* context; 
	const char* separators = " []"; 
	char* token = strtok(line, separators); 
	while(token) 
	{ 
		const double token_value=atof(token);
		CMatrix item ;
		item=(const double)token_value;
		row.addColumn(item); 
		token = strtok(NULL, separators); 
	}
if(row.nC>0 && (row.nC==nC || nR==0)) addRow(row);
line = strtok(Remainlines, lineSeparators);
Remainlines= strtok(NULL, "");
} 
delete[] buffer;
}

/** A function to get string of matrix. 
 *
 *  Used to get the values of a matrix in form of a
 *  string between square brackets
 *
 */

string CMatrix::getString1()
{
	string s;
	if (nR==1&&nC==1)
	{
		char buffer[50]; 
		snprintf(buffer, 50, "[ %f ]", values[0][0]); 
		s = buffer; 
		return s;
	}

	for(int iR=0;iR<nR;iR++) 
	{ 
		for(int iC=0;iC<nC;iC++) 
		{
			if (iR==0&&iC==0)

			{
				char buffer[50]; 
				snprintf(buffer, 50, "[ %f", values[iR][iC]); 
				s += buffer; 
			}
			else if(iR==nR-1&&iC==nC-1)
			{
				char buffer[50]; 
				snprintf(buffer, 50, " %f ]", values[iR][iC]); 
				s += buffer; 	
			}	
			else
			{
				char buffer[50]; 
				snprintf(buffer, 50, " %f", values[iR][iC]); 
				s += buffer;
			} 
		}

		if(iR!=nR-1)
		 s+=" ;"; 
	}

	return s;


}



/** A function to get string of matrix. 
 *
 *  Used to get the values of a matrix same as 
 *  matlab or octave
 *
 */

string CMatrix::getString() 
{ 
	string s; 
	for(int iR=0;iR<nR;iR++) 
	{ 
		for(int iC=0;iC<nC;iC++) 
		{
			
			char buffer[50]; 
			snprintf(buffer, 50, " %f \t", values[iR][iC]); 
			s += buffer; 
		} s+="\n"; 
	} return s; 
}

/*
string CMatrix::getString() 
{ 
	string s; 
	for(int iR=0;iR<nR;iR++) 
	{ 
		for(int iC=0;iC<nC;iC++) 
		{
			
			char buffer[50]; 
			sprintf_s(buffer, 50, "%g\t", values[iR][iC]); 
			s += buffer; 
		} s+="\n"; 
	} return s; 
}
*/








/////////////////////////////////////////////////       USEFUL FUNCTIONS          ////////////////////////////////////////////



/** @brief this fn sets a inner matrix within a larger one
 *  @param r is the number of row of inner matrix
 *  @param c is the number nof column of inner matrix
 *  @param m is the inner matrix to be set
 */


void CMatrix::setSubMatrix(int r, int c, CMatrix& m) 
{ 
	if((r+m.nR)>nR || (c+m.nC)>nC)throw("Invalid matrix dimension"); 
	for(int iR=0;iR<m.nR;iR++) 
		for(int iC=0;iC<m.nC;iC++) 
			values[r+iR][c+iC] = m.values[iR][iC]; 
}


/** @brief this fn gets a innner matrix within a larger one
 *  @param r is the number of row of inner matrix
 *  @param c is the number of column of inner matrix
 *  @param nr is the number of rows to get
 *  @param nc is the number of columns to get
 */


CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc) 
{ if((r+nr)>nR || (c+nc)>nC)throw("Invalid matrix dimension"); 
CMatrix m(nr, nc); 
for(int iR=0;iR<m.nR;iR++) 
	for(int iC=0;iC<m.nC;iC++) 
		m.values[iR][iC] = values[r+iR][c+iC]; 
return m; 
}


/** @brief this fn adds a column to a matrix
 *  @param m is the matrix to add a column to
 *
 */

void CMatrix::addColumn(CMatrix& m) 
{ 
	CMatrix n(max(nR, m.nR), nC+m.nC); 
	n.setSubMatrix(0, 0, *this); 
	n.setSubMatrix(0, nC, m); 
	*this = n; 
}


/** @brief this fn adds a row to a matrix
 *  @param m is the matrix to add a row to
 *
 */


void CMatrix::addRow(CMatrix& m) 
{ 
	CMatrix n(nR+m.nR, max(nC, m.nC)); 
	n.setSubMatrix(0, 0, *this); 
	n.setSubMatrix(nR, 0, m); 
	*this = n; 
}





//////////////////////////////////////////////    COPY MATRIX OPERATOR         ///////////////////////////////////////////////


/** @brief this an operator overloading fn
 *	that equalize this matrix to d matrix
 *	@return this matrix
 *  @see reset()
 */


CMatrix CMatrix::operator=(CMatrix d)
{
	
	reset();
	if(d.nR==0 && d.nC==0)
	{
		nR=nC=0;
		values=NULL;
		return *this;
	}

	nR=d.nR;
	nC=d.nC;
	values = new double*[nR];
	for(int i=0;i<nR;i++)
	{
		values[i] = new double[nC]; 
		for(int j=0;j<nC;j++)
		values[i][j]=d.values[i][j];

	}

return *this; 
}



/////////////////////////////////////////////        DOUBLE  INPUT       //////////////////////////////////////////////////////

/** A constructor.
 *
 *  @brief Used to construct a 1x1 matrix 
 *  @param d is the value of 1x1 matrix
 *  @see copy(double d)
 */


CMatrix::CMatrix(double d) 
{
	nR = nC = 0; 
values = NULL;
copy(d); 
}


/** A constructor.
 *
 *  @brief Used to construct a 1x1 matrix
 *  @param d is the value of 1x1 matrix
 *  
 */


void CMatrix::copy(double d) 
{ 
	reset();
this->nR = 1; 
this->nC = 1; 
values = new double*[1]; 
values[0] = new double[1]; 
values[0][0] = d; 
}



/** @brief this an operator overloading fn
 *	
 *  @param d is the value of 1x1 matrix
 *
 *  @return this matrix
 *  
 *  @see copy(double d)
 *
 */


CMatrix CMatrix::operator=(double d) 
{ 
	copy(d); 
return *this; 
}




//////////////////////////////////////////////////////       ADD FUNCTIONS     ////////////////////////////////////////////////

/** @brief this fn add this matrix to m matrix
 *
 *  @param m is the matrix to be added to this 
 *
 */
void CMatrix::add(CMatrix m) 
{ 
	if (nR != m.nR || nC != m.nC)
throw("Invalid matrix dimension"); 
for (int iR = 0; iR<nR; iR++)
	for (int iC = 0; iC<nC; iC++)
	values[iR][iC] += m.values[iR][iC]; 
}


/** @brief this an addition operator fn
 *
 *  @param m is the matrix to be added to this
 * 
 *  @see add(CMatrix m)
 */

void CMatrix::operator+=(CMatrix m) 
{ add(m);}

/** @brief this an addition operator fn
 *
 *  @param d is the number to be added to this
 *
 *  @see add(CMatrix m)
 */

void CMatrix::operator+=(double d)
{ add(CMatrix(nR, nC, MI_VALUE, d)); }


/** @brief this an addition operator fn
 *
 *  @param m is the matrix to be added to this
 *  @return this matrix added with matrix m  
 *  @see operator+=(CMatrix m)
 */

CMatrix CMatrix::operator+(CMatrix m) 
{ 
	CMatrix r = *this;
r += m; 
return r; 
}

/** @brief this an addition operator fn
 *
 *  @param d is the number to be added to this
 *  @return this matrix elements added with double d 
 *  @see operator+=(double d)
 */


CMatrix CMatrix::operator+(double d) 
{ 
	CMatrix r = *this; 
r += d;
return r;
}



//////////////////////////////////////////////////         SUBTRACT FUNCTIONS       ///////////////////////////////////////

/** @brief this fn subtract this matrix and m matrix
 *
 *  @param m is the matrix to be subtracted from this
 * 
 */

void CMatrix::sub(CMatrix m)
{
	if (nR != m.nR || nC != m.nC)
		throw("Invalid matrix dimension");
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			values[iR][iC] -= m.values[iR][iC];
}

/** @brief this an subtraction operator fn
 *  
 *  @param m is the matrix to be subtracted from this
 *
 *  @see sub(CMatrix m)
 * 
 */


void CMatrix::operator-=(CMatrix m)
{
	sub(m);
}

/** @brief this an subtraction operator fn
 *
 *  @param d is the number to be subtracted from this 
 *  @see sub(CMatrix m)
 */


void CMatrix::operator-=(double d)
{
	sub(CMatrix(nR, nC, MI_VALUE, d));
}

/** @brief this an subtraction operator fn
 *
 *  @return r is this matrix subtracted with matrix m  
 *  @see operator-=(CMatrix m)
 */

CMatrix CMatrix::operator-(CMatrix m)
{
	CMatrix r = *this;
	r -= m;
	return r;
}

/** @brief this an subtraction operator fn
 *
 *  @return r is this matrix elements subtracted with double d 
 *  @see operator-=(double d)
 */

CMatrix CMatrix::operator-(double d)
{
	CMatrix r = *this;
	r -= d;
	return r;
}






///////////////////////////////////////////        MULTIPLICATION          ///////////////////////////////////////////////////

/** @brief this fn multiply this matrix by m matrix
 *
 * 
 */

void CMatrix::mul(CMatrix m)
{ 
	if(nC!=m.nR) 
		throw("Invalid matrix dimension"); 
	if(nC==0 && m.nC==0)
		return;
	
	CMatrix d(nR, m.nC);
	for(int iR=0;iR<d.nR;iR++) 
		for(int iC=0;iC<d.nC;iC++)
		{
			d.values[iR][iC] = 0; 
			for(int k=0;k<m.nR;k++)
			d.values[iR][iC] += values[iR][k]*m.values[k][iC]; 
		}
	

		reset();
	
		this->nR=d.nR;
		this->nC=d.nC;
		values = new double*[nR];
		for(int i=0;i<nR;i++)
		{
			values[i] = new double[nC]; 
			for(int j=0;j<nC;j++)
			values[i][j]=d.values[i][j];
	
		}
	
}

/** @brief this an multiplication operator overloading fn
 *
 *  @param m is the matrix to be multiplied to this
 *  @see mul(CMatrix m)
 */

void CMatrix::operator*=(CMatrix m)
{ mul(m); } 

/** @brief this an multiplication operator overloading fn
 *
 *  @param d is the element to be multiplied to this
 *  
 */

void CMatrix::operator*=(double d)
{ 
	for(int iR=0;iR<nR;iR++) 
		for(int iC=0;iC<nC;iC++) 
			values[iR][iC] *= d;
}
/** @brief this an multiplication operator fn
 *
 *  @param m is the matrix to be multiplied to this
 *  @return r is this matrix multiplied by matrix m 
 *  @see operator*=(CMaatrix m)
 *
 */

CMatrix CMatrix::operator*(CMatrix m)
{
	CMatrix r = *this;
	r*=m;
	return r;
}

/** @brief this an multiplication operator fn
 *
 *  @param d is the element to be multiplied to this
 *  @return r is this matrix multiplied by double d 
 *  @see operator*=(double d)
 *
 */

CMatrix CMatrix::operator*(double d)
{
	CMatrix r = *this; 
	r*=d; 
	return r;
}


///////////////////////////////////////////        INCREMENTAL OPERATORS          ///////////////////////////////////////////////////

/** @brief this an pre_add operator fn
 *
 *  @return this matrix with elements increased by one 
 *  @see add(CMatrix m)
 */

CMatrix CMatrix::operator++()
{ add(CMatrix(nR, nC, MI_VALUE, 1.0)); return *this;
}

/** @brief this an pos_tadd operator fn
 *
 *  @return this matrix then increase it's elements by one 
 *  @see add(CMatrix m)
 */

CMatrix CMatrix::operator++(int)
{
CMatrix C = *this; add(CMatrix(nR, nC, MI_VALUE, 1.0)); return C;
}

/** @brief this an pre_sub. operator fn
 *
 *  @return this matrix with elements decreased by one 
 *  @see add(CMatrix m)
 */

CMatrix CMatrix::operator--()
{ add(CMatrix(nR, nC, MI_VALUE, -1.0)); return *this;
}

/** @brief this an post_sub. operator fn
 *
 *  @return this matrix then decreased it's elements by one 
 *  @see add(CMatrix m)
 */

CMatrix CMatrix::operator--(int)
{
CMatrix r = *this; add(CMatrix(nR, nC, MI_VALUE, -1.0)); return r;
}

/** @brief this an operator overloading fn
 *
 *  @return this matrix with inverted elements 
 *  
 */

CMatrix CMatrix::operator-()
{ for(int iR=0;iR<nR;iR++) for(int iC=0;iC<nC;iC++) values[iR][iC] = -values[iR][iC];
return *this;
}

/** @brief this an operator overloading fn
 *
 *  @return this matrix 
 *  
 */

CMatrix CMatrix::operator+()
{ return *this;
}

///////////////////////////////////////////        INVERSE       ///////////////////////////////////////////////////


/** @brief this fn makes inverse of the given matrix
 *
 *  @return a matrix that is the inverse of this
 *
 */


CMatrix CMatrix::inverse()
{
    int nr=nR;
    int nc=nC;
    CMatrix d(nR,nC*2,MI_ZEROS,0); //new matrix to carry augmented values
    CMatrix outt(nR,nC);
    CMatrix temp(1,2*nC,MI_ZEROS,0); //inverse matrix
    for(int i=0;i<nC;i++)
    {
        for(int j=0;j<nR;j++)
        {
            d.values[i][j]=values[i][j];  //putting values of matrix in the augm. matrix

        }
    }

    for(int i=0;i<nR;i++)   //ones diagonal
    {
         d.values[i][nR+i]=1;   // adding the identity matrix to augm. matrix
    }


    int j=0;
    double diag=d.values[0][0];
    for(int i2=1;i2<nR;i2++)
    {
        if(d.values[i2][0]>diag || diag==0)
        {
            for(int k1=0;k1<2*nC;k1++)
            {
                temp.values[0][k1]=d.values[0][k1];
                d.values[0][k1]=d.values[i2][k1];
                d.values[i2][k1]=temp.values[0][k1];
            }
            }
            diag=d.values[0][0];
    }
    double num=0;
    for(int i=0;i<nR;i++)
    {
           for(int x=0;x<2*nC;x++)
           {
               if(diag==0){throw ("matrix has no inverse");}

               d.values[i][x]=d.values[i][x]/diag;
           }
           //cout<<endl;
           for(int k=0;k<nR;k++)
           {
               num=d.values[k][j];
               for(int l=0;l<2*nC;l++)
               {
                   if(k!=i)
                   {
                      d.values[k][l]=d.values[k][l]-(num*d.values[i][l]);
                   }
               }
           }
           if(i==nr-1){goto ending;}
           diag=d.values[i+1][j+1];
        for(int i2=i+1;i2<nR;i2++)
        {
            if(i2==nR-1){break;}
        if(d.values[i2+1][j+1]>diag || diag==0)
        {
            for(int k1=0;k1<2*nC;k1++)
            {
                temp.values[0][k1]=d.values[i+1][k1];
                d.values[i+1][k1]=d.values[i2+1][k1];
                d.values[i2+1][k1]=temp.values[0][k1];
            }
            diag=d.values[i+1][j+1];
        }
    }
         j++;
       }

    ending :
        for(int p=0;p<nr;p++)
    {
        for(int h=0;h<nc;h++)
        {
            outt.values[p][h]=d.values[p][h+nc];
        }
    }
    //cout<<outt.getString();
    //cout<<endl;
    return outt;
}











/*

CMatrix CMatrix::adjoint()
{
CMatrix adj(nR,nC);                     //Create a matrix to store the adjoint and return it
if (nR == 1)
{
adj.values[0][0] = 1;
return adj;
}

int sign = 1;
CMatrix temp(nR,nC);                    // temp is used to store the cofactors of "this"

for (int i=0; i<nR; i++)
{
for (int j=0; j<nC; j++)
{
temp=getCofactor(i, j);                  // get cofactor of element this[i][j]

// sign of adj[j][i] positive if sum of row
// and column indexes is even.
sign = ((i+j)%2==0)? 1: -1;

// Interchanging rows and columns to get the
// transpose of the cofactor matrix
adj.values[j][i] = (sign)*(temp.getDeterminant());
}
}
return adj;
}

CMatrix CMatrix::inverse()
{
    CMatrix inverse(nR, nC);              //Create a matrix to store the inverse and return it
    CMatrix current(nR, nC);              //this matrix will hold the values of this in the next line
    current=*this;
    // Find determinant of current (this)
    double det = current.getDeterminant();
    if (det == 0)
    {
        throw("Invalid matrix dimension");
    }
	
    // Find adjoint
    CMatrix adj(nR, nC);
    adj= current.adjoint();
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<nR; i++)
        for (int j=0; j<nC; j++)
            inverse.values[i][j] = adj.values[i][j]/det;
 
    return inverse;
}




CMatrix CMatrix::getCofactor(int r, int c) 
{ 
	if (nR <= 1 && nC <= 1)
throw("Invalid matrix dimension"); 

CMatrix m(nR - 1, nC - 1); 

for (int iR = 0; iR<m.nR; iR++)
	for (int iC = 0; iC<m.nC; iC++) 
{

	int sR = (iR<r) ? iR : iR + 1; 
    int sC = (iC<c) ? iC : iC + 1; 
    m.values[iR][iC] = values[sR][sC]; 
	}
return m; 
}




double CMatrix::getDeterminant() {
	if (nR != nC)throw("Invalid matrix dimension"); 

if (nR == 1 && nC == 1)

	return values[0][0];

double value = 0, m = 1;

for (int iR = 0; iR<nR; iR++) 
 {
	value += m * values[0][iR] * getCofactor(0, iR).getDeterminant(); 
m *= -1;
 }
	if(value==0)                                           // to prevent the program to return 0 so the program stops
		throw("can't devide , determinant = zero ");
	
	

return value;
}
*/
///////////////////////////////////////////        DIVISION          ///////////////////////////////////////////////////


/** @brief this fn takes a matrix and divide it by matrix m
 *
 * 
 */

void CMatrix::div(CMatrix m)
{  
	CMatrix INV(nR, nC);
	INV=m.inverse();
	if(nC!=INV.nR) 
		throw("Invalid matrix dimension");
	CMatrix current (nR,nC);
	current=*this;
	CMatrix result(nR,INV.nC);
	result= current*INV;
	reset();
	if(result.nR==0 && result.nC==0)
	{
		nR=nC=0;
		values=NULL;
		return;
	}

	nR=result.nR;
	nC=result.nC;
	values = new double*[nR];
	for(int i=0;i<nR;i++)
	{
		values[i] = new double[nC]; 
		for(int j=0;j<nC;j++)
		values[i][j]=result.values[i][j];

	}

	
}

/** @brief this an operator overloading fn
 *
 *  @see div(m)
 */

void CMatrix::operator/=(CMatrix m)
{ div(m); } 

/** @brief this an operator overloading fn
 *
 *  @return this matrix divided by m matrix 
 *  @see operator/=(CMatrix m)
 */

CMatrix CMatrix::operator/(CMatrix m)
{
	CMatrix r = *this;
	r/=m;
	return r;
}













//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @brief this fn makes transpose of the given matrix
 *
 *  @return result is a matrix that is the transpose of this
 *
 */

CMatrix CMatrix::transpose ()
{	//CMatrix that =*this					// there's no need for this line we already have this matrix that the function calls
	CMatrix result(nC,nR);
	for (int i=0 ; i< nR ;i++)
	{
   		for (int j =0 ; j<nC; j++) 
   		{
      			result.values[j][i]= values[i][j];
   		}
	}
return result;
}

/** @brief this fn that inverse the elements of the given matrix
 *
 *  @return a matrix that has inversed elements of this elements
 *
 */

CMatrix CMatrix::elediv ()
{
	CMatrix result(nR,nC);
 	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=1.0/values[iR][iC];
		}
	}
	return result;

}

/////////////////////////////////////    dividing the elements of a matrix with a certain value    //////////////////////////////////////

/** @brief this fn divides the elements of a matrix with a certain value
 *
 *  @param element is the number to be divided by the elements of the matrix
 *
 *  @return a matrix all its elements divided by element
 *
 */

CMatrix CMatrix::elediv (double element)
{
	CMatrix result(nR,nC);
	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=values[iR][iC]/element;
		}
	}
 	
	return result;

}

/////////////////////////////////////    powering the elements of a matrix with a certain value    //////////////////////////////////////

/** @brief this fn raises the elements of a matrix to the power of a certain value
 *
 *  @param element is the number to be raised as a power to the elements of the matrix
 *
 *  @return a matrix all its elements are raised to the power of element
 *
 */

CMatrix CMatrix::elepow (double element)
{
	CMatrix result(nR,nC);
 	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=pow((values[iR][iC]),element);
		}
	}
	return result;

}

/////////////////////////////////////    subtracting the elements of a matrix with a certain value    //////////////////////////////////////

/** @brief this fn subtracts the elements of a matrix with a certain value
 *
 *  @param element is the number to be subracted to the elements of the matrix
 *
 *  @return a matrix all its elements subtracted by element
 *
 */

CMatrix CMatrix::elesub (double element)
{
	CMatrix result(nR,nC);
 	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=values[iR][iC]-element;
		}
	}
	return result;

}

/////////////////////////////////////    adding the elements of a matrix with a certain value    //////////////////////////////////////

/** @brief this fn adds the elements of a matrix with a certain value
 *
 *  @param t is the number to be added to the elements of the matrix
 *
 *  @return a matrix all its elements added to t
 *
 */

CMatrix CMatrix::eleadd (double t)
{
	CMatrix result(nR,nC);
 	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=t+values[iR][iC];
		}
	}
	return result;

}

/////////////////////////////////////    multiplying the elements of a matrix with a certain value    //////////////////////////////////////

/** @brief this fn multiplies the elements of a matrix with a certain value
 *
 *  @param t is the number to be multiplied to the elements of the matrix
 *
 *  @return a matrix all its elements multilied by t
 *
 */

CMatrix CMatrix::elemul (double t)
{
	CMatrix result(nR,nC);
 	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=t*values[iR][iC];
		}
	}
	return result;

}





/////////////////////////////////////    declaring a matrix with random numbers    //////////////////////////////////////

/** @brief this fn makes the rand matrix
 *
 *  @param nR is the number of rows and nC is columns
 *
 *  @return a matrix all its elements are random numbers
 *
 */

CMatrix CMatrix::random(int nR, int nC)
{
	CMatrix result(nR,nC);
	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=(rand() % 1000000) / 1000000.0;
		}
	}
	return result;
}

/////////////////////////////////////    declaring a matrix with zeros    //////////////////////////////////////

/** @brief this fn makes the zeroes matrix
 *
 *  @param nR is the number of rows and nC is columns
 *
 *  @return a matrix all its elements are 0s
 *
 */

CMatrix CMatrix::zeros(int nR, int nC)
{
	CMatrix result(nR,nC);
	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			result.values[iR][iC]=0;
		}
	}
	return result;
}


///////////////////////////////////////////////////// ONES Matrix ////////////////////////////////////////////////////////////////

/** @brief this fn makes the ones matrix
 *
 *  @param Number1 is the number of rows and Number2 is columns
 *
 *  @return a matrix all its elements are 1s
 *
 */

CMatrix CMatrix::ones (int Number1 , int Number2)
{
	CMatrix result(Number1,Number2);
 	for(int iR=0;iR<Number1;iR++)
	{
		for(int iC=0;iC<Number2;iC++)
		{
			result.values[iR][iC]=1;
		}
	}
	return result;

}

/** @brief this fn makes the ones matrix
 *
 *  @param Number1 is the number of rows and columns
 *
 *  @return a matrix all its elements are 1s
 *
 */

CMatrix CMatrix::ones (int Number1)
{
	CMatrix result(Number1,Number1);
 	for(int iR=0;iR<Number1;iR++)
	{
		for(int iC=0;iC<Number1;iC++)
		{
			result.values[iR][iC]=1;
		}
	}
	return result;

}

///////////////////////////////////////////////////// I Matrix ////////////////////////////////////////////////////////////////

/** @brief this fn makes the identity matrix
 *
 *  @param Number1 is the number of rows and Number2 is columns
 *
 *  @return an identity matrix its diagonals are 1s
 *
 */

CMatrix CMatrix::eye (int Number1 , int Number2)
{

	CMatrix result(Number1,Number2);
 	for(int iR=0;iR<Number1;iR++)
	{
		for(int iC=0;iC<Number2;iC++)
		{
			result.values[iR][iC]=(iR == iC) ? 1 :  0;
		}
	}
	return result;
}

/** @brief this fn makes the identity matrix
 *
 *  @param Number1 is the number of rows and columns
 *
 *  @return an identity matrix its diagonals are 1s
 *
 */

CMatrix CMatrix::eye (int Number1)
{

	CMatrix result(Number1,Number1);
 	for(int iR=0;iR<Number1;iR++)
	{
		for(int iC=0;iC<Number1;iC++)
		{
			result.values[iR][iC]=(iR == iC) ? 1 :  0;
		}
	}
	return result;
}




///////////////////////////////////////////////////// Log   Log10   sqrt   exp ////////////////////////////////////////////

/** @brief this fn makes the log for each element in the matrix
 *
 *  @return n is a matrix where each element with log of this matrix
 *
 */


CMatrix   CMatrix :: logg()
{
	//double inf=1.0/0.0;
	CMatrix n(nR,nC);

for (int i=0 ;i<nR;i++)
{
for (int j=0 ;j<nC;j++)
{

double t = values[i][j];
    if (t==0)
	n.values[i][j]=-std::numeric_limits<double>::infinity() ;
	//else if (t<0)complex
	else if (t==std::numeric_limits<double>::infinity())
		n.values[i][j]=std::numeric_limits<double>::infinity();
//	else if (t==-inf)
		//n.values[i][j]=inf;   complex -inf


	else
		n.values[i][j]=log(t);
}}
 return n;
 }

/** @brief this fn makes the log10 for each element in the matrix
 *
 *  @return n is a matrix where each element with log10 of this matrix
 *
 */

  CMatrix   CMatrix :: logg10()
{
	

	CMatrix n(nR,nC);

for (int i=0 ;i<nR;i++)
{
for (int j=0 ;j<nC;j++)
{
	
double t = values[i][j];
if (t==0)
	n.values[i][j]=- std::numeric_limits<double>::infinity();
// else if (t<0)//complec

//else if(t==-inf)n.values[i][j]= complex-inf
else if (t==std::numeric_limits<double>::infinity())
n.values[i][j]=std::numeric_limits<double>::infinity();

else 
	n.values[i][j]=log10(t);
}}
 return n;
 }
  
/** @brief this fn makes the exp for each element in the matrix
 *
 *  @return a matrix where each element with exp of this matrix
 *
 */

  CMatrix   CMatrix :: expp()
{
	
	CMatrix n(nR,nC);

for (int i=0 ;i<nR;i++)
{
for (int j=0 ;j<nC;j++)
{

double t = values[i][j];
if (t==std::numeric_limits<double>::infinity())
 n.values[i][j]=std::numeric_limits<double>::infinity();

else if (t==-std::numeric_limits<double>::infinity())
 n.values[i][j]=0;

 else n.values[i][j]=exp(t);
}}
 return n;
 }
/** @brief this fn makes the square root for each element in the matrix
 *
 *  @return a matrix where each element with sqrt of this matrix
 *
 */

   CMatrix   CMatrix :: sqrtt()
{
	CMatrix n(nR,nC);

for (int i=0 ;i<nR;i++)
{
for (int j=0 ;j<nC;j++)
{
	
double t = values[i][j];
if (t==std::numeric_limits<double>::infinity())
 n.values[i][j] =std::numeric_limits<double>::infinity();
//else if (t<0) complex no.
//else if (t==-inf)  n.values[i][j]=-infi
else  n.values[i][j]=sqrt(t);
}}
 return n;
 }







 ///////////////////////////////////////////////////trig fn //////////////////////////

 /** @brief this fn makes the sin dot for each element in the matrix
 *
 *  @return a matrix where each element with sin made for it
 *
 */

CMatrix CMatrix::sinn()
{
CMatrix n(nR,nC);

	for (int i=0 ; i<nR; i++)
	{

  		for(int z=0 ;z<nC ;z++)
  		{
    		double x = sin(values[i][z]);
			if (x>exp(10) || x<(-exp(10)))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			//cout<<x<<endl;
			}


			n.values[i][z]= x;
		}

	}

	return n;
}

/** @brief this fn makes the cos dot for each element in the matrix
 *
 *  @return a matrix where each element with cos made for it
 *
 */

CMatrix CMatrix::coss()
{
CMatrix n(nR,nC);

	for (int i=0 ; i<nR; i++)
	{

  		for(int z=0 ;z<nC ;z++)
  		{
    		double x = cos(values[i][z]);
    		//cout<<x<<endl;
			if (x>exp(10) || x<(-exp(10)))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			}

			n.values[i][z]= x;
		}

	}

	return n;
}

/** @brief this fn makes the tan dot for each element in the matrix
 *
 *  @return a matrix where each element with tan made for it
 *
 */

CMatrix CMatrix::tann()
{
CMatrix n(nR,nC);

	for (int i=0 ; i<nR; i++)
	{

  		for(int z=0 ;z<nC ;z++)
  		{
    		double x = tan(values[i][z]);

			if (x>exp(10) || x<(-exp(10)))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			}

			n.values[i][z]= x;
		}

	}

	return n;
}
/** @brief this fn makes the sin-1 dot for each element in the matrix
 *
 *  @return a matrix where each element with sin-1 made for it 
 *
 */

CMatrix CMatrix::asinn()
{
CMatrix n(nR,nC);
for (int i=0 ; i<nR; i++)
{
  for(int z=0 ;z<nC ;z++)
  {
if(values[i][z]>=-1.0 && values[i][z]<=1.0)   
 	{
 		double x = asin(values[i][z]);

			if (x>exp(10))   {x=std::numeric_limits<double>::infinity();}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )  {x=0.0;}

			n.values[i][z]= x;
	}
	else 
    {
    	n.values[i][z] = std::numeric_limits<double>::quiet_NaN();
	}
  }
}
return n;
}

/** @brief this fn makes the cos-1 dot for each element in the matrix
 *
 *  @return a matrix where each element with cos-1 made for it 
 *
 */

CMatrix CMatrix::acoss()
{
CMatrix n(nR,nC);
for (int i=0 ; i<nR; i++)
{
  for(int z=0 ;z<nC ;z++)
  {
	if(values[i][z]>=-1.0 && values[i][z]<=1.0)   
 	{
 		double x = acos(values[i][z]);

			if (x>exp(10))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			}

			n.values[i][z]= x;
	}
	else 
    {
    	n.values[i][z] = std::numeric_limits<double>::quiet_NaN();
	}
  }
}

return n;
}

/** @brief this fn makes the tan-1 dot for each element in the matrix
 *
 *  @return a matrix where each element with tan-1 made for it 
 *
 */

CMatrix CMatrix::atann()
{
CMatrix n(nR,nC);
for (int i=0 ; i<nR; i++)
{
  for(int z=0 ;z<nC ;z++)
  {
	if(values[i][z]==std::numeric_limits<double>::infinity() || values[i][z]>exp(12))
	{n.values[i][z]=pi/(double)2; continue;}
	else
	{
    		double x = atan(values[i][z]);

			if (x>exp(10) || x<(-exp(10)))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			}

			n.values[i][z]= x;
	}
  }
}

return n;
}

/** @brief this fn makes the sinh dot for each element in the matrix 
 *
 *  @return a matrix where each element with sinh made for it 
 *
 */

CMatrix CMatrix::sinnh()                 
{
CMatrix n(nR,nC);

	for (int i=0 ; i<nR; i++)
	{

  		for(int z=0 ;z<nC ;z++)
  		{
    		double x = sinh(values[i][z]);

			if (x>exp(10) || x<(-exp(10)))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			}

			n.values[i][z]= x;
		}

	}

	return n;
}

/** @brief this fn makes the cosh dot for each element in the matrix 
 *
 *  @return a matrix where each element with cosh made for it 
 *
 */

CMatrix CMatrix::cossh()
{
CMatrix n(nR,nC);

	for (int i=0 ; i<nR; i++)
	{

  		for(int z=0 ;z<nC ;z++)
  		{
    		double x = cosh(values[i][z]);

			if (x>exp(10) || x<(-exp(10)))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			}

			n.values[i][z]= x;
		}

	}

	return n;
}

/** @brief this fn makes the tanh dot for each element in the matrix
 *
 *  @return a matrix where each element with tanh made for it 
 *
 */

CMatrix CMatrix::tannh()
{
	CMatrix n(nR,nC);

	for (int i=0 ; i<nR; i++)
	{

  		for(int z=0 ;z<nC ;z++)
  		{
    		double x = tanh(values[i][z]);

			if (x>exp(10) || x<(-exp(10)))
			{
			x=std::numeric_limits<double>::infinity();
			}

			if ( (x<exp(-10) && x>0 ) || ( x<0 && x>(-exp(-10)) ) )
			{
			x=0.0;
			}

			n.values[i][z]= x;
		}

	}

	return n;
}













///////////////////////////////////////////        PRINT MATRIX          ///////////////////////////////////////////////////

/** Fn to print matrix.
 *		This function takes a matrix and prints out its contents 
 * in an organized way similar to octave
 *
 */


void CMatrix::PrintMatrix()
{
	for (int i = 0; i < nR; i++)
	{
		for (int j = 0; j < nC; j++)
			cout << values[i][j] << "   ";
		cout <<endl;
	}
}



/** Fn to support ostream.
 *		This function enables the matrix
 *  to print its contents as a string using cout<<
 *
 */

ostream& operator <<(ostream &os,CMatrix m)
{
	os << m.getString();
	return os;
}




////////////////////////////////////////power///////////////////////////////////////////////////////

/** @brief this an operator overloading fn
 *
 *  @return a matrix raised to the power of d 
 *  @see power(d)
 */


CMatrix CMatrix::operator^(int d)
{

	return power(d);
}

/** @brief this an operator overloading fn
 *
 *  @return double which represent the single element in 1x1 matrix raised to the power of d 
 *  
 */

double CMatrix::operator^(double d)
{
	CMatrix result(nR,nC);

	if(nC!=result.nR) 
		throw("Invalid matrix dimension"); 

	if( d == 0 )
	{
		result = eye (nR , nC);
	}

	else 
	{
		result.values[0][0]=pow(values[0][0],d);
	}
	return result.values[0][0];	
}

/** @brief this fn takes a matrix and raises it to an int power
 *
 *  @param N is the integer power
 *  @return a matrix raised to the power of d
 * 
 */

CMatrix CMatrix::power(int N)
{ 
	CMatrix result(nR,nC);

	if(nC!=result.nR) 
		throw("Invalid matrix dimension"); 

	if( N == 0 )
	{
		result = eye (nR , nC);
	}

	else if(N>0)
	{
 		for(int iR=0;iR<nR;iR++)
		{
			for(int iC=0;iC<nC;iC++)
			{
				result.values[iR][iC]=(values[iR][iC]);
			}
		}

		for(int i=1 ; i<N ; i++)
			result*=*this;
	}

	else if(N<0)
	{
 		for(int iR=0;iR<nR;iR++)
		{
			for(int iC=0;iC<nC;iC++)
			{
				result.values[iR][iC]=(values[iR][iC]);
			}
		}

	
		result = (result.InverseforPower()).power(abs(N));
	}
	
	return result;
}

/** @brief this fn makes inverse of the given matrix
 *  using Gauss method 
 *  @return a matrix that is the inverse of this
 *
 */

CMatrix CMatrix :: InverseforPower()
{	
    //int nr=nR;
    //int nc=nC;
    CMatrix current(nR,nC*2,MI_ZEROS,0); //new matrix to carry augmented values
    CMatrix result(nR,nC);
   // CMatrix temp(1,2*nC,MI_ZEROS,0); //inverse matrix
    for(int i=0;i<nC;i++)
    {
        for(int j=0;j<nR;j++)
        {
            current.values[i][j]=values[i][j];  //putting values of matrix in the augm. matrix

        }
    }

    for(int i=0;i<nR;i++)   //ones diagonal
    {
         current.values[i][nR+i]=1;   // adding the identity matrix to augm. matrix
    }

    for(int ir=0 ; ir<nR ;ir++)
    {
        double c = current.values[ir][ir] ;
        for(int ic=0 ; ic<2*nC ; ic++)
        {
            current.values[ir][ic]=current.values[ir][ic]/c;
        }

        for(int k=0 ; k<nR ; k++)
        {
            double v = current.values[k][ir] ;
            for(int i=0 ; i<2*nC ; i++)
            {
                if(ir == k)  { continue; }
                else
                    current.values[k][i]=current.values[k][i]-(v*current.values[ir][i]);
            }
        }
    }

	for(int ir=0 ; ir<nR ; ir++)
	{
		for(int k=nC ; k<2*nC ; k++)
			result.values[ir][k-nC]=current.values[ir][k];
	}

    return result;
}



















/////////////////////////////////////////////////main functions ///////////////////////////////////////////

/*

void arrayModification(int y,int x,double*p)
{
	for(int i=y;i<=x+1;i++)
	{
		*(p+(i))=*(p+i+1);
	}
}
void arrayModification(int y,int x,char *p)
{
	for(int i=y;i<=x+1;i++)
	{
		*(p+(i))=*(p+i+1);
	}
}
void arrayModification(int y,int x,int *p)
{
	for(int i=y;i<=x+1;i++)
	{
		*(p+(i))=*(p+i+1);
	}
}
string Get_Result(string s1)
{
	int flag=0;                                //to count the number of the operations between two brackets ()
	char elements [100]={};                    //contains the operands of the input string * , - , + , / , ^
	int places[100]={};                        //contains the index of each operand 
	string values[100]={};                     //contains all the numbers in the input string in order in string form
	double Values[100]={};					   //contains all the numbers in the input string in order in double form
	double Result;                             //contains the final result of the input string as a double form
	string result;                             //contains the final result of the input string as a string form 
	int j=0;
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
	values[j]=s1.substr(places[j-1]+1,s1.size()-places[j-1]-1);
	Values[j]=atof(values[j].c_str());
	for (int i = 0; i < j; i++)
	{
		if (elements[i]=='^')
		{
			
			if (i==0)
			{
				Values[i+1]=pow(Values[i],Values[i+1]);
				result=to_string(Values[i+1]);
				s1.erase(0,places[i]+values[i+1].length()+1);
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=pow(Values[i],Values[i+1]);
				result=to_string(Values[i+1]);
				s1.erase(places[i-1]+1,places[i+1]-1);
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
			
			if (i==0)
			{
				Values[i+1]=Values[i]*Values[i+1];
				result=to_string(Values[i+1]);
				s1.erase(0,places[i]+values[i+1].length()+1);
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=Values[i]*Values[i+1];
				result=to_string(Values[i+1]);
				//arrayModification(i,j,Values);
				s1.erase(places[i-1]+1,places[i+1]-1);
				s1.insert(places[i-1]+1,result);
				arrayModification(i,j,Values);
				arrayModification(i,j,elements);
				arrayModification(i,j,places);
			}
		}
		if (elements[i]=='/')
		{
			
			if (i==0)
			{
				Values[i+1]=Values[i]/Values[i+1];
				result=to_string(Values[i+1]);
				s1.erase(0,places[i]+values[i+1].length());              
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=Values[i]/Values[i+1];
				result=to_string(Values[i+1]);
				//arrayModification(i,j,Values);
				s1.erase(places[i-1]+1,places[i+1]-1);
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
			if (i==0)
			{
				Values[i+1]=Values[i]+Values[i+1];
				result=to_string(Values[i+1]);
				s1.erase(0,places[i]+values[i+1].length()+1);
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=Values[i]+Values[i+1];
				result=to_string(Values[i+1]);
				s1.erase(0,places[i+1]-1);
				s1.insert(0,result);
			}
		}
		if (elements[i]=='-')
		{
			if (i==0)
			{
				Values[i+1]=Values[i]-Values[i+1];
				result=to_string(Values[i+1]);
				s1.erase(0,places[i]+values[i+1].length()+1);
				s1.insert(0,result);
			}
			else
			{
				Values[i+1]=Values[i]-Values[i+1];
				result=to_string(Values[i+1]);
				s1.erase(0,places[i+1]-1);       
				s1.insert(0,result);
			}
		}
		
	}
	return s1;
}

string spacetrim(string x)            //remove any unused spaces from the input string
{
	for(int i=0;i<x.length();i++)
	{
		if(x[i]==' '||x[i]==NULL)
		{x.erase(i,1);}
	}
	return x;
}




string hesab (string t)
{
	//string t="100/(50*2+50-50)";
	t=spacetrim(t);
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
	//cout<<operand<<R<<endl;
	
	return R;
}


string cleanexp(string b)
{
	//cout<<b<<endl;

	//string b="A = [[2.0[3.4;2.4 ;(3.5+9.1)] 2^3 -3+1.2 15/3]]";
	char x[1000000];
	strcpy (x,b.c_str());
	//char x[]="[[2.0[3.4;2.4 ;(3.5+9.1)] 2^3 -3+ 1.2 15 / 3]]";
	string s=x;
	char* spearators = "[] ;,";
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






*/


