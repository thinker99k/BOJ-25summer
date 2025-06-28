const fs = require('fs');

let n;
let parent, v, e;

function Find(v) {
    if (parent[v] === v) {
        return v;
    } else {
        parent[v] = Find(parent[v]); // 경로압축
        return parent[v];
    }
}

function Union(u, v) {
    const root_u = Find(u);
    const root_v = Find(v);

    if (root_u !== root_v) {
        if (root_u < root_v) {
            parent[root_v] = root_u;
        } else {
            parent[root_u] = root_v;
        }
        // 루트가 같지 않으면 -> union 성공 -> true 반환
        return true;
    } else {
        // 루트가 같으면 -> union 실패 -> false 반환
        return false;
    }
}


function distance(x1, x2, y1, y2) {
    return Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
}

function kruskal() {
    for (let i = 0; i < n; i++) {
        parent[i] = i;
    }

    e.sort((e1, e2) => e1[0] - e2[0]);

    let ret = 0.0;

    for (const it of e) {
        if (Union(it[1], it[2])) {
            ret += it[0];
        }
    }

    return ret;
}

function main() {
    let input = fs.readFileSync('/dev/stdin').toString().split('\n');
    n = Number(input[0]);

    parent = new Array(n);
    v = new Array(n);
    e = [];

    for (let i = 1; i <= n; i++) {
        let line = input[i].split(' ');
        v[i - 1] = [Number(line[0]), Number(line[1])];
    }

    for (let i = 0; i < n - 1; i++) {
        for (let j = i + 1; j < n; j++) {
            e.push([distance(v[i][0], v[j][0], v[i][1], v[j][1]), i, j]);
        }
    }

    console.log(kruskal().toFixed(2));
}

main();