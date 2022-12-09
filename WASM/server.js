const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 8000 });

//event handler
wss.on('connection', (ws,eq) => {

    console.log("Connection Recieved")
    ws.isalive = true;
    ws.send(JSON.stringify({type: 'ping'}));

    const Runner = new Runner; 

    var time1 = now();
    
    Runner.addPlayers();
    Runner.start();

    
    var time2 = now();

    var time = time2- time1;

 
});

console.log("Server Started");