# StockAnalysis
Read stock data from file and write all local extrema found in data. Calculate simple moving average and write local extreme of the averaged data to give a more general idea of the highs and lows of the stock. Project is a Microsoft Visual Studio C++ solution.

How to use:

Download excel file containing relevant stock data from http://www.nasdaq.com/quotes/historical-quotes.aspx

Copy data from the excel file into the "data.txt" file found in the "StockAnalysis" folder. Please copy every column of data as well as the
column names (date, low, high, etc).

Data file should look something like this:

date	close	volume	open	high	low
					
2018-01-05	0.235	104309	0.2294	0.261	0.22
2018-01-04	0.2213	257935	0.299	0.299	0.2213
2018-01-03	0.2578	275061	0.234	0.2665	0.1865
2018-01-02	0.218	465736	0.3015	0.3015	0.2052
.
.
.

The data.txt file also already contains an example.

The program will ignore the first line in the file that contains anything. This is intended to be the line containing the column names.


Data definitions:

Volume refers to the total number of stock shares traded in the given day. 

Close refers to the value of the stock when trading closed for that day while open refers to the value when trading opened.

High and low refer to the greatest and least price of the stock on that day.
