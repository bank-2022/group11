const express = require('express');
const router = express.Router();
const customer_has_account = require('../models/customer_has_account_model');

router.get('/:id?',
 function(request, response) {
  if (request.params.id) {
    customer_has_account.getById(request.params.id, function(err, dbResult) {
      if (err) {
        response.status(503).json(err);
      } else {
        response.json(dbResult);
      }
    });
  } else {
    customer_has_account.getAll(function(err, dbResult) {
      if (err) {
        response.status(503).json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
});


router.post('/',
function(request, response) {
  customer_has_account.add(request.body, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id',
function(request, response) {
  customer_has_account.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id',
function(request, response) {
  customer_has_account.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.status(503).json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
