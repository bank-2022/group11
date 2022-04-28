const express = require('express');
const router = express.Router();
const donation = require('../models/donation_model');

router.post('/credit',
function(request, response) {
  donation.credit(request.body, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.post('/debit',
function(request, response) {
  donation.debit(request.body, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(request.body);
    }
  });
});


module.exports = router;
