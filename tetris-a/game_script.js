
let ctx;

let initial_width =  400;

let canvas_width;
let canvas_height;

let nickname = "unnamed";
let scoreboard = null;
function onLoad() {
    /* configure nickname in html */
    nickname = localStorage.getItem("nick");
    document.getElementById("nick").textContent = nickname;

    /* get scoreboard */
    scoreboard = localStorage.getItem("scoreboard");
    if(scoreboard) {
        scoreboard = JSON.parse(scoreboard);
    } else {
        scoreboard = new Array(0);
    }

    /* calculate size of blocks and outlines */
    cell_size = initial_width * (1 - (COLS + 1)/100) / COLS;
    outline_thickness = initial_width * ((COLS + 1)/100) / (COLS + 1);

    /* create canvas */
    let canvas = document.createElement("canvas");
    ctx = canvas.getContext("2d");
    ctx.translate(0.5, 0.5);

    canvas_height = (cell_size) * ROWS + outline_thickness * 2;
    canvas_width = (cell_size) * COLS + outline_thickness * 2;

    canvas.width = canvas_width;
    canvas.height = canvas_height;

    document.getElementById("canvas-wrap").appendChild(canvas);
    document.addEventListener("keydown", handleKeyboard);

    /* run */
    run();
}

const ROWS = 20;
const COLS = 10;

let cell_size;
let outline_thickness;

const colors = {
    // 'empty' 'I' 'S' 'Z' 'L' 'J' 'T' 'O'
    table: ['#888', '#f00', '#0f0', '#f0f',
            '#ff0', '#f60', '#00f', '#f99'],

    getColor(/* int */ id) {
        if(id < 0 || id > this.table.length - 1) {
            return this.table[0];
        }
        return this.table[id]
    }
}

