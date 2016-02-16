// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.animation.ValueAnimator;
import android.view.View;

import com.eegeo.animation.ReversibleAnimatorSet;
import com.eegeo.animation.ReversibleValueAnimator;
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
        
        ReversibleValueAnimator onScreenAnimator = ReversibleValueAnimator.ofInt(offScreenXPx, closedOnScreenXPx);
		onScreenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		onScreenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
		
		m_onScreenAnimatorSet.addAnimator(onScreenAnimator);
		
		ReversibleValueAnimator openAnimator = ReversibleValueAnimator.ofInt(closedOnScreenXPx, openOnScreenXPx);
		openAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		openAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
		
		m_openAnimatorSet.addAnimator(openAnimator);
	}
}
