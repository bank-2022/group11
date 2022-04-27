var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const helmet = require('helmet');
const cors = require('cors');
const jwt = require('jsonwebtoken');

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

var loginRouter = require('./routes/login');  
var accountRouter = require('./routes/account');
var cardRouter = require('./routes/card');
var charityRouter = require('./routes/charity');
var customerRouter = require('./routes/customer');
var transactionsRouter = require('./routes/transactions');
var customer_has_accountRouter = require('./routes/customer_has_account');
var withdrawalRouter = require('./routes/withdrawal');
var donationRouter = require('./routes/donation');
var infoRouter = require('./routes/info');
var lockedRouter = require('./routes/locked');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(helmet());
app.use(cors());

app.use('/login', loginRouter);

app.use(authenticateToken);
// Protected routes
app.use('/account', accountRouter);
app.use('/card', cardRouter);
app.use('/charity', charityRouter);
app.use('/customer', customerRouter);
app.use('/transactions', transactionsRouter);
app.use('/customerhasaccount', customer_has_accountRouter);
app.use('/withdrawal', withdrawalRouter);
app.use('/donation', donationRouter);
app.use('/info', infoRouter);
app.use('/locked', lockedRouter);

module.exports = app;