function createMatrix(width, height) {
    let matrix = new Array(height);
    for(let i = 0; i < height; i++) {
        matrix[i] = new Array(width);
        for(let j = 0; j < width; j++) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

function createFigure(type) {
    switch (type) {
        case "I":
            return [
                [0, 1, 0, 0],
                [0, 1, 0, 0],
                [0, 1, 0, 0],
                [0, 1, 0, 0]
            ];

        case "S":
            return [
                [0, 2, 2],
                [2, 2, 0],
                [0, 0, 0]
            ];

        case "Z":
            return [
                [3, 3, 0],
                [0, 3, 3],
                [0, 0, 0]
            ];

        case "L":
            return [
                [0, 4, 0],
                [0, 4, 0],
                [0, 4, 4]
            ];

        case "J":
            return [
                [0, 5, 0],
                [0, 5, 0],
                [5, 5, 0]
            ];

        case "T":
            return [
                [6, 6, 6],
                [0, 6, 0],
                [0, 0, 0]
            ];

        case "O":
            return [
                [7, 7],
                [7, 7]
            ];

        default:
            return null;
    }
}

let board = {
    area: createMatrix(COLS, ROWS),

    draw() {
        for(let i = 0; i < this.area.length; i++){
            for(let j = 0; j < this.area[i].length; j++) {
                let canvas_x = (outline_thickness) + j * (cell_size);
                let canvas_y = (outline_thickness) + i * (cell_size);

                ctx.beginPath();
                ctx.rect(canvas_x,canvas_y, cell_size, cell_size);

                ctx.fillStyle = colors.getColor(this.area[i][j]);
                ctx.fill();

                ctx.strokeStyle = "#bbb";
                ctx.lineWidth = outline_thickness;
                ctx.stroke();
            }
        }
    },

    collide(block) {
        let [m, o] = [block.figure, block.pos];
        for(let i = 0; i < m.length; i++) {
            for(let j = 0; j < m[i].length; j++) {
                if(m[i][j] !== 0) {
                    if(i + o.y < 0) {
                        continue;
                    }

                    if(i + o.y >= this.area.length || j + o.x < 0 || j + o.x >= this.area[0].length) {
                        return true;
                    }

                    if(this.area[i + o.y][j + o.x] !== 0) {
                        return true;
                    }
                }
            }
        }

        return false;
    },

    putBlock(block) {
        let [m, o] = [block.figure, block.pos];
        for(let i = 0; i < m.length; i++) {
            for(let j = 0; j < m[i].length; j++) {
                if(m[i][j] !== 0 && i + o.y >= 0) {
                    this.area[i + o.y][j + o.x] = m[i][j];
                }
            }
        }
    },

    sweep() {
        let multiplier = 1;
        outer: for(let i = this.area.length - 1; i >= 0 ; i--) {
            for(let j = 0; j < this.area[i].length; j++) {
                if(this.area[i][j] === 0) {
                    continue outer;
                }
            }

            const row = this.area.splice(i, 1)[0].fill(0);
            this.area.unshift(row);

            i++;

            score += (multiplier++) * 5;
        }

        if(multiplier > 1) {
            difficulty += 2;
        }
    },

    isOverflowed() {
        for(let i = 0; i < this.area[0].length; i++) {
            if(this.area[0][i] !== 0) {
                return true;
            }
        }
        return false;
    }
};

function transpose(matrix) {
    for(let y = 0; y < matrix.length; y++) {
        for(let x = 0; x < y; x++) {
            [
                matrix[x][y],
                matrix[y][x],
            ] = [
                matrix[y][x],
                matrix[x][y]
            ];
        }
    }
}
const block = {
    pos: {x: 3, y: -2},
    figure: [
        [1, 1],
        [1, 1]
    ],

    draw() {
        for(let i = 0; i < this.figure.length; i++){
            for(let j = 0; j < this.figure[i].length; j++) {
                if(this.figure[i][j] === 0) continue; // skip empty (zeroes) parts of matrix

                let canvas_x = (outline_thickness) + (j + this.pos.x) * (cell_size);
                let canvas_y = (outline_thickness) + (i + this.pos.y) * (cell_size);

                ctx.beginPath();
                ctx.rect(canvas_x,canvas_y, cell_size, cell_size);

                ctx.fillStyle = colors.getColor(this.figure[i][j]);
                ctx.fill();

                ctx.strokeStyle = "#000";
                ctx.lineWidth = outline_thickness;
                ctx.stroke();
            }
        }
    },

    shiftDown() {
        block.pos.y++;
        if(board.collide(this)) {
            this.pos.y--;
            board.putBlock(this);

            score += 5;
            difficulty += 0.5;

            if(board.isOverflowed()) {
                finish = true;
                this.pos.y = - (this.figure.length + 1);
            } else {
                this.reset();
            }
        }
        shiftCounter = 0;
    },

    move(dir) {
        this.pos.x += dir;
        if(board.collide(this)) {
            this.pos.x -= dir;
        }
    },

    rotateLeft() {
        transpose(this.figure);
        this.figure.reverse();
    },

    rotateRight() {
        transpose(this.figure);
        this.figure.forEach(row => row.reverse());
    },

    reset() {
        const types = "ISZLJTO";
        this.figure = createFigure(types[types.length * Math.random() | 0]);
        this.pos.y = - this.figure.length;

        // move figure down to border of board
        let lastRowIsEmpty = true;
        for(let i = 0; i < this.figure.length; i++) {
            if(this.figure[this.figure.length - 1][i] !== 0) {
                lastRowIsEmpty = false;
                break;
            }
        }

        if (lastRowIsEmpty) {
            this.pos.y++;
        }

        this.pos.x =
            (board.area[0].length / 2 | 0) -
            (this.figure[0].length / 2 | 0);
    }
}


function draw() {
    ctx.fillStyle = colors.getColor(0);
    ctx.fillRect(0, 0, canvas_width, canvas_height);

    board.draw();
    block.draw();
}


let shiftCounter = 0;
const initialShiftInterval = 800;
let difficulty = 0;

let score = 0;
const scoreUpdateInterval = 200;
let scoreUpdateTimer = 0;

let lastTime = 0;
function update(/* number */ time) {
    if(difficulty > 90) difficulty = 90;

    const deltaTime = time - lastTime;
    lastTime = time;

    shiftCounter += deltaTime;
    scoreUpdateTimer += deltaTime;

    let shiftInterval = initialShiftInterval * (1 - difficulty / 100);

    if(shiftCounter >= shiftInterval) {
        block.shiftDown();
        board.sweep();
    }

    if(scoreUpdateTimer >= scoreUpdateInterval) {
        updateScore();
        scoreUpdateTimer = 0;
    }
}


let pause = false;
let finish = false;

function run(time = 0.) {
    if(pause === true){
        drawPauseScreen();
        return;
    }

    if(finish === true) {
        drawGameOverScreen();
        updateScoreboard();
        return;
    }

    update(time);
    draw();

    requestAnimationFrame(run);
}

function handleKeyboard(event) {
    if(finish) return;

    if(event.key === "Escape") {
        pause = !pause;
        if(!pause) {
            run();
        };
    }

    if(pause) return;

    switch (event.key) {
        case "ArrowUp":
            const pos = block.pos.x;

            block.rotateRight();
            let offset = 1;
            while(board.collide(block)) {
                block.pos.x += offset;
                offset = -(offset + (offset > 0 ? 1 : -1));
                if(offset > block.figure[0].length) {
                    block.rotateLeft();
                    block.pos.x = pos;
                    break;
                }
            }
            break;

        case "ArrowDown":
            block.shiftDown();
            break;

        case "ArrowLeft":
            block.move(-1)
            break;

        case "ArrowRight":
            block.move(1);
            break;

        default:
            console.log(event.key);
    }
}

function fillScreen() {
    ctx.fillStyle = "#000000A0";
    ctx.fillRect(0, 0, canvas_width, canvas_height);
}

function drawPauseScreen() {
    fillScreen();

    let font_size = canvas_width/5;

    ctx.font = `normal normal bold ${font_size}px sans-serif`;
    ctx.strokeStyle = outline_thickness / 2;

    ctx.fillStyle = "#F00";
    ctx.strokeStyle = "#000";
    ctx.textAlign = "center";

    ctx.fillText("Pause", canvas_width/2, canvas_height/2);
    ctx.strokeText("Pause", canvas_width/2, canvas_height/2);
}

function drawGameOverScreen() {
    fillScreen();

    let font_size = canvas_width/7;

    ctx.font = `normal normal bold ${font_size}px sans-serif`;
    ctx.strokeStyle = outline_thickness / 3;

    ctx.fillStyle = "#F00";
    ctx.strokeStyle = "#000";
    ctx.textAlign = "center";

    ctx.fillText("Game Over", canvas_width/2, canvas_height/2);
    ctx.strokeText("Game Over", canvas_width/2, canvas_height/2);
}

function updateScore() {
    document.getElementById("score").textContent = score;
}

function updateScoreboard() {
    scoreboard.push({nick: nickname, score: score});
    scoreboard.sort((a, b) => {
        let diff = b.score - a.score;
        if(diff === 0) {
            return a.nick > b.nick ? -1 : a.nick < b.nick ? -1 : 0;
        }
        return diff;
    })

    localStorage.setItem("scoreboard", JSON.stringify(scoreboard));
}