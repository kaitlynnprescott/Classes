/************************************************************************************
 * Name        : user.js
 * Author      : Kaitlynn Prescott
 * Date        : Apr 10, 2017
 * Description : CS-564 Lab 9: A Simple User Login System
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

const users = [{
        _id: "1245325124124", 
        username: "masterdetective123", 
        hashedPassword: "$2a$06$PHPllli6U0D0aXaKMVejxOfvwYISspU7kumJ.l0zVjOas/DfshYjq", 
        firstName: "Sherlock", 
        lastName: "Holmes",
        profession: "Detective",
        bio: "Sherlock Holmes (/ˈʃɜːrlɒk ˈhoʊmz/) is a fictional private detective created by British author Sir Arthur Conan Doyle. Known as a \"consulting detective\" in the stories, Holmes is known for a proficiency with observation, forensic science, and logical reasoning that borders on the fantastic, which he employs when investigating cases for a wide variety of clients, including Scotland Yard."

    }, 
    { 
        _id: "723445325124124", 
        username: "lemon", 
        hashedPassword: "$2a$06$SagJO.YW8T7c7Fzh.0VaIuYaAetQKsU2PbmI.VzzjjfWKA8yyLbQe", 
        firstName: "Elizabeth", 
        lastName: "Lemon",
        profession: "Writer",
        bio: " Elizabeth Miervaldis \"Liz\" Lemon is the main character of the American television series 30 Rock. She created and writes for the fictional comedy-sketch show The Girlie Show or TGS with Tracy Jordan." 
    }, 
    {
        _id: "23240544353345344",
        username: "theboywholived",
        hashedPassword: "$2y$10$ZFpnl0B6P2wSYD4gkzL.OuHnOKjXKBAXtW6TQalYDQAERhX8SWuQ.",
        firstName: "Harry",
        lastName: "Potter",
        profession: "Student",
        bio: "Harry Potter is a series of fantasy novels written by British author J. K. Rowling. The novels chronicle the life of a young wizard, Harry Potter, and his friends Hermione Granger and Ron Weasley, all of whom are students at Hogwarts School of Witchcraft and Wizardry . The main story arc concerns Harry's struggle against Lord Voldemort, a dark wizard who intends to become immortal, overthrow the wizard governing body known as the Ministry of Magic, and subjugate all wizards and Muggles."
    }
  ]


// getUserById
let getUserById = (id) => {
    return new Promise((fulfill, reject) => {
        if (!id) {
            throw "User ID is invalid!";
        }
        var result = users.filter(function(user) {
            return user._id === id;
        });
        if (!result[0]) {
            reject("User not found");
            return;
        }
        fulfill(result[0]);
    });
}

// getUserByUserName
let getUserByUserName = (username) => {
    return new Promise((fulfill, reject) => {
        if (!username) {
            throw "Username is invalid!";
        }
        var result = users.filter(function(user) {
            return user.username === username;
        });
        if (!result[0]) {
            reject("User not found");
            return;
        }
        fulfill(result[0]);
    });
}

module.exports = {
    getUserById,
    getUserByUserName
}
