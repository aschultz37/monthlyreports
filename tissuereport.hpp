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
            
            void importParser(std::string lineIn);
            int tissueMonthFilter(std::string month, std::string year);
        private:
            std::vector <TR::EntryData*> parsedLines;
            std::vector <TR::EntryData*> filteredLines;
            std::vector <TR::EntryData*> sortedLines;

    };
}