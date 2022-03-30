

# group_example : Peppi sovellus

 

Esimerkki on yksinkertainen versio oppilasrekisteristä (kuten Peppi).

 

## Asennusohje

 

aja api kansiossa komento npm install. Sitten sovellus käynnistyy komennolla npm start

 

### .env

 

Luo api kansioon tiedosto .env ja kirjoita sinne muuttuja nimeltään MY_TOKEN.

Aja komentoriviltä komento node create_token.js ja kopsaa "token" muuttujaan MY_TOKEN

 

### Tietokanta

 

Suorita tuo tiedosto "database_dump.sql" ja aja komennot <br>

CREATE USER 'peppiuser'@'localhost' IDENTIFIED WITH mysql_native_password BY 'peppipass'; <br>

GRANT ALL ON peppi.* to 'peppiuser'@'localhost';

 

## ER-kaavio

 

Tietokannan ER-kaavio näyttää tältä <img src="documents/er-diagram-database.png">

 
