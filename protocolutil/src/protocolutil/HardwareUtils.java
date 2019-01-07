package protocolutil;

import java.nio.charset.Charset;
import java.util.Locale;
import java.util.UUID;

public class HardwareUtils {
    public HardwareUtils() {
    }

    public static String getAddress(byte[] var0) {
        return String.format(Locale.US, "%02X:%02X:%02X:%02X:%02X:%02X", var0[0], var0[1], var0[2], var0[3], var0[4], var0[5]);
    }

    public static byte[] getAddress(String var0) {
        String[] var3 = var0.split(":");
        byte[] var2 = new byte[var3.length];

        for(int var1 = 0; var1 < var3.length; ++var1) {
            var2[var1] = (byte)Integer.parseInt(var3[var1], 16);
        }

        return var2;
    }

    public static short getMeshId(String var0) {
        StringBuilder var2 = new StringBuilder();
        var2.append(var0.substring(12, 14));
        var2.append(var0.substring(15, 17));
        int var1 = Integer.parseInt(var2.toString(), 16);
        if (var1 != 0 && var1 != 32768) {
            var1 %= 32768;
        } else {
            var1 = 1;
        }

        return (short)var1;
    }

    public static String getUuid(String var0) {
        Charset var1 = Charset.forName("UTF-8");
        return UUID.nameUUIDFromBytes(var0.replace("-", "").replace(":", "").toLowerCase(Locale.US).getBytes(var1)).toString();
    }
}
