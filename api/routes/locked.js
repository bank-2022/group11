const express = require('express');
const router = express.Router();
const locked = require('../models/locked_model');

router.get('/:cardnumber',
function(request, response) {
  locked.getByCardnumber(request.params.cardnumber, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(dbResult[0]);
    }
  });
});

router.put('/:cardnumber',
function(request, response) {
  locked.update(request.params.cardnumber, request.body, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
