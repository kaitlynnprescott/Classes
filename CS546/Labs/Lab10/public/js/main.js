/************************************************************************************
 * Name        : main.js
 * Author      : Kaitlynn Prescott
 * Date        : Apr 27, 2017
 * Description : CS-564 Lab 10: Fix All The Things
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

(function($) {
  const theForm = $("#email-form");
  const theEmail = $("#email");
  const theMessage = $("#message");
  const theResult = $("#the-result");

  theForm.submit(e => {
    e.preventDefault();
    const formData = {
      email: theEmail.val(),
      message: theMessage.val()
    };

    $.ajax({
      type: "POST",
      url: "/",
      data: JSON.stringify(formData),
      success: function(data) {
        console.log(`SUCCESS`);
        var resultMessage = jQuery.parseJSON(data);
        theResult.text(data.reply);
        // success
        $(`#success`).html(`<div class="alert alert-success">`);
        $(`#success > .alert-success`).append(`${resultMessage.reply}`);
        $(`#success > .alert-success`).append(`</div>`);
        //clear
        $(`#email-form`).trigger("reset");
      },
      contentType: "application/json",
      dataType: "json"
    });
  });
})(jQuery); // jQuery is exported as $ and jQuery