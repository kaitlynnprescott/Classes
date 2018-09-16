var imageArray = ['images/Brian Borowski.jpeg', 
                  'images/Taylor Swift.jpeg',
                  'images/Morgan Freeman.jpeg', 
                  'images/Harrison Ford.jpeg',
                  'images/Gordon Ramsay.jpeg',
                  'images/Donald Trump.jpg',
                  'images/Robert De Niro.jpeg'];
var imageIndex = 0;
 
function nextImage(element) {
    var image = document.getElementById(element);
    imageIndex = (imageIndex + 1) % imageArray.length;
    image.src = imageArray[imageIndex];
    var current = document.getElementById("changing_image");
    var src = current.src;
    if(src.indexOf('/') >= 0) {
        src = src.substring(src.lastIndexOf('/')+1);
    }
    if(src.indexOf('.') >= 0) {
        src = src.substring(0, src.lastIndexOf('.'));
    }
    src = src.replace("%20"," ")
    document.getElementById("names").innerHTML = src;
}
 
 
// window.onload is fired when the entire page loads, including its
// content (images, css, scripts, etc.)
// It must be assigned a function.
window.onload = function() {
    // setInterval returns a number, representing the ID value of the
    // timer that is set. It cannot be directly assigned to
    // window.onload.
    setInterval(nextImage, 3000, "changing_image");
}