/************************************************************************************
 * Name        : app.js
 * Author      : Kaitlynn Prescott
 * Date        : Apr 27, 2017
 * Description : CS-564 Lab 10: Fix All The Things
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const path = require("path");

app.use("/public", express.static(__dirname + "/public"));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.post("/", (req, res) => {
  const email = req.body.email;
  const message = req.body.message;

  console.log(`******Test******`);
  console.log(email);
  console.log(message);

  const dataResponse = {
    email: email,
    message: message,
    reply: `[${email}]: ${message}`
  };

  res.json(JSON.stringify(dataResponse));
});

app.get("/", (req, res) => {
  res.sendFile(path.resolve(__dirname, "index.html"));
});

app.listen(3000, () => {
  console.log("We've now got a server!");
  console.log("Your routes will be running on http://localhost:3000");
});