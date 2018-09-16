/************************************************************************************
 * Name        : mongoCollections.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 16, 2017
 * Description : CS-564 Lab 4: Our First ToDo
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const dbConnection = require("./mongoConnection");

let getConnectionFn = (collection) => {
    let _col = undefined;

    return () => {
        if (!_col) {
            _col = dbConnection().then(db => {
                return db.collection(collection);
            });
        }
        return _col;
    }
}

module.exports = {
    todoItems: getConnectionFn("todoItems")
};
