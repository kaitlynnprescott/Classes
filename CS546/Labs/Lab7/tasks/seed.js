/************************************************************************************
 * Name        : seed.js
 * Author      : Kaitlynn Prescott
 * Date        : Mar 9, 2017
 * Description : CS-564 Lab 7: A Recipe API
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const dbConnection = require("../config/mongoConnection");
const data = require("../data/");
const recipes = data.recipes;

dbConnection().then(db => {
    return db.dropDatabase().then(() => {
        return dbConnection;
    }).then((db) => {
        // add recipes 
        let title = "Fried Eggs";
        let ingredients = [
            {
                name: "Eggs",
                amount: "2 eggs"
            },
            {
                name: "Olive oil",
                amount: "2 tbsp"
            },
        ];
        let steps = [
            "First, heat a non-stick pan on medium-high until hot",
            "Add the oil to the pan and allow oil to warm; it is ready the oil immediately sizzles upon contact with a drop of water.",
            "Crack the egg and place the egg and yolk in a small prep bowl; do not crack the yolk!",
            "Gently pour the egg from the bowl onto the oil",    
            "Wait for egg white to turn bubbly and completely opaque (approx 2 min)",
            "Using a spatula, flip the egg onto its uncooked side until it is completely cooked (approx 2 min)",
            "Remove from oil and plate",
            "Repeat for second egg"
        ];
        return recipes.addRecipe(title, ingredients, steps);
    }).then((friedEggs) => {
        // add comments
        const id = friedEggs._id;
        console.log('added recipe with id ' + id);
        recipes.addComment(id, "Katie Prescott", "Yum!").then((newComment1) => {
            console.log(`added comment by Katie Prescott`);
        });
        recipes.addComment(id, "Gordon Ramsey", "These eggs are delicious!").then((newComment2) => {
            console.log(`added comment by Gordon Ramsey`);
            recipes.getCommentById(newComment2._id).then((comment1) => {
                console.log(comment1);
                db.close();
            });
        });
    }).then(() => {
        console.log("Done seeding database");
        //db.close();
    });
}, (error) => {
    console.error(error);
});