#########################################################
##  Purpose: Create pretty classification tree
##  Developer: KD         
##
#########################################################

#########################################################
##  Step 0: Clear the environment
##           
##
#########################################################
rm(list=ls())


#########################################################
##  Step 1: Load the relavent packages
##           
##
#########################################################
installed.packages()

install.packages("rpart")  # CART standard package


#install.packages("rpart")
#install.packages("rpart.plot")     # Enhanced tree plots
#install.packages("rattle")         # Fancy tree plot
#install.packages("RColorBrewer")   # colors needed for rattle
library(rpart)
library(rpart.plot)  			# Enhanced tree plots
library(rattle)           # Fancy tree plot
library(RColorBrewer)     # colors needed for rattle
  
#########################################################
 
##  Step 2:  example
##           
##
#########################################################
 


rm(list=ls())

dsn<-
  read.csv("C://AIMS/Stevens_/CS513_datamining/Other/Titanic_rows.csv")
 

#View(dsn) 
#attach(dsn)
#detach(dsn)


table(dsn$Survived)

#Grow the tree 
mytree<-rpart( Survived~.,data=dsn)

mytree

# use the table to interpret the resutls.

table(dsn$Survived,dsn$Sex)

# plot the tree
#?rpart()
## default plotting is not very good.
#plot(mytree)
#text(mytree)

## a better plot
library(rpart.plot)
prp(mytree)


# much fancier graph
fancyRpartPlot(mytree)

 
