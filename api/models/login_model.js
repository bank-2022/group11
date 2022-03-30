const db = require('../database');

const login={
  checkPassword: function(cardnumber, callback) {
      return db.query('SELECT pin FROM card WHERE cardnumber = ?',[cardnumber], callback); 
    }
};
          
module.exports = login;