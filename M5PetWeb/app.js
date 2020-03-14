
	var express = require('express');
    var fs = require('fs');
	var app = express();
	var port = process.env.PORT || 17777;
   
	
	var bodyParser = require('body-parser');
	app.use(bodyParser.json()); // support json encoded bodies
	app.use(bodyParser.urlencoded({	extended: true })); // support encoded bodies
	
	// ====================================
	// STATIC PAGES =====================
	// ====================================
    app.use('/', express.static(__dirname + '/'));
 
    //make way for some custom css, js and images
    app.use('/css', express.static(__dirname + '/css'));
    app.use('/js', express.static(__dirname + '/js'));
    app.use('/images', express.static(__dirname + '/images'));	


	// ====================================
	// URL PARAMETERS =====================
	// ====================================

//For posting score

	// http://localhost:17777/api/submit?name=bob&score=64&gID=1&geo=GB
	app.get('/api/submit', function(req, res) {
	  var userName = req.param('name');
	  var score = req.param('score');
	  var gameID = req.param('gID');  
      var geo = req.param('geo');  
      var date = new Date().toLocaleDateString();
      var scoreob = {user: userName, score: score, geo: geo, gameID: gameID, date: date};
      var check = checkParams(userName, score, geo, gameID);
      if (check != "success"){
          res.send(check);
      }
    else{
         res.send('submitted');
    }
        postNewScore(scoreob); 
	});
	
//For accessing scores
//http://localhost:8080/scores?gID=2
app.get('/scores', function(req, res){
    var gameID = req.param('gID');  
})


// start the server
	app.listen(port);
	console.log('Server started! At http://localhost:' + port);

function checkParams(userName, score, geo, gID) {
  var nameOkay = isAlphaNumeric(userName);
  if(!nameOkay){
      return "Name error";
  }
 if(isNaN(score)){
     return "Score error";
 }
 if(geo.length > 2){
     return "Geo error";
 }
 if(isNaN(gID)){
     return "Invalid game ID";
 }
 if(gID > 8){
     return "Invalid game ID";
 }
 return "success";
    
}

function isAlphaNumeric(str) {
  var code, i, len;

  for (i = 0, len = str.length; i < len; i++) {
    code = str.charCodeAt(i);
    if (!(code > 47 && code < 58) && // numeric (0-9)
        !(code > 64 && code < 91) && // upper alpha (A-Z)
        !(code > 96 && code < 123)) { // lower alpha (a-z)
      return false;
    }
  }
  return true;
};
 
function postNewScore(scoreObj) {
    gameID = scoreObj.gameID;
    var file; 
    var scoreToAdd;
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
    break;
}
    fs.readFile(file, (err, data) => {    
      if (err) throw err; 
      arrData = JSON.parse(data);
      scoreToAdd = JSON.stringify(scoreObj, null);
      arrData.push(scoreToAdd);
      arrData.sort(function(a,b){return b.score - a.score});
      var arrLen = arrData.length;
      if (arrLen > 50){
        var toRemove = arrLen - 50;
        console.log("Removing: " + toRemove);
        arrData.splice(50, toRemove);
     }
    fs.writeFile(file, JSON.stringify(arrData, null), function(err) {
          if(err) {
            console.log(err);
          } else {
            console.log("Clean JSON saved to: " + file);
          }
    })
})
                
};
 
















