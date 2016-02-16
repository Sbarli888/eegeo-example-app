package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;
import android.view.ViewGroup.MarginLayoutParams;

public class RightMarginAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public RightMarginAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animation)
	{
		MarginLayoutParams marginLayoutParams = (MarginLayoutParams)m_view.getLayoutParams();
		marginLayoutParams.rightMargin = (Integer)(animation.getAnimatedValue());
		m_view.setLayoutParams(marginLayoutParams);
	}
}
