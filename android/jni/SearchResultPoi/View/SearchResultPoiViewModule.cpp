// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiView.h"
#include "SearchResultPoiController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiViewModule::SearchResultPoiViewModule(
                AndroidNativeState& nativeState,
                ISearchResultPoiViewModel& searchResultPoiViewModel
            )
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(SearchResultPoiView)(nativeState);
                m_pController = Eegeo_NEW(SearchResultPoiController)(*m_pView, searchResultPoiViewModel);
            }

            SearchResultPoiViewModule::~SearchResultPoiViewModule()
            {
                ASSERT_UI_THREAD
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            SearchResultPoiView& SearchResultPoiViewModule::GetView() const
            {
                return *m_pView;
            }

            SearchResultPoiController& SearchResultPoiViewModule::GetController() const
            {
                return *m_pController;
            }
        }
    }
}
