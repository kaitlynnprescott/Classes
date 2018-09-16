/************************************************************************************
 * Name        : comments.js
 * Author      : Kaitlynn Prescott
 * Date        : Mar 9, 2017
 * Description : CS-564 Lab 7: A Recipe API
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require('express');
const router = express.Router();
const data = require("../data");
const recipeData = data.recipes;

router.get("/recipe/:recipeId", (req, res) => {
    recipeData.getAllComments(req.params.recipeId).then((comment) => {
        recipeData.getRecipeById(req.params.recipeId).then((recipe) => {
            let result = {
                _id: recipe._id,
                recipeTitle: recipe.title,
                comments: comment
            }
            res.json(result);
        });
    }).catch((error) => {
        res.status(404).json({ error: error });
    });
});

router.get("/:commentId", (req, res) => {
    // path: /comments/:commentId
    // Returns the comment specified by that commentId in the format of {_id: COMMENT_ID, recipeId: RECIPE_ID, reciipeTitle: RECIPE_TITLE, poster: COMMENT_NAME, comment: COMMENT}
    recipeData.stupidGetCommentById(req.params.commentId).then((comment) => {
        recipeData.getRecipeById(comment._id).then((recipe) => {
            result = {
                _id: comment.comments._id,
                recipeId: recipe._id,
                recipeTitle: recipe.title,
                poster: comment.comments[0].poster,
                comment: comment.comments[0].comment
            }
            res.json(result);
        });
    }).catch(() => {
        res.status(404).json({ error: "Comment not found" });
    });
});

router.post("/:recipeId", (req, res) => {
    // path: /comments/:recipeId/
    // Creates a new comment with the supplied data in the request body for the stated recipe, and returns the new comment
    let recipeID = req.params.recipeId;
    let commentInfo = req.body;
    console.log(commentInfo);
    if (!commentInfo) {
        res.status(400).json({ error: "Must enter data for comment" });
        return;
    }
    if (!commentInfo.poster) {
        res.status(400).json({ error: "Must enter poster data" });
        return;
    }
    if (!commentInfo.comment) {
        res.status(400).json({ error: "Must enter comment data" });
        return;
    }
    recipeData.addComment(recipeID, commentInfo.poster, commentInfo.comment).then((newComment) => {
        console.log("RecipeID: " + recipeID) 
        console.log("Poster: " + commentInfo.poster) 
        console.log("Comment: " + commentInfo.comment);
        res.json(newComment);
    }).catch((er) => {
        res.status(500).json({ error: er });
    });
});

router.put("/:recipeId/:commentId", (req, res) => {
    // path: /comments/:recipeId/:commentId
    // Updates the specified comment for the stated recipe with only the supplied changes, and returns the updated comment
    let updatedData = req.body;
    let getComment = recipeData.getCommentById(req.params.commentId);
    getComment.then(() => {
        return recipeData.updateComment(req.params.recipeId, req.params.commentId, updatedData)
            .then((updatedComment) => {
                res.json(updatedComment);
            }).catch((e) => {
                console.log(e);
                res.status(500).json({ error: e });
            });
    }).catch((err) => {
        console.log(err);
        res.status(404).json({ error: err });
    });

});

router.delete("/:id", (req, res) => {
    // path: /comments/:id
    // Deletes the comment specified
    let newComment = recipeData.getCommentById(req.params.id);
    newComment.then(() => {
        return recipeData.removeComment(req.params.id).then(() => {
            res.sendStatus(200);
        }).catch((er) => {
            res.status(500).json({ error: er });
        });
    }).catch(() => {
        res.status(404).json({ error: "Comment not found" });
    });
});

module.exports = router;