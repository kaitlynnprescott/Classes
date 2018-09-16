/************************************************************************************
 * Name        : recipes.js (../routes)
 * Author      : Kaitlynn Prescott
 * Date        : Mar 9, 2017
 * Description : CS-564 Lab 7: A Recipe API
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require('express');
const router = express.Router();
const data = require("../data");
const recipeData = data.recipes;

router.get("/:id", (req, res) => {
    // path: /recipes
    // Responds with a list of all recipes in the format of {_id: RECIPE_ID, title: RECIPE_TITLE}
    recipeData.getRecipeById(req.params.id).then((recipe) => {
        res.json(recipe);
    }).catch((error) => {
        // Not found!
        res.status(404).json({ message: "Recipe not found" });
    });
});

router.get("/", (req, res) => {
    // path: /recipes/:id
    // Responds with the full content of the specified recipe
    recipeData.getAllRecipes().then((recipeList) => {
        res.json(recipeList);
    }, () => {
        // Something went wrong with the server!
        res.status(500).send();
    });
});

router.post("/", (req, res) => {
    // path: /recipes
    // Creates a recipe with the supplied data in the request body, and returns the new recipe
    let newRecipeInfo = req.body;
    if (!newRecipeInfo) {
        res.status(400).json({ error: "Must enter data for a recipe" });
    }
    if (!newRecipeInfo.title) {
        res.status(400).json({ error: "Must enter title data" });
        return;
    }
    if (!newRecipeInfo.ingredients) {
        res.status(400).json({ error: "Must enter ingredient data" });
        return;
    }
    if (!newRecipeInfo.steps) {
        res.status(400).json({ error: "Must enter step data" });
        return;
    }

    recipeData.addRecipe(newRecipeInfo.title, newRecipeInfo.ingredients, newRecipeInfo.steps).then((newRecipe) => {
        res.json(newRecipe);
    }, () => {
        res.sendStatus(500);
    });
});

router.put("/:id", (req, res) => {
   let updatedData = req.body;
   let getRecipe = recipeData.getRecipeById(req.params.id);
   getRecipe.then(() => {
       return recipeData.updateRecipe(req.params.id, updatedData)
           .then((updatedRecipe) => {
               res.json(updatedRecipe);
           }).catch((e) => {
               res.status(500).json({ error: e });
           });
   }).catch((err) => {
       res.status(404).json({ error: err });
   });
});

router.delete("/:id", (req, res) => {
    // path: /recipes/:id
    // Deletes the recipe
    console.log("ID: " + req.params.id);
    let recipe = recipeData.getRecipeById(req.params.id).then(() => {
        return recipeData.removeRecipe(req.params.id).then(() => {
            res.sendStatus(200);
        }).catch(() => {
            res.sendStatus(500);
        });
    }).catch(() => {
        res.status(404).json({ error: "Recipe not found" });
    });
});

module.exports = router;