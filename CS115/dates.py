#
# dates.py
#
# name:
#
import copy
class Date:
    """ a user-defined data structure that
        stores and manipulates dates
    """


    DIM = [0,31,28,31,30,31,30,31,31,30,31,30,31]
    DOW = ['Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday']
    
    # the constructor is always named __init__ !
    def __init__(self, month, day, year):
        """ the constructor for objects of type Date """
        self.month = month
        self.day = day
        self.year = year


    # the "printing" function is always named __repr__ !
    def __repr__(self):
        """ This method returns a string representation for the
            object of type Date that calls it (named self).

             ** Note that this _can_ be called explicitly, but
                it more often is used implicitly via the print
                statement or simply by expressing self's value.
        """
        s =  "%02d/%02d/%04d" % (self.month, self.day, self.year)
        return s


    # here is an example of a "method" of the Date class:
    def isLeapYear(self):
        """ Returns True if the calling object is
            in a leap year; False otherwise. """
        if self.year % 400 == 0: return True
        elif self.year % 100 == 0: return False
        elif self.year % 4 == 0: return True
        return False



    def tomorrow(self):
        """Sets the date to the next day"""
        if self.isLeapYear():
            Date.DIM[2] = 29
        else:
            Date.DIM[2] = 28

        if self.day < Date.DIM[self.month]:
            self.day = self.day+1
            return
        elif self.month == 12:
            self.year = self.year + 1
            self.month = 1
            self.day = 1
            return
        else:                          
            self.month = self.month + 1
            self.day =1 

    def yesterday(self):
        """Sets d for the previous day"""
        if self.isLeapYear():
            Date.DIM[2] = 29
        else:
            Date.DIM[2] = 28
        if self.month == 1 and self.day == 1:
            self.year = self.year - 1
            self.month = 12
            self.day = 31
            return
        elif self.day == 1:
            self.day = Date.DIM[self.month-1]
            self.month=self.month-1
            return
        else:                          
            self.day =self.day-1


    def addNDays(self,N):
        """Adds the amount of days "N" to d"""
        if self.isLeapYear():
            Date.DIM[2] = 29
        else:
            Date.DIM[2] = 28
        print self
        for i in range(N):
            self.tomorrow()
            print self

    def subNDays(self, N):
        """Subtracts the amount of days "N" from d"""
        if self.isLeapYear():
            Date.DIM[2] = 29
        else:
            Date.DIM[2] = 28
        print self
        for i in range(N):
            self.yesterday()
            print self
            
    def isBefore(self, d2):
        """Returns Boolean value if d is before the date d2"""
        if self.year>d2.year:
            return False
        elif self.year<d2.year:
            return True
        elif self.month>d2.month:
            return False
        elif self.month<d2.month:
            return True
        elif self.day>d2.day:
            return False
        elif self.day<d2.day:
            return True
        else:
            return False
    def isAfter(self, d2):
        """Returns Boolean value if d is after the date d2"""
        if self.year<d2.year:
            return False
        elif self.year>d2.year:
            return True
        elif self.month<d2.month:
            return False
        elif self.month>d2.month:
            return True
        elif self.day<d2.day:
            return False
        elif self.day>d2.day:
            return True
        else:
            return False
    def diff(self,d2):
        """Returns integer representing the number of days between self and d2"""
        i=0
        d1=copy.copy(self)
        d2=copy.copy(d2)
        if d1.isAfter(d2):
            while d1.isAfter(d2):
                if d1.isLeapYear():
                    Date.DIM[2] = 29
                else:
                    Date.DIM[2] = 28
                d1.yesterday()
                i=i+1
        else:
            while d1.isBefore(d2):
                if d1.isLeapYear():
                    Date.DIM[2] = 29
                else:
                    Date.DIM[2] = 28
                d1.tomorrow()
                i=i-1
        return i
            
                
    def dow(self):
        """Returns the day of the week of self"""
        y=Date(1,1,2014).diff(self)
        if y%7==0:
            return 'Wednesday'
        elif y%7==1:
            return 'Tuesday'
        elif y%7==2:
            return 'Monday'
        elif y%7==3:
            return 'Sunday'
        elif y%7==4:
            return 'Saturday'
        elif y%7==5:
            return 'Friday'
        elif y%7==6:
            return 'Thursday'
    def dow2(self,refdate):
        """Takes in a reference date and updates the day of the week to it"""
        y=refdate.diff(self)
        if y%7==0:
            return 'Wednesday'
        elif y%7==1:
            return 'Tuesday'
        elif y%7==2:
            return 'Monday'
        elif y%7==3:
            return 'Sunday'
        elif y%7==4:
            return 'Saturday'
        elif y%7==5:
            return 'Friday'
        elif y%7==6:
            return 'Thursday'


def nycounter():
    """Takes New Years Day and returns the total amount of days on which
    New Years lands on from 2011 to 2112"""
    
    dowd = {}              # dowd == 'day of week dictionary'
    dowd["Sunday"] = 0     # a 0 entry for Sunday
    dowd["Monday"] = 0     # and so on...
    dowd["Tuesday"] = 0
    dowd["Wednesday"] = 0
    dowd["Thursday"] = 0
    dowd["Friday"] = 0
    dowd["Saturday"] = 0

    # live for another 100 years...
    for year in range(2011, 2112):
        d = Date(1, 1, year)   # get ny
        print 'Current date is', d
        s = d.dow()        # get day of week
        dowd[s] += 1       # count it

    print 'totals are', dowd

    # we could return dowd here
    # but we don't need to right now
    # return dowd
def daycounter(d):
    """Takes date d and returns the amount of day that the date has fallen on"""
    dowd = {}              # dowd == 'day of week dictionary'
    dowd["Sunday"] = 0     # a 0 entry for Sunday
    dowd["Monday"] = 0     # and so on...
    dowd["Tuesday"] = 0
    dowd["Wednesday"] = 0
    dowd["Thursday"] = 0
    dowd["Friday"] = 0
    dowd["Saturday"] = 0

    for year in range(d.year,d.year+100):
        d.year=year
        print 'Current date is',d
        s=d.dow()
        dowd[s] +=1
    print 'Totals are', dowd

def thirteenthCounter(d):
    """Finds the amount of days that the 13th of each month lands on from the
    year that d starts on"""
    refdate=Date(1,1,2014)
    dowd = {}              # dowd == 'day of week dictionary'
    dowd["Sunday"] = 0     # a 0 entry for Sunday
    dowd["Monday"] = 0     
    dowd["Tuesday"] = 0
    dowd["Wednesday"] = 0
    dowd["Thursday"] = 0
    dowd["Friday"] = 0
    dowd["Saturday"] = 0

    for year in range(d.year,d.year+400):
        for month in range(1,13):
            d.month=month
            d=Date(d.month,13,d.year)
            s=d.dow2(refdate)
            if s=='Wednesday':
                refdate=copy.copy(d)
            dowd[s]+=1
        d.year=d.year+1
    print dowd
        
        
    
