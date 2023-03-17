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
    string binNum = clearBinNum;

    void BinaryModul(int input_num, string& output_num);
    string MakeAdditional(string binaryNum);
    string BinNumInverse(string binaryNum);
    string BinSum(string binaryNum1, string binaryNum2);
    string BinMin(string binaryNum1, string binaryNum2);
    vector <string> MakeMultVector(string binaryNum1, string binaryNum2);
    string BinDev(string num1, string num2);
    string FindRealNum(string num);
    bool MoreThan(string num1, string num2);
    string AddZeros(string realNum);

public:

    BinaryNum();
    BinaryNum(int input_num);
    float CalculateInTen();
    void ConsoleOutput();

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
void BinaryNum::BinaryModul(int input_num, string& output_num)
{
    int i = output_num.size() - 1;
    do
    {
        output_num[i] = char('0' + input_num % 2);
        input_num = input_num / 2;
        i--;
    } while (input_num > 0);
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
        {
            if (oneForNextDigit == 0)
            {
                binaryNum1[i] = '0';
                oneForNextDigit = 1;
            }
            else
            {
                binaryNum1[i] = '1';
                oneForNextDigit = 1;
            }  
        }
        else if ((binaryNum1[i] == '0' && binaryNum2[i] == '1') || (binaryNum1[i] == '1' && binaryNum2[i] == '0')) 
        {
            if (oneForNextDigit == 0)
                binaryNum1[i] = '1';
            else
                binaryNum1[i] = '0';
        }
        else if (binaryNum1[i] == '0' && binaryNum2[i] == '0') 
        {
            if (oneForNextDigit == 0)
                binaryNum1[i] = '0';
            else
            {
                oneForNextDigit = 0;
                binaryNum1[i] = '1';
            }
        }
    }
    return binaryNum1;
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
    string MinusZero = "1";
    for (int i = 1; i < output.size(); i++)
        MinusZero.push_back('0');
    if(output == MinusZero)
    {
        output = "";
        for (int i = 0; i < MinusZero.size(); i++)
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
        
        while ((!MoreThan(MinBuff, num2))&&(MinBuff.size() < num1.size()))
        {
            if (i < num1.size())
            {
                MinBuff.push_back(num1[i]);
                i++;
                if (addZeroToAnsw == true)
                    output.push_back('0');
                addZeroToAnsw = true;
                MinBuff = FindRealNum(MinBuff);
                bool isThereOnes = false;
                for(int k = i - 1; k < num1.size(); k++)
                    if (num1[k] == '1') 
                    { 
                        isThereOnes = true;
                        break;
                    }
                if (isThereOnes == 0)
                {
                    for (int k = i - 1; k < num1.size(); k++)
                    {
                        output.push_back('0');
                    }
                }
                if (MinBuff == "1" && num1.size() - i < num2.size() && num2 != "1")
                {
                    for (int k = i - 1; k < num1.size(); k++)
                    {
                        output.push_back('0');
                    }
                }
            }
            else
                break;
        }
        if (MoreThan(MinBuff, num2))
        {
            ;
            MinBuff = BinMin(AddZeros(MinBuff), AddZeros(num2));
            string MinBuff_plus_zero = MinBuff;
            MinBuff = FindRealNum(MinBuff);
            output.push_back('1');
            addZeroToAnsw = false;
        }
        else
            return output;
    }
    return string();
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
        output.binNum[0] == '1';

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

class BinaryFloatNum 
{
    string minus;
    string exp;
    string mantiss;
    const string clearMantiss = "00000000000000000000000"; //23
    const string exp127 = "01111111"; //8

