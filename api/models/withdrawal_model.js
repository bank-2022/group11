const db = require('../database');

const withdrawal = {
 
  // calls the procedure which withdraws money from the users account.
  // if the transaction fails, no money is removed from users account.
  // this is a credit operation which means that the account balance can go negative.
  credit: function(withdrawal, callback) {
    return db.query(
      'call credit_withdraw(?,?)',
      [withdrawal.cardnumber, withdrawal.amount],
      callback
    );
  },

  // calls the procedure which withdraws money from the users account.
  // if the transaction fails, no money is removed from users account.
  // this is a debit operation which means that the account balance cannot go negative.
  debit: function(withdrawal, callback) {
    return db.query(
      'call debit_withdraw(?,?)',
      [withdrawal.cardnumber, withdrawal.amount],
      callback
    );
  },
};
module.exports = withdrawal;
