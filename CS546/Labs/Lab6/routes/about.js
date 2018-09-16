/************************************************************************************
 * Name        : about.js
 * Author      : Kaitlynn Prescott
 * Date        : Mar 2, 2017
 * Description : CS-564 Lab 6: JSON Routes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require('express');
const router = express.Router();

router.get("/", (req, res) => {
    var biography = "I'm going to tell you a little bit about myself. I went to a wizard school, but SHH! It's a secret! I learned all I could, and got put on special assignment to learn more about you people, the ones without magic! That's how I ended up at Stevens, my people want to learn more about the ways you muggles do things without magic, and I must say, it's mesmerizing! You guys come up with some pretty cool things! The internet? So COOL! I got a little off topic! Anyway, I'm from California. It's this mystical land out west, most people have heard of it. A lot of people here think it's a very strange place, full of weird people and customs, but to me, it's home! A lot of wizards live in California, and come to think of it, that's probably why everyone thinks people from California are weird... Anyway, thats me!"
    aboutData = {
        "name": "Katie Prescott",
        "biography": biography,
        "favoriteShows": ["Harry Potter -- Oh wait, did you say TV shows? Well, it's a series, so it counts to me.", "Game Of Thrones", "Gilmore Girls", "Teen Wolf", "Timeless", "The Magicians", "Breaking Bad"],
        "hobbies": ["Watching Harry Potter", "Knitting", "Netflix", "Eating Ice Cream", "Playing with my dog"]
    };
    res.json(aboutData);
});

module.exports = router;