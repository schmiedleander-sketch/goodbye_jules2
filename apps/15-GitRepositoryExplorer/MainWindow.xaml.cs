using System.Collections.ObjectModel;
using Microsoft.UI.Xaml;

namespace GitRepositoryExplorer;

public sealed partial class MainWindow : Window
{
    private ObservableCollection<string> _commits = new();

    public MainWindow()
    {
        this.InitializeComponent();
        CommitList.ItemsSource = _commits;
        LoadMockGitLog();
    }

    private void OnReadLogClicked(object sender, RoutedEventArgs e) => LoadMockGitLog();

    private void LoadMockGitLog()
    {
        _commits.Clear();
        _commits.Add("[7c9590c] Initial commit - Setup repository structure");
        _commits.Add("[a1b2c3d] feat: Windows App SDK 1.6 package integration");
        _commits.Add("[e4f5g6h] feat: GACL DirectStorage texture conditioning pipeline");
        _commits.Add("[i7j8k9l] docs: Add comprehensive app suite overview");
    }
}
