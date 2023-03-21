#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <vector>



using namespace std;

class BinaryNum 
{
    const string clearBinNum = "00000000";
    const string binOne = "00000001";
    const string minusZero = "10000000";
    string binNum = clearBinNum;

    void BinaryModul(int decNum, string& output);
    string MakeAdditional(string binaryNum);
    string BinNumInverse(string binaryNum);
    string BinSum(string binaryNum1, string binaryNum2);
    string BinMin(string binaryNum1, string binaryNum2);
    vector <string> MakeMultVector(string binaryNum1, string binaryNum2);
    string BinDev(string num1, string num2);
    string FindRealNum(string num);
    bool MoreThan(string num1, string num2);
    string AddZeros(string realNum);
    void SumOfTwoOnes(string& num1, string& num2, bool &oneForNextDigit, int index);
    void SumOfOneAndZero(string& num1, string& num2, bool &oneForNextDigit, int index);
    void SumOfTwoZeros(string& num1, string& num2, bool &oneForNextDigit, int index);
    void DevNumAdditing(string& num1, string &num2, string& minBuff, int& index, bool& addZeroToAnsw, string &output);
    void MinFromMinBuffer(string& num1, string& num2, string& minBuff, bool& addZeroToAnswer, string& output);

public:

    BinaryNum();
    BinaryNum(int input_num);
    float CalculateInTen();
    void ConsoleOutput();
    int calcInDec();

    BinaryNum operator + (const BinaryNum& num1);
    BinaryNum operator - (const BinaryNum& num1);
    BinaryNum operator * (const BinaryNum& num1);
    BinaryNum operator / (const BinaryNum& num1);
    void operator = (const BinaryNum& num1);


};

void BinaryNum::ConsoleOutput() 
{
    cout << this->binNum << endl;
}
void BinaryNum::BinaryModul(int decNum, string& output)
{
    int i = output.size() - 1;
    do
    {
        output[i] = char('0' + decNum % 2);
        decNum = decNum / 2;
        i--;
    } while (decNum > 0);
}
string BinaryNum::BinNumInverse(string binaryNum)
{
    for (int i = 1; i < binaryNum.size(); i++)
    {
        if (binaryNum[i] == '0')
            binaryNum[i] = '1';
        else if (binaryNum[i] == '1')
            binaryNum[i] = '0';
    }
    return binaryNum;
}
string BinaryNum::BinSum(string binaryNum1, string binaryNum2)
{
    bool oneForNextDigit = 0;
    for (int i = binaryNum1.size() - 1; i >= 0; i--) 
    {
        if (binaryNum1[i] == '1' && binaryNum2[i] == '1') 
            SumOfTwoOnes(binaryNum1, binaryNum2, oneForNextDigit, i);
        else if ((binaryNum1[i] == '0' && binaryNum2[i] == '1') || (binaryNum1[i] == '1' && binaryNum2[i] == '0')) 
            SumOfOneAndZero(binaryNum1, binaryNum2, oneForNextDigit, i);
        else if (binaryNum1[i] == '0' && binaryNum2[i] == '0') 
            SumOfTwoZeros(binaryNum1, binaryNum2, oneForNextDigit, i);
    }
    return binaryNum1;
}

void BinaryNum::SumOfTwoOnes(string& num1, string& num2, bool &oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
    {
        num1[index] = '0';
        oneForNextDigit = 1;
    }
    else
    {
        num1[index] = '1';
        oneForNextDigit = 1;
    }
}
void BinaryNum::SumOfOneAndZero(string& num1, string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
        num1[index] = '1';
    else
        num1[index] = '0';
}
void BinaryNum::SumOfTwoZeros(string& num1, string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
        num1[index] = '0';
    else
    {
        oneForNextDigit = 0;
        num1[index] = '1';
    }
}