    void SeparateParts(float DecNum, string &intPart, string &behindPoinPart);
    void MakeIntBinary(int input_num, string& output_num);
    void MakeBehindPointBinary(float input_num, string& output_num);
    string BinarySum(string binaryNum1, string binaryNum2);
    bool IsExpMore(string exp1, string exp2);
    void MoveNum(string &mantiss, int added);
    void MantiissEqualize(BinaryFloatNum &num1, BinaryFloatNum &num2);
    BinaryFloatNum MantissSum(BinaryFloatNum& num1, BinaryFloatNum& num2);
    string MakeAdditional(string binaryNum);
    string BinNumInverse(string binaryNum);
    float IntPartInFloat(string intPart);
    float BehindPointPartInFloat(string behindPointPart);

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
BinaryFloatNum::BinaryFloatNum(float input_num)
{
    this->exp = exp127;
    if (input_num < 0)
        this->minus = '1';
    else
        this->minus = '0';
    string intPart = clearMantiss;
    string beforePointPart = clearMantiss;
    SeparateParts(input_num, intPart, beforePointPart);
    cout << intPart << " " << beforePointPart << endl;
    int i = 0;
    if(intPart != this->clearMantiss)
    {
        while (intPart[i] == '0')
            i++;
        for (int j = i + 1; j < intPart.size(); j++)
        {
            this->mantiss.push_back(intPart[j]);
            this->exp = BinarySum("00000001", this->exp);
        }
        int mantissSize = this->mantiss.size();
        for(int j = 0; j < 23 - mantissSize; j++)
            this->mantiss.push_back(beforePointPart[j]);
        cout << this->minus << " " << this->exp << " " << this->mantiss << endl;
    }
    else 
    {
        while (beforePointPart[i] == '0'){
            i++;
            this->exp = BinarySum("11111111", this->exp);
        }
        this->exp = BinarySum("11111111", this->exp);
        for (int j = i + 1; j < beforePointPart.size(); j++)
            this->mantiss.push_back(beforePointPart[j]);
        for (int j = this->mantiss.size(); j < 23; j++)
        {
            this->mantiss.push_back('0');
        }

        cout << this->minus << " " << this->exp << " " << this->mantiss << endl;
    }
}

void BinaryFloatNum::SeparateParts(float DecNum, string& intPart, string& behindPoinPart)
{
    float DecIntPart;
    float DecBehindPoinPart = modf(DecNum, &DecIntPart);
    cout << DecBehindPoinPart << endl;
    MakeIntBinary(DecIntPart, intPart);
    MakeBehindPointBinary(DecBehindPoinPart, behindPoinPart);
}

void BinaryFloatNum::MakeIntBinary(int input_num, string& output_num)
{
    int i = output_num.size() - 1;
    do
    {
        output_num[i] = char('0' + input_num % 2);
        input_num = input_num / 2;
        i--;
    } while (input_num > 0);
}
void BinaryFloatNum::MakeBehindPointBinary(float input_num, string& output_num)
{
    if (input_num < 0)
        input_num *= -1;
    for (int i = 0; i < 23; i++)
    {
        input_num *= 2;
        if (input_num >= 1)
        {
            input_num -= 1;
            output_num[i] = '1';
        }
        else
            output_num[i] = '0';
    }
}
string BinaryFloatNum::BinarySum(string binaryNum1, string binaryNum2)
{
    bool oneForNextDigit = 0;
    for (int i = binaryNum1.size() - 1; i >= 0; i--)
    {
        if (binaryNum1[i] == '1' && binaryNum2[i] == '1')
        {
            if (oneForNextDigit == 0)
            {
                binaryNum1[i] = '0';
                oneForNextDigit = 1;
            }
            else
            {
                binaryNum1[i] = '1';
                oneForNextDigit = 1;
            }
        }
        else if ((binaryNum1[i] == '0' && binaryNum2[i] == '1') || (binaryNum1[i] == '1' && binaryNum2[i] == '0'))
        {
            if (oneForNextDigit == 0)
                binaryNum1[i] = '1';
            else
                binaryNum1[i] = '0';
        }
        else if (binaryNum1[i] == '0' && binaryNum2[i] == '0')
        {
            if (oneForNextDigit == 0)
                binaryNum1[i] = '0';
            else
            {
                oneForNextDigit = 0;
                binaryNum1[i] = '1';
            }
        }
    }
    return binaryNum1;
}

BinaryFloatNum BinaryFloatNum::operator+(const BinaryFloatNum& num)
{
    BinaryFloatNum num1;
    num1.minus = this->minus;
    num1.exp = this->exp;
    num1.mantiss = this->mantiss;
    BinaryFloatNum num2;
    num2.minus = num.minus;
    num2.exp = num.exp;
    num2.mantiss = num.mantiss;
    MantiissEqualize(num1,num2);
    MantissSum(num1, num2);
    

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
    num2.exp = BinarySum(num2.exp, "00000001");
    MoveNum(num2.mantiss, 1);
    num1.exp = BinarySum(num1.exp, "00000001");
    MoveNum(num1.mantiss, 1);
    if (IsExpMore(num1.exp, num2.exp))
    {
        while (IsExpMore(num1.exp, num2.exp))
        {
            num2.exp = BinarySum(num2.exp, "00000001");
            MoveNum(num2.mantiss, 0);
        }
    }
    else if (IsExpMore(num2.exp, num1.exp))
    {
        while (IsExpMore(num2.exp, num1.exp))
        {
            num1.exp = BinarySum(num1.exp, "00000001");
            MoveNum(num1.mantiss, 0);
        }
    }
}
BinaryFloatNum BinaryFloatNum::MantissSum(BinaryFloatNum& num1, BinaryFloatNum& num2)
{
    string num1MantissBuff = "00000000";
    string num2MantissBuff = "00000000";
    BinaryFloatNum output;
    for (int i = 0; i < num1.mantiss.size(); i++)
        num1MantissBuff.push_back(num1.mantiss[i]);
    for (int i = 0; i < num2.mantiss.size(); i++)
        num2MantissBuff.push_back(num2.mantiss[i]);
    if (num1.minus[0] == '1')
        num1MantissBuff = MakeAdditional(num1MantissBuff);
    if (num2.minus[0] == '1')
        num2MantissBuff = MakeAdditional(num2MantissBuff);

    num1MantissBuff = BinarySum(num1MantissBuff, num2MantissBuff);

    if(num1MantissBuff[0] = '1')
    {
        MakeAdditional(num1MantissBuff);
        output.minus = "1";
    }
    int capOfZeros = 1;
    while (num1MantissBuff[capOfZeros] == '0')
        capOfZeros++;
    if (capOfZeros < 8) 
    {
        for(int i = capOfZeros; i < 8; i++)
            BinarySum(num1.exp, "00000001");
    }
    if (capOfZeros > 8)
    {
        int i = 8;
        while (num1MantissBuff[i - 1] == '0') 
        {
            i++;
            BinarySum(num1.exp, "11111111");
        }
    }



    output.exp = num1.exp;
    output.mantiss = exp127;
    for (int i = capOfZeros - 1; i < 23 + capOfZeros; i++)
        output.mantiss.push_back(num1MantissBuff[i]);
    
    return output;
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
    //if (binaryNum[0] == '1')
    
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
    float output = 0;
    string intPart = "1";
    string behindPointPart = "";
    if (this->exp != this->exp127)
    {
        if (this->exp[0] == '0')
        {
            this->exp = BinarySum(this->exp, "00000001");
            while (this->exp != this->exp127)
            {
                this->exp = BinarySum(this->exp, "00000001");
                behindPointPart.push_back('0');
            }
            intPart = "0";
            behindPointPart = "1";
            for (int i = 0; i < this->mantiss.size(); i++)
                behindPointPart.push_back(this->mantiss[i]);

        }
        else if (this->exp[0] == '1')
        {
            int i = 0;
            while (this->exp != this->exp127)
            {
                this->exp = BinarySum(this->exp, "11111111");
                intPart.push_back(this->mantiss[i]);
                i++;
            }
            for(int j = i; j < this->mantiss.size(); j++)
                behindPointPart.push_back(this->mantiss[j]);
        }
    }
    cout << IntPartInFloat(intPart) << " " << BehindPointPartInFloat(behindPointPart)<<endl;
    output = IntPartInFloat(intPart) + BehindPointPartInFloat(behindPointPart);
    if (this->minus == "1")
        output *= -1;
    return output;
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
    float koeff = 1;
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
    BinaryNum num1(30);
    num1.ConsoleOutput();
    BinaryNum num2(-35);
    num2.ConsoleOutput();
    num1 = num1 + num2;
    num1.ConsoleOutput();

    BinaryFloatNum num3(0.625);
    BinaryFloatNum num4(0.625);
    num3 = num3 + num4;
    num3.ConsoleOutput();
    cout << num3.calcInDec() << endl;
}

