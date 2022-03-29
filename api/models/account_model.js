const db = require('../database');

const account = {
  getById: function(id, callback) {
    return db.query('select * from account where idaccount=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  add: function(account, callback) {
    return db.query(
      'insert into account (accountnumber,balance) values(?,?)',
      [account.accountnumber, account.balance],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where idaccount=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set accountnumber=?,balance=?, where idaccount=?',
      [account.accountnumber, account.balance, id],
      callback
    );
  }
};
module.exports = account;
