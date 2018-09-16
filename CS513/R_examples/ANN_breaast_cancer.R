#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         : running ANN on breast cancer data

remove(list=ls())

bc<-
  read.csv("/Users/katieprescott/Desktop/CS513/midterm/breast-cancer-wisconsin.data.csv",
           na.strings = "?")

### perform EDS

summary(bc)
mean(bc$F2)
mean(bc$F6)
apply(bc[,c(-1,-11)],2,mean)


### remove all the records with missing value
### see mfv and median for other strategies
?na.omit()
bc2<-na.omit(bc)

index <- seq (1,nrow(bc2),by=5)
test<-bc2[index,]
training<-bc2[-index,]


library("neuralnet")
?neuralnet()
class(training$Class)
net_bc2  <- neuralnet(Class~F1+F2+F3+F4+F5+F6+F7+F8+F9
                     ,training, hidden=5, threshold=0.01)




#Plot the neural network
plot(net_bc2)

net_bc2_results <-compute(net_bc2, test[,c(-1,-11)]) 
ANN=as.numeric(net_bc2_results$net.result)


ANN_round<-round(ANN)
ANN_cat<-ifelse(ANN<2.5,2,4)
  


table(Actual=test$Class,ANN_round)
table(Actual=test$Class,ANN_cat)

wrong<- (test$Class!=ANN_cat)
rate<-sum(wrong)/length(wrong)

