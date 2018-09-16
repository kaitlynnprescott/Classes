#########################################################################################
## File Name       : midterm.R
## Name            : Kaitlynn Prescott
## Assignment      : Use knn to classify the breast cancer dataset
## Pledge          : I pledge my honor that I have abided by the Stevens honor system.
#########################################################################################

library(class)
#install.packages('VIM')
library(VIM)
install.packages('modeest')
library(modeest)
######################
## Step 0: clean up ##
######################

rm(list=ls())

##########################
## Step 1: read in data ##
##########################

bc <- read.csv('/Users/katieprescott/Desktop/CS513/midterm/breast-cancer-wisconsin.data.csv', na.strings = '?')
# delete rows with question marks
bc<-bc[complete.cases(bc),]
bc = bc[,-1]

##########################################
## Step 2: store test and training data ##
##########################################

# get every 5th data point
myData = seq(from=1, to=nrow(bc), by=5) 
# store every 5th as test data set
test<-bc[myData,]
# store every thing else as training data set
training<-bc[-myData,]

############################################
## Step 3: use knn with k = 5 to classify ##
############################################

knn1<-knn(training[,-10], test[,-10], training[,10], k=5)
knn1

########################################
## Step 4: measure performance of knn ##
########################################

err1<-1-sum(test[,10]==knn1)/length(knn1)
err1

# show prediction vs test
table(Prediction=knn1,Actual=test[,10] )



