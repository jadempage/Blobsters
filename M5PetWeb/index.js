var images = document.getElementsByTagName("img");
for(var i = 0; i < images.length; i++) {
    var image = images[i];
    image.onclick = function(event) {
        gameID = this.id;
        let urlParams = new URLSearchParams(window.location.search);
       var myID = gameID.slice(-1);
        window.open('scores.html?' + myID);
         console.log(myID); 
    };
}
