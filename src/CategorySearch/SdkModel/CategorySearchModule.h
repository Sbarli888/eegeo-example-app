// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICategorySearchModule.h"
#include "Types.h"
#include "Search.h"
#include "Menu.h"
#include "CategorySearchSelectedMessageHandler.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            class CategorySearchModule : public ICategorySearchModule, private Eegeo::NonCopyable
            {
            public:
                CategorySearchModule(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                     Menu::View::IMenuViewModel& menuViewModel,
                                     ExampleAppMessaging::TMessageBus& messageBus);

                ~CategorySearchModule();

                Menu::View::IMenuModel& GetCategorySearchMenuModel() const;

                View::ICategorySearchRepository& GetCategorySearchRepository() const;

            private:
                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                View::ICategorySearchRepository* m_pCategorySearchRepository;
                CategorySearchSelectedMessageHandler* m_pCategorySearchSelectedMessageHandler;
            };
        }
    }
}
