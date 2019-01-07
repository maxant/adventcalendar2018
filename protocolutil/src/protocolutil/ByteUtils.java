package protocolutil;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class ByteUtils {
    public ByteUtils() {
    }

    private static byte[][] append(byte[][] var0, byte[] var1) {
        byte[][] var2 = new byte[var0.length + 1][];
        System.arraycopy(var0, 0, var2, 0, var0.length);
        var2[var0.length] = var1;
        return var2;
    }

    public static int bytesToColor(byte[] var0) {
        return rgb(var0[0] & 255, var0[1] & 255, var0[2] & 255);
    }

    public static ArrayList<Integer> bytesToColors(byte[] var0) {
        ArrayList var2 = new ArrayList();

        for(int var1 = 0; var1 < var0.length / 3; ++var1) {
            byte[] var3 = new byte[3];
            System.arraycopy(var0, var1 * 3, var3, 0, 3);
            var2.add(bytesToColor(var3));
        }

        return var2;
    }

    public static int bytesToInt(byte var0, byte var1) {
        return (var0 & 255) << 8 | var1 & 255;
    }

    public static int bytesToInt(ByteOrder var0, byte[] var1) {
        ByteBuffer var2 = ByteBuffer.wrap(var1);
        var2.order(var0);
        return var2.getInt();
    }

    public static int bytesToInt(byte[] var0) {
        return bytesToInt(var0[0], var0[1]);
    }

    public static short bytesToShort(ByteOrder var0, byte[] var1) {
        ByteBuffer var2 = ByteBuffer.wrap(var1);
        var2.order(var0);
        return var2.getShort();
    }

    public static byte[] colorToBytes(int var0) {
        return new byte[]{(byte)red(var0), (byte)green(var0), (byte)blue(var0)};
    }

    public static byte[] colorsToBytes(ArrayList<Integer> var0) {
        ByteBuffer var2 = ByteBuffer.allocate(var0.size() * 3);

        for(int var1 = 0; var1 < var0.size(); ++var1) {
            var2.put(colorToBytes((Integer)var0.get(var1)));
        }

        return var2.array();
    }

    public static int crc16(byte[] var0) {
        int var5 = var0.length;
        int var2 = 0;

        int var1;
        for(var1 = 65535; var2 < var5 - 2; ++var2) {
            int var3 = var0[var2];

            for(int var4 = 0; var4 < 8; ++var4) {
                var1 = (new short[]{0, -24575})[(var1 ^ var3) & 1] & '\uffff' ^ var1 >> 1;
                var3 >>= 1;
            }
        }

        return var1;
    }

    public static void fillCrc(byte[] var0, int var1) {
        int var2 = var0.length - 2;
        var0[var2] = (byte)(var1 & 255);
        var0[var2 + 1] = (byte)(var1 >> 8 & 255);
    }

    public static int formatIntToHex(int var0) {
        return Integer.valueOf(String.valueOf(var0), 16);
    }

    public static boolean getBitInByte(byte var0, int var1) {
        return (var0 & (int)Math.pow(2.0D, (double)var1)) != 0;
    }

    public static String getBytesArrayAsString(byte[] var0) {
        String var2 = "";
        String var3;
        if (var0 != null) {
            int var1 = 0;

            while(true) {
                var3 = var2;
                if (var1 >= var0.length) {
                    break;
                }

                StringBuilder var4 = new StringBuilder();
                var4.append(var2);
                var4.append(" 0x");
                var4.append(formatIntToHex(var0[var1]));
                var2 = var4.toString();
                ++var1;
            }
        } else {
            var3 = "null";
        }

        return var3;
    }

    public static int getValueFromBitToBit(byte var0, int var1, int var2) {
        int var7 = 0;

        int var8;
        for(var8 = 0; var7 < var2; ++var7) {
            double var5 = (double)var8;
            double var3;
            if (getBitInByte(var0, var1 + var7)) {
                var3 = Math.pow(2.0D, (double)var7);
            } else {
                var3 = 0.0D;
            }

            Double.isNaN(var5);
            var8 = (int)(var5 + var3);
        }

        return var8;
    }

    public static byte[] intToBytes(ByteOrder var0, int var1) {
        ByteBuffer var2 = ByteBuffer.allocate(4);
        var2.order(var0);
        var2.putInt(var1);
        return var2.array();
    }

    public static byte[] reverse(byte[] var0) {
        byte[] var2 = new byte[var0.length];

        for(int var1 = 0; var1 < var2.length; ++var1) {
            var2[var1] = var0[var0.length - 1 - var1];
        }

        return var2;
    }

    public static byte setBitInByte(byte var0, int var1, boolean var2) {
        int var6 = 0;

        byte var3;
        for(var3 = 0; var6 < 8; ++var6) {
            double var4 = 0.0D;
            if (var6 == var1) {
                if (var2) {
                    var4 = Math.pow(2.0D, (double)var6);
                }

                var3 += (byte)((int)var4);
            } else {
                if (getBitInByte(var0, var6)) {
                    var4 = Math.pow(2.0D, (double)var6);
                }

                var3 += (byte)((int)var4);
            }
        }

        return var3;
    }

    public static byte setValueFromBitToBit(byte var0, int var1, int var2, int var3, int var4) {
        int var6 = 0;

        byte var5;
        for(var5 = 0; var6 < 8; ++var6) {
            if (var6 >= var1 && var6 < var1 + var2) {
                boolean var7;
                if (((int)Math.pow(2.0D, (double)(var6 + var4 - var1)) & var3) != 0) {
                    var7 = true;
                } else {
                    var7 = false;
                }

                var5 = setBitInByte(var5, var6, var7);
            } else {
                var5 = setBitInByte(var5, var6, getBitInByte(var0, var6));
            }
        }

        return var5;
    }

    public static byte[] shortToBytes(ByteOrder var0, short var1) {
        ByteBuffer var2 = ByteBuffer.allocate(2);
        var2.order(var0);
        var2.putShort(var1);
        return var2.array();
    }

    public static byte[][] split(byte[] var0, byte[] var1) {
        int var3 = -1;
        byte[][] var7 = new byte[0][];

        int var2;
        byte[][] var8;
        for(var2 = 0; var2 <= var0.length - var1.length; var7 = var8) {
            int var5 = 0;

            boolean var4;
            for(var4 = true; var5 < var1.length; ++var5) {
                boolean var6;
                if (var0[var2 + var5] == var1[var5]) {
                    var6 = true;
                } else {
                    var6 = false;
                }

                var4 &= var6;
            }

            var5 = var3;
            var8 = var7;
            if (var4) {
                var8 = var7;
                if (var3 >= 0) {
                    int var10 = var2 - var3;
                    byte[] var11 = new byte[var10];
                    System.arraycopy(var0, var3, var11, 0, var10);
                    var8 = append(var7, var11);
                }

                var5 = var2;
            }

            ++var2;
            var3 = var5;
        }

        byte[][] var9 = var7;
        if (var3 >= 0) {
            var2 = var0.length - var3;
            var1 = new byte[var2];
            System.arraycopy(var0, var3, var1, 0, var2);
            var9 = append(var7, var1);
        }

        return var9;
    }

    public static byte[] toByteArray(String var0, int var1) {
        ByteBuffer var3 = ByteBuffer.allocate(var1);
        int var2 = Math.min(var0.length(), var1);

        for(var1 = 0; var1 < var2; ++var1) {
            var3.put((byte)var0.charAt(var1));
        }

        return var3.array();
    }

    public static byte[] xor(byte[] var0, byte[] var1) throws IllegalArgumentException {
        if (var0.length != var1.length) {
            throw new IllegalArgumentException("Invalid length");
        } else {
            byte[] var3 = new byte[var0.length];

            for(int var2 = 0; var2 < var3.length; ++var2) {
                var3[var2] = (byte)(var0[var2] ^ var1[var2]);
            }

            return var3;
        }
    }

    public static class ArrayComparator implements Comparator<byte[]> {
        public ArrayComparator() {
        }

        public int compare(byte[] var1, byte[] var2) {
            return !Arrays.equals(var1, var2) ? -1 : 0;
        }
    }

    // copied from https://android.googlesource.com/platform/frameworks/base/+/refs/heads/master/graphics/java/android/graphics/Color.java

    public static int red(int color) {
        return (color >> 16) & 0xFF;
    }

    public static int green(int color) {
        return (color >> 8) & 0xFF;
    }

    /**
     * Return the blue component of a color int. This is the same as saying
     * color & 0xFF
     */
    public static int blue(int color) {
        return color & 0xFF;
    }

    public static int rgb(float red, float green, float blue) {
        return 0xff000000 |
                ((int) (red   * 255.0f + 0.5f) << 16) |
                ((int) (green * 255.0f + 0.5f) <<  8) |
                (int) (blue  * 255.0f + 0.5f);
    }

    public static int rgb(
            int red,
            int green,
            int blue) {
        return 0xff000000 | (red << 16) | (green << 8) | blue;
    }

}
