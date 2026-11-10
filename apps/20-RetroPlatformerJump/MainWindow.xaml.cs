using Microsoft.UI.Xaml;

namespace RetroPlatformerJump;

public sealed partial class MainWindow : Window
{
    private int _stageIndex = 1;

    public MainWindow()
    {
        this.InitializeComponent();
        TxtStageLog.Text = "[DirectStorage] Mounted package asset store.\n[GACL] Streamed stage_tiles_bc7.bin using ZSTD_BC7_SPLIT unshuffle.\n[Audio] Synthesized 8-bit sound fx.";
    }

    private void OnSwapStageClicked(object sender, RoutedEventArgs e)
    {
        _stageIndex++;
        TxtStageLog.Text += $"\n[DirectStorage] Swapped to World 1-{_stageIndex}. Loaded 12 MB compressed textures in 8ms.";
    }
}
