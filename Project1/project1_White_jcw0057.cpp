/* AUTHOR: Jonathan White
 * USER ID: jcw0057
 * FILE NAME: project1_White_jcw0057.cpp
 * Compile program => g++ project1_White_jcw0057.cpp
 * Run program => ./a.out
 */

#include <iostream>

using namespace std;

int   main() {
    // VARIABLE INITIALIZATION Properly define your variables........ .......................

    float loan = 0; // Starting Balance
    float interestRate = 0; // User input interest rate yearly => converted to monthly in program
    float interestRateC = 0; // Divided down to give a percentage
    float interestPayment = 0;
    float monthlyPaid = 0; // Monthly payment amount
    int currentMonth = 0;
    int totalMonths = 0;
    float interestTotal = 0; // Total Amount of interest compounded
    float balance = 0; // Moving balance that way I don't change the initial loan amount and could always be accessed.

    // CURRENCY FORMATTING
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // USER INPUT
    // NOTE: For valid input, the loan, interest, and monthly payment must
    // be positive. The monthly payment must also be large enough to
    // terminate the loan.
    cout << "\nLoan Amount: ";
    cin >>  loan;
    if (loan <= 0) {
        cout << "\nPlease enter a positive number: ";
        cin >> loan;
    }
    balance = loan; // sets balance so it can be changed

    cout << "Interest Rate (% per year): ";
    cin >>  interestRate;
    if (interestRate <= 0) {
        cout << "\nPlease enter a positive number: ";
        cin >> interestRate;
    }

    // GET PROPER INTEREST RATES FOR CALCULATIONS
    interestRate /= 12; // Converts to monthly interest
    interestRateC = interestRate / 100; // Converts from percent to value

    interestPayment = interestRateC * balance; // Checks interest payment needed first month
    cout << "Monthly Payments: ";
    cin >>  monthlyPaid;

    if (monthlyPaid < interestPayment) {
        cout << "\nPlease enter a payment that is larger than $" << interestPayment << ": ";
        cin >> monthlyPaid;
    }

    cout << endl;

    // AMORTIZATION TABLE
    cout << "*****************************************************************\n"
         << "\tAmortization Table\n"
         << "*****************************************************************\n"
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
    // LOOP TO FILL TABLE
    while (balance > 0)  {
            // would be way easier to have a function do this for me?
            if  (currentMonth == 0) { // THIS FORMATS LINE 1
                cout << currentMonth++ <<  "\t$"   << loan;
                // if  (balance < 1000) cout << "\t" ; // Formatting MAGIC
                    cout << "\t"  << "N/A\tN/A\tN/A\t\tN/A\n";
            }
            if (balance * (1 + interestRateC) >= monthlyPaid) {
                interestPayment = interestRateC * balance;
                balance += interestPayment;
                balance -= monthlyPaid;

                cout << currentMonth << "\t$" << balance;
                if (balance < 1000) cout << "\t";
                cout << "\t$" << monthlyPaid;
                cout << "\t" << interestRate;
                cout << "\t$" << interestPayment;
                cout << "\t\t$" << monthlyPaid - interestPayment << "\n";
                currentMonth++;
            } else { // VERY MUCH A ROUND ABOUT WAY OF DOING IT, BUT IT WORKS SO I SMILE
                interestPayment = interestRateC * balance;
                float finalPrincipal = balance;
                balance += interestPayment;
                balance -= balance;
                cout << currentMonth << "\t$" << balance;
                if (balance < 1000) cout << "\t";
                cout << "\t$" << finalPrincipal + interestPayment;
                cout << "\t" << interestRate;
                cout << "\t$" << interestPayment;
                cout << "\t\t$" << finalPrincipal << "\n";
            }




            interestTotal += interestPayment;
    }

        // Properly calculate and display “monthlyPaid” and “principal” when  (1) loan * (1 + interestRateC) < monthlyPaid and (2) loan * (1 + interestRateC) >= monthlyPaid

            cout << "*****************************************************************\n";
            cout << "\nIt takes " << currentMonth <<  " months to pay off "
                 << "the loan.\n"
                 << "Total interest paid is: $" << interestTotal;
                 cout << endl << endl;
                 return 0;
}