string BinaryNum::BinMin(string binaryNum1, string binaryNum2)
{
    string output = "";
    string firstNumCopy = binaryNum1;
    string secondNumCopy = binaryNum2;
    if (secondNumCopy[0] == '1')
        secondNumCopy[0] = '0';
    else
        secondNumCopy[0] = '1';
    firstNumCopy = MakeAdditional(firstNumCopy);
    secondNumCopy = MakeAdditional(secondNumCopy);
    output = BinSum(firstNumCopy, secondNumCopy);
    output = MakeAdditional(output);
    if(output == minusZero)
    {
        output = "";
        for (int i = 0; i < minusZero.size(); i++)
            output.push_back('0');
    }
    return output;
}
string BinaryNum::BinDev(string num1, string num2)
{
    string output = "";
    num1 = FindRealNum(num1);
    num2 = FindRealNum(num2);
    int i = 0;
    string MinBuff = "";
    for (i = 0; i < num2.size(); i++)
        MinBuff.push_back(num1[i]);
    bool addZeroToAnsw = false;
    while(1)
    {       
        DevNumAdditing(num1, num2, MinBuff, i, addZeroToAnsw, output);
        if (MoreThan(MinBuff, num2))
            MinFromMinBuffer(num1, num2, MinBuff, addZeroToAnsw, output);
        else
            return output;
    }
    return string();
}
void BinaryNum::DevNumAdditing(string& num1, string& num2, string& minBuff, int& index, bool& addZeroToAnsw, string& output)
{
    while ((!MoreThan(minBuff, num2)) && (minBuff.size() < num1.size()))
    {
        if (index < num1.size())
        {
            minBuff.push_back(num1[index]);
            index++;
            if (addZeroToAnsw == true)
                output.push_back('0');
            addZeroToAnsw = true;
            minBuff = FindRealNum(minBuff);
            bool isThereOnes = false;
            for (int k = index - 1; k < num1.size(); k++)
                if (num1[k] == '1')
                {
                    isThereOnes = true;
                    break;
                }
            if (isThereOnes == 0)
                for (int k = index - 1; k < num1.size(); k++)
                    output.push_back('0');
            if (minBuff == "1" && num1.size() - index < num2.size() && num2 != "1")
                for (int k = index - 1; k < num1.size(); k++)
                    output.push_back('0');
        }
        else
            break;
    }
}
void BinaryNum::MinFromMinBuffer(string& num1, string& num2, string& minBuff, bool & addZeroToAnswer, string& output)
{
    minBuff = BinMin(AddZeros(minBuff), AddZeros(num2));
    string MinBuff_plus_zero = minBuff;
    minBuff = FindRealNum(minBuff);
    output.push_back('1');
    addZeroToAnswer = false;
}
bool BinaryNum::MoreThan(string num1, string num2)
{
    if (num1.size() > num2.size())
        return true;
    else if (num1.size() < num2.size())
        return false;
    else 
    {
        for (int i = 0; i < num1.size(); i++) 
        {
            if (num1[i] == '1' && num2[i] == '0')
                return true;
            if (num1[i] == '0' && num2[i] == '1')
                return false;
        }
    }
    return true;
}
string BinaryNum::FindRealNum(string num)
{
    string newString;
    int nullChacker = 0;
    while ((num[nullChacker] == '0') && (nullChacker < num.size()))
    {
        nullChacker++;
    }
    if (nullChacker == num.size())
        return "0";
    for (int i = nullChacker; i < num.size(); i++)
        newString.push_back(num[i]);
    return newString;
}
string BinaryNum::MakeAdditional(string binaryNum) 
{
    if (binaryNum[0] == '1')
    {
        binaryNum = BinNumInverse(binaryNum);
        binaryNum = BinSum(binaryNum, binOne);
    }
    return binaryNum;
}
vector<string> BinaryNum::MakeMultVector(string binaryNum1, string binaryNum2)
{
    vector <string> outputV;
    string buffer = "";
    for (int i = binaryNum2.size() - 1; i >= 1; i--) 
    {
        buffer = "";
        if (binaryNum2[i] == '1')
        {
            buffer.push_back('0');
            for (int j = 1 + (-i) + 7; j < binaryNum2.size(); j++)
            {
                buffer.push_back(binaryNum1[j]);
            }
            for (int j = 0; j < (-i) + 7; j++)
                buffer.push_back('0');
        }
        else if (binaryNum2[i] == '0')
            buffer = clearBinNum;
        outputV.push_back(buffer);
    }
    return outputV;
}
BinaryNum::BinaryNum() 
{

}
BinaryNum::BinaryNum(int Num)
{
    bool minus = false;
    if (Num < 0)
    {
        Num *= -1;
        minus = true;
    }
    BinaryModul(Num, this->binNum);
    if (minus == true)
        this->binNum[0] = '1';
}
void BinaryNum::operator=(const BinaryNum& num) 
{
    this->binNum = num.binNum;
}
BinaryNum BinaryNum::operator+(const BinaryNum& num)
{
    BinaryNum output;
    string firstNumCopy = this->binNum;
    string secondNumCopy = num.binNum;
    firstNumCopy = MakeAdditional(firstNumCopy);
    secondNumCopy = MakeAdditional(secondNumCopy);
    output.binNum = BinSum(firstNumCopy, secondNumCopy);
    output.binNum = MakeAdditional(output.binNum);
    return output;
}
BinaryNum BinaryNum::operator-(const BinaryNum& num)
{
    BinaryNum output;
    output.binNum = BinMin(this->binNum, num.binNum);
    return output;
}
BinaryNum BinaryNum::operator*(const BinaryNum& num) 
{
    
    vector<string> vectOfIntermidValue;
    vectOfIntermidValue = MakeMultVector(this->binNum, num.binNum);
    for (int i = 1; i < vectOfIntermidValue.size(); i++)
        vectOfIntermidValue[0] = BinSum(vectOfIntermidValue[0], vectOfIntermidValue[i]);
    BinaryNum outNum;
    outNum.binNum = vectOfIntermidValue[0];
    if ((this->binNum[0] == '0' && num.binNum[0] == '1') || (this->binNum[0] == '1' && num.binNum[0] == '0'))
        outNum.binNum[0] = '1';
    return outNum;
}
BinaryNum BinaryNum::operator/(const BinaryNum& num) 
{
    string num1 = this->binNum;
    string num2 = num.binNum;

    string num1_no_minus = "";
    string num2_no_minus = "";

    for (int i = 1; i < num1.size(); i++) 
    {
        num1_no_minus.push_back(num1[i]);
        num2_no_minus.push_back(num2[i]);
    }
    BinaryNum output; 
    output.binNum = BinDev(num1_no_minus, num2_no_minus);
    output.binNum = AddZeros(output.binNum);
    if ((num1[0] == '1' && num2[0] == '0') || (num1[0] == '0' && num2[0] == '1'))
        output.binNum[0] = '1';

    return output;
}
string BinaryNum::AddZeros(string realNum)
{
    do 
    {
        realNum = '0' + realNum;
    } while (realNum.size() < 8);
    return realNum;
}
int BinaryNum::calcInDec()
{
    float koeff = 1;
    float buffer = 0;
    float output = 0;
    for (int i = this->binNum.size() - 1; i > 0; i--)
    {
        buffer = this->binNum[i] - '0';
        output += buffer * koeff;
        koeff *= 2;
    }
    if (this->binNum[0] == '1')
        output *= -1;
    return output;
}



