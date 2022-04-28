const express = require('express');
const router = express.Router();
const withdrawal = require('../models/withdrawal_model');

router.post('/credit',
function(request, response) {
  withdrawal.credit(request.body, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.post('/debit',
function(request, response) {
  withdrawal.debit(request.body, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(request.body);
    }
  });
});


module.exports = router;
