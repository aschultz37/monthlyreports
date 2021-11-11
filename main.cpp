#include "reportgenerator.hpp"

using namespace std;

void setupMonthYear(int &month, int &year);
int monthsetup(int &month);
int yearsetup(int &year);
int mainmenu();
int filetypemenu();
int sortmenu();

int main(int argc, char **argv){
    bool initbit = true;
    bool runbit = true;
    bool rerun = false;
    RG::ReportGenerator report = RG::ReportGenerator();

    int month = 0; int year = 0;
    setupMonthYear(month, year);

    while(runbit){
        int option = 0;
        while(option == 0){
            option = mainmenu();
            if(option == -1){
                printf("Invalid option, please try again.\n");
                option = 0;
            }
        }

        if(option == 1){ //import
            if(rerun){
                report = RG::ReportGenerator();
            }
            rerun = true;
            int filetype = 0;
            while(filetype == 0){
                filetype = filetypemenu();
                if(filetype == -1){
                    printf("Invalid option, please try again.\n");
                    filetype = 0;
                }
                report.setFileType(filetype);
            }
            if(filetype != 4){ 
                string filename = "";
                printf("Please enter filename (including .csv): ");
                cin >> filename;
                report.importCSV(filename);
                printf("File imported successfully.\n");
                //now filter by month
                report.filterMonth(month, year);
                printf("Filtered by %d-%d.\n", month, year);
                report.copytoSort(); //need to do this in case want to display/write without sorting
            }    
        }
        else if(option == 2){ //sort
            int sorttype = 0;
            while(sorttype == 0){
                sorttype = sortmenu();
                if(sorttype == -1){
                    printf("Invalid option, please try again.\n");
                    sorttype = 0;
                }
            }
            report.sort(sorttype);
        }
        else if(option == 3){ //display
            report.displayReport();
        }
        else if(option == 4){ //write
            string outputfile = "monthly_report.txt";
            cout << "The output will be written to " << outputfile << ".\n";
            report.writeReport(outputfile);
        }
        else if(option == 5){ //set month/year
            month = year = 0;
            setupMonthYear(month, year);
            report.filterMonth(month, year);
            printf("Filtered by %d-%d.\n", month, year);
            report.copytoSort(); //need to do this in case want to display/write without sorting
        }
        else if(option == 6){ //quit
            printf("Program closing.\n");
            runbit = false;
        }
        else{
            printf("Unknown error, program closing.\n");
            runbit = false;
        }
    }

    return 0;
}

void setupMonthYear(int &month, int &year){
    bool mybit = true;
    while(mybit){
        while(month == 0){
            //month = monthsetup();
            if(monthsetup(month) == -1){
                printf("Invalid option, please try again.\n");
                month = 0;
            }
        }
        while(year == 0){
            //year = yearsetup();
            if(yearsetup(year) == -1){
                printf("Invalid option, please try again.\n");
                year = 0;
            }
        }
        string ynbit = "";
        printf("You selected %d-%d. Is this correct? (y/n): ", month, year);
        cin >> ynbit;
        if(ynbit.compare("y") == 0 || ynbit.compare("Y") == 0) mybit = false;
        else{ printf("OK, try again.\n"); month = 0; year = 0;}
    }
}

int monthsetup(int &month){
    string userChoice = "";
    printf("As a number 1-12, please enter the month for the report (e.g., 7 for July): ");
    cin >> userChoice;
    if(userChoice.compare("1") == 0){ month = 1; return 1;}
    if(userChoice.compare("2") == 0){ month = 2; return 2;}
    if(userChoice.compare("3") == 0){ month = 3; return 3;}
    if(userChoice.compare("4") == 0){ month = 4; return 4;}
    if(userChoice.compare("5") == 0){ month = 5; return 5;}
    if(userChoice.compare("6") == 0){ month = 6; return 6;}
    if(userChoice.compare("7") == 0){ month = 7; return 7;}
    if(userChoice.compare("8") == 0){ month = 8; return 8;}
    if(userChoice.compare("9") == 0){ month = 9; return 9;}
    if(userChoice.compare("10") == 0){ month = 10; return 10;}
    if(userChoice.compare("11") == 0){ month = 11; return 11;}
    if(userChoice.compare("12") == 0){ month = 12; return 12;}
    return -1;
}

int yearsetup(int &year){
    string userChoice = "";
    printf("Please enter the four-digit year for the report (e.g. 2021): ");
    cin >> userChoice;
    year = stoi(userChoice);
    return year;
}

int mainmenu(){
    string userChoice = "";
    printf("---MAIN MENU---\nPlease select an option:\n");
    printf("1. Import File\n2. Sort File\n3. Display Results\n4. Write Results to File\n5. Set Month/Year\n6. Quit\n");
    printf("Choice: ");
    cin >> userChoice;
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    if(userChoice.compare("5") == 0) return 5;
    if(userChoice.compare("6") == 0) return 6;
    return -1;
}

int filetypemenu(){
    string userChoice = "";
    printf("-File Type Menu-\nPlease select an option:\n");
    printf("1. Blood\n2. Tissue\n3. Stool\n4. Back to Main Menu\n");
    printf("Choice: ");
    cin >> userChoice;
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    return -1;
}

int sortmenu(){
    string userChoice = "";
    printf("-Sort Menu-\nPlease select an option:\n");
    printf("1. PN\n2. OncID\n3. Subject ID\n4. Timepoint\n5. Date\n6. Back to Main Menu\n");
    printf("Choice: ");
    cin >> userChoice;
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    if(userChoice.compare("5") == 0) return 5;
    if(userChoice.compare("6") == 0) return 6;
    return -1;
}