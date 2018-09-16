/************************************************************************************
 * Name        : index.js (../routes)
 * Author      : Kaitlynn Prescott
 * Date        : Apr 4, 2017
 * Description : CS-564 Lab 8: Palindromes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const palindromeRoutes = require("./palindrome");

const constructorMethod = (app) => {
    app.use("/palindrome", palindromeRoutes);

    app.use("*", (req, res) => {
        res.redirect("/palindrome/static");
    })
};

module.exports = constructorMethod;