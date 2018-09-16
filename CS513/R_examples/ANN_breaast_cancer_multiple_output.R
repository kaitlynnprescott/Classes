
#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         : running c5.0 on breast cancer data
#                  : Two output nodes


remove(list=ls())

bc<-
  read.csv("C://AIMS/Stevens_/2017_Fall_DataMining_I/Raw_data/breast-cancer-wisconsin.data.csv",
           na.strings = "?")

### perform EDS

summary(bc)
mean(bc$F2)
mean(bc$F6)
apply(bc[,c(-1,-11)],2,mean)


### remove all the records with missing value
### see mfv and median for other strategies
?na.omit()


benign<-ifelse(bc$Class==2,1,0)
malignant<-ifelse(bc$Class==4,1,0)

bc2<- na.omit(data.frame(bc,benign,malignant))

index <- seq (1,nrow(bc2),by=5)
test<-bc2[index,]
training<-bc2[-index,]


library("neuralnet")
?neuralnet()

net_bc2  <- neuralnet(benign+malignant~F1+F2+F3+F4+F5+F6+F7+F8+F9
                      ,training, hidden=5, threshold=0.01)


 

#Plot the neural network
plot(net_bc2)

net_bc2_results <-compute(net_bc2, test[,c(-1,-11,-12,-13)]) 
class(net_bc2_results$net.result)
 

str(net_bc2_results)

resutls<-data.frame(Actual_Benign=test$benign,
                    Actual_Malignant=test$malignant,
                    ANN_Benign=round(net_bc2_results$net.result[,1]),
                    ANN_Malignant=round(net_bc2_results$net.result[,2]))


resutls2<-data.frame(Actual_Benign=test$benign,
                    Actual_Malignant=test$malignant,
                    ANN_Benign=round(net_bc2_results$net.result[,1]),
                    ANN_Malignant=round(net_bc2_results$net.result[,2])
                    ,Prediction=ifelse(round(net_bc2_results$net.result[,1])==1,'B','M'))

table(Actual=resutls2$Actual_Malignant,Prediction=resutls2$Prediction)

wrong<- (round(net_bc2_results$net.result[,1])!=test$benign )
error_rate<-sum(wrong)/length(wrong)
error_rate
