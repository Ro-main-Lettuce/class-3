#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
/* Rosalyn Navarrete
 * rdn0011
 * project1_Navarrete_rdn0011.cpp
 * to compile the code, the following:
 * g++ project1_Navarrete_rdn0011.cpp -o testPUno
 * to test the code, the following:
 * ./testPUno
 * enter values of the first case (1000,18,50), second case (2000,12,80)
 * getbrightup.com to get the formula for monthly calculation
 * exit() being explained by TA Weekaroon
 * James S.Plank online notes for cin.fail()
 */
int main() {
    // sets the numbers to be read with a decimal, from Ch.1 of C++ textbook
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    // variables that require user input.
    double loanAmount, interestRate, monthly;
    // variables to be used for calculating the time to pay the loan.
    double iRateMon, durationMonth, totalInterest = 0, totalT;
    // reads in the loan amount
    cout << "Loan Amount: ";
    // Takes user input for loan amount and to a variable
    cin >> loanAmount;
    // Test case of Invalid inputs of negative values and non-numerical values for loan amount
    // cin.fail sees if cinn >> loanAmount fails, if the entered value not match the wanted variable type
    if(cin.fail()|| loanAmount < 0){
        cerr << "Invalid loan\n";
        exit(1);
    }
    // Takes in user input of Interest rate
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;
    // Test case of Invalid inputs of negative values and non-numerical values for interest rates
    if(cin.fail() || interestRate < 0){
        cerr << "Invalid interest rate\n";
        exit(1);
    }
    // Takes in user input of Monthly payment
    cout << "Monthly Payments: ";
    cin >> monthly;
    // Test case of non-numerical inputs and negative inputs.
    if(cin.fail() || monthly < 0){
        cerr << "Invalid interest rate\n";
        exit(1);
    }

    // Finds the interest rate for the month in decimal form
    iRateMon = interestRate / 1200;
    // Test case of Invalid inputs of negative values and non-numerical values for monthly1 payment

    // Test case of monthly being less than or equal to the principal amount
    if(monthly <= (iRateMon * loanAmount)){
        cerr << "Insufficient payment\n";
        exit(0);
    }
    // the header of the Amortization Table
    cout << "**********************************************************\n"
         << "\tAmortization Table\n"
         << "**********************************************************\n"
         << "Month   Balance   Payment      Rate   Interest   Principal\n";

    // the eqn for finding the months to pay the loan. Credit to getbrightup for the equation
    durationMonth = -(log(1-(loanAmount * iRateMon)/monthly))/log(1+iRateMon);
    // case of 0 interest rate
    if(interestRate == 0){
        durationMonth = loanAmount / monthly;
    }
    // to round up the months to pay
    durationMonth = durationMonth + 0.5;
    // casts the month into integer
    int month = static_cast<int>(durationMonth);
    // the first row of the table
    cout << "0       $"<< loanAmount << "  N/A          N/A    N/A        N/A\n";
    int counter;
    //principal = monthly - (iRateMon * loanAmount);
    //interest = (iRateMon * loanAmount);
    //for loop goes until the counter is equal to the calculated month
    for (counter = 1; counter <= month; counter++){
        // totalT = loan balance
        totalT = loanAmount - (monthly - (iRateMon * loanAmount));
        // case if balance is negative after charge
        if(totalT < 0){
            totalT = 0;
        }
        // format if balance is over 1000
        if(totalT > 1000){
            cout << counter
                 <<"\t$" << totalT
                 <<"  $" << monthly
                 <<"       "<<  iRateMon * 100
                 <<"  $"<< (iRateMon * loanAmount)
                 <<"\t $"<< monthly - (iRateMon * loanAmount) << endl;
        }
        // format for balance under 1000
        else {
            cout << counter
                 << "\t$" << totalT
                 << "\t  $" << monthly
                 << "       " << iRateMon * 100
                 << "  $" << (iRateMon * loanAmount)
                 << "\t $" << monthly - (iRateMon * loanAmount) << endl;
        }
        // Each iteration adds to the total interest
        totalInterest = totalInterest + (iRateMon * loanAmount);
        // loan Amount updated after each iteration
        loanAmount = loanAmount - (monthly - (iRateMon * loanAmount));
        // precaution for the last payment. The balance less than the payment.
        if(totalT < monthly){
            monthly = loanAmount + (iRateMon * loanAmount);
        }

    }
    // Closing output of month calculation and total interest CASE of single month
    if(month > 1) {
        cout << "**********************************************************\n"
             << "It takes " << month << " months to pay off this loan.\n"
             << "Total interest paid off is: $" << totalInterest << endl;
    }
    // Closing output of month calculation and total interest CASE of MONTHS
    else{
        cout << "**********************************************************\n"
             << "It takes " << month << " month to pay off this loan.\n"
             << "Total interest paid off is: $" << totalInterest << endl;

    }

    return 0;
}
