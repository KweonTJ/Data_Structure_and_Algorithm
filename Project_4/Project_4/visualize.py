import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# ───── 파일 로드 ──────────────────────────────────────────
root   = Path(__file__).parent        # visualize.py 위치
obs    = np.loadtxt(root / "map.txt",       skiprows=1, dtype=int)
path_A = np.loadtxt(root / "path_A.txt",    dtype=int)   # A*
path_D = np.loadtxt(root / "path_D.txt",    dtype=int)   # Dijkstra
path_R = np.loadtxt(root / "path_R.txt",    dtype=float) # RRT*

# ───── 그림 설정 ──────────────────────────────────────────
fig, ax = plt.subplots(figsize=(6, 6))
ax.set_xticks(range(21)); ax.set_yticks(range(21))
ax.grid(ls=':', color='lightgray')
ax.set_xlim(0, 20); ax.set_ylim(0, 20)
ax.set_aspect('equal'); ax.invert_yaxis()

# ───── 장애물 사각형 ──────────────────────────────────────
for l, t, r, b in obs:
    ax.add_patch(
        plt.Rectangle(
            (l - 1, t - 1),           # 좌상단
            r - l + 1, b - t + 1,     # 너비, 높이
            fc='gray', ec='k', alpha=.35
        )
    )

# ───── 경로 플롯 ──────────────────────────────────────────
ax.plot(path_A[:, 1] - .5, path_A[:, 0] - .5,
        'ro-',  lw=1.5,  label='A*')
ax.plot(path_D[:, 1] - .5, path_D[:, 0] - .5,
        'g-.', lw=1.5,  label='Dijkstra')
ax.plot(path_R[:, 1] - .5, path_R[:, 0] - .5,
        'b--', lw=1.5,  label='RRT*')

# ───── 마무리 ────────────────────────────────────────────
ax.legend(loc='upper left')
plt.tight_layout()
plt.show()
