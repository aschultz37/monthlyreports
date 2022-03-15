#include "reportgenerator.hpp"

using namespace std;

void setupMonthYear(int &month, int &year);
int monthsetup(int &month);
int yearsetup(int &year);
int mainmenu();
int filetypemenu();
string studyNumMenu();
int sortmenu();
void writefile(string &filename);

int main(int argc, char **argv){ //argv format:./a.out mm yyyy filetype infilename outfilename
    bool runbit = true;
    bool rerun = false;
    RG::ReportGenerator report = RG::ReportGenerator();

    int month = 0; int year = 0;

    if(argc >= 5){ //for use with script
        try{
            month = stoi(argv[1]);
            year = stoi(argv[2]);
            report.setFileType(stoi(argv[3]));
            string infilename = argv[4];
            report.importCSV(infilename);
            cout << infilename << " imported successfully.\n";
            //printf("File imported successfully.\n");
            //count total # of each timepoint
            report.totalTimepoints(month, year);
            //now filter by month
            int numEntriesMonth = report.filterMonth(month, year);
            printf("Filtered by %d-%d.\n\nThere are %d samples.\n", month, year, numEntriesMonth);
            report.copytoSort(); //need to do this in case want to display/write without sorting
            if(argc >= 6 && numEntriesMonth == 0){ runbit = false;}            
            else if(argc >= 6){
                report.sort(5); //sort by timepoint (to fill timepointTracker)
                report.sort(6); //sort by date
                report.writeReport(argv[5]); //write to file specified
                runbit = false;
            }
        } catch(std::exception){
            cout << "Error: Invalid command line argument. Proceeding to manual setup.\n";
            setupMonthYear(month, year);
        }
    }
    else{ setupMonthYear(month, year);}

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
            //report.setStudyNumber(studyNumMenu());
            if(filetype != 4){ 
                string filename = "";
                printf("Please enter filename (including .csv): ");
                cin >> filename;
                try{
                    report.importCSV(filename);
                    printf("File imported successfully.\n");
                    //count total # of each timepoint
                    report.totalTimepoints(month, year);
                    //now filter by month
                    int numEntriesMonth = report.filterMonth(month, year);
                    printf("Filtered by %d-%d.\n\nThere are %d samples.\n", month, year, numEntriesMonth);
                    report.copytoSort(); //need to do this in case want to display/write without sorting
                } catch(runtime_error){
                    cout << "Runtime Error: Check file name/type and try again.\n";
                } catch(logic_error){
                    cout << "Logic Error: Check file name/type and try again.\n";
                }
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
                if(sorttype == 4){ //stool ID sort
                    if(report.getFileType() != RG::filetypes::stool){
                        printf("Error: You cannot sort by Stool ID for a non-stool sheet, please try again.\n");
                        printf("For VICTORY, please sort by Subject ID.\n");
                        sorttype = 0; 
                    }
                }
            }
            report.sort(sorttype);
        }
        else if(option == 3){ //display
            report.displayReport();
        }
        else if(option == 4){ //write
            string outputfile = "monthly_report.csv"; //default output location
            writefile(outputfile);
            cout << "The output will be written to " << outputfile << ".\n";
            try{
                report.writeReport(outputfile);
            } catch(runtime_error){
                cout << "Runtime Error: Check file name and try again.\n";
            } catch(logic_error){
                cout << "Logic Error: Check file name and try again.\n";
            }
        }
        else if(option == 5){ //set month/year
            month = year = 0;
            setupMonthYear(month, year);
            report.filterMonth(month, year);
            printf("Filtered by %d-%d.\n", month, year);
            report.copytoSort(); //need to do this in case want to display/write without sorting
            report.clearTimepointTracker(); //clear timepointTracker
            report.clearTimepointTotal(); //clear timepointTotal
            report.totalTimepoints(month, year); //recalculate totalTimepoints with new month/year
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
            if(monthsetup(month) == -1){
                printf("Invalid option, please try again.\n");
                month = 0;
            }
        }
        while(year == 0){
            if(yearsetup(year) == -1){
                printf("Invalid option, please try again.\n");
                year = 0;
            }
        }
        string ynbit = "";
        printf("You selected %d-%d. Is this correct? (y/n): ", month, year);
        cin >> ynbit;
        if(ynbit.length() > 0){ ynbit = ynbit.substr(0,1);}
        if(ynbit.compare("y") == 0 || ynbit.compare("Y") == 0) mybit = false;
        else{ printf("OK, try again.\n"); month = 0; year = 0;}
    }
}

