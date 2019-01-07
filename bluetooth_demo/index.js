var noble = require('noble');

process.env.NOBLE_HCI_DEVICE_ID = '2687:fb01';

noble.on('stateChange', function(state) {
  console.log("state changed: '" + state + "'");
  if (state === 'poweredOn') {
    console.log("starting scan...");
    noble.startScanning();
    console.log("started scan...");
  } else if (state === 'poweredOff') {
    console.log("State is powered off => exiting");
    process.exit(22);
  } else {
    console.log("stopping scan...");
    noble.stopScanning();
    console.log("stopped scan...");
  }
});

noble.on('discover', function(peripheral) {
    console.log('peripheral with ID ' + peripheral.id + ' found');
});

