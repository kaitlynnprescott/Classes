function is_numeric(val) 
{
  return val !== null && val !== "" && !isNaN(val);
}
  
function who_is_older(your_age) 
{
  const MY_AGE = 36;
  if (your_age < MY_AGE) 
  { 
    return "I am older than you.";
  }
  if (your_age > MY_AGE)
  {
    return "You are older than I.";
  }
  if (your_age == MY_AGE)
  {
    return "We are the same age.";
  }
  return "";
}

function log_to_page(message)
{
  var node = document.createElement("p");
  var textnode = document.createTextNode(message);
  node.appendChild(textnode);
  document.body.appendChild(node);
}

function swap(array, a, b )
{
  var temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}
  
function selection_sort(array)
{
  
  for (var i = 0; i < array.length - 1; i++)
  {
    var min_index = i;
    for (var j = i + 1; j < array.length; j++)
    {
      if (array[j] < array[min_index])
      {
        min_index = j;
      }
    }
    if (min_index != i)
    {
      swap(array, min_index, i);
    }
  }
}

