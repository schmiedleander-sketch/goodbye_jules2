using System;
using System.Net.Http;
using Microsoft.UI.Xaml;

namespace RestApiClient;

public sealed partial class MainWindow : Window
{
    private static readonly HttpClient _httpClient = new HttpClient();

    public MainWindow()
    {
        this.InitializeComponent();
        _httpClient.DefaultRequestHeaders.UserAgent.ParseAdd("WindowsAppSDK-RestClient/1.0");
    }

    private async void OnSendClicked(object sender, RoutedEventArgs e)
    {
        var url = TxtUrl.Text.Trim();
        TxtStatus.Text = "Sending HTTP request...";
        try
        {
            var methodStr = (ComboMethod.SelectedItem as Microsoft.UI.Xaml.Controls.ComboBoxItem)?.Content?.ToString() ?? "GET";
            var request = new HttpRequestMessage(new HttpMethod(methodStr), url);
            var response = await _httpClient.SendAsync(request);

            var body = await response.Content.ReadAsStringAsync();
            TxtResponseBody.Text = body;
            TxtStatus.Text = $"Status: {(int)response.StatusCode} {response.StatusCode} | Size: {body.Length} characters";
        }
        catch (Exception ex)
        {
            TxtResponseBody.Text = "";
            TxtStatus.Text = $"HTTP Error: {ex.Message}";
        }
    }
}
