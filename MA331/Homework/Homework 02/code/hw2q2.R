# n = 20

v <- rep(0, times = 100)
m <- rep(0, times = 100)
for (i in 1:100)
{
  n2 <- rnorm(20, mean = 2, sd = 3)
  v2 <- var(n2)
  v[i] <- v2
  m2 <- mean(n2)
  m[i] <- m2
}
plot(v, type = 'l', xlab = 'Test Number', ylab = 'Sample Variance', xlim = range(0:100), ylim = range(0:20), main = 'Variance when n = 20')
plot(m, type = 'l', xlab = 'Test Number', ylab = 'Sample Mean', xlim = range(0:100), ylim = range(0:4), main = 'Mean when n = 20')


# n = 30

v <- rep(0, times = 100)
m <- rep(0, times = 100)
for (i in 1:100)
{
  n3 <- rnorm(20, mean = 2, sd = 3)
  v3 <- var(n3)
  v[i] <- v3
  m3 <- mean(n3)
  m[i] <- m3
}
plot(v, type = 'o', xlab = 'Test Number', ylab = 'Sample Variance', xlim = range(0:100), ylim = range(0:20), main = 'Variance when n = 30')
plot(m, type = 'o', xlab = 'Test Number', ylab = 'Sample Mean', xlim = range(0:100), ylim = range(0:4), main = 'Mean when n = 30')



# n = 50

v <- rep(0, times = 100)
m <- rep(0, times = 100)
for (i in 1:100)
{
  n5 <- rnorm(20, mean = 2, sd = 3)
  v5 <- var(n5)
  v[i] <- v5
  m5 <- mean(n5)
  m[i] <- m5
}
plot(v, type = 'o', xlab = 'Test Number', ylab = 'Sample Variance', xlim = range(0:100), ylim = range(0:20), main = 'Variance when n = 50')
plot(m, type = 'o', xlab = 'Test Number', ylab = 'Sample Mean', xlim = range(0:100), ylim = range(0:4), main = 'Mean when n = 50')
