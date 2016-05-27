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
            
            m_categoryToIconIndex["entertainment"] = 4;

            m_categoryToIconIndex["accommodation"] = 5;
            
            m_categoryToIconIndex["art_museums"] = 15;

            m_categoryToIconIndex["tourism"] = 11;

            m_categoryToIconIndex["business"] = 12;

            m_categoryToIconIndex["sports_leisure"] = 19;

            m_categoryToIconIndex["amenities"] = 24;

        }
        
        SearchResultIconCategoryMapper::~SearchResultIconCategoryMapper()
        {
            
        }
        
        int SearchResultIconCategoryMapper::GetIconIndexFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const
        {
            std::map<std::string, int>::const_iterator it = m_categoryToIconIndex.find(searchResultModel.GetCategory());
            
            if(it == m_categoryToIconIndex.end())
            {
                const int defaultIconIndex = 23;
                return defaultIconIndex;
            }
            else
            {
                return it->second;
            }
        }
    }
}
