//Zenith Kile
//WEEKLY PAYROLL INFORMATION (final program)
/*This program shows the user a menu of options
from which they can see the information collected from the week's payroll
as well as an option to exit the program.*/

//Preprocessor Directives
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//Named Constants
const double FEDERAL_TAX = 0.09;
const double STATE_TAX = 0.05;
const double FICA_TAX = 0.062;
const int ROWS = 10;
const int MAX_HOURS = 40;
const double OVERTIME_RATE = 1.5;

//Function Declarations
void fullNameConcatenation(string first[], string last[], string full[]);
void grossCalculations(double pRate[], double time[], double total[]);
void taxesCalculations(double overall[], double taxTotal[], double final[]);

//Main Function
int main()
{
    //Program Title and Desc.
    cout << "WEEKLY PAYROLL INFORMATION" << endl;
    cout << "This program shows the user a menu of options" << endl
        << "from which they can see the information collected from the week's payroll" << endl
        << "as well as an option to exit the program." << endl << endl;

    //Local Variable Declaration
    int menuOption;
    string lName[ROWS];
    string fName[ROWS];
    string fullName[ROWS];
    double payrate[ROWS];
    double hours[ROWS];
    double gross[ROWS];
    double totalGross = 0;
    double taxes[ROWS];
    double totalTaxes = 0;
    double net[ROWS];
    double totalNet = 0;
    int rowLocation; //counter variable

    do //Outer Loop to continue program until terminated
    {
        do //inner loop to check for input validity
        {
            //Menu Output
            cout << "Main Menu" << endl;
            cout << setw(10) << left << "1. " << "Run Payroll Report" << endl
                << setw(10) << left << "2. " << "View Payroll Statistics" << endl
                << setw(10) << left << "3. " << "View Overtime Employees" << endl
                << setw(10) << left << "4. " << "Exit the Program" << endl << endl;
            cout << "Your choice: "; //User Input
            cin >> menuOption;

            //Validity Check
            if (menuOption < 1 || menuOption > 4 || !cin)
            {
                cout << "Invalid Input" << endl
                    << "Please try again." << endl << endl;

                cin.clear(); //revivies program failstate
                cin.ignore(100, '\n'); //clears program garbage after failstate
            }

        } while (menuOption < 1 || menuOption > 4 || !cin);

        //File Varible Declaration
        ifstream fin;
        ofstream fout;

        //Open Files
        fin.open("hourlyInput.txt");
        fout.open("hourlyOutput.txt");

        //File Open Check
        if (!fin.is_open())
        {
            cout << "There was a problem with opening the input file. Please try again.";
            cout << endl;
            return 1; //terminates program with an error
        }

        else
        {
            //Read In Input from file
            for (rowLocation = 0; rowLocation < ROWS; rowLocation++)
            {
                fin >> lName[rowLocation];
                fin >> fName[rowLocation];
                fin >> payrate[rowLocation];
                fin >> hours[rowLocation];
            }

            //Calculations
            fullNameConcatenation(fName, lName, fullName); //Makes new string array
            grossCalculations(payrate, hours, gross); //Finds gross amounts and forms array
            taxesCalculations(gross, taxes, net); //Finds tax amounts and net amounts and forms respective arrays

            if (menuOption == 1) //Prints Payroll Report
            {
                //Print Output = Column Names
                fout << setw(25) << left << "Name" << setw(10) << right << "PayRate"
                    << setw(10) << right << "Hours" << setw(10) << right << "Gross"
                    << setw(10) << right << "Taxes" << setw(10) << right << "Net"
                    << endl;

                fout << showpoint << fixed << setprecision(2); //Formats Decimals

                //Column Output
                for (rowLocation = 0; rowLocation < ROWS; rowLocation++)
                {
                    fout << setw(25) << left << fullName[rowLocation]
                        << setw(10) << right << payrate[rowLocation]
                        << setw(10) << right << hours[rowLocation]
                        << setw(10) << right << gross[rowLocation]
                        << setw(10) << right << taxes[rowLocation]
                        << setw(10) << right << net[rowLocation]
                        << endl;
                }
                //Confirmation Output
                cout << "The payroll report has been run successfully" << endl << endl; 
            }

            else if (menuOption == 2) //Prints Payroll Statistics
            {
                system("cls"); //Screen clear

                cout << "Weekly Payroll Statistics" << endl << endl;

                //Finds sum of gross array and outputs to screen
                for (rowLocation = 0; rowLocation < ROWS; rowLocation++)
                    totalGross = gross[rowLocation] + totalGross;          
                cout << setw(20) << left << "Total Gross Pay: "
                    << setw(5) << right << "$" << totalGross;
                cout << endl;

                //finds sum of taxes array, outputs to screen
                for (rowLocation = 0; rowLocation < ROWS; rowLocation++)
                    totalTaxes = taxes[rowLocation] + totalTaxes;         
                cout << setw(20) << left << "Total Taxes: "
                    << setw(5) << right << "$" << totalTaxes;
                cout << endl;

                //finds sum of net array, outputs to screen
                for (rowLocation = 0; rowLocation < ROWS; rowLocation++)
                    totalNet = net[rowLocation] + totalNet;
                cout << setw(20) << left << "Total Net Pay: "
                    << setw(5) << right << "$" << totalNet;
                cout << endl << endl;
            }

            else if (menuOption == 3) //Prints Overtime Report
            {
                system("cls"); //Screen Clear

                cout << "Overtime Report" << endl << endl;

                for (rowLocation = 0; rowLocation < ROWS; rowLocation++) //Locates overtime hours
                {
                    //Locates worker name and outputs data to the screen
                    if (hours[rowLocation] >= MAX_HOURS)
                    {
                        cout << setw(20) << left << fullName[rowLocation]
                            << setw(5) << right << hours[rowLocation] << " hours";
                        cout << endl;
                    }

                }
                cout << endl;
            }
            else if (menuOption == 4) //Exit Program Output
            {
                //Close Files
                fin.close();
                fout.close();

                cout << "Thank you for using this program." << endl;
            }

        }

    } while (menuOption != 4);

    return 0;
}

//Function Definitions

void fullNameConcatenation(string first[], string last[], string full[])
{
    int rnum; //counter variable

    for (rnum = 0; rnum < ROWS; rnum++)
    {
        full[rnum] = last[rnum] + " " + first[rnum]; //concatenation
    }
}

void grossCalculations(double pRate[], double time[], double total[])
{
    int rLoc; //row location counter

    for (rLoc = 0; rLoc < ROWS; rLoc++)
    {
        if (time[rLoc] <= MAX_HOURS)
        {
            total[rLoc] = pRate[rLoc] * time[rLoc];
        }
        else //Calculations for overtime hours
        {
            total[rLoc] = (pRate[rLoc] * MAX_HOURS) 
                + ((time[rLoc] - MAX_HOURS) * 1.5 * pRate[rLoc]);
        }
    }
}

void taxesCalculations(double overall[], double taxTotal[], double final[])
{
    int rowCounter; //counter variable

    //Local Variable Declaratioins
    double federal, state, fica;

    for (rowCounter = 0; rowCounter < ROWS; rowCounter++) //forms array of tax information
    {
        federal = FEDERAL_TAX * overall[rowCounter]; //total federal
        state = STATE_TAX * overall[rowCounter]; //total state
        fica = FICA_TAX * overall[rowCounter]; //total fica

        taxTotal[rowCounter] = federal + state + fica;
    }
    for (rowCounter = 0; rowCounter < ROWS; rowCounter++) //forms array of net information
    {
        final[rowCounter] = overall[rowCounter] - taxTotal[rowCounter];
    }
}
