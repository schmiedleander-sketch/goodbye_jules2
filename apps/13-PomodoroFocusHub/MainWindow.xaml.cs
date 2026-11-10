using System;
using Microsoft.UI.Xaml;

namespace PomodoroFocusHub;

public sealed partial class MainWindow : Window
{
    private DispatcherTimer _timer = new();
    private int _remainingSeconds = 25 * 60;
    private int _completedCount = 0;

    public MainWindow()
    {
        this.InitializeComponent();
        _timer.Interval = TimeSpan.FromSeconds(1);
        _timer.Tick += (s, e) =>
        {
            if (_remainingSeconds > 0)
            {
                _remainingSeconds--;
                UpdateDisplay();
            }
            else
            {
                _timer.Stop();
                _completedCount++;
                TxtCompleted.Text = $"Completed Sessions: {_completedCount}";
                _remainingSeconds = 25 * 60;
                UpdateDisplay();
            }
        };
    }

    private void UpdateDisplay()
    {
        int min = _remainingSeconds / 60;
        int sec = _remainingSeconds % 60;
        TxtTimer.Text = $"{min:D2}:{sec:D2}";
    }

    private void OnStartClicked(object sender, RoutedEventArgs e) => _timer.Start();
    private void OnPauseClicked(object sender, RoutedEventArgs e) => _timer.Stop();
    private void OnResetClicked(object sender, RoutedEventArgs e)
    {
        _timer.Stop();
        _remainingSeconds = 25 * 60;
        UpdateDisplay();
    }
}