///////////////////////////////////////////////////////////////////


class BinaryFloatNum 
{
    string minus;
    string exp;
    string mantiss;
    const string clearMantiss = "00000000000000000000000"; //23
    const string exp127 = "01111111"; //8
    const string clearExp = "00000000";
    const string binOne = "00000001";
    const string binMinusOne = "11111111";

    void SeparateParts(float decNum, string &intPart, string &behindPoinPart);
    void MakeIntBinary(int decNum, string& output);
    void MakeBehindPointBinary(float DecNum, string& output);
    string BinarySum(string binaryNum1, string binaryNum2);
    bool IsExpMore(string exp1, string exp2);
    void MoveNum(string &mantiss, int added);
    void MantiissEqualize(BinaryFloatNum &num1, BinaryFloatNum &num2);
    BinaryFloatNum MantissSum(BinaryFloatNum& num1, BinaryFloatNum& num2);
    string MakeAdditional(string binaryNum);
    string BinNumInverse(string binaryNum);
    float IntPartInFloat(string intPart);
    float BehindPointPartInFloat(string behindPointPart);
    void FillByNumWithIntPart(string &intPart, string &behindPointPart, int &index);
    void FillByNumWhithNoIntPart(string& intPart, string& behindPointPart, int& index);
    void SumOfTwoOnes(string& num1, string& num2, bool& oneForNextDigit, int index);
    void SumOfOneAndZero(string& num1, string& num2, bool& oneForNextDigit, int index);
    void SumOfTwoZeros(string& num1, string& num2, bool& oneForNextDigit, int index);
    void ConvertToStandartFormat(string& num1MantissBuff, BinaryFloatNum& num1, BinaryFloatNum& output);
    void MultByExpWithNegativeDegree(BinaryFloatNum& copyOfMainNum, string& intPart, string& behindPointPart);
    void MultByExpWithPositiveDegree(BinaryFloatNum& copyOfMainNum, string& intPart, string& behindPointPart);

public:
    BinaryFloatNum();
    BinaryFloatNum(float input_num);

