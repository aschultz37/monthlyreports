#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace RG{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;
        std::string oncID;
        std::string studyID;
        std::string received;
        std::string date;
    };

    class ReportGenerator{
        public:
            void importCSV(std::string inFileName);     //imports lines from CSV and parses it into struct
            void displayReport();                       //prints resulting/sorted list to terminal
            void writeReport(std::string outFileName);  //writes the resulting/sorted list to txt file
            int filterMonth(std::string month);              //copies only lines from the correct month into filteredLines; returns total #
            int sort(int option);                       //sorts by option: 1) PN; 2) OncID; 3) Study ID; 4) Timepoint; 5) Date
        
        private:
            std::vector <std::string> fileLines;
            std::vector <RG::EntryData> filteredLines;
            std::vector <RG::EntryData> sortedLines;

            void importParser();
            void pnSort();
            void oncSort();
            void studySort();
            void timeSort();
            void dateSort();
    };
}