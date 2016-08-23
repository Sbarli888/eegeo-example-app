// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "EegeoTagIconMapper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoTagIconMapper::EegeoTagIconMapper()
                    : m_defaultTag("misc")
                {
                    // TODO tags: extract & data-drive this
                    m_tagToTagIconKeyMapping.insert(std::make_pair("aroundme", "aroundme"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("accommodation", "accommodation"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("art_museums", "art_museums"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("business", "business"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("entertainment", "entertainment"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("food_drink", "food_drink"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("amenities", "amenities"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("health", "health"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("shopping", "shopping"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("sports_leisure", "sports_leisure"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("tourism", "tourism"));
                    m_tagToTagIconKeyMapping.insert(std::make_pair("transport", "transport"));
                }

                EegeoTagIconMapper::~EegeoTagIconMapper()
                {
                }

                ExampleApp::Search::SdkModel::TagIconKey EegeoTagIconMapper::GetIconKeyForTags(const std::vector<std::string>& tags) const
                {
                    for (std::vector<std::string>::const_iterator tag = tags.begin();
                        tag != tags.end();
                        ++tag)
                    {
                        std::map<std::string, std::string>::const_iterator result = m_tagToTagIconKeyMapping.find(*tag);

                        if (result != m_tagToTagIconKeyMapping.end())
                        {
                            return result->second;
                        }
                    }

                    return m_defaultTag;
                }
            }
        }
    }
}
