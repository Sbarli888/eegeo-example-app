// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.view.View;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;

public class SearchResultsScrollListener implements OnScrollListener
{
	private Button m_searchResultsScrollButton;
	private ImageView m_searchResultsFade;
	private boolean m_searchResultsScrollable;
	
	public SearchResultsScrollListener(Button button, ImageView imageView, boolean scrollable) 
	{
		m_searchResultsScrollButton = button;
		m_searchResultsFade = imageView;
		m_searchResultsScrollable = scrollable;
	}
	
	public void UpdateScrollable(boolean scrollable)
	{
		m_searchResultsScrollable = scrollable;
	}

	@Override
	public void onScrollStateChanged(AbsListView view, int scrollState) 
	{
		
	}
	@Override
	public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) 
	{	
		if(totalItemCount == 0)
			return;
	
		View lastChild = (View) view.getChildAt(view.getChildCount() - 1);
		
	    boolean childAlignsWithBottomofView = false;
		if(lastChild.getBottom() - (view.getHeight() + view.getScrollY()) == 0)
		{
				childAlignsWithBottomofView = true;
		}
	    
	    final int lastItem = firstVisibleItem + visibleItemCount;

	    if( childAlignsWithBottomofView && lastItem == totalItemCount)
	    {
	    	m_searchResultsFade.setVisibility(view.INVISIBLE);
			m_searchResultsScrollButton.setVisibility(view.INVISIBLE);
	    }
		else if (m_searchResultsScrollable)
		{
			m_searchResultsFade.setVisibility(view.VISIBLE);
			m_searchResultsScrollButton.setVisibility(view.VISIBLE);
		}       
	}
}
