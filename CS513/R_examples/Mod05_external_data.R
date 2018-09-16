############################################## ###
#  Company    : Stevens 
#  Project    : R Bootcamp 
#  Purpose    : external data
#  First Name  : Khasha
#  Last Name  : Dehnad
#  Id			    : 12345
#  Date       :
#  Comments   :

rm(list=ls())
############################################## ###
##   Step:
## 
##       read.csv
##       file
##       close
##       write.csv
##       setdiff
##       getwd
##
##
##
##
##
################### ###

##       read.csv   ####
?read.csv()
 
Titanic<-
    read.csv("C://AIMS/Stevens_/R- Bootcamp/raw_data/Titanic_rows.csv")

View(Titanic)

dsn<-
  read.csv("C://AIMS/Stevens_/R- Bootcamp/raw_data/Titanic_rows.csv")

con<-file("C://AIMS/Stevens_/R- Bootcamp/raw_data/lung.csv",'r')
lung <- read.csv(con)
close(con)
View(lung)

con<-file("C://AIMS/Stevens_/R- Bootcamp/raw_data/lung.csv",'r')
 
lung <- read.csv(con, 
                      header = TRUE,
                  colClasses=c("ID"="character","AREA"="factor",
                               "Gender_father"="NULL"))
 close(con)
 View(lung)

# read csv file into R
 dsn <- read.csv("https://sit.instructure.com/courses/13110/modules/Titanic_rows.csv" 
                 ) 
 
dsn <- read.csv("http://www.math.smith.edu/sasr/datasets/dsn.csv",
                colClasses=c("id"="character"))
View(dsn)
View(dsn)

 
##       write.csv   ####
?write.csv()
write.csv(dsn,"C://AIMS/Stevens_/R- Bootcamp/raw_data/dsn.csv")
write.csv(dsn,"C://AIMS/garbage/dsn.csv")

a<-c("a1","a2","a3","a4")
ax<-c("a1","a2")
setdiff(a,ax)


?setdiff()
keep<-c("dsn","Titanic","keep")
setdiff(ls(),keep)
rm(list=(setdiff(ls(),keep)))

getwd()
setwd("C:/AIMS/Stevens_/R- Bootcamp/wd")
setwd("C:/Users/Khasha/Documents")
rm(list=ls())    
 