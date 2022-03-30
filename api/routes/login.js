const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.cardnumber && request.body.pin){
      const card = request.body.cardnumber;
      const pin = request.body.pin;
      
        login.checkPassword(card, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pin, dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ cardnumber: card });
                  response.send(token);
                }
                else {
                    console.log("wrong pin");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("card does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("card number or pin missing");
      response.send(false);
    }
  }
);

function generateAccessToken(cardnumber) {
  dotenv.config();
  return jwt.sign(cardnumber, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;