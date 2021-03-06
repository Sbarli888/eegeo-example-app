﻿using System;
using System.Windows;
using System.Windows.Media;
using ExampleApp;
using System.Windows.Media.Animation;
using System.Windows.Controls;
using System.Diagnostics;

namespace ExampleAppWPF
{
    class WatermarkView : ControlBase
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;

        private int m_stateChangeAnimationTimeMilliseconds = 200;
        private double m_yPosInactive;
        private double m_yPosActive;
        private bool m_isFirstLayout = true;

        private string m_imageAssetUrl;
        private string m_popupTitle;
        private string m_popupBody;
        private string m_webUrl;
        private bool m_shouldShowShadow;

        private Image m_imageView = null;
        private ControlClickHandler m_imageClickHandler = null;
        private bool m_isActive = false;

        static WatermarkView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(WatermarkView), new FrameworkPropertyMetadata(typeof(WatermarkView)));
        }

        public WatermarkView(IntPtr nativeCallerPointer, 
                             string imageAssetUrl,
                             string popupTitle,
                             string popupBody,
                             string webUrl,
                             bool shouldShowShadow)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);
            m_currentWindow.SizeChanged += OnLayoutChanged;
            Loaded += OnLayoutChanged;

            m_imageAssetUrl = imageAssetUrl;
            UpdateWatermarkData(imageAssetUrl, popupTitle, popupBody, webUrl, shouldShowShadow);

            Opacity = 0.8;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_imageView = (Image)GetTemplateChild("WatermarkImage");
            
            m_imageClickHandler = new ControlClickHandler(m_imageView, OnClick);
        }

        private void OnClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            DialogBox dialogBox = new DialogBox(m_popupTitle, m_popupBody, "Find Out More", "Later");
            dialogBox.Owner = m_currentWindow;

            m_currentWindow.SetOpacity(MainWindow.OpacityOnPopup);

            bool? result = dialogBox.ShowDialog();

            m_currentWindow.SetOpacity(1.0f);

            WatermarkCLI.OnSelected(m_nativeCallerPointer);

            if (result != null && result == true)
            {
                Process.Start(new ProcessStartInfo(m_webUrl));
            }
        }

        private void OnLayoutChanged(object sender, RoutedEventArgs e)
        {
            Point currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            double screenHeight = mainWindow.MainGrid.ActualHeight;
            double screenWidth = mainWindow.MainGrid.ActualWidth;

            double viewHeight = ActualHeight;
            double viewWidth = ActualWidth;

            const double margin = 23.0;
            m_yPosActive = screenHeight * 0.5 - (viewHeight * 0.5) - (margin);
            m_yPosInactive = screenHeight * 0.5 + viewHeight * 0.5;

            var transform = new TranslateTransform((screenWidth * 0.5) - (ActualWidth * 0.5), m_isActive ? m_yPosActive : m_yPosInactive);

            RenderTransform = transform;
        }

        void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void AnimateToInactive()
        {
            AnimateViewToY(m_yPosInactive);
            m_isActive = false;
        }

        public void AnimateToActive()
        {
            AnimateViewToY(m_yPosActive);
            m_isActive = true;
        }

        public void AnimateViewToY(double y)
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            var animation = new DoubleAnimation();
            animation.From = currentPosition.Y;
            animation.To = y;
            animation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));
            animation.EasingFunction = new SineEase();

            var transform = new TranslateTransform(currentPosition.X, currentPosition.Y);
            RenderTransform = transform;
            transform.BeginAnimation(TranslateTransform.YProperty, animation);
        }

        public void AnimateToIntermediateOnScreenState(float onScreenState)
        {
            Point currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            double viewY = currentPosition.Y;
            double newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;

            if (viewY != newY)
            {
                RenderTransform = new TranslateTransform(currentPosition.X, newY);
            }
        }

        public void UpdateWatermarkData(string imageAssetUrl,
                                        string popupTitle,
                                        string popupBody,
                                        string webUrl,
                                        bool shouldShowShadow)
        {
            m_popupTitle = popupTitle;
            m_popupBody = popupBody;
            m_webUrl = webUrl;
            m_shouldShowShadow = shouldShowShadow;

            bool shouldTransitionImage = imageAssetUrl != m_imageAssetUrl;

            if (shouldTransitionImage)
            {
                m_imageAssetUrl = imageAssetUrl;
                TransitionToNewImage();
            }
        }

        private void TransitionToNewImage()
        {
            string imageAssetPlusExtension = m_imageAssetUrl + ".png";
            var src = StartupResourceLoader.GetBitmap(imageAssetPlusExtension);

            if (src == null)
            {
                StartupResourceLoader.LoadImage(imageAssetPlusExtension);
                src = StartupResourceLoader.GetBitmap(imageAssetPlusExtension);
            }

            m_imageView.Source = src;
        }
    }
}
