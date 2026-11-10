using System;
using Microsoft.UI;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media;
using Windows.UI;

namespace DevPalette;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        UpdateColor();
    }

    private void OnColorChanged(object sender, RoutedEventArgs e) => UpdateColor();

    private void UpdateColor()
    {
        if (SliderR == null || SliderG == null || SliderB == null) return;

        byte r = (byte)SliderR.Value;
        byte g = (byte)SliderG.Value;
        byte b = (byte)SliderB.Value;
        var color = Color.FromArgb(255, r, g, b);

        ColorPreviewBox.Background = new SolidColorBrush(color);
        TxtHex.Text = $"#{r:X2}{g:X2}{b:X2}";
        TxtRgb.Text = $"rgb({r}, {g}, {b})";

        double cR = r / 255.0, cG = g / 255.0, cB = b / 255.0;
        double max = Math.Max(cR, Math.Max(cG, cB)), min = Math.Min(cR, Math.Min(cG, cB));
        double h = 0, s = 0, l = (max + min) / 2.0;
        if (max != min)
        {
            double d = max - min;
            s = l > 0.5 ? d / (2.0 - max - min) : d / (max + min);
            if (max == cR) h = (cG - cB) / d + (cG < cB ? 6 : 0);
            else if (max == cG) h = (cB - cR) / d + 2;
            else h = (cR - cG) / d + 4;
            h *= 60;
        }
        TxtHsl.Text = $"hsl({(int)h}, {(int)(s * 100)}%, {(int)(l * 100)}%)";

        // Relative luminance
        double Lum(double c) => c <= 0.03928 ? c / 12.92 : Math.Pow((c + 0.055) / 1.055, 2.4);
        double L = 0.2126 * Lum(cR) + 0.7152 * Lum(cG) + 0.0722 * Lum(cB);
        double contrastW = (1.0 + 0.05) / (L + 0.05);
        double contrastB = (L + 0.05) / (0.0 + 0.05);

        TxtContrastWhite.Text = $"Contrast against White (#FFFFFF): {contrastW:F2}:1 ({(contrastW >= 4.5 ? "PASS AA" : "FAIL")})";
        TxtContrastBlack.Text = $"Contrast against Black (#000000): {contrastB:F2}:1 ({(contrastB >= 4.5 ? "PASS AA" : "FAIL")})";
    }

    private void OnGeneratePaletteClicked(object sender, RoutedEventArgs e)
    {
        SwatchesPanel.Children.Clear();
        byte r = (byte)SliderR.Value;
        byte g = (byte)SliderG.Value;
        byte b = (byte)SliderB.Value;

        for (int i = 0; i < 5; i++)
        {
            byte nr = (byte)Math.Clamp(r + (i - 2) * 35, 0, 255);
            byte ng = (byte)Math.Clamp(g + (i - 2) * 20, 0, 255);
            byte nb = (byte)Math.Clamp(b + (i - 2) * 30, 0, 255);
            var swatch = new Border
            {
                Width = 60,
                Height = 60,
                CornerRadius = new CornerRadius(6),
                Background = new SolidColorBrush(Color.FromArgb(255, nr, ng, nb))
            };
            SwatchesPanel.Children.Add(swatch);
        }
    }
}
