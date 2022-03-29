const db = require('../database');

const charity = {
  getById: function(id, callback) {
    return db.query('select * from charity where idcharity=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from charity', callback);
  },
  add: function(charity, callback) {
    return db.query(
      'insert into charity (accountnumber,balance) values(?,?)',
      [charity.accountnumber, charity.balance],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from charity where idcharity=?', [id], callback);
  },
  update: function(id, charity, callback) {
    return db.query(
      'update charity set accountnumber=?,balance=? where idcharity=?',
      [charity.accountnumber, charity.balance, id],
      callback
    );
  }
};
module.exports = charity;
