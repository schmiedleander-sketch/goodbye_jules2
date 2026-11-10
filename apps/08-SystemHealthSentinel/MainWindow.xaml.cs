using System;
using System.IO;
using System.Text;
using Microsoft.UI.Xaml;

namespace SystemHealthSentinel;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        RefreshStats();
    }

    private void RefreshStats()
    {
        TxtOSVersion.Text = $"OS Version: {Environment.OSVersion}";
        TxtProcessorCount.Text = $"Logical CPU Cores: {Environment.ProcessorCount}";
        TxtMachineName.Text = $"Device: {Environment.MachineName} (User: {Environment.UserName})";
        TxtClrVersion.Text = $".NET CLR: {Environment.Version}";
        var uptimeSpan = TimeSpan.FromMilliseconds(Environment.TickCount64);
        TxtUptime.Text = $"System Uptime: {uptimeSpan.Days}d {uptimeSpan.Hours}h {uptimeSpan.Minutes}m";

        var sb = new StringBuilder();
        try
        {
            foreach (var d in DriveInfo.GetDrives())
            {
                if (d.IsReady)
                {
                    double freeGb = d.AvailableFreeSpace / (1024.0 * 1024 * 1024);
                    double totalGb = d.TotalSize / (1024.0 * 1024 * 1024);
                    sb.AppendLine($"Drive {d.Name} ({d.DriveFormat})");
                    sb.AppendLine($"  Volume: {d.VolumeLabel}");
                    sb.AppendLine($"  Free: {freeGb:F1} GB / {totalGb:F1} GB ({((totalGb - freeGb) / totalGb * 100):F0}% used)");
                    sb.AppendLine();
                }
            }
        }
        catch (Exception ex)
        {
            sb.AppendLine($"Error reading drives: {ex.Message}");
        }
        TxtDrives.Text = sb.Length > 0 ? sb.ToString() : "No local drives available.";
    }

    private void OnRefreshClicked(object sender, RoutedEventArgs e) => RefreshStats();
}
