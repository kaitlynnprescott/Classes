
#  Create the following x and y vectors:
#  x= 1,2,3
#  y= 11,12,13,14,15,16

 
x<-c(1,2,3)
y<-c(11,12,13,14,15,16)

#2.2   Calculate and display z=x+y.
#2.3   Explain the results.




z<-x+y
z


#2.4   Create a vector of your last name.
#2.5   Create a vector of your first name.
#2.6   Create a vector of your student ID.


last_name<-"Dehand"
first_name<-"Khasha"
id<- 12345;

#2.7   What are the length and data type of the "last name" vector? Why?
 
length(last_name)
mode(last_name)

#2.8   Combine your first name, last name and student id into a single vector ("myinfo").
#2.9   Display "myinfo" in the Console.
#2.10 What are the length and data type of "myinfo"?




#combine your first name, last name and student id into a single vector "myinfo"
#display "myinfo" in Console
#what are the length and data type of "myinfo"?
myinfo<- c(last_name, first_name, id)
myinfo
length(myinfo)
mode(myinfo)

#2.11 Remove the "first_name" object.
#2.12 Display "myinfo" in the Console again.

rm("first_name")
myinfo

#2.13 Create a dataframe "roster"  using the following table:
#  First     	  Last         ID
#  fname1   lname1   1111
#  fname2   lname2   2222

#2.14 View the "roster".




roster<- data.frame(First=c("fname1,fname2"),Last=c("lname1","lname2"),ID=c(1111,2222))

View(roster)

#2.15 Export the data frame "roster" to a csv file.
?write.csv()

write.csv( roster  ,file="c://junk//roster.csv",row.names=FALSE )



#2.17 Remove all the objects in your session.

rm(list=ls())
