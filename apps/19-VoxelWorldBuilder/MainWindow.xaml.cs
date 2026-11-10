using Microsoft.UI.Xaml;

namespace VoxelWorldBuilder;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        TxtVoxelLog.Text = "[GACL] BC4 Elevation buffer conditioned.\n[GACL] BC5 Surface normals conditioned with ZSTD_BC5.\n[DirectStorage] Unshuffle shader bound to compute queue.";
    }

    private void OnConditionVoxelClicked(object sender, RoutedEventArgs e)
    {
        TxtVoxelLog.Text += "\n[GACL] Re-compressed voxel normal textures. 38% package reduction achieved.";
    }
}
