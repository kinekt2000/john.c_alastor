function onLoad() {
    let scoreboard = localStorage.getItem("scoreboard");

    if(scoreboard) {
        scoreboard = JSON.parse(scoreboard);
        if(scoreboard.length > 0) {

            for(let player of scoreboard) {
                let nick = document.createElement("span");
                nick.textContent = player.nick;

                let score = document.createElement("span");
                score.textContent = player.score;

                let li = document.createElement("li");
                li.appendChild(nick);
                li.appendChild(score);

                document.getElementById("scoreboard").appendChild(li);
            }

            return
        }
    }

    let emptyScoreboardLine = document.createElement("p");
    emptyScoreboardLine.textContent = "Scoreboard is empty :(";
    document.body.appendChild(emptyScoreboardLine);
}