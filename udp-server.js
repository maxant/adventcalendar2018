var PORT = 55056;
var HOST = '192.168.1.255';

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

server.on('listening', function () {
    server.setBroadcast(true); //so we can send messages below
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
//    if('192.168.1.151' !== remote.address) {
        console.log(remote.address + ':' + remote.port +' - ' + message);
//    }
});

server.bind(PORT, HOST);

const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.on('line', (input) => {
    server.send(input, 0, input.length, PORT, HOST, function(err, bytes) {
        if (err) throw err;
        //console.log('UDP message sent to ' + HOST +':'+ PORT);
    });
});

setInterval(function(){
    var msg = "{'cmd':'ping'}";
    server.send(msg, 0, msg.length, PORT, HOST, function(err, bytes) {
        if(err) throw err;
    });
}, 1000);
