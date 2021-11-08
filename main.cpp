#include "reportgenerator.hpp"

using namespace std;

int monthsetup();
int yearsetup();
int mainmenu();
int filetypemenu();
int sortmenu();

int main(int argc, char **argv){
    bool initbit = true;
    bool runbit = true;
    RG::ReportGenerator report = RG::ReportGenerator();

    int month = 0; int year = 0;
    while(initbit){
        while(month == 0){
            month = monthsetup();
            if(month == -1){
                printf("Invalid option, please try again.\n");
                month = 0;
            }
        }
        while(year == 0){
            year = yearsetup();
            if(year == -1){
                printf("Invalid option, please try again.\n");
                year = 0;
            }
        }
        string ynbit = "";
        printf("You selected %d-%d. Is this correct? (y/n): ", month, year);
        cin >> ynbit;
        if(ynbit.compare("y") == 0 || ynbit.compare("Y") == 0) initbit = false;
        else printf("OK, try again.\n");
    }

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
            int filetype = 0;
            while(filetype == 0){
                filetype = filetypemenu();
                if(filetype == -1){
                    printf("Invalid option, please try again.\n");
                    filetype = 0;
                }
            }
            if(filetype != 4){ 
                string filename = "";
                printf("Please enter filename (including .csv): ");
                cin >> filename;
                report.importCSV(filename, filetype);
                printf("File imported successfully.\n");
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

        }
        else if(option == 4){ //write

        }
        else if(option == 5){ //quit
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

int monthsetup(){
    string userChoice = "";
    printf("As a number 1-12, please enter the month for the report (e.g., 7 for July): ");
    cin >> userChoice;
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    if(userChoice.compare("5") == 0) return 5;
    if(userChoice.compare("6") == 0) return 6;
    if(userChoice.compare("7") == 0) return 7;
    if(userChoice.compare("8") == 0) return 8;
    if(userChoice.compare("9") == 0) return 9;
    if(userChoice.compare("10") == 0) return 10;
    if(userChoice.compare("11") == 0) return 11;
    if(userChoice.compare("12") == 0) return 12;
    return -1;
}

int yearsetup(){
    string userChoice = "";
    printf("Please enter the four-digit year for the report (e.g. 2021): ");
    cin >> userChoice;
    return stoi(userChoice);
}

int mainmenu(){
    string userChoice = "";
    printf("---MAIN MENU---\nPlease select an option:\n");
    printf("1. Import file\n2. Sort file\n3. Display results\n4. Write results to file\n5. Quit\n");
    printf("Choice: ");
    cin >> userChoice;
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    if(userChoice.compare("5") == 0) return 5;
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