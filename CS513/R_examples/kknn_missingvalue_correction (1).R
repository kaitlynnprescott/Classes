
#  Course          : CS 513
#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         : apply kknn to iris dataset



## remove all objects
rm(list=ls())


# check to see if you have the kknn package
installed.packages()
#install.packages("kknn")
#Use the R library("kknn") 

library(kknn)
?kknn()
#Load the iris dataset and attach it
data(iris)
View(iris)
 Sepal.Length

attach(iris)
 
##Define max-min normalization function
mmnorm <-function(x,minx,maxx) {z<-((x-minx)/(maxx-minx))
                                return(z) 
}


#Create Normalized data
iris_normalized_nospecies<-as.data.frame (         
  cbind( Sepal.Length=mmnorm(iris[,1],min(iris[,1]),max(iris[,1]))
         , sepal.Width=mmnorm(iris[,2],min(iris[,2]),max(iris[,2] ))
         ,Petal.Length=mmnorm(iris[,3],min(iris[,3]),max(iris[,3] ))
         , Petal.Width=mmnorm(iris[,4],min(iris[,4]),max(iris[,4] ))
        
  )
)       

 


index <- seq (1,nrow(iris_normalized_nospecies ),by=10)


 test<-iris_normalized_nospecies[index,]
is.data.frame(test)
missing<-test

 missing[,1]<-NA
  
training <-iris_normalized_nospecies[-index,]
?kknn() 

predict_k5 <- kknn(formula=Sepal.Length~., training, missing, kernel="rectangular", k=5)


#Extract fitted values from the object "predict_k1"
fit <- fitted(predict_k5)

newvalues<-cbind(fit,Missing=missing[,1],original=test[,1] )

 


rm(list=ls())