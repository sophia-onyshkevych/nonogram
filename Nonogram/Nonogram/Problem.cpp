#include "Problem.h"



namespace ngm 
{
    // class Problem
    // -------------------------------------

    Problem::Problem(
        const std::string& catalogue,
        const std::string& title,
        const std::string& by,
        const std::string& copyright,
        const std::string& license,
        const DimensionData& columnsData,
        const DimensionData& rowsData)
        : _catalogue(catalogue), 
          _title(title), 
          _by(by), 
          _copyright(copyright), 
          _license(license),
          _columnsData(columnsData),
          _rowsData(rowsData)
    {
    }


    const std::string& Problem::GetCatalogue() const
    {
        return _catalogue;
    }

    const std::string& Problem::GetTitle() const
    {
        return _title;
    }

    const std::string& Problem::GetBy() const
    {
        return _by;
    }

    const std::string& Problem::GetCopyright() const
    {
        return _copyright;
    }

    const std::string& Problem::GetLicense() const
    {
        return _license;
    }

    const DimensionData& Problem::GetColumnsData() const
    {
        return _columnsData;
    }

    const DimensionData& Problem::GetRowsData() const
    {
        return _rowsData;
    }

    size_t Problem::GetWidth() const
    {
        return _columnsData.size();
    }

    size_t Problem::GetHeight() const
    {
        return _rowsData.size();
    }
}