//
//  main.cpp
//  hw5
/**
Author: <Patricia Antlitz>
Date: <2/23/23><3/11/2023>
Purpose: <Takes two fraction and compare it to each other to find the smallest, greater, equal fractions. It then performs addition, subtraction, multiplication and division of the fractions, reducing it to its smallest form>
Sources of Help: <https://www.tutorialspoint.com/reduce-the-fraction-to-its-lowest-form-in-cplusplus>
Time Spent: <1hr first day (2/23), 4 hrs second day (3/11)>
**/
/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 02/23/2023
Name:Patricia Antlitz
 
 second version on: 03/11/2023 (I was under the impression it was sure on 03/13/2023)
*/

#include <iostream>
using namespace std;

void denominatorHelper(int &userDenominator);

class Rational{
public:
    Rational():numerator(0), denominator(1){}
    Rational(int wholeNumber):numerator(wholeNumber), denominator(1){}
    Rational(int aNumerator, int aDenominator);
    
    void setNumerator(int aNumerator)
    {
        numerator = aNumerator;
    }
    int getNumerator(void) const
    {
        return numerator;
    }
    void setDenominator(int aDenominator)
    {
        denominator = aDenominator;
    }
    int getDenominator(void) const
    {
        return denominator;
    }
    
    int euclidean(int numeratorNum, int denominatorNum);
    void normalizeFraction(void);
    /*
     Overload all the following operators so that they correctly apply to the type Rational: ==, <, <=, >, >=, +, − (with two
     operands, not the unary -), *, and /
     */
    bool operator<(const Rational &lessNum);
    bool operator>(const Rational &greaterNum);
    bool operator<=(const Rational &lessEqual);
    bool operator>=(const Rational &greaterEqual);
    friend bool operator==(const Rational &aNum, const Rational &aDen);
    
    friend const Rational operator+(const Rational &aNum, const Rational &aDen);
    friend const Rational operator-(const Rational &aNum, const Rational &aDen);
    friend const Rational operator*(const Rational &aNum, const Rational &aDen);
    friend const Rational operator/(const Rational &aNum, const Rational &aDen);
    
    //Overload the input and output operators >> and <<
    friend ostream& operator<<(ostream &outStream , const Rational &num);
    friend istream& operator>>(istream &inStream , const Rational &num);
    
private:
    int numerator;
    int denominator;
};

bool operator==(const Rational &aNum, const Rational &aDen);
const Rational operator+(const Rational &aNum, const Rational &aDen);
const Rational operator-(const Rational &aNum, const Rational &aDen);
const Rational operator*(const Rational &aNum, const Rational &aDen);
const Rational operator/(const Rational &aNum, const Rational &aDen);
ostream& operator<<(ostream &outStream , const Rational &num);
istream& operator>>(istream &inStream , const Rational &num);

int main(int argc, const char * argv[])
{
    int userNumerator;
    int userDenominator;
    int testNum;
    int testDen;
    //test default constructor
    Rational defaultConst;
    cout << "Default Value: " << endl << defaultConst << endl;
    //test 1 parameter constructor:
    Rational obj(2);
    cout << "Whole number over 1: " << endl << obj << endl;
    //user entry
    cout << "Please enter a number for the numerator: ";
    cin >> userNumerator;
    cout << "Please enter a number for the denominator: ";
    cin >> userDenominator;
    //check if the denominator entered is 0. 0 is not allowed
    denominatorHelper(userDenominator);
    //object, new fraction
    //this constructor calls the normalize funtion
    Rational userRational(userNumerator, userDenominator);
    //second fraction
    cout << "First fraction entered: " << endl << userRational << endl;
  
    cout << "New fraction" << endl;
    cout << "Enter a numerator to compare: ";
    cin >> testNum;
    cout << "Enter a denominator to compare: ";
    cin >> testDen;
    //denominator cannot be = 0
    denominatorHelper(testDen);
    //new fraction
    Rational testEqual(testNum, testDen);
    cout << "Second fraction entered: " << endl << testEqual << endl;
    //check is greater than
    cout << endl << "Is " << userRational << " Greater or Less Than, Equal to, or Greater/Less or Equal to " << testEqual << "?" << endl << endl;
    
    //when fractions are equal (denominator and numerator
    if(userRational == testEqual)
    {
        cout << "Fractions Are Equal" << endl << endl;
    }
    else
    {
        cout << "Fractions Are Not equal" << endl << endl;
    }
    //if greater or greater or equal
    if(userRational >= testEqual)
    {
        cout << userRational << " The Fraction is Greater or Equal to " << testEqual << endl;
        
        if(userRational > testEqual)
        {
            cout << userRational << " The Fraction is Greater Than " << testEqual << endl;
        }
    }
    //when less than, or less or equal
    else if (userRational <= testEqual)
    {
        cout << userRational << " The Fraction is Less or Equal to " << testEqual << endl;
        
        if(userRational < testEqual)
        {
            cout << userRational << " The Fraction is Less Than " << testEqual << endl;
        }
    }
    

    //sum
    cout << endl << "Sum Fractions: " << endl;
    cout << userRational + testEqual << endl;
    //subtraction
    cout << endl << "Subtract Fractions:" << endl;
    cout << userRational - testEqual << endl;
    //multiplication
    cout << endl << "Multiply Fractions:" << endl;
    cout << userRational * testEqual << endl;
    //division
    cout << endl << "Divide Fractions:" << endl;
    cout << userRational / testEqual << endl;
    
    return 0;
}

