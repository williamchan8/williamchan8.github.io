

var Players = ["Bill","Bob","Balls","Becky","Barny"]

function generator() {
    document.getElementById("name").innerHTML = Players[Math.floor(Math.random() * Players.length)] 
    document.getElementById("points").innerHTML = "with " + Math.floor(Math.random() * 100) + ' points';

}

function loadPlayers(){

    var N = document.getElementById('N').value;
    var T = document.getElementById('T').value;




}
