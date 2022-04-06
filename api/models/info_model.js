const db = require('../database');

const info = {
  // gets the type of card (credit / debit) from the database
  getType: function(cardnumber, callback) {
    return db.query('select type from card where cardnumber=?', [cardnumber], callback);
  },

  // gets the name and accountnumber from the database
  getCustomerInfo: function(cardnumber, callback) {
    return db.query('select name, accountnumber from (card inner join customer on card.customer_idcustomer = customer.idcustomer) inner join account on card.account_idaccount = account.idaccount where cardnumber=?', [cardnumber], callback);
  },

  // gets the transactions from the database
  get10Transactions: function(req, callback) {
    return db.query('select datetime, event, convert(sum, char(20)) as sum from transactions where accountnumber=? order by idtransactions desc limit ?, 10', [req.params.accountnumber, parseInt(req.params.row)], callback);
  },

  // gets the last five transactions from the database
  get5Transactions: function(accountnumber, callback) {
    return db.query('select datetime, event, convert(sum, char(20)) as sum from transactions where accountnumber=? order by idtransactions desc limit 5', [accountnumber], callback);
  },

  // gets the balance of the account from the database
  getBalance: function(accountnumber, callback) {
    return db.query('select convert(balance, char(20)) as balance from account where accountnumber=?', [accountnumber], callback);
  },
};

module.exports = info;
