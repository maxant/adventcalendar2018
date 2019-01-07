package protocolutil;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public final class Protocol {
    public static final String CHARACTERISTIC_MESH_LIGHT_COMMAND = "00010203-0405-0607-0809-0a0b0c0d1912";
    public static final String CHARACTERISTIC_MESH_LIGHT_OTA = "00010203-0405-0607-0809-0a0b0c0d1913";
    public static final String CHARACTERISTIC_MESH_LIGHT_PAIR = "00010203-0405-0607-0809-0a0b0c0d1914";
    public static final String CHARACTERISTIC_MESH_LIGHT_STATUS = "00010203-0405-0607-0809-0a0b0c0d1911";
    static final byte COMMAND_GET_ALARMS_RECEIVED = -25;
    static final byte COMMAND_GET_ALARMS_SENT = -26;
    static final byte COMMAND_GET_DEVICE_ADDRESS = -21;
    static final byte COMMAND_GET_GROUPS_SENT = -35;
    static final byte COMMAND_GET_GROUP_RECEIVED = -44;
    static final byte COMMAND_GET_PIR_CURRENT_LUMINOSITY = 18;
    static final byte COMMAND_GET_PIR_SETTINGS = 17;
    static final byte COMMAND_GET_PLUG_MESH_CONSUMPTION_DAILY = 21;
    static final byte COMMAND_GET_PLUG_MESH_CONSUMPTION_HOURLY = 20;
    static final byte COMMAND_GET_PLUG_MESH_CURRENT_DATA = 19;
    static final byte COMMAND_GET_PLUG_MESH_SCHEDULE = 22;
    static final byte COMMAND_GET_SCENES_RECEIVED = -63;
    static final byte COMMAND_GET_SCENES_SENT = -64;
    static final byte COMMAND_GET_STATUS_RECEIVED = -37;
    static final byte COMMAND_GET_STATUS_SENT = -38;
    static final byte COMMAND_GET_TIME_RECEIVED = -23;
    static final byte COMMAND_GET_TIME_SENT = -24;
    static final byte COMMAND_GET_USER_NOTIFY_RECEIVED = -40;
    static final byte COMMAND_GET_USER_NOTIFY_SENT = -22;
    static final byte COMMAND_KICK_OUT = -29;
    static final byte COMMAND_LOAD_SCENE = -17;
    static final byte COMMAND_MISC = -48;
    static final byte COMMAND_MISC_2 = -9;
    static final byte COMMAND_NOTIFICATION_RECEIVED = -36;
    static final byte COMMAND_SET_ALARM = -27;
    static final byte COMMAND_SET_COLOR = -30;
    static final byte COMMAND_SET_COLOR_BRIGHTNESS = -14;
    static final byte COMMAND_SET_COLOR_SEQUENCE_COLOR_DURATION = -11;
    static final byte COMMAND_SET_COLOR_SEQUENCE_FADE_DURATION = -10;
    static final byte COMMAND_SET_COLOR_SEQUENCE_PRESET = -56;
    static final byte COMMAND_SET_GROUP = -41;
    static final byte COMMAND_SET_LED_STATE = 23;
    static final byte COMMAND_SET_LIGHT_MODE = 51;
    static final byte COMMAND_SET_MESH_ADDRESS_RECEIVED = -31;
    static final byte COMMAND_SET_MESH_ADDRESS_SENT = -32;
    static final byte COMMAND_SET_PIR_SETTINGS = 0;
    static final byte COMMAND_SET_POWER_STATE = -48;
    static final byte COMMAND_SET_SCHEDULE = -34;
    static final byte COMMAND_SET_TIME = -28;
    static final byte COMMAND_SET_WHITE_BRIGHTNESS = -15;
    static final byte COMMAND_SET_WHITE_TEMPERATURE = -16;
    static final byte COMMAND_STORE_SCENE = -1;
    static final byte EXTENDED_COMMAND_RESCUE_PEBBLE = 1;
    static final byte EXTENDED_COMMAND_SET_ALL_GROUPS = 18;
    static final int INDEX_DAWN_SIMULATOR = 1;
    static final int INDEX_NIGHTLIGHT = 8;
    static final int INDEX_PRESENCE_SIMULATOR = 0;
    static final int INDEX_PROGRAM = 15;
    static final int INDEX_RANGE_1 = 0;
    static final int INDEX_RANGE_2 = 1;
    static final int INDEX_RANGE_3 = 2;
    static final int INDEX_RANGE_4 = 3;
    static final int INDEX_RANGE_5 = 4;
    static final int INDEX_RANGE_6 = 5;
    static final int INDEX_TIMER = 0;
    static final byte OPCODE_ENC_FAIL = 14;
    static final byte OPCODE_ENC_REQ = 12;
    static final byte OPCODE_ENC_RSP = 13;
    static final byte OPCODE_PAIR_CONFIRM = 7;
    static final byte OPCODE_PAIR_LTK = 6;
    static final byte OPCODE_PAIR_NETWORK_NAME = 4;
    static final byte OPCODE_PAIR_PASS = 5;
    static final byte PARAMETER_EXTENDED_COMMANDS = -18;
    static final byte PARAM_USER_NOTIFY_DAILY_SCHEDULE = 8;
    static final byte PARAM_USER_NOTIFY_DEVICE_ADDRESS = 0;
    static final byte PARAM_USER_NOTIFY_SEQUENCE_COLOR_DURATION = 1;
    static final byte PARAM_USER_NOTIFY_SEQUENCE_TRANSITION_DURATION = 2;
    static final byte PARAM_USER_NOTIFY_SIMPLE_SCHEDULE = 7;
    static final byte RELAY_TIMES = 16;
    static final String SERVICE_TELINK = "00010203-0405-0607-0809-0a0b0c0d1910";
    private static final byte[] SRC = new byte[]{0, 0};
    static final int TYPE_DAWN_SIMULATOR = 2;
    static final int TYPE_NIGHTLIGHT = 1;
    static final int TYPE_PLUG_MESH_SCHEDULE = 4;
    static final int TYPE_PRESENCE_SIMULATOR = 6;
    static final int TYPE_TIMER = 3;
    private static final byte[] VENDOR_ID = new byte[]{96, 1};
    private static int sSequenceNumber;

    private Protocol() {
    }

    public static byte[] decryptValue(String hwAddress, byte[] probablySessionKey, byte[] var2) {
        byte[] var3 = new byte[8];
        System.arraycopy(ByteUtils.reverse(HardwareUtils.getAddress(hwAddress)), 0, var3, 0, 3);
        System.arraycopy(var2, 0, var3, 3, 5);
        return AES.decrypt(probablySessionKey, var3, var2);
    }

    public static byte[] encrypt(byte[] var0, byte[] var1) {
        byte[] var2 = ByteUtils.reverse(var0);
        var0 = ByteUtils.reverse(var1);

        try {
            SecretKeySpec var4 = new SecretKeySpec(var2, "AES");
            Cipher var5 = Cipher.getInstance("AES/ECB/NoPadding");
            var5.init(1, var4);
            var1 = var5.doFinal(var0);
            return var1;
        } catch (Exception var3) {
            return var0;
        }
    }

    static byte[] encryptValue(String hwAddress, byte[] sessionKey, byte[] var2) {
        byte[] var3 = new byte[8];
        System.arraycopy(ByteUtils.reverse(HardwareUtils.getAddress(hwAddress)), 0, var3, 0, 4);
        var3[4] = 1;
        System.arraycopy(var2, 0, var3, 5, 3);
        return AES.encrypt(sessionKey, var3, var2);
    }

    static byte getCommand(byte[] var0) {
        return var0[7];
    }

    static byte[] getData(byte[] var0) {
        byte[] var1 = new byte[var0.length - 10];
        System.arraycopy(var0, 10, var1, 0, var1.length);
        return var1;
    }

    static byte[] getPairValue(byte[] var0, byte[] var1, byte[] var2) {
        var0 = encrypt(Arrays.copyOf(var2, 16), ByteUtils.xor(var0, var1));
        var1 = new byte[17];
        var1[0] = 12;
        System.arraycopy(var2, 0, var1, 1, var2.length);
        System.arraycopy(ByteUtils.reverse(var0), 0, var1, 9, 8);
        return var1;
    }

    /** called in response to characterstic 0a0b0c0d1914 */
    public static byte[] getSessionKey(byte[] meshName, byte[] meshPassword, byte[] sessionRandom, byte[] characteristicBytes1to9) {
        byte[] var4 = new byte[16];
        System.arraycopy(sessionRandom, 0, var4, 0, sessionRandom.length);
        System.arraycopy(characteristicBytes1to9, 0, var4, 8, characteristicBytes1to9.length);
        return ByteUtils.reverse(encrypt(ByteUtils.xor(meshName, meshPassword), var4));
/*
    public void onCharacteristicRead(BluetoothGatt var1, BluetoothGattCharacteristic var2, int var3) {
        super.onCharacteristicRead(var1, var2, var3);
        if (this.mBluetoothDevice != null) {
            if (this.mBluetoothDevice.equals(var1.getDevice())) {
                String var5 = var2.getService().getUuid().toString();
                String var4 = var2.getUuid().toString();
                byte[] var8 = var2.getValue();
                if ("00010203-0405-0607-0809-0a0b0c0d1910".equals(var5) && "00010203-0405-0607-0809-0a0b0c0d1914".equals(var4)) {
                    if (var8[0] == 13) {
                        this.mHandler.removeCallbacks(this.mLktRunnable);
                        byte[] var7 = new byte[8];
                        System.arraycopy(var8, 1, var7, 0, 8);
                        this.mSessionKey = Protocol.getSessionKey(this.mMeshName, this.mMeshPassword, this.mSessionRandom, var7);
                        this.writeInternal(this.mDevice.meshId, "time", System.currentTimeMillis());
                        DeviceManager.getInstance().setEntryMesh(this);
                        if (OperationManager.checkOperation(this.mDevice.uuid)) {
                            this.writeInternal(this.mDevice.meshId, "mesh_groups", MeshUtils.getMeshGroups(this.mContext, this.mDevice));
                        }

                        super.onConnected();
                        return;
                    }
*/

    }

    static byte[] getValue(short var0, byte var1, byte[] var2) {
        return getValue(ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putShort(var0).array(), var1, var2);
    }

    static byte[] getValue(byte[] var0, byte var1, byte[] var2) {
        ++sSequenceNumber;
        ByteBuffer var3 = ByteBuffer.allocate(20);
        var3.put((byte)(sSequenceNumber & 255));
        var3.put((byte)(sSequenceNumber >> 8 & 255));
        var3.put((byte)(sSequenceNumber >> 16 & 255));
        var3.put(SRC);
        var3.put(var0);
        var3.put(var1);
        var3.put(VENDOR_ID);
        var3.put(var2);
        return var3.array();
    }
}
