#include "reportgenerator.hpp"

using namespace std;

short mainmenu();
short filetypemenu();
short sortmenu();

int main(int argc, char **argv){
    bool runbit = true;
    RG::ReportGenerator report();

    while(runbit){
        short option = 0;
        while(option == 0){
            option = mainmenu();
            if(option == -1){
                printf("Invalid option, please try again\n");
                option = 0;
            }
        }

        switch (option){
            case 1: //import
                short filetype = 0;
                bool skip = false;
                while(filetype == 0){
                    filetype = filetypemenu();
                    if(filetype == -1){
                        printf("Invalid option, please try again\n");
                        filetype = 0;
                    }
                }
                switch (filetype){
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        skip = true;
                        break;
                }
                if(skip) break;
                string filename = "";
                printf("Please enter filename (including .csv): ");
                cin >> filename;
                report.importCSV(filename, filetype);
                break;
            case 2: //sort
            case 3: //display
            case 4: //write
            case 5: //quit
                runbit = false;
                break;
            default:
                printf("Unknown error, program closing.\n");
                runbit = false;
                break;
        }
    }

    return 0;
}

short mainmenu(){
    string userChoice = "";
    printf("---MAIN MENU---\nPlease select an option:\n");
    printf("1. Import file\n2. Sort file\n3. Display results\n4. Write results to file\n5.Quit\n");
    printf("Choice: ");
    cin >> userChoice;
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    if(userChoice.compare("5") == 0) return 5;
    return -1;
}

short filetypemenu(){
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

short sortmenu(){
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