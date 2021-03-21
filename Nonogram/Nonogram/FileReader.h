#ifndef _FILE_READER_H_
#define _FILE_READER_H_


#include "Problem.h"

#include <map>
#include <sstream>



namespace ngm 
{
    class FileReader
    {
    public:

        virtual std::unique_ptr<Problem> 
            ReadFile(const std::string& fileName) const = 0;
        
        virtual ~FileReader() = 0 { }

    protected:

        std::unique_ptr<std::stringstream> 
            GetStringStream(const std::string& fileName) const;
    };


    class NonFileReader
        : public FileReader
    {
    public:

        virtual std::unique_ptr<Problem> 
            ReadFile(const std::string& fileName) const override;

    private:

        std::unique_ptr<std::map<std::string, std::string>>
            GetHeaderKeyValues(std::stringstream& buffer) const;

        std::unique_ptr<std::map<std::string, DimensionData>>
            GetDataKeyValues(std::stringstream& buffer, 
                const int height, 
                const int width) const;

    private:

        static const int            _nHeaderKeys;
        static const std::string    _catalogueKey;
        static const std::string    _titleKey;
        static const std::string    _byKey;
        static const std::string    _copyrightKey;
        static const std::string    _licenseKey;
        static const std::string    _heightKey;
        static const std::string    _widthKey;

        static const int            _nDataKeys;
        static const std::string    _rowsKey;
        static const std::string    _columnsKey;

    };
}


#endif // !_FILE_READER_H_
