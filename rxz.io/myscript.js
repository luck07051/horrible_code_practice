var zx, zy, inx, iny, textr, texte;
var inTimes = 0,
    outTimes = 0;

function main() {
    //input
    inx = document.getElementById("R").value;
    iny = document.getElementById("X").value;
    document.getElementById("R").innerHTML='';
    document.getElementById("X").innerHTML='';

    //輸入的電抗顯示
    var text;
    inTimes++;
    if (iny > 0)
        text = inx + '+j' + iny + 'Ω';
    else if (iny < 0)
        text = inx + '-j' + iny * -1 + 'Ω';
    else
        text = inx + 'Ω';
    document.getElementById('inZ').innerHTML += '<tr><td>#' + inTimes + '</td><td>' + text + '</td></tr>';

    //計算
    if (typeof zx == 'undefined') {
        zx = inx;
        zy = iny;
    } else {
        var mulx = zx * inx - zy * iny,
            muly = zy * inx + zx * iny,
            addx = zx * 1 + inx * 1,
            addy = zy * 1 + iny * 1;
        var A = addx * addx + addy * addy;
        zx = (mulx * addx + muly * addy) / A;
        zy = (muly * addx - mulx * addy) / A;
    }

    //顯示
    //坐標
    if (zy > 0)
        textr = zx + '+j' + zy + 'Ω';
    else if (zy < 0)
        textr = zx + '-j' + zy * -1 + 'Ω';
    else
        textr = zx + 'Ω';
    //向量
    if (zy != 0)
        texte = Math.sqrt(zx * zx + zy * zy) + '∠' + Math.atan2(zy, zx) * 180 / Math.PI + '°';
    else
        texte = zx + '∠0°Ω'
    document.getElementById("ans").innerHTML = 'Z=' + textr + '<br>&nbsp&nbsp&nbsp=' + texte;
    return;
}

function next() {
    if (textr != undefined && texte != undefined) {
        //輸出的電抗顯示
        outTimes++;
        var outtext = textr + '<br>' + texte;
        document.getElementById('outZ').innerHTML += '<tr><td>#' + outTimes + '</td><td>' + outtext + '</td></tr>';

        //reset
        document.getElementById('inZ').innerHTML = '<th>輸入</th>';
        document.getElementById("ans").innerHTML = 'Z=';
        inTimes = 0;
        zx = undefined;
        zy = undefined;
        textr = undefined;
        texte = undefined;
    }
}
