-- MySQL dump 10.11
--
-- Host: localhost    Database: ejemplomysql
-- ------------------------------------------------------
-- Server version	5.0.45

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ajustes_conci`
--

DROP TABLE IF EXISTS `ajustes_conci`;
CREATE TABLE `ajustes_conci` (
  `cuenta` varchar(40) default NULL,
  `fecha` date default NULL,
  `debe` decimal(14,2) default NULL,
  `haber` decimal(14,2) default NULL,
  `concepto` varchar(255) default NULL,
  `dif_conciliacion` varchar(40) default '',
  `conciliado` tinyint(1) default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ajustes_conci`
--

LOCK TABLES `ajustes_conci` WRITE;
/*!40000 ALTER TABLE `ajustes_conci` DISABLE KEYS */;
/*!40000 ALTER TABLE `ajustes_conci` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `amortcontable`
--

DROP TABLE IF EXISTS `amortcontable`;
CREATE TABLE `amortcontable` (
  `ejercicio` varchar(40) NOT NULL default '',
  `asiento` bigint(20) default NULL,
  PRIMARY KEY  (`ejercicio`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `amortcontable`
--

LOCK TABLES `amortcontable` WRITE;
/*!40000 ALTER TABLE `amortcontable` DISABLE KEYS */;
INSERT INTO `amortcontable` VALUES ('2008',36);
/*!40000 ALTER TABLE `amortcontable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `amortfiscalycontable`
--

DROP TABLE IF EXISTS `amortfiscalycontable`;
CREATE TABLE `amortfiscalycontable` (
  `ejercicio` varchar(40) NOT NULL default '',
  `cuenta_activo` varchar(40) NOT NULL default '',
  `codigo_activo` varchar(40) default NULL,
  `cuenta_am_acum` varchar(40) default NULL,
  `cuenta_gasto` varchar(40) default NULL,
  `dotacion_contable` decimal(14,2) default NULL,
  `dotacion_fiscal` decimal(14,2) default NULL,
  PRIMARY KEY  (`ejercicio`,`cuenta_activo`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `amortfiscalycontable`
--

LOCK TABLES `amortfiscalycontable` WRITE;
/*!40000 ALTER TABLE `amortfiscalycontable` DISABLE KEYS */;
INSERT INTO `amortfiscalycontable` VALUES ('2008','21700003','PC3','28170003','68100001','106.64','900.00');
/*!40000 ALTER TABLE `amortfiscalycontable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `amortpers`
--

DROP TABLE IF EXISTS `amortpers`;
CREATE TABLE `amortpers` (
  `cuenta` varchar(40) NOT NULL default '',
  `ejercicio` varchar(40) NOT NULL default '',
  `importe` decimal(14,2) default NULL,
  PRIMARY KEY  (`cuenta`,`ejercicio`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `amortpers`
--

LOCK TABLES `amortpers` WRITE;
/*!40000 ALTER TABLE `amortpers` DISABLE KEYS */;
/*!40000 ALTER TABLE `amortpers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `borrador`
--

DROP TABLE IF EXISTS `borrador`;
CREATE TABLE `borrador` (
  `asiento` bigint(20) default NULL,
  `usuario` varchar(80) default NULL,
  `cuenta` varchar(40) default NULL,
  `concepto` varchar(80) default NULL,
  `debe` varchar(40) default NULL,
  `haber` varchar(40) default NULL,
  `documento` varchar(40) default NULL,
  `ctabaseiva` varchar(40) default NULL,
  `baseiva` varchar(40) default NULL,
  `claveiva` varchar(40) default NULL,
  `tipoiva` varchar(40) default NULL,
  `tipore` varchar(40) default NULL,
  `cuotaiva` varchar(40) default NULL,
  `cuentafra` varchar(40) default NULL,
  `diafra` varchar(40) default NULL,
  `mesfra` varchar(40) default NULL,
  `anyofra` varchar(40) default NULL,
  `soportado` varchar(40) default NULL,
  `ci` varchar(40) default NULL,
  `prorrata` varchar(40) default '',
  `rectificativa` varchar(40) default '',
  `autofactura` varchar(40) default ''
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `borrador`
--

LOCK TABLES `borrador` WRITE;
/*!40000 ALTER TABLE `borrador` DISABLE KEYS */;
/*!40000 ALTER TABLE `borrador` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cab_as_modelo`
--

DROP TABLE IF EXISTS `cab_as_modelo`;
CREATE TABLE `cab_as_modelo` (
  `asientomodelo` varchar(255) NOT NULL default '',
  `fecha` varchar(255) default NULL,
  PRIMARY KEY  (`asientomodelo`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cab_as_modelo`
--

LOCK TABLES `cab_as_modelo` WRITE;
/*!40000 ALTER TABLE `cab_as_modelo` DISABLE KEYS */;
/*!40000 ALTER TABLE `cab_as_modelo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cabeceraestados`
--

DROP TABLE IF EXISTS `cabeceraestados`;
CREATE TABLE `cabeceraestados` (
  `titulo` varchar(255) NOT NULL default '',
  `cabecera` varchar(255) default NULL,
  `parte1` varchar(255) default NULL,
  `parte2` varchar(255) default NULL,
  `observaciones` varchar(255) default NULL,
  `formulabasepor` varchar(255) default NULL,
  `fechacalculo` date default NULL,
  `ejercicio1` varchar(255) default NULL,
  `ejercicio2` varchar(255) default NULL,
  `analitica` tinyint(1) default NULL,
  `haycolref` tinyint(1) default NULL,
  `colref` varchar(80) default NULL,
  `ci` varchar(80) default NULL,
  `desglose` tinyint(1) default NULL,
  `des_cabecera` varchar(255) default NULL,
  `des_pie` varchar(255) default NULL,
  `estadosmedios` tinyint(1) default NULL,
  `valorbasepor1` decimal(14,2) default NULL,
  `valorbasepor2` decimal(14,2) default NULL,
  `diarios` varchar(255) default NULL,
  `grafico` tinyint(1) default NULL,
  PRIMARY KEY  (`titulo`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cabeceraestados`
--

LOCK TABLES `cabeceraestados` WRITE;
/*!40000 ALTER TABLE `cabeceraestados` DISABLE KEYS */;
INSERT INTO `cabeceraestados` VALUES ('BALANCE PYMES PLAN 2007','BALANCE DE PYMES AL CIERRE DEL EJERCICIO','ACTIVO','PATRIMONIO NETO Y PASIVO','','','2008-03-31','2008','',0,1,'Nota','',NULL,NULL,NULL,0,'0.00','0.00','APERTURA SIN_ASIGNAR REGULARIZACION',NULL),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','CUENTA DE PÉRDIDAS Y GANANCIAS PYMES','','','','','2008-03-31','2008','',0,1,'Nota','',NULL,NULL,NULL,0,'0.00','0.00','APERTURA SIN_ASIGNAR',NULL),('BALANCE GRAFICO','BALANCE GRAFICO','ACTIVO','PATRIMONIO NETO Y PASIVO','','','2008-09-04','2008','',0,1,'Nota','',0,'','',0,'0.00','0.00','APERTURA SIN_ASIGNAR REGULARIZACION',1);
/*!40000 ALTER TABLE `cabeceraestados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ci`
--

DROP TABLE IF EXISTS `ci`;
CREATE TABLE `ci` (
  `codigo` varchar(40) NOT NULL default '',
  `descripcion` varchar(80) default NULL,
  `nivel` int(11) NOT NULL default '0',
  PRIMARY KEY  (`codigo`,`nivel`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ci`
--

LOCK TABLES `ci` WRITE;
/*!40000 ALTER TABLE `ci` DISABLE KEYS */;
/*!40000 ALTER TABLE `ci` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ci_amort`
--

DROP TABLE IF EXISTS `ci_amort`;
CREATE TABLE `ci_amort` (
  `cuenta` varchar(40) NOT NULL default '',
  `ci` varchar(40) NOT NULL default '',
  `asignacion` double default NULL,
  PRIMARY KEY  (`cuenta`,`ci`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ci_amort`
--

LOCK TABLES `ci_amort` WRITE;
/*!40000 ALTER TABLE `ci_amort` DISABLE KEYS */;
/*!40000 ALTER TABLE `ci_amort` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `conceptos`
--

DROP TABLE IF EXISTS `conceptos`;
CREATE TABLE `conceptos` (
  `clave` varchar(10) NOT NULL default '',
  `descripcion` varchar(80) default NULL,
  PRIMARY KEY  (`clave`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `conceptos`
--

LOCK TABLES `conceptos` WRITE;
/*!40000 ALTER TABLE `conceptos` DISABLE KEYS */;
/*!40000 ALTER TABLE `conceptos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `configuracion`
--

DROP TABLE IF EXISTS `configuracion`;
CREATE TABLE `configuracion` (
  `empresa` varchar(255) default NULL,
  `nif` varchar(255) default NULL,
  `domicilio` varchar(255) default NULL,
  `poblacion` varchar(255) default NULL,
  `cpostal` varchar(255) default NULL,
  `provincia` varchar(255) default NULL,
  `email` varchar(255) default NULL,
  `web` varchar(255) default NULL,
  `anchocuentas` int(11) default NULL,
  `cuenta_iva_soportado` varchar(255) default NULL,
  `cuenta_iva_repercutido` varchar(255) default NULL,
  `cuenta_ret_irpf` varchar(255) default NULL,
  `cuentasapagar` varchar(255) default NULL,
  `cuentasacobrar` varchar(255) default NULL,
  `clave_iva_defecto` varchar(255) default NULL,
  `clave_gastos` varchar(255) default NULL,
  `clave_ingresos` varchar(255) default NULL,
  `cuenta_pyg` varchar(255) default NULL,
  `prox_asiento` bigint(20) default NULL,
  `prox_pase` bigint(20) default NULL,
  `prox_vencimiento` bigint(20) default NULL,
  `numrel` tinyint(1) default NULL,
  `igic` tinyint(1) default NULL,
  `analitica` tinyint(1) default NULL,
  `version` varchar(40) default NULL,
  `bloqsaldosmedios` tinyint(1) default NULL,
  `id_registral` varchar(255) default NULL,
  `prorrata_iva` decimal(5,2) default '0.00',
  `prorrata_especial` tinyint(1) default '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `configuracion`
--

LOCK TABLES `configuracion` WRITE;
/*!40000 ALTER TABLE `configuracion` DISABLE KEYS */;
INSERT INTO `configuracion` VALUES ('Ejemplo 2008 mysql','','','','','','','',8,'472','477','','400,401','430,431','GN','6','7','129.0',42,151,13,0,0,0,'2.2',0,'','0.00',0);
/*!40000 ALTER TABLE `configuracion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cuenta_ext_conci`
--

DROP TABLE IF EXISTS `cuenta_ext_conci`;
CREATE TABLE `cuenta_ext_conci` (
  `numero` bigint(20) unsigned NOT NULL auto_increment,
  `cuenta` varchar(40) default NULL,
  `fecha` date default NULL,
  `debe` decimal(14,2) default NULL,
  `haber` decimal(14,2) default NULL,
  `saldo` decimal(14,2) default NULL,
  `concepto` varchar(255) default NULL,
  `dif_conciliacion` varchar(40) default '',
  `conciliado` tinyint(1) default '0',
  PRIMARY KEY  (`numero`),
  UNIQUE KEY `numero` (`numero`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `cuenta_ext_conci`
--

LOCK TABLES `cuenta_ext_conci` WRITE;
/*!40000 ALTER TABLE `cuenta_ext_conci` DISABLE KEYS */;
/*!40000 ALTER TABLE `cuenta_ext_conci` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `datossubcuenta`
--

DROP TABLE IF EXISTS `datossubcuenta`;
CREATE TABLE `datossubcuenta` (
  `cuenta` varchar(40) NOT NULL default '',
  `razon` varchar(80) default NULL,
  `nombrecomercial` varchar(80) default NULL,
  `cif` varchar(80) default NULL,
  `nifcomunitario` varchar(40) default NULL,
  `domicilio` varchar(80) default NULL,
  `poblacion` varchar(80) default NULL,
  `codigopostal` varchar(40) default NULL,
  `provincia` varchar(80) default NULL,
  `pais` varchar(80) default NULL,
  `tfno` varchar(80) default NULL,
  `fax` varchar(80) default NULL,
  `email` varchar(80) default NULL,
  `observaciones` varchar(80) default NULL,
  `ccc` varchar(255) default NULL,
  `cuota` varchar(40) default NULL,
  PRIMARY KEY  (`cuenta`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `datossubcuenta`
--

LOCK TABLES `datossubcuenta` WRITE;
/*!40000 ALTER TABLE `datossubcuenta` DISABLE KEYS */;
/*!40000 ALTER TABLE `datossubcuenta` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `det_as_modelo`
--

DROP TABLE IF EXISTS `det_as_modelo`;
CREATE TABLE `det_as_modelo` (
  `asientomodelo` varchar(255) default NULL,
  `cuenta` varchar(255) default NULL,
  `concepto` varchar(255) default NULL,
  `expresion` varchar(255) default NULL,
  `d_h` varchar(255) default NULL,
  `ci` varchar(255) default NULL,
  `baseiva` varchar(255) default NULL,
  `cuentafra` varchar(255) default NULL,
  `cuentabaseiva` varchar(255) default NULL,
  `claveiva` varchar(255) default NULL,
  `documento` varchar(255) default NULL,
  `orden` int(11) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `det_as_modelo`
--

LOCK TABLES `det_as_modelo` WRITE;
/*!40000 ALTER TABLE `det_as_modelo` DISABLE KEYS */;
/*!40000 ALTER TABLE `det_as_modelo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `diario`
--

DROP TABLE IF EXISTS `diario`;
CREATE TABLE `diario` (
  `asiento` bigint(20) default NULL,
  `pase` bigint(20) NOT NULL default '0',
  `fecha` date default NULL,
  `cuenta` varchar(40) default NULL,
  `debe` decimal(14,2) default NULL,
  `haber` decimal(14,2) default NULL,
  `concepto` varchar(80) default NULL,
  `documento` varchar(40) default NULL,
  `diario` varchar(20) default NULL,
  `ci` varchar(40) default NULL,
  `usuario` varchar(80) default NULL,
  `conciliado` tinyint(1) default '0',
  `dif_conciliacion` varchar(40) default '',
  PRIMARY KEY  (`pase`),
  KEY `cuenta` (`cuenta`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `diario`
--

LOCK TABLES `diario` WRITE;
/*!40000 ALTER TABLE `diario` DISABLE KEYS */;
INSERT INTO `diario` VALUES (1,1,'2008-01-01','10000000','0.00','60000.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,2,'2008-01-01','11200000','0.00','7500.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,3,'2008-01-01','12900000','0.00','5600.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,4,'2008-01-01','21000001','20000.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,5,'2008-01-01','21100001','25000.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,6,'2008-01-01','28110001','0.00','1250.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,7,'2008-01-01','21600001','4000.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,8,'2008-01-01','28160001','0.00','2000.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,9,'2008-01-01','21700001','1000.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,10,'2008-01-01','28170001','0.00','500.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,11,'2008-01-01','21700002','800.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,12,'2008-01-01','28170002','0.00','200.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,13,'2008-01-01','30000000','24000.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,14,'2008-01-01','40000001','0.00','2000.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,15,'2008-01-01','40000002','0.00','1500.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,16,'2008-01-01','43000001','500.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,17,'2008-01-01','43000002','400.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,18,'2008-01-01','47500000','0.00','850.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,19,'2008-01-01','47520000','0.00','300.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(1,20,'2008-01-01','57000000','6000.00','0.00','Asiento de apertura','','APERTURA','','root@localhost',0,''),(2,21,'2008-01-08','47500000','850.00','0.00','Ingreso IVA 4t 2007','','','','root@localhost',0,''),(2,22,'2008-01-08','57000000','0.00','850.00','Ingreso IVA 4t 2007','','','','root@localhost',0,''),(3,23,'2008-01-10','43000001','0.00','500.00','Vto. Cliente A de 01.01.2008','','',NULL,'root@localhost',0,''),(3,24,'2008-01-10','57000000','500.00','0.00','Vto. Cliente A de 01.01.2008','','',NULL,'root@localhost',0,''),(6,30,'2008-01-16','43000002','0.00','400.00','Vto. Cliente B de 01.01.2008','','',NULL,'root@localhost',0,''),(6,31,'2008-01-16','57000000','400.00','0.00','Vto. Cliente B de 01.01.2008','','',NULL,'root@localhost',0,''),(7,32,'2008-01-20','40000001','1500.00','0.00','Vto. Proveedor A de 01.01.2008','','',NULL,'root@localhost',0,''),(7,33,'2008-01-20','57000000','0.00','1500.00','Vto. Proveedor A de 01.01.2008','','',NULL,'root@localhost',0,''),(9,36,'2008-02-10','40000001','500.00','0.00','Vto. Proveedor A de 01.01.2008','','',NULL,'root@localhost',0,''),(9,37,'2008-02-10','57000000','0.00','500.00','Vto. Proveedor A de 01.01.2008','','',NULL,'root@localhost',0,''),(8,34,'2008-02-05','40000002','1500.00','0.00','Vto. Proveedor B de 01.01.2008','','',NULL,'root@localhost',0,''),(8,35,'2008-02-05','57000000','0.00','1500.00','Vto. Proveedor B de 01.01.2008','','',NULL,'root@localhost',0,''),(4,25,'2008-01-10','70000000','0.00','100.00','Cliente A','','','','root@localhost',0,''),(4,26,'2008-01-10','47700000','0.00','16.00','Cliente A','','','','root@localhost',0,''),(4,27,'2008-01-10','43000001','116.00','0.00','Cliente A','','','','root@localhost',0,''),(5,28,'2008-01-10','43000001','0.00','116.00','Vto. Cliente A de 10.01.2008','','',NULL,'root@localhost',0,''),(5,29,'2008-01-10','57000000','116.00','0.00','Vto. Cliente A de 10.01.2008','','',NULL,'root@localhost',0,''),(10,38,'2008-03-15','70000000','0.00','150.00','Cliente B','','','','root@localhost',0,''),(10,39,'2008-03-15','47700000','0.00','24.00','Cliente B','','','','root@localhost',0,''),(10,40,'2008-03-15','43000002','174.00','0.00','Cliente B','','','','root@localhost',0,''),(11,41,'2008-03-15','43000002','0.00','174.00','Vto. Cliente B de 15.03.2008','','',NULL,'root@localhost',0,''),(11,42,'2008-03-15','57000000','174.00','0.00','Vto. Cliente B de 15.03.2008','','',NULL,'root@localhost',0,''),(12,43,'2008-03-18','60000000','1000.00','0.00','Proveedor A','','','','root@localhost',0,''),(12,44,'2008-03-18','47200000','160.00','0.00','Proveedor A','','','','root@localhost',0,''),(12,45,'2008-03-18','40000001','0.00','1160.00','Proveedor A','','','','root@localhost',0,''),(13,46,'2008-03-18','40000001','1160.00','0.00','Vto. Proveedor A de 18.03.2008','','',NULL,'root@localhost',0,''),(13,47,'2008-03-18','57000000','0.00','1160.00','Vto. Proveedor A de 18.03.2008','','',NULL,'root@localhost',0,''),(14,48,'2008-03-31','47200000','0.00','160.00','Liquidación IVA 1t','','','','root@localhost',0,''),(14,49,'2008-03-31','47700000','40.00','0.00','Liquidación IVA 1t','','','','root@localhost',0,''),(14,50,'2008-03-31','47000000','120.00','0.00','Liquidación IVA 1t','','','','root@localhost',0,''),(16,53,'2008-04-20','70000000','0.00','490.00','Cliente A','','','','root@localhost',0,''),(16,54,'2008-04-20','47700000','0.00','78.40','Cliente A','','','','root@localhost',0,''),(16,55,'2008-04-20','43000001','568.40','0.00','Cliente A','','','','root@localhost',0,''),(17,56,'2008-04-20','43000001','0.00','568.40','Vto. Cliente A de 20.04.2008','','',NULL,'root@localhost',0,''),(17,57,'2008-04-20','57000000','568.40','0.00','Vto. Cliente A de 20.04.2008','','',NULL,'root@localhost',0,''),(19,60,'2008-06-10','70000000','0.00','500.00','Cliente B','','','','root@localhost',0,''),(19,61,'2008-06-10','47700000','0.00','80.00','Cliente B','','','','root@localhost',0,''),(19,62,'2008-06-10','43000002','580.00','0.00','Cliente B','','','','root@localhost',0,''),(18,58,'2008-04-20','43000002','0.00','580.00','Vto. Cliente B de 10.06.2008','','',NULL,'root@localhost',0,''),(18,59,'2008-04-20','57000000','580.00','0.00','Vto. Cliente B de 10.06.2008','','',NULL,'root@localhost',0,''),(20,63,'2008-06-30','12900000','5600.00','0.00','Reparto pérdidas y ganancias 2007','','','','root@localhost',0,''),(20,64,'2008-06-30','11200000','0.00','500.00','Reparto pérdidas y ganancias 2007','','','','root@localhost',0,''),(20,65,'2008-06-30','11300000','0.00','5100.00','Reparto pérdidas y ganancias 2007','','','','root@localhost',0,''),(21,66,'2008-06-30','47000000','0.00','120.00','liquidación IVA 2t','','','','root@localhost',0,''),(21,67,'2008-06-30','47700000','158.40','0.00','liquidación IVA 2t','','','','root@localhost',0,''),(21,68,'2008-06-30','47500000','0.00','38.40','liquidación IVA 2t','','','','root@localhost',0,''),(22,69,'2008-07-10','47500000','38.40','0.00','ingreso IVA 2t','','','','root@localhost',0,''),(22,70,'2008-07-10','57000000','0.00','38.40','ingreso IVA 2t','','','','root@localhost',0,''),(23,73,'2008-07-10','52300001','0.00','1044.00','Proveedor de inmovilizado a CP','','','','root@localhost',0,''),(23,72,'2008-07-10','47200000','144.00','0.00','Proveedor de inmovilizado a CP','','','','root@localhost',0,''),(23,71,'2008-07-10','21700003','900.00','0.00','Proveedor de inmovilizado a CP','','','','root@localhost',0,''),(23,74,'2008-07-10','52300001','1044.00','0.00','Proveedor de inmovilizado a CP','','','','root@localhost',0,''),(23,75,'2008-07-10','57000000','0.00','1044.00','Proveedor de inmovilizado a CP','','','','root@localhost',0,''),(24,76,'2008-07-20','70000000','0.00','5000.00','Cliente A','','','','root@localhost',0,''),(24,77,'2008-07-20','47700000','0.00','800.00','Cliente A','','','','root@localhost',0,''),(24,78,'2008-07-20','43000001','5800.00','0.00','Cliente A','','','','root@localhost',0,''),(25,79,'2008-07-20','43000001','0.00','5800.00','Vto. Cliente A de 20.07.2008','','',NULL,'root@localhost',0,''),(25,80,'2008-07-20','57000000','5800.00','0.00','Vto. Cliente A de 20.07.2008','','',NULL,'root@localhost',0,''),(26,81,'2008-07-22','47520000','300.00','0.00','pago impuesto sobre sociedades','','','','root@localhost',0,''),(26,82,'2008-07-22','57000000','0.00','300.00','pago impuesto sobre sociedades','','','','root@localhost',0,''),(27,83,'2008-09-30','47700000','800.00','0.00','liquidación IVA 3T','','','','root@localhost',0,''),(27,84,'2008-09-30','47200000','0.00','144.00','liquidación IVA 3T','','','','root@localhost',0,''),(27,85,'2008-09-30','47500000','0.00','656.00','liquidación IVA 3T','','','','root@localhost',0,''),(28,86,'2008-10-12','47500000','656.00','0.00','Ingreso IVA 3t','','','','root@localhost',0,''),(28,87,'2008-10-12','57000000','0.00','656.00','Ingreso IVA 3t','','','','root@localhost',0,''),(29,88,'2008-10-12','47300001','250.00','0.00','Pago a cuenta IS 2P','','','','root@localhost',0,''),(29,89,'2008-10-12','57000000','0.00','250.00','Pago a cuenta IS 2P','','','','root@localhost',0,''),(30,90,'2008-11-10','70000000','0.00','2000.00','Cliente B','','','','root@localhost',0,''),(30,91,'2008-11-10','47700000','0.00','320.00','Cliente B','','','','root@localhost',0,''),(30,92,'2008-11-10','43000002','2320.00','0.00','Cliente B','','','','root@localhost',0,''),(31,93,'2008-11-10','43000002','0.00','2320.00','Vto. Cliente B de 10.11.2008','','',NULL,'root@localhost',0,''),(31,94,'2008-11-10','57000000','2320.00','0.00','Vto. Cliente B de 10.11.2008','','',NULL,'root@localhost',0,''),(32,95,'2008-12-14','47300001','250.00','0.00','Pago a cuenta IS 3P','','','','root@localhost',0,''),(32,96,'2008-12-14','57000000','0.00','250.00','Pago a cuenta IS 3P','','','','root@localhost',0,''),(33,97,'2008-12-31','47700000','320.00','0.00','Liquidación IVA 4T','','','','root@localhost',0,''),(33,98,'2008-12-31','47500000','0.00','320.00','Liquidación IVA 4T','','','','root@localhost',0,''),(34,99,'2008-12-31','61000001','24000.00','0.00','Saldos iniciales','','','','root@localhost',0,''),(34,100,'2008-12-31','30000000','0.00','24000.00','Saldos iniciales','','','','root@localhost',0,''),(35,101,'2008-12-31','30000000','23000.00','0.00','Saldos finales','','','','root@localhost',0,''),(35,102,'2008-12-31','61000001','0.00','23000.00','Saldos finales','','','','root@localhost',0,''),(36,107,'2008-12-31','28170003','0.00','106.64','Amortización del inmovilizado','','','','root@localhost',0,''),(36,106,'2008-12-31','28170002','0.00','200.00','Amortización del inmovilizado','','','','root@localhost',0,''),(36,105,'2008-12-31','28170001','0.00','250.00','Amortización del inmovilizado','','','','root@localhost',0,''),(36,104,'2008-12-31','28160001','0.00','800.00','Amortización del inmovilizado','','','','root@localhost',0,''),(36,103,'2008-12-31','28110001','0.00','500.00','Amortización del inmovilizado','','','','root@localhost',0,''),(36,108,'2008-12-31','68100001','1856.64','0.00','Amortización del inmovilizado','','','','root@localhost',0,''),(37,143,'2008-12-31','47520000','0.00','377.00','Liquidación impuesto sobre sociedades','','','','root@localhost',0,''),(37,142,'2008-12-31','47300001','0.00','700.00','Liquidación impuesto sobre sociedades','','','','root@localhost',0,''),(37,141,'2008-12-31','63000000','1077.00','0.00','Liquidación impuesto sobre sociedades','','','','root@localhost',0,''),(38,112,'2008-12-31','63010001','238.01','0.00','Cálculo del impuesto diferido','','','','root@localhost',0,''),(38,113,'2008-12-31','47900001','0.00','238.01','Cálculo del impuesto diferido','','','','root@localhost',0,''),(15,52,'2008-04-15','57000000','0.00','200.00','Pago a cuenta 1P IS','','','','root@localhost',0,''),(15,51,'2008-04-15','47300001','200.00','0.00','Pago a cuenta 1P IS','','','','root@localhost',0,''),(41,144,'2008-12-31','60000000','0.00','1000.00','REGULARIZACIÓN','','REGULARIZACION',NULL,'root@localhost',0,''),(41,145,'2008-12-31','61000001','0.00','1000.00','REGULARIZACIÓN','','REGULARIZACION',NULL,'root@localhost',0,''),(41,146,'2008-12-31','63000000','0.00','1077.00','REGULARIZACIÓN','','REGULARIZACION',NULL,'root@localhost',0,''),(41,147,'2008-12-31','63010001','0.00','238.01','REGULARIZACIÓN','','REGULARIZACION',NULL,'root@localhost',0,''),(41,148,'2008-12-31','68100001','0.00','1856.64','REGULARIZACIÓN','','REGULARIZACION',NULL,'root@localhost',0,''),(41,149,'2008-12-31','70000000','8240.00','0.00','REGULARIZACIÓN','','REGULARIZACION',NULL,'root@localhost',0,''),(41,150,'2008-12-31','12900000','0.00','3068.35','REGULARIZACIÓN','','REGULARIZACION',NULL,'root@localhost',0,'');
/*!40000 ALTER TABLE `diario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `diarios`
--

DROP TABLE IF EXISTS `diarios`;
CREATE TABLE `diarios` (
  `codigo` varchar(40) NOT NULL default '',
  `descripcion` varchar(255) default NULL,
  PRIMARY KEY  (`codigo`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `diarios`
--

LOCK TABLES `diarios` WRITE;
/*!40000 ALTER TABLE `diarios` DISABLE KEYS */;
/*!40000 ALTER TABLE `diarios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dif_conciliacion`
--

DROP TABLE IF EXISTS `dif_conciliacion`;
CREATE TABLE `dif_conciliacion` (
  `codigo` varchar(40) NOT NULL default '',
  `descripcion` varchar(80) default '',
  PRIMARY KEY  (`codigo`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dif_conciliacion`
--

LOCK TABLES `dif_conciliacion` WRITE;
/*!40000 ALTER TABLE `dif_conciliacion` DISABLE KEYS */;
/*!40000 ALTER TABLE `dif_conciliacion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ejercicios`
--

DROP TABLE IF EXISTS `ejercicios`;
CREATE TABLE `ejercicios` (
  `codigo` varchar(40) NOT NULL default '',
  `apertura` date default NULL,
  `cierre` date default NULL,
  `cerrado` tinyint(1) default NULL,
  `cerrando` tinyint(1) default NULL,
  `primerasiento` bigint(20) default NULL,
  `base_ejercicio` varchar(80) default '',
  `base_presupuesto` varchar(80) default '',
  `presupuesto_base_cero` tinyint(1) default '1',
  `incremento` decimal(14,4) default '0.0000',
  PRIMARY KEY  (`codigo`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ejercicios`
--

LOCK TABLES `ejercicios` WRITE;
/*!40000 ALTER TABLE `ejercicios` DISABLE KEYS */;
INSERT INTO `ejercicios` VALUES ('2008','2008-01-01','2008-12-31',0,0,1,'','',1,'0.0000');
/*!40000 ALTER TABLE `ejercicios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `equivalenciasplan`
--

DROP TABLE IF EXISTS `equivalenciasplan`;
CREATE TABLE `equivalenciasplan` (
  `cod` varchar(40) NOT NULL default '',
  `equiv` varchar(40) default NULL,
  PRIMARY KEY  (`cod`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `equivalenciasplan`
--

LOCK TABLES `equivalenciasplan` WRITE;
/*!40000 ALTER TABLE `equivalenciasplan` DISABLE KEYS */;
/*!40000 ALTER TABLE `equivalenciasplan` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `estados`
--

DROP TABLE IF EXISTS `estados`;
CREATE TABLE `estados` (
  `titulo` varchar(166) NOT NULL default '',
  `apartado` varchar(255) default NULL,
  `parte1` tinyint(1) NOT NULL default '0',
  `clave` varchar(255) default NULL,
  `nodo` varchar(166) NOT NULL default '',
  `formula` varchar(255) default NULL,
  `referencia` varchar(80) default NULL,
  `importe1` decimal(14,2) default NULL,
  `importe2` decimal(14,2) default NULL,
  `calculado` tinyint(1) default NULL,
  PRIMARY KEY  (`titulo`,`nodo`,`parte1`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `estados`
--

LOCK TABLES `estados` WRITE;
/*!40000 ALTER TABLE `estados` DISABLE KEYS */;
INSERT INTO `estados` VALUES ('BALANCE PYMES PLAN 2007','VII. Resultado del ejercicio',0,'7','A.1.7','-[129]','','3068.35','0.00',1),('BALANCE PYMES PLAN 2007','VIII. Dividendo a cuenta',0,'8','A.1.8','-[557]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','A-2) Subvenciones, donaciones y legados recibidos',0,'2','A.2','-[130]-[131]-[132]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','VI. Otras aportaciones de socios',0,'6','A.1.6','-[118]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','V. Resultados de ejercicios anteriores',0,'5','A.1.5','-[120]-[121]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','IV. Acciones y participaciones en patrimonio propias',0,'4','A.1.4','-[108]-[109]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','1. Capital escriturado',0,'1','A.1.1.1','-[100]-[101]-[102]','','60000.00','0.00',1),('BALANCE PYMES PLAN 2007','2. Capital no exigido',0,'2','A.1.1.2','-[1030]-[1040]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','II. Prima de emisión',0,'2','A.1.2','-[110]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','III. Reservas',0,'3','A.1.3','-[112]-[113]-[114]-[119]','','13100.00','0.00',1),('BALANCE PYMES PLAN 2007','I. Capital',0,'1','A.1.1','{A.1.1.1(2)}+{A.1.1.2(2)}','','60000.00','0.00',1),('BALANCE PYMES PLAN 2007','A) PATRIMONIO NETO',0,'A','A','{A.1(2)}+{A.2(2)}','','76168.35','0.00',1),('BALANCE PYMES PLAN 2007','A-1) Fondos propios',0,'1','A.1','{A.1.1(2)}+{A.1.2(2)}+{A.1.3(2)}+{A.1.4(2)}+{A.1.5(2)}+{A.1.6(2)}+{A.1.7(2)}+{A.1.8(2)}','','76168.35','0.00',1),('BALANCE PYMES PLAN 2007','TOTAL ACTIVO (A+B)',1,'TOTAL','TOTAL','{A(1)}+{B(1)}','','77103.36','0.00',1),('BALANCE PYMES PLAN 2007','VI. Efectivo y otros activos líquidos equivalentes',1,'6','B.6','[57]','','8210.00','0.00',1),('BALANCE PYMES PLAN 2007','V. Periodificaciones a corto plazo',1,'5','B.5','[480]+[567]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','IV. Inversiones financieras a corto plazo',1,'4','B.4','[5305]+[5315]+[5325]+[5335]+[5345]+[5355]+[5395]+[540]+[541]+[542]+[543]+[545]+[546]+[547]+[548]+[549]+[551+] +[5525+] +[5590]+[565]+[566]+[5935]+[5945]+[5955]+[596]+[597]+[598]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','III. Inversiones en empresas del grupo y asociadas a corto  plazo',1,'3','B.3','[5303]+[5304]+[5313]+[5314]+[5323]+[5324]+[5333]+[5334]+[5343]+[5344]+[5353]+[5354]+[5393]+[5394]+[5523]+ [5524]+ [5933]+[5934]+ [5943]+[5944]+[5953]+[5954]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','3. Otros deudores',1,'3','B.2.3','[44]+[460]+[470]+[471]+[472]+[544]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','2. Accionistas (socios) por desembolsos exigidos',1,'2','B.2.2','[5580]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','1. Clientes por ventas y Prestaciones de servicios',1,'1','B.2.1','[430]+[431]+[432]+[433]+[434]+[435]+[436]+[437]+[490]+[493]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','I. Existencias',1,'1','B.1','[30]+[31]+[32]+[33]+[34]+[35]+[36]+[39]+[407]','','23000.00','0.00',1),('BALANCE PYMES PLAN 2007','II. Deudores comerciales y otras cuentas a cobrar',1,'2','B.2','{B.2.1(1)}+{B.2.2(1)}+{B.2.3(1)}','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','B) ACTIVO CORRIENTE',1,'B','B','{B.1(1)}+{B.2(1)}+{B.3(1)}+{B.4(1)}+{B.5(1)}+{B.6(1)}','','31210.00','0.00',1),('BALANCE PYMES PLAN 2007','A) ACTIVO NO CORRIENTE',1,'A','A','{A.1(1)}+{A.2(1)}+{A.3(1)}+{A.4(1)}+{A.5(1)}+{A.6(1)}','','45893.36','0.00',1),('BALANCE PYMES PLAN 2007','I. Inmovilizado intangible',1,'1','A.1','[20]+[280]+[290]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','II. Inmovilizado material',1,'2','A.2','[21]+[281]+[291]+[23]','','45893.36','0.00',1),('BALANCE PYMES PLAN 2007','III. Inversiones inmobiliarias',1,'3','A.3','[22]+[282]+[292]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','IV. Inversiones en empresas del grupo y asociadas a largo plazo',1,'4','A.4','[2403]+[2404]+[2413]+[2414]+[2423]+[2424]+[2493]+[2494]+[2933]+[2934]+[2943]+[2944] + [2953] + [2954]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','V. Inversiones financieras a largo plazo',1,'5','A.5','[2405]+[2415]+[2425]+ [2495]  +[250]+[251]+[252]+[253]+[254] +[255]+[258]+[259]+[26]+[2935]+[2945]+ [2955]+ [296]+ [297]+ [298]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','VI. Activos por impuesto diferido',1,'6','A.6','[474]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','D) RESULTADO DEL EJERCICIO (C+17)',1,'18D','18D','{16C(1)}+{17(1)}','','3068.35','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','B) RESULTADO FINANCIERO (12+13+14+15+16)',1,'16B','16B','{12(1)}+{13(1)}+{14(1)}+{15(1)}+{16(1)}','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','C) RESULTADO ANTES DE IMPUESTOS (A+B)',1,'16C','16C','{11A(1)}+{16B(1)}','','4383.36','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','17. Impuesto sobre beneficios',1,'17','17','-[6300]-[6301]-[633]-[638]','','-1315.01','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','A) RESULTADO DE EXPLOTACIÓN (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 )',1,'11A','11A','{01(1)}+{02(1)}+{03(1)}+{04(1)}+{05(1)}+{06(1)}+{07(1)}+{08(1)}+{09(1)}+{10(1)}+{11(1)}','','4383.36','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','15. Diferencias de cambio',1,'15','15','-[668]-[768]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','16. Deterioro y resultado por enajenaciones de instrumentos financieros',1,'16','16','-[666]-[667]-[673]-[675]-[696]-[697]-[698]-[699]-[766]-[773]-[775]-[796]-[797]-[798]-[799]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','13. Gastos financieros',1,'13','13','-[660]-[661]-[662]-[664]-[665]-[669]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','14. Variación del valor razonable en instrumentos financieros',1,'14','14','-[663]-[763]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','10. Excesos de provisiones',1,'10','10','-[7951]-[7952]-[7955]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','11. Deterioro y resultado por enajenaciones del inmovilizado',1,'11','11','-[670]-[671]-[672]-[690]-[691]-[692]-[770]-[771]-[772]-[790]-[791]-[792]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','12. Ingresos financieros',1,'12','12','-[760]-[761]-[762]-[769]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','8. Amortización del inmovilizado',1,'08','08','-[68]','','-1856.64','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','9. Imputación de subvenciones de inmovilizado no financiero y otras',1,'09','09','-[746]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','6. Gastos de personal',1,'06','06','-[64]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','7. Otros gastos de explotación',1,'07','07','-[62]-[631]-[634]-[636]-[639]-[65]-[694]-[695]-[794]-[7954]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','5. Otros ingresos de explotación',1,'05','05','-[740]-[747]-[75]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','3. Trabajos realizados por la empresa para su activo',1,'03','03','-[73]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','4. Aprovisionamientos',1,'04','04','-[600]-[601]-[602]-[606]-[607]-[608]-[609]-[61]-[6931]-[6932]-[6933]-[7931]-[7932]-[7933]','','-2000.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','2. Variación de existencias de productos terminados y en curso de fabricación',1,'02','02','-[71]-[6930]-[7930]','','0.00','0.00',1),('CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007','1. Importe neto de la cifra de negocios',1,'01','01','-[700]-[701]-[702]-[703]-[704]-[705]-[706]-[708]-[709]','','8240.00','0.00',1),('BALANCE PYMES PLAN 2007','V. Periodificaciones',0,'5','C.5','-[485]-[568]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','TOTAL PATRIMONIO NETO Y PASIVO (A + B + C)',0,'TOTAL','TOTAL','{A(2)}+{B(2)}+{C(2)}','','77103.36','0.00',1),('BALANCE PYMES PLAN 2007','1. Proveedores',0,'1','C.4.1','-[400]-[401]-[403]-[404]-[405]-[406]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','2. Otros acreedores',0,'2','C.4.2','-[41]-[438]-[465]-[475]-[476]-[477]','','697.00','0.00',1),('BALANCE PYMES PLAN 2007','IV. Acreedores comerciales y otras cuentas a pagar',0,'4','C.4','{C.4.1(2)}+{C.4.2(2)}','','697.00','0.00',1),('BALANCE PYMES PLAN 2007','III. Deudas con empresas del grupo y asociadas a corto plazo',0,'3','C.3','-[5103]-[5104]-[5113]-[5114]-[5123]-[5124]-[5133]-[5134]-[5143]-[5144]-[5523]-[5524]-[5563]-[5564]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','1. Deudas con entidades de crédito',0,'1','C.2.1','-[5105]-[520]-[527]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','2. Acreedores por arrendamiento financiero',0,'2','C.2.2','-[5125]-[524]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','3. Otras deudas a corto plazo',0,'3','C.2.3','-[1034]-[1044]-[190]-[192]-[194]-[500]-[505]-[506]-[509]-[5115]-[5135]-[5145]-[521]-[522]-[523]-[525]-[526]-[528]-[551-]-[5525-]- [555]- [5565] -[5566]-[5595]-[560]-[561]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','II. Deudas a corto plazo',0,'2','C.2','{C.2.1(2)}+{C.2.2(2)}+{C.2.3(2)}','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','I. Provisiones a corto plazo',0,'1','C.1','-[499]-[529]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','C) PASIVO CORRIENTE',0,'C','C','{C.1(2)}+{C.2(2)}+{C.3(2)}+{C.4(2)}+{C.5(2)}','','697.00','0.00',1),('BALANCE PYMES PLAN 2007','V. Periodificaciones a largo plazo',0,'5','B.5','-[181]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','IV. Pasivos por impuesto diferido',0,'4','B.4','-[479]','','238.01','0.00',1),('BALANCE PYMES PLAN 2007','3. Otras deudas a largo plazo',0,'3','B.2.3','-[1615]-[1635]-[171]-[172]-[173]-[175]-[176]-[177]-[179]-[180]-[185]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','III. Deudas con empresas del grupo y asociadas a largo plazo',0,'3','B.3','-[1603]-[1604]-[1613]-[1614]-[1623]-[1624]-[1633]-[1634]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','1. Deudas con entidades de crédito',0,'1','B.2.1','-[1605]-[170]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','2. Acreedores por arrendamiento financiero',0,'2','B.2.2','-[1625]-[174]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','II. Deudas a largo plazo',0,'2','B.2','{B.2.1(2)}+{B.2.2(2)}+{B.2.3(2)}','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','I. Provisiones a largo plazo',0,'1','B.1','-[14]','','0.00','0.00',1),('BALANCE PYMES PLAN 2007','B) PASIVO NO CORRIENTE',0,'B','B','{B.1(2)}+{B.2(2)}+{B.3(2)}+{B.4(2)}+{B.5(2)}','','238.01','0.00',1),('BALANCE GRAFICO','A) ACTIVO NO CORRIENTE',1,'A','A','{A.1(1)}+{A.2(1)}+{A.3(1)}+{A.4(1)}+{A.5(1)}+{A.6(1)}',NULL,'45893.36','0.00',1),('BALANCE GRAFICO','I. Inmovilizado intangible',1,'1','A.1','[20]+[280]+[290]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','II. Inmovilizado material',1,'2','A.2','[21]+[281]+[291]+[23]',NULL,'45893.36','0.00',1),('BALANCE GRAFICO','III. Inversiones inmobiliarias',1,'3','A.3','[22]+[282]+[292]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','IV. Inversiones en empresas del grupo y asociadas a largo plazo',1,'4','A.4','[2403]+[2404]+[2413]+[2414]+[2423]+[2424]+[2493]+[2494]+[2933]+[2934]+[2943]+[2944] + [2953] + [2954]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','V. Inversiones financieras a largo plazo',1,'5','A.5','[2405]+[2415]+[2425]+ [2495]  +[250]+[251]+[252]+[253]+[254] +[255]+[258]+[259]+[26]+[2935]+[2945]+ [2955]+ [296]+ [297]+ [298]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','VI. Activos por impuesto diferido',1,'6','A.6','[474]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','B) ACTIVO CORRIENTE',1,'B','B','{B.1(1)}+{B.2(1)}+{B.3(1)}+{B.4(1)}+{B.5(1)}+{B.6(1)}',NULL,'31210.00','0.00',1),('BALANCE GRAFICO','I. Existencias',1,'1','B.1','[30]+[31]+[32]+[33]+[34]+[35]+[36]+[39]+[407]',NULL,'23000.00','0.00',1),('BALANCE GRAFICO','II. Deudores comerciales y otras cuentas a cobrar',1,'2','B.2','{B.2.1(1)}+{B.2.2(1)}+{B.2.3(1)}',NULL,'0.00','0.00',1),('BALANCE GRAFICO','1. Clientes por ventas y Prestaciones de servicios',1,'1','B.2.1','[430]+[431]+[432]+[433]+[434]+[435]+[436]+[437]+[490]+[493]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','2. Accionistas (socios) por desembolsos exigidos',1,'2','B.2.2','[5580]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','3. Otros deudores',1,'3','B.2.3','[44]+[460]+[470]+[471]+[472]+[544]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','III. Inversiones en empresas del grupo y asociadas a corto  plazo',1,'3','B.3','[5303]+[5304]+[5313]+[5314]+[5323]+[5324]+[5333]+[5334]+[5343]+[5344]+[5353]+[5354]+[5393]+[5394]+[5523]+ [5524]+ [5933]+[5934]+ [5943]+[5944]+[5953]+[5954]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','IV. Inversiones financieras a corto plazo',1,'4','B.4','[5305]+[5315]+[5325]+[5335]+[5345]+[5355]+[5395]+[540]+[541]+[542]+[543]+[545]+[546]+[547]+[548]+[549]+[551+] +[5525+] +[5590]+[565]+[566]+[5935]+[5945]+[5955]+[596]+[597]+[598]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','V. Periodificaciones a corto plazo',1,'5','B.5','[480]+[567]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','VI. Efectivo y otros activos líquidos equivalentes',1,'6','B.6','[57]',NULL,'8210.00','0.00',1),('BALANCE GRAFICO','A) PATRIMONIO NETO',0,'A','A','{A.1(2)}+{A.2(2)}',NULL,'76168.35','0.00',1),('BALANCE GRAFICO','A-1) Fondos propios',0,'1','A.1','{A.1.1(2)}+{A.1.2(2)}+{A.1.3(2)}+{A.1.4(2)}+{A.1.5(2)}+{A.1.6(2)}+{A.1.7(2)}+{A.1.8(2)}',NULL,'76168.35','0.00',1),('BALANCE GRAFICO','I. Capital',0,'1','A.1.1','{A.1.1.1(2)}+{A.1.1.2(2)}',NULL,'60000.00','0.00',1),('BALANCE GRAFICO','1. Capital escriturado',0,'1','A.1.1.1','-[100]-[101]-[102]',NULL,'60000.00','0.00',1),('BALANCE GRAFICO','2. Capital no exigido',0,'2','A.1.1.2','-[1030]-[1040]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','II. Prima de emisión',0,'2','A.1.2','-[110]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','III. Reservas',0,'3','A.1.3','-[112]-[113]-[114]-[119]',NULL,'13100.00','0.00',1),('BALANCE GRAFICO','IV. Acciones y participaciones en patrimonio propias',0,'4','A.1.4','-[108]-[109]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','V. Resultados de ejercicios anteriores',0,'5','A.1.5','-[120]-[121]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','VI. Otras aportaciones de socios',0,'6','A.1.6','-[118]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','VII. Resultado del ejercicio',0,'7','A.1.7','-[129]',NULL,'3068.35','0.00',1),('BALANCE GRAFICO','VIII. Dividendo a cuenta',0,'8','A.1.8','-[557]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','A-2) Subvenciones, donaciones y legados recibidos',0,'2','A.2','-[130]-[131]-[132]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','B) PASIVO NO CORRIENTE',0,'B','B','{B.1(2)}+{B.2(2)}+{B.3(2)}+{B.4(2)}+{B.5(2)}',NULL,'238.01','0.00',1),('BALANCE GRAFICO','I. Provisiones a largo plazo',0,'1','B.1','-[14]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','II. Deudas a largo plazo',0,'2','B.2','{B.2.1(2)}+{B.2.2(2)}+{B.2.3(2)}',NULL,'0.00','0.00',1),('BALANCE GRAFICO','1. Deudas con entidades de crédito',0,'1','B.2.1','-[1605]-[170]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','2. Acreedores por arrendamiento financiero',0,'2','B.2.2','-[1625]-[174]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','3. Otras deudas a largo plazo',0,'3','B.2.3','-[1615]-[1635]-[171]-[172]-[173]-[175]-[176]-[177]-[179]-[180]-[185]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','III. Deudas con empresas del grupo y asociadas a largo plazo',0,'3','B.3','-[1603]-[1604]-[1613]-[1614]-[1623]-[1624]-[1633]-[1634]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','IV. Pasivos por impuesto diferido',0,'4','B.4','-[479]',NULL,'238.01','0.00',1),('BALANCE GRAFICO','V. Periodificaciones a largo plazo',0,'5','B.5','-[181]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','C) PASIVO CORRIENTE',0,'C','C','{C.1(2)}+{C.2(2)}+{C.3(2)}+{C.4(2)}+{C.5(2)}',NULL,'697.00','0.00',1),('BALANCE GRAFICO','I. Provisiones a corto plazo',0,'1','C.1','-[499]-[529]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','II. Deudas a corto plazo',0,'2','C.2','{C.2.1(2)}+{C.2.2(2)}+{C.2.3(2)}',NULL,'0.00','0.00',1),('BALANCE GRAFICO','1. Deudas con entidades de crédito',0,'1','C.2.1','-[5105]-[520]-[527]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','2. Acreedores por arrendamiento financiero',0,'2','C.2.2','-[5125]-[524]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','3. Otras deudas a corto plazo',0,'3','C.2.3','-[1034]-[1044]-[190]-[192]-[194]-[500]-[505]-[506]-[509]-[5115]-[5135]-[5145]-[521]-[522]-[523]-[525]-[526]-[528]-[551-]-[5525-]- [555]- [5565] -[5566]-[5595]-[560]-[561]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','III. Deudas con empresas del grupo y asociadas a corto plazo',0,'3','C.3','-[5103]-[5104]-[5113]-[5114]-[5123]-[5124]-[5133]-[5134]-[5143]-[5144]-[5523]-[5524]-[5563]-[5564]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','IV. Acreedores comerciales y otras cuentas a pagar',0,'4','C.4','{C.4.1(2)}+{C.4.2(2)}',NULL,'697.00','0.00',1),('BALANCE GRAFICO','1. Proveedores',0,'1','C.4.1','-[400]-[401]-[403]-[404]-[405]-[406]',NULL,'0.00','0.00',1),('BALANCE GRAFICO','2. Otros acreedores',0,'2','C.4.2','-[41]-[438]-[465]-[475]-[476]-[477]',NULL,'697.00','0.00',1),('BALANCE GRAFICO','V. Periodificaciones',0,'5','C.5','-[485]-[568]',NULL,'0.00','0.00',1);
/*!40000 ALTER TABLE `estados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `libroiva`
--

DROP TABLE IF EXISTS `libroiva`;
CREATE TABLE `libroiva` (
  `pase` bigint(20) NOT NULL default '0',
  `cta_base_iva` varchar(40) default NULL,
  `base_iva` decimal(14,2) default NULL,
  `clave_iva` varchar(4) default NULL,
  `tipo_iva` decimal(5,2) default NULL,
  `tipo_re` decimal(5,2) default NULL,
  `cuota_iva` decimal(14,2) default NULL,
  `cuenta_fra` varchar(40) default NULL,
  `fecha_fra` date default NULL,
  `soportado` tinyint(1) default NULL,
  `aib` tinyint(1) default NULL,
  `eib` tinyint(1) default NULL,
  `prorrata` decimal(5,2) default '1.00',
  `rectificativa` tinyint(1) default '0',
  `autofactura` tinyint(1) default '0',
  PRIMARY KEY  (`pase`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `libroiva`
--

LOCK TABLES `libroiva` WRITE;
/*!40000 ALTER TABLE `libroiva` DISABLE KEYS */;
INSERT INTO `libroiva` VALUES (26,'70000000','100.00','GN','16.00','0.00','16.00','43000001','2008-01-10',0,0,0,'1.00',0,0),(39,'70000000','150.00','GN','16.00','0.00','24.00','43000002','2008-03-15',0,0,0,'1.00',0,0),(44,'60000000','1000.00','GN','16.00','0.00','160.00','40000001','2008-03-18',1,0,0,'1.00',0,0),(54,'70000000','490.00','GN','16.00','0.00','78.40','43000001','2008-04-20',0,0,0,'1.00',0,0),(61,'70000000','500.00','GN','16.00','0.00','80.00','43000002','2008-06-10',0,0,0,'1.00',0,0),(72,'21700003','900.00','GN','16.00','0.00','144.00','52300001','2008-07-10',1,0,0,'1.00',0,0),(77,'70000000','5000.00','GN','16.00','0.00','800.00','43000001','2008-07-20',0,0,0,'1.00',0,0),(91,'70000000','2000.00','GN','16.00','0.00','320.00','43000002','2008-11-10',0,0,0,'1.00',0,0);
/*!40000 ALTER TABLE `libroiva` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nuevoplan`
--

DROP TABLE IF EXISTS `nuevoplan`;
CREATE TABLE `nuevoplan` (
  `codigo` varchar(40) NOT NULL default '',
  `descripcion` varchar(255) default NULL,
  PRIMARY KEY  (`codigo`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `nuevoplan`
--

LOCK TABLES `nuevoplan` WRITE;
/*!40000 ALTER TABLE `nuevoplan` DISABLE KEYS */;
/*!40000 ALTER TABLE `nuevoplan` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `periodos`
--

DROP TABLE IF EXISTS `periodos`;
CREATE TABLE `periodos` (
  `ejercicio` varchar(40) NOT NULL default '',
  `codigo` varchar(40) NOT NULL default '',
  `inicio` date default NULL,
  `fin` date default NULL,
  PRIMARY KEY  (`ejercicio`,`codigo`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `periodos`
--

LOCK TABLES `periodos` WRITE;
/*!40000 ALTER TABLE `periodos` DISABLE KEYS */;
INSERT INTO `periodos` VALUES ('2008','ENERO','2008-01-01','2008-01-31'),('2008','FEBRERO','2008-02-01','2008-02-29'),('2008','MARZO','2008-03-01','2008-03-31'),('2008','ABRIL','2008-04-01','2008-04-30'),('2008','MAYO','2008-05-01','2008-05-31'),('2008','JUNIO','2008-06-01','2008-06-30'),('2008','JULIO','2008-07-01','2008-07-31'),('2008','AGOSTO','2008-08-01','2008-08-31'),('2008','SEPTIEMBRE','2008-09-01','2008-09-30'),('2008','OCTUBRE','2008-10-01','2008-10-31'),('2008','NOVIEMBRE','2008-11-01','2008-11-30'),('2008','DICIEMBRE','2008-12-01','2008-12-31');
/*!40000 ALTER TABLE `periodos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `planamortizaciones`
--

DROP TABLE IF EXISTS `planamortizaciones`;
CREATE TABLE `planamortizaciones` (
  `cuenta_activo` varchar(40) NOT NULL default '',
  `fecha_func` date default NULL,
  `codigo_activo` varchar(40) default NULL,
  `cuenta_am_acum` varchar(40) default NULL,
  `cuenta_gasto` varchar(40) default NULL,
  `valor_residual` decimal(14,2) default NULL,
  `amort_personalizada` tinyint(1) default NULL,
  `coef_amort_contable` double default NULL,
  `coef_amort_fiscal` double default NULL,
  `amort_fiscal_1ejer` tinyint(1) default NULL,
  PRIMARY KEY  (`cuenta_activo`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `planamortizaciones`
--

LOCK TABLES `planamortizaciones` WRITE;
/*!40000 ALTER TABLE `planamortizaciones` DISABLE KEYS */;
INSERT INTO `planamortizaciones` VALUES ('21100001','2002-07-01','','28110001','68100001','0.00',0,0.02,0,0),('21600001','2005-07-01','','28160001','68100001','0.00',0,0.2,0,0),('21700001','2006-01-01','PC1','28170001','68100001','0.00',0,0.25,0,0),('21700002','2007-01-01','PC2','28170002','68100001','0.00',0,0.25,0,0),('21700003','2008-07-12','PC3','28170003','68100001','0.00',0,0.25,0,1);
/*!40000 ALTER TABLE `planamortizaciones` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `plancontable`
--

DROP TABLE IF EXISTS `plancontable`;
CREATE TABLE `plancontable` (
  `codigo` varchar(40) default NULL,
  `descripcion` varchar(255) default NULL,
  `auxiliar` tinyint(1) default '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `plancontable`
--

LOCK TABLES `plancontable` WRITE;
/*!40000 ALTER TABLE `plancontable` DISABLE KEYS */;
INSERT INTO `plancontable` VALUES ('1','FINANCIACIÓN BÁSICA',0),('10','CAPITAL',0),('100','Capital social',0),('10000000','Capital social',0),('101','Fondo social',0),('102','Capital',0),('103','Socios por desembolsos no exigidos',0),('1033','Socios por desembolsos no exigidos, empresas del grupo',0),('1034','Socios por desembolsos no exigidos, empresas asociadas',0),('1035','Socios por desembolsos no exigidos, otras partes vinculadas',0),('1036','Otros socios por desembolsos no exigidos',0),('104','Socios por aportaciones no dinerarias pendientes',0),('1043','Socios por aportaciones no dinerarias pendientes, empresas del grupo',0),('1044','Socios por aportaciones no dinerarias pendientes, empresas asociadas',0),('1045','Socios por aportaciones no dinerarias pendientes, otras partes vinculadas',0),('1046','Otros socios por aportaciones no dinerarias pendientes',0),('108','Acciones o participaciones propias en situaciones especiales',0),('109','Acciones o participaciones propias para reducción de capital',0),('11','RESERVAS',0),('110','Prima de emisión o asunción',0),('112','Reservas legal',0),('11200000','Reserva legal',0),('113','Reserva voluntaria',0),('11300000','Reservas voluntarias',0),('114','Reservas especiales',0),('1140','Reservas para acciones o participaciones de la sociedad dominante',0),('1141','Reservas estatutarias',0),('1142','Reservas por capital amortizado',0),('118','Aportaciones de socios o propietarios',0),('119','Diferencias por ajuste del capital a euros',0),('12','RESULTADOS PENDIENTES DE APLICACIÓN',0),('120','Remanente',0),('121','Resultados negativos de ejercicios anteriores',0),('129','Resultados del ejercicio',0),('12900000','Pérdidas y Ganancias',0),('13','SUBVENCIONES, DONACIONES Y AJUSTES POR CAMBIOS DE VALOR',0),('130','Subvenciones oficiales de capital',0),('131','Donaciones y legados de capital',0),('132','Otras subvenciones, donaciones y legados',0),('133','Ajustes por valoración en activos financieros disponibles para la venta',0),('1330','Ajustes por activos financieros para la venta.',0),('1331','Ajustes por valoración en pasivos financieros a valor razonable con cambios en patrimonio neto.',0),('134','Operaciones de cobertura',0),('1340','Cobertura de flujos de efectivo',0),('1341','Cobertura de una inversión neta en un negocio en el extranjero',0),('135','Diferencias de conversión',0),('136','Ajustes por valoración en activos no corrientes y grupos enajenables de elementos mantenidos para la venta',0),('137','Ingresos fiscales a distribuir en varios ejercicios',0),('1370','Ingresos fiscales por diferencias permanentes a distribuir en varios ejercicios',0),('1371','Ingresos fiscales por deducciones y bonificaciones a distribuir en varios ejercicios',0),('14','PROVISIONES',0),('140','Provisión para retribuciones y otras prestaciones al personal',0),('141','Provisión para impuestos',0),('142','Provisión para otras responsabilidades',0),('143','Provisión por desmantelamiento, retiro o rehabilitación del inmovilizado.',0),('144','Provisión por contratos onerosos',0),('145','Provisión para actuaciones medioambientales',0),('15','DEUDAS A LARGO PLAZO CON CARACTERÍSTICAS ESPECIALES',0),('150','Acciones o participaciones a largo plazo contabilizadas como pasivo',0),('153','Desembolsos no exigidos por acciones o participaciones contabilizadas como pasivo',0),('1533','Desembolsos no exigidos, empresas del grupo',0),('1534','Desembolsos no exigidos, empresas asociadas',0),('1535','Desembolsos no exigidos, otras partes vinculadas',0),('1536','Otros desembolsos no exigidos',0),('154','Aportaciones no dinerarias pendientes por acciones o participaciones contabilizadas como pasivo',0),('1543','Aportaciones no dinerarias pendientes, empresas del grupo',0),('1544','Aportaciones no dinerarias pendientes, empresas asociadas',0),('1545','Aportaciones no dinerarias pendientes, otras partes vinculadas',0),('1546','Otras aportaciones no dinerarias pendientes',0),('16','DEUDAS A LARGO PLAZO CON PARTES VINCULADAS',0),('160','Deudas a largo plazo con entidades de crédito vinculadas',0),('1603','Deudas a largo plazo con entidades de crédito, empresas del grupo',0),('1604','Deudas a largo plazo con entidades de crédito, empresas asociadas',0),('1605','Deudas a largo plazo con otras entidades de crédito vinculadas',0),('161','Proveedores de inmovilizado a largo plazo, partes vinculadas',0),('1613','Proveedores de inmovilizado a largo plazo, empresas del grupo',0),('1614','Proveedores de inmovilizado a largo plazo, empresas asociadas',0),('1615','Proveedores de inmovilizado a largo plazo, otras partes vinculadas',0),('162','Otras deudas a largo plazo con partes vinculadas',0),('1623','Otras deudas a largo plazo, empresas del grupo',0),('1624','Otras deudas a largo plazo, empresas asociadas',0),('1625','Otras deudas a largo plazo, con otras partes vinculadas',0),('17','DEUDAS A LARGO PLAZO POR PRÉSTAMOS RECIBIDOS Y OTROS CONCEPTOS',0),('170','Deudas a largo plazo con entidades de crédito',0),('171','Deudas a largo plazo',0),('172','Deudas a largo plazo transformables en subvenciones',0),('173','Proveedores de inmovilizado a largo plazo',0),('174','Efectos a pagar a largo plazo',0),('176','Obligaciones y bonos',0),('177','Obligaciones y bonos convertibles',0),('178','Deudas representadas en otros valores negociables',0),('18','PASIVOS POR FIANZAS Y GARANTÍAS A LARGO PLAZO',0),('180','Fianzas recibidas a largo plazo',0),('185','Depósitos recibidos a largo plazo',0),('189','Garantías financieras a largo plazo',0),('19','SITUACIONES TRANSITORIAS DE FINANCIACIÓN',0),('190','Acciones o participaciones emitidas',0),('192','Suscriptores de acciones',0),('194','Capital social, sociedad en formación',0),('2','INMOVILIZADO',0),('20','INMOVILIZACIONES INTANGIBLES',0),('200','Gastos de investigación y desarrollo',0),('201','Concesiones administrativas',0),('202','Propiedad industrial',0),('203','Fondo de comercio',0),('204','Derechos de traspaso',0),('205','Aplicaciones informáticas',0),('209','Anticipos para inmovilizaciones intangibles',0),('21','INMOVILIZACIONES MATERIALES',0),('210','Terrenos y bienes naturales',0),('21000001','Terreno local comercial A',0),('211','Construcciones',0),('21100001','Construcción local comercial A',0),('212','Instalaciones técnicas',0),('213','Maquinaria',0),('214','Utillaje',0),('215','Otras instalaciones',0),('216','Mobiliario',0),('21600001','Mobiliario diverso',0),('217','Equipos para procesos de información',0),('21700001','Equipo proceso inforcación PC1',0),('21700002','Equipo proceso información PC2',0),('21700003','Equipo proceso información PC3',0),('218','Elementos de transporte',0),('219','Otro inmovilizado material',0),('22','INVERSIONES INMOBILIARIAS',0),('220','Terrenos y bienes naturales',0),('221','Construcciones',0),('23','INMOVILIZACIONES MATERIALES EN CURSO',0),('230','Adaptación de terrenos y bienes naturales',0),('231','Construcciones en curso',0),('232','Instalaciones técnicas en montaje',0),('233','Maquinaria en montaje',0),('237','Equipos para procesos de información en montaje',0),('239','Anticipos para inmovilizaciones materiales',0),('24','INVERSIONES FINANCIERAS EN PARTES VINCULADAS',0),('240','Participaciones a largo plazo en partes vinculadas',0),('2403','Participaciones a largo plazo en empresas del grupo',0),('2404','Participaciones a largo plazo en empresas asociadas',0),('2405','Participaciones a largo plazo en otras partes vinculadas',0),('241','Valores representativos de deuda a largo plazo de partes vinculadas',0),('2413','Valores representativos de deuda a largo plazo de empresas del grupo',0),('2414','Valores representativos de deuda a largo plazo de empresas asociadas',0),('2415','Valores representativos de deuda a largo plazo de otras partes vinculadas',0),('242','Créditos a largo plazo a partes vinculadas',0),('2423','Créditos a largo plazo a empresas del grupo',0),('2424','Créditos a largo plazo a empresas asociadas',0),('2425','Créditos a largo plazo a otras partes vinculadas',0),('243','Intereses a largo plazo de inversiones financieras en partes vinculadas',0),('2433','Intereses a largo plazo de inversiones financieras en empresas del grupo',0),('2434','Intereses a largo plazo de inversiones financieras en empresas asociadas',0),('2435','Intereses a largo plazo de inversiones financieras en otras partes vinculadas',0),('248','Desembolsos pendientes sobre participaciones a largo plazo en partes vinculadas',0),('2483','Desembolsos pendientes sobre participaciones a largo plazo en empresas del grupo.',0),('2484','Desembolsos pendientes sobre participaciones a largo plazo en empresas asociadas.',0),('2485','Desembolsos pendientes sobre participaciones a largo plazo en otras partes vinculadas',0),('25','OTRAS INVERSIONES FINANCIERAS A LARGO PLAZO',0),('250','Inversiones financieras a largo plazo en instrumentos de patrimonio',0),('251','Valores representativos de deuda a largo plazo',0),('252','Créditos a largo plazo',0),('253','Créditos a largo plazo por enajenación de inmovilizado',0),('254','Créditos a largo plazo al personal',0),('255','Activos por derivados financieros a largo plazo',0),('256','Intereses a largo plazo de valores representativos de deuda',0),('257','Intereses a largo plazo de créditos',0),('258','Imposiciones a largo plazo',0),('259','Desembolsos pendientes sobre instrumentos de patrimonio',0),('26','FIANZAS Y DEPÓSITOS CONSTITUIDOS A LARGO PLAZO',0),('260','Fianzas constituidas a largo plazo',0),('265','Depósitos constituidos a largo plazo',0),('28','AMORTIZACIÓN ACUMULADA DEL INMOVILIZADO',0),('280','Amortización acumulada del inmovilizado intangible',0),('2800','Amortización acumulada de gastos de investigación y desarrollo',0),('2801','Amortización acumulada de concesiones administrativas',0),('2802','Amortización acumulada de propiedad industrial',0),('2804','Amortización acumulada de derechos de traspaso',0),('2805','Amortización acumulada de aplicaciones informáticas',0),('281','Amortización acumulada del inmovilizado material',0),('2811','Amortización acumulada de construcciones',0),('28110001','Amort. acumulada construcción local A',0),('2812','Amortización acumulada de instalaciones técnicas',0),('2813','Amortización acumulada de maquinaria',0),('2814','Amortización acumulada de utillaje',0),('2815','Amortización acumulada de otras instalaciones',0),('2816','Amortización acumulada de mobiliario',0),('28160001','Amort. acumulada mobiliario diverso',0),('2817','Amortización acumulada de equipos para procesos de información',0),('28170001','Amortización eq. proc. información PC1',0),('28170002','Amortización equipo proc. información PC2',0),('28170003','Amortización ac. eq.proc. información PC3',0),('2818','Amortización acumulada de elementos de transporte',0),('2819','Amortización acumulada de otro inmovilizado material',0),('282','Amortización acumulada de las inversiones inmobiliarias',0),('29','DETERIORO DE VALOR DEL INMOVILIZADO',0),('290','Deterioro de valor del inmovilizado intangible',0),('2901','Deterioro de valor de concesiones administrativas',0),('2902','Deterioro de valor de propiedad industrial',0),('2903','Deterioro de valor del fondo de comercio',0),('2904','Deterioro de valor de derechos de traspaso',0),('2905','Deterioro de valor de aplicaciones informáticas',0),('291','Deterioro de valor del inmovilizado material',0),('2910','Deterioro de valor de gastos de investigación y desarrollo',0),('2910','Deterioro de valor de terrenos y bienes naturales',0),('2911','Deterioro de valor de construcciones',0),('2912','Deterioro de valor de instalaciones técnicas',0),('2913','Deterioro de valor de maquinaria',0),('2914','Deterioro de valor de utillaje',0),('2915','Deterioro de valor de otras instalaciones',0),('2916','Deterioro de valor de mobiliario',0),('2917','Deterioro de valor de equipos para procesos de información',0),('2918','Deterioro de valor de elementos de transporte',0),('2919','Deterioro de valor de otro inmovilizado material',0),('292','Deterioro de valor de las inversiones inmobiliarias',0),('2920','Deterioro de valor de los terrenos y bienes naturales',0),('2921','Deterioro de valor de construcciones',0),('293','Deterioro de valor de participaciones a largo plazo en partes vinculadas',0),('2933','Deterioro de valor de participaciones a largo plazo en empresas del grupo',0),('2934','Deterioro de valor de participaciones a largo plazo en empresas asociadas',0),('2935','Deterioro de valor de participaciones a largo plazo en otras partes vinculadas',0),('294','Deterioro de valores representativos de deuda a largo plazo de partes vinculadas',0),('2943','Deterioro de valores representativos de deuda a largo plazode empresas del grupo',0),('2944','Deterioro de valores representativos de deuda a largo plazo de empresas asociadas',0),('2945','Deterioro de valores representativos de deuda a largo plazo de otras partes vinculadas',0),('295','Deterioro de valor de créditos a largo plazo a partes vinculadas',0),('2953','Deterioro de valor de créditos a largo plazo a empresas del grupo',0),('2954','Deterioro de valor de créditos a largo plazo a empresas asociadas',0),('2955','Deterioro de valor de créditos a largo plazo a otras partes vinculadas',0),('296','Deterioro de valor de participaciones en el patrimonio neto a largo plazo',0),('297','Deterioro de valor de valores representativos de deuda a largo plazo',0),('298','Deterioro de valor de créditos a largo plazo',0),('3','EXISTENCIAS',0),('30','COMERCIALES',0),('300','Mercaderías A',0),('30000000','Existencias comerciales',0),('301','Mercaderías B',0),('31','MATERIAS PRIMAS',0),('310','Materias primas A',0),('311','Materias primas B',0),('32','OTROS APROVISIONAMIENTOS',0),('320','Elementos y conjuntos incorporables',0),('321','Combustibles',0),('322','Repuestos',0),('325','Materiales diversos',0),('326','Embalajes',0),('327','Envases',0),('328','Material de oficina',0),('33','PRODUCTOS EN CURSO',0),('330','Productos en curso A',0),('331','Productos en curso B',0),('34','PRODUCTOS SEMITERMINADOS',0),('340','Productos semiterminados A',0),('341','Productos semiterminados B',0),('35','PRODUCTOS TERMINADOS',0),('350','Productos terminados A',0),('351','Productos terminados B',0),('36','SUBPRODUCTOS, RESIDUOS Y MATERIALES RECUPERADOS',0),('360','Subproductos A',0),('361','Subproductos B',0),('365','Residuos A',0),('366','Residuos B',0),('368','Materiales recuperados A',0),('369','Materiales recuperados B',0),('39','DETERIORO DE VALOR DE LAS EXISTENCIAS',0),('390','Deterioro de valor de las mercaderías',0),('391','Deterioro de valor de las materias primas',0),('392','Deterioro de valor de otros aprovisionamientos',0),('393','Deterioro de valor de los productos en curso',0),('394','Deterioro de valor de los productos semiterminados',0),('395','Deterioro de valor de los productos terminados',0),('396','Deterioro de valor de los subproductos, residuos y materiales recuperados',0),('4','ACREEDORES Y DEUDORES POR OPERACIONES COMERCIALES',0),('40','PROVEEDORES',0),('400','Proveedores',0),('4000','Proveedores (euros)',0),('40000001','Proveedor A',0),('40000002','Proveedor B',0),('4004','Proveedores (moneda extranjera)',0),('4009','Proveedores, facturas pendientes de recibir o de formalizar',0),('401','Proveedores, efectos comerciales a pagar',0),('403','Proveedores, empresas del grupo',0),('4030','Proveedores, empresas del grupo (euros)',0),('4031','Efectos comerciales a pagar, empresas del grupo',0),('4034','Proveedores, empresas del grupo (moneda extranjera)',0),('4036','Envases y embalajes a devolver a proveedores, empresas del grupo',0),('4039','Proveedores, empresas del grupo, facturas pendientes de recibir o de formalizar',0),('404','Proveedores, empresas asociadas',0),('405','Proveedores, otras partes vinculadas',0),('406','Envases y embalajes a devolver a proveedores',0),('407','Anticipos a proveedores',0),('41','ACREEDORES VARIOS',0),('410','Acreedores por prestaciones de servicios',0),('4100','Acreedores por prestaciones de servicios (euros)',0),('4104','Acreedores por prestaciones de servicios, (moneda extranjera)',0),('4109','Acreedores por prestaciones de servicios, facturas pendientes de recibir o de formalizar',0),('411','Acreedores, efectos comerciales a pagar',0),('419','Acreedores por operaciones en común',0),('43','CLIENTES',0),('430','Clientes',0),('4300','Clientes (euros)',0),('43000001','Cliente A',0),('43000002','Cliente B',0),('4304','Clientes, (moneda extranjera)',0),('4309','Clientes, facturas pendientes de formalizar',0),('431','Clientes, efectos comerciales a cobrar',0),('4310','Efectos comerciales en cartera',0),('4311','Efectos comerciales descontados',0),('4312','Efectos comerciales en gestión de cobro',0),('4315','Efectos comerciales impagados',0),('433','Clientes, empresas del grupo',0),('4330','Clientes empresas del grupo (euros)',0),('4331','Efectos comerciales a cobrar, empresas del grupo',0),('4334','Clientes empresas del grupo, (moneda extranjera)',0),('4336','Clientes empresas del grupo de dudoso cobro',0),('4337','Envases y embalajes a devolver a clientes, empresas del grupo',0),('4339','Clientes empresas del grupo, facturas pendientes de formalizar',0),('434','Clientes, empresas asociadas',0),('435','Clientes, otras partes vinculadas',0),('436','Clientes de dudoso cobro',0),('437','Envases y embalajes a devolver por clientes',0),('438','Anticipos de clientes',0),('44','DEUDORES VARIOS',0),('440','Deudores',0),('4400','Deudores (euros)',0),('4404','Deudores (moneda extranjera)',0),('4409','Deudores, facturas pendientes de formalizar',0),('441','Deudores, efectos comerciales a cobrar',0),('4410','Deudores, efectos comerciales en cartera',0),('4411','Deudores, efectos comerciales descontados',0),('4412','Deudores, efectos comerciales en gestión de cobro',0),('4415','Deudores, efectos comerciales impagados',0),('445','Deudores de dudoso cobro',0),('449','Deudores por operaciones en común',0),('46','PERSONAL',0),('460','Anticipos de remuneraciones',0),('465','Remuneraciones pendientes de pago',0),('47','ADMINISTRACIONES PÚBLICAS',0),('470','Hacienda Pública, deudora por diversos conceptos',0),('4700','Hacienda Pública, deudora por IVA',0),('47000000','Hacienda pública, deudora por IVA',0),('4708','Hacienda Pública, deudora por subvenciones concedidas',0),('4709','Hacienda Pública, deudora por devolución de impuestos',0),('471','Organismos de la Seguridad Social, deudores',0),('472','Hacienda Pública, IVA soportado',0),('47200000','H.P. Iva soportado',0),('473','Hacienda Pública, retenciones y pagos a cuenta',0),('47300001','Pagos a cuenta Impuesto Sociedades',0),('474','Activos por impuesto diferido',0),('4740','Diferencias temporarias deducibles',0),('4742','Derechos por deducciones y bonificaciones pendientes de aplicar',0),('4745','Crédito por pérdidas a compensar del ejercicio',0),('475','Hacienda Pública, acreedora por conceptos fiscales',0),('4750','Hacienda Pública, acreedora por IVA',0),('47500000','H.P. acreedora por IVA',0),('4751','Hacienda Pública, acreedora por retenciones practicadas',0),('4752','Hacienda Pública, acreedora por impuesto sobre sociedades',0),('47520000','H.P. acreedor por IS',0),('4758','Hacienda Pública, acreedora por subvenciones a reintegrar',0),('476','Organismos de la Seguridad Social, acreedores',0),('477','Hacienda Pública, IVA repercutido',0),('47700000','H.P. IVA repercutido',0),('479','Diferencias temporarias imponibles',0),('47900001','Diferencias temporarias imponibles',0),('48','AJUSTES POR PERIODIFICACIÓN',0),('480','Gastos anticipados',0),('485','Ingresos anticipados',0),('49','DETERIORO DE VALOR DE CRÉDITOS COMERCIALES Y PROVISIONES A CORTO PLAZO',0),('490','Deterioro de valor de créditos por operaciones comerciales',0),('493','Deterioro de valor de créditos por operaciones comerciales con partes vinculadas',0),('4933','Deterioro de valor de créditos por operaciones comerciales con empresas del grupo',0),('4934','Deterioro de valor de créditos por operaciones comerciales con empresas asociadas',0),('4935','Deterioro de valor de créditos por operaciones comerciales con otras partes vinculadas',0),('499','Provisión para operaciones comerciales',0),('4994','Provisión por contratos onerosos',0),('4999','Provisión para otras operaciones comerciales',0),('5','CUENTAS FINANCIERAS',0),('50','EMPRÉSTITOS, DEUDAS CON CARÁCTERÍSTICAS ESPECIALES Y OTRAS EMISIONES ANÁLOGAS A CORTO PLAZO',0),('500','Obligaciones y bonos a corto plazo',0),('502','Acciones o participaciones a corto plazo contabilizadas como pasivo',0),('505','Deudas representadas en otros valores negociables a corto plazo',0),('506','Intereses de empréstitos y otras emisiones análogas',0),('507','Dividendos de emisiones contabilizadas como pasivo',0),('509','Valores negociables amortizados',0),('5090','Obligaciones y bonos amortizados',0),('5095','Otros valores negociables amortizados',0),('51','DEUDAS A CORTO PLAZO CON PARTES VINCULADAS',0),('510','Deudas a corto plazo con entidades de crédito vinculadas',0),('5103','Deudas a corto plazo con entidades de crédito, empresas del grupo',0),('5104','Deudas a corto plazo con entidades de crédito, empresas asociadas',0),('5105','Deudas a corto plazo con otras entidades de crédito vinculadas',0),('511','Proveedores de inmovilizado a corto plazo, partes vinculadas',0),('5113','Proveedores de inmovilizado a corto plazo, empresas del grupo',0),('5114','Proveedores de inmovilizado a corto plazo, empresas asociadas',0),('5115','Proveedores de inmovilizado a corto plazo, otras partes vinculadas',0),('512','Otras deudas a corto plazo con partes vinculadas',0),('5123','Otras deudas a corto plazo con empresas del grupo',0),('5124','Otras deudas a corto plazo con empresas asociadas',0),('5125','Otras deudas a corto plazo con otras partes vinculadas',0),('513','Intereses a corto plazo de deudas con partes vinculadas',0),('5133','Intereses a corto plazo de deudas, empresas del grupo',0),('5134','Intereses a corto plazo de deudas, empresas asociadas',0),('5135','Intereses a corto plazo de deudas, otras partes vinculadas',0),('52','DEUDAS A CORTO PLAZO POR PRÉSTAMOS RECIBIDOS Y OTROS CONCEPTOS',0),('520','Deudas a corto plazo con entidades de crédito',0),('5200','Préstamos a corto plazo de entidades de crédito',0),('5201','Deudas a corto plazo por crédito dispuesto',0),('5208','Deudas por efectos descontados',0),('521','Deudas a corto plazo',0),('522','Deudas a corto plazo transformables en subvenciones, donaciones y legados',0),('523','Proveedores de inmovilizado a corto plazo',0),('52300001','Proveedor de inmovilizado a CP',0),('524','Efectos a pagar a corto plazo',0),('525','Dividendo activo a pagar',0),('526','Intereses a corto plazo de deudas con entidades de crédito',0),('527','Intereses a corto plazo de deudas',0),('529','Provisiones a corto plazo',0),('5291','Provisión para impuestos',0),('5292','Provisiones para otras responsabilidades',0),('5293','Provisiones por desmantelamiento, retiro o rehabilitación del inmovilizado',0),('5295','Provisiones para actuaciones medioambientales',0),('53','INVERSIONES FINANCIERAS A CORTO PLAZO EN PARTES VINCULADAS',0),('530','Participaciones a corto plazo en partes vinculadas',0),('5303','Participaciones a corto plazo, en empresas del grupo',0),('5304','Participaciones a corto plazo, en empresas asociadas',0),('5305','Participaciones a corto plazo, en otras partes vinculadas',0),('531','Valores representativos de deuda a corto plazo de partes vinculadas',0),('5313','Valores representativos de deuda a corto plazo de empresas del grupo',0),('5314','Valores representativos de deuda a corto plazo de empresas asociadas',0),('5315','Valores representativos de deuda a corto plazo de otras partes vinculadas',0),('532','Créditos a corto plazo a partes vinculadas',0),('5323','Créditos a corto plazo a empresas del grupo',0),('5324','Créditos a corto plazo a empresas asociadas',0),('5325','Créditos a corto plazo a otras partes vinculadas',0),('533','Intereses a corto plazo de inversiones financieras en partes vinculadas',0),('5333','Intereses a corto plazo de inversiones financieras en empresas del grupo',0),('5334','Intereses a corto plazo de inversiones financieras en empresas asociadas',0),('5335','Intereses a corto plazo de inversiones financieras en otras partes vinculadas',0),('538','Desembolsos pendientes sobre participaciones a corto plazo de partes vinculadas',0),('5383','Desembolsos pendientes sobre participaciones a largo plazo en empresas del grupo.',0),('5384','Desembolsos pendientes sobre participaciones a largo plazo en empresas asociadas.',0),('5385','Desembolsos pendientes sobre participaciones a largo plazo en otras partes vinculadas',0),('54','OTRAS INVERSIONES FINANCIERAS TEMPORALES',0),('540','Inversiones financieras temporales en instrumentos de patrimonio',0),('541','Valores representativos de deuda a corto plazo',0),('542','Créditos a corto plazo',0),('543','Créditos a corto plazo por enajenación de inmovilizado',0),('544','Créditos a corto plazo al personal',0),('545','Dividendo a cobrar',0),('546','Intereses a corto plazo de inversiones financieras',0),('548','Imposiciones a corto plazo',0),('549','Desembolsos pendientes sobre participaciones en el patrimonio neto a corto plazo',0),('55','OTRAS CUENTAS NO BANCARIAS',0),('550','Titular de la explotación',0),('551','Cuenta corriente con socios y administradores',0),('552','Cuenta corriente con otras personas y entidades vinculadas',0),('5523','Cuenta corriente con empresas del grupo',0),('5524','Cuenta corriente con empresas asociadas',0),('5525','Cuenta corriente con otras partes vinculadas',0),('554','Cuenta corriente con uniones temporales de empresas y comunidades de bienes',0),('555','Partidas pendientes de aplicación',0),('556','Desembolsos exigidos sobre participaciones en el patrimonio neto',0),('5563','Desembolsos exigidos sobre participaciones, empresas del grupo',0),('5564','Desembolsos exigidos sobre participaciones, empresas asociadas',0),('5565','Desembolsos exigidos sobre participaciones, otras partes vinculadas',0),('5566','Desembolsos exigidos sobre participaciones de otras empresas',0),('557','Dividendo activo a cuenta',0),('558','Socios por desembolsos exigidos',0),('559','Derivados financieros a corto plazo',0),('5590','Activos por derivados financieros a corto plazo',0),('5591','Pasivos por derivados financieros a corto plazo',0),('56','FIANZAS Y DEPÓSITOS RECIBIDOS Y CONSTITUIDOS A CORTO PLAZO, Y AJUSTES POR PERIODIFICACIÓN',0),('560','Fianzas recibidas a corto plazo',0),('561','Depósitos recibidos a corto plazo',0),('565','Fianzas constituidas a corto plazo',0),('566','Depósitos constituidos a corto plazo',0),('567','Intereses pagados por anticipado',0),('568','Intereses cobrados por anticipado',0),('569','Garantías financieras a corto plazo',0),('57','TESORERÍA',0),('570','Caja, euros',0),('57000000','Caja, euros',0),('571','Caja, moneda extranjera',0),('572','Bancos e instituciones de crédito c/c vista, euros',0),('573','Bancos e instituciones de crédito c/c vista, moneda extranjera',0),('574','Bancos e instituciones de crédito, cuentas de ahorro, euros',0),('575','Bancos e instituciones de crédito, cuentas de ahorro, moneda extranjera',0),('59','DETERIORO DEL VALOR DE INSTRUMENTOS FINANCIEROS',0),('593','Deterioro de valor de participaciones a corto plazo en partes vinculadas',0),('5933','Deterioro de valor de participaciones a corto plazo en empresas del grupo',0),('5934','Deterioro de valor de participaciones a corto plazo en empresas asociadas',0),('5935','Deterioro de valor de participaciones a corto en otras partes vinculadas',0),('594','Deterioro de valores representativos de deuda a corto de partes vinculadas',0),('5943','Deterioro de valores representativos de deuda a corto plazo de empresas del grupo',0),('5944','Deterioro de valores representativos de deuda a corto plazo de empresas asociadas',0),('5945','Deterioro de valores representativos de deuda a corto plazo de otras partes vinculadas',0),('595','Deterioro de valor de créditos a corto plazo a partes vinculadas',0),('5953','Deterioro de valor de créditos a corto plazo a empresas del grupo',0),('5954','Deterioro de valor de créditos a corto plazo a empresas asociadas',0),('5955','Deterioro de valor de créditos a corto plazo a otras partes vinculadas',0),('596','Deterioro de valor de participaciones a corto plazo',0),('597','Deterioro de valor de valores representativos de deuda a corto plazo',0),('598','Deterioro de valor de créditos a corto plazo',0),('6','COMPRAS Y GASTOS',0),('60','COMPRAS',0),('600','Compras de mercaderías',0),('60000000','Compras de mercaderías',0),('601','Compras de materias primas',0),('602','Compras de otros aprovisionamientos',0),('606','Descuentos sobre ventas por pronto pago',0),('6060','Descuentos sobre compras por pronto pago de mercaderías',0),('6061','Descuentos sobre compras por pronto pago de materias primas',0),('6062','Descuentos sobre compras por pronto pago de otros aprovisionamientos',0),('607','Trabajos realizados por otras empresas',0),('608','Devoluciones de compras y operaciones similares',0),('6080','Devoluciones de compras de mercaderias',0),('6081','Devoluciones de compras de materias primas',0),('6082','Devoluciones de compras de otros aprovisionamientos',0),('609','\"Rappels\" por compras',0),('6090','\"Rappels\" por compras de mercaderias',0),('6091','\"Rappels\" por compras de materias primas',0),('6092','\"Rappels\" por compras de otros aprovisionamientos',0),('61','VARIACIÓN DE EXISTENCIAS',0),('610','Variación de existencias de mercaderías',0),('61000001','Variación existencias mercaderías',0),('611','Variación de existencias de materias primas',0),('612','Variación de existencias de otros aprovisionamientos',0),('62','SERVICIOS EXTERIORES',0),('620','Gastos en investigación y desarrollo del ejercicio',0),('621','Arrendamientos y cánones',0),('622','Reparaciones y conservación',0),('623','Servicios de profesionales independientes',0),('624','Transportes',0),('625','Primas de seguros',0),('626','Servicios bancarios y similares',0),('627','Publicidad, propaganda y relaciones públicas',0),('628','Suministros',0),('629','Otros servicios',0),('63','TRIBUTOS',0),('630','Impuesto sobre beneficios',0),('6300','Impuesto corriente',0),('63000000','Impuesto corriente',0),('6301','Impuesto diferido',0),('63010001','Impuesto diferido',0),('631','Otros tributos',0),('633','Ajustes negativos en la imposición sobre beneficios',0),('634','Ajustes negativos en la imposición indirecta',0),('6341','Ajustes negativos en IVA de activo corriente',0),('6342','Ajustes negativos en IVA de inversiones',0),('636','Devolución de impuestos',0),('638','Ajustes positivos en la imposición sobre beneficios',0),('639','Ajustes positivos en la imposición indirecta',0),('6391','Ajustes positivos en IVA de activo corriente',0),('6392','Ajustes positivos en IVA de inversiones',0),('64','GASTOS DE PERSONAL',0),('640','Sueldos y salarios',0),('641','Indemnizaciones',0),('642','Seguridad Social a cargo de la empresa',0),('649','Otros gastos sociales',0),('65','OTROS GASTOS DE GESTIÓN',0),('650','Pérdidas de créditos comerciales incobrables',0),('651','Resultados de operaciones en común',0),('6510','Beneficio transferido (gestor)',0),('6511','Pérdida soportada (partícipe o asociado no gestor)',0),('659','Otras pérdidas en gestión corriente',0),('66','GASTOS FINANCIEROS',0),('661','Intereses de obligaciones y bonos',0),('6610','Intereses de obligaciones y bonos a largo plazo, empresas del grupo',0),('6611','Intereses de obligaciones y bonos a largo plazo, empresas asociadas',0),('6612','Intereses de obligaciones y bonos a largo plazo, otras partes vinculadas',0),('6613','Intereses de obligaciones y bonos a largo plazo, otras empresas',0),('6615','Intereses de obligaciones y bonos a corto plazo, empresas del grupo',0),('6616','Intereses de obligaciones y bonos a corto plazo, empresas asociadas',0),('6617','Intereses de obligaciones y bonos a corto plazo, otras partes vinculadas',0),('6618','Intereses de obligaciones y bonos a corto plazo, otras empresas',0),('662','Intereses de deudas',0),('6620','Intereses de deudas, empresas del grupo',0),('6621','Intereses de deudas, empresas asociadas',0),('6622','Intereses de deudas, otras partes vinculadas',0),('6623','Intereses de deudas con entidades de crédito',0),('6624','Intereses de deudas, otras empresas',0),('663','Pérdidas por valoración de instrumentos financieros por su valor razonable',0),('664','Dividendos de acciones o participaciones contabilizadas como pasivo',0),('6640','Dividendos de pasivos, empresas del grupo',0),('6641','Dividendos de pasivos, empresas asociadas',0),('6642','Dividendos de pasivos, otras partes vinculadas',0),('6643','Dividendos de pasivos, otras empresas',0),('665','Intereses por descuento de efectos',0),('6650','Intereses por descuento de efectos en entidades de crédito del grupo',0),('6651','Intereses por descuento de efectos en entidades de crédito asociadas',0),('6652','Intereses por descuento de efectos en otras entidades de crédito vinculadas',0),('6653','Intereses por descuento de efectos en otras entidades de crédito',0),('666','Pérdidas en participaciones y valores representativos de deuda',0),('6660','Pérdidas en participaciones y valores representativos de deuda a largo plazo, empresas del grupo',0),('6661','Pérdidas en participaciones y valores representativos de deuda a largo plazo, empresas asociadas',0),('6662','Pérdidas en participaciones y valores representativos de deuda a largo plazo, otras partes vinculadas',0),('6663','Pérdidas en participaciones y valores representativos de deuda a largo plazo, otras empresas',0),('6665','Pérdidas en participaciones y valores representativos de deuda a corto plazo, empresas del grupo',0),('6666','Pérdidas en participaciones y valores representativos de deuda a corto plazo, empresas asociadas',0),('6667','Pérdidas en participaciones y valores representativos de deuda a corto plazo, otras partes vinculadas',0),('6668','Pérdidas en participaciones y valores representativos de deuda a corto plazo, de otras empresas',0),('667','Pérdidas de créditos no comerciales',0),('6670','Pérdidas de créditos a largo plazo, empresas del grupo',0),('6671','Pérdidas de créditos a largo plazo, empresas asociadas',0),('6672','Pérdidas de créditos a largo plazo, otras partes vinculadas',0),('6673','Pérdidas de créditos a largo plazo, otras empresas',0),('6675','Pérdidas de créditos a corto plazo, empresas del grupo',0),('6676','Pérdidas de créditos a corto plazo, empresas asociadas',0),('6677','Pérdidas de créditos a corto plazo, otras partes vinculadas',0),('6678','Pérdidas de créditos a corto plazo, de otras empresas',0),('668','Diferencias negativas de cambio',0),('669','Otros gastos financieros',0),('67','PÉRDIDAS PROCEDENTES DE ACTIVOS NO CORRIENTES Y GASTOS EXCEPCIONALES',0),('670','Pérdidas procedentes del inmovilizado intangible',0),('671','Pérdidas procedentes del inmovilizado material',0),('672','Pérdidas procedentes de las inversiones inmobiliarias',0),('673','Pérdidas procedentes de participaciones a largo plazo en partes vinculadas',0),('6733','Pérdidas procedentes de participaciones a largo plazo, empresas del grupo',0),('6734','Pérdidas procedentes de participaciones a largo plazo, empresas asociadas',0),('6735','Pérdidas procedentes de participaciones a largo plazo, otras partes vinculadas',0),('675','Pérdidas por operaciones con obligaciones propias',0),('678','Gastos excepcionales',0),('68','DOTACIONES PARA AMORTIZACIONES',0),('680','Amortización del inmovilizado intangible',0),('681','Amortización del inmovilizado material',0),('68100001','Amortización del inmovilizado material',0),('682','Amortización de las inversiones inmobiliarias',0),('69','PÉRDIDAS POR DETERIODO Y OTRAS DOTACIONES',0),('690','Pérdidas por deterioro del inmovilizado intangible',0),('691','Pérdidas por deterioro del inmovilizado material',0),('692','Pérdidas por deterioro de las inversiones inmobiliarias',0),('693','Pérdidas por deterioro de existencias',0),('6930','Pérdidas por deterioro de productos terminados y en curso de fabricación',0),('6931','Pérdidas por deterioro de mercaderías',0),('6932','Pérdidas por deterioro de materias primas',0),('6933','Pérdidas por deterioro de otros aprovisionamientos',0),('694','Pérdidas por deterioro de créditos comerciales',0),('695','Dotación a la provisión por operaciones comerciales',0),('6954','Contratos onerosos',0),('6959','Otras operaciones comerciales',0),('696','Pérdidas por deterioro de participaciones y valores representativos de deuda a largo plazo',0),('6960','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas del grupo',0),('6961','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas asociadas',0),('6962','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras partes vinculadas',0),('6963','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras empresas',0),('6965','Pérdidas en valores representativos de deuda a largo plazo, empresas del grupo',0),('6966','Pérdidas en valores representativos de deuda a largo plazo, empresas asociadas',0),('6967','Pérdidas en valores representativos de deuda a largo plazo, otras partes vinculadas',0),('6968','Pérdidas en valores representativos de deuda a largo plazo, de otras empresas',0),('697','Pérdidas por deterioro de créditos a largo plazo',0),('6970','Pérdidas por deterioro de créditos a largo plazo, empresas del grupo',0),('6971','Pérdidas por deterioro de créditos a largo plazo, empresas asociadas',0),('6972','Pérdidas por deterioro de créditos a largo plazo, otras partes vinculadas',0),('6973','Pérdidas por deterioro de créditos a largo plazo, otras empresas',0),('698','Pérdidas deterioro de participaciones y valores representativos de deuda a corto plazo',0),('6980','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas del grupo',0),('6981','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas asociadas',0),('6982','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, otras partes vinculadas',0),('6983','Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, otras empresas',0),('6985','Pérdidas por deterioro en valores representativos de deuda a corto plazo, empresas del grupo',0),('6986','Pérdidas por deterioro en valores representativos de deuda a corto plazo, empresas asociadas',0),('6987','Pérdidas por deterioro en valores representativos de deuda a corto plazo, otras partes vinculadas',0),('6988','Pérdidas por deterioro en valores representativos de deuda a corto plazo, de otras empresas',0),('699','Pérdidas por deterioro de créditos a corto plazo',0),('6990','Pérdidas por deterioro de créditos a largo plazo, empresas del grupo',0),('6991','Pérdidas por deterioro de créditos a largo plazo, empresas asociadas',0),('6992','Pérdidas por deterioro de créditos a largo plazo, otras partes vinculadas',0),('6993','Pérdidas por deterioro de créditos a largo plazo, otras empresas',0),('7','VENTAS E INGRESOS',0),('70','VENTAS DE MERCADERÍAS, DE PRODUCCIÓN PROPIA, DE SERVICIOS, ETC',0),('700','Ventas de mercaderías',0),('70000000','Ventas de mercaderías',0),('701','Ventas de productos terminados',0),('702','Ventas de productos semiterminados',0),('703','Ventas de subproductos y residuos',0),('704','Ventas de envases y embalajes',0),('705','Prestaciones de servicios',0),('706','Descuentos sobre compras por pronto pago',0),('7060','Descuentos sobre compras por pronto pago de mercaderias',0),('7061','Descuentos sobre compras por pronto pago de productos terminados',0),('7062','Descuentos sobre compras por pronto pago de productos semiterminados',0),('7063','Descuentos sobre ventas por pronto pago de subproductos y residuos',0),('7064','Descuentos sobre ventas por pronto pago de envases y embalajes',0),('708','Devoluciones de ventas y operaciones similares',0),('7080','Devoluciones de ventas de mercaderías',0),('7081','Devoluciones de ventas de productos terminados',0),('7082','Devoluciones de ventas de productos semiterminados',0),('7083','Devoluciones de ventas de subproductos y residuos',0),('7084','Devoluciones de ventas de envases y embalajes',0),('709','\"Rappels\" sobre ventas',0),('7090','\"Rappels\" sobre ventas de mercaderias',0),('7091','\"Rappels\" sobre ventas de productos terminados',0),('7092','\"Rappels\" sobre ventas de productos semiterminados',0),('7093','\"Rappels\" sobre ventas de subproductos y residuos',0),('7094','\"Rappels\" sobre ventas de envases y embalajes',0),('71','VARIACIÓN DE EXISTENCIAS',0),('710','Variación de existencias de productos en curso',0),('711','Variación de existencias de productos semiterminados',0),('712','Variación de existencias de productos terminados',0),('713','Variación de existencias de subproductos, residuos y materiales recuperados',0),('73','TRABAJOS REALIZADOS PARA LA EMPRESA',0),('730','Trabajos realizados para el inmovilizado intangible',0),('731','Trabajos realizados para el inmovilizado material',0),('732','Trabajos realizados en inversiones inmobiliarias',0),('733','Trabajos realizados para el inmovilizado material en curso',0),('74','SUBVENCIONES, DONACIONES Y LEGADOS',0),('740','Subvenciones, donaciones y legados a la explotación',0),('746','Subvenciones, donaciones y legados de capital transferidas al resultado del ejercicio',0),('747','Otras subvenciones, donaciones y legados transferidos al resultado del ejercicio',0),('75','OTROS INGRESOS DE GESTIÓN',0),('751','Resultados de operaciones en común',0),('7510','Pérdida transferida (gestor)',0),('7511','Beneficio atribuido (partícipe o asociado no gestor)',0),('752','Ingresos por arrendamientos',0),('753','Ingresos de propiedad industrial cedida en explotación',0),('754','Ingresos por comisiones',0),('755','Ingresos por servicios al personal',0),('759','Ingresos por servicios diversos',0),('76','INGRESOS FINANCIEROS',0),('760','Ingresos de participaciones en instrumentos de patrimonio',0),('7600','Ingresos de participaciones en instrumentos de patrimonio, empresas del grupo',0),('7601','Ingresos de participaciones en instrumentos de patrimonio, empresas asociadas',0),('7602','Ingresos de participaciones en instrumentos de patrimonio, otras partes vinculadas',0),('7603','Ingresos de participaciones en instrumentos de patrimonio, de otras empresas',0),('761','Ingresos de valores representativos de deuda',0),('7610','Ingresos de valores representativos de deuda, empresas del grupo',0),('7611','Ingresos de valores representativos de deuda, empresas asociadas',0),('7612','Ingresos de valores representativos de deuda, otras partes vinculadas',0),('7613','Ingresos de valores representativos de deuda, otras empresas',0),('762','Ingresos de créditos',0),('7620','Ingresos de créditos a largo plazo',0),('76200','Ingresos de créditos a largo plazo, empresas del grupo',0),('76201','Ingresos de créditos a largo plazo, empresas asociadas',0),('76202','Ingresos de créditos a largo plazo, otras partes vinculadas',0),('76203','Ingresos de créditos a largo plazo, otras empresas',0),('7621','Ingresos de créditos a corto plazo',0),('76210','Ingresos de créditos a corto plazo, empresas del grupo',0),('76211','Ingresos de créditos a corto plazo, empresas asociadas',0),('76212','Ingresos de créditos a corto plazo, otras partes vinculadas',0),('76213','Ingresos de créditos a corto plazo, otras empresas',0),('763','Beneficios por la valoración de instrumentos financieros por su valor razonable',0),('766','Beneficios en valores negociables',0),('7660','Beneficios en valores negociables a largo plazo, empresas del grupo',0),('7661','Beneficios en valores negociables a largo plazo, empresas asociadas',0),('7662','Beneficios en valores negociables a largo plazo, otras partes vinculadas',0),('7663','Beneficios en valores negociables a largo plazo, otras empresas',0),('7665','Beneficios en valores negociables a corto plazo, empresas del grupo',0),('7666','Beneficios en valores negociables a corto plazo, empresas asociadas',0),('7667','Beneficios en valores negociables a corto plazo, otras partes vinculadas',0),('7668','Beneficios en valores negociables a corto plazo, de otras empresas',0),('768','Diferencias positivas de cambio',0),('769','Otros ingresos financieros',0),('77','BENEFICIOS PROCEDENTES DE ACTIVOS NO CORRIENTES E INGRESOS EXCEPCIONALES',0),('770','Beneficios procedentes del inmovilizado intangible',0),('771','Beneficios procedentes del inmovilizado material',0),('772','Beneficios procedentes de las inversiones inmobiliarias',0),('773','Beneficios procedentes de participaciones a largo plazo en partes vinculadas',0),('7733','Beneficios procedentes de participaciones a largo plazo, empresas del grupo',0),('7734','Beneficios procedentes de participaciones a largo plazo, empresas asociadas',0),('7735','Beneficios procedentes de participaciones a largo plazo, otras partes vinculadas',0),('775','Beneficios por operaciones con obligaciones propias',0),('778','Ingresos excepcionales.',0),('79','EXCESOS Y APLICACIONES DE PROVISIONES Y DE PÉRDIDAS POR DETERIORO',0),('790','Reversión del deterioro del inmovilizado intangible',0),('791','Reversión del deterioro del inmovilizado material',0),('792','Reversión del deterioro de las inversiones inmobiliarias',0),('793','Reversión del deterioro de existencias',0),('7930','Reversión del deterioro de productos terminados y en curso de fabricación',0),('7931','Reversión del deterioro de mercaderias',0),('7932','Reversión del deterioro de materias primas',0),('7933','Reversión del deterioro de otros aprovisionamientos',0),('794','Reversión del deterioro de créditos comerciales',0),('795','Exceso de provisiones',0),('7951','Exceso de provisión para impuestos',0),('7952','Exceso de provisión para otras responsabilidades',0),('7954','Exceso de provisión pora operaciones comerciales',0),('79544','Contratos onerosos',0),('79549','Otras operaciones comerciales',0),('7955','Exceso de provisión para actuaciones medioambientales',0),('796','Reversión del deterioro de participaciones y valores representativos de deuda a largo plazo',0),('7960','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas del grupo',0),('7961','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas asociadas',0),('7962','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras partes vinculadas',0),('7963','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras empresas',0),('7965','Reversión del deterioro de valores representativos de deuda a largo plazo, empresas del grupo',0),('7966','Reversión del deterioro de valores representativos de deuda a largo plazo, empresas asociadas',0),('7967','Reversión del deterioro de valores representativos de deuda a largo plazo, otras partes vinculadas',0),('7968','Reversión del deterioro de valores representativos de deuda a largo plazo, de otras empresas',0),('797','Reversión del deterioro de créditos a largo plazo',0),('7970','Reversión del deterioro de créditos a largo plazo, empresas del grupo',0),('7971','Reversión del deterioro de créditos a largo plazo, empresas asociadas',0),('7972','Reversión del deterioro de créditos a largo plazo, otras partes vinculadas',0),('7973','Reversión del deterioro de créditos a largo plazo, otras empresas',0),('798','Reversión del deterioro de participaciones y valores representativos de deuda a corto plazo',0),('7980','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas del grupo',0),('7981','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas asociadas',0),('7982','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, otras partes vinculadas',0),('7983','Reversión del deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, otras empresas',0),('7985','Reversión del deterioro en valores representativos de deuda a corto plazo, empresas del grupo',0),('7986','Reversión del deterioro en valores representativos de deuda a corto plazo, empresas asociadas',0),('7987','Reversión del deterioro en valores representativos de deuda a corto plazo, otras partes vinculadas',0),('7988','Reversión del deterioro en valores representativos de deuda a corto plazo, de otras empresas',0),('799','Reversión del deterioro de créditos a corto plazo',0),('7990','Reversión del deterioro de créditos a largo plazo, empresas del grupo',0),('7991','Reversión del deterioro de créditos a largo plazo, empresas asociadas',0),('7992','Reversión del deterioro de créditos a largo plazo, otras partes vinculadas',0),('7993','Reversión del deterioro de créditos a largo plazo, otras empresas',0);
/*!40000 ALTER TABLE `plancontable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `presupuesto`
--

DROP TABLE IF EXISTS `presupuesto`;
CREATE TABLE `presupuesto` (
  `ejercicio` varchar(40) NOT NULL default '',
  `cuenta` varchar(40) NOT NULL default '',
  `ejerciciobase` varchar(40) default '',
  `presupuestobase` varchar(40) default '',
  `base` decimal(14,2) default '0.00',
  `base1` decimal(14,2) default '0.00',
  `base2` decimal(14,2) default '0.00',
  `base3` decimal(14,2) default '0.00',
  `base4` decimal(14,2) default '0.00',
  `base5` decimal(14,2) default '0.00',
  `base6` decimal(14,2) default '0.00',
  `base7` decimal(14,2) default '0.00',
  `base8` decimal(14,2) default '0.00',
  `base9` decimal(14,2) default '0.00',
  `base10` decimal(14,2) default '0.00',
  `base11` decimal(14,2) default '0.00',
  `base12` decimal(14,2) default '0.00',
  `base13` decimal(14,2) default '0.00',
  `base14` decimal(14,2) default '0.00',
  `base15` decimal(14,2) default '0.00',
  `presupuesto` decimal(14,2) default '0.00',
  `presupuesto1` decimal(14,2) default '0.00',
  `presupuesto2` decimal(14,2) default '0.00',
  `presupuesto3` decimal(14,2) default '0.00',
  `presupuesto4` decimal(14,2) default '0.00',
  `presupuesto5` decimal(14,2) default '0.00',
  `presupuesto6` decimal(14,2) default '0.00',
  `presupuesto7` decimal(14,2) default '0.00',
  `presupuesto8` decimal(14,2) default '0.00',
  `presupuesto9` decimal(14,2) default '0.00',
  `presupuesto10` decimal(14,2) default '0.00',
  `presupuesto11` decimal(14,2) default '0.00',
  `presupuesto12` decimal(14,2) default '0.00',
  `presupuesto13` decimal(14,2) default '0.00',
  `presupuesto14` decimal(14,2) default '0.00',
  `presupuesto15` decimal(14,2) default '0.00',
  PRIMARY KEY  (`ejercicio`,`cuenta`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `presupuesto`
--

LOCK TABLES `presupuesto` WRITE;
/*!40000 ALTER TABLE `presupuesto` DISABLE KEYS */;
/*!40000 ALTER TABLE `presupuesto` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `saldossubcuenta`
--

DROP TABLE IF EXISTS `saldossubcuenta`;
CREATE TABLE `saldossubcuenta` (
  `codigo` varchar(40) NOT NULL default '',
  `saldo` decimal(14,2) default NULL,
  `saldomedio1` decimal(14,2) default NULL,
  `saldomedio2` decimal(14,2) default NULL,
  PRIMARY KEY  (`codigo`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `saldossubcuenta`
--

LOCK TABLES `saldossubcuenta` WRITE;
/*!40000 ALTER TABLE `saldossubcuenta` DISABLE KEYS */;
INSERT INTO `saldossubcuenta` VALUES ('10000000','-60000.00','0.00','0.00'),('11200000','-8000.00','0.00','0.00'),('11300000','-5100.00','0.00','0.00'),('12900000','0.00','0.00','0.00'),('21000001','20000.00','0.00','0.00'),('21100001','25000.00','0.00','0.00'),('21600001','4000.00','0.00','0.00'),('21700001','1000.00','0.00','0.00'),('21700002','800.00','0.00','0.00'),('21700003','900.00','0.00','0.00'),('28110001','-1750.00','0.00','0.00'),('28160001','-2800.00','0.00','0.00'),('28170001','-750.00','0.00','0.00'),('28170002','-400.00','0.00','0.00'),('28170003','-106.64','0.00','0.00'),('30000000','23000.00','0.00','0.00'),('40000001','0.00','0.00','0.00'),('40000002','0.00','0.00','0.00'),('43000001','0.00','0.00','0.00'),('43000002','0.00','0.00','0.00'),('47000000','0.00','0.00','0.00'),('47200000','0.00','0.00','0.00'),('47300001','0.00','0.00','0.00'),('47500000','-320.00','0.00','0.00'),('47520000','-377.00','0.00','0.00'),('47700000','0.00','0.00','0.00'),('47900001','-238.01','0.00','0.00'),('52300001','0.00','0.00','0.00'),('57000000','8210.00','0.00','0.00'),('60000000','0.00','0.00','0.00'),('61000001','0.00','0.00','0.00'),('63000000','0.00','0.00','0.00'),('63010001','0.00','0.00','0.00'),('68100001','0.00','0.00','0.00'),('70000000','-3068.35','0.00','0.00');
/*!40000 ALTER TABLE `saldossubcuenta` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tiposiva`
--

DROP TABLE IF EXISTS `tiposiva`;
CREATE TABLE `tiposiva` (
  `clave` varchar(4) NOT NULL default '',
  `tipo` decimal(5,2) default NULL,
  `re` decimal(5,2) default NULL,
  `descripcion` varchar(80) default NULL,
  PRIMARY KEY  (`clave`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tiposiva`
--

LOCK TABLES `tiposiva` WRITE;
/*!40000 ALTER TABLE `tiposiva` DISABLE KEYS */;
INSERT INTO `tiposiva` VALUES ('GN','16.00','0.00','TIPO GENERAL'),('GN2','16.00','4.00','TIPO GENERAL CON RECARGO DE EQUIVALENCIA'),('RD','7.00','0.00','TIPO REDUCIDO'),('RD2','7.00','1.00','TIPO REDUCIDO CON RECARGO DE EQUIVALENCIA'),('SRD','4.00','0.00','TIPO SUPERREDUCIDO'),('SRD2','4.00','0.50','TIPO SUPERREDUCIDO CON RECARGO DE EQUIVALENCIA');
/*!40000 ALTER TABLE `tiposiva` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `var_as_modelo`
--

DROP TABLE IF EXISTS `var_as_modelo`;
CREATE TABLE `var_as_modelo` (
  `asientomodelo` varchar(166) NOT NULL default '',
  `variable` varchar(166) NOT NULL default '',
  `tipo` varchar(255) default NULL,
  `descripcion` varchar(255) default NULL,
  `orden` int(11) default NULL,
  PRIMARY KEY  (`asientomodelo`,`variable`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `var_as_modelo`
--

LOCK TABLES `var_as_modelo` WRITE;
/*!40000 ALTER TABLE `var_as_modelo` DISABLE KEYS */;
/*!40000 ALTER TABLE `var_as_modelo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vencimientos`
--

DROP TABLE IF EXISTS `vencimientos`;
CREATE TABLE `vencimientos` (
  `num` bigint(20) NOT NULL default '0',
  `cta_ordenante` varchar(40) default NULL,
  `fecha_operacion` date default NULL,
  `importe` decimal(14,2) default NULL,
  `cuenta_tesoreria` varchar(40) default NULL,
  `fecha_vencimiento` date default NULL,
  `derecho` tinyint(1) default NULL,
  `pendiente` tinyint(1) default NULL,
  `anulado` tinyint(1) default NULL,
  `pase_diario_operacion` bigint(20) default NULL,
  `pase_diario_vencimiento` bigint(20) default NULL,
  `usuario` varchar(80) default NULL,
  PRIMARY KEY  (`num`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `vencimientos`
--

LOCK TABLES `vencimientos` WRITE;
/*!40000 ALTER TABLE `vencimientos` DISABLE KEYS */;
INSERT INTO `vencimientos` VALUES (1,'40000001','2008-01-01','1500.00','57000000','2008-01-20',0,0,0,14,32,'root@localhost'),(2,'40000001','2008-01-01','500.00','57000000','2008-02-10',0,0,0,14,36,'root@localhost'),(3,'40000002','2008-01-01','1500.00','57000000','2008-02-05',0,0,0,15,34,'root@localhost'),(4,'43000001','2008-01-01','500.00','57000000','2008-01-10',1,0,0,16,23,'root@localhost'),(5,'43000002','2008-01-01','400.00','57000000','2008-01-16',1,0,0,17,30,'root@localhost'),(6,'43000001','2008-01-10','116.00','57000000','2008-01-10',1,0,0,27,28,'root@localhost'),(7,'43000002','2008-03-15','174.00','57000000','2008-03-15',1,0,0,40,41,'root@localhost'),(8,'40000001','2008-03-18','1160.00','57000000','2008-03-18',0,0,0,45,46,'root@localhost'),(9,'43000001','2008-04-20','568.40','57000000','2008-04-20',1,0,0,55,56,'root@localhost'),(10,'43000002','2008-06-10','580.00','57000000','2008-04-20',1,0,0,62,58,'root@localhost'),(11,'43000001','2008-07-20','5800.00','57000000','2008-07-20',1,0,0,78,79,'root@localhost'),(12,'43000002','2008-11-10','2320.00','57000000','2008-11-10',1,0,0,92,93,'root@localhost');
/*!40000 ALTER TABLE `vencimientos` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2008-09-04  9:21:38
