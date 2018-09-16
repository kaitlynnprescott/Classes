

#  Course    : 
#  First Name  : Khasha
#  Last Name  : Dehnad
#  Solution to assignment #3  


rm(list=ls())

 data(iris)
 length(iris)
 nrow(iris)
 

idx=seq(from=1,to=nrow(iris),by=5)
 
test<-iris[idx,]
training<-iris[-idx,]
library(class)

# use the head and the tail functions to examine the data
?head()
head(training,20)
head(test)
tail(test)
 

inputvalues<-training[,-5]
testvalues<-test[,-5]
outcomevalues<-training[,5]

mode(outcomevalues )
typeof(outcomevalues)
View(outcomevalues)
is.factor(outcomevalues)

# use knn to classify the data
#predict<-knn(inputvalues,testvalues,outcomevalues )

predict<-knn(training[,-5],test[,-5],training[,5],k=1)
 
 
# combine the prediction with the test data
results<-cbind(test, as.character(predict))
head(results)




# combine the prediction with the test data
?table()
table(Actual=results[,5],Prediction=results[,6])

wrong<-results[,5]!=results[,6]
 
rate<-sum(wrong)/length(wrong)

rate
 

# data were not normalized before. Normalize the data:

mmnorm <-function(x,minx,maxx) {z<-((x-minx)/(maxx-minx))
                     return(z) 
                    }

# test your function
x<-0:10
mmnorm(x,0,10)

tstdata<- as.matrix(0:10)
mmnorm(x,min(x),max(x))

#create a new dataset with
species<-iris[,5]
mode(species)
is.factor(species)


newdata<-cbind(  Sepal.Length=mmnorm(iris[,1],min(iris[,1]),max(iris[,1]))
                , sepal.Width=mmnorm(iris[,2],min(iris[,2]),max(iris[,2] ))
                ,Petal.Length=mmnorm(iris[,3],min(iris[,3]),max(iris[,3] ))
                , Petal.Width=mmnorm(iris[,4],min(iris[,4]),max(iris[,4] ))
                ,as.character(species) 
              )

 
idx=seq(from=1,to=150,by=5)

newtest <- newdata[idx,]
newtraining <- newdata[-idx,]

?knn()
## you can choose different 'k' to find the best 'k'


newpredict<-knn(newtraining[,-5],newtest[,-5],newtraining[,5],k=1)

newresults<-cbind(newtest,as.character(newpredict) )
head(newresults)

table(newresults[,5],newresults[,6])
wrong<-newresults[,5]!=newresults[,6]

rate<-sum(wrong)/length(wrong)
rate
## you can try different training and test dataset by chosing different 'from' or by
idx2=seq(from=5,to=150,by=5)
newtest2 <- newdata[idx2,]
newtraining2 <- newdata[-idx2,]

 
newpredict2<-knn(newtraining2[,-5],newtest2[,-5],newtraining2[,5],k=100)

newresults2<-cbind(newtest2,as.character(newpredict2) )
head(newresults2)

table(newresults2[,5],newresults2[,6])

rates<-rbind()

for (i in c(1,5,10)) {
   newpredict<-knn(newtraining[,-5],newtest[,-5],newtraining[,5],k=i)
   newresults<-cbind(newtest,as.character(newpredict) )
   wrong<-newresults[,5]!=newresults[,6]
   rate<-sum(wrong)/length(wrong)
  print(i) 
  print(rate)
  rates<-rbind(rates,rate)
}
