/************************************************************************************
 * Name        : app.js
 * Author      : Kaitlynn Prescott
 * Date        : Apr 4, 2017
 * Description : CS-564 Lab 8: Palindromes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const static = express.static(__dirname + '/public');

const configRoutes = require("./routes");

const exphbs = require('express-handlebars');

const Handlebars = require('handlebars');

const handlebarsInstance = exphbs.create({
    defaultLayout: 'main',
    // Specify helpers which are only registered on this instance.
    helpers: {
        asJSON: (obj, spacing) => {
            if (typeof spacing === "number")
                return new Handlebars.SafeString(JSON.stringify(obj, null, spacing));
        
            return new Handlebars.SafeString(JSON.stringify(obj));
        }
    }
});


app.use("/public", static);
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));


app.engine('handlebars', handlebarsInstance.engine);
app.set('view engine', 'handlebars');

configRoutes(app);

app.listen(5000, () => {
    console.log("We've now got a server!");
    console.log("Your routes will be running on http://localhost:5000");
});