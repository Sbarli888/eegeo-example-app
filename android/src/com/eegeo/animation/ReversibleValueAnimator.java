package com.eegeo.animation;

import android.animation.TimeInterpolator;
import android.animation.ValueAnimator;
import android.view.animation.AccelerateDecelerateInterpolator;

public class ReversibleValueAnimator extends ValueAnimator
{
	public static ReversibleValueAnimator ofInt(int... values)
	{
		ReversibleValueAnimator reversibleValueAnimator = new ReversibleValueAnimator();
		reversibleValueAnimator.setIntValues(values);
		
		return reversibleValueAnimator;
	}
	
	public static ReversibleValueAnimator ofFloat(float... values)
	{
		ReversibleValueAnimator reversibleValueAnimator = new ReversibleValueAnimator();
		reversibleValueAnimator.setFloatValues(values);
		
		return reversibleValueAnimator;
	}
	
	private ReversibleValueAnimator()
	{
		super();
		
		setInterpolator(new AccelerateDecelerateInterpolator());
	}
	
	@Override
	public void setInterpolator(TimeInterpolator value)
	{
		super.setInterpolator(new ReversibleTimeInterpolator(value));
	}
	
	public ReversibleTimeInterpolator getReversibleInterpolator()
	{
		return (ReversibleTimeInterpolator)super.getInterpolator();
	}
}
