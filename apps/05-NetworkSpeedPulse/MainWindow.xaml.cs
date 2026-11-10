using System;
using System.Net.NetworkInformation;
using System.Text;
using Microsoft.UI.Xaml;

namespace NetworkSpeedPulse;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        LoadInterfaces();
    }

    private void LoadInterfaces()
    {
        var sb = new StringBuilder();
        foreach (var nic in NetworkInterface.GetAllNetworkInterfaces())
        {
            if (nic.OperationalStatus == OperationalStatus.Up)
            {
                sb.AppendLine($"Interface: {nic.Name}");
                sb.AppendLine($"  Type: {nic.NetworkInterfaceType}");
                sb.AppendLine($"  Speed: {nic.Speed / 1_000_000} Mbps");
                sb.AppendLine($"  Status: {nic.OperationalStatus}");
                sb.AppendLine();
            }
        }
        TxtInterfaceDetails.Text = sb.Length > 0 ? sb.ToString() : "No active network interfaces detected.";
    }

    private async void OnPingClicked(object sender, RoutedEventArgs e)
    {
        var host = TxtHost.Text.Trim();
        TxtLatency.Text = "Pinging...";
        try
        {
            using var ping = new Ping();
            var reply = await ping.SendPingAsync(host, 2000);
            if (reply.Status == IPStatus.Success)
            {
                TxtLatency.Text = $"{reply.RoundtripTime} ms";
                TxtPacketLoss.Text = $"Status: Success (TTL: {reply.Options?.Ttl})";
            }
            else
            {
                TxtLatency.Text = "Timeout";
                TxtPacketLoss.Text = $"Status: {reply.Status}";
            }
        }
        catch (Exception ex)
        {
            TxtLatency.Text = "Error";
            TxtPacketLoss.Text = ex.Message;
        }
    }
}
