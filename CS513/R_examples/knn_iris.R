
#  Course          : CS 513
#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         : apply knn to iris dataset

## Step 0 clean up!!!


rm(list=ls())


## Define a funcition!!!

mmnorm <-function(x,minx,maxx)
       {z<-((x-minx)/(maxx-minx))
        return(z)                              
}

mmnorm(5,0,10)
x<-0:10
mmnorm(x,min(x),max(x))


# look at list of packages 
#installed.packages()
#install.packages("ggplot2")

library(ggplot2)

library(class)
?knn()


data()
data(iris)
View(iris)



?sample()
range_1_100<- 1:100
smpl80 <- sort(sample(range_1_100,80))
?sort()



idx<-sort(sample(nrow(iris),as.integer(.70*nrow(iris))))

training<-iris[idx,]

test<-iris[-idx,]

library(class)
?knn()

#training2<-training[,-5]
#test2<-test[,-5]
#outcome<-training[,5]
#knn(training[,-5],test[,-5],training[,5],k=50)

predict<-knn(training[,-5],test[,-5],training[,5],k=3)

table(Prediction=predict,Actual=test[,5] )


