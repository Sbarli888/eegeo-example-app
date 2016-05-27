// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultIconCategoryMapper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        SearchResultIconCategoryMapper::SearchResultIconCategoryMapper()
        {
            m_categoryToIconIndex["transport"] = 0;
            
            m_categoryToIconIndex["health"] = 1;
            
            m_categoryToIconIndex["shopping"] = 2;
            
            m_categoryToIconIndex["food_drink"] = 3;
            
            m_categoryToIconIndex["arts"] = 4;
            
            m_categoryToIconIndex["art_museums"] = 5;

            m_categoryToIconIndex["tourism"] = 6;

            m_categoryToIconIndex["business"] = 7;

            m_categoryToIconIndex["accommodation"] = 8;

            m_categoryToIconIndex["sports_leisure"] = 9;

            m_categoryToIconIndex["amenities"] = 10;

        }
        
        SearchResultIconCategoryMapper::~SearchResultIconCategoryMapper()
        {
            
        }
        
        int SearchResultIconCategoryMapper::GetIconIndexFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const
        {
            std::map<std::string, int>::const_iterator it = m_categoryToIconIndex.find(searchResultModel.GetCategory());
            
            if(it == m_categoryToIconIndex.end())
            {
                return 12;
            }
            else
            {
                return it->second;
            }
        }
    }
}
