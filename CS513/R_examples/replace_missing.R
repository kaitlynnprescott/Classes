
#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         : replacing missing values with knn and mode


remove(list=ls())

## Step 1 load the data
## changing ? to NA

bc<-
  read.csv("C://AIMS/Stevens_/2017_Fall_DataMining_I/Raw_data/breast-cancer-wisconsin.data.csv",
           na.strings = "?")


#install.packages('VIM')
library('VIM')
?kNN



bc2<-kNN(bc,variable ='F6',
         dist_var=c('F1','F2','F3','F4','F5','F7','F8','F9'))

#install.packages("modeest")
library(modeest)
?mlv()
str(mode1)
mode1<-mfv(bc$F6) 