int monthsetup(int &month){
    string userChoice = "";
    printf("As a number 1-12, please enter the month for the report (e.g., 7 for July): ");
    cin >> userChoice;
    if(userChoice.length() > 2){ userChoice = userChoice.substr(0,2);}
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
    bool waiting = true;
    while(waiting){
        string userChoice = "";
        printf("Please enter the four-digit year for the report (e.g. 2021): ");
        cin >> userChoice;
        try{
            year = stoi(userChoice);
            waiting = false;
        } catch(invalid_argument){
            cout << "Input not a number, please try again.\n";
        }
    }
    return year;
}

int mainmenu(){
    string userChoice = "";
    printf("\n\n---MAIN MENU---\nPlease select an option:\n");
    printf("1. Import File\n2. Sort File\n3. Display Results\n4. Write Results to File\n5. Set Month/Year\n6. Quit\n");
    printf("Choice: ");
    cin >> userChoice; 
    if(userChoice.length() > 0){ userChoice = userChoice.substr(0,1);}
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
    printf("\n-File Type Menu-\nPlease select an option:\n");
    printf("1. Blood\n2. Tissue\n3. Stool\n4. Back to Main Menu\n");
    printf("Choice: ");
    cin >> userChoice;
    if(userChoice.length() > 0){ userChoice = userChoice.substr(0,1);}
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    return -1;
}

string studyNumMenu(){
    string userInput = "";
    bool running = true;
    while(running){
        string userChoice = "";
        printf("Please enter the study number without a hyphen (e.g. 20166): ");
        cin >> userInput;
        cout << "You input " << userInput << ", is that correct? (y/n): ";
        cin >> userChoice;
        if(userChoice.compare("y") == 0 || userChoice.compare("Y") == 0){ running = false;}
        else{ printf("OK, try again.\n"); userInput = "";}
    }
    return userInput;
}

int sortmenu(){
    string userChoice = "";
    printf("\n-Sort Menu-\nPlease select an option:\n");
    printf("1. PN\n2. OncID\n3. Subject ID\n4. Stool ID\n5. Timepoint\n6. Date\n7. Back to Main Menu\n");
    printf("Choice: ");
    cin >> userChoice;
    if(userChoice.length() > 0){ userChoice = userChoice.substr(0,1);}
    if(userChoice.compare("1") == 0) return 1;
    if(userChoice.compare("2") == 0) return 2;
    if(userChoice.compare("3") == 0) return 3;
    if(userChoice.compare("4") == 0) return 4;
    if(userChoice.compare("5") == 0) return 5;
    if(userChoice.compare("6") == 0) return 6;
    if(userChoice.compare("7") == 0) return 7;
    return -1;
}

void writefile(string &filename){
    cout << "Default location: " << filename << endl;
    bool setbit = true;
    while(setbit){
        string userin = "";
        printf("Would you like to change the file location? (y/n): ");
        cin >> userin; 
        if(userin.length() > 0){ userin = userin.substr(0,1);}
        if(userin.compare("y") == 0 || userin.compare("Y") == 0){
            string filenamein = "";
            printf("Please enter the output file name (ending in .csv): ");
            cin >> filenamein;
            string checkin = "";
            cout << "You entered " << filenamein << ", is that correct? (y/n): ";
            cin >> checkin;
            if(checkin.length() > 0){ checkin = checkin.substr(0,1);}
            if(checkin.compare("y") == 0 || checkin.compare("Y") == 0){ 
                setbit = false; filename = filenamein;
            }
            else{ cout << "OK, try again.\n";}
        }
        else setbit = false;
    }
}