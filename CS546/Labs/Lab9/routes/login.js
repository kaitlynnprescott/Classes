/************************************************************************************
 * Name        : login.js
 * Author      : Kaitlynn Prescott
 * Date        : Apr 10, 2017
 * Description : CS-564 Lab 9: A Simple User Login System
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require('express');
const passport = require('passport');
const router = express.Router();

// get
router.get("/", (req, res) => {
    res.render('login', {error: req.flash('loginMessage')});
});

//post
router.post("/", passport.authenticate('local', {failureRedirect: '/login', failureFlash: true }), (req, res) => {
        res.redirect("/private");
});

module.exports = router;

