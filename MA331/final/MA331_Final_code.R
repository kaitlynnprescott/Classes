#11.42
getwd()
setwd("/Users/katieprescott/Desktop/stats_final")
pcbtable <- read.csv("pcb.csv", header = TRUE, sep = ",")
View(pcbtable)

summary(pcbtable$pcb)
#Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
#6.10   30.18   47.96   68.47   91.63  318.70 
summary(pcbtable$pcb52)
#Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
#0.020   0.228   0.477   0.958   0.892   9.060 
summary(pcbtable$pcb118)
#Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
#0.236   1.490   2.420   3.256   3.890  18.900 
summary(pcbtable$pcb138)
#Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
#0.640   3.180   4.920   6.827   8.650  32.300 
summary(pcbtable$pcb180)
#Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
#0.395   1.240   2.690   4.158   4.490  31.500 

boxplot(pcbtable$pcb, main="Boxplot of PCB", ylab="PCB")
boxplot(pcbtable$pcb53, main="Boxplot of PCB52", ylab="PCB52")
boxplot(pcbtable$pcb118, main="Boxplot of PCB118", ylab="PCB118")
boxplot(pcbtable$pcb138, main="Boxplot of PCB138", ylab="PCB138")
boxplot(pcbtable$pcb180, main="Boxplot of PCB180", ylab="PCB180")

cor(pcbtable$pcb, pcbtable$pcb52) 
cor(pcbtable$pcb, pcbtable$pcb118)
cor(pcbtable$pcb, pcbtable$pcb138)
cor(pcbtable$pcb, pcbtable$pcb180)

cor(pcbtable$pcb52, pcbtable$pcb118)
cor(pcbtable$pcb52, pcbtable$pcb138)
cor(pcbtable$pcb52, pcbtable$pcb180)

cor(pcbtable$pcb118, pcbtable$pcb138)
cor(pcbtable$pcb118, pcbtable$pcb180)

cor(pcbtable$pcb138, pcbtable$pcb180)

plot(pcbtable$pcb52, pcbtable$pcb, main="Scatterplot of PCB vs PCB52", xlab="PCB52", ylab="PCB")
plot(pcbtable$pcb118, pcbtable$pcb, main="Scatterplot of PCB vs PCB118", xlab="PCB118", ylab="PCB")
plot(pcbtable$pcb138, pcbtable$pcb, main="Scatterplot of PCB vs PCB138", xlab="PCB138", ylab="PCB")
plot(pcbtable$pcb180, pcbtable$pcb, main="Scatterplot of PCB vs PCB180", xlab="PCB180", ylab="PCB")
plot(pcbtable$pcb118, pcbtable$pcb52, main="Scatterplot of PCB52 vs PCB118", xlab="PCB118", ylab="PCB52")
plot(pcbtable$pcb138, pcbtable$pcb52, main="Scatterplot of PCB52 vs PCB138", xlab="PCB138", ylab="PCB52")
plot(pcbtable$pcb180, pcbtable$pcb52, main="Scatterplot of PCB52 vs PCB180", xlab="PCB180", ylab="PCB52")
plot(pcbtable$pcb138, pcbtable$pcb118, main="Scatterplot of PCB118 vs PCB138", xlab="PCB138", ylab="PCB118")
plot(pcbtable$pcb180, pcbtable$pcb118, main="Scatterplot of PCB118 vs PCB180", xlab="PCB180", ylab="PCB118")
plot(pcbtable$pcb180, pcbtable$pcb138, main="Scatterplot of PCB138 vs PCB180", xlab="PCB180", ylab="PCB138")

#11.43
newpcb = subset(pcbtable, select=c("pcb", "pcb52", "pcb118", "pcb138", "pcb180"))
lm1 = lm(pcb ~ pcb52 + pcb118 + pcb138 + pcb180, data=newpcb)
summary(lm1)

anova(lm1)

qqnorm(residuals(lm1))
plot(lm1, which=2)

#11.44
plot(lm1)
#change data file-- take out the outliers.
newtable <- read.table("pcb2.csv", header=TRUE)
lm1 <- lm(pcb ~ (pcb52+pcb118+pcb138+pcb180), data=newtable)
summary(lm1)

#11.45
lm2 <- lm(pcb ~ (pcb52 + pcb118 + pcb138), data=pcbtable)
summary(lm2)

#11.46
lm4 <- lm(teq ~ (teqpcb + teqdioxin + teqfuran), data=pcbtable)
summary(lm4)

anova(lm4)

#11.47
lm5 <- lm(teq ~ (pcb52 + pcb118 + pcb138 + pcb180), data=pcbtable)
summary(lm5)

summary(aov(lm5))

#11.48
#change pcb file again-- replace 0 values in PCB126 and use 1/2 the smallest non-zero value observed for each
dl <- read.csv("pcb3.csv", header=TRUE)
sdl <- subset(dl, select=c("LOG.pcb", "LOG.pcb28", "LOG.pcb52", "LOG.pcb118", "LOG.pcb126", "LOG.pcb138", "LOG.pcb153", "LOG.pcb180", "LOG.teq"))
summary(sdl)
boxplot(sdl)
                            
#11.49
sdl <- subset(dl, select=c("pcb", "LOG.pcb", "LOG.pcb28", "LOG.pcb52", "LOG.pcb118", "LOG.pcb126", "LOG.pcb138", "LOG.pcb153", "LOG.pcb180"))
pairs(sdl, pch=".")
cor(sdl)

#11.50
table3<-read.csv("pcb4.csv", header = TRUE)
lm6 <- lm(teq ~ (LN.pcb + LN.pcb52 + LN.pcb118 + LN.pcb138 + LN.pcb153 + LN.pcb180), data=table3)
summary(lm6)

#11.51
#change pcb file
dl <- read.csv("pcb3.csv", header = TRUE)
sdl<- subset(dl, select=c("LOG.teq", "LOG.pcb126", "LOG.pcb28"))
lm7 <- lm(LOG.teq ~ (LOG.pcb126 + LOG.pcb28), data=sdl)
summary(lm7)
anova(lm7)
                      
#11.52
dl <- read.csv("pcb3.csv", header = TRUE)
sdl <- subset(dl, select=c("LOG.teq", "LOG.pcb28", "LOG.pcb52", "LOG.pcb118", "LOG.pcb126", "LOG.pcb138", "LOG.pcb153", "LOG.pcb180"))
lm8 <- lm(LOG.teq ~ (LOG.pcb28 + LOG.pcb52 + LOG.pcb118 + LOG.pcb126 + LOG.pcb138 + LOG.pcb153 + LOG.pcb180), data=sdl)
summary(lm8)
anova(lm8)