    BinaryFloatNum operator+(const BinaryFloatNum& num1);
    void operator=(const BinaryFloatNum& num1);
    void ConsoleOutput();
    float calcInDec();

};

BinaryFloatNum::BinaryFloatNum()
{
    this->minus = '0';
    this->exp = this->exp127;
    this->mantiss = this->clearMantiss;
}
BinaryFloatNum::BinaryFloatNum(float decNum)
{
    this->exp = exp127;
    if (decNum < 0)
    {
        this->minus = '1';
        decNum *= -1;
    }
    else
        this->minus = '0';
    string intPart = clearMantiss;
    string behindPointPart = clearMantiss;
    SeparateParts(decNum, intPart, behindPointPart);
    int i = 0;
    if(intPart != this->clearMantiss)
        FillByNumWithIntPart(intPart, behindPointPart, i);
    else 
        FillByNumWhithNoIntPart(intPart, behindPointPart, i);
}
void BinaryFloatNum::FillByNumWithIntPart(string &intPart, string &behindPointPart, int &index)
{
    while (intPart[index] == '0')
        index++;
    for (int j = index + 1; j < intPart.size(); j++)
    {
        this->mantiss.push_back(intPart[j]);
        this->exp = BinarySum(binOne, this->exp);
    }
    int mantissSize = this->mantiss.size();
    for (int j = 0; j < 23 - mantissSize; j++)
        this->mantiss.push_back(behindPointPart[j]);
}
void BinaryFloatNum::FillByNumWhithNoIntPart(string& intPart, string& behindPointPart, int& index)
{
    while (behindPointPart[index] == '0') {
        index++;
        this->exp = BinarySum(binMinusOne, this->exp);
    }
    this->exp = BinarySum(binMinusOne, this->exp);
    for (int j = index + 1; j < behindPointPart.size(); j++)
        this->mantiss.push_back(behindPointPart[j]);
    for (int j = this->mantiss.size(); j < 23; j++)
    {
        this->mantiss.push_back('0');
    }
}

void BinaryFloatNum::SeparateParts(float decNum, string& intPart, string& behindPoinPart)
{
    float DecIntPart;
    float DecBehindPoinPart = modf(decNum, &DecIntPart);
    MakeIntBinary(DecIntPart, intPart);
    MakeBehindPointBinary(DecBehindPoinPart, behindPoinPart);
}

