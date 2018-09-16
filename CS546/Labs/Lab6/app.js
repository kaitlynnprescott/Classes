/************************************************************************************
 * Name        : app.js
 * Author      : Kaitlynn Prescott
 * Date        : Mar 2, 2017
 * Description : CS-564 Lab 6: JSON Routes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require("express");
let app = express();
let configRoutes = require("./routes");

configRoutes(app);

app.listen(3000, () => {
    console.log("We've now got a server!");
    console.log("Your routes will be running on http://localhost:3000");
});