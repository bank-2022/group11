const db = require('../database');

const locked = {
  getByCardnumber: function(cardnumber, callback) {
    return db.query(
      'select locked from card where cardnumber=?',
      [cardnumber], callback);
  },
  update: function(cardnumber, locked,  callback) {
    return db.query(
      'update card set locked=? where cardnumber=?',
      [locked.locked, cardnumber],
      callback);
  }
};
module.exports = locked;
