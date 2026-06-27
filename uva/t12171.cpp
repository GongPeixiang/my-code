#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXN = 55, MAXL = 1001;
constexpr int dx[6] = {1, -1, 0, 0, 0, 0}, dy[6] = {0, 0, 1, -1, 0, 0}, dz[6] = {0, 0, 0, 0, 1, -1};

int n; ll s = 0, v = 0;
int mx, my, mz, xh[MAXN*2], yh[MAXN*2], zh[MAXN*2];
bool buf[MAXN*2][MAXN*2][MAXN*2], vis[MAXN*2][MAXN*2][MAXN*2];
struct Box {
    int x0, y0, z0;
    int x, y, z;
} box[MAXN];
struct Cell { int x, y, z; };

inline ll get_vol(int i, int j, int k) {
    ll xl = xh[i+1] - xh[i], yl = yh[j+1] - yh[j], zl = zh[k+1] - zh[k];
    return xl * yl * zl;
}

inline ll get_surf_area(int i, int j, int k, int dir) {
    ll xl = xh[i+1] - xh[i], yl = yh[j+1] - yh[j], zl = zh[k+1] - zh[k];
    if (dir == 0 || dir == 1) return yl * zl; // ±x: yz 平面
    else if (dir == 2 || dir == 3) return xl * zl;
    else return xl * yl;
}

void preprocess() {
    xh[2*n+1] = yh[2*n+1] = zh[2*n+1] = MAXL;
    sort(xh, xh + 2 * n + 2); sort(yh, yh + 2 * n + 2); sort(zh, zh + 2 * n + 2);
    mx = unique(xh, xh + 2 * n + 2) - xh - 1;
    my = unique(yh, yh + 2 * n + 2) - yh - 1;
    mz = unique(zh, zh + 2 * n + 2) - zh - 1;
    for (int ii = 1; ii <= n; ++ii) {
        int xs = lower_bound(xh, xh + mx + 1, box[ii].x0) - xh;
        int xe = lower_bound(xh, xh + mx + 1, box[ii].x0 + box[ii].x) - xh;
        int ys = lower_bound(yh, yh + my + 1, box[ii].y0) - yh;
        int ye = lower_bound(yh, yh + my + 1, box[ii].y0 + box[ii].y) - yh;
        int zs = lower_bound(zh, zh + mz + 1, box[ii].z0) - zh;
        int ze = lower_bound(zh, zh + mz + 1, box[ii].z0 + box[ii].z) - zh;
        // 修正:确保结束索引不超过点数
        if (xe > mx) xe = mx;
        if (ye > my) ye = my;
        if (ze > mz) ze = mz;
        for (int i = xs; i < xe; ++i) 
            for (int j = ys; j < ye; ++j) 
                for (int k = zs; k < ze; ++k) 
                    buf[i][j][k] = true;
    }
    v = (xh[mx] - xh[0]) * (yh[my] - yh[0]) * (zh[mz] - zh[0]);
}

// 格子的索引和点的索引
void bfs(int x, int y, int z) {
    ll sa = 0, va = 0;
    queue<Cell> q;
    vis[x][y][z] = true;
    q.push(Cell{x, y, z});
    while (!q.empty()) {
        Cell cur = q.front(); q.pop();
        va += get_vol(cur.x, cur.y, cur.z);
        for (int i = 0; i < 6; ++i) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i], nz = cur.z + dz[i];
            if (nx < 0 || nx >= mx || ny < 0 || ny >= my || nz < 0 || nz >= mz) continue;
            if (!vis[nx][ny][nz]) {
                if (!buf[nx][ny][nz]) {
                    vis[nx][ny][nz] = true;
                    q.push(Cell{nx, ny, nz});
                }
                else sa += get_surf_area(cur.x, cur.y, cur.z, i);
            }
        }
    }
    v -= va; s = sa;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        memset(buf, 0, sizeof(buf));
        memset(vis, 0, sizeof(vis));
        memset(xh, 0, sizeof(xh));
        memset(yh, 0, sizeof(yh));
        memset(zh, 0, sizeof(zh));
        v = 0, s = 0;
        cin >> n;
        xh[0] = yh[0] = zh[0] = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> box[i].x0 >> box[i].y0 >> box[i].z0 >> box[i].x >> box[i].y >> box[i].z;
            xh[i*2-1] = box[i].x0, xh[i*2] = box[i].x0 + box[i].x;
            yh[i*2-1] = box[i].y0, yh[i*2] = box[i].y0 + box[i].y;
            zh[i*2-1] = box[i].z0, zh[i*2] = box[i].z0 + box[i].z;
        }
        preprocess();
        bfs(0, 0, 0);
        cout << s << ' ' << v << '\n';
    }
}