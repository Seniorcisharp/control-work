#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int binaryToDecimal(string);
int calculateSum(string);
int calculateSumFromFile(string);
void calculateSumTest(string);

int main()
{
    calculateSumTest("test.txt");
}

int calculateSum(string source)
{
    int sum = 0;
    string currentBinary = "";

    for (char ch : source)
    {
        if (ch == '0' || ch == '1') {
            currentBinary += ch;
        }
        else {
            if (!currentBinary.empty()) {
                sum += binaryToDecimal(currentBinary);
                currentBinary = "";
            }
        }
    }

    if (!currentBinary.empty()) {
        sum += binaryToDecimal(currentBinary);
    }

    return sum;
}


int calculateSumFromFile(string fileName)
{
    {
        ifstream inFile(fileName);
        if (!inFile.is_open()) {
            throw runtime_error("Stream does not open");
        }

        string line;
        int totalSum = 0;
        while (getline(inFile, line)) {
            totalSum += calculateSum(line);
        }

        inFile.close();
        return totalSum;
    }
}

int binaryToDecimal(string binary)
{
    int decimal = 0;
    int power = 0;

    for (int i = binary.length() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += pow(2, power);
        }
        power++;
    }

    return decimal;
}

void calculateSumTest(string fileName)
{
	bool result = calculateSum("1+-0100+*** 1000") == 13;
	cout << "Test for parsing " << (result ? "Passed." : "Failed.") << endl;
	result = calculateSum("1000001+-1000+* 100** 1--- 0000001") == 79;
	cout << "Test for parsing " << (result ? "Passed." : "Failed.") << endl;
	result = calculateSum("10000000000011111+11+*** 1111000111") == 66537;
	cout << "Test for parsing " << (result ? "Passed." : "Failed.") << endl;
	result = calculateSum("1111111111111000011111+-11111111111+*   1111** -22--- ") == 4195885;
	cout << "Test for parsing " << (result ? "Passed." : "Failed.") << endl;
	result = calculateSumFromFile(fileName) == 4262515;
	cout << "Test for parsing " << (result ? "Passed." : "Failed.") << endl;
}