# CTS Data Parser

Consolidated Tape System (CTS) market data streams are produced and distributed worldwide. This data feed consists of reports of trades in equity markets in the US. All exchanges are obligated to provide their trade (last sale) data to CTS where it is timestamped and published on their data feed. 

Data arrives as an input stream of bytes. Example:

>EBBO BR 000347817D'IHb13'IH`,*      2|RH0P3QFRSX          NP 0     000@   0  F000013510000000000200DD 0
>EBBO B" 000347818D'IHc&K'IHaUz'IHb|+"wqA46LLHRSX          TP 0     000@   0  B000000001351000000100DD 0
>EBBO BW 000347819Y'IHncC'IHn^"      %=K0008VyRSX           P 0     000@   0  B000000001352000000999DD 0
>EBBO BW 000347820Y'IHnco'IHn^"      %=L0008VzRSX           P 0     000@   0  B000000001352000000500DD 0
>EBBO BW 000347821Y'IHnd#'IHn^"      %=M0008W0RSX           P 0     000   I0  B000000001352000000047AA 0

The assignment was to deserialize the data and parse a data set contained in equity_trades_small.txt file and output them in a comma-delimited file. 

For example, the above code will be parsed and the output is:

>15:58:59.33534,57539015000,0,125877446207540168,E,B,B,000347817,D,RSX,13.51,200,@,N
>15:58:59.41538,57539028000,57539040651,19403742540922945,E,B,B,000347818,D,RSX,13.51,100,@,T
>15:58:59.146600,57539146092,0,35227933796521694,E,B,B,000347819,Y,RSX,13.52,999,@, 
>15:58:59.146644,57539146092,0,35228668888412320,E,B,B,000347820,Y,RSX,13.52,500,@, 
>15:58:59.146663,57539146092,0,35229403980302966,E,B,B,000347821,Y,RSX,13.52,47,I, 
>15:58:59.153983,57539147000,57539153084,19588985697361110,E,B,B,000347822,D,RSX,13.52,654,@,T

The output fields are a subset of data present in the messages. They are:
-CTS Timestamp formatted as hh:mm:ss.nnnn
-Timestamp1 as microseconds since midnight
-Timestamp2 as microseconds sincemighight
-Transaction ID B
-Message Category (1 character)
-Message Type (1 character)
-Message Network (1 character)
-Message Sequence Number
-Participant ID
-Security Symbol
-Trade Price
-Trade Volume
-Sale Condition
-TRF identifier

The finished csv file is equity_trades_small_ctsparser.txt file.