//constructor
Rational::Rational(int aNumerator, int aDenominator)
{
    numerator = aNumerator;
    denominator = aDenominator;
    //normalize function will move the negative sign from the denominator to the numerator (given there is one) and reduce the fraction to its smallest form
    normalizeFraction();
}
//Hint: Two rational numbers a/b and c/d are equal if a*d equals c*b.
//equal
bool operator==(const Rational &aNum, const Rational &aDen)
{
    return ((aNum.getNumerator() * aDen.denominator) == (aNum.getDenominator() * aDen.numerator));
}

//If b and d are positive rational numbers, a/b is less than c/d provided a*d is less than c*b.
//less than
bool Rational::operator<(const Rational &lessNum)
{
    return ((getNumerator() * lessNum.denominator) < (getDenominator() * lessNum.numerator));
}
//less than c/d provided a*d is less than c*b.
//valid for <, >, >=, <=
//greater than
bool Rational::operator>(const Rational &greaterNum)
{
    return ((getNumerator() * greaterNum.denominator) > (getDenominator() * greaterNum.numerator));
}
//less or equal
bool Rational::operator<=(const Rational &lessEqual)
{
    return ((getNumerator() * lessEqual.denominator) <= (getDenominator() * lessEqual.numerator));;
}
//greater or equal
bool Rational::operator>=(const Rational &greaterEqual)
{
    return ((getNumerator() * greaterEqual.denominator) >= (getDenominator() * greaterEqual.numerator));;
}

/*
You should include a function to normalize the values stored so that,
 after normalization, the denominator is positive, and the numerator and denominator are as small as possible. For
 example, after normalization 4/-8 would be represented the same as −1/2. How to simplify 4/8 to 1/2? You may
 take a look at the Euclidean algorithm for computing the greatest common divisor of two numbers (search the
 web). Implement this function and the normalize function as helper functions (private functions) that your class
 can use when simplifying fractions.
 */
int Rational::euclidean(int gcd1, int gcd2)
{
    if(gcd1 == 0 || gcd2 == 0)
        return 1;
    if(gcd1 < 0)
        gcd1 = -1 * gcd1;
    if(gcd2 < 0)
        gcd2 = -1 * gcd2;

    while(gcd2 != 0)
    {
        int tempNum = gcd2;
        gcd2 = gcd1 % gcd2;
        gcd1 = tempNum;
    }
    return gcd1;
}

void Rational::normalizeFraction()
{
    if(numerator == 0)
    {
        denominator = 1;
    }
    else if(denominator < 0)
    {
        numerator = -1 * numerator;
        denominator = -1 * denominator;
    }
    
    int gcd = euclidean(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}
//addition
const Rational operator+(const Rational &aNum, const Rational &aDen)
{
    int updateNumerator = (aNum.numerator * aDen.denominator) + (aDen.numerator * aNum.denominator);
    
    int updateDenominator = aNum.denominator * aDen.denominator;
    
    Rational addNum(updateNumerator, updateDenominator);
    
    return addNum;
}

const Rational operator-(const Rational &aNum, const Rational &aDen)
{
    int updateNumerator = (aNum.numerator * aDen.denominator) - (aDen.numerator * aNum.denominator);
    
    int updateDenominator = aNum.denominator * aDen.denominator;
    
    Rational subNum(updateNumerator, updateDenominator);
    
    return subNum;
}

const Rational operator*(const Rational &aNum, const Rational &aDen)
{
    int updateNumerator = aNum.numerator * aDen.numerator;
    
    int updateDenominator = aNum.denominator * aDen.denominator;
    
    Rational multiNum(updateNumerator, updateDenominator);
    
    return multiNum;
}

const Rational operator/(const Rational &aNum, const Rational &aDen)
{
    
    int updateNumerator = aDen.denominator * aNum.numerator;
    
    int updateDenominator = aDen.numerator * aNum.denominator;
    
    Rational divideNum(updateNumerator, updateDenominator);
    
    return divideNum;
}

ostream& operator<<(ostream &outStream , const Rational &num)
{
    return outStream << num.numerator << "/" << num.denominator;
}

istream& operator>>(istream &inStream , const Rational &num)
{
    int aNumerator;
    int aDenominator;
    
    inStream >> aNumerator;
    inStream >> aDenominator;
    
    return inStream;
}

void denominatorHelper(int &userDenominator)
{
    while(userDenominator == 0)
    {
        cout << endl << "Error, denominator cannot be equal to 0. Please enter a number for the denominator: ";
        cin >> userDenominator;
    }
}
