// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "types.h"

#include <set>
#include "TweetRepository.h"
#include "Tours.h"
#include "WorldPins.h"
#include "TwitterFeed.h"
#include <map>
#include <TweetStateData.h>
#include "BidirectionalBus.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace TwitterFeed
                {
                    class TwitterFeedTourObserver : private Eegeo::NonCopyable
                    {
                    private:
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        ITourService& m_tourService;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                        Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                        ITourRepository& m_tourRepository;
                        Social::TwitterFeed::ITwitterFeedService& m_twitterFeedService;
                        
                        const std::map<std::string, TweetStateData>& m_tweetStateDataMap;
                        std::map<std::string, std::string> m_twitterTourIconOverrideMap;
                        
                        std::set<std::string> m_setOfTourTwitterBaseUserNames;
                        
                        Eegeo::Helpers::TCallback2<TwitterFeedTourObserver, const std::string&, Social::TwitterFeed::TweetRepository&> m_twitterFeedLoadedCallback;
                        
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        
                        void OnTwitterFeedLoaded(const std::string& userId,
                                                 Social::TwitterFeed::TweetRepository& tweetRepository);
                        
                        void UpadateTweetLinksOut();
                        
                        std::string PinIconKeyForTwitterUser(const std::string twitterUserId) const;
                    public:
                        TwitterFeedTourObserver(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                ITourService& tourService,
                                                WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                ITourRepository& tourRepository,
                                                Social::TwitterFeed::ITwitterFeedService& twitterFeedService,
                                                const std::map<std::string, TweetStateData>& tweetStateDataMap,
                                                const std::map<std::string, std::string>& twitterTourIconOverrideMap,
                                                ExampleAppMessaging::TMessageBus& messageBus);
                        ~TwitterFeedTourObserver();
                    };
                }
            }
        }
    }
}
