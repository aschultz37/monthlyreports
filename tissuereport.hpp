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

        private:
            std::vector <TR::EntryData*> filteredLines;
            std::vector <TR::EntryData*> sortedLines;

            void importParser(std::string lineIn, TR::EntryData &fieldsOut);
    };
}