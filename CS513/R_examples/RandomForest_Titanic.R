#install.packages('randomForest')

library(randomForest)

Titanic <- read.csv('/Users/katieprescott/Desktop/CS513/R_examples/Titanic_rows.csv')

set.seed(321)

index <- seq(1, nrow(Titanic), by=5)
test<-Titanic[index,]
training<-Titanic[-index,]

fit <- randomForest(Survived~., data = training, importance = TRUE, ntree= 2000)
importance(fit)
varImpPlot(fit)
Prediciton <- predict(fit, test)
#table(actual test[ 4] prediction)


