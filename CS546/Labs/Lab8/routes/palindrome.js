/************************************************************************************
 * Name        : palindrome.js (../routes)
 * Author      : Kaitlynn Prescott
 * Date        : Apr 4, 2017
 * Description : CS-564 Lab 8: Palindromes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require('express');
const router = express.Router();

router.get("/static", (req, res) => {
    res.render("static", {});
});


module.exports = router;