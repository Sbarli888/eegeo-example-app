// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import android.animation.ValueAnimator;
import android.view.View;

import com.eegeo.entrypointinfrastructure.MainActivity;

public abstract class MenuAnimationHandler
{
	protected MainActivity m_mainActivity = null;
	protected View m_view;
	protected MenuView m_menuView;
	
	protected ValueAnimator m_onScreenAnimator = null;
	protected ValueAnimator m_openAnimator = null;
	
	final private float m_lowEndThreshold = 0.01f;
	final private float m_highEndThreshold = 0.99f;
	
	public MenuAnimationHandler(MainActivity mainActivity, View view, MenuView menuView)
	{
		m_mainActivity = mainActivity;
		m_view = view;
		m_menuView = menuView;
		
		InitializeAnimators();
	}
	
	protected abstract void InitializeAnimators();
	
	public void playToOffScreen()
	{
		m_onScreenAnimator.removeAllListeners();
		m_onScreenAnimator.addListener(new MenuOffScreenAnimatorListener(m_menuView));
		m_onScreenAnimator.setCurrentPlayTime(m_onScreenAnimator.getDuration());
		m_onScreenAnimator.reverse();
	}
	
	public void playToClosedOnScreen()
	{
		if(getOpenOnScreenState() > m_highEndThreshold)
		{
			m_openAnimator.removeAllListeners();
			m_openAnimator.addListener(new MenuClosedOnScreenAnimatorListener(m_menuView));
			m_openAnimator.setCurrentPlayTime(m_openAnimator.getDuration());
			m_openAnimator.reverse();
		}
		else
		{
			m_onScreenAnimator.removeAllListeners();
			m_onScreenAnimator.addListener(new MenuClosedOnScreenAnimatorListener(m_menuView));
			m_onScreenAnimator.setCurrentPlayTime(0);
			m_onScreenAnimator.start();
		}
	}
	
	public void playToOpenOnScreen()
	{
		m_openAnimator.removeAllListeners();
		m_openAnimator.addListener(new MenuOpenOnScreenAnimatorListener(m_menuView));
		m_openAnimator.setCurrentPlayTime(0);
		m_openAnimator.start();
	}
	
	public void setToIntermediateOnScreenState(float onScreenState)
	{
		m_onScreenAnimator.removeAllListeners();
		m_onScreenAnimator.setCurrentPlayTime((long)(onScreenState * m_onScreenAnimator.getDuration()));
	}
	
	public void setToIntermediateOpenState(float openState)
	{
		m_openAnimator.removeAllListeners();
		m_openAnimator.setCurrentPlayTime((long)(openState * m_openAnimator.getDuration()));
	}
	
	public float getOnScreenState()
	{
		return m_onScreenAnimator.getAnimatedFraction();
	}
	
	public float getOpenOnScreenState()
	{
		return m_openAnimator.getAnimatedFraction();
	}
	
	public boolean isOffScreen()
	{
		return getOnScreenState() < m_lowEndThreshold;
	}
	
	public boolean isClosedOnScreen()
	{
		return getOnScreenState() > m_highEndThreshold && getOpenOnScreenState() < m_lowEndThreshold;
	}
	
	public boolean isOpenOnScreen()
	{
		return getOpenOnScreenState() > m_highEndThreshold;
	}
}
