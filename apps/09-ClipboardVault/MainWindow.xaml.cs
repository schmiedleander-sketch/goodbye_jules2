using System.Collections.ObjectModel;
using Microsoft.UI.Xaml;

namespace ClipboardVault;

public sealed partial class MainWindow : Window
{
    private ObservableCollection<string> _snippets = new();

    public MainWindow()
    {
        this.InitializeComponent();
        VaultList.ItemsSource = _snippets;

        _snippets.Add("git commit -m \"feat: modern WinUI 3 desktop integration\"");
        _snippets.Add("https://github.com/microsoft/WindowsAppSDK");
        _snippets.Add("Color.FromArgb(255, 0, 120, 212)");
    }

    private void OnAddClicked(object sender, RoutedEventArgs e)
    {
        var text = TxtNewSnippet.Text.Trim();
        if (!string.IsNullOrEmpty(text))
        {
            _snippets.Insert(0, text);
            TxtNewSnippet.Text = "";
        }
    }

    private void OnClearClicked(object sender, RoutedEventArgs e) => _snippets.Clear();
}
