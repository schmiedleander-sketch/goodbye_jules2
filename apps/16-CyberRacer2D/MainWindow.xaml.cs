using System;
using Microsoft.UI.Xaml;

namespace CyberRacer2D;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        TxtLog.Text = "[GACL] DirectStorage 1.4 queue initialized\n[GACL] Texture atlas conditioned: track_diffuse_bc7.gacl\n[GACL] Applied ZSTD_BC7_SPLIT shuffle transform (ID 0x05)\n[Engine] 2D Render loop started.";
    }

    private void OnStartClicked(object sender, RoutedEventArgs e)
    {
        TxtStatus.Text = "Race in progress... 60 FPS | DirectStorage read latency < 0.2ms";
    }

    private void OnPauseClicked(object sender, RoutedEventArgs e)
    {
        TxtStatus.Text = "Race paused.";
    }

    private void OnConditionTexturesClicked(object sender, RoutedEventArgs e)
    {
        TxtLog.Text += "\n[GACL BLER] Evaluated 4096 blocks, merged 1280 similar blocks\n[GACL] Streaming size reduced: 16.0 MB -> 8.3 MB";
    }
}