void BinaryFloatNum::MakeIntBinary(int decNum, string& output)
{
    int i = output.size() - 1;
    do
    {
        output[i] = char('0' + decNum % 2);
        decNum = decNum / 2;
        i--;
    } while (decNum > 0);
}
void BinaryFloatNum::MakeBehindPointBinary(float numLowerThanOne, string& output)
{
    if (numLowerThanOne < 0)
        numLowerThanOne *= -1;
    for (int i = 0; i < 23; i++)
    {
        numLowerThanOne *= 2;
        if (numLowerThanOne >= 1)
        {
            numLowerThanOne -= 1;
            output[i] = '1';
        }
        else
            output[i] = '0';
    }
}

string BinaryFloatNum::BinarySum(string binaryNum1, string binaryNum2)
{
    bool oneForNextDigit = 0;
    for (int i = binaryNum1.size() - 1; i >= 0; i--)
    {
        if (binaryNum1[i] == '1' && binaryNum2[i] == '1')
            SumOfTwoOnes(binaryNum1, binaryNum2, oneForNextDigit, i);
        else if ((binaryNum1[i] == '0' && binaryNum2[i] == '1') || (binaryNum1[i] == '1' && binaryNum2[i] == '0'))
            SumOfOneAndZero(binaryNum1, binaryNum2, oneForNextDigit, i);
        else if (binaryNum1[i] == '0' && binaryNum2[i] == '0')
            SumOfTwoZeros(binaryNum1, binaryNum2, oneForNextDigit, i);
    }
    return binaryNum1;
}
void BinaryFloatNum::SumOfTwoOnes(string& num1, string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
    {
        num1[index] = '0';
        oneForNextDigit = 1;
    }
    else
    {
        num1[index] = '1';
        oneForNextDigit = 1;
    }
}
void BinaryFloatNum::SumOfOneAndZero(string& num1, string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
        num1[index] = '1';
    else
        num1[index] = '0';
}
void BinaryFloatNum::SumOfTwoZeros(string& num1, string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
        num1[index] = '0';
    else
    {
        oneForNextDigit = 0;
        num1[index] = '1';
    }
}

BinaryFloatNum BinaryFloatNum::operator+(const BinaryFloatNum& num)
{
    BinaryFloatNum num1;
    num1.minus = this->minus;
    num1.exp = this->exp;
    num1.mantiss = this->mantiss;
    BinaryFloatNum num2 = num;
    MantiissEqualize(num1,num2);
    num1 = MantissSum(num1, num2);
    
    return num1;
}
bool BinaryFloatNum::IsExpMore(string exp1, string exp2)
{
    for (int i = 0; i < exp1.size(); i++) 
    {
        if (exp1[i] == '1' && exp2[i] == '0')
            return true;
        if (exp1[i] == '0' && exp2[i] == '1')
            return false;
    }
    return false;
}
void BinaryFloatNum::MoveNum(string &mantiss, int added)
{
    string buffer = "";
    if(added == 1)
        buffer.push_back('1');
    else if((added == 0))
        buffer.push_back('0');
    for (int i = 0; i < mantiss.size() - 1; i++)
        buffer.push_back(mantiss[i]);
    mantiss = buffer;
}
void BinaryFloatNum::MantiissEqualize(BinaryFloatNum& num1, BinaryFloatNum &num2)
{
    num2.exp = BinarySum(num2.exp, binOne);
    MoveNum(num2.mantiss, 1);
    num1.exp = BinarySum(num1.exp, binOne);
    MoveNum(num1.mantiss, 1);
    if (IsExpMore(num1.exp, num2.exp))
    {
        while (IsExpMore(num1.exp, num2.exp))
        {
            num2.exp = BinarySum(num2.exp, binOne);
            MoveNum(num2.mantiss, 0);
        }
    }
    else if (IsExpMore(num2.exp, num1.exp))
    {
        while (IsExpMore(num2.exp, num1.exp))
        {
            num1.exp = BinarySum(num1.exp, binOne);
            MoveNum(num1.mantiss, 0);
        }
    }
}
BinaryFloatNum BinaryFloatNum::MantissSum(BinaryFloatNum& num1, BinaryFloatNum& num2)
{
    string num1MantissBuff = clearExp;
    string num2MantissBuff = clearExp;
    BinaryFloatNum output;
    for (int i = 0; i < num1.mantiss.size(); i++)
        num1MantissBuff.push_back(num1.mantiss[i]);
    for (int i = 0; i < num2.mantiss.size(); i++)
        num2MantissBuff.push_back(num2.mantiss[i]);
    if (num1.minus == "1")
        num1MantissBuff = MakeAdditional(num1MantissBuff);
    if (num2.minus == "1")
        num2MantissBuff = MakeAdditional(num2MantissBuff);

    num1MantissBuff = BinarySum(num1MantissBuff, num2MantissBuff);

    if(num1MantissBuff[0] == '1')
    {
        num1MantissBuff = MakeAdditional(num1MantissBuff);
        output.minus = "1";
    }
    ConvertToStandartFormat(num1MantissBuff, num1, output);
    return output;
}
void BinaryFloatNum::ConvertToStandartFormat(string &num1MantissBuff, BinaryFloatNum &num1, BinaryFloatNum &output)
{
    int capOfZeros = 1;
    while (num1MantissBuff[capOfZeros] == '0')
        capOfZeros++;
    if (capOfZeros < 7)
    {
        for (int i = capOfZeros; i < 8; i++)
            BinarySum(num1.exp, binOne);
    }
    if (capOfZeros > 7)
    {
        int i = 7;
        while (num1MantissBuff[i] == '0')
        {
            i++;
            num1.exp = BinarySum(num1.exp, binMinusOne);
        }
    }
    output.exp = num1.exp;
    output.mantiss = "";
    for (int i = capOfZeros + 1; i < 23 + capOfZeros; i++)
        output.mantiss.push_back(num1MantissBuff[i]);
}

