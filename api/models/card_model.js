const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const card = {
  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(card, callback) {
    bcrypt.hash(card.pin, saltRounds, function(err, hash) {
    return db.query(
      'insert into card (customer_idcustomer, account_idaccount, cardnumber, pin, type, locked) values(?,?,?,?,?,?)',
      [card.customer_idcustomer, card.account_idaccount,
      card.cardnumber, hash, card.type, card.locked],
      callback)
      });
  },
  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },
  update: function(id, card, callback) {
    bcrypt.hash(card.pin, saltRounds, function(err, hash) {
    return db.query(
      'update card set customer_idcustomer=?, account_idaccount=?, cardnumber=?, pin=?, type=?, locked=? where idcard=?',
      [card.customer_idcustomer, card.account_idaccount,
      card.cardnumber, hash, card.type, card.locked, id],
      callback)
      });
  }
};
module.exports = card;
