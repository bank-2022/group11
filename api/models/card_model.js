const db = require('../database');

const card = {
  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(card, callback) {
    return db.query(
      'insert into card (customer_idcustomer, account_idaccount, cardnumber, pin, type, locked) values(?,?,?,?,?,?)',
      [card.customer_idcustomer, card.account_idaccount,
      card.cardnumber, card.pin, card.type, card.locked],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },
  update: function(id, card, callback) {
    return db.query(
      'update card set customer_idcustomer=?, account_idaccount=?, cardnumber=?, pin=?, type=?, locked=? where idcard=?',
      [card.customer_idcustomer, card.account_idaccount,
      card.cardnumber, card.pin, card.type, card.locked, id],
      callback
    );
  }
};
module.exports = card;