void BinaryFloatNum::operator=(const BinaryFloatNum& num1)
{
    this->minus = num1.minus;
    this->exp = num1.exp;
    this->mantiss = num1.mantiss;
}
string BinaryFloatNum::MakeAdditional(string binaryNum)
{
    string binOne = "";
    binOne.push_back('1');
    for(int i = 1; i < binaryNum.size(); i++)
        binOne.push_back('0');
    
        binaryNum = BinNumInverse(binaryNum);
        binaryNum = BinarySum(binaryNum, binOne);
    
    return binaryNum;
}
string BinaryFloatNum::BinNumInverse(string binaryNum)
{
    for (int i = 1; i < binaryNum.size(); i++)
    {
        if (binaryNum[i] == '0')
            binaryNum[i] = '1';
        else if (binaryNum[i] == '1')
            binaryNum[i] = '0';
    }
    return binaryNum;
}

void BinaryFloatNum::ConsoleOutput()
{
    cout << this->minus << " " << this->exp << " " << this->mantiss << endl;
}

float BinaryFloatNum::calcInDec()
{
    BinaryFloatNum copyOfMainNum;
    copyOfMainNum.minus = this->minus;
    copyOfMainNum.exp = this->exp;
    copyOfMainNum.mantiss = this->mantiss;
    float output = 0;
    string intPart = "1";
    string behindPointPart = "";
    if (copyOfMainNum.exp != this->exp127)
    {
        if (copyOfMainNum.exp[0] == '0')
            MultByExpWithNegativeDegree(copyOfMainNum, intPart, behindPointPart);
        else if (copyOfMainNum.exp[0] == '1')
            MultByExpWithPositiveDegree(copyOfMainNum, intPart, behindPointPart);
    }
    else
        for (int i = 0; i < copyOfMainNum.mantiss.size(); i++)
            behindPointPart.push_back(copyOfMainNum.mantiss[i]);
    output = IntPartInFloat(intPart) + BehindPointPartInFloat(behindPointPart);
    if (this->minus == "1")
        output *= -1;
    return output;
}
void BinaryFloatNum::MultByExpWithNegativeDegree(BinaryFloatNum &copyOfMainNum, string &intPart, string &behindPointPart)
{
    copyOfMainNum.exp = BinarySum(copyOfMainNum.exp, binOne);
    while (copyOfMainNum.exp != this->exp127)
    {
        copyOfMainNum.exp = BinarySum(copyOfMainNum.exp, binMinusOne);
        behindPointPart.push_back('0');
    }
    intPart = "0";
    behindPointPart.push_back('1');
    for (int i = 0; i < copyOfMainNum.mantiss.size(); i++)
        behindPointPart.push_back(copyOfMainNum.mantiss[i]);
}
void BinaryFloatNum::MultByExpWithPositiveDegree(BinaryFloatNum& copyOfMainNum, string& intPart, string& behindPointPart)
{
    int i = 0;
    while (copyOfMainNum.exp != this->exp127)
    {
        copyOfMainNum.exp = BinarySum(copyOfMainNum.exp, binMinusOne);
        intPart.push_back(copyOfMainNum.mantiss[i]);
        i++;
    }
    for (int j = i; j < copyOfMainNum.mantiss.size(); j++)
        behindPointPart.push_back(copyOfMainNum.mantiss[j]);
}
float BinaryFloatNum::IntPartInFloat(string intPart)
{
    float koeff = 1;
    float buffer = 0;
    float output = 0;
    for (int i = intPart.size() - 1; i >= 0; i--)
    {
        buffer = intPart[i] - '0';
        output += buffer * koeff;
        koeff *= 2;
    }
    return output;
}

