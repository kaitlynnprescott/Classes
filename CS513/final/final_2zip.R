#########################################################################################
## File Name       : final_2zip.R                                                      ##
## Name            : Kaitlynn Prescott                                                 ##
## Assignment      : Use Hierarchical Clustering and Kmeans to cluster NJ zip codes    ##
## Pledge          : I pledge my honor that I have abided by the Stevens honor system. ##
#########################################################################################

library(class)
library(ggplot2)

######################
## Step 0: clean up ##
######################

rm(list=ls())

##########################
## Step 1: read in data ##
##########################

zip <- as.data.frame(read.csv('/Users/katieprescott/Desktop/CS513/datasets/NJ_zip_median_income.csv'))

####################################
## Step 2: categorize with hclust ##
####################################

clustersP <- hclust(dist(zip[, 2:2]), method='average')
#plot(clustersP)

######################################
## Step 3: separate into 3 clusters ##
######################################

clusterCutP <- cutree(clustersP, 3)
table(clusterCutP, zip[,2])

#ggplot(zip, aes(Median, Mean, color = zip$Zip)) + 
 # geom_point(alpha = 0.4, size = 3.5) + geom_point(col = clusterCutP) + 
  #scale_color_manual(values = c('blue', 'red', 'green'))


####################################
## Step 4: categorize with kmeans ##
####################################

med = as.data.frame(zip[,-2])
pop = as.data.frame(med[,-3])

kmeans_3 <- kmeans(pop, 3, nstart=10)
kmeans_3$cluster
table(kmeans_3$cluster,zip$Pop)
table(kmeans_3$cluster,zip$Zip)
