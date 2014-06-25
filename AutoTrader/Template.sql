/*
Navicat MySQL Data Transfer

Source Server         : 192.168.74.149
Source Server Version : 50535
Source Host           : 192.168.74.149:3306
Source Database       : VDatabase

Target Server Type    : MYSQL
Target Server Version : 50535
File Encoding         : 65001

Date: 2014-04-08 09:47:50
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for Template
-- ----------------------------
DROP TABLE IF EXISTS `Template`;
CREATE TABLE `Template` (
  `ID` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT '唯一ID',
  `CODE` varchar(255) DEFAULT NULL COMMENT '交易代码',
  `YesterdaySettlementPrice` decimal(10,3) unsigned DEFAULT NULL COMMENT '昨日结算价',
  `OpenPrice` decimal(10,3) unsigned DEFAULT NULL COMMENT '开盘价',
  `SellPrice` decimal(10,3) unsigned DEFAULT NULL COMMENT '卖价',
  `BuyPrice` decimal(10,3) unsigned DEFAULT NULL COMMENT '买价',
  `Unknow1` int(255) DEFAULT NULL COMMENT '分割符',
  `NewPrice` decimal(10,3) unsigned DEFAULT NULL COMMENT '最新价',
  `SellVolume` int(30) DEFAULT NULL COMMENT '卖量',
  `BuyVolume` int(30) DEFAULT NULL COMMENT '买量',
  `Unknow2` int(10) DEFAULT NULL,
  `HightPrice` decimal(10,3) DEFAULT NULL COMMENT '最高价',
  `LowPrice` decimal(10,3) DEFAULT NULL COMMENT '最低价',
  `AveragePrice` decimal(10,0) DEFAULT NULL COMMENT '均价',
  `PriceChangePoint` decimal(10,3) DEFAULT NULL COMMENT '涨跌点数',
  `TradingVolume` int(20) DEFAULT NULL COMMENT '成交量',
  `HoldPosition` int(20) unsigned DEFAULT NULL COMMENT '持仓量',
  `TradeMoney` int(30) DEFAULT NULL COMMENT '交易金额',
  `LimitUp` decimal(10,3) DEFAULT NULL COMMENT '涨停价',
  `LimitDown` decimal(10,3) DEFAULT NULL COMMENT '跌停价',
  `Unknow11` int(5) DEFAULT NULL,
  `Unknow12` int(5) DEFAULT NULL,
  `Unknow13` int(5) DEFAULT NULL,
  `Unknow14` int(5) DEFAULT NULL,
  `Unknow15` int(5) DEFAULT NULL,
  `YesterdayClosePrice` decimal(10,3) DEFAULT NULL,
  `AddPosition` int(10) DEFAULT NULL COMMENT '增仓',
  `UnknowNew` decimal(10,3) DEFAULT NULL COMMENT '可能是最新价',
  `UnknowSettlement` decimal(10,3) DEFAULT NULL COMMENT '可能是结算价三',
  `SQLTimeStamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'SQL时间戳',
  `HSTimeStamp` varchar(20) DEFAULT NULL COMMENT '恒生时间',
  `UnknowZero` varchar(255) DEFAULT NULL COMMENT '未知零 集合',
  `HSDate` date DEFAULT NULL COMMENT '日期',
  `UnknowGateway` varchar(255) DEFAULT NULL COMMENT '网关',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
