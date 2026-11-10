using System.Collections.ObjectModel;
using Microsoft.UI.Xaml;

namespace BatchRenamePro;

public sealed partial class MainWindow : Window
{
    private ObservableCollection<string> _previewItems = new();

    public MainWindow()
    {
        this.InitializeComponent();
        PreviewList.ItemsSource = _previewItems;
        GeneratePreview();
    }

    private void OnPreviewClicked(object sender, RoutedEventArgs e) => GeneratePreview();

    private void GeneratePreview()
    {
        _previewItems.Clear();
        string prefix = TxtPrefix.Text;
        string suffix = TxtSuffix.Text;
        int.TryParse(TxtStartNum.Text, out int start);

        string[] sampleFiles = { "photo_vacation.jpg", "document_scan.pdf", "data_export.csv", "texture_diffuse.png", "audio_track.wav" };

        for (int i = 0; i < sampleFiles.Length; i++)
        {
            var oldName = sampleFiles[i];
            var ext = System.IO.Path.GetExtension(oldName);
            var newName = $"{prefix}{start + i:D3}{suffix}{ext}";
            _previewItems.Add($"{oldName}  --->  {newName}");
        }
    }
}
