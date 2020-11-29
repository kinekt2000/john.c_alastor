function submitAndGo() {
    let nick = document.getElementById("login").value;

    if(nick.length < 4 || nick.length > 20) {
        alert("Nickname length must be no more than 20 and no less than 4 characters");
        return;
    }

    localStorage.setItem("nick", nick);
    window.location.href = "game.html";
}