// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewModule.h"
#include "MyPinDetailsViewController.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
    	MyPinDetailsViewModule::MyPinDetailsViewModule(
    			AndroidNativeState& nativeState,
    			IMyPinDetailsViewModel& myPinDetailsViewModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
		{
    		m_pViewController = Eegeo_NEW(MyPinDetailsViewController)(nativeState, myPinDetailsViewModel, uiToNativeMessageBus);
		}

		MyPinDetailsViewModule::~MyPinDetailsViewModule()
		{
			Eegeo_DELETE m_pViewController;
		}

    }
}
