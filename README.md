

# group11 : BankSimul

## Asennusohje

 

aja api kansiossa komento npm install. Sitten sovellus käynnistyy komennolla npm start

 

### .env

 

Luo api kansioon tiedosto .env ja kirjoita sinne muuttuja nimeltään MY_TOKEN.

Aja komentoriviltä komento node create_token.js ja kopsaa "token" muuttujaan MY_TOKEN

 

### Tietokanta

 

Suorita tuo tiedosto "banksimul.sql" ja aja komennot <br>

CREATE USER 'testman'@'localhost' IDENTIFIED WITH mysql_native_password BY 'test_pass'; <br>

GRANT ALL ON banksimul.* to 'testman'@'localhost';

 

## ER-kaavio

 

Tietokannan ER-kaavio näyttää tältä <img src="documents/er-diagram-database.png">

 
