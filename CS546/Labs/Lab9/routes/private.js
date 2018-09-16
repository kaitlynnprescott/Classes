/************************************************************************************
 * Name        : private.js
 * Author      : Kaitlynn Prescott
 * Date        : Apr 10, 2017
 * Description : CS-564 Lab 9: A Simple User Login System
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require('express');
const passport = require('passport');
const router = express.Router();


// get
router.get("/", require('connect-ensure-login').ensureLoggedIn(), (req, res) => {
    res.render('private', req.user);
});

module.exports = router;