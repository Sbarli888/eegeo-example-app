// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

@class MenuView;

@interface CustomTableView : UITableView

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
                    container:(UIScrollView*)container
                     menuView:(MenuView*)menuView
                  hasSubMenus:(bool)hasSubMenus
                    cellWidth:(float)cellWidth
                    cellInset:(float)cellInset;

- (BOOL)hasDynamicCellPresentation;

- (BOOL)isAnimating;

- (void)updateAnimation:(double)deltaSeconds;

- (float)getCellWidth;

- (float)getCellInset;

@property (nonatomic, retain) UIView* pBackgroundView;

@end
