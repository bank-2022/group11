

# group11 : BankSimul



### Installation

 
Run command "npm install" in the api folder. Then the program starts with the command "npm start".

 
 
### Database

 
Import "banksimul.sql" and run commands. 

```mysql
CREATE USER 'testman'@'localhost' IDENTIFIED WITH mysql_native_password BY 'test_pass'; <br>

GRANT ALL ON banksimul.* to 'testman'@'localhost';
```


### .env


Luo api kansioon tiedosto .env ja kirjoita sinne muuttuja nimeltään MY_TOKEN.

Aja komentoriviltä komento node create_token.js ja kopsaa "token" muuttujaan MY_TOKEN

  

## ER-kaavio

 

Tietokannan ER-kaavio näyttää tältä <img src="documents/er-diagram-database.png">



## RFID tunnukset


06000DE540

0B0032AD79
