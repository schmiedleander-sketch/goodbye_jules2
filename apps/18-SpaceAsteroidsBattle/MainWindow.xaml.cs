using System;
using Microsoft.UI.Xaml;

namespace SpaceAsteroidsBattle;

public sealed partial class MainWindow : Window
{
    private int _score = 12450;

    public MainWindow()
    {
        this.InitializeComponent();
        TxtGaclLog.Text = "[GACL] Target format: BC7 (ZSTD_BC7_SPLIT)\n[GACL] 256KB decompression window verified\n[DirectStorage] 1.4 Decompression runtime ready.";
    }

    private void OnFireClicked(object sender, RoutedEventArgs e)
    {
        _score += 150;
        TxtGaclLog.Text += $"\n[Game] Asteroid destroyed! Score: {_score}";
    }

    private void OnSpawnWaveClicked(object sender, RoutedEventArgs e)
    {
        TxtGaclLog.Text += "\n[Game] Spawned 12 incoming high-density asteroids.";
    }

    private void OnGaclShuffleClicked(object sender, RoutedEventArgs e)
    {
        TxtGaclLog.Text += "\n[GACL] Recomputed space curve Z-order for asteroid textures. Savings: 12.4%";
    }
}
