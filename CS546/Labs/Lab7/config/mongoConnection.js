/************************************************************************************
 * Name        : mongoConnection.js
 * Author      : Kaitlynn Prescott
 * Date        : Mar 9, 2017
 * Description : CS-564 Lab 7: A Recipe API
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const MongoClient = require("mongodb").MongoClient;;

const settings = {
    mongoConfig: {
        serverUrl: "mongodb://localhost:27017/",
        database: "lab7-recipes"
    }
};

let fullMongoUrl = settings.mongoConfig.serverUrl + settings.mongoConfig.database;
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