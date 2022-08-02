using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace ZINISCourseProject
{
    public class Threefish : SymmetricAlgorithm
    {
        private const int DefaultCipherSize = 256;
        private ulong[] tweak;

        public Threefish()
        {
            // Set up supported key and block sizes for Threefish
            KeySizes[] supportedSizes =
            {
                new KeySizes(256, 512, 256),
                new KeySizes(1024, 1024, 0)
            };
            LegalBlockSizesValue = supportedSizes;
            LegalKeySizesValue = supportedSizes;
            // Set up default sizes
            KeySizeValue = DefaultCipherSize;
            BlockSizeValue = DefaultCipherSize;
            FeedbackSizeValue = DefaultCipherSize / 2;
            // CBC is the default for the other symmetric ciphers in the standard library.
            ModeValue = CipherMode.CBC;
        }

        public void SetTweak(ulong[] newTweak)
        {
            if (newTweak.Length != 2)
                throw new ArgumentException("Tweak must be an array of two unsigned 64-bit integers.");
            tweak = newTweak;
        }

        public override ICryptoTransform CreateDecryptor(byte[] rgbKey, byte[] rgbIV)
        {
            var tsm = new ThreefishTransform(rgbKey, rgbIV, FeedbackSize,
                ThreefishTransformMode.Decrypt, ModeValue, PaddingValue);
            if (tweak != null)
                tsm.InternalSetTweak(tweak);
            return tsm;
        }

        public override ICryptoTransform CreateEncryptor(byte[] rgbKey, byte[] rgbIV)
        {
            var tsm = new ThreefishTransform(rgbKey, rgbIV, FeedbackSize,
                ThreefishTransformMode.Encrypt, ModeValue, PaddingValue);
            if (tweak != null)
                tsm.InternalSetTweak(tweak);
            return tsm;
        }

        public override void GenerateIV()
        { IVValue = GenerateRandomBytes(BlockSizeValue / 8); }

        public override void GenerateKey()
        { KeyValue = GenerateRandomBytes(KeySizeValue / 8); }

        private static byte[] GenerateRandomBytes(int amount)
        {
            var rngCrypto = new RNGCryptoServiceProvider();
            var bytes = new byte[amount];
            rngCrypto.GetBytes(bytes);
            return bytes;
        }
    }
}
