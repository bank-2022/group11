const express = require('express');
const router = express.Router();
const info = require('../models/info_model');


router.get('/type/:cardnumber',
 function(request, response) {
   info.getType(request.params.cardnumber, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0]);
      }
    });
});


router.get('/customer/:cardnumber',
 function(request, response) {
   info.getCustomerInfo(request.params.cardnumber, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0]);
      }
    });
});


router.get('/10transactions/:accountnumber/:row',
 function(request, response) {
   request.params.accountnumber;
   request.params.row;
   info.get10Transactions(request, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});


router.get('/5transactions/:accountnumber',
 function(request, response) {
   info.get5Transactions(request.params.accountnumber, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});


router.get('/balance/:accountnumber',
 function(request, response) {
   info.getBalance(request.params.accountnumber, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0]);
      }
    });
});


module.exports = router;
