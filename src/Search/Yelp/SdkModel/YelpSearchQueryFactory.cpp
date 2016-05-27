// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Search.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"
#include "SearchResultModel.h"
#include "YelpSearchQueryFactory.h"
#include "YelpSearchQuery.h"
#include "YelpBusinessQuery.h"
#include "YelpSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpSearchQueryFactory::YelpSearchQueryFactory(
                    const std::string& yelpConsumerKey,
                    const std::string& yelpConsumerSecret,
                    const std::string& yelpOAuthToken,
                    const std::string& yelpOAuthTokenSecret,
                    Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
                    : m_yelpConsumerKey(yelpConsumerKey)
                    , m_yelpConsumerSecret(yelpConsumerSecret)
                    , m_yelpOAuthToken(yelpOAuthToken)
                    , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
                    , m_webRequestFactory(webRequestFactory)
                {

                    m_applicationToYelpCategoryMap = Yelp::SearchConstants::GetApplicationToYelpCategoryMap();
                }

                YelpSearchQueryFactory::~YelpSearchQueryFactory()
                {
                }

                SdkModel::IYelpSearchQuery* YelpSearchQueryFactory::CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery &query,
                    Eegeo::Helpers::ICallback0 &completionCallback)

                {
                    std::string yelpCategory;
                    
                    if (query.IsCategory())
                    {
                        std::map<std::string, std::string>::const_iterator category = m_applicationToYelpCategoryMap.find(query.Query());

                        if (category != m_applicationToYelpCategoryMap.end())
                        {
                            yelpCategory = category->second;
                        }
                    }

                    return Eegeo_NEW(YelpSearchQuery)(
                        m_yelpConsumerKey,
                        m_yelpConsumerSecret,
                        m_yelpOAuthToken,
                        m_yelpOAuthTokenSecret,
                        query,
                        completionCallback,
                        m_webRequestFactory,
                        yelpCategory);
                }

                SdkModel::IYelpSearchQuery* YelpSearchQueryFactory::CreateYelpSearchForSpecificLocation(
                    const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                    Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    return nullptr;
                    
                    /*return Eegeo_NEW(YelpBusinessQuery)(
                        m_yelpConsumerKey,
                        m_yelpConsumerSecret,
                        m_yelpOAuthToken,
                        m_yelpOAuthTokenSecret,
                        query,
                        completionCallback,
                        m_webRequestFactory);*/
                }
            }
        }
    }
}
