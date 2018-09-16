'''
Created on Apr 16, 2015

@author:   Katie Prescott

Pledge:    I pledge my honor that I have abided by the Stevens honor system.

CS115 - Hw 11 - Date class
'''
DAYS_IN_MONTH = (0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)

class Date:
    '''A user-defined data structure that stores and manipulates dates.'''

    # The constructor is always named __init__.
    def __init__(self, month, day, year):
        '''The constructor for objects of type Date.'''
        self.month = month
        self.day = day
        self.year = year

    # The 'printing' function is always named __str__.
    def __str__(self):
        '''This method returns a string representation for the
           object of type Date that calls it (named self).

             ** Note that this _can_ be called explicitly, but
                it more often is used implicitly via the print
                statement or simply by expressing self's value.'''
        return '%02d/%02d/%04d' % (self.month, self.day, self.year)

    # Here is an example of a 'method' of the Date class.
    def isLeapYear(self):
        ''' Returns True if the calling object is in a leap year; False
            otherwise.'''
        if self.year % 400 == 0:
            return True
        if self.year % 100 == 0:
            return False
        if self.year % 4 == 0:
            return True
        return False

    def copy(self):
         ''' Returns a new object with the same month, day, year
             as the calling object (self).'''
         dnew = Date(self.month, self.day, self.year)
         return dnew

    def equals(self, d2):
        ''' Decides if self and d2 represent the same calendar date,
            whether or not they are the in the same place in memory.'''
        return self.year == d2.year and self.month == d2.month and \
               self.day == d2.day

    def tomorrow(self):
        ''' Changes the calling object so that it represents one calendar day
            AFTER the date it originally represented. self.day will definitely
            change, self.month and self.year have the potential to change. '''
        DIM =  (0,31,28,31,30,31,30,31,31,30,31,30,31)
        if self.day == 31 and self.month == 12:
            self.month = 1
            self.day = 1
            self.year += 1
        elif self.day >= DIM[self.month]:
            if self.day == 28 and self.month == 2:
                if self.isLeapYear() == True:
                    self.day = 29
                else:
                    self.day = 1
                    self.month = 3
            else:
                self.month += 1
                self.day = 1
        else:
            self.day += 1

    def yesterday(self):
        ''' Changes the calling object so that it represents one calendar day
            BEFORE the date it originally represented. self.day will definitely
            change, self.month and self.year have the potential to change. '''
        DIM =  (0,31,28,31,30,31,30,31,31,30,31,30,31)
        if self.day == 1 and self.month == 1:
            self.month = 12
            self.day = 31
            self.year = self.year - 1
        elif self.day == 1 and self.month == 3:
            if self.isLeapYear() == True:
                self.month = 2
                self.day = 29
            else: 
                self.day = 28
                self.month = 2
        elif self.day == 1:
            self.month = self.month - 1
            self.day = DIM[self.month]
        else:
            self.day = self.day - 1


    def addNDays(self, N):
        ''' This method only needs to handle nonnegative integer inputs N.
            Like the tomorrow method, this method should not return anything.
            Rather, it should change the calling object so that it represents
            N calendar days after the date it originally represented. '''
        print self
        if N == 0:
            return
        else:
            for i in range(N):
                self.tomorrow()
                print self
    
    def subNDays(self, N):
        ''' This method only needs to handle nonnegative integer inputs N.
            Like the addNDays method, this method should not return anything.
            Rather, it should change the calling object so that it represents
            N calendar days before the date it originally represented. You might
            consider using yesterday and a for loop to implement this! '''
        print self
        if N == 0:
            return
        else:
            for i in range(N):
                self.yesterday()
                print self


    def isBefore(self, d2):
        ''' Return True if the calling object is a calendar date BEFORE the
            input named d2 (which will always be an object of type Date). If
            self and d2 represent the same day, this method should return
            False. Similarly, if self is after d2, this should return False. '''
        if self.year < d2.year:
            return True
        elif self.month < d2.month and self.year == d2.year:
            return True
        elif self.day < d2.day and self.month == d2.month and self.year == d2.year:
            return True
        return False

    def isAfter(self, d2):
        ''' Return True if the calling object is a calendar date AFTER the
            input named d2 (which will always be an object of type Date). If
            self and d2 represent the same day, this method should return
            False. Similarly, if self is before d2, this should return False.'''
        if self.year > d2.year:
            return True
        elif self.month > d2.month and self.year == d2.year:
            return True
        elif self.day > d2.day and self.month == d2.month and self.year == d2.year:
            return True
        return False
            
    def diff(self, d2):
        ''' Return an integer representing the number of days between self
            and d2. You can think of it as returning the integer representing
            self - d2. '''
        dnew = self.copy()
        days = 0
        if self.equals(d2):
            return 0
        if self.isAfter(d2):
            while not (dnew.equals(d2)):
                days += 1
                dnew.yesterday()
            return days
        if self.isBefore(d2):
            while not (dnew.equals(d2)):
                days -= 1
                dnew.tomorrow()
            return days

    def dow(self):
        ''' Return a string that indicates the day of the week of the object
            (of type Date) that calls it. That is, this method returns one of
            the following strings: 'Monday', 'Tuesday', 'Wednesday', 'Thursday',
            'Friday', 'Saturday', 'Sunday'. '''
        x = Date(11, 9, 2011).diff(self)
        if x % 7 == 0:
            return 'Wednesday'
        elif x % 7 == 1:
            return 'Tuesday'
        elif x % 7 == 2:
            return 'Monday'
        elif x % 7 == 3:
            return 'Sunday'
        elif x % 7 == 4:
            return 'Saturday'
        elif x % 7 == 5:
            return 'Friday'
        elif x % 7 == 6:
            return 'Thursday'
            

        
