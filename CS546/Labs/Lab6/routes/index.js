/************************************************************************************
 * Name        : index.js
 * Author      : Kaitlynn Prescott
 * Date        : Mar 2, 2017
 * Description : CS-564 Lab 6: JSON Routes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const aboutRoutes = require("./about");
const educationRoutes = require("./education");
const storyRoutes = require("./story");

const constructorMethod = (app) => {
    app.use("/about", aboutRoutes);
    app.use("/education", educationRoutes);
    app.use("/story", storyRoutes);

    app.use("*", (req, res) => {
        res.status(404).json({error: "Not found"});
    });
};

module.exports = constructorMethod;