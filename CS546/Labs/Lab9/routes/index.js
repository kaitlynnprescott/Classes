/************************************************************************************
 * Name        : index.js (../routes)
 * Author      : Kaitlynn Prescott
 * Date        : Apr 10, 2017
 * Description : CS-564 Lab 9: A Simple User Login System
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const loginRoutes = require("./login");
const privateRoutes = require("./private");
const passport = require('passport');
const Strategy = require('passport-local').Strategy;

const constructorMethod = (app) => {
    app.use("/login", loginRoutes);
    app.use("/private", privateRoutes);

    app.use("*", require('connect-ensure-login').ensureLoggedIn(), (req, res) => {
        // if the login information is valid, redirect to private
        res.redirect("/private");
    })
};

module.exports = constructorMethod;