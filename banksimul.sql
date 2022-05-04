CREATE DATABASE  IF NOT EXISTS `banksimul` /*!40100 DEFAULT CHARACTER SET utf8 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `banksimul`;
-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: localhost    Database: banksimul
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
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,'FI01010101',10000),(2,'FI6654198',10000),(3,'FI6654207',10000),(9,'FI5566778899',483000),(10,'FI4278907654123400',-44800),(11,'FI5061110531139841',469000),(12,'FI3849998319917629',418100);
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
  `pin` varchar(255) DEFAULT NULL,
  `type` varchar(6) NOT NULL,
  `locked` varchar(3) NOT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `card` (`cardnumber`),
  KEY `fk_card_customer1_idx` (`customer_idcustomer`),
  KEY `fk_card_account1_idx` (`account_idaccount`),
  CONSTRAINT `fk_card_account1` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`),
  CONSTRAINT `fk_card_customer1` FOREIGN KEY (`customer_idcustomer`) REFERENCES `customer` (`idcustomer`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,1,1,'0100100','1414','debit','no'),(2,2,2,'999665','1234','debit','no'),(3,3,3,'999667','0000','debit','no'),(4,4,9,'0987666','$2a$10$U6m2mCn/OBVv8AiVv0PK3Od/.06tRCSB2OJQvMYh2EKAQcNy./j4.','debit','no'),(5,2,9,'123456','$2a$10$2pLs6qoD60oq3NQMKX0eqOkFzNde47HcEgShO5Dcy1kyjfCsLHOLu','debit','no'),(10,5,10,'66778899','$2a$10$NW/N7vEhTEnEDBVdVfBtdez/EoKyvJOiMGFEP29Q1tWsGneQJwpRW','credit','no'),(11,6,11,'06000DE540','$2a$10$4AG5FcpTjy1oN/j6i7.Hset0/0oIvug4h66L0KVkPUqhoz9yWXlRu','debit','no'),(12,7,12,'0B0032AD79','$2a$10$TFILqKUVKI2KZeaX6Ro3w.9bHPyP6EB3XfB2J9tUgqeMfBhXWTvnC','credit','no');
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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `charity`
--

LOCK TABLES `charity` WRITE;
/*!40000 ALTER TABLE `charity` DISABLE KEYS */;
INSERT INTO `charity` VALUES (3,'FI4265431234000012',59700);
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
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Leevi','Ouluntie 68','0458345783'),(2,'Leena','Ouluntie 69','04509823665'),(3,'Lasse','Ouluntie 69','04509823667'),(4,'Olavi','Koulukuja 42','0456784334'),(5,'Ruusu Retiisi','Kasvikuja 13','04588776655'),(6,'Matti Meikäläinen','Ouluntie 13','0454527887'),(7,'Maija Mäkelä','Ojakatu 42','0448642309');
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
  `sum` bigint DEFAULT NULL,
  PRIMARY KEY (`idtransactions`),
  KEY `account_idaccount_idx` (`account_idaccount`),
  CONSTRAINT `account_idaccount` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=188 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactions`
--

LOCK TABLES `transactions` WRITE;
/*!40000 ALTER TABLE `transactions` DISABLE KEYS */;
INSERT INTO `transactions` VALUES (66,9,'FI5566778899','0987666','2022-04-11 10:15:01','withdrawal',300),(67,9,'FI5566778899','0987666','2022-04-11 10:20:16','withdrawal',2000),(68,9,'FI5566778899','0987666','2022-04-20 17:00:16','withdrawal',2000),(69,9,'FI5566778899','0987666','2022-04-21 19:28:03','withdrawal',4000),(70,9,'FI5566778899','0987666','2022-04-21 20:50:24','withdrawal',1000),(71,9,'FI5566778899','0987666','2022-04-21 21:05:42','withdrawal',1000),(72,9,'FI5566778899','0987666','2022-04-21 22:03:13','withdrawal',1000),(73,9,'FI5566778899','0987666','2022-04-21 23:02:50','withdrawal',1000),(74,9,'FI5566778899','0987666','2022-04-21 23:05:09','withdrawal',1000),(75,9,'FI5566778899','0987666','2022-04-21 23:07:36','withdrawal',2000),(76,9,'FI5566778899','0987666','2022-04-21 23:09:49','withdrawal',1000),(77,9,'FI5566778899','0987666','2022-04-21 23:10:05','withdrawal',100),(78,9,'FI5566778899','0987666','2022-04-21 23:19:06','withdrawal',100),(79,9,'FI5566778899','0987666','2022-04-21 23:21:18','withdrawal',100),(80,9,'FI5566778899','0987666','2022-04-21 23:21:32','withdrawal',1000),(81,9,'FI5566778899','0987666','2022-04-21 23:25:13','withdrawal',1000),(82,9,'FI5566778899','0987666','2022-04-21 23:27:53','withdrawal',1000),(83,9,'FI5566778899','0987666','2022-04-21 23:29:57','withdrawal',1000),(84,9,'FI5566778899','0987666','2022-04-22 08:35:24','withdrawal',1000),(85,9,'FI5566778899','0987666','2022-04-22 08:35:38','withdrawal',1000),(86,9,'FI5566778899','0987666','2022-04-22 08:41:15','withdrawal',1000),(87,9,'FI5566778899','0987666','2022-04-22 09:02:23','withdrawal',1000),(88,9,'FI5566778899','0987666','2022-04-24 23:26:13','withdrawal',1000),(89,9,'FI5566778899','0987666','2022-04-25 09:28:29','withdrawal',1100),(90,9,'FI5566778899','0987666','2022-04-25 09:39:57','withdrawal',1100),(91,9,'FI5566778899','0987666','2022-04-25 09:42:46','withdrawal',1100),(92,9,'FI5566778899','0987666','2022-04-25 09:45:31','withdrawal',1100),(93,9,'FI5566778899','0987666','2022-04-25 10:55:28','withdrawal',1100),(94,9,'FI5566778899','0987666','2022-04-25 10:58:25','withdrawal',1000),(95,9,'FI5566778899','0987666','2022-04-25 11:13:38','withdrawal',1000),(96,9,'FI5566778899','0987666','2022-04-25 12:54:29','withdrawal',1000),(97,10,'FI4278907654123400','66778899','2022-04-25 13:12:38','withdrawal',1000),(98,10,'FI4278907654123400','66778899','2022-04-25 13:12:46','withdrawal',50000),(99,10,'FI4278907654123400','66778899','2022-04-25 13:12:50','withdrawal',50000),(100,10,'FI4278907654123400','66778899','2022-04-25 13:12:52','withdrawal',50000),(101,10,'FI4278907654123400','66778899','2022-04-25 13:12:53','withdrawal',50000),(102,10,'FI4278907654123400','66778899','2022-04-25 13:12:54','withdrawal',50000),(103,10,'FI4278907654123400','66778899','2022-04-25 13:12:55','withdrawal',50000),(104,10,'FI4278907654123400','66778899','2022-04-25 13:12:56','withdrawal',50000),(105,10,'FI4278907654123400','66778899','2022-04-25 13:12:56','withdrawal',50000),(106,10,'FI4278907654123400','66778899','2022-04-25 13:12:57','withdrawal',50000),(107,10,'FI4278907654123400','66778899','2022-04-25 13:12:58','withdrawal',50000),(108,10,'FI4278907654123400','66778899','2022-04-25 13:12:58','withdrawal',50000),(109,10,'FI4278907654123400','66778899','2022-04-25 13:15:03','withdrawal',50000),(110,10,'FI4278907654123400','66778899','2022-04-25 13:15:12','withdrawal',5000),(111,10,'FI4278907654123400','66778899','2022-04-25 13:18:43','donation',2000),(112,10,'FI4278907654123400','66778899','2022-04-25 13:24:45','donation',1000),(113,10,'FI4278907654123400','66778899','2022-04-25 13:24:53','withdrawal',1000),(114,10,'FI4278907654123400','66778899','2022-04-25 15:25:08','donation',1000),(115,10,'FI4278907654123400','66778899','2022-04-25 15:35:57','donation',1000),(116,9,'FI5566778899','0987666','2022-04-25 15:36:18','donation',1000),(117,10,'FI4278907654123400','66778899','2022-04-25 15:38:25','withdrawal',1000),(118,10,'FI4278907654123400','66778899','2022-04-25 15:38:31','donation',1000),(119,9,'FI5566778899','0987666','2022-04-25 15:38:48','withdrawal',1000),(120,9,'FI5566778899','0987666','2022-04-25 15:38:55','donation',1000),(121,9,'FI5566778899','0987666','2022-04-25 15:39:18','withdrawal',1000),(122,9,'FI5566778899','0987666','2022-04-25 22:24:47','donation',1000),(123,9,'FI5566778899','0987666','2022-04-25 22:25:08','withdrawal',1000),(124,10,'FI4278907654123400','66778899','2022-04-25 22:25:32','donation',1000),(125,10,'FI4278907654123400','66778899','2022-04-25 22:25:40','withdrawal',1000),(126,9,'FI5566778899','0987666','2022-04-26 13:03:45','withdrawal',1000),(127,9,'FI5566778899','0987666','2022-04-26 13:03:50','donation',1000),(128,10,'FI4278907654123400','66778899','2022-04-26 13:04:13','withdrawal',1000),(129,10,'FI4278907654123400','66778899','2022-04-26 13:04:18','donation',1000),(130,10,'FI4278907654123400','66778899','2022-04-26 20:54:38','withdrawal',1000),(131,10,'FI4278907654123400','66778899','2022-04-26 20:55:41','donation',1000),(132,10,'FI4278907654123400','66778899','2022-04-26 21:11:10','withdrawal',1000),(133,10,'FI4278907654123400','66778899','2022-04-26 21:11:19','donation',1000),(134,9,'FI5566778899','0987666','2022-04-26 21:11:30','withdrawal',1000),(135,9,'FI5566778899','0987666','2022-04-26 21:11:36','donation',1000),(136,10,'FI4278907654123400','66778899','2022-04-27 10:19:45','withdrawal',1000),(137,9,'FI5566778899','0987666','2022-04-28 09:01:20','withdrawal',1000),(138,9,'FI5566778899','0987666','2022-04-28 09:01:33','donation',1000),(139,10,'FI4278907654123400','66778899','2022-04-28 09:02:04','withdrawal',1000),(140,10,'FI4278907654123400','66778899','2022-04-28 09:02:12','donation',1000),(141,10,'FI4278907654123400','66778899','2022-04-28 13:53:55','withdrawal',1000),(142,10,'FI4278907654123400','66778899','2022-04-28 14:06:59','withdrawal',1000),(143,10,'FI4278907654123400','66778899','2022-04-28 14:28:30','withdrawal',1000),(144,9,'FI5566778899','0987666','2022-04-28 14:28:56','withdrawal',1000),(145,10,'FI4278907654123400','66778899','2022-04-28 14:36:31','withdrawal',1000),(146,10,'FI4278907654123400','66778899','2022-04-28 14:36:41','withdrawal',1000),(147,10,'FI4278907654123400','66778899','2022-04-28 14:38:12','withdrawal',1000),(148,10,'FI4278907654123400','66778899','2022-04-28 14:38:16','donation',1000),(149,10,'FI4278907654123400','66778899','2022-04-29 13:17:59','donation',1100),(150,10,'FI4278907654123400','66778899','2022-04-29 13:19:36','donation',1200),(151,10,'FI4278907654123400','66778899','2022-04-29 13:43:27','donation',1100),(152,10,'FI4278907654123400','66778899','2022-04-29 13:43:39','withdrawal',1000),(153,10,'FI4278907654123400','66778899','2022-04-29 13:52:00','donation',1300),(154,10,'FI4278907654123400','66778899','2022-04-29 13:52:08','withdrawal',1000),(155,10,'FI4278907654123400','66778899','2022-04-29 14:16:59','withdrawal',1000),(156,10,'FI4278907654123400','66778899','2022-04-29 14:17:08','donation',1100),(157,9,'FI5566778899','0987666','2022-04-29 14:17:22','donation',1000),(158,10,'FI4278907654123400','66778899','2022-04-29 14:19:49','withdrawal',1000),(159,10,'FI4278907654123400','66778899','2022-04-29 14:19:53','donation',1000),(160,10,'FI4278907654123400','66778899','2022-04-29 14:21:50','withdrawal',1000),(161,9,'FI5566778899','0987666','2022-05-02 09:24:51','withdrawal',1000),(162,9,'FI5566778899','0987666','2022-05-02 09:25:00','donation',1000),(163,9,'FI5566778899','0987666','2022-05-02 09:25:09','withdrawal',1000),(164,10,'FI4278907654123400','66778899','2022-05-02 12:03:29','withdrawal',1000),(165,12,'FI3849998319917629','0B0032AD79','2022-05-02 14:34:17','withdrawal',1000),(166,12,'FI3849998319917629','0B0032AD79','2022-05-02 14:34:23','donation',1000),(167,11,'FI5061110531139841','06000DE540','2022-05-02 14:34:40','withdrawal',1000),(168,11,'FI5061110531139841','06000DE540','2022-05-02 14:34:43','donation',1000),(169,12,'FI3849998319917629','0B0032AD79','2022-05-02 16:46:10','withdrawal',1000),(170,12,'FI3849998319917629','0B0032AD79','2022-05-02 16:46:19','donation',2000),(171,11,'FI5061110531139841','06000DE540','2022-05-03 15:51:26','withdrawal',1000),(172,11,'FI5061110531139841','06000DE540','2022-05-03 15:51:32','donation',2000),(173,12,'FI3849998319917629','0B0032AD79','2022-05-03 15:53:49','withdrawal',1000),(174,12,'FI3849998319917629','0B0032AD79','2022-05-03 15:53:55','donation',2000),(175,11,'FI5061110531139841','06000DE540','2022-05-03 16:05:48','withdrawal',4000),(176,11,'FI5061110531139841','06000DE540','2022-05-03 16:05:53','donation',2000),(177,11,'FI5061110531139841','06000DE540','2022-05-03 18:11:23','withdrawal',4000),(178,11,'FI5061110531139841','06000DE540','2022-05-03 18:11:39','donation',9000),(179,12,'FI3849998319917629','0B0032AD79','2022-05-03 18:12:36','withdrawal',10000),(180,12,'FI3849998319917629','0B0032AD79','2022-05-03 18:13:15','donation',6900),(181,11,'FI5061110531139841','06000DE540','2022-05-04 07:02:15','withdrawal',1000),(182,11,'FI5061110531139841','06000DE540','2022-05-04 07:02:45','withdrawal',5000),(183,11,'FI5061110531139841','06000DE540','2022-05-04 07:02:54','donation',1000),(184,12,'FI3849998319917629','0B0032AD79','2022-05-04 07:04:10','withdrawal',1000),(185,12,'FI3849998319917629','0B0032AD79','2022-05-04 07:04:27','donation',5000),(186,12,'FI3849998319917629','0B0032AD79','2022-05-04 07:05:21','withdrawal',50000),(187,12,'FI3849998319917629','0B0032AD79','2022-05-04 07:05:32','donation',1000);
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
CREATE DEFINER=`root`@`localhost` PROCEDURE `credit_charity`(IN cnumber VARCHAR(30), IN charitynumber VARCHAR(18), IN amount BIGINT)
BEGIN
  DECLARE test1, test2 INT DEFAULT 0;
  DECLARE anumber VARCHAR(18);
  DECLARE id INT;
  SELECT accountnumber INTO anumber FROM account INNER JOIN card ON account.idaccount = card.account_idaccount WHERE cnumber = cardnumber;
  SELECT account_idaccount INTO id FROM card WHERE cnumber = cardnumber;
  START TRANSACTION;
  UPDATE account SET balance = balance - amount WHERE accountnumber = anumber;
  SET test1 = ROW_COUNT();
  UPDATE charity SET balance = balance + amount WHERE accountnumber = charitynumber;
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
CREATE DEFINER=`root`@`localhost` PROCEDURE `credit_withdraw`(IN cnumber VARCHAR(30), IN amount BIGINT)
BEGIN
  DECLARE anumber VARCHAR(18);
  DECLARE id INT;
  SELECT accountnumber INTO anumber FROM account INNER JOIN card ON account.idaccount = card.account_idaccount WHERE cnumber = cardnumber;
  SELECT account_idaccount INTO id FROM card WHERE cnumber = cardnumber;
  UPDATE account SET balance = balance - amount WHERE accountnumber = anumber;
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
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_charity`(IN cnumber VARCHAR(30), IN charitynumber VARCHAR(18), IN amount BIGINT)
BEGIN
  DECLARE test1, test2 INT DEFAULT 0;
  DECLARE anumber VARCHAR(18);
  DECLARE id INT;
  SELECT accountnumber INTO anumber FROM account INNER JOIN card ON account.idaccount = card.account_idaccount WHERE cnumber = cardnumber;
  SELECT account_idaccount INTO id FROM card WHERE cnumber = cardnumber;
  START TRANSACTION;
  UPDATE account SET balance = balance - amount WHERE accountnumber = anumber AND balance >= amount;
  SET test1 = ROW_COUNT();
  UPDATE charity SET balance = balance + amount WHERE accountnumber = charitynumber;
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
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_withdraw`(IN cnumber VARCHAR(30), IN amount BIGINT)
BEGIN
  DECLARE test INT DEFAULT 0;
  DECLARE anumber VARCHAR(18);
  DECLARE id INT;
  SELECT accountnumber INTO anumber FROM account INNER JOIN card ON account.idaccount = card.account_idaccount WHERE cnumber = cardnumber;
  SELECT account_idaccount INTO id FROM card WHERE cnumber = cardnumber;
  START TRANSACTION;
  UPDATE account SET balance = balance - amount WHERE accountnumber = anumber AND balance >= amount;
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

-- Dump completed on 2022-05-04 15:29:31
