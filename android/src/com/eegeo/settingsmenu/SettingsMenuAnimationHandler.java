// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.settingsmenu;

import android.animation.ValueAnimator;
import android.view.View;
import android.widget.RelativeLayout;

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
		
		m_onScreenAnimator = ValueAnimator.ofInt(offScreenXPx, closedOnScreenXPx);
		m_onScreenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		m_onScreenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
		
		m_openAnimator = ValueAnimator.ofInt(closedOnScreenXPx, openOnScreenXPx);
		m_openAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		m_openAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
	}
}
