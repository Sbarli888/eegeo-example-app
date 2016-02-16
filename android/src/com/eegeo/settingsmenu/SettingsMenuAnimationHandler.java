// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.settingsmenu;

import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuAnimationHandler;
import com.eegeo.menu.MenuView;
import com.eegeo.menu.ViewXAnimatorUpdateListener;
import com.eegeo.mobileexampleapp.R;

public class SettingsMenuAnimationHandler extends MenuAnimationHandler
{
	protected final int m_stateChangeAnimationTimeMilliseconds = 300;
	
	public SettingsMenuAnimationHandler(MainActivity mainActivity, View view, MenuView menuView)
	{
		super(mainActivity, view, menuView);
	}
	
	@Override
	protected void InitializeAnimators()
	{
		View listContainerView = m_view.findViewById(R.id.settings_menu_view_list_container);
		View dragTabView = m_view.findViewById(R.id.settings_menu_drag_tab_view);
		
		final RelativeLayout uiRoot = (RelativeLayout)m_mainActivity.findViewById(R.id.ui_container);
		
		int screenWidthPx = uiRoot.getWidth();
		
		int listContainerWidthPx = listContainerView.getWidth();
        int dragTabWidthPx = dragTabView.getWidth();
        
        int offScreenXPx = screenWidthPx;
        int closedOnScreenXPx = screenWidthPx - dragTabWidthPx;
        int openOnScreenXPx = screenWidthPx - dragTabWidthPx - listContainerWidthPx;
		
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
