const express = require("express")
const cors = require("cors");
const child_process = require('child_process');
 
let app = express();
app.use(cors());
app.get("/chat",function(req,res){
    var response = req.query.question
   
   var chat = child_process.exec('python chat.py '+response, function (error, stdout, stderr){
    if(error) {
        console.info('stderr : '+stderr);
    }
    //console.log('chat: ' + );
    res.end(JSON.stringify(stdout));
})
})

//监听3000端口
app.listen(3005);


