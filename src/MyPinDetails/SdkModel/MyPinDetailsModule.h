// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinDetails.h"
#include "IMyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "BidirectionalBus.h"
#include "MyPinDetailsViewRemovePinHandler.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            class MyPinDetailsModule: public IMyPinDetailsModule, private Eegeo::NonCopyable
            {
            private:
                View::MyPinDetailsViewModel* m_pMyPinDetailsViewModel;
                View::MyPinDetailsModelSelectedObserver* m_pMyPinDetailsModelSelectedObserver;
                MyPinDetailsViewRemovePinHandler* m_pMyPinDetailsViewRemovePinHandler;

            public:
                MyPinDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                   Reaction::View::IReactionControllerModel& reactionControllerModel,
                                   MyPins::SdkModel::IMyPinsService& myPinsService,
                                   ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinDetailsModule();

                View::IMyPinDetailsViewModel& GetMyPinDetailsViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
            };
        }
    }
}
