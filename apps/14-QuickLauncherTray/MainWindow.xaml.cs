using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace QuickLauncherTray;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
    }

    private void OnLaunchTool(object sender, RoutedEventArgs e)
    {
        if (sender is Button btn)
        {
            var tool = btn.Content?.ToString();
            // In Windows, launches process; here safe notification
            Title = $"Quick Launcher Tray - Triggered: {tool}";
        }
    }
}
