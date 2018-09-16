#scatterplots
x = c(0.2, 1.2, 0.9, 2.2, 6.2, 3.6, 5.3, 6.2, 7.1, 8.6, 9.0)
y = c(1.1, 2.3, 1.1, 3.6, 0.1, 4.8, 6.5, 7.8, 8.0, 9.4, 9.8)

plot(x, y, main = "Scatter Plot", xlab = "x-coordinates", ylab = "y-coordinates", pch=20)
abline(lm(y~x), col="red")
lines(lowess(x,y), col="blue")
