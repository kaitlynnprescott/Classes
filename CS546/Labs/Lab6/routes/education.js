/************************************************************************************
 * Name        : education.js
 * Author      : Kaitlynn Prescott
 * Date        : Mar 2, 2017
 * Description : CS-564 Lab 6: JSON Routes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require('express');
const router = express.Router();

router.get("/", (req, res) => {
    var school1 = {
        "Name": "Conway Elementary School",
        "Degree": "Primary School",
        "FavoriteClass": "Kindegarten-- Nap time!",
        "MemorableMemory": "My twin sister and I got to take a picture together on Pajama Day!"
    };
    var school2 = {
        "Name": "Rincon Middle School",
        "Degree": "Jr. High",
        "FavoriteClass": "Yearbook-- I actually got to do something fun for a change.",
        "MemerableMemory": "Greek Olympics Day at school and getting to wear a Toga."
    };
    var school3 = {
        "Name": "Ilvermorny",
        "Degree": "School for Witchcraft and Wizardry",
        "FavoriteClass": "ALL OF THEM, but mostly Transfiguration.",
        "MemorableMemory": "That time I almost lost my hand to a velociraptor."
    };
    var school4 = {
        "Name": "Stevens Institute of Technology",
        "Degree": "Bachelors",
        "FavoriteClass": "Web Programming",
        "MemorableMemory": "Learning about programming"
    }; 

    educationData = {
        "school1": school1,
        "school2": school2,
        "school3": school3,
        "school4": school4
    };
    res.json(educationData);
});

module.exports = router;