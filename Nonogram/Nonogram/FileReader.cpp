#include "FileReader.h"

#include <algorithm>
#include <fstream>
#include <iterator>



namespace ngm
{
    // class FileReader
    // -------------------------------------
    std::unique_ptr<std::stringstream>  
        FileReader::GetStringStream(const std::string& fileName) const
    {
        std::ifstream ifs(fileName);

        if (!ifs)
        {
            std::cerr << "Could not open file \"" << fileName << "\"." << std::endl;
            return nullptr;
        }

        auto bufferPtr = std::make_unique<std::stringstream>();
        (*bufferPtr) << ifs.rdbuf();

        ifs.close();

        return std::move(bufferPtr);
    }



    // class NonFileReader
    // -------------------------------------

    std::unique_ptr<Problem> NonFileReader::ReadFile(const std::string& fileName) const
    {
        const std::string invalidFormatString =
            "File \"" + fileName + "\": invalid format.";

        auto buffer = GetStringStream(fileName);        

        auto headerKVs = GetHeaderKeyValues(*buffer);
        if ( headerKVs == nullptr )
        {
            std::cerr << invalidFormatString << std::endl;
            return nullptr;
        }

        int width;
        int height;
        try
        {
            height = std::stoi(headerKVs->at( _heightKey ));
            width  = std::stoi(headerKVs->at( _widthKey  ));
        }
        catch (const std::exception& exc)
        {
            std::cerr << invalidFormatString << std::endl;
            return nullptr;
        }

        auto dataKVs = GetDataKeyValues(*buffer, height, width);
        if ( dataKVs == nullptr )
        {
            std::cerr << invalidFormatString << std::endl;
            return nullptr;
        }

        return std::make_unique<Problem>(
                headerKVs->at( _catalogueKey ), 
                headerKVs->at( _titleKey ), 
                headerKVs->at( _byKey ), 
                headerKVs->at( _copyrightKey ), 
                headerKVs->at( _licenseKey ), 
                dataKVs->at( _columnsKey ), 
                dataKVs->at( _rowsKey )
            );
    }

    std::unique_ptr<std::map<std::string, std::string>> 
        NonFileReader::GetHeaderKeyValues(std::stringstream& buffer) const
    {
        auto headerKeyValues = std::make_unique<std::map<std::string, std::string>>();

        std::string key;
        std::string value;

        for (int i = 0; i < _nHeaderKeys; ++i)
        {
            std::getline(buffer, key, ' ');
            std::getline(buffer, value);
            (*headerKeyValues)[key] = value;
        }

        std::string serviceText;
        std::getline(buffer, serviceText); // empty line

        auto hdmEndIter = headerKeyValues->end();

        if ((headerKeyValues->find(_catalogueKey) == hdmEndIter) ||
            (headerKeyValues->find(_titleKey)     == hdmEndIter) ||
            (headerKeyValues->find(_byKey)        == hdmEndIter) ||
            (headerKeyValues->find(_copyrightKey) == hdmEndIter) ||
            (headerKeyValues->find(_licenseKey)   == hdmEndIter) ||
            (headerKeyValues->find(_heightKey)    == hdmEndIter) ||
            (headerKeyValues->find(_widthKey)     == hdmEndIter))
        {
            return nullptr;
        }

        return std::move(headerKeyValues);
    }

    std::unique_ptr<std::map<std::string, DimensionData>>
        NonFileReader::GetDataKeyValues(std::stringstream& buffer, 
            const int height, 
            const int width) const
    {
        auto dataKVs = std::make_unique<std::map<std::string, DimensionData>>();
        
        dataKVs->insert(std::make_pair( _rowsKey,    DimensionData(height) ));
        dataKVs->insert(std::make_pair( _columnsKey, DimensionData(width)  ));

        std::string key;
        std::string serviceText;

        for (int i = 0; i < _nDataKeys; ++i)
        {
            std::getline(buffer, key); // "columns" or "rows"
            
            if (dataKVs->find(key) == dataKVs->end()) 
                return nullptr;

            std::for_each(dataKVs->at(key).begin(), dataKVs->at(key).end(), 
                [&buffer](std::vector<int>& row) {
                    std::string line;
                    std::getline(buffer, line);
                    std::replace(line.begin(), line.end(), ',', ' ');
                    std::stringstream lineBuffer(line);
                    std::copy(
                        std::istream_iterator<int>(lineBuffer),
                        std::istream_iterator<int>(),
                        std::back_inserter(row));
                });

            std::getline(buffer, serviceText); // empty line
        }

        return std::move(dataKVs);
    }

    const int         NonFileReader::_nHeaderKeys  = 7;
    const std::string NonFileReader::_catalogueKey = "catalogue";
    const std::string NonFileReader::_titleKey     = "title";
    const std::string NonFileReader::_byKey        = "by";
    const std::string NonFileReader::_copyrightKey = "copyright";
    const std::string NonFileReader::_licenseKey   = "license";
    const std::string NonFileReader::_heightKey    = "height";
    const std::string NonFileReader::_widthKey     = "width";

    const int         NonFileReader::_nDataKeys    = 2;
    const std::string NonFileReader::_rowsKey      = "rows";
    const std::string NonFileReader::_columnsKey   = "columns";
}