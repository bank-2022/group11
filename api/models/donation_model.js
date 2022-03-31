const db = require('../database');

const donation = {
 
  credit: function(donation, callback) {
    return db.query(
      'call credit_charity(?,?,?)',
      [donation.cardnumber, donation.accountnumber, donation.amount],
      callback
    );
  },


  debit: function(donation, callback) {
    return db.query(
      'call debit_charity(?,?,?)',
      [donation.cardnumber,donation.accountnumber, donation.amount],
      callback
    );
  },
};
module.exports = donation;
