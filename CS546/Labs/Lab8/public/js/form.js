/************************************************************************************
 * Name        : form.js
 * Author      : Kaitlynn Prescott
 * Date        : Apr 4, 2017
 * Description : CS-564 Lab 8: Palindromes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/


(function () {
    let palindromeMethods = {};

    function check_palindrome(str) {
        // remove spaces and punctuation and make it all lowercase
        if (typeof str !== "string") throw "Must provide a string";
        if (str === "") throw "Must enter a string";
        var removeChar = str.replace(/[\W_]/g,'').toLowerCase();
        // reverse string
        var checker = removeChar.split('').reverse().join('');
        // check if they are the same
        return checker === removeChar;
    }

    var staticForm = document.getElementById("static-form");

    if (staticForm) {
        var stringElement = document.getElementById("string1");

        var errorContainer = document.getElementById("error-container");
        
        var errorTextElement = errorContainer.getElementsByClassName("text-goes-here")[0];

        var ispalindromeContainer = document.getElementById("palindrome-container");

        var notpalindromeContainer = document.getElementById("notpalindrome-container");

        staticForm.addEventListener("submit", (event) => {
            event.preventDefault();

            try {
                errorContainer.classList.add("hidden");
                var value = stringElement.value;
                var result = check_palindrome(value);
                if (result) {
                    var ul = document.getElementById("palindromes");
                    var li = document.createElement("li");
                    li.appendChild(document.createTextNode(value));
                    ul.appendChild(li);
                    ispalindromeContainer.classList.remove("hidden");
                } else {
                    var ul = document.getElementById("notpalindromes");
                    var li = document.createElement("li");
                    li.appendChild(document.createTextNode(value));
                    ul.appendChild(li);
                    notpalindromeContainer.classList.remove("hidden");
                }
            } catch (e) {
                var message = typeof e === "string" ? e : e.message;
                errorTextElement.textContent = e;
                errorContainer.classList.remove("hidden");
            }
        });
    }
})();