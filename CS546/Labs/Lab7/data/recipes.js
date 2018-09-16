/************************************************************************************
 * Name        : recipes.js (../data)
 * Author      : Kaitlynn Prescott
 * Date        : Mar 9, 2017
 * Description : CS-564 Lab 7: A Recipe API
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const mongoCollections = require("../config/mongoCollections");
const recipes = mongoCollections.recipes;
const uuid = require('node-uuid');

let exportedMethods = {
    getRecipeById(id) {
        // check if recipe exists
        if (!id) {
            return Promise.reject("Recipe ID is invalid!");
        }
        return recipes().then((recipeCollection) => {
            return recipeCollection.findOne({ _id: id }).then((recipe) => {
                if (!recipe) throw "Recipe not found";
                return recipe;
            });
        });
    },
    getAllRecipes() {
        return recipes().then((recipeCollection) => {
            return recipeCollection.find({}).toArray();
        })
    },
    addRecipe(title, ingredients, steps) {
        // check if title exists
        if (!title) {
            return Promise.reject("Must enter title of recipe");
        }
        // check if ingredients exists
        if (!ingredients) {
            return Promise.reject("Must enter ingredients of recipe");
        }
        // check if steps exists
        if (!steps) {
            return Promise.reject("Must enter steps of recipe");
        }
        return recipes().then((recipeCollection) => {
            let newRecipe = {
                _id: uuid.v4(),
                title: title,
                ingredients: ingredients,
                steps: steps,
                comments: []  
            };
            return recipeCollection.insertOne(newRecipe).then((newInsertInformation) => {
                return newInsertInformation.insertedId;
            }).then((newId) => {
                return this.getRecipeById(newId);
            });
        });
    },
    removeRecipe(id) {
        // check if recipe exists
        if (!id) {
            return Promise.reject("Invalid recipe ID");
        }
        return recipes().then((recipeCollection) => {
            return recipeCollection.removeOne({ _id: id }).then((deletionInfo) => {
                if (deletionInfo.deletedCount === 0) {
                    throw (`Could not delete recipe with id of ${id}`)
                } else { }
            });
        });
    },
    updateRecipe(recipeId, updatedRecipe) {
        // check if recipe exists
        if (!recipeId) {
            return Promise.reject("Invalid Recipe Id");
        }
        // check if new recipe exists
        if (!updatedRecipe) {
            return Promise.reject("You must enter some data");
        }
        return recipes().then((recipeCollection) => {
            let newRecipeData = {};
            if (updatedRecipe.title) {
                newRecipeData.title = updatedRecipe.title;
            }
            if (updatedRecipe.ingredients) {
                newRecipeData.ingredients = updatedRecipe.ingredients;
            }
            if (updatedRecipe.steps) {
                newRecipeData.steps = updatedRecipe.steps;
            }

            return recipeCollection.updateOne({ _id: recipeId }, { $set: newRecipeData }).then((result) => {
                return this.getRecipeById(recipeId)
            })
        });

   },
    addComment(recipeId, poster, comment) {
        // check if recipe exists
        if (!recipeId) {
            return Promise.reject("Invalid recipe ID");
        }
        // check if poster exists
        if (!poster) {
            return Promise.reject("Must enter poster");
        }
        // check if comment exists
        if (!comment) {
            return Promise.reject("Must enter comment");
        }
        return recipes().then((recipeCollection) => {
            let newComment = {
                _id: uuid.v4(),
                poster: poster,
                comment: comment
            }
            return recipeCollection.updateOne({ _id: recipeId }, {
                $addToSet: {
                    comments: newComment
                }
            }).then(() => {
                return newComment;
            });
        });
    },
    removeComment(commentId) {
        // check if comment exists
        if (!commentId) {
            return Promise.reject("Invalid comment ID");
        }
        return recipes().then((recipeCollection) => {
            return recipeCollection.update({}, { $pull: {comments: {_id: commentId}}}, false, true)
            .then((deletionInfo) => {
                if (deletionInfo.deletedCount === 0) {
                    return Promise.reject('Could not delete comment with Id ' + commentId);
                } else {}
            }).catch((err) => {
                return Promise.reject(err);
            });
        });
    },
    updateComment(recipeId, commentId, updatedComment) {
        // check if recipe exists
        if (!recipeId) {
            return Promise.reject("Invalid Recipe id");
        }
        // check if recipe exists
        if (!commentId) {
            return Promise.reject("Invalid Comment Id");
        }
        // check if recipe exists
        if (!updatedComment) {
            return Promise.reject("You must enter new data");
        }

        return recipes().then((recipeCollection) => {
            let newComment = {};
            if (updatedComment.poster) {
                newComment.poster = updatedComment.poster;
            }
            if (updatedComment.comment) {
                newComment.comment = updatedComment.comment;
            }
            newComment._id = commentId;
            return recipeCollection.update({ "comments._id": commentId }, {
                $set: { "comments.$": newComment }
            }).then(() => {
                return this.getCommentById(commentId);
            });
        });
    },
    getCommentById(commentId) {
        // check if comment exists
        if (!commentId) {
            return Promise.reject("Invalid comment ID");
        }
        return recipes().then((recipeCollection) => {
            return recipeCollection.findOne({ "comments._id": commentId }, { 'comments.$': 1 })
            .then((recipe) => {
                if (!recipe) throw "Comment not found";
                return recipe.comments;
            })
        });
    },
    stupidGetCommentById(commentId) {
        // check if comment exists
        if (!commentId) {
            return Promise.reject("Invalid comment ID");
        }
        return recipes().then((recipeCollection) => {
            return recipeCollection.findOne({ "comments._id": commentId }, { 'comments.$': 1 })
            .then((recipe) => {
                if (!recipe) throw "Comment not found";
                return recipe;
            })
        });
    },
    getAllComments(recipeId) {
        // check if recipe exists
        if (!recipeId) {
            return Promise.reject("Invalid recipe ID.");
        }
        return recipes().then((recipeCollection) => {
            return recipeCollection.findOne({ "_id": recipeId }).then((recipe) => {
                if (!recipe) throw "Recipe not found";
                return recipe.comments;
            })
        });
    }
}

module.exports = exportedMethods;