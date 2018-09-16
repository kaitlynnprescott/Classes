#########################################################################################
## File Name       : final_4bc.R                                                       ##
## Name            : Kaitlynn Prescott                                                 ##
## Assignment      : Use Random Forrest to classify breast cancer dataset              ##
## Pledge          : I pledge my honor that I have abided by the Stevens honor system. ##
#########################################################################################

library(class)
library(randomForest)

######################
## Step 0: clean up ##
######################

rm(list=ls())

##########################
## Step 1: read in data ##
##########################

bc <- read.csv('/Users/katieprescott/Desktop/CS513/datasets/wisc_bc_ContinuousVar.csv', na.strings = '?')
# delete rows with question marks
bc<-bc[complete.cases(bc),]
bc = bc[,-1]
set.seed(321)

##########################################
## Step 2: store test and training data ##
##########################################

# get every 5th data point
myData = seq(from=1, to=nrow(bc), by=5) 
# store every 5th as test data set
test<-bc[myData,]
# store every thing else as training data set
training<-bc[-myData,]

###########################################
## Step 3: use random forest to classify ##
###########################################

diagnosisCol = 1
newtraining = as.data.frame(training[,-diagnosisCol])
trainingLabels = as.factor(unlist(training[,diagnosisCol]))
testValues = as.data.frame(test[,diagnosisCol])
testLabels = as.factor(unlist(test[,diagnosisCol]))

fit <- randomForest(newtraining,trainingLabels,ntree=1000)

#importance(fit)
#varImpPlot(fit)

Prediction <- predict(fit, test)
Prediction

table(prediction=Prediction,Actual=test[,10])

wrong = (testLabels != Prediction)
wrong

rate = sum(wrong)/length(wrong)
rate




