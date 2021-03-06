// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITourStateMachineState.h"
#include "Tours.h"
#include "TourStateModel.h"
#include "OrbitCameraMode.h"
#include "LatLongAltitude.h"
#include "WorldPins.h"
#include "WorldPinInteriorData.h"
#include <string>
#include "Interiors.h"
#include "Camera.h"
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
                namespace Example
                {
                    class ExampleTourState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                    public:
                        
                        ExampleTourState(const TourStateModel& stateModel,
                                         Eegeo::Space::LatLong position,
                                         bool isInterior,
                                         Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                         WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                         WorldPins::SdkModel::WorldPinInteriorData& worldPinInteriorData,
                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                         ExampleAppMessaging::TMessageBus& messageBus);
                        ~ExampleTourState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                        
                    private:
                        
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::OrbitCameraMode m_cameraMode;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        WorldPins::SdkModel::WorldPinItemModel* m_pPinItemModel;
                        Eegeo::Space::LatLong m_position;
                        bool m_cameraTransitionComplete;
                        bool m_interiorTransitionComplete;
                        
                        bool m_interior;
                        WorldPins::SdkModel::WorldPinInteriorData m_worldPinInteriorData;
                        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        
                        ExampleCurrentTourCardTappedHandler* m_pTourCardTappedHandler;
                    };
                }
            }
        }
    }
}