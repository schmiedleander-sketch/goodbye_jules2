using System;
using System.IO;
using Microsoft.UI.Xaml;

namespace AudioWaveLab;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
        SliderFreq.ValueChanged += (s, e) => TxtFreqDisplay.Text = $"{(int)SliderFreq.Value} Hz";
        SliderDuration.ValueChanged += (s, e) => TxtDurationDisplay.Text = $"{(int)SliderDuration.Value} Seconds";
    }

    private void OnGenerateWavClicked(object sender, RoutedEventArgs e)
    {
        try
        {
            int sampleRate = 44100;
            short channels = 1;
            short bitsPerSample = 16;
            double freq = SliderFreq.Value;
            double duration = SliderDuration.Value;
            int numSamples = (int)(sampleRate * duration);
            int dataChunkSize = numSamples * channels * (bitsPerSample / 8);

            string outPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), $"tone_{freq:F0}Hz.wav");

            using (var stream = new FileStream(outPath, FileMode.Create))
            using (var writer = new BinaryWriter(stream))
            {
                // RIFF chunk
                writer.Write(new char[] { 'R', 'I', 'F', 'F' });
                writer.Write(36 + dataChunkSize);
                writer.Write(new char[] { 'W', 'A', 'V', 'E' });

                // fmt chunk
                writer.Write(new char[] { 'f', 'm', 't', ' ' });
                writer.Write(16); // subchunk size
                writer.Write((short)1); // PCM
                writer.Write(channels);
                writer.Write(sampleRate);
                writer.Write(sampleRate * channels * (bitsPerSample / 8)); // byte rate
                writer.Write((short)(channels * (bitsPerSample / 8))); // block align
                writer.Write(bitsPerSample);

                // data chunk
                writer.Write(new char[] { 'd', 'a', 't', 'a' });
                writer.Write(dataChunkSize);

                for (int i = 0; i < numSamples; i++)
                {
                    double t = (double)i / sampleRate;
                    double sampleVal = Math.Sin(2 * Math.PI * freq * t);
                    if (ComboWaveType.SelectedIndex == 1) // Square
                        sampleVal = sampleVal >= 0 ? 0.8 : -0.8;
                    else if (ComboWaveType.SelectedIndex == 2) // Sawtooth
                        sampleVal = 2.0 * (t * freq - Math.Floor(t * freq + 0.5));

                    short sampleShort = (short)(sampleVal * short.MaxValue * 0.5);
                    writer.Write(sampleShort);
                }
            }

            TxtStatus.Text = $"Exported: {outPath} ({dataChunkSize / 1024} KB)";
        }
        catch (Exception ex)
        {
            TxtStatus.Text = $"Export error: {ex.Message}";
        }
    }
}
