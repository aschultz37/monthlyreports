#include "fileio.hpp"

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
            void importCSV(std::string inFileName, std::ifstream &inFile);
            void writeReport(std::string outFileName, std::ofstream &outFile);
            int filterMonth();      //copies only lines from the correct month into filteredLines; returns total #
            int sort(int option);   //sorts by option: 1) PN; 2) OncID; 3) Study ID; 4) Timepoint; 5) Date
        
        private:
            std::ifstream inFile;
            std::ofstream outFile;
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