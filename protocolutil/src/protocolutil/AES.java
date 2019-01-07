package protocolutil;

public class AES {
    static {
        System.loadLibrary("TelinkCrypto"); // taken from APK/lib/x86
    }

    public AES() {
    }

    public static byte[] decrypt(byte[] var0, byte[] var1, byte[] var2) {
        return decryptCmd(var2, var1, var0);
    }

    private static native byte[] decryptCmd(byte[] var0, byte[] var1, byte[] var2);

    public static byte[] encrypt(byte[] var0, byte[] var1, byte[] var2) {
        return encryptCmd(var2, var1, var0);
    }

    private static native byte[] encryptCmd(byte[] var0, byte[] var1, byte[] var2);
}
