using System;
using System.Runtime.InteropServices;

namespace GameAssetConditioning;

/// <summary>
/// GACL (Game Asset Conditioning Library) native P/Invoke bindings.
/// Based on https://github.com/microsoft/Game-Asset-Conditioning-Library
/// Provides texture conditioning, Block-Level Entropy Reduction (BLER),
/// and DirectStorage shuffle transforms.
/// </summary>
public static class GaclNative
{
    public const string GaclDllName = "gacl.dll";

    public enum GaclShuffleTransform : uint
    {
        None = 0x00,
        BC1 = 0x01,
        BC3 = 0x02,
        BC4 = 0x03,
        BC5 = 0x04,
        BC7Split = 0x05, // DirectStorage 1.4 GA
        BC1_44 = 0x06,
        BC3_664 = 0x07,
        BC5_2266 = 0x08,
        BC7Join = 0x09,
        BC1_EX = 0x0B,
        BC2_EX = 0x0C,
        BC3_EX = 0x0D,
        BC4_EX = 0x0E,
        BC5_EX = 0x0F,
        BC7_EX = 0x10,
        AnySupported = 0xFFFFFFFD,
        AnyExperimental = 0xFFFFFFFE
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct ShuffleCompressParameters
    {
        public uint StructSize;
        public uint Width;
        public uint Height;
        public uint Format;
        public uint WindowSize; // DirectStorage clamp 256KB
        public float CompressionLevel;
    }

    [DllImport(GaclDllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "GACL_RDO_BlockLevelEntropyReduce")]
    private static extern void Native_GACL_RDO_BlockLevelEntropyReduce(
        uint numBlocks,
        IntPtr encodedData,
        uint bcElementSizeBytes,
        IntPtr decodedR8G8B8A8,
        float uniqueBlockReduce,
        float maxDistSq,
        float avgDistSq
    );

    [DllImport(GaclDllName, CallingConvention = CallingConvention.Cdecl, EntryPoint = "GACL_Shuffle_ApplySpaceCurve")]
    [return: MarshalAs(UnmanagedType.I1)]
    private static extern bool Native_GACL_Shuffle_ApplySpaceCurve(
        IntPtr dest,
        IntPtr src,
        nuint size,
        nuint elementSizeBytes,
        nuint widthInPixels,
        [MarshalAs(UnmanagedType.I1)] bool forward
    );

    /// <summary>
    /// Executes Block-Level Entropy Reduction (BLER) to unify visually similar 4x4 BCn blocks.
    /// Falls back to managed memory copy if unmanaged native binary is absent at development runtime.
    /// </summary>
    public static unsafe bool ApplyBLER(ReadOnlySpan<byte> sourceBlocks, Span<byte> outBlocks, float uniqueBlockReduce = 0.5f)
    {
        if (sourceBlocks.Length != outBlocks.Length) return false;
        try
        {
            fixed (byte* pSrc = sourceBlocks, pDst = outBlocks)
            {
                Native_GACL_RDO_BlockLevelEntropyReduce(
                    (uint)(sourceBlocks.Length / 16),
                    (IntPtr)pDst,
                    16,
                    IntPtr.Zero,
                    uniqueBlockReduce,
                    256.0f,
                    32.0f
                );
                return true;
            }
        }
        catch (DllNotFoundException)
        {
            sourceBlocks.CopyTo(outBlocks);
            return true;
        }
    }

    /// <summary>
    /// Transforms texture blocks into 16KB micro-tile space curve (Z-order) layout.
    /// </summary>
    public static unsafe bool ApplySpaceCurve(ReadOnlySpan<byte> source, Span<byte> dest, int widthPixels, int elementSizeBytes, bool forward)
    {
        if (source.Length != dest.Length) return false;
        try
        {
            fixed (byte* pSrc = source, pDst = dest)
            {
                return Native_GACL_Shuffle_ApplySpaceCurve((IntPtr)pDst, (IntPtr)pSrc, (nuint)source.Length, (nuint)elementSizeBytes, (nuint)widthPixels, forward);
            }
        }
        catch (DllNotFoundException)
        {
            source.CopyTo(dest);
            return true;
        }
    }
}
