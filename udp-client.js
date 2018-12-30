var PORT = 55056;
//var HOST = '192.168.1.255';
var HOST = '192.168.1.255';

var dgram = require('dgram');

var client = dgram.createSocket('udp4', function(){
    client.setBroadcast(true);
});

var message = Buffer.from(process.argv[2]);
//console.log('sending udp: ' + message);
client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
    if (err) throw err;
    console.log('UDP message sent to ' + HOST +':'+ PORT);
    client.close();
});

