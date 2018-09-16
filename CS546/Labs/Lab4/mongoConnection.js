/************************************************************************************
 * Name        : mongoConnection.js
 * Author      : Kaitlynn Prescott
 * Date        : Feb 16, 2017
 * Description : CS-564 Lab 4: Our First ToDo
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const MongoClient = require("mongodb").MongoClient;

const settings = {
    mongoConfig: {
        serverURL: "mongodb://localhost:27017/",
        database: "lab4"
    }
};

let fullMongoUrl = settings.mongoConfig.serverURL + settings.mongoConfig.database;
let _connection = undefined

let connectDb = () => {
    if (!_connection) {
        _connection = MongoClient.connect(fullMongoUrl)
            .then((db) => {
                return db;
            });
    }

    return _connection;
};

module.exports = connectDb;