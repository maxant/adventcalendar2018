package protocolutil;

public class Main {

    public static void main(String[] args) {

        String toDecrypt = "110000292b2f5766be7d6141b21c7ac265d7e3c7";

        byte[] bytes = new byte[toDecrypt.length() / 2];
        for(int i = 0; i < toDecrypt.length();) {
            String s = toDecrypt.charAt(i++) + "" + toDecrypt.charAt(i++);
            byte b = (byte) Integer.parseInt(s, 16);
            bytes[(i/2)-1] = b;
            System.out.println(b); hmmm shouldnt be negative?
        }


        TelinkMeshLightController controller = new TelinkMeshLightController("a4:c1:38:b7:12:d8");
        //System.out.println(controller.writeCharacteristicComponent());


        /* TelinkMeshLightController


    public TelinkMeshLightController(Device device) {
        super(device);
        Context var3 = SingletonApplication.INSTANCE.getApplicationContext();
        String var2 = this.mDevice.friendlyName;
        if (var2 == null) {
            StringBuilder var5 = new StringBuilder("friendlyName is null for device uuid = ");
            var5.append(device.getUUID());
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


    public void onConnected() {
        this.mConnecting = false;
        this.mProperties.clear();
        this.mHandler.postDelayed(this.mLktRunnable, 3000L);
        this.mSessionRandom = new byte[8];
        (new SecureRandom()).nextBytes(this.mSessionRandom);
        if (this.mBluetoothGattManager == null) {
            StringBuilder var1 = new StringBuilder("onConnected() mBluetoothGattManager == null ");
            var1.append(this.mBluetoothDevice.toString());
            var1.append("@");
            var1.append(this.mBluetoothDevice.hashCode());
            Log.e(this, var1.toString(), new Object[0]);
        } else {
            this.mBluetoothGattManager.writeCharacteristic(this.mBluetoothDevice, "00010203-0405-0607-0809-0a0b0c0d1910", "00010203-0405-0607-0809-0a0b0c0d1914", Protocol.getPairValue(this.mMeshName, this.mMeshPassword, this.mSessionRandom), true);
            this.mBluetoothGattManager.readCharacteristic(this.mBluetoothDevice, "00010203-0405-0607-0809-0a0b0c0d1910", "00010203-0405-0607-0809-0a0b0c0d1914", true);
            this.mBluetoothGattManager.writeCharacteristic(this.mBluetoothDevice, "00010203-0405-0607-0809-0a0b0c0d1910", "00010203-0405-0607-0809-0a0b0c0d1911", new byte[]{1}, true);
            this.mBluetoothGattManager.setCharacteristicNotification(this.mBluetoothDevice, "00010203-0405-0607-0809-0a0b0c0d1910", "00010203-0405-0607-0809-0a0b0c0d1911", true);
        }
    }
        */



        //byte[] sessionKey = Protocol.getSessionKey();
        //System.out.println(Protocol.decryptValue("a4:c1:38:b7:12:d8", sessionKey));
    }
}
