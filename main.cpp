#include <iostream>
#include <iomanip>
#include <string>

// Add this line to avoid repeating std::
using namespace std;


// Function to validate and extract a numeric value
double extractNumeric(const string& str) {
    bool hasDecimal = false;
    bool hasSign = false;
    bool isValid = true;
    int digitCount = 0;

    for (size_t i = 0; i < str.length(); ++i) {
        char ch = str[i];

        // Check for sign (+ or -) at the start of the string
        if ((ch == '+' || ch == '-') && i == 0) {
            hasSign = true;
        }
        // Allow digits
        else if (ch >= '0' && ch <= '9') {
            digitCount++;
        }
        // Allow a single period (.)
        else if (ch == '.' && !hasDecimal) {
            hasDecimal = true;
        }
        // Any other character makes the input invalid
        else {
            isValid = false;
            break;
        }
    }

    // Input is invalid if it contains no digits or has a trailing decimal
    if (digitCount == 0 || (!isValid) || (str.back() == '.')) {
        return -999999.99;
    }

    // Convert the string to a double without using std::stod
    double result = 0.0;
    double decimalMultiplier = 0.1;
    bool isNegative = (str[0] == '-');
    bool inDecimalPart = false;

    for (char ch : str) {
        if (ch == '+' || ch == '-') {
            continue; // Skip the sign character
        }
        if (ch == '.') {
            inDecimalPart = true;
            continue;
        }
        if (inDecimalPart) {
            result += (ch - '0') * decimalMultiplier;
            decimalMultiplier /= 10;
        } else {
            result = result * 10 + (ch - '0');
        }
    }

    // Apply the negative sign if needed
    if (isNegative) {
        result = -result;
    }

    return result;
}




int main () {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric (input);

        if (number != -999999.99) {
            cout << "The input is: "<< fixed << setprecision (4)
                << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }
    
    return 0;
}