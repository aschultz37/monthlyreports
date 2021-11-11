#include <string>
#include <vector>

namespace TR{
    struct EntryData{
        std::string PN;
        std::string studyArm;
        std::string visit;//aka timepoint
        std::string oncID;
        std::string subjectID;
        std::string sampleType;
        std::string biopsyType;
        std::string date;
    };

    class TissueReport{
        public:
            TissueReport();
            ~TissueReport(); //delete structs from filteredLines and sortedLines
            
            std::vector <TR::EntryData*> const &getFilteredLines(){ return filteredLines;}
            std::vector <TR::EntryData*> const &getSortedLines(){ return sortedLines;}

            void pushSortedLines(TR::EntryData* input){ sortedLines.push_back(input);}

            void importParser(std::string lineIn);
            int tissueMonthFilter(int month, int year);
            void copytoSortTissue();
            void clearSort();
            void clearFiltered();
            void swapSortedLines(int index1, int index2);
        private:
            std::vector <TR::EntryData*> parsedLines;
            std::vector <TR::EntryData*> filteredLines;
            std::vector <TR::EntryData*> sortedLines;

            int extractMonth(std::string date);
            int extractYear(std::string date);
    };
}