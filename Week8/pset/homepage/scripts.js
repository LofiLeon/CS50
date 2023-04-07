var img = document.getElementById("vfb");
var scale = 0.5;
var direction = 1;
setInterval(scaleImage, 100);

function scaleImage() {
    scale += direction * 0.1;
    if (scale > 1.5 || scale < 0.5) {
        direction = -direction;
    }
    img.style.width = (scale * 300) + "px";
    img.style.height = (scale * 300) + "px";
}