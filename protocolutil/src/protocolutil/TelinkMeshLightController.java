package protocolutil;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

public class TelinkMeshLightController {
    public static final int COLOR_BRIGHTNESS_MAX = 100;
    public static final int COLOR_BRIGHTNESS_MIN = 10;
    private static final short MESH_ID_ALL = -1;
    private static final long OFFLINE_NOTIFICATION_DELAY = 2000L;
    private static final String START_MAC_ADDRESS = "A4:C1";
    public static final int WHITE_BRIGHTNESS_MAX = 127;
    public static final int WHITE_BRIGHTNESS_MIN = 1;
    public static final int WHITE_TEMPERATURE_MAX = 127;
    public static final int WHITE_TEMPERATURE_MIN = 0;
    private static final long WRITE_DELAY = 200L;
    private static final long WRITE_KICKOUT_DELAY = 1000L;

    private short mMeshIdThis = 0;
    private byte[] mMeshName;
    private byte[] mMeshPassword;
    private Map<String, Boolean> mOfflineNotifications = new HashMap();
    private final HashSet<String> mProperties = new HashSet();
    private byte[] mSessionKey = new byte[16];
    private byte[] mSessionRandom = new byte[8];
    private byte[] mSetMeshAddress;
    private String hwAddress;

    public TelinkMeshLightController(String hwAddress) {
        this.hwAddress = hwAddress;
    }

    /*
    public TelinkMeshLightController(Device var1) {
        super(var1);
        Context var3 = SingletonApplication.INSTANCE.getApplicationContext();
        String var2 = this.mDevice.friendlyName;
        if (var2 == null) {
            StringBuilder var5 = new StringBuilder("friendlyName is null for device uuid = ");
            var5.append(var1.getUUID());
            Log.w(this, var5.toString(), new Object[0]);
        } else {
            String var4;
            if (!ConfigHelper.DEMO_MODE && !var2.equals("unpaired") && !var2.startsWith("R-") && !var2.startsWith("S-") && !var2.startsWith("P-") && !var2.startsWith("I-")) {
                var4 = var3.getSharedPreferences(Mesh.PREFS_NAME, 0).getString("mesh_password", "");
            } else {
                var4 = "1234";
            }

            this.mMeshName = Arrays.copyOf(var2.getBytes(), 16);
            this.mMeshPassword = Arrays.copyOf(var4.getBytes(), 16);
        }
    }
*/

    public void readInternal(short var1, String var2) {
        Object var3 = null;
        byte[] var4;
        if (!"power_state".equals(var2) && !"light_mode".equals(var2) && !"white_brightness".equals(var2) && !"white_temperature".equals(var2) && !"color_brightness".equals(var2) && !"color".equals(var2) && !"plug_led".equals(var2)) {
            if ("color_sequence_color_duration".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 1});
            } else if ("color_sequence_fade_duration".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 2});
            } else if ("time".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-24, new byte[]{16});
            } else if ("alarms".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-26, new byte[]{16});
            } else if ("timer".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 7, 0});
            } else if ("nightlight".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 7, 8});
            } else if ("dawn_simulator".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 7, 1});
            } else if ("presence_simulator".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 8, 0});
            } else if ("program".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 7, 15});
            } else if ("mesh_groups".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-35, new byte[]{16, 1});
            } else if ("scenes".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-64, new byte[]{16});
            } else if ("pir_settings".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 17});
            } else if ("pir_current_luminosity".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 18});
            } else if ("power_consumption_history_mesh".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 19});
            } else if ("power_consumption_mesh".equals(var2)) {
                this.mProperties.add(var2);
                var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, 19});
            } else if ("power_consumption_hourly".equals(var2)) {
                this.mProperties.add(var2);
                this.writeCharacteristicComponent(var1, (byte)20, (byte)0);
                this.writeCharacteristicComponent(var1, (byte)20, (byte)1);
                this.writeCharacteristicComponent(var1, (byte)20, (byte)2);
                this.writeCharacteristicComponent(var1, (byte)20, (byte)3);
                this.writeCharacteristicComponent(var1, (byte)20, (byte)4);
                this.writeCharacteristicComponent(var1, (byte)20, (byte)5);
                var4 = (byte[])var3;
            } else if ("power_consumption_daily".equals(var2)) {
                this.mProperties.add(var2);
                this.writeCharacteristicComponent(var1, (byte)21, (byte)0);
                this.writeCharacteristicComponent(var1, (byte)21, (byte)1);
                this.writeCharacteristicComponent(var1, (byte)21, (byte)2);
                this.writeCharacteristicComponent(var1, (byte)21, (byte)3);
                var4 = (byte[])var3;
            } else if ("plug_mesh_schedule".equals(var2)) {
                this.mProperties.add(var2);
                this.writeCharacteristicComponent(var1, (byte)22, (byte)0);
                this.writeCharacteristicComponent(var1, (byte)22, (byte)1);
                this.writeCharacteristicComponent(var1, (byte)22, (byte)2);
                this.writeCharacteristicComponent(var1, (byte)22, (byte)3);
                this.writeCharacteristicComponent(var1, (byte)22, (byte)4);
                this.writeCharacteristicComponent(var1, (byte)22, (byte)5);
                this.writeCharacteristicComponent(var1, (byte)22, (byte)6);
                var4 = (byte[])var3;
            } else {
                System.err.println("Property not handled : ".concat(String.valueOf(var2)));
                var4 = (byte[])var3;
            }
        } else if (this.mProperties.isEmpty()) {
            this.mProperties.add(var2);
            var4 = Protocol.getValue(var1, (byte)-38, new byte[]{16});
        } else {
            this.mProperties.add(var2);
            var4 = (byte[])var3;
        }

        if (var4 != null) {
            var4 = Protocol.encryptValue(hwAddress/*this.mBluetoothDevice.getAddress()*/, this.mSessionKey, var4);
            System.out.println("WRITE CHARACTERISTIC: " + var4);
/*                this.mBluetoothGattManager.writeCharacteristic(this.mBluetoothDevice, "00010203-0405-0607-0809-0a0b0c0d1910", "00010203-0405-0607-0809-0a0b0c0d1912", var4, true);*/
        }
    }

    public void resetMeshNetwork(short var1) {
        byte[] var2 = Protocol.getValue(var1, (byte)-29, new byte[]{0});
        var2 = Protocol.encryptValue(hwAddress/*this.mBluetoothDevice.getAddress()*/, this.mSessionKey, var2);
        System.out.println("WRITE CHARACTERISTIC: " + var2);
        /*this.mBluetoothGattManager.writeCharacteristic(this.mBluetoothDevice, "00010203-0405-0607-0809-0a0b0c0d1910", "00010203-0405-0607-0809-0a0b0c0d1912", var2, true);
        this.mHandler.postDelayed(new Runnable() {
            public void run() {
                TelinkMeshLightController.this.onWrite("mesh_network", 0);
            }
        }, 1000L);
        */
    }

    public void writeCharacteristicComponent(short var1, byte var2, byte var3) {
        byte[] var4 = Protocol.getValue(var1, (byte)-22, new byte[]{16, var2, var3});
        var4 = Protocol.encryptValue(hwAddress/*this.mBluetoothDevice.getAddress()*/, this.mSessionKey, var4);
        System.out.println("WRITE CHARACTERISTIC: " + var4);
        /*
        this.mBluetoothGattManager.writeCharacteristic(this.mBluetoothDevice, "00010203-0405-0607-0809-0a0b0c0d1910", "00010203-0405-0607-0809-0a0b0c0d1912", var4, true);
        */
    }

    /*
    TelinkMesLightController => onCharacteristicRead

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
