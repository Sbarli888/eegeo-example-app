//
//  AndroidRouteMatchingExampleViewFactory.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__AndroidRouteMatchingExampleViewFactory__
#define __ExampleApp__AndroidRouteMatchingExampleViewFactory__

#include "Types.h"
#include "IRouteMatchingExampleViewFactory.h"
#include "AndroidNativeState.h"

namespace Examples
{
    class AndroidRouteMatchingExampleViewFactory : public IRouteMatchingExampleViewFactory, private Eegeo::NonCopyable
    {
    	AndroidNativeState& m_nativeState;

    public:
    	AndroidRouteMatchingExampleViewFactory(
    			AndroidNativeState& androidNativeState);
        
        virtual ~AndroidRouteMatchingExampleViewFactory();
        
        virtual IRouteMatchingExampleView* CreateRouteMatchingExampleView() const;
    };
}

#endif /* defined(__ExampleApp__AndroidRouteMatchingExampleViewFactory__) */
