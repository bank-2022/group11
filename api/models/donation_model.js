const db = require('../database');

const donation = {
  // calls the procedure which donates money from the users account to a charity account.
  // if the transaction fails, no money is removed from users account nor added to charity account.
  // this is a credit operation which means that the account balance can go negative.
  credit: function(donation, callback) {
    return db.query(
      'call credit_charity(?,?,?)',
      [donation.cardnumber, donation.accountnumber, donation.amount],
      callback
    );
  },

  // calls the procedure which donates money from the users account to a charity account.
  // if the transaction fails, no money is removed from users account nor added to charity account.
  // this is a debit operation which means that the account balance cannot go negative.
  debit: function(donation, callback) {
    return db.query(
      'call debit_charity(?,?,?)',
      [donation.cardnumber,donation.accountnumber, donation.amount],
      callback
    );
  },
};
module.exports = donation;
