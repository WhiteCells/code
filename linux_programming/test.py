import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# 定义参数
beta = 1.0  # 可调参数

# 定义方程
def cstr(t, x):
    return 1 - x - beta * x

# 设置时间范围
t_span = (0, 10)
x0 = [0.1, 0.5, 0.9]  # 初始条件，可以设置多个

# 绘制相平面图
plt.figure(figsize=(8, 6))
for x_initial in x0:
    sol = solve_ivp(cstr, t_span, [x_initial], t_eval=np.linspace(0, 10, 400))
    plt.plot(sol.y[0], cstr(0, sol.y[0]), label=f'x0={x_initial}')

plt.axhline(0, color='black',linewidth=0.5)
plt.axvline(0, color='black',linewidth=0.5)
plt.xlabel('Concentration of A, x')
plt.ylabel('Rate of change of concentration, dx/dθ')
plt.title('Phase Plane Diagram for CSTR')
plt.legend()
plt.grid(True)
plt.show()
