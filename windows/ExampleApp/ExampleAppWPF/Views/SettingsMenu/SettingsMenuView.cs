using ExampleApp;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace ExampleAppWPF
{
    public class SettingsMenuView : MenuView
    {
        private MenuListAdapter m_adapter;
        private ControlClickHandler m_menutItemHandler;

        static SettingsMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SettingsMenuView), new FrameworkPropertyMetadata(typeof(SettingsMenuView)));
        }

        public SettingsMenuView(IntPtr nativeCallerPointer) : base(nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            Loaded += SettingsMenuView_Loaded;
        }

        private void SettingsMenuView_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_menutItemHandler = new ControlClickHandler(OnSelectionChanged, m_list);

            m_menuIcon = (Button)GetTemplateChild("SecondaryMenuDragTabView");

            m_menuIcon.Click += OnIconClick;

            m_mainContainer = (Grid)GetTemplateChild("SecondaryMenuViewListContainer");

            var fadeInItemStoryboard = ((Storyboard)Template.Resources["FadeInNewItems"]).Clone();
            var fadeOutItemStoryboard = ((Storyboard)Template.Resources["FadeOutOldItems"]).Clone();

            m_menuViewContainer = (Grid)GetTemplateChild("SearchMenuViewContainer");
            m_backgroundRectangle = (Rectangle)GetTemplateChild("BackgroundRect");

            m_menuIcon = (Button)GetTemplateChild("SecondaryMenuDragTabView");
            m_menuIconGrid = (Grid)GetTemplateChild("SearchIconGrid");

            m_menuIcon.Click += OnIconClick;

            m_mainContainer = (Grid)GetTemplateChild("SerchMenuMainContainer");

            m_openSearchIconAnim = ((Storyboard)Template.Resources["OpenSearchViewIcon"]).Clone();
            m_closeSearchIconAnim = ((Storyboard)Template.Resources["CloseSearchViewIcon"]).Clone();

            m_openSearchContainerAnim = ((Storyboard)Template.Resources["OpenSearchContainer"]).Clone();
            m_closeSearchContainerAnim = ((Storyboard)Template.Resources["CloseSearchContainer"]).Clone();

            m_openBackgroundRect = ((Storyboard)Template.Resources["OpenBackgroundRect"]).Clone();
            m_closeBackgroundRect = ((Storyboard)Template.Resources["CloseBackgroundRect"]).Clone();

            m_adapter = new MenuListAdapter(false, m_list, fadeInItemStoryboard, fadeOutItemStoryboard, "SettingsMenuItemPanel");

            PerformLayout(null, null);
        }

        private void OnIconClick(object sender, RoutedEventArgs e)
        {
            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        private void OnSelectionChanged(object sender, MouseEventArgs e)
        {
            if (IsAnimating() || m_adapter.IsAnimating())
            {
                (sender as ListBox).SelectedItem = null;
                return;
            }

            var item = m_list.SelectedItem as SubMenuListItem;
            if (item != null)
            {
                var position = m_adapter.Children
                    .Select((_t, _i) => Tuple.Create(_t, _i))
                    .Where(_t => _t.Item1.Heading == item.Heading)
                    .Single().Item2;

                int sectionIndex = m_adapter.GetSectionIndex(position);
                int childIndex = m_adapter.GetItemIndex(position);

                MenuViewCLIMethods.SelectedItem(m_nativeCallerPointer, sectionIndex, childIndex);
            }
        }

        public override void AnimateToClosedOnScreen()
        {
            base.AnimateToClosedOnScreen();
            m_mainContainer.Visibility = Visibility.Hidden;
        }

        public override void AnimateToOpenOnScreen()
        {
            base.AnimateToOpenOnScreen();
            m_mainContainer.Visibility = Visibility.Visible;
        }

        private void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            
        }


        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(groups, groupsExpandable, groupToChildrenMap);

            var itemsSource = new List<SubMenuListItem>();

            var detailsList = groupToChildrenMap[groups[0]];

            foreach (var str in detailsList)
            {
                var jObject = JObject.Parse(str);
                var item = new SubMenuListItem(str, 0);
                itemsSource.Add(item);
            }

            m_list.ItemsSource = itemsSource;

            if (m_list.DataContext != m_adapter)
            {
                m_list.DataContext = m_adapter;
            }

        }
    }
}
