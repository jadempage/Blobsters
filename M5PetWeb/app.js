// grab the packages we need
	var express = require('express');
    var fs = require('fs');
	var app = express();
	var port = process.env.PORT || 8080;
	
	var bodyParser = require('body-parser');
	app.use(bodyParser.json()); // support json encoded bodies
	app.use(bodyParser.urlencoded({	extended: true })); // support encoded bodies
	
	// routes will go here
	
	// ====================================
	// URL PARAMETERS =====================
	// ====================================
	// http://localhost:8080/api/submit?name=bob&score=64&gID=1&geo=GB
	app.get('/api/submit', function(req, res) {
	  var userName = req.param('name');
	  var score = req.param('score');
	  var gameID = req.param('gID');  
      var geo = req.param('geo');  
      var date = new Date().toLocaleDateString();
    
      cleanUp();
      var scoreob = {user: userName, score: score, geo: geo, gameID: gameID, date: date};
      var check = checkParams(userName, score, geo, gameID);
      if (check != "success"){
          res.send(check);
      }
    else{
         res.send('submitted');
    }
        dumpScore(scoreob); 
	});
	

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



function dumpScore(scoreob){
var outputFilename = 'data/test.json';  
   fs.appendFile(outputFilename, JSON.stringify(scoreob, null) + "\n", function(err) {
    if(err) {
      console.log(err);
    } else {
      console.log("JSON saved to " + outputFilename);
    }
});  }


function cleanUp(){
    //Serialize data, sort, save top 50, delete the rest
    var arrData;
    var outputFilename = 'data/test.json';  
    var cleanedUp = false;
       fs.readFile('data/mock.json', (err, data) => { 
      if (err) throw err; 
    
      arrData = JSON.parse(data);
      var arrLen = arrData.length;
      console.log(arrLen); 
      if (arrLen > 50){
        arrData.sort(function(a,b){return b.score - a.score});
        var toRemove = arrLen - 50;
        console.log(toRemove);
        arrData.splice(50, toRemove);
        fs.writeFile(outputFilename, JSON.stringify("", null), function(err) {
          if(err) {
            console.log(err);
          } else {
            console.log("JSON saved to " + outputFilename);
          }
      });
      for(var i = 0; i < arrData.length; i++){
        scoreob = arrData[i];
        dumpScore(scoreob);
      }
      }
      console.log(arrData);
      console.log(arrData.length);
  }) 

}




















