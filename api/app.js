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
var indexRouter = require('./routes/index');
var accountRouter = require('./routes/account');
var cardRouter = require('./routes/card');
var charityRouter = require('./routes/charity');
var customerRouter = require('./routes/customer');
var transactionsRouter = require('./routes/transactions');

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
app.use('/', indexRouter);
app.use(authenticateToken);
app.use('/account', accountRouter);
app.use(authenticateToken);
app.use('/card', cardRouter);
app.use(authenticateToken);
app.use('/charity', charityRouter);
app.use(authenticateToken);
app.use('/customer', customerRouter);
app.use(authenticateToken);
app.use('/transactions', transactionsRouter);

module.exports = app;
