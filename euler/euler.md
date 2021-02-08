# Euler法

関数$f(x)$は$f(x)=0$における解近傍$\alpha$において$C^2$級とする。 



ニュートン法は
$$
\begin{align}
\frac{dx}{dt}&= \lim_{\Delta t\to0}\frac{f(x+\Delta t) - f(x)}{\Delta t} \\
\frac{dx}{dt}&=\frac{f(x+\Delta t) - f(x)}{\Delta t} = f'(x, t)\ \ \  (\because \ \Delta t\to0)\\
f(x+\Delta t) &= \frac{dx}{dt} \Delta t + f(x)\\
\end{align}
$$

離散で考えると、
$$
\begin{align}
f(x_1) &= f'(x_0)\Delta t + f(x_0)
\end{align}
$$
となる。



オイラー法は同じように微分を差分商で近似
$$
y_{t+1} = y_t + h f(x_t, y_t)
$$




