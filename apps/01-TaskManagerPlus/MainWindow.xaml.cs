using System;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace TaskManagerPlus;

public class ProcessItem
{
    public int Id { get; set; }
    public string ProcessName { get; set; } = string.Empty;
    public string MemoryMB { get; set; } = "0";
    public int ThreadsCount { get; set; }
    public string StartTime { get; set; } = string.Empty;
}

public sealed partial class MainWindow : Window
{
    private ObservableCollection<ProcessItem> _allProcesses = new();
    private ObservableCollection<ProcessItem> _filteredProcesses = new();

    public MainWindow()
    {
        this.InitializeComponent();
        ProcessListView.ItemsSource = _filteredProcesses;
        LoadProcesses();
    }

    private void LoadProcesses()
    {
        try
        {
            _allProcesses.Clear();
            long totalMemBytes = 0;
            var procList = Process.GetProcesses();

            foreach (var p in procList)
            {
                long mem = 0;
                int threads = 0;
                string startTimeStr = "N/A";
                try
                {
                    mem = p.WorkingSet64;
                    totalMemBytes += mem;
                    threads = p.Threads.Count;
                    startTimeStr = p.StartTime.ToString("HH:mm:ss");
                }
                catch { }

                _allProcesses.Add(new ProcessItem
                {
                    Id = p.Id,
                    ProcessName = p.ProcessName,
                    MemoryMB = (mem / (1024.0 * 1024.0)).ToString("F2"),
                    ThreadsCount = threads,
                    StartTime = startTimeStr
                });
            }

            TxtTotalProcesses.Text = _allProcesses.Count.ToString();
            TxtTotalMemory.Text = (totalMemBytes / (1024.0 * 1024.0)).ToString("F0") + " MB";
            ApplyFilter();
            TxtStatus.Text = $"Loaded {_allProcesses.Count} active processes at {DateTime.Now:HH:mm:ss}";
        }
        catch (Exception ex)
        {
            TxtStatus.Text = $"Error: {ex.Message}";
        }
    }

    private void ApplyFilter()
    {
        var query = TxtSearch?.Text?.Trim().ToLowerInvariant() ?? "";
        _filteredProcesses.Clear();
        foreach (var p in _allProcesses.Where(p => string.IsNullOrEmpty(query) || p.ProcessName.ToLowerInvariant().Contains(query)))
        {
            _filteredProcesses.Add(p);
        }
    }

    private void OnRefreshClicked(object sender, RoutedEventArgs e) => LoadProcesses();

    private void OnSearchTextChanged(object sender, TextChangedEventArgs e) => ApplyFilter();

    private void OnEndTaskClicked(object sender, RoutedEventArgs e)
    {
        if (ProcessListView.SelectedItem is ProcessItem item)
        {
            try
            {
                var proc = Process.GetProcessById(item.Id);
                proc.Kill();
                TxtStatus.Text = $"Terminated process {item.ProcessName} (PID {item.Id})";
                LoadProcesses();
            }
            catch (Exception ex)
            {
                TxtStatus.Text = $"Failed to kill process: {ex.Message}";
            }
        }
        else
        {
            TxtStatus.Text = "Please select a process to terminate.";
        }
    }
}
