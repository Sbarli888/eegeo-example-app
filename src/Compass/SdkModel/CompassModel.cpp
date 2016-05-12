// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassModel.h"
#include "EnvironmentFlatteningService.h"
#include "IAppCameraController.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "VectorMath.h"
#include "NavigationService.h"
#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "IAppModeModel.h"
#include "IAlertBoxFactory.h"
#include "IInteriorsNavigationService.h"
#include "InteriorsExplorerModel.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassModel::CompassModel(Eegeo::Location::NavigationService& navigationService,
                                       InteriorsNavigation::SdkModel::IInteriorsNavigationService& interiorsNavigationService,
                                       Eegeo::Location::ILocationService& locationService,
                                       ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                                       Metrics::IMetricsService& metricsService,
                                       InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorExplorerModel,
                                       AppModes::SdkModel::IAppModeModel& appModeModel,
                                       Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory)
                :m_navigationService(navigationService)
                ,m_interiorsNavigationService(interiorsNavigationService)
                ,m_locationService(locationService)
                ,m_cameraController(cameraController)
                ,m_metricsService(metricsService)
                , m_interiorExplorerModel(interiorExplorerModel)
                , m_appModeModel(appModeModel)
                , m_appModeChangedCallback(this, &CompassModel::OnAppModeChanged)
                , m_alertBoxFactory(alertBoxFactory)
                , m_failAlertHandler(this, &CompassModel::OnFailedToGetLocation)
                , m_exitInteriorTriggered(false)
            {
                m_compassGpsModeToNavigationGpsMode[Eegeo::Location::NavigationService::GpsModeOff] = GpsMode::GpsDisabled;
                m_compassGpsModeToNavigationGpsMode[Eegeo::Location::NavigationService::GpsModeFollow] = GpsMode::GpsFollow;
                m_compassGpsModeToNavigationGpsMode[Eegeo::Location::NavigationService::GpsModeCompass] = GpsMode::GpsCompassMode;

                m_navigationGpsModeToCompassGpsMode[GpsMode::GpsDisabled] = Eegeo::Location::NavigationService::GpsModeOff;
                m_navigationGpsModeToCompassGpsMode[GpsMode::GpsFollow] = Eegeo::Location::NavigationService::GpsModeFollow;
                m_navigationGpsModeToCompassGpsMode[GpsMode::GpsCompassMode] = Eegeo::Location::NavigationService::GpsModeCompass;
                
                m_gpsModeToString[GpsMode::GpsDisabled] = "GpsDisabled";
                m_gpsModeToString[GpsMode::GpsFollow] = "GpsFollow";
                m_gpsModeToString[GpsMode::GpsCompassMode] = "GpsCompassMode";
                
                
                m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
            }

            CompassModel::~CompassModel()
            {
                m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            }

            bool CompassModel::GetGpsModeActive() const
            {
                return GetGpsMode() != GpsMode::GpsDisabled;
            }

            GpsMode::Values CompassModel::GetGpsMode() const
            {
                return m_gpsMode;
            }

            void CompassModel::CycleToNextGpsMode()
            {
                if(!m_locationService.GetIsAuthorized())
                {
                    DisableGpsMode();
                    m_gpsModeUnauthorizedCallbacks.ExecuteCallbacks();
                    return;
                }
                
                Eegeo::Space::LatLong latlong = Eegeo::Space::LatLong::FromDegrees(0.0, 0.0);
                if(!m_locationService.GetLocation(latlong))
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain location",
                                                                 "Could not get the device location. Please ensure you have GPS enabled",
                                                                 m_failAlertHandler);
                    DisableGpsMode();
                    return;
                }
                
                int gpsMode = static_cast<int>(m_gpsMode);
                gpsMode = (gpsMode + 1) % static_cast<int>(GpsMode::GpsMode_Max);
                GpsMode::Values newGpsMode = static_cast<GpsMode::Values>(gpsMode);

                if(GetGpsModeActive() && newGpsMode == GpsMode::GpsDisabled)
                {
                    m_gpsMode = newGpsMode;
                    CycleToNextGpsMode();
                }
                else
                {
                    SetGpsMode(newGpsMode);
                }
            }
            
            bool CompassModel::NeedsToExitInterior(GpsMode::Values gpsMode)
            {
                const AppModes::SdkModel::AppMode appMode = m_appModeModel.GetAppMode();
                return ((appMode != AppModes::SdkModel::WorldMode) &&
                        !m_exitInteriorTriggered &&
                        (gpsMode != GpsMode::GpsDisabled) &&
                        !m_interiorsNavigationService.IsPositionInInterior());
            }

            void CompassModel::TryUpdateToNavigationServiceGpsMode(Eegeo::Location::NavigationService::GpsMode value)
            {
                if(!m_locationService.GetIsAuthorized())
                {
                    DisableGpsMode();
                    return;
                }
                
                GpsMode::Values gpsModeValueFromNavigationService = m_compassGpsModeToNavigationGpsMode[value];
                // override value if we know we are using navigation service
                if(m_exitInteriorTriggered)
                {
                    gpsModeValueFromNavigationService = m_compassGpsModeToNavigationGpsMode[m_navigationService.GetGpsMode()];
                }
                
                bool forceSetGpsMode = false;
                const AppModes::SdkModel::AppMode appMode = m_appModeModel.GetAppMode();
                
                if (NeedsToExitInterior(gpsModeValueFromNavigationService))
                {
                    m_interiorExplorerModel.Exit();
                    m_exitInteriorTriggered = true;
                    forceSetGpsMode = true;
                }
                else if (appMode == AppModes::SdkModel::WorldMode)
                {
                    m_exitInteriorTriggered = false;
                }
                
                if(forceSetGpsMode || gpsModeValueFromNavigationService != GetGpsMode())
                {
                    SetGpsMode(gpsModeValueFromNavigationService);
                }
            }

            void CompassModel::DisableGpsMode()
            {
            	if (GetGpsMode() != GpsMode::GpsDisabled)
            	{
            		SetGpsMode(GpsMode::GpsDisabled);
            	}
            }

            void CompassModel::SetGpsMode(GpsMode::Values gpsMode)
            {
                m_gpsMode = gpsMode;
                
                const AppModes::SdkModel::AppMode appMode = m_appModeModel.GetAppMode();
                if (appMode == AppModes::SdkModel::WorldMode || m_exitInteriorTriggered)
                {
                    m_navigationService.SetGpsMode(m_navigationGpsModeToCompassGpsMode[gpsMode]);
                    m_interiorsNavigationService.SetGpsMode(m_navigationGpsModeToCompassGpsMode[GpsMode::GpsDisabled]);
                }
                else
                {
                    m_navigationService.SetGpsMode(m_navigationGpsModeToCompassGpsMode[GpsMode::GpsDisabled]);
                    m_interiorsNavigationService.SetGpsMode(m_navigationGpsModeToCompassGpsMode[gpsMode]);
                }
                
                m_metricsService.SetEvent("SetGpsMode", "GpsMode", m_gpsModeToString[m_gpsMode]);
                
                m_gpsModeChangedCallbacks.ExecuteCallbacks();
            }

            float CompassModel::GetHeadingRadians() const
            {
                const Eegeo::Camera::RenderCamera renderCamera = m_cameraController.GetRenderCamera();
                const Eegeo::m44& cameraModelMatrix = renderCamera.GetModelMatrix();

                const Eegeo::v3& viewDirection = cameraModelMatrix.GetRow(2);

                Eegeo::v3 ecefUp = renderCamera.GetEcefLocation().ToSingle().Norm();
                const float epsilon = 0.001f;
                Eegeo::v3 heading;
                if (Eegeo::Math::Abs(Eegeo::v3::Dot(viewDirection, ecefUp)) > (1.f - epsilon))
                {
                    const Eegeo::v3& viewUp = cameraModelMatrix.GetRow(1);
                    heading = viewUp;
                }
                else
                {
                    heading = viewDirection;
                }

                return Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(renderCamera.GetEcefLocation(), heading);
            }

            float CompassModel::GetHeadingDegrees() const
            {
                float headingRadians = GetHeadingRadians();
                return Eegeo::Math::Rad2Deg(headingRadians);
            }

            void CompassModel::InsertGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_gpsModeChangedCallbacks.AddCallback(callback);
            }

            void CompassModel::RemoveGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_gpsModeChangedCallbacks.RemoveCallback(callback);
            }
            
            void CompassModel::InsertGpsModeUnauthorizedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_gpsModeUnauthorizedCallbacks.AddCallback(callback);
            }
            
            void CompassModel::RemoveGpsModeUnauthorizedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_gpsModeUnauthorizedCallbacks.RemoveCallback(callback);
            }
            
            void CompassModel::OnAppModeChanged()
            {
                const AppModes::SdkModel::AppMode appMode = m_appModeModel.GetAppMode();
                if (appMode != AppModes::SdkModel::WorldMode)
                {
                    DisableGpsMode();
                    return;
                }
            }
            
            void CompassModel::OnFailedToGetLocation()
            {
                Eegeo_TTY("Failed to get comapass loation");
            }
        }
    }
}
