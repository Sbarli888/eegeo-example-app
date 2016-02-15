// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.animation.ValueAnimator;
import android.view.View;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuAnimationHandler;
import com.eegeo.menu.MenuView;
import com.eegeo.menu.ViewXAnimatorUpdateListener;
import com.eegeo.mobileexampleapp.R;

public class SearchMenuAnimationHandler extends MenuAnimationHandler
{
	protected final int m_stateChangeAnimationTimeMilliseconds = 300;
	
	public SearchMenuAnimationHandler(MainActivity mainActivity, View view, MenuView menuView)
	{
		super(mainActivity, view, menuView);
	}
	
	@Override
	protected void InitializeAnimators()
	{
		View listContainerView = m_view.findViewById(R.id.search_menu_view_list_container);
		View dragTabView = m_view.findViewById(R.id.search_menu_drag_button_view);
		
		int listContainerWidthPx = listContainerView.getWidth();
        int dragTabWidthPx = dragTabView.getWidth();
        
        int offScreenXPx = -listContainerWidthPx - dragTabWidthPx;
        int closedOnScreenXPx = -listContainerWidthPx;
        int openOnScreenXPx = 0;
        
        m_openAnimator = ValueAnimator.ofInt(closedOnScreenXPx, openOnScreenXPx);
		m_openAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		m_openAnimator.setCurrentPlayTime(0);
		m_openAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
		
		m_onScreenAnimator = ValueAnimator.ofInt(offScreenXPx, closedOnScreenXPx);
		m_onScreenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		m_onScreenAnimator.setCurrentPlayTime(0);
		m_onScreenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
	}
}
