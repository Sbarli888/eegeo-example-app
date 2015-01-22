// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CategorySearchSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            void CategorySearchSelectedMessageHandler::OnCategorySearchSelectedMessage(const CategorySearchSelectedMessage& message)
            {
                m_searchQueryPerformer.PerformSearchQuery(message.Category(), true);
            }

            CategorySearchSelectedMessageHandler::CategorySearchSelectedMessageHandler(
                Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &CategorySearchSelectedMessageHandler::OnCategorySearchSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            CategorySearchSelectedMessageHandler::~CategorySearchSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }
        }
    }
}
