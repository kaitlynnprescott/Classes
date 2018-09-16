/************************************************************************************
 * Name        : index.js (../routes)
 * Author      : Kaitlynn Prescott
 * Date        : Mar 9, 2017
 * Description : CS-564 Lab 7: A Recipe API
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const recipeData = require("./recipes");
const commentData = require("./comments");

const constructorMethod = (app) => {
    app.use("/recipes", recipeData);
    app.use("/comments", commentData);

    app.use("*", (req, res) => {
        res.status(404).json({error: "Not found"});
    });
};

module.exports = constructorMethod;