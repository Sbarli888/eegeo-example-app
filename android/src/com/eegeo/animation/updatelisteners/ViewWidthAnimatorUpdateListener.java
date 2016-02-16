package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;
import android.view.ViewGroup;

public class ViewWidthAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public ViewWidthAnimatorUpdateListener(View view)
	{
	    m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animator)
	{
		ViewGroup.LayoutParams layoutParams = m_view.getLayoutParams();
		layoutParams.width = (Integer)animator.getAnimatedValue();
		m_view.setLayoutParams(layoutParams);
	}
}
