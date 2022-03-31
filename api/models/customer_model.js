const db = require('../database');

const customer = {
  getById: function(id, callback) {
    return db.query('select * from customer where idcustomer=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  add: function(customer, callback) {
    return db.query(
      'insert into customer (name,address,pnumber) values(?,?,?)',
      [customer.name, customer.address, customer.pnumber],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer where idcustomer=?', [id], callback);
  },
  update: function(id, customer, callback) {
    return db.query(
      'update customer set name=?,address=?, pnumber=? where idcustomer=?',
      [customer.name, customer.address, customer.pnumber, id],
      callback
    );
  }
};
module.exports = customer;