float BinaryFloatNum::BehindPointPartInFloat(string behindPointPart)
{
    float koeff = 0.5;
    float buffer = 0;
    float output = 0;
    for (int i = 0; i < behindPointPart.size(); i++)
    {
        buffer = behindPointPart[i] - '0';
        output += buffer * koeff;
        koeff *= 0.5;
    }
    return output;
}

int main()
{
    cout << "-------------<Tests>-------------" << endl;
    cout << "Input first int num:" << endl;
    int intNum1 = 0, intNum2 = 0;
    cin >> intNum1;
    BinaryNum num1(intNum1);
    cout << "Binary form:" << endl;
    num1.ConsoleOutput();
    cout << endl;
    cout << "Input second int num:" << endl;
    cin >> intNum2;
    BinaryNum num2(intNum2);
    cout << "Binary form:" << endl;
    num2.ConsoleOutput();
    
    cout << "---------------------------------" << endl;
    cout << endl;
    cout <<"          " << "Sum:" << endl;
    
    BinaryNum output;
    output = num1 + num2;
    output.ConsoleOutput();
    cout << intNum1 << " + " << intNum2 << " = " << output.calcInDec()<< endl;
    
    cout << "          " << "Diff:" << endl;
    output = num1 - num2;
    output.ConsoleOutput();
    cout << intNum1 << " - " << intNum2 << " = " << output.calcInDec() << endl;

    cout << "          " << "Mult:" << endl;
    output = num1 * num2;
    output.ConsoleOutput();
    cout << intNum1 << " * " << intNum2 << " = " << output.calcInDec() << endl;

    cout << "          " << "Dev:" << endl;
    output = num1 / num2;
    output.ConsoleOutput();
    cout << intNum1 << " / " << intNum2 << " = " << output.calcInDec() << endl;
    
    cout << "---------------------------------" << endl;

    cout << "Input first float num:" << endl;
    float floatNum1 = 0, floatNum2 = 0;
    cin >> floatNum1;
    BinaryFloatNum num1F(floatNum1);
    cout << "Binary form:" << endl;
    num1F.ConsoleOutput();
    cout << endl;
    cout << "Input second int num:" << endl;
    cin >> floatNum2;
    BinaryFloatNum num2F(floatNum2);
    cout << "Binary form:" << endl;
    num2F.ConsoleOutput();

    cout << "---------------------------------" << endl;

    cout << "Sum:" << endl;

    BinaryFloatNum outputF;
    outputF = num1F + num2F;
    outputF.ConsoleOutput();
    cout << floatNum1 << " + " << floatNum2 << " = " << outputF.calcInDec() << endl;


}

