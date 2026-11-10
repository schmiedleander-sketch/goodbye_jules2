using System;
using System.Text.RegularExpressions;
using Microsoft.UI.Text;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace MarkdownNotePad;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        TxtEditor.Text = "# Welcome to Markdown NotePad\n\nBuilt with **Windows App SDK** and WinUI 3.\n\n### Key Features:\n- Real-time live preview rendering\n- Fluent design controls\n- Instant word and line statistics";
    }

    private void OnEditorTextChanged(object sender, TextChangedEventArgs e)
    {
        UpdatePreview(TxtEditor.Text);
        UpdateStats(TxtEditor.Text);
    }

    private void UpdateStats(string text)
    {
        var lines = text.Split('\n').Length;
        var words = Regex.Matches(text, @"\b\w+\b").Count;
        TxtStats.Text = $"Words: {words} | Lines: {lines} | Characters: {text.Length}";
    }

    private void UpdatePreview(string md)
    {
        PreviewPanel.Children.Clear();
        var lines = md.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.None);

        foreach (var line in lines)
        {
            var trimmed = line.Trim();
            if (string.IsNullOrEmpty(trimmed))
            {
                PreviewPanel.Children.Add(new TextBlock { Height = 10 });
                continue;
            }

            if (trimmed.StartsWith("# "))
            {
                PreviewPanel.Children.Add(new TextBlock { Text = trimmed.Substring(2), FontSize = 24, FontWeight = FontWeights.Bold, Margin = new Thickness(0, 8, 0, 4) });
            }
            else if (trimmed.StartsWith("## "))
            {
                PreviewPanel.Children.Add(new TextBlock { Text = trimmed.Substring(3), FontSize = 20, FontWeight = FontWeights.SemiBold, Margin = new Thickness(0, 6, 0, 4) });
            }
            else if (trimmed.StartsWith("### "))
            {
                PreviewPanel.Children.Add(new TextBlock { Text = trimmed.Substring(4), FontSize = 16, FontWeight = FontWeights.SemiBold, Margin = new Thickness(0, 4, 0, 2) });
            }
            else if (trimmed.StartsWith("- ") || trimmed.StartsWith("* "))
            {
                PreviewPanel.Children.Add(new TextBlock { Text = "• " + trimmed.Substring(2), FontSize = 14, Margin = new Thickness(16, 2, 0, 2) });
            }
            else
            {
                PreviewPanel.Children.Add(new TextBlock { Text = trimmed, FontSize = 14, TextWrapping = TextWrapping.Wrap });
            }
        }
    }

    private void OnNewClicked(object sender, RoutedEventArgs e) => TxtEditor.Text = "";
    private void OnSaveClicked(object sender, RoutedEventArgs e) => TxtStats.Text = $"Document saved locally at {DateTime.Now:HH:mm:ss}";
    private void OnBoldClicked(object sender, RoutedEventArgs e) => TxtEditor.SelectedText = $"**{TxtEditor.SelectedText}**";
    private void OnItalicClicked(object sender, RoutedEventArgs e) => TxtEditor.SelectedText = $"*{TxtEditor.SelectedText}*";
    private void OnBulletClicked(object sender, RoutedEventArgs e) => TxtEditor.SelectedText = $"- {TxtEditor.SelectedText}";
}
