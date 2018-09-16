#################################################
#  Company    : Stevens 
#  Project    : R Bootcamp 
#  Purpose    : subset
#  First Name  : Khasha
#  Last Name  : Dehnad
#  Id			    : 12345
#  Date       :
#  Comments   :
rm(list=ls())

#################################################
##   Step:
##    [[]]
##     []
##
##
##
##
##
##
##
##
##
##
######################

avector<-c("A","B","C","D")
second<-avector[2]
names(avector)<-c("first","second","third","fourth" )
avector
avector[2]<-"E"
avector


my.lst <- list(34453, c("Khasha", "Dehand"), c(14.3,12,15,19))
my.lst[2:3]
is.list(my.lst[2:3])

element2<-my.lst[[2]] 
typeof(element2)
is.list(element2)
is.vector(element2)
last_name<-my.lst[[2]][2] 


data(iris)
View(iris)

iris[,3]

subset1<-iris[c(2,1,5,8),c(2,3,4)]


subset1<-iris[c(1,2,5,8), ]
subset3<-iris[-c(1,2,5,8), ]
subset4<-iris[c(T,F),]

subset2<-iris[c(T,F),c(2,3,4)]


dsn <- read.csv("http://www.math.smith.edu/sasr/datasets/help.csv")
View(dsn)

table(dsn$substance,dsn$racegrp)
ftable(Gender=dsn$female,Substance=dsn$substance,race=dsn$racegrp)

substance 
dsn$substance
attach(dsn)
substance
substance<-c("x1","x2")
rm("substance")
detach(dsn)
substance

mydata.frame<-
  data.frame(cbind(mypcs1=dsn$pcs1,mymsc1=dsn$mcs1,myracegrp=as.character(dsn$racegrp)))
is.data.frame(mydata.frame) 

pcs1<-dsn[is.na(dsn$pcs1)==FALSE,"pcs1"]
mcs1<-dsn[is.na(dsn$pcs1)==FALSE,"mcs1"]
pcs1_mcs1<-cbind(pcs1,mcs1)
stack_pcs1_mcs1<-rbind(pcs1,mcs1)
typeof(pcs1_mcs1)
is.data.frame(pcs1_mcs1)
is.matrix(pcs1_mcs1)
pcs1_mcs2<-as.data.frame(cbind(pcs1,mcs1)) 


indx<-seq(from=1, to=nrow(iris), by=5)
test<-iris[indx,]
training<-iris[-indx,]


