// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.animation.CircleInOutTimeInterpolator;
import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.animation.updatelisteners.LeftMarginAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.RightMarginAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewWidthAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewXAnimatorUpdateListener;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuAnimationHandler;
import com.eegeo.menu.MenuView;
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
		View listContainerView = m_view.findViewById(R.id.search_menu_list_container);
		View dragTabView = m_view.findViewById(R.id.search_menu_drag_button_view);
		View titleContainerView = m_view.findViewById(R.id.search_menu_title_bar);
		
        int dragTabWidthPx = dragTabView.getWidth();
        int titleContainerWidthPx = titleContainerView.getWidth();
        
        m_view.setX(0.0f);
        
        int menuButtonMargin = (int) m_mainActivity.getResources().getDimension(R.dimen.menu_button_margin);
		
		ReversibleValueAnimator dragTobOnScreenAnimator = ReversibleValueAnimator.ofInt(-dragTabWidthPx, menuButtonMargin);
		dragTobOnScreenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		dragTobOnScreenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(dragTabView));
		
		ReversibleValueAnimator titleContainerOnScreenAnimator = ReversibleValueAnimator.ofInt(-titleContainerWidthPx, -titleContainerWidthPx);
		titleContainerOnScreenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		titleContainerOnScreenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(titleContainerView));
		
		ReversibleValueAnimator titleContainerOnScreenWidthAnimator = ReversibleValueAnimator.ofInt(0, 0);
		titleContainerOnScreenWidthAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		titleContainerOnScreenWidthAnimator.addUpdateListener(new ViewWidthAnimatorUpdateListener(titleContainerView));
		
		ReversibleValueAnimator listViewOnScreenAnimator = ReversibleValueAnimator.ofInt(-titleContainerWidthPx, -titleContainerWidthPx);
		listViewOnScreenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		listViewOnScreenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(listContainerView));
		
		m_onScreenAnimatorSet.addAnimator(dragTobOnScreenAnimator);
		m_onScreenAnimatorSet.addAnimator(titleContainerOnScreenAnimator);
		m_onScreenAnimatorSet.addAnimator(titleContainerOnScreenWidthAnimator);
		m_onScreenAnimatorSet.addAnimator(listViewOnScreenAnimator);
		
		ReversibleValueAnimator dragTobOpenAnimator = ReversibleValueAnimator.ofInt(menuButtonMargin, titleContainerWidthPx);
		dragTobOpenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		dragTobOpenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(dragTabView));
		
		ReversibleValueAnimator titleContainerOpenAnimator = ReversibleValueAnimator.ofInt(menuButtonMargin, 0);
		titleContainerOpenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		titleContainerOpenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(titleContainerView));
		
		ReversibleValueAnimator titleContainerOpenWidthAnimator = ReversibleValueAnimator.ofInt(0, titleContainerWidthPx);
		titleContainerOpenWidthAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		titleContainerOpenWidthAnimator.addUpdateListener(new ViewWidthAnimatorUpdateListener(titleContainerView));
		
		ReversibleValueAnimator listViewOpenAnimator = ReversibleValueAnimator.ofInt(-titleContainerWidthPx, 0);
		listViewOpenAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		listViewOpenAnimator.addUpdateListener(new ViewXAnimatorUpdateListener(listContainerView));
		
		m_openAnimatorSet.addAnimator(dragTobOpenAnimator);
		m_openAnimatorSet.addAnimator(titleContainerOpenAnimator);
		m_openAnimatorSet.addAnimator(titleContainerOpenWidthAnimator);
		m_openAnimatorSet.addAnimator(listViewOpenAnimator);
	}
}
