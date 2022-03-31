const db = require('../database');

const customer_has_account = {
  getById: function(id, callback) {
    return db.query('select * from customer_has_account where customer_idcustomer=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from customer_has_account', callback);
  },
  add: function(customer_has_account, callback) {
    return db.query(
      'insert into customer_has_account (customer_idcustomer,account_idaccount) values(?,?)',
      [customer_has_account.customer_idcustomer, customer_has_account.account_idaccount],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer_has_account where customer_idcustomer=?', [id], callback);
  },
  update: function(id, customer_has_account, callback) {
    return db.query(
      'update customer_has_account set customer_idcustomer=?,account_idaccount=? where customer_idcustomer=?',
      [customer_has_account.customer_idcustomer, customer_has_account.account_idaccount, id],
      callback
    );
  }
};
module.exports = customer_has_account;
