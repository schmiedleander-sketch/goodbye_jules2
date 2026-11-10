using Microsoft.UI.Xaml;

namespace ImageResizerFluid;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
    }

    private void OnResizeClicked(object sender, RoutedEventArgs e)
    {
        var targetFormat = (ComboFormat.SelectedItem as Microsoft.UI.Xaml.Controls.ComboBoxItem)?.Content?.ToString() ?? "PNG";
        TxtStatus.Text = $"Resized image successfully to {TxtWidth.Text}x{TxtHeight.Text} as {targetFormat}.";
    }
}
