const db = require('../database');

const info = {
  getType: function(cardnumber, callback) {
    return db.query('select type from card where cardnumber=?', [cardnumber], callback);
  },

  getCustomerInfo: function(cardnumber, callback) {
    return db.query('select name, accountnumber from (card inner join customer on card.customer_idcustomer = customer.idcustomer) inner join account on card.account_idaccount = account.idaccount where cardnumber=?', [cardnumber], callback);
  },

  getTransactions: function(accountnumber, callback) {
    return db.query('select * from transactions where accountnumber=?', [accountnumber], callback);
  },

  get5Transactions: function(accountnumber, callback) {
    return db.query('select * from transactions where accountnumber=? order by idtransactions desc limit 5', [accountnumber], callback);
  },

  getBalance: function(accountnumber, callback) {
    return db.query('select balance from account where accountnumber=?', [accountnumber], callback);
  },
};

module.exports = info;
