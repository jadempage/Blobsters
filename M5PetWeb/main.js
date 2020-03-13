 var gameID = 0;

function populateList(gameID){
    getData(1);
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
$.getJSON( "data/test.json", function( json ) {
//  $.each( json, function( user, score, geo, date ) {
//    items.push( "User: " + user + " score: " + score + "location: " + geo + "date: " + date);
//    console.log(items);
//      console.log(items.length);
    console.log(json.length);
    
    for(var i = 0; i < json.length; i++) {
        var obj = json[i];
        var listItem = document.createElement("li");
        listItem.textContent = ("Date: " + obj.date + "User: " + obj.user + " score: " + obj.score + " location: " + obj.geo); 
         ol.appendChild(listItem);
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