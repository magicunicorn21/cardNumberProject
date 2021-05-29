#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

//Luhn algorithm implementation
bool validCheck(string cardNumber) {
    int sum = 0;
    //starts at the second rightmost digit and continues to the left (every other digit)
    for (int i = cardNumber.length() - 2; i >= 0; i -= 2) {
        //gets the digit as a number
        int doubledDigit = cardNumber.at(i) - '0';
        //doubles the digit
        doubledDigit = doubledDigit * 2;
        //checks if the multiplication is greater than 9
        if (doubledDigit > 9)
            //calculates the sum of multiplication's digits
            doubledDigit = doubledDigit % 10 + doubledDigit / 10;
        //computes the sum gardually
        sum += doubledDigit;
        //checks if there are undoubled digits left and adds the next one to the sum
        if ((i - 1) >= 0)
            sum += cardNumber.at(i - 1) - '0';
    }
    //adds the last digit of the card number to the sum
    sum += cardNumber.back() - '0';
    //checks if sum is divisiblle with 10
    if (sum % 10 == 0)
        return true;
    return false;
}


int main()
{
    string inFileName = "test.in";
    string outFileName = "test.out";
    //input file
    ifstream inFile(inFileName);
    //output file
    ofstream outFile(outFileName);
    //valid card numbers vector
    vector<string> cardNumbers;

    if (inFile.is_open()) {
        string line;
        //pattern to recognize card numbers starting with 4 and having either 13, 16 or 19 digits
        //pattern takes the character in front and after the number for making sure there is no numbers before of after the pattern (the card number would be invalid)
        regex pattern("((\\D|^)4[0-9]{18}(\\D|$))|((\\D|^)4[0-9]{15}(\\D|$))|((\\D|^)4[0-9]{12}(\\D|$))");
        while (getline(inFile, line)) {
            //removing white spaces from line read
            line = regex_replace(line, std::regex("\\s+"), "");
            smatch m;
            //searches for the pattern in line
            while (regex_search(line, m, pattern)) {
                //found card number
                string cardNo = m[0];
                //removing all non-digit characters from the card number
                cardNo = regex_replace(cardNo, std::regex("\\D"), "");
                //check if card number is valid with Luhn algorithm
                if (validCheck(cardNo))
                    //add valid card number to card numbers verctor
                    cardNumbers.push_back(cardNo);
                //removes the beginning of the line for the algorithm to continue with the pattern recognition after the currently found card number
                line = m.suffix().str();
            }
        }
        inFile.close();
    }
    else
        cout << "Unable to open in file" << endl;

    //writes the valid card numbers in the output file
    if (outFile.is_open()) {
        for (string cardNo : cardNumbers)
            outFile << cardNo << endl;
        outFile.close();
    }
    else
        cout << "Unable to open out file";

    return 0;
}

