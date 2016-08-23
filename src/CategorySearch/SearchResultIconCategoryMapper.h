// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "Search.h"
#include "ISearchResultIconCategoryMapper.h"
#include "SearchResultModel.h"
#include "Types.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class SearchResultIconCategoryMapper : public ISearchResultIconCategoryMapper, private Eegeo::NonCopyable
        {
        public:
            ~SearchResultIconCategoryMapper();

            ExampleApp::Search::SdkModel::TagIconKey GetIconKeyFromSearchResult(
                    const Search::SdkModel::SearchResultModel& searchResultModel) const;
       };
    }
}
