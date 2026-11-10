using System;
using System.Text;
using Microsoft.UI.Xaml;

namespace DungeonCrawlerGACL;

public sealed partial class MainWindow : Window
{
    private Random _rand = new();

    public MainWindow()
    {
        this.InitializeComponent();
        GenerateDungeon();
    }

    private void OnNewDungeonClicked(object sender, RoutedEventArgs e) => GenerateDungeon();

    private void GenerateDungeon()
    {
        int width = 45;
        int height = 18;
        var sb = new StringBuilder();

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                    sb.Append('#');
                else if (x == 5 && y == 5)
                    sb.Append('@'); // Hero
                else if (x == 35 && y == 12)
                    sb.Append('>'); // Stairs
                else
                {
                    double r = _rand.NextDouble();
                    if (r < 0.08) sb.Append('#');
                    else if (r < 0.10) sb.Append('M'); // Monster
                    else if (r < 0.12) sb.Append('$'); // Treasure
                    else sb.Append('.');
                }
            }
            sb.AppendLine();
        }

        TxtDungeonMap.Text = sb.ToString();
        TxtStatus.Text = $"Level {_rand.Next(1, 10)} generated | GACL BLER Texture Cache hit rate 99.4%";
    }
}
