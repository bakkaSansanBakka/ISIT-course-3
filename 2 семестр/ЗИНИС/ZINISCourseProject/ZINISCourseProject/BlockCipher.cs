using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZINISCourseProject
{
    public abstract class BlockCipher
    {
        public int InputBlockLengthBits { get; private set; }

        public readonly int InputBlockLengthBytes;

        protected byte[] key;

        protected BlockCipher(byte[] key, int inputBlockLengthBits)
        {
            InputBlockLengthBits = inputBlockLengthBits;
            InputBlockLengthBytes = InputBlockLengthBits / 8;

            this.key = key;
        }

        public abstract long Encrypt(byte[] input, long offset, byte[] output, long outputOffset, long length);

        public abstract long Decrypt(byte[] input, long offset, byte[] output, long outputOffset, long length);
    }
}
