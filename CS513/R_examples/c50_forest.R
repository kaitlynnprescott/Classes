rm(list=ls())


library('C50')

forest_data <- read.csv('/Users/katieprescott/Desktop/CS513/R_examples/forest_data_example.csv')

mytree<- C5.0(Target~F1+F2, data = forest_data)
plot(mytree)

mytree<- C5.0(Target~F2+F3, data = forest_data)
plot(mytree)

mytree<- C5.0(Target~F3+F4, data = forest_data)
plot(mytree)
