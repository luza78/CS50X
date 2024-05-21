/* setting some globals for functions */
var fade = false;
var delayInSeconds = 1;


function starthome() {
    var phrases = ['To learn more about me, check out the buttons above', 'If you want to contact me click HERE', "I hope you're having a fantastic day"];
    var num = 0;

    /*hiding contact popup*/
    document.getElementById('contactbutton').style.visibility = "hidden";
    document.getElementById('contactbutton').style.opacity = "0";

    var changephrase = function() {
        var len = phrases.length;

        if (fade == true){
            document.getElementById('dynamic1').innerHTML = phrases[num++];
            document.getElementById('dynamic1').style.opacity = 1;
        }

        if (fade == false) {
            document.getElementById('dynamic2').style.opacity = 0;
            document.getElementById('dynamic1').style.opacity = 1;
            fade = true;
        }
        if (num == 2){
            document.getElementById('contactbutton').style.visibility = "visible";
            document.getElementById('contactbutton').style.opacity = "1";
        }

        if (num == len) {
            num = 0;
        }
    };
setInterval(changephrase, delayInSeconds * 8000);
};
function scrollingfade() {
        if (fade == true) {
            document.getElementById('dynamic1').style.opacity = 0;
        }
};

/* initializes functions when page loaded */
window.onload=function(){
starthome();
setInterval(scrollingfade, delayInSeconds * 7800);
contactbtn();
};

/*all to do with the interactive button*/
function contactbtn(){
    var btn = document.getElementById("contactbutton");
    /* This is to listen for mouseover in the contact button */
    btn.addEventListener("mouseover", mousetrue, false);
    btn.addEventListener("mouseout", mousefalse, false);

    function mousetrue(){
    btn.setAttribute("style", "background-color: #013220;")
    }

    function mousefalse(){
    btn.setAttribute("style", "background-color: #3CB371;")
    }
};

function sendmail(){
    window.location="mailto:lukeschaufuss@gmail.com";
};