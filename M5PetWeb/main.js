 var gameID = 0;

function populateList(gameID){
    getData(gameID);
}

function generateTitle(gameID){
    var title = document.getElementById("maintitle");
    
switch(gameID) {
  case '1':
    title.innerHTML="Fruit Catch";
    break;
  case '2':
   title.innerHTML="High or Low";
    break;
  case '3':
    title.innerHTML="Pong";
    break;
  case '4':
    title.innerHTML="Treasure";
    break;
  case '5':
   title.innerHTML="Invalid Game ID";
    break;
  case '6':
    title.innerHTML="Invalid Game ID";
    break;
  case '7':
   title.innerHTML="Invalid Game ID";
    break;
  case '8':
   title.innerHTML="Invalid Game ID";
    break;            
  default:
    title.innerHTML="Invalid Game ID";
}
}


function getData(gameID){
var ol = document.querySelector("ol");
var items = [];    
var file;    
switch(gameID) {
  case '1':
    file = "data/fruit.json";
    break;
  case '2':
   file = "data/hilo.json";
    break;
  case '3':
    file = "data/pong.json";
    break;
  case '4':
    file = "data/treasure.json";
    break;
  case '5':
   file = "data/test.json";
    break;
  case '6':
    file = "data/test.json";
    break;
  case '7':
   file = "data/test.json";
    break;
  case '8':
   file = "data/test.json";
    break;            
  default:
    file = "data/test2.json";
}    
       
$.getJSON( file, function( json ) {
    console.log(json.length);
    
    for(var i = 0; i < json.length; i++) {
        var obj = JSON.parse(json[i]);
    
        console.log(obj);
        var table = document.getElementById("mainTable");
        var topRow = document.getElementById("topRow");
        var row = table.insertRow(i+1);
        var cell1 = row.insertCell(0);
        var cell2 = row.insertCell(1);
        var cell3 = row.insertCell(2);
        
        cell1.innerHTML = obj.date;
        cell2.innerHTML = obj.user;
        cell3.innerHTML = obj.score;
    }
  });
    
}


function fetchJSONFile(path, callback) {
    var httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = function() {
        if (httpRequest.readyState === 4) {
            if (httpRequest.status === 200) {
                var data = JSON.parse(httpRequest.responseText);
                if (callback) callback(data);
            }
        }
    };
    httpRequest.open('GET', path);
    httpRequest.send(); 
}

function startLoad(){
    let toGetID = window.location.search;
    var numberID = toGetID.slice(-1);
    console.log(numberID);
    generateTitle(numberID);
    populateList(numberID);
}

 window.onload = startLoad();

