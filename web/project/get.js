var mysql = require('mysql');
var express = require('express');
var app = express(); 
const mqtt = require('mqtt');

var connection = mysql.createConnection({     
  host     : '49.233.60.32',       
  user     : 'user',              
  password : 'password',       
  port: '3306',                   
  database: 'test' 
}); 

const host = '49.233.60.32';
const port = '1883';
const clientId = `mqtt_${Math.random().toString(16).slice(3)}` ;
const connectUrl = `mqtt://${host}:${port}`;

const client = mqtt.connect(connectUrl, {
  clientId,
  clean: true,
  connectTimeout: 4000,
  username: 'server',
  password: '123456',
  reconnectPeriod: 1000,
});
const topic = 'dev/#'
client.on('connect', () => {
 console.log('Connected')
  client.subscribe([topic], () => {
   console.log(`Subscribe to topic '${topic}'`)
  })
})
var bodyda = ' '; 
var topi = '';
client.on('message', (topic, payload) => {
    bodyda= String(payload);
    topi = String(topic);
    console.log(bodyda);
var datebody=bodyda.split(",");
//console.log("datebody{1}:",datebody[0]);
//console.log("datebody{2}:",datebody[1]);
//console.log("timedatebody[3]:",datebody[2]);
if (datebody[1] != datebody[1]){return;}
var hum = (Number(datebody[0])%1000);
var temstate = 0;
if( Math.floor(Number(datebody[0])/1000000) == 1){ temstate =1; }else {temstate = -1;}
//console.log("temstate: ",temstate);
//console.log(Number(datebody[0])%1000000);
var tem =(Number(datebody[0])%1000000-hum)/1000/10;
console.log(tem);
var hum1 =hum/10;
var tem1 = tem * temstate;
//console.log(hum1,tem1);
var  addSql = 'INSERT INTO test_date(id,dev,time,tem,hum) VALUES(0,?,?,?,?)';
var  addsqlParams = [topic,datebody[1],tem1,hum1];
connection.query(addSql,addsqlParams);

})
