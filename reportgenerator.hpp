#include <iostream>
#include <fstream>
#include "bloodreport.hpp"
#include "tissuereport.hpp"
#include "stoolreport.hpp"

/*reportgenerator.hpp
* This class assumes that an input .csv has standard format.
* The .csv should be a standard Blood Processing sheet from BTIL Biospecimens.
* This class can extract and manipulate entries from a given month/year combination.
* Results can be displayed to the terminal or written to a .txt file.
*/

namespace RG{
    enum filetypes {blood = 1, tissue = 2, stool = 3};

    struct ReportSheets{ //blood, tissue, and stool sheets for each report
        BR::BloodReport* bloodreport;
        TR::TissueReport* tissuereport;
        SR::StoolReport* stoolreport;
    };

    class ReportGenerator{
        public:
            ReportGenerator();
            ~ReportGenerator();
            
            void importCSV(std::string inFileName);
            int filterMonth(int month, int year);
            void copytoSort();
            void displayReport();
            void writeReport(std::string outFileName);
            void sort(int option);

            void setFileType(int inFileType){ filetype = inFileType;}
        private:
            std::vector <std::string> fileLines;
            RG::ReportSheets* sheets;
            int filetype;
            
            void pnSort();
            void oncSort();
            void subjectSort();
            void timeSort();
            void dateSort();
            int dateCompare(std::string date1, std::string date2);
            void bloodSwap(BR::EntryData &entry1, BR::EntryData &entry2);
            void tissueSwap(TR::EntryData &entry1, TR::EntryData &entry2);
            void stoolSwap(SR::EntryData &entry1, SR::EntryData &entry2);
    };
}