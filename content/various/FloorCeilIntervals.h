/**
 * Author: Jelefy
 * Date: 2025-10-30
 * License: CC0
 * Description: Iterate through every $[l,r]$ such that $\forall x\in[l,r],\left\lfloor\frac nx\right\rfloor=\left\lfloor\frac nl\right\rfloor$. Similarly for $\lceil\rceil$.
 * Time: O(\sqrt n)
 */
#pragma once

void FloorCeilIntervals(int n) {
	for (int l = 1, r; l <= n; l = r + 1) { // floor
		int val = n / l; r = n / val;
	}
	for (int r = n, l; r > 0; r = l - 1) { // ceil
		int val = (n + r - 1) / r; l = (n + val - 1) / val;
	}
}
