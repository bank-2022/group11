const db = require('../database');

const transactions = {
  getById: function(id, callback) {
    return db.query('select * from transactions where idtransactions=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from transactions', callback);
  },
  add: function(transactions, callback) {
    return db.query(
      'insert into transactions (account_idaccount, accountnumber, cardnumber, datetime, event, sum) values(?,?,?,?,?,?)',
      [transactions.account_idaccount, transactions.accountnumber,
      transactions.cardnumber, transactions.datetime, transactions.event,
      transactions.sum],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from transactions where idtransactions=?', [id], callback);
  },
  update: function(id, transactions, callback) {
    return db.query(
      'update transactions set account_idaccount=?,accountnumber=?, cardnumber=?, datetime=?, event=?, sum=? where idtransactions=?',
      [transactions.account_idaccount, transactions.accountnumber,
      transactions.cardnumber, transactions.datetime, transactions.event,
      transactions.sum, id],
      callback
    );
  }
};
module.exports = transactions;
