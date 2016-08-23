// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "ITagIconMapper.h"
#include "Types.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoTagIconMapper : public SearchResultPoi::SdkModel::ITagIconMapper, private Eegeo::NonCopyable
                {
                    //TODO: Optimise out values into separate vector
                    std::map<std::string, Search::SdkModel::TagIconKey> m_tagToTagIconKeyMapping;

                    const std::string m_defaultTag;

                public:
                    EegeoTagIconMapper();

                    ~EegeoTagIconMapper();

                    Search::SdkModel::TagIconKey GetIconKeyForTags(const std::vector<std::string>& tags) const;
                };
            }
        }
    }
}
