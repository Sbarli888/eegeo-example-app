// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.settingsmenu;

import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.animation.updatelisteners.LeftMarginAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewWidthAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewXAnimatorUpdateListener;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuAnimationHandler;
import com.eegeo.menu.MenuView;
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
		View dragTabView = m_view.findViewById(R.id.settings_menu_drag_tab_view);
		View titleContainerView = m_view.findViewById(R.id.settings_menu_title_container);
		View listItemContainerView = m_view.findViewById(R.id.settings_menu_list_container);
		
		final RelativeLayout uiRoot = (RelativeLayout)m_mainActivity.findViewById(R.id.ui_container);
		
		int screenWidthPx = uiRoot.getWidth();
		
		int titleContainerWidthPx = titleContainerView.getWidth();
		RelativeLayout.LayoutParams listContainerLayout = (RelativeLayout.LayoutParams)listItemContainerView.getLayoutParams();
		int listContainerLeftMarginPx = listContainerLayout.leftMargin;
        int dragTabWidthPx = dragTabView.getWidth();
        
        int offScreenXPx = screenWidthPx;
        int closedOnScreenXPx = screenWidthPx - dragTabWidthPx - listContainerLeftMarginPx;
        int openOnScreenXPx = screenWidthPx - dragTabWidthPx - titleContainerWidthPx;
		
        ReversibleValueAnimator onScreenAnimator = ReversibleValueAnimator.ofInt(offScreenXPx, closedOnScreenXPx);
		onScreenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		onScreenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
		
		ReversibleValueAnimator onScreenTitleViewAnimator = ReversibleValueAnimator.ofInt(0, 0);
		onScreenTitleViewAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		onScreenTitleViewAnimator.addUpdateListener(new ViewWidthAnimatorUpdateListener(titleContainerView));
		
		ReversibleValueAnimator onScreenListViewAnimator = ReversibleValueAnimator.ofInt(listContainerLeftMarginPx, listContainerLeftMarginPx);
		onScreenListViewAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		onScreenListViewAnimator.addUpdateListener(new LeftMarginAnimatorUpdateListener(listItemContainerView));
		
		m_onScreenAnimatorSet.addAnimator(onScreenAnimator);
		m_onScreenAnimatorSet.addAnimator(onScreenTitleViewAnimator);
		m_onScreenAnimatorSet.addAnimator(onScreenListViewAnimator);
		
		ReversibleValueAnimator openAnimator = ReversibleValueAnimator.ofInt(closedOnScreenXPx, openOnScreenXPx);
		openAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		openAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(m_view));
		
		ReversibleValueAnimator openTitleViewAnimator = ReversibleValueAnimator.ofInt(0, titleContainerWidthPx);
		openTitleViewAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		openTitleViewAnimator.addUpdateListener(new ViewWidthAnimatorUpdateListener(titleContainerView));
		
		ReversibleValueAnimator openListViewAnimator = ReversibleValueAnimator.ofInt(listContainerLeftMarginPx, 0);
		openListViewAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		openListViewAnimator.addUpdateListener(new LeftMarginAnimatorUpdateListener(listItemContainerView));
		
		m_openAnimatorSet.addAnimator(openAnimator);
		m_openAnimatorSet.addAnimator(openTitleViewAnimator);
		m_openAnimatorSet.addAnimator(openListViewAnimator);
	}
}
