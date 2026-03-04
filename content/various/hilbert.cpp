/**
 * Author: Vannes
 * Date: 2025-10-27
 * License: CC0
 * Description: Use this as the comparator for Mo algorithm
 */
const int LN = 20;
int hilbert(int x, int y) {
    int d = 0;
    for (int s = 1LL << (LN - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s; d = d << 2 | rx * 3 ^ ry;
        if (ry) continue;
        if (rx) { x = (1 << LN) - x; y = (1 << LN) - y; }
        swap(x, y);
    }
    return d;
}
