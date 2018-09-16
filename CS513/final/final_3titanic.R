#########################################################################################
## File Name       : final_3titanic.R                                                  ##
## Name            : Kaitlynn Prescott                                                 ##
## Assignment      : Use ANN with 5 nodes to classify passengers                       ##
## Pledge          : I pledge my honor that I have abided by the Stevens honor system. ##
#########################################################################################

library(class)
library(neuralnet)
library(nnet)

######################
## Step 0: clean up ##
######################

rm(list=ls())

##########################
## Step 1: read in data ##
##########################

titanic <- read.csv('/Users/katieprescott/Desktop/CS513/datasets/Titanic_rows.csv', stringsAsFactors = TRUE)
titanic$iClass= as.integer(as.factor(titanic$Class))
titanic$iSex= as.integer(as.factor(titanic$Sex))
titanic$iAge= as.integer(as.factor(titanic$Age))
titanic$iSurvived= as.integer(as.factor(titanic$Survived))

##########################################
## Step 2: store test and training data ##
##########################################

# get every 5th data point
myData = seq(from=1, to=nrow(titanic), by=5) 
# store every 5th as test data set
test<-titanic[myData,]
# store every thing else as training data set
training<-titanic[-myData,]

#############################################
## Step 3: perform ann on training dataset ##
#############################################

training$survive = training$iSurvived == "2"
training$dead = training$iSurvived == "1"

ann = neuralnet(iSurvived~ iClass + iSex + iAge, training, hidden=5, threshold=0.1)

plot(ann)

ann_res <- compute(ann, test[, 5:7])
ann2=as.numeric(ann_res$net.result)

ann_round<-round(ann2)
ann_cat<-ifelse(ann2<1.4,1,2)


table(Actual=test$iSurvived,ann_round)
table(Actual=test$iSurvived,ann_cat)

wrong<- (test$iSurvived!=ann_cat)
rate<-sum(wrong)/length(wrong)

rate
