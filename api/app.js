var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const helmet = require('helmet');
const cors = require('cors');

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

app.use('/', indexRouter);
app.use('/account', accountRouter);
app.use('/card', cardRouter);
app.use('/charity', charityRouter);
app.use('/customer', customerRouter);
app.use('/transactions', transactionsRouter);

module.exports = app;
