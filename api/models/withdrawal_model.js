const db = require('../database');

const withdrawal = {
 
  credit: function(withdrawal, callback) {
    return db.query(
      'call credit_withdraw(?,?)',
      [withdrawal.cardnumber, withdrawal.amount],
      callback
    );
  },


  debit: function(withdrawal, callback) {
    return db.query(
      'call debit_withdraw(?,?)',
      [withdrawal.cardnumber, withdrawal.amount],
      callback
    );
  },
};
module.exports = withdrawal;
