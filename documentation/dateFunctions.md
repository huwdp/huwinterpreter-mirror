# Date functions
## Month
month(timestamp)
Month funcution will return a month number based on a Unix timestamp.
### Example
```
month(1485199747)
```

## MonthName
monthName(integer)
MonthName function returns the month name based on a number from 1 and 12.  MonthName function requires 1 argument.
### Example
```
monthName(month(1485199747))
```

## WeekDay
weekday(timestamp)
Weekday function returns the weekday number based on a Unix timestamp.  WeekDay function requires 1 argument.
### Example
```
weekday(1485199747)
```

## WeekDayName
weekDayName(timestamp)
WeekDayName function returns the weekday name (e.g. Monday) based off Unix timestamp. WeekDayName function requires 1 argument. Monday is the first day of week in the implementation.
### Example
```
weekdayName(1485199747)
```

## Year
year(timestamp)
Year function returns the the year based on a Unix timestamp given through an argument. Year requires 1 argument.
### Example
```
year(1440544844)
```

## Now
now()
Now function gives the current time and date based on 32bit Unix timestamp. Now requires 0 argument.
### Example
```
now()
```

## DateFormat(variable)
dateFormat(timestamp, format)
DateFormat function returns text based on time and formatting passed to the function. The date format is based on strftime within CPP. DateFormat function requires 2 argument.
Example
```
dateFormat(1485199747, "%A")
```
