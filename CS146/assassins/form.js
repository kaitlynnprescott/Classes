function summarize() {
  var str = "First Name: " + document.getElementById("sid").value.trim() + "<br />" +
            document.getElementById("firstname").value.trim() + " " +
            document.getElementById("lastname").value.trim() + "<br />" +
            document.getElementById("address1").value.trim() + "<br />";
  var field = document.getElementById("address2").value;
  if (field != null && field.trim() != "") {
      str += field + "<br />";
  }
  str += document.getElementById("city").value.trim() + ", " +
         document.getElementById("state").value.trim() + " " + 
         document.getElementById("zipcode").value.trim() + "<br />";
  str += "Grade: ";
  var radios = document.getElementsByName("grade_year");
  for (var i = 0; i < radios.length; ++i) {
      if (radios[i].checked) {
          str += radios[i].value + "<br />";
          break;
      }
  }
  str += "Devices: ";
  var checkboxes = document.getElementsByName("devices[]");
  var selected_devices = [];
  for (var i = 0; i < checkboxes.length; ++i) {
      if (checkboxes[i].checked) {
          selected_devices.push(checkboxes[i].value);
      }
  }
  str += selected_devices + "<br />";
  str += "Date enrolled: " + document.getElementById("date_enrolled").value + "<br />";
  str += "Favorite color: " + document.getElementById("favcolor").value + "<br />";
  str += "Fun facts: " + document.getElementById("fun_facts").value.trim();
  document.getElementById("summary").innerHTML = str;
  document.getElementById("summary_wrapper").style.display = "block";
}

function reset_form() {
  document.getElementById("summary").innerHTML = "";
  document.getElementById("summary_wrapper").style.display = "none";
}