using System;
using System.Text.Json;
using System.Xml.Linq;
using Microsoft.UI.Xaml;

namespace JsonXmlForge;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        TxtInput.Text = "{\"name\":\"WindowsAppSDK\",\"version\":\"1.6\",\"tags\":[\"desktop\",\"xaml\",\"winui3\"]}";
    }

    private void OnPrettifyJsonClicked(object sender, RoutedEventArgs e)
    {
        try
        {
            var doc = JsonDocument.Parse(TxtInput.Text);
            TxtOutput.Text = JsonSerializer.Serialize(doc.RootElement, new JsonSerializerOptions { WriteIndented = true });
            TxtStatus.Text = "JSON formatted and validated successfully.";
        }
        catch (Exception ex)
        {
            TxtStatus.Text = $"JSON Syntax Error: {ex.Message}";
        }
    }

    private void OnPrettifyXmlClicked(object sender, RoutedEventArgs e)
    {
        try
        {
            var doc = XDocument.Parse(TxtInput.Text);
            TxtOutput.Text = doc.ToString();
            TxtStatus.Text = "XML formatted and validated successfully.";
        }
        catch (Exception ex)
        {
            TxtStatus.Text = $"XML Syntax Error: {ex.Message}";
        }
    }

    private void OnMinifyClicked(object sender, RoutedEventArgs e)
    {
        try
        {
            var raw = TxtInput.Text.Replace("\r", "").Replace("\n", "").Replace("  ", " ").Trim();
            TxtOutput.Text = raw;
            TxtStatus.Text = $"Minified to {raw.Length} characters.";
        }
        catch (Exception ex)
        {
            TxtStatus.Text = ex.Message;
        }
    }

    private void OnClearClicked(object sender, RoutedEventArgs e)
    {
        TxtInput.Text = "";
        TxtOutput.Text = "";
        TxtStatus.Text = "Cleared.";
    }
}
