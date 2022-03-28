-- MySQL dump 10.13  Distrib 8.0.27, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: banksimul
-- ------------------------------------------------------
-- Server version	8.0.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `idaccount` int NOT NULL AUTO_INCREMENT,
  `accountnumber` varchar(18) NOT NULL,
  `balance` bigint NOT NULL,
  PRIMARY KEY (`idaccount`),
  UNIQUE KEY `account` (`accountnumber`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL AUTO_INCREMENT,
  `customer_idcustomer` int NOT NULL,
  `account_idaccount` int NOT NULL,
  `cardnumber` varchar(30) NOT NULL,
  `pin` varchar(120) NOT NULL,
  `type` varchar(6) NOT NULL,
  `locked` varchar(3) NOT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `card` (`cardnumber`),
  KEY `fk_card_customer1_idx` (`customer_idcustomer`),
  KEY `fk_card_account1_idx` (`account_idaccount`),
  CONSTRAINT `fk_card_account1` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`),
  CONSTRAINT `fk_card_customer1` FOREIGN KEY (`customer_idcustomer`) REFERENCES `customer` (`idcustomer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `charity`
--

DROP TABLE IF EXISTS `charity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `charity` (
  `idcharity` int NOT NULL AUTO_INCREMENT,
  `accountnumber` varchar(18) DEFAULT NULL,
  `balance` bigint DEFAULT NULL,
  PRIMARY KEY (`idcharity`),
  UNIQUE KEY `charity` (`accountnumber`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `charity`
--

LOCK TABLES `charity` WRITE;
/*!40000 ALTER TABLE `charity` DISABLE KEYS */;
/*!40000 ALTER TABLE `charity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `idcustomer` int NOT NULL AUTO_INCREMENT,
  `name` varchar(80) NOT NULL,
  `address` varchar(80) NOT NULL,
  `pnumber` varchar(13) NOT NULL,
  PRIMARY KEY (`idcustomer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer_has_account`
--

DROP TABLE IF EXISTS `customer_has_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer_has_account` (
  `customer_idcustomer` int NOT NULL,
  `account_idaccount` int NOT NULL,
  PRIMARY KEY (`customer_idcustomer`),
  KEY `fk_customer_has_account_account1_idx` (`account_idaccount`),
  KEY `fk_customer_has_account_customer_idx` (`customer_idcustomer`),
  CONSTRAINT `fk_customer_has_account_account1` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`),
  CONSTRAINT `fk_customer_has_account_customer` FOREIGN KEY (`customer_idcustomer`) REFERENCES `customer` (`idcustomer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer_has_account`
--

LOCK TABLES `customer_has_account` WRITE;
/*!40000 ALTER TABLE `customer_has_account` DISABLE KEYS */;
/*!40000 ALTER TABLE `customer_has_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transactions`
--

DROP TABLE IF EXISTS `transactions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transactions` (
  `idtransactions` int NOT NULL AUTO_INCREMENT,
  `account_idaccount` int NOT NULL,
  `accountnumber` varchar(18) NOT NULL,
  `cardnumber` varchar(30) DEFAULT NULL,
  `datetime` varchar(50) NOT NULL,
  `event` varchar(10) NOT NULL,
  `sum` int NOT NULL,
  PRIMARY KEY (`idtransactions`),
  KEY `account_idaccount_idx` (`account_idaccount`),
  CONSTRAINT `account_idaccount` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactions`
--

LOCK TABLES `transactions` WRITE;
/*!40000 ALTER TABLE `transactions` DISABLE KEYS */;
/*!40000 ALTER TABLE `transactions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'banksimul'
--
/*!50003 DROP PROCEDURE IF EXISTS `credit_charity` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `credit_charity`(IN id INT, IN cid INT, IN amount BIGINT, IN cnumber VARCHAR(30))
BEGIN
  DECLARE anumber VARCHAR(18);
  DECLARE test1, test2 INT DEFAULT 0;
  SELECT accountnumber INTO anumber FROM account WHERE idaccount = id;
  START TRANSACTION;
  UPDATE account SET balance = balance - amount WHERE idaccount = id;
  SET test1 = ROW_COUNT();
  UPDATE charity SET balance = balance + amount WHERE idcharity = cid;
  SET test2 = ROW_COUNT();
    IF (test1 > 0 AND test2 > 0) THEN
      COMMIT;
      INSERT INTO transactions(account_idaccount, accountnumber, cardnumber, datetime, event, sum) VALUES(id, anumber, cnumber, NOW(), 'donation', amount);
    ELSE
      ROLLBACK;
  END IF;
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `credit_withdraw` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `credit_withdraw`(IN id INT, IN amount BIGINT, IN cnumber VARCHAR(30))
BEGIN
  DECLARE anumber VARCHAR(18);
  SELECT accountnumber INTO anumber FROM account WHERE idaccount = id;
  UPDATE account SET balance = balance - amount WHERE idaccount = id;
  INSERT INTO transactions(account_idaccount, accountnumber, cardnumber, datetime, event, sum) VALUES(id, anumber, cnumber, NOW(), 'withdrawal', amount);
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `debit_charity` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_charity`(IN id INT, IN cid INT, IN amount BIGINT, IN cnumber VARCHAR(30))
BEGIN
  DECLARE test1, test2 INT DEFAULT 0;
  DECLARE anumber VARCHAR(18);
  SELECT accountnumber INTO anumber FROM account WHERE idaccount = id;
  START TRANSACTION;
  UPDATE account SET balance = balance - amount WHERE idaccount = id AND balance >= amount;
  SET test1 = ROW_COUNT();
  UPDATE charity SET balance = balance + amount WHERE idcharity = cid;
  SET test2 = ROW_COUNT();
    IF (test1 > 0 AND test2 > 0) THEN   
      COMMIT;    
	  INSERT INTO transactions(account_idaccount, accountnumber, cardnumber, datetime, event, sum) VALUES(id, anumber, cnumber, NOW(), 'donation', amount);
    ELSE
      ROLLBACK;
  END IF;
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `debit_withdraw` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_withdraw`(IN id INT, IN amount BIGINT, IN cnumber VARCHAR(30))
BEGIN
  DECLARE test INT DEFAULT 0;
  DECLARE anumber VARCHAR(18);
  SELECT accountnumber INTO anumber FROM account WHERE idaccount = id;
  START TRANSACTION;
  UPDATE account SET balance = balance - amount WHERE idaccount = id AND balance >= amount;
  SET test = ROW_COUNT();
    IF (test > 0) THEN   
      COMMIT;    
	  INSERT INTO transactions(account_idaccount, accountnumber, cardnumber, datetime, event, sum) VALUES(id, anumber, cnumber, NOW(), 'withdrawal', amount);
    ELSE
      ROLLBACK;
  END IF;
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-03-28 14:11:27
