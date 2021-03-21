#ifndef _PROBLEM_H_
#define _PROBLEM_H_


#include <iostream>
#include <string>
#include <vector>



namespace ngm
{
    typedef std::vector<std::vector<int>> DimensionData;

    class Problem
    {
    public:
        
        Problem(const std::string& catalogue, 
                const std::string& title,
                const std::string& by,
                const std::string& copyright,
                const std::string& license, 
                const DimensionData& columnsData, 
                const DimensionData& rowsData);

        const std::string& GetCatalogue() const;
        const std::string& GetTitle()     const;
        const std::string& GetBy()		  const;
        const std::string& GetCopyright() const;
        const std::string& GetLicense()   const;

        const DimensionData& GetColumnsData() const;
        const DimensionData& GetRowsData()    const;

        size_t GetWidth () const;
        size_t GetHeight() const;

        //friend std::ostream&  operator<<(std::ofstream& ofs, const Problem& pb);

    private:

        std::string	    _catalogue;
        std::string	    _title;
        std::string	    _by;
        std::string	    _copyright;
        std::string	    _license;
        DimensionData   _columnsData;
        DimensionData   _rowsData;
    };
}


#endif // !_PROBLEM_H_