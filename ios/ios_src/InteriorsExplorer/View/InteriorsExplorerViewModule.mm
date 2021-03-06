// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModule.h"
#include "ScreenProperties.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerViewInterop.h"
#include "InteriorsExplorerController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerViewModule::InteriorsExplorerViewModule(SdkModel::InteriorsExplorerModel& model,
                                                                     InteriorsExplorerViewModel& viewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                     Eegeo::Helpers::IdentityProvider& identityProvider)
            {
                const int screenWidth = screenProperties.GetScreenWidth();
                const int screenHeight = screenProperties.GetScreenHeight();
                const int pixelScale = screenProperties.GetPixelScale();
                
                m_pTutorialView = [[InteriorsExplorerTutorialView alloc] initWithParams: screenWidth : screenHeight : pixelScale];
                
                m_pView = [[InteriorsExplorerView alloc] initWithParams: screenWidth : screenHeight : pixelScale : *m_pTutorialView ];
                
                m_pController = Eegeo_NEW(InteriorsExplorerController)(model,
                                                                       *[m_pView getInterop],
                                                                       viewModel,
                                                                       messageBus);
            }
            
            InteriorsExplorerViewModule::~InteriorsExplorerViewModule()
            {
                Eegeo_DELETE m_pController;
                
                [m_pView release];
                
                [m_pTutorialView release];
            }
            
            InteriorsExplorerController& InteriorsExplorerViewModule::GetController() const
            {
                return *m_pController;
            }
            
            InteriorsExplorerView& InteriorsExplorerViewModule::GetView() const
            {
                return *m_pView;
            }
            
            InteriorsExplorerTutorialView& InteriorsExplorerViewModule::GetTutorialView() const
            {
                return *m_pTutorialView;
            }
        }
    }
}
