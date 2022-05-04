

# BankSimul



The aim of this school project was to make a simulated ATM where the user can withdraw money, view transactions, donate to a charity and check the balance. The additional objective was to learn skills required to develop such applications. You need a USB serial port RFID reader to use this application properly.


<img src="documents/mainmenu.JPG">



## Project Members


Database, REST API, bankautomat: https://github.com/tpoldsam <br>
Database, REST API, DLLRestApi: https://github.com/valttir <br>
Database, REST API, DLLPinUI: https://github.com/robinpylvas <br>
Database, REST API, DLLSerialPort: https://github.com/EmilAhve



## Installation


### npm

 
Run command ```npm install``` in the api folder. Then the program starts with the command ```npm start```.

 
 
### Database

 
Import "banksimul.sql" and run commands. 

```mysql
CREATE USER 'testman'@'localhost' IDENTIFIED WITH mysql_native_password BY 'test_pass';

GRANT ALL ON banksimul.* to 'testman'@'localhost';
```



### .env


Create .env-file in api directory and add following line to .env:
```javascript
SQL_SERVER = 'mysql://testman:test_pass@localhost:3306/banksimul'
```

Add a variable ```MY_TOKEN```.

Run command ```node create_token.js``` in the api directory and copy token to the ```MY_TOKEN``` variable.



### RFIDs


06000DE540

0B0032AD79



## Database ER-diagram

<img src="documents/er-diagram-database.png">
