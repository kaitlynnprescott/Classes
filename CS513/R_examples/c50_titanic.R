#install.packages("C50")
Titanic <- read.csv('/Users/katieprescott/Desktop/CS513/R_examples/Titanic_rows.csv')

library('C50')

mytree<-C5.0(Survived~.,data=Titanic)
summary(mytree)
mytree
plot(mytree)

mytree<-C5.0(Survived~.,data=Titanic)
summary(mytree)
mytree
plot(mytree)