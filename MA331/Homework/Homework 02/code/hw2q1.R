#actual
x <- c(20, 30, 50, 100)
pbinom(8.25, size = x, prob = 0.4)

#approximations
n <- c(20, 30, 50, 100)
np <- (n*0.4)
npp <- (np*0.6)
num <- (8.25 - np)
denom <- sqrt(npp)

pnorm((num/denom), mean = 0, sd = 1)

#errors
a <- c(5.955987e-01, 9.401122e-02, 2.305229e-04, 5.431127e-13)
b <- c(5.454243e-01, 8.112525e-02, 3.470073e-04, 4.557597e-11)
z <- c(20, 30, 50, 100)
error <- a - b
plot(z, error)
error

